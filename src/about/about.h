#ifndef ABOUT_H
#define ABOUT_H

#include <QApplication>
#include <QDate>
#include <QDebug>
#include <QMessageBox>
#include <QObject>

class About : public QObject {
	Q_OBJECT

	public:
		static QMessageBox* createMessageBox(QWidget *parent = nullptr);
		static void show();
};

#endif // ABOUT_H
