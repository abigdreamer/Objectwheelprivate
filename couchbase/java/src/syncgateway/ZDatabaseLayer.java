/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package syncgateway;
import com.couchbase.lite.CouchbaseLiteException;
import com.couchbase.lite.Database;
import com.couchbase.lite.Document;
import com.couchbase.lite.JavaContext;
import com.couchbase.lite.Manager;
import com.couchbase.lite.replicator.Replication;
import java.io.IOException;
import java.net.MalformedURLException;
import java.net.URL;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.GregorianCalendar;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.logging.Logger;
import java.lang.reflect.Type;
import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.reflect.TypeToken;
/**
 *
 * @author kozmon
 */
public class ZDatabaseLayer {
    private final static Logger PrintLog = Logger.getLogger("logger");
    private final static String TAG = "ZDatabaseLayer() : ";
    
    private String databaseName = null; // "sync_gateway";
    private String hostAddress = null;  // "http://127.0.0.1:4984/sync_gateway";
    private Manager manager = null;
    private Database database = null;
    private boolean removeRunning=false;
    
    static {
    	System.load("/home/kozmon/Projeler/Git/objectwheelprivate/couchbase/c++/zcouchbasemanager/zcouchbasemanager/build-zcouchbasemanager/libzcouchbasemanager.so");
    }
    public native void changedNativeCallBack();

    public ZDatabaseLayer() {
        System.out.println("ZDatabaseLayer STARTED !");
    }

    public boolean delCurrentDoc() {
    	removeRunning=true;
        int iterator = Integer.parseInt(database.getDocument("0").getProperty("current_id").toString());
        /* Current doc dan sonraki doclar siliniyor */
        for (int i=docCount();iterator<i;i--) {
            Document buff = database.getDocument(String.valueOf(i));
            try {
                buff.delete();
            } catch (CouchbaseLiteException ex) {
                return false;
            }
        }
        /* Current docu da sil ve bir öncekini current olarak ayarla*/
        Document buffer = database.getDocument(String.valueOf(iterator));
        try {
            buffer.delete();
        } catch (CouchbaseLiteException ex) {
            return false;
        }
        removeRunning=false;
        return setCurrentDoc(String.valueOf(docCount()-1));
    }
    
    public boolean addDoc( String json ) {
        int iterator = Integer.parseInt(database.getDocument("0").getProperty("current_id").toString());
        if (iterator < docCount()) {
            /* Current doc dan sonraki doclar siliniyor */
            for (int i=docCount();iterator<i;i--) {
                Document buff = database.getDocument(String.valueOf(i));
                try {
                    buff.delete();
                } catch (CouchbaseLiteException ex) {
                    return false;
                }
            }
            
            /* En sona yeni docu ekle ve current olarak ayarla */
            Document nextDoc = database.getDocument(String.valueOf(docCount() + 1));
            SimpleDateFormat dateFormatter = new SimpleDateFormat("yyyy-MM-dd'T'HH:mm:ss");
            Calendar calendar = GregorianCalendar.getInstance();
            String currentTimeString = dateFormatter.format(calendar.getTime());
            Map<String, Object> p = jsonToMap(json);
            p.put("created_at", currentTimeString);
            try {
                nextDoc.putProperties(p);
            } catch (CouchbaseLiteException ex) {
                return false;
            }
            return setCurrentDoc(String.valueOf(Integer.parseInt(nextDoc.getId())-1));
            
        } else {
            /* En sona yeni docu ekle ve current olarak ayarla */
            Document nextDoc = database.getDocument(String.valueOf(docCount() + 1));
            SimpleDateFormat dateFormatter = new SimpleDateFormat("yyyy-MM-dd'T'HH:mm:ss");
            Calendar calendar = GregorianCalendar.getInstance();
            String currentTimeString = dateFormatter.format(calendar.getTime());
            Map<String, Object> p = jsonToMap(json);
            p.put("created_at", currentTimeString);
            try {
                nextDoc.putProperties(p);
            } catch (CouchbaseLiteException ex) {
                return false;
            }
            return setCurrentDoc(String.valueOf(Integer.parseInt(nextDoc.getId())-1));
            
        }
    }
    
    public int docCount() {
        /* Veritabanindaki toplam doc adedini dondur (0 numara haric) */
        return database.getDocumentCount()-1;
    }
    
    public int getCurrentDocId() {
    	/* Current doc id sini döndür */
    	return (Integer.parseInt(database.getDocument("0").getProperty("current_id").toString())-1);
    }

    public boolean setCurrentDoc( String id ) {
        /* Current docu belirle */
        id = String.valueOf(Integer.parseInt(id)+1);
        Document doc = database.getDocument("0");
        Map<String, Object> properties = new HashMap<String, Object>();
        properties.putAll(doc.getProperties());
        properties.put("current_id", id);
        try {
            doc.putProperties(properties);
        } catch (CouchbaseLiteException e) {
           return false;
        }
        return true;
    }
    
    public String getCurrentDoc() {
        /* Current docu getir */
        return mapToJson(database.getDocument(database.getDocument("0").getProperty("current_id").toString()).getUserProperties());
    }
    
