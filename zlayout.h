/****************************************************************************
**
** Copyright (C) 2015 Omer Goktas.
** Contact: kozmon@hotmail.com
**
** ZLayout, auto expandable free layout for Qt Creator. This file is part
** of the ZLayout.
**
** Commercial License Usage
** Licensees holding valid commercial ZLayout licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Omer Goktas. For further information
** use my email address.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
****************************************************************************/

#ifndef ZLAYOUT_H
#define ZLAYOUT_H


#include <QObject>
#include <QWidget>
#include <QVector>
#include <QtGlobal>
#include <QRect>

class ZLayout : public QObject
	{
		Q_OBJECT
	private:
		QVector<QWidget*> widgetList;
		QVector<QRect> widgetRects;
		QVector<int> modeList;
		QVector<int> alignList;
		QRect mwRect;
		QWidget *cW, *mW;
		bool aspectRatioProtected;
		bool isNull();
		bool started;
		static float ratioConstantH;
		static float ratioConstantV;

	public:
		/// if a property keeped, it don't change in runtime
		enum { KeepWidthHeight=0, KeepOnlyWidth=1,
			   KeepOnlyHeigt=2, KeepNot=3,
			   AlignLeft=4, AlignRight=5,
			   AlignTop=6, AlignBottom=7,
			   AlignTopLeft=8, AlignTopRight=9,
			   AlignBottomLeft=10, AlignBottomRight=11, NoAlign=12};
		ZLayout();
		void addItem(QWidget *widget, int mode=KeepNot, int align=NoAlign);
		void initMainWidgets(QWidget *centralWidget, QWidget *middleWidget);
		void clearAllItem();
		void removeWidgetOf(QWidget *widget);
		void setAspectRatioProtected(bool boolean);
		int indexOf(QWidget *widget) const;
		int size() const;

		void stop()
			{started=false;}
		void start()
			{started=true;}
	public slots:
		void updateWidgets();

	};


#endif // ZLAYOUT_H
