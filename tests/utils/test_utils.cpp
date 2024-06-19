#include <QTest>
#include <QPair>
#include <QRandomGenerator>
#include "../../src/utils/utils.h"

struct TestData {
	QString tag;
	QString value;
	int beatmapId = -1;
};

class UtilsTest : public QObject {
	Q_OBJECT

	private:
		static QList<TestData> getTestData();

	private slots:
		[[maybe_unused]] static void testGetUrls_data();
		[[maybe_unused]] static void testGetUrls();
		[[maybe_unused]] static void testGetOsuBeatmapUrls_data();
		[[maybe_unused]] static void testGetOsuBeatmapUrls();
		[[maybe_unused]] static void testGetBeatmapIdFromOsuBeatmapLink_data();
		[[maybe_unused]] static void testGetBeatmapIdFromOsuBeatmapLink();
};


QList<TestData> UtilsTest::getTestData() {
	auto oldStd = QString("https://old.ppy.sh/s/292301");
	auto oldStd2 = QString("https://old.ppy.sh/p/beatmap?b=658127&m=0");
	auto std = QString("https://osu.ppy.sh/b/658127");
	auto std2 = QString("https://osu.ppy.sh/beatmapsets/292301#osu/658127");
	auto std3 = QString("https://osu.ppy.sh/beatmapsets/292301");

	auto oldTaiko = QString("https://old.ppy.sh/s/1746436");
	auto oldTaiko2 = QString("https://old.ppy.sh/p/beatmap?b=3572290&m=1");
	auto taiko = QString("https://osu.ppy.sh/b/3572290");
	auto taiko2 = QString("https://osu.ppy.sh/beatmapsets/1746436#taiko/3572290");
	auto taiko3 = QString("https://osu.ppy.sh/beatmapsets/1746436");

	auto oldMania = QString("https://old.ppy.sh/s/272871");
	auto oldMania2 = QString("https://old.ppy.sh/b/646681&m=3");
	auto mania = QString("https://osu.ppy.sh/b/646681");
	auto mania2 = QString("https://osu.ppy.sh/beatmapsets/272871#mania/646681");
	auto mania3 = QString("https://osu.ppy.sh/beatmapsets/272871");

	auto oldCtb = QString("https://old.ppy.sh/s/432720");
	auto oldCtb2 = QString("https://old.ppy.sh/p/beatmap?b=933017&m=2");
	auto ctb = QString("https://osu.ppy.sh/b/933017");
	auto ctb2 = QString("https://osu.ppy.sh/beatmapsets/432720#fruits/933017");
	auto ctb3 = QString("https://osu.ppy.sh/beatmapsets/432720");
	return {
			{"old.ppy.sh | std",     oldStd},
			{"old.ppy.sh | std 2",   oldStd2, 658127},
			{"osu.ppy.sh | std",     std, 658127},
			{"osu.ppy.sh | std 2",   std2, 658127},
			{"osu.ppy.sh | std 3",   std3},
			{"old.ppy.sh | taiko",   oldTaiko},
			{"old.ppy.sh | taiko 2", oldTaiko2, 3572290},
			{"osu.ppy.sh | taiko",   taiko, 3572290},
			{"osu.ppy.sh | taiko 2", taiko2, 3572290},
			{"osu.ppy.sh | taiko 3", taiko3},
			{"old.ppy.sh | mania",   oldMania},
			{"old.ppy.sh | mania 2", oldMania2, 646681},
			{"osu.ppy.sh | mania",   mania, 646681},
			{"osu.ppy.sh | mania 2", mania2, 646681},
			{"osu.ppy.sh | mania 3", mania3},
			{"old.ppy.sh | ctb",     oldCtb},
			{"old.ppy.sh | ctb 2",   oldCtb2, 933017},
			{"osu.ppy.sh | ctb",     ctb, 933017},
			{"osu.ppy.sh | ctb 2",   ctb2, 933017},
			{"osu.ppy.sh | ctb 3",   ctb3}
	};
}

