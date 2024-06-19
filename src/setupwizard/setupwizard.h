#ifndef SETUPWIZARD_H
#define SETUPWIZARD_H

#include <QWizard>
#include <QJsonObject>
#include <QIntValidator>
#include <QSettings>

namespace Ui {
	 class SetupWizard;
}

// @formatter:off
class SetupWizard : public QWizard {
	Q_OBJECT

	public:
		explicit SetupWizard(QWidget *parent = nullptr);
		~SetupWizard() override;

	signals:
		void wizardFinished(QJsonObject json);

	private slots:
		 [[maybe_unused]] void on_SetupWizard_finished(int result);

	private:
		void setupUi();

		QJsonObject gatherData();
		QJsonObject getGosumemoryData();
		QJsonObject getOsuApiData();
		QJsonObject getTwitchData();
		QJsonObject getOsuircData();
		static void saveData(QJsonObject data);
		Ui::SetupWizard *ui;
};
// @formatter:on

#endif // SETUPWIZARD_H
