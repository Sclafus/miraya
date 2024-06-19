#ifndef GOSUMEMORYCLIENT_H
#define GOSUMEMORYCLIENT_H

#include <QDebug>
#include <QObject>
#include <QSettings>
#include <QUrl>
#include <QWebSocket>

#include "osu/data/gosu/gosumemorydatawrapper.h"

// @formatter:off
class GosumemoryClient : public QObject {
	Q_OBJECT

	public:
		explicit GosumemoryClient(QObject *parent = nullptr);
		[[maybe_unused]] explicit GosumemoryClient(QUrl url, QObject *parent = nullptr);
		void enableRead(bool enable);
		void init();
		void restart();
		void setUrl(const QUrl &newUrl);

	private:
		void initSignals();
		void refreshData();
		bool readEnabled{};
		QWebSocket socket;
		QUrl url;

	signals:
		void connected();
		void messageReceived(GosuMemoryDataWrapper message);
		void disconnected();

	public slots:
		void onConnected();
		void onTextMessageReceived(QString message);
		void onDisconnected();
};
// @formatter:on

#endif
