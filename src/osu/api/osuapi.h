#ifndef OSUAPI_H
#define OSUAPI_H

#include <QUrl>
#include <QSettings>
#include <QDebug>
#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>

#include "api/auth/clientCredentialsFlow.h"

// @formatter:off
class OsuApi : public QObject {
	public:
		OsuApi();
		QJsonObject getBeatmapInfo(int beatmapId);
		bool isValid();

	private:
		QString clientId;
		QString clientSecret;
		QString oAuthUrl;
		QJsonObject token;
};
// @formatter:on

#endif // OSUAPI_H
