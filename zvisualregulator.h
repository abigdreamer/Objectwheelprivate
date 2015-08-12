#ifndef ZVISUALREGULATOR_H
#define ZVISUALREGULATOR_H

#define MOBILE_SCALE_FACTOR  2.0
#define PC_SCALE_FACTOR      1.0
#define BASE_RESOLUTION_W 1366.0
#define BASE_RESOLUTION_H  768.0

#include <QObject>
#include <QWidget>
#include <QDesktopWidget>
#include <QRect>

class ZVisualRegulator : public QObject
	{
		Q_OBJECT
	public:
		enum Platform { Pc, Mobile, Custom };
		explicit ZVisualRegulator(QObject *parent = 0);
		static void regulateWidget( QWidget* widget, const Platform platform = Pc, const bool haveLayout=true, const float customFactor=1.0 );
		static void regulateFont( QWidget* widget, const Platform platform = Pc, const float customFactor=1.0 );
		static void regulateFont( QFont& font, const Platform platform = Pc, const float customFactor=1.0 );

	signals:

	public slots:
	};

#endif // ZVISUALREGULATOR_H
