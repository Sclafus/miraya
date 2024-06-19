#ifndef THEME_H
#define THEME_H

#include <QDebug>
#include <QStyleFactory>
#include <QObject>
#include <QSettings>
#include <QPalette>
#include <QColor>
#include <QApplication>

// @formatter:off
class Theme : public QObject {
	Q_OBJECT

	public:
		static void loadTheme();
	private:
		static void loadDarkMode();
		static void loadLightMode();
		static void loadThemeFromSetting(const QVariant& darkModeSettings);
		static void loadDefaultThemeWindows();
};
// @formatter:on

#endif // THEME_H
