#include <QTest>
#include "../../../src/updater/version.h"

class VersionTest : public QObject {
	Q_OBJECT
private slots:
	[[maybe_unused]] static void testFromString();
	[[maybe_unused]] static void testFromString_data();
	[[maybe_unused]] static void testIsPrerelease();
	[[maybe_unused]] static void testIsPrerelease_data();
	[[maybe_unused]] static void testOperatorEq_data();
	[[maybe_unused]] static void testOperatorEq();
	[[maybe_unused]] static void testOperatorGt_data();
	[[maybe_unused]] static void testOperatorGt();
	[[maybe_unused]] static void testOperatorGte_data();
	[[maybe_unused]] static void testOperatorGte();
};

[[maybe_unused]] void VersionTest::testFromString_data() {
	QTest::addColumn<QString>("versionString");
	QTest::addColumn<QString>("expectedVersion");

	QTest::newRow("1.0.0") << QString("1.0.0") << QString("1.0.0");
	QTest::newRow("1.0.0-alpha.1") << QString("1.0.0-alpha.1") << QString("1.0.0-alpha.1");
	QTest::newRow("1.0.0-beta.1") << QString("1.0.0-beta.1") << QString("1.0.0-beta.1");
	QTest::newRow("1.0.0-rc.1") << QString("1.0.0-rc.1") << QString("1.0.0-rc.1");
	QTest::newRow("1.0.0-rc.1-1") << QString("1.0.0-rc.1-1") << QString("1.0.0-rc.1-1");
}

[[maybe_unused]] void VersionTest::testFromString() {
	QFETCH(QString, versionString);
	QFETCH(QString, expectedVersion);

	auto ver = Version::fromString(versionString);
	QCOMPARE(ver.toString(), expectedVersion);
}

[[maybe_unused]] void VersionTest::testIsPrerelease_data(){
	QTest::addColumn<QString>("versionString");
	QTest::addColumn<bool>("expectedIsPrerelease");

	QTest::newRow("1.0.0") << QString("1.0.0") << false;
	QTest::newRow("1.0.0-alpha.1") << QString("1.0.0-alpha.1") << true;
	QTest::newRow("1.0.0-beta.1") << QString("1.0.0-beta.1") << true;
	QTest::newRow("1.0.0-rc.1") << QString("1.0.0-rc.1") << true;
	QTest::newRow("1.0.0-rc.1-1") << QString("1.0.0-rc.1-1") << true;
}

[[maybe_unused]] void VersionTest::testIsPrerelease(){
	QFETCH(QString, versionString);
	QFETCH(bool, expectedIsPrerelease);
	auto ver = Version::fromString(versionString);
	QCOMPARE(ver.isPrerelease(), expectedIsPrerelease);
}

[[maybe_unused]] void VersionTest::testOperatorEq_data() {
	QTest::addColumn<QString>("versionString1");
	QTest::addColumn<QString>("versionString2");
	QTest::addColumn<bool>("expectedIsEqual");

	QTest::newRow("true1") << QString("1.0.0") << QString("1.0.0") << true;
	QTest::newRow("true2") << QString("1.0.0-alpha.1") << QString("1.0.0-alpha.1") << true;
	QTest::newRow("true3") << QString("1.0.0-beta.1") << QString("1.0.0-beta.1") << true;
	QTest::newRow("true4") << QString("1.0.0-rc.1") << QString("1.0.0-rc.1") << true;
	QTest::newRow("true5") << QString("1.0.0-rc.1-1") << QString("1.0.0-rc.1-1") << true;

	QTest::newRow("false1") << QString("1.0.0") << QString("1.0.0-alpha.1") << false;
	QTest::newRow("false2") << QString("1.0.0") << QString("1.0.0-beta.1") << false;
	QTest::newRow("false3") << QString("1.0.0") << QString("1.0.0-rc.1") << false;
	QTest::newRow("false4") << QString("1.0.0") << QString("1.0.0-rc.1-1") << false;

	QTest::newRow("false5") << QString("1.0.0-alpha.1") << QString("1.0.0") << false;
	QTest::newRow("false6") << QString("1.0.0-alpha.1") << QString("1.0.0-beta.1") << false;
	QTest::newRow("false7") << QString("1.0.0-alpha.1") << QString("1.0.0-rc.1") << false;
	QTest::newRow("false8") << QString("1.0.0-alpha.1") << QString("1.0.0-rc.1-1") << false;

	QTest::newRow("false11") << QString("1.0.0-beta.1") << QString("1.0.0") << false;
	QTest::newRow("false12") << QString("1.0.0-beta.1") << QString("1.0.0-alpha.1") << false;
	QTest::newRow("false13") << QString("1.0.0-beta.1") << QString("1.0.0-rc.1") << false;
	QTest::newRow("false14") << QString("1.0.0-beta.1") << QString("1.0.0-rc.1-1") << false;


	QTest::newRow("false15") << QString("1.0.0-rc.1") << QString("1.0.0") << false;
	QTest::newRow("false16") << QString("1.0.0-rc.1") << QString("1.0.0-alpha.1") << false;
	QTest::newRow("false17") << QString("1.0.0-rc.1") << QString("1.0.0-beta.1") << false;
	QTest::newRow("false18") << QString("1.0.0-rc.1") << QString("1.0.0-rc.1-1") << false;

	QTest::newRow("false19") << QString("1.0.0-rc.1-1") << QString("1.0.0") << false;
	QTest::newRow("false20") << QString("1.0.0-rc.1-1") << QString("1.0.0-alpha.1") << false;
	QTest::newRow("false21") << QString("1.0.0-rc.1-1") << QString("1.0.0-beta.1") << false;
	QTest::newRow("false22") << QString("1.0.0-rc.1-1") << QString("1.0.0-rc.1") << false;
}

