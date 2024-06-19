#ifndef MIRAYA_UPDATERURLS_H
#define MIRAYA_UPDATERURLS_H

#include <QObject>

// @formatter:off
class UpdaterUrls{
	public:
		constexpr static const char* latestStable = "https://api.github.com/repos/MirayaProject/miraya/releases/latest";
		[[maybe_unused]] constexpr static const char* allReleases = "https://api.github.com/repos/MirayaProject/miraya/releases";
};
// @formatter:on


#endif //MIRAYA_UPDATERURLS_H
