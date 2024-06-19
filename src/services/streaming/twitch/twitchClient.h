#ifndef TWITCHCLIENT_H
#define TWITCHCLIENT_H

#include <QDebug>
#include <QObject>
#include <QSettings>
#include <QString>
#include <QUrl>
#include <QWebSocket>

#include "twitchdatawrapper.h"

// @formatter:off
class TwitchClient : public QObject {
	Q_OBJECT

	public:
		explicit TwitchClient(QObject *parent = nullptr);
		[[maybe_unused]] explicit TwitchClient(
			QUrl url,
			QString botNick,
			QString oauth,
			QString channel,
			QObject *parent = nullptr
		);
		void init();
		void restart();
		void setChannel(QString newChannel);
		void setBotNick(QString newBotNick);
		void setOauth(QString newOauth);
		void setUrl(QUrl newUrl);
		void sendChatMessage(const QString& message);

	private:
		void handlePing();
		static bool isCommand(const QString& message);
		void initSignals();
		void refreshData();
		void sendMessage(const QString& message);
		bool shouldBeFiltered(const QString& message);
		QWebSocket socket;
		QUrl url;
		QString oauth;
		QString botNick;
		QString channel;

	signals:
		void connected();
		void textMessageReceived(TwitchDataWrapper message);
		void commandReceived(TwitchDataWrapper command);
		void disconnected();

	public slots:
		void onConnected();
		void onTextMessageReceived(QString message);
		void onDisconnected();
};
// @formatter:on

#endif
