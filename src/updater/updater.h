#ifndef UPDATER_H
#define UPDATER_H

#include <QCoreApplication>
#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>
#include <QVersionNumber>

#include "updaterurls.h"
#include "version.h"

// @formatter:off
class Updater : public QObject {
	Q_OBJECT
	public:
		explicit Updater(QObject *parent = nullptr);
		void checkVersion();

	signals:
		void newVersionAvailable();

	private:
		void onReplyFinished(QNetworkReply *reply);
		static QUrl getUrl();
		static Version getLatestVersion(const QJsonDocument& json);
};
// @formatter:on

#endif // UPDATER_H
