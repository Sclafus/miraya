#ifndef TWITCHDATAWRAPPER_H
#define TWITCHDATAWRAPPER_H

#include <QString>
#include "streamingServiceDataWrapper.h"

// @formatter:off
class TwitchDataWrapper : public StreamingServiceDataWrapper {
	public:
		explicit TwitchDataWrapper(QString &data);
		QString getMessage() override;
		QString getUsername() override;

	private:
		void parseData();
		QString data;
		QString message;
		QString username;
};
// @formatter:on

#endif // TWITCHDATAWRAPPER_H
