import QtQuick 2.2
import QtWebView 1.0

WebView {
    id: webView
    objectName: "webView"
    url: "https://m.facebook.com"

    signal loadingProgressChanged(int p)
    signal urlChanged(string s);
    onLoadProgressChanged:loadingProgressChanged(loadProgress), urlChanged(url)
}


