#include "about.h"

void About::show() {
	qDebug() << "[About] Displaying about...";
	createMessageBox()->show();
	qDebug() << "[About] Closed";
}

QMessageBox *About::createMessageBox(QWidget *parent) {
	auto *msgBox = new QMessageBox(parent);
	msgBox->setWindowTitle("About Miraya");
	auto body = (
			QString("<h1>Miraya</h1>"
			        "<p>A Twitch chatbot with GosuMemory and osu! IRC support.</p>"
			        "<p>Version: %1</p>"
			        "<p>Copyright © %2 Miraya Project</p>"
			        "<p>This program is free software: you can redistribute it and/or modify "
			        "it under the terms of the GNU General Public License as published by "
			        "the Free Software Foundation, either version 3 of the License, or "
			        "(at your option) any later version.</p>"
			        "<p>This program is distributed in the hope that it will be useful, "
			        "but WITHOUT ANY WARRANTY; without even the implied warranty of "
			        "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the "
			        "GNU General Public License for more details.</p>"
			        "<p>You should have received a copy of the GNU General Public License "
			        "along with this program.  If not, see <a href=\"https://www.gnu.org/licenses/\">"
			        "https://www.gnu.org/licenses/</a>.</p>"
			        "<p>Icons provided by <a href=\"https://icons8.com\">Icons8</a></p>").arg(
					QApplication::applicationVersion(), QString::number(QDate::currentDate().year()))
	);
	msgBox->setText(body);
	msgBox->setIcon(QMessageBox::Information);
	msgBox->setStandardButtons(QMessageBox::Ok);
	msgBox->setWindowFlags(msgBox->windowFlags() & ~Qt::WindowContextHelpButtonHint);

	return msgBox;
}
