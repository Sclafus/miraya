#include "osuircclient.h"

#include <utility>

[[maybe_unused]] OsuIrcClient::OsuIrcClient(
		QString nickname,
		QString password,
		QString server,
		const int &port,
		QObject *parent
) : QObject(parent), nickname(std::move(nickname)), password(std::move(password)), server(std::move(server)),
    port(port) {
	initSignals();
}


OsuIrcClient::OsuIrcClient(QObject *parent) : QObject(parent) {
	initSignals();
}


void OsuIrcClient::initSignals() {
	connect(&socket, &QTcpSocket::connected, this, &OsuIrcClient::onConnected);
	connect(&socket, &QTcpSocket::readyRead, this, &OsuIrcClient::onReadyRead);
	connect(&socket, &QTcpSocket::disconnected, this, &OsuIrcClient::onDisconnected);
}


void OsuIrcClient::init() {
	refreshData();
	qDebug() << "[osu!IRC] Connecting to: " << server << ":" << port;

	socket.connectToHost(server, port);
	socket.write("PASS " + password.toLocal8Bit() + "\r\n");
	socket.write("USER " + nickname.toLocal8Bit() + " " + nickname.toLocal8Bit() + " " + nickname.toLocal8Bit() + " :" +
	             nickname.toLocal8Bit() + "\r\n");
	socket.write("NICK " + nickname.toLocal8Bit() + "\r\n");

	sendPrivmsg("Ready to process requests!");
}


void OsuIrcClient::refreshData() {
	qDebug() << "[osu!IRC] Refreshing data...";
	QSettings settings;

	setNickname(settings.value("osuirc/nick").toString());
	setPassword(settings.value("osuirc/password").toString());
	setServer(settings.value("osuirc/server").toString());
	setPort(settings.value("osuirc/port").toInt());
}


void OsuIrcClient::restart() {
	socket.close();
	init();
}


void OsuIrcClient::onConnected() {
	qDebug() << "[osu!IRC] Connected to: " << socket.peerAddress().toString();
	emit connected();
}


void OsuIrcClient::onDisconnected() {
	qDebug() << "[osu!IRC] Disconnected from: " << socket.peerAddress().toString();
	emit disconnected();
}


void OsuIrcClient::setNickname(const QString &newNickname) {
	nickname = newNickname;
}


void OsuIrcClient::setPassword(const QString &newPassword) {
	password = newPassword;
}


void OsuIrcClient::setServer(const QString &newServer) {
	server = newServer;
}


void OsuIrcClient::setPort(const int &newPort) {
	port = newPort;
}


void OsuIrcClient::sendPrivmsg(const QString &message) {
	socket.write("PRIVMSG " + nickname.toLocal8Bit() + " :" + message.toLocal8Bit() + "\r\n");
}


void OsuIrcClient::sendMap(const QUrl &url, TwitchDataWrapper message) {
	qDebug() << "[osu!IRC] Sending map-request: " << url.toString() << " by " << message.getUsername();

	QString msg = QString("[%1 Map request] sent by %2").arg(url.toString(), message.getUsername());
	sendPrivmsg(msg);
}

void OsuIrcClient::sendMap(QJsonObject map, TwitchDataWrapper message) {
	QString requestor = message.getUsername();
	QString artist = map["beatmapset"].toObject()["artist"].toString();
	QString title = map["beatmapset"].toObject()["title"].toString();
	QString status = map["beatmapset"].toObject()["status"].toString();
	int mapId = map["id"].toInt();
	QString url = QString("https://osu.ppy.sh/b/%1").arg(mapId);

	qDebug() << "[osu!IRC] Sending map-request: " << url << " by " << requestor << " (" << artist << " - " << title
	         << " - " << status << ")";

	QString msg = QString("(%1) [%2 %3 - %4] sent by %5")
			.arg(status, url, artist, title, message.getUsername());

	sendPrivmsg(msg);
}

void OsuIrcClient::handlePing() {
	socket.write("PONG :\r\n");
	qDebug() << "[osu!IRC] PING request handled";
}

void OsuIrcClient::onReadyRead() {
	auto data = QString(socket.readAll());

	if (data.contains("PING")) {
		handlePing();
	}
	emit readyRead();
}
