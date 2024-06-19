#ifndef COMMANDSWINDOW_H
#define COMMANDSWINDOW_H

#include <QDialog>
#include <QMessageBox>
#include <QSettings>

namespace Ui {
	 class CommandsWindow;
}

// @formatter:off
class CommandsWindow : public QDialog {
	Q_OBJECT

	public:
		explicit CommandsWindow(QWidget *parent = nullptr);
		~CommandsWindow() override;

	private:
		void on_addCommandBtn_clicked();
		void on_removeCommandBtn_clicked();
		void on_saveBtn_clicked();
		void loadData();
		void addRow(const QString& command, const QString& response);
		Ui::CommandsWindow *ui;
};
// @formatter:on

#endif // COMMANDSWINDOW_H
