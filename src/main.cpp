#include <QApplication>
#include <QIcon>
#include "mainwindow.h"

int main(int argc, char **argv) {
	QApplication app(argc, argv);
	QApplication::setOrganizationName("miraya");
	QApplication::setOrganizationDomain("github.com/MirayaProject");
	QApplication::setApplicationName("bot");
	QApplication::setApplicationVersion("1.3.0-alpha.1");
#ifdef Q_OS_LINUX
	QApplication::setWindowIcon(QIcon(":/resources/logo/logo.png"));
#endif
	MainWindow mw;
	mw.show();
	return QApplication::exec();
}
