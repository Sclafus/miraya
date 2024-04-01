#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QStringList>
#include <QRegularExpression>

class Utils {
	public:
		static QStringList getOsuBeatmapUrls(const QString &message);
		static QStringList getUrls(const QString &message);
		static int getBeatmapIdFromOsuBeatmapLink(const QString &link);
};

#endif // UTILS_H