[[maybe_unused]] void UtilsTest::testGetUrls_data() {
	QTest::addColumn<QString>("message");
	QTest::addColumn<QStringList>("expected");

	QTest::newRow("testGetUrls1") << QString("Hello, World!") << QStringList{};
	QTest::newRow("testGetUrls2") << QString("https://www.google.com") << QStringList{"https://www.google.com"};
	QTest::newRow("testGetUrls3") << QString("https://google.com") << QStringList{"https://google.com"};
	QTest::newRow("testGetUrls4") << QString("https://old.ppy.sh") << QStringList{"https://old.ppy.sh"};
	QTest::newRow("testGetUrls5") << QString("Hello, World! https://www.google.com Hello, World!")
	                              << QStringList{"https://www.google.com"};
	QTest::newRow("testGetUrls6") << QString("Hello, World! https://google.com Hello, World!")
	                              << QStringList{"https://google.com"};
	QTest::newRow("testGetUrls7") << QString("Hello, World! https://old.ppy.sh Hello, World!")
	                              << QStringList{"https://old.ppy.sh"};
	QTest::newRow("testGetUrls8") << QString("https://www.osu.ppy.sh and https://www.google.com")
	                              << QStringList{"https://www.osu.ppy.sh", "https://www.google.com"};
	QTest::newRow("testGetUrls9") << QString("https://osu.ppy.sh and https://google.com")
	                              << QStringList{"https://osu.ppy.sh", "https://google.com"};
	QTest::newRow("testGetUrls10") << QString("https://www.osu.ppy.sh and https://google.com")
	                               << QStringList{"https://www.osu.ppy.sh", "https://google.com"};
	QTest::newRow("testGetUrls11") << QString("https://osu.ppy.sh and https://www.google.com")
	                               << QStringList{"https://osu.ppy.sh", "https://www.google.com"};
}

[[maybe_unused]] void UtilsTest::testGetUrls() {
	QFETCH(QString, message);
	QFETCH(QStringList, expected);
	auto actual = Utils::getUrls(message);
	QCOMPARE(actual, expected);
}

[[maybe_unused]] void UtilsTest::testGetOsuBeatmapUrls_data() {
	QTest::addColumn<QString>("message");
	QTest::addColumn<QStringList>("expected");

	auto testData = getTestData();
	for (const auto &test: testData) {
		QTest::newRow(test.tag.toStdString().c_str()) << test.value << QStringList{test.value};
	}

	auto random1 = testData[QRandomGenerator::global()->bounded(testData.size())].value;
	auto random2 = testData[QRandomGenerator::global()->bounded(testData.size())].value;
	QTest::newRow("combined | random") << QString("hello, world! %1 hello, world!").arg(random1) << QStringList{random1};
	QTest::newRow("combined | 2 randoms") << "hello, world! " + random1 + " hello, world!" + random2
	                                      << QStringList{random1, random2};
	QTest::newRow("combined | 2 randoms reversed") << "hello, world! " + random2 + " hello, world!" + random1
	                                               << QStringList{random2, random1};
}

[[maybe_unused]] void UtilsTest::testGetOsuBeatmapUrls() {
	QFETCH(QString, message);
	QFETCH(QStringList, expected);
	auto actual = Utils::getOsuBeatmapUrls(message);
	QCOMPARE(actual, expected);
}

[[maybe_unused]] void UtilsTest::testGetBeatmapIdFromOsuBeatmapLink_data() {
	QTest::addColumn<QString>("message");
	QTest::addColumn<int>("expected");

	auto testData = getTestData();
	for (const auto &test: testData) {
		QTest::newRow(test.tag.toStdString().c_str()) << test.value << test.beatmapId;
	}
}

[[maybe_unused]] void UtilsTest::testGetBeatmapIdFromOsuBeatmapLink() {
	QFETCH(QString, message);
	QFETCH(int, expected);
	auto actual = Utils::getBeatmapIdFromOsuBeatmapLink(message);
	QCOMPARE(actual, expected);
}

QTEST_MAIN(UtilsTest)
#include "test_utils.moc"
