#include "twitchClient.h"

#include <utility>

[[maybe_unused]] TwitchClient::TwitchClient(
			 QUrl url,
			 QString botNick,
			 QString oauth,
			 QString channel,
			 QObject *parent
) : QObject(parent), url(std::move(url)), oauth(std::move(oauth)), botNick(std::move(botNick)),
    channel(std::move(channel)) {
	initSignals();
}


TwitchClient::TwitchClient(QObject *parent) : QObject(parent) {
	initSignals();
}


void TwitchClient::initSignals() {
	connect(&socket, &QWebSocket::connected, this, &TwitchClient::onConnected);
	connect(&socket, &QWebSocket::textMessageReceived, this, &TwitchClient::onTextMessageReceived);
	connect(&socket, &QWebSocket::disconnected, this, &TwitchClient::onDisconnected);
}


void TwitchClient::init() {
	refreshData();
	qDebug() << "[TwitchClient] Connecting to: " << url.toString();
	socket.open(QUrl(url));
}


void TwitchClient::refreshData() {
	qDebug() << "[TwitchClient] Refreshing data...";
	QSettings settings;

	setChannel(settings.value("twitch/channel").toString());
	setBotNick(settings.value("twitch/botNick").toString());
	setOauth(settings.value("twitch/oauth").toString());
	setUrl(QUrl("ws://irc-ws.chat.twitch.tv:80"));
}


void TwitchClient::restart() {
	socket.close();
	init();
}


void TwitchClient::sendChatMessage(const QString &message) {
	qDebug() << "[TwitchClient] Sending channel message: " << message;
	socket.sendTextMessage("PRIVMSG #" + channel + " :" + message);
}


void TwitchClient::sendMessage(const QString &message) {
	qDebug() << "[TwitchClient] Sending message: " << message;
	socket.sendTextMessage(message);
}


void TwitchClient::onConnected() {
	qDebug() << "[TwitchClient] Connected to: " << url.toString();
	emit connected();
	sendMessage("PASS " + oauth);
	sendMessage("NICK " + botNick);
	sendMessage("JOIN #" + channel);
}


void TwitchClient::onTextMessageReceived(QString message) {
	auto wrappedMessage = TwitchDataWrapper(message);
	qDebug() << "[TwitchClient] Message received from: " << url.toString();

	if (shouldBeFiltered(message)) {
		qDebug() << "[TwitchClient] Message filtered";
		return;
	}

	if (isCommand(wrappedMessage.getMessage())) {
		qDebug() << "[TwitchClient] Command received";
		emit commandReceived(wrappedMessage);
	}

	emit textMessageReceived(wrappedMessage);
}


void TwitchClient::handlePing() {
	qDebug() << "[TwitchClient] Handling ping";
	sendMessage("PONG :tmi.twitch.tv");
}


bool TwitchClient::shouldBeFiltered(const QString &message) {
	// TODO: this can be done better, i think.
	if (message.startsWith("PING")) {
		handlePing();
		return true;
	}

	if (message.startsWith(":tmi.twitch.tv")) {
		return true;
	}

	if (message.startsWith(":" + botNick)) {
		return true;
	}
	return false;
}


bool TwitchClient::isCommand(const QString &message) {
	if (message.startsWith("!")) {
		return true;
	}
	return false;
}


void TwitchClient::onDisconnected() {
	qDebug() << "[TwitchClient] Disconnected from:" << url.toString();
	emit disconnected();
}


void TwitchClient::setChannel(QString newChannel) {
	channel = std::move(newChannel);
}


void TwitchClient::setBotNick(QString newBotNick) {
	botNick = std::move(newBotNick);
}


void TwitchClient::setOauth(QString newOauth) {
	oauth = std::move(newOauth);
}


void TwitchClient::setUrl(QUrl newUrl) {
	url = QUrl(std::move(newUrl));
}
