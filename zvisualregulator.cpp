#include "zvisualregulator.h"

ZVisualRegulator::ZVisualRegulator(QObject *parent) : QObject(parent)
	{

	}

void ZVisualRegulator::regulateWidget(QWidget* widget, const ZVisualRegulator::Platform platform, const bool haveLayout, const float customFactor)
	{
	QDesktopWidget dwidget;
	QRect mainScreenSize = dwidget.screenGeometry( dwidget.primaryScreen() );

	float ratioConstantH = ( mainScreenSize.width() / BASE_RESOLUTION_W );
	float ratioConstantV = ( mainScreenSize.height() / BASE_RESOLUTION_H );

	if (ratioConstantH>ratioConstantV)
		ratioConstantH=ratioConstantV;
	else
		ratioConstantV=ratioConstantH;

	switch (platform)
		{
		case Pc:
			{
			if (haveLayout==true)
				{
				widget->setMinimumHeight(widget->minimumHeight()*ratioConstantH*PC_SCALE_FACTOR);
				widget->setMaximumHeight(widget->maximumHeight()*ratioConstantH*PC_SCALE_FACTOR);
				widget->setMinimumWidth(widget->minimumWidth()*ratioConstantH*PC_SCALE_FACTOR);
				widget->setMaximumWidth(widget->maximumWidth()*ratioConstantH*PC_SCALE_FACTOR);
				}
			else
				{
				widget->setGeometry(widget->x()*ratioConstantH*PC_SCALE_FACTOR,
									widget->y()*ratioConstantH*PC_SCALE_FACTOR,
									widget->width()*ratioConstantH*PC_SCALE_FACTOR,
									widget->height()*ratioConstantH*PC_SCALE_FACTOR);
				}
			break;
			}

		case Mobile:
			{
			if (haveLayout==true)
				{
				widget->setMinimumHeight(widget->minimumHeight()*ratioConstantH*MOBILE_SCALE_FACTOR);
				widget->setMaximumHeight(widget->maximumHeight()*ratioConstantH*MOBILE_SCALE_FACTOR);
				widget->setMinimumWidth(widget->minimumWidth()*ratioConstantH*MOBILE_SCALE_FACTOR);
				widget->setMaximumWidth(widget->maximumWidth()*ratioConstantH*MOBILE_SCALE_FACTOR);
				}
			else
				{
				widget->setGeometry(widget->x()*ratioConstantH*MOBILE_SCALE_FACTOR,
									widget->y()*ratioConstantH*MOBILE_SCALE_FACTOR,
									widget->width()*ratioConstantH*MOBILE_SCALE_FACTOR,
									widget->height()*ratioConstantH*MOBILE_SCALE_FACTOR);
				}
			break;
			}

		case Custom:
			{
			if (haveLayout==true)
				{
				widget->setMinimumHeight(widget->minimumHeight()*ratioConstantH*customFactor);
				widget->setMaximumHeight(widget->maximumHeight()*ratioConstantH*customFactor);
				widget->setMinimumWidth(widget->minimumWidth()*ratioConstantH*customFactor);
				widget->setMaximumWidth(widget->maximumWidth()*ratioConstantH*customFactor);
				}
			else
				{
				widget->setGeometry(widget->x()*ratioConstantH*customFactor,
									widget->y()*ratioConstantH*customFactor,
									widget->width()*ratioConstantH*customFactor,
									widget->height()*ratioConstantH*customFactor);
				}
			break;
			}

		default:
			qWarning("ZVisualRegulator : Forbidden parameters");
			break;

		}
	}

void ZVisualRegulator::regulateFont(QWidget* widget, const ZVisualRegulator::Platform platform, const float customFactor)
	{
	QDesktopWidget dwidget;
	QRect mainScreenSize = dwidget.screenGeometry( dwidget.primaryScreen() );

	float ratioConstantH = ( mainScreenSize.width() / BASE_RESOLUTION_W );
	float ratioConstantV = ( mainScreenSize.height() / BASE_RESOLUTION_H );

	if (ratioConstantH>ratioConstantV)
		ratioConstantH=ratioConstantV;
	else
		ratioConstantV=ratioConstantH;

	switch (platform)
		{
		case Pc:
			{
			QFont f = widget->font();
			f.setPointSizeF(f.pointSizeF()*ratioConstantH*PC_SCALE_FACTOR);
			widget->setFont(f);
			break;
			}

		case Mobile:
			{
			QFont f = widget->font();
			f.setPointSizeF(f.pointSizeF()*ratioConstantH*MOBILE_SCALE_FACTOR);
			widget->setFont(f);
			break;
			}

		case Custom:
			{
			QFont f = widget->font();
			f.setPointSizeF(f.pointSizeF()*ratioConstantH*customFactor);
			widget->setFont(f);
			break;
			}

		default:
			qWarning("ZVisualRegulator : Forbidden parameters");
			break;

		}
	}

void ZVisualRegulator::regulateFont(QFont& font, const ZVisualRegulator::Platform platform, const float customFactor)
	{
	QDesktopWidget dwidget;
	QRect mainScreenSize = dwidget.screenGeometry( dwidget.primaryScreen() );

	float ratioConstantH = ( mainScreenSize.width() / BASE_RESOLUTION_W );
	float ratioConstantV = ( mainScreenSize.height() / BASE_RESOLUTION_H );

	if (ratioConstantH>ratioConstantV)
		ratioConstantH=ratioConstantV;
	else
		ratioConstantV=ratioConstantH;

	switch (platform)
		{
		case Pc:
			{
			font.setPointSizeF(font.pointSizeF()*ratioConstantH*PC_SCALE_FACTOR);
			break;
			}

		case Mobile:
			{
			font.setPointSizeF(font.pointSizeF()*ratioConstantH*MOBILE_SCALE_FACTOR);
			break;
			}

		case Custom:
			{
			font.setPointSizeF(font.pointSizeF()*ratioConstantH*customFactor);
			break;
			}

		default:
			qWarning("ZVisualRegulator : Forbidden parameters");
			break;

		}
	}

float ZVisualRegulator::getRatio()
	{
	QDesktopWidget dwidget;
	QRect mainScreenSize = dwidget.screenGeometry( dwidget.primaryScreen() );

	float ratioConstantH = ( mainScreenSize.width() / BASE_RESOLUTION_W );
	float ratioConstantV = ( mainScreenSize.height() / BASE_RESOLUTION_H );

	if (ratioConstantH>ratioConstantV)
		ratioConstantH=ratioConstantV;
	else
		ratioConstantV=ratioConstantH;

	return ratioConstantH;
	}

