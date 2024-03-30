#include "version.h"

Version::Version(const QVersionNumber &version, const QString &suffix) {
	this->version = version;
	this->suffix = suffix;
}

Version Version::fromString(const QString &versionString) {
	qsizetype suffixIndex;
	auto v = QVersionNumber::fromString(versionString, &suffixIndex);
	auto suffix = versionString.mid(suffixIndex);
	qDebug() << "[Version] parsed version" << v << "with suffix" << suffix;
	return {v, suffix};
}

bool Version::isPrerelease() const {
	return suffix != "";
}

QString Version::toString() const {
	return version.toString() + suffix;
}


bool Version::operator>(const Version &other) const {
	//	local version is newer than remote
	if (this->version > other.version) {
		return true;
	}
	//	version is equal and no suffix
	if (this->version == other.version && this->suffix.isEmpty() && other.suffix.isEmpty()) {
		return false;
	}

	if (this->version == other.version && this->suffix.isEmpty() && !other.suffix.isEmpty()) {
		return true;
	}

	//	local version is equal to remote
	if (this->version == other.version && !this->suffix.isEmpty() && !other.suffix.isEmpty()) {
		// let's check the suffix
		auto preReleaseType = this->suffix.split(".")[0];
		auto otherPreReleaseType = other.suffix.split(".")[0];
		if (preReleaseType > otherPreReleaseType) {
			return true;
		} else if (preReleaseType < otherPreReleaseType) {
			return false;
		}
		//	both are alpha/beta/rc versions, let's check the number at the end
		auto preReleaseNumber = this->suffix.split(".")[1];
		auto otherPreReleaseNumber = other.suffix.split(".")[1];
		if (preReleaseNumber > otherPreReleaseNumber) {
			return true;
		}
		return false;
	}
	return false;
}

bool Version::operator==(const Version &other) const {
	return this->version == other.version && this->suffix == other.suffix;
}

bool Version::operator>=(const Version &other) const {
	return *this > other || *this == other;
}
