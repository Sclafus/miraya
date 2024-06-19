#ifndef TWITCHCOMMANDHANDLER_H
#define TWITCHCOMMANDHANDLER_H

#include <QSettings>
#include <QString>

#include "twitchdatawrapper.h"
#include "osu/data/gosu/gosumemorydatawrapper.h"

// @formatter:off
class TwitchCommandHandler {
	public:
		TwitchCommandHandler();
		[[maybe_unused]] TwitchCommandHandler(TwitchDataWrapper *newTwitchData, GosuMemoryDataWrapper *gosumemoryData);
		void setGosumemoryData(GosuMemoryDataWrapper *newGosumemoryData);
		void setTwitchData(TwitchDataWrapper *newTwitchData);
		GosuMemoryDataWrapper* getGosumemoryData();
		[[maybe_unused]] TwitchDataWrapper* getTwitchData();
		QString getResponse();

	private:
		QString getResponseStaticCommands();
		QString getResponseAllCommands();
		QString getResponseNowPlaying();
		QString getResponseSkin();
		TwitchDataWrapper *twitchData;
		GosuMemoryDataWrapper *gosumemoryData;
};
// @formatter:on

#endif // TWITCHCOMMANDHANDLER_H