    public boolean open() {
        /* Db olustur */
        if (databaseName != null) {
            try {
                manager = new Manager(new JavaContext(databaseName), Manager.DEFAULT_OPTIONS);
            } catch (IOException ex) {
                return false;
            }
            try {
                database = manager.getDatabase("owdatabase");
            } catch (CouchbaseLiteException ex) {
                return false;
            }
        }
        else
            return false;
        
        if ( database.getDocumentCount() <= 0 ) {
            /* iterator docu olustur */
            Document iteratorDoc = database.getDocument("0");
            Map<String, Object> p = new HashMap<String, Object>();
            p.put("current_id", "1");
            try {
                iteratorDoc.putProperties(p);
            } catch (CouchbaseLiteException ex) {
                try {
                    iteratorDoc.delete();
                } catch (CouchbaseLiteException ex1) {
                    return false;
                }
                return false;
            }
            
            /* ilk bos docu olustur */
            SimpleDateFormat dateFormatter = new SimpleDateFormat("yyyy-MM-dd'T'HH:mm:ss");
            Calendar calendar = GregorianCalendar.getInstance();
            String currentTimeString = dateFormatter.format(calendar.getTime());
            
            Document firstDoc = database.getDocument("1");
            p.clear();
            p.put("created_at", currentTimeString);
            try {
                firstDoc.putProperties(p);
            } catch (CouchbaseLiteException ex) {
                return false;
            }
            
        }
        
        /* Cocuhbase server ile senkronizasyonu olustur */
        URL syncUrl;
        try {
            syncUrl = new URL(hostAddress);
        } catch (MalformedURLException e) {
            throw new RuntimeException(e);
        }
        Replication pullReplication = database.createPullReplication(syncUrl);
        pullReplication.setContinuous(true);
        Replication pushReplication = database.createPushReplication(syncUrl);
        pushReplication.setContinuous(true);
      
      	//Push & Pull Replication changeListeners
        pushReplication.addChangeListener(new Replication.ChangeListener() {
            @Override
            public void changed(Replication.ChangeEvent event) {
                // will be called back when the push replication status changes
                Replication replication = event.getSource();
                PrintLog.info(TAG+ "Push Replication : " + replication + " changed.");
                if (!replication.isRunning()) {
                    String msg = String.format("Push Replicator %s not running", replication);
                    PrintLog.info(TAG+ msg);
                }
                else {
                    int processed = replication.getCompletedChangesCount();
                    int total = replication.getChangesCount();
                    String msg = String.format("Push Replicator processed %d / %d", processed, total);
                    PrintLog.info(TAG+ msg);
                }
                if (event.getError() != null) {
                    PrintLog.info("Push Sync error--"+ event.getError().toString());
                }
            }
        });
        
        pullReplication.addChangeListener(new Replication.ChangeListener() {
            @Override
            public void changed(Replication.ChangeEvent event) {
                // will be called back when the pull replication status changes
                Replication replication = event.getSource();
                PrintLog.info(TAG+ "Pull Replication : " + replication + " changed.");
                if (!replication.isRunning()) {
                    String msg = String.format("Pull Replicator %s not running", replication);
                    PrintLog.info(TAG+ msg);
                }
                else {
                    int processed = replication.getCompletedChangesCount();
                    int total = replication.getChangesCount();
                    String msg = String.format("Pull Replicator processed %d / %d", processed, total);
                    PrintLog.info(TAG+ msg);
                }
                if (event.getError() != null) {
                    PrintLog.info("Pull Sync error--"+ event.getError().toString());
                }
            }
        });

        database.addReplication(pushReplication);
        database.addReplication(pullReplication);
        startSync();
        startChangeListener();
        return true;
    }
    
    public void setDatabaseName( final String dbname ) {
        databaseName = dbname;
    }
    
    public void setHostAddress( final String haddress ) {
        hostAddress = haddress;
    }
    
    private Map<String, Object> jsonToMap( String json ) {
        Gson gson = new Gson();
        Type stringStringMap = new TypeToken<Map<String, Object>>(){}.getType();
        Map<String,Object> map = gson.fromJson(json, stringStringMap);
        return map;
    }

    private String mapToJson(Map<String,Object> map) {
    	Gson gson = new GsonBuilder().enableComplexMapKeySerialization()
        .setPrettyPrinting().create();
		return gson.toJson(map);
    }

    public void startSync() {
        /* Replikasyonlari baslat */
        List<Replication> replications = database.getAllReplications();
        for (int i=0;i<replications.size();i++)
            replications.get(i).start();
    }
    
    public void stopSync() {
        /* Replikasyonlari durdur */
        List<Replication> replications = database.getAllReplications();
        for (int i=0;i<replications.size();i++)
            replications.get(i).stop();
    }
    
    public void startChangeListener() {
        if(database != null) {
         database.addChangeListener(new Database.ChangeListener() {
             @Override
             public void changed(Database.ChangeEvent event) {
                 //
                 // Call native changeListener
                 //
             	if(removeRunning==false) {
             		System.out.println("ZDatabaseLayer : Change Event Called!");
             		changedNativeCallBack();
                	}
                }

            });
        } 
    }
}
