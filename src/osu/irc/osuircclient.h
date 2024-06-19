#ifndef OSUIRCCLIENT_H
#define OSUIRCCLIENT_H

#include <QObject>
#include <QJsonObject>
#include <QSettings>
#include <QTcpSocket>
#include <QUrl>

#include "twitchdatawrapper.h"

// @formatter:off
class OsuIrcClient : public QObject {
	Q_OBJECT

	public:
		explicit OsuIrcClient(QObject *parent = nullptr);
		[[maybe_unused]] explicit OsuIrcClient(
				QString nickname,
				QString password,
				QString server,
				const int &port,
				QObject *parent = nullptr
		);
		void init();
		void initSignals();
		void restart();
		void setNickname(const QString &newNickname);
		void setPassword(const QString &newPassword);
		void setServer(const QString &newServer);
		void setPort(const int &newPort);
		void sendPrivmsg(const QString &message);
		void sendMap(const QUrl &url, TwitchDataWrapper message);
		void sendMap(QJsonObject map, TwitchDataWrapper message);

	private:
		void handlePing();
		void refreshData();
		QString nickname;
		QString password;
		QString server;
		int port{};
		QTcpSocket socket;

	signals:
		void connected();
		void readyRead();
		void disconnected();

	public slots:
		void onConnected();
		void onReadyRead();
		void onDisconnected();
};
// @formatter:on

#endif // OSUIRCCLIENT_H
