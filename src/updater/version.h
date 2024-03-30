#ifndef MIRAYA_VERSION_H
#define MIRAYA_VERSION_H

#include <QVersionNumber>
#include <QDebug>

class Version {
	public:
		Version(const QVersionNumber& version, const QString& suffix);
		static Version fromString(const QString& versionString);

		[[nodiscard]] bool isPrerelease() const;
		[[nodiscard]] QString toString() const;

		bool operator>(const Version& other) const;
		bool operator==(const Version& other) const;
		bool operator>=(const Version& other) const;

		QVersionNumber version;
		QString suffix;

};


#endif //MIRAYA_VERSION_H
