#include "updater.h"

Updater::Updater(QObject *parent)
		: QObject{parent} {
}

void Updater::checkVersion() {
	qDebug() << "[Updater] starting version check";
	auto *manager = new QNetworkAccessManager(this);
	auto url = getUrl();
	connect(manager, &QNetworkAccessManager::finished, this, &Updater::onReplyFinished);

	QNetworkRequest request(url);
	request.setHeader(QNetworkRequest::UserAgentHeader, "Miraya");
	manager->get(request);
	qDebug() << "[Updater] version check request sent";
}

void Updater::onReplyFinished(QNetworkReply *reply) {
	qDebug() << "[Updater] version reply received";
	if (reply->error() != QNetworkReply::NoError) {
		return;
	}

	QByteArray responseData = reply->readAll();
	QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);

	auto latestVersion = getLatestVersion(jsonDoc);
	auto currentVersion = Version::fromString(QCoreApplication::applicationVersion());
	qDebug() << "[Updater] current version: " << currentVersion.toString();
	qDebug() << "[Updater] latest version: " << latestVersion.toString();


	if (currentVersion >= latestVersion) {
		qDebug() << "[Updater] already running on latest or pre-release version";
		return;
	}
	emit newVersionAvailable();
}


QUrl Updater::getUrl() {
	auto url = QUrl(UpdaterUrls::latestStable);

	auto const version = Version::fromString(QCoreApplication::applicationVersion());

	if (version.isPrerelease()) {
		url = QUrl(UpdaterUrls::allReleases);
	}
	qDebug() << "[Updater] url: " << url.toString();
	return url;
}

Version Updater::getLatestVersion(const QJsonDocument &json) {
	QString version;
	if (json.isArray()) {
		auto array = json.array();
		auto first = array.at(0).toObject();
		version = first.value("tag_name").toString();
	} else {
		version = json.object().value("tag_name").toString();
	}
	qDebug() << "[Updater] latest version: " << version;
	return Version::fromString(version);
}
