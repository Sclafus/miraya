#ifndef BACKUP_H
#define BACKUP_H

#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QMessageBox>
#include <QObject>
#include <QSettings>

// @formatter:off
class Backup {
	public:
		static void backup(QString filePath, bool includeSensitiveInfo);
		static void restore(const QString &filePath);
};
// @formatter:on

#endif // BACKUP_H