[[maybe_unused]] void VersionTest::testOperatorEq() {
	QFETCH(QString, versionString1);
	QFETCH(QString, versionString2);
	QFETCH(bool, expectedIsEqual);

	auto ver1 = Version::fromString(versionString1);
	auto ver2 = Version::fromString(versionString2);
	QCOMPARE(ver1 == ver2, expectedIsEqual);
}

[[maybe_unused]] void VersionTest::testOperatorGt_data() {
	QTest::addColumn<QString>("versionString1");
	QTest::addColumn<QString>("versionString2");
	QTest::addColumn<bool>("expectedIsGt");

	QTest::newRow("true1") << QString("2.0.0") << QString("1.0.0") << true;
	QTest::newRow("true2") << QString("1.1.0") << QString("1.0.0") << true;
	QTest::newRow("true3") << QString("1.0.1") << QString("1.0.0") << true;

	QTest::newRow("true4") << QString("1.0.0-beta.1") << QString("1.0.0-alpha.1") << true;
	QTest::newRow("true5") << QString("1.0.0-rc.1") << QString("1.0.0-alpha.1") << true;
	QTest::newRow("true6") << QString("1.0.0-rc.1") << QString("1.0.0-beta.1") << true;
	QTest::newRow("true7") << QString("1.0.0-rc.1-1") << QString("1.0.0-alpha.1") << true;
	QTest::newRow("true8") << QString("1.0.0-rc.1-1") << QString("1.0.0-beta.1") << true;
	QTest::newRow("true9") << QString("1.0.0-rc.1-1") << QString("1.0.0-rc.1") << true;
	QTest::newRow("true10") << QString("1.0.0") << QString("1.0.0-alpha.1") << true;
	QTest::newRow("true11") << QString("1.0.0") << QString("1.0.0-beta.1") << true;
	QTest::newRow("true12") << QString("1.0.0") << QString("1.0.0-rc.1") << true;
	QTest::newRow("true13") << QString("1.0.0") << QString("1.0.0-rc.1-1") << true;

	QTest::newRow("false1") << QString("1.0.0") << QString("1.0.0") << false;
	QTest::newRow("false2") << QString("1.0.0-alpha.1") << QString("1.0.0-alpha.1") << false;
	QTest::newRow("false3") << QString("1.0.0-beta.1") << QString("1.0.0-beta.1") << false;
	QTest::newRow("false4") << QString("1.0.0-rc.1") << QString("1.0.0-rc.1") << false;
	QTest::newRow("false5") << QString("1.0.0-rc.1-1") << QString("1.0.0-rc.1-1") << false;

	QTest::newRow("false6") << QString("1.0.0") << QString("1.1.0-alpha.1") << false;
	QTest::newRow("false7") << QString("1.0.0") << QString("1.1.0-beta.1") << false;
	QTest::newRow("false8") << QString("1.0.0") << QString("1.1.0-rc.1") << false;
	QTest::newRow("false9") << QString("1.0.0") << QString("1.1.0-rc.1-1") << false;

	QTest::newRow("false10") << QString("1.0.0-alpha.1") << QString("1.0.0-alpha.2") << false;
	QTest::newRow("false11") << QString("1.0.0-alpha.1") << QString("1.0.0-beta.1") << false;
	QTest::newRow("false12") << QString("1.0.0-alpha.1") << QString("1.0.0-rc.1") << false;
	QTest::newRow("false13") << QString("1.0.0-alpha.1") << QString("1.0.0-rc.1-1") << false;

	QTest::newRow("false14") << QString("1.0.0-beta.1") << QString("1.0.0-beta.2") << false;
	QTest::newRow("false15") << QString("1.0.0-beta.1") << QString("1.0.0-rc.1") << false;
	QTest::newRow("false16") << QString("1.0.0-beta.1") << QString("1.0.0-rc.1-1") << false;

	QTest::newRow("false17") << QString("1.0.0-rc.1") << QString("1.0.0-rc.2") << false;
	QTest::newRow("false18") << QString("1.0.0-rc.1") << QString("1.0.0-rc.1-1") << false;

	QTest::newRow("false19") << QString("1.0.0-rc.1-1") << QString("1.0.0-rc.1-2") << false;
	QTest::newRow("false20") << QString("1.0.0-rc.1-1") << QString("1.0.0-rc.1-1") << false;
}

