#ifndef CLIENTCREDENTIALSFLOW_H
#define CLIENTCREDENTIALSFLOW_H

#include <QUrl>
#include <QDebug>
#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>

// @formatter:off
class ClientCredentialsFlow {
	public:
		static QJsonObject getToken(
			const QString &clientId,
			const QString &clientSecret,
			const QString &oAuthUrl = QString("https://osu.ppy.sh/oauth/token")
		);
};
// @formatter:on

#endif // CLIENTCREDENTIALSFLOW_H
