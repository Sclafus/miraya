#ifndef STREAMINGSERVICEDATAWRAPPER_H
#define STREAMINGSERVICEDATAWRAPPER_H

#include <QString>

// @formatter:off
class StreamingServiceDataWrapper {
	public:
		virtual QString getMessage() = 0;
		virtual QString getUsername() = 0;
};
// @formatter:on

#endif // STREAMINGSERVICEDATAWRAPPER_H
