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

#include "zlayout.h"
float ZLayout::ratioConstantH = 0;
float ZLayout::ratioConstantV = 0;

ZLayout::ZLayout()
	{
	cW=0;
	mW=0;
	aspectRatioProtected=false;
	started=false;
	}

void ZLayout::addItem(QWidget *widget, int mode, int align)
	{
	widgetList.push_back(widget);
	modeList.push_back(mode);
	alignList.push_back(align);
	widgetRects.push_back(widget->frameGeometry());
	}

void ZLayout::initMainWidgets(QWidget *centralWidget, QWidget *middleWidget)
	{
	cW=centralWidget;
	mW=middleWidget;
	mwRect=mW->frameGeometry();

	if (ratioConstantH <= 0)
		{
		ratioConstantH = ((float)(cW->width()))/mwRect.width();
		ratioConstantV = ((float)(cW->height()))/mwRect.height();
		if (aspectRatioProtected)
			{
			if (ratioConstantH>ratioConstantV)
				ratioConstantH=ratioConstantV;
			else
				ratioConstantV=ratioConstantH;
			}
		}
	}

void ZLayout::removeWidgetOf(QWidget* widget)
	{
	int index=widgetList.indexOf(widget);
	if (index!=-1){
		widgetList.removeAt(index);
		widgetRects.removeAt(index);
		modeList.removeAt(index);
		alignList.removeAt(index);
		}
	}

void ZLayout::setAspectRatioProtected(bool boolean)
	{
	aspectRatioProtected=boolean;
	}

int ZLayout::indexOf(QWidget* widget) const
	{
	///Returns -1 if no item matched.
	return widgetList.indexOf(widget);
	}

int ZLayout::size() const
	{
	return widgetList.size();
	}

void ZLayout::clearAllItem()
	{
	widgetRects.clear();
	widgetList.clear();
	modeList.clear();
	alignList.clear();
	}

bool ZLayout::isNull()
	{
	if (mW==0 || cW==0)
		{
		qWarning("ZLayout: in isNull() function, Main widgets was not added.");
		return true;
		}

	if (widgetList.isEmpty())
		{
		qWarning("ZLayout: in isNull() function, Child widgets was not added.");
		return true;
		}

	return false;
	}

void ZLayout::updateWidgets()
	{
	if (started)
		{
		if (!this->isNull())
			{

			for (int i=0;i<widgetList.size();i++)
				///
				if (modeList[i]==KeepOnlyWidth && alignList[i]==AlignRight)
					widgetList[i]->setGeometry((widgetRects[i].x()+widgetRects[i].width())*ratioConstantH-widgetRects[i].width(),
											   widgetRects[i].y()*ratioConstantV,
											   widgetRects[i].width(),
											   widgetRects[i].height()*ratioConstantV);

				else if (modeList[i]==KeepOnlyWidth && alignList[i]==AlignLeft)
					widgetList[i]->setGeometry(widgetRects[i].x()*ratioConstantH,
											   widgetRects[i].y()*ratioConstantV,
											   widgetRects[i].width(),
											   widgetRects[i].height()*ratioConstantV);
			///
				else if (modeList[i]==KeepOnlyHeigt && alignList[i]==AlignTop)
					widgetList[i]->setGeometry(widgetRects[i].x()*ratioConstantH,
											   widgetRects[i].y()*ratioConstantV,
											   widgetRects[i].width()*ratioConstantH,
											   widgetRects[i].height());

				else if (modeList[i]==KeepOnlyHeigt && alignList[i]==AlignBottom)
					widgetList[i]->setGeometry(widgetRects[i].x()*ratioConstantH,
											   (widgetRects[i].y()+widgetRects[i].height())*ratioConstantV-widgetRects[i].height(),
											   widgetRects[i].width()*ratioConstantH,
											   widgetRects[i].height());
			///
				else if (modeList[i]==KeepWidthHeight && alignList[i]==AlignTopLeft)
					widgetList[i]->setGeometry(widgetRects[i].x()*ratioConstantH,
											   widgetRects[i].y()*ratioConstantV,
											   widgetRects[i].width(),
											   widgetRects[i].height());

				else if (modeList[i]==KeepWidthHeight && alignList[i]==AlignTopRight)
					widgetList[i]->setGeometry((widgetRects[i].x()+widgetRects[i].width())*ratioConstantH-widgetRects[i].width(),
											   widgetRects[i].y()*ratioConstantV,
											   widgetRects[i].width(),
											   widgetRects[i].height());

				else if (modeList[i]==KeepWidthHeight && alignList[i]==AlignBottomLeft)
					widgetList[i]->setGeometry(widgetRects[i].x()*ratioConstantH,
											   (widgetRects[i].y()+widgetRects[i].height())*ratioConstantV-widgetRects[i].height(),
											   widgetRects[i].width(),
											   widgetRects[i].height());

				else if (modeList[i]==KeepWidthHeight && alignList[i]==AlignBottomRight)
					widgetList[i]->setGeometry((widgetRects[i].x()+widgetRects[i].width())*ratioConstantH-widgetRects[i].width(),
											   (widgetRects[i].y()+widgetRects[i].height())*ratioConstantV-widgetRects[i].height(),
											   widgetRects[i].width(),
											   widgetRects[i].height());
			///
				else if (modeList[i]==KeepNot)
					widgetList[i]->setGeometry(widgetRects[i].x()*ratioConstantH,
											   widgetRects[i].y()*ratioConstantV,
											   widgetRects[i].width()*ratioConstantH,
											   widgetRects[i].height()*ratioConstantV);

			mW->setGeometry(mwRect.x()*ratioConstantH,
							mwRect.y()*ratioConstantV,
							mwRect.width()*ratioConstantH,
							mwRect.height()*ratioConstantV);

			}
		}
	}
