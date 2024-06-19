#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDesktopServices>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLabel>
#include <QListWidgetItem>
#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QSettings>
#include <QStyleFactory>
#include <QUrl>

#include "about.h"
#include "commandswindow.h"
#include "osu/data/gosu/gosumemoryclient.h"
#include "osu/data/gosu/gosumemorydatawrapper.h"
#include "osu/irc/osuircclient.h"
#include "preferences.h"
#include "setupwizard.h"
#include "skinsurl.h"
#include "theme.h"
#include "twitchClient.h"
#include "twitchcommandhandler.h"
#include "twitchdatawrapper.h"
#include "updater.h"
#include "utils.h"
#include "osu/api/osuapi.h"


namespace Ui {
	 class MainWindow;
}

// @formatter:off
class MainWindow : public QMainWindow {
	Q_OBJECT

	public:
		explicit MainWindow(QWidget *parent = nullptr);
		~MainWindow() override;

	private slots:
		[[maybe_unused]] void on_btnStart_clicked();
		void on_actionStart_Setup_triggered();
		[[maybe_unused]] static void on_actionGithub_triggered();
		[[maybe_unused]] static void on_actionDiscord_triggered();
		[[maybe_unused]] static void on_actionAbout_triggered();
		[[maybe_unused]] void on_actionPreferences_triggered();
		[[maybe_unused]] void on_actionSkins_triggered();
		[[maybe_unused]] void on_actionCommands_triggered();
		static void onThemeChanged();
		void onTwitchClientConnected();
		void onGosumemoryClientConnected();
		void onOsuIrcClientConnected();
		void onTwitchClientDisconnected();
		void onGosumemoryClientDisconnected();
		void onOsuIrcClientDisconnected();
		void onGosumemoryClientMessageReceived(GosuMemoryDataWrapper message);
		void onTwitchClientMessageReceived(TwitchDataWrapper message);
		void onTwitchClientCommandReceived(TwitchDataWrapper command);
		void onNewVersionReceived();


	private:
		void setupSignals();
		void setupStatusbar();
		void setupUi();
		static QLabel *getTwitchChatMessage(const QString& username, const QString& message);
		static QString getRichTextMessage(const QString& message);
		Ui::MainWindow *ui;
		TwitchClient *twitchClient;
		TwitchCommandHandler *twitchCommandHandler;
		GosumemoryClient *gosumemoryClient;
		OsuIrcClient *osuIrcClient;
		Updater *updater;
		OsuApi *osuApi;
		QLabel *ircConnectionLabel{};
		QLabel *twitchConnectionLabel{};
		QLabel *gosumemoryConnectionLabel{};
};
// @formatter:on

#endif // MAINWINDOW_H
