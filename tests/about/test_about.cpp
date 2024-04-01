#include <QTest>
#include "../../src/about/about.h"

class AboutTest : public QObject {
	Q_OBJECT

	private slots:

	[[maybe_unused]] static void testShow();
};

[[maybe_unused]] void AboutTest::testShow() {
	auto *messageBox = About::createMessageBox();
	auto text = messageBox->text();
	QVERIFY(messageBox->parent() == nullptr);
	QVERIFY(text.contains(QApplication::applicationVersion()));
	QVERIFY(text.contains(QString::number(QDate::currentDate().year())));
	QVERIFY(text.contains("https://icons8.com"));
	QVERIFY(text.contains("Miraya"));
	QVERIFY(messageBox->windowTitle() == "About Miraya");
}

QTEST_MAIN(AboutTest)

#include "test_about.moc"