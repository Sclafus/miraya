#ifndef MIRAYA_UPDATERURLS_H
#define MIRAYA_UPDATERURLS_H

#include <QObject>

class UpdaterUrls{
	public:
		constexpr static const char* latestStable = "https://api.github.com/repos/MirayaProject/miraya/releases/latest";
		constexpr static const char* allReleases = "https://api.github.com/repos/MirayaProject/miraya/releases";
};


#endif //MIRAYA_UPDATERURLS_H