[[maybe_unused]] void VersionTest::testOperatorGt() {
	QFETCH(QString, versionString1);
	QFETCH(QString, versionString2);
	QFETCH(bool, expectedIsGt);

	auto ver1 = Version::fromString(versionString1);
	auto ver2 = Version::fromString(versionString2);
	QCOMPARE(ver1 > ver2, expectedIsGt);
}

[[maybe_unused]] void VersionTest::testOperatorGte_data() {
	QTest::addColumn<QString>("versionString1");
	QTest::addColumn<QString>("versionString2");
	QTest::addColumn<bool>("expectedIsGte");

	QTest::newRow("true1") << QString("2.0.0") << QString("1.0.0") << true;
	QTest::newRow("true2") << QString("1.1.0") << QString("1.0.0") << true;
	QTest::newRow("true3") << QString("1.0.1") << QString("1.0.0") << true;

	QTest::newRow("true4") << QString("1.0.0-beta.1") << QString("1.0.0-alpha.1") << true;
	QTest::newRow("true5") << QString("1.0.0-rc.1") << QString("1.0.0-alpha.1") << true;
	QTest::newRow("true6") << QString("1.0.0-rc.1") << QString("1.0.0-beta.1") << true;
	QTest::newRow("true7") << QString("1.0.0-rc.1-1") << QString("1.0.0-alpha.1") << true;
	QTest::newRow("true8") << QString("1.0.0-rc.1-1") << QString("1.0.0-beta.1") << true;
	QTest::newRow("true9") << QString("1.0.0-rc.1-1") << QString("1.0.0-rc.1") << true;

	QTest::newRow("true10") << QString("1.0.0") << QString("1.0.0") << true;
	QTest::newRow("true11") << QString("1.0.0-alpha.1") << QString("1.0.0-alpha.1") << true;
	QTest::newRow("true12") << QString("1.0.0-beta.1") << QString("1.0.0-beta.1") << true;
	QTest::newRow("true13") << QString("1.0.0-rc.1") << QString("1.0.0-rc.1") << true;
	QTest::newRow("true14") << QString("1.0.0-rc.1-1") << QString("1.0.0-rc.1-1") << true;
	QTest::newRow("true15") << QString("1.0.0") << QString("1.0.0-alpha.1") << true;
	QTest::newRow("true16") << QString("1.0.0") << QString("1.0.0-beta.1") << true;
	QTest::newRow("true17") << QString("1.0.0") << QString("1.0.0-rc.1") << true;
	QTest::newRow("true18") << QString("1.0.0") << QString("1.0.0-rc.1-1") << true;
	QTest::newRow("true19") << QString("1.0.0-rc.1-1") << QString("1.0.0-rc.1-1") << true;

	QTest::newRow("false6") << QString("1.0.0") << QString("1.1.0-alpha.1") << false;
	QTest::newRow("false7") << QString("1.0.0") << QString("1.1.0-beta.1") << false;
	QTest::newRow("false8") << QString("1.0.0") << QString("1.1.0-rc.1") << false;
	QTest::newRow("false9") << QString("1.0.0") << QString("1.1.0-rc.1-1") << false;

	QTest::newRow("false14") << QString("1.0.0-alpha.1") << QString("1.0.0-alpha.2") << false;
	QTest::newRow("false15") << QString("1.0.0-alpha.1") << QString("1.0.0-beta.1") << false;
	QTest::newRow("false16") << QString("1.0.0-alpha.1") << QString("1.0.0-rc.1") << false;
	QTest::newRow("false17") << QString("1.0.0-alpha.1") << QString("1.0.0-rc.1-1") << false;

	QTest::newRow("false18") << QString("1.0.0-beta.1") << QString("1.0.0-beta.2") << false;
	QTest::newRow("false19") << QString("1.0.0-beta.1") << QString("1.0.0-rc.1") << false;
	QTest::newRow("false20") << QString("1.0.0-beta.1") << QString("1.0.0-rc.1-1") << false;

	QTest::newRow("false21") << QString("1.0.0-rc.1") << QString("1.0.0-rc.2") << false;
	QTest::newRow("false22") << QString("1.0.0-rc.1") << QString("1.0.0-rc.1-1") << false;

	QTest::newRow("false23") << QString("1.0.0-rc.1-1") << QString("1.0.0-rc.1-2") << false;
}

[[maybe_unused]] void VersionTest::testOperatorGte() {
	QFETCH(QString, versionString1);
	QFETCH(QString, versionString2);
	QFETCH(bool, expectedIsGte);

	auto ver1 = Version::fromString(versionString1);
	auto ver2 = Version::fromString(versionString2);
	QCOMPARE(ver1 >= ver2, expectedIsGte);
}

QTEST_MAIN(VersionTest)
#include "test_updater_version.moc"