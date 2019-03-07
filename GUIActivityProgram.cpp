#include "GUIActivityProgram.h"
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>
#include <string>
#include <algorithm>
#include "GUIMainWindow.h"

void CurrentWindowGUI::initGUIComponents() {

	QHBoxLayout* layout = new QHBoxLayout;
	setLayout(layout);

	QWidget* leftWidget = new QWidget;
	QVBoxLayout* leftVerticalLayout = new QVBoxLayout;
	leftWidget->setLayout(leftVerticalLayout);
	lst = new QListWidget;
	QWidget* detailWidget = new QWidget;
	lst = new QListWidget;
	leftVerticalLayout->addWidget(lst);

	QWidget* leftButtonWidget = new QWidget;
	QVBoxLayout* leftButtonLayout = new QVBoxLayout;
	btnExportToCVS = new QPushButton("Export to CVS");
	btnExportToHTML = new QPushButton("Export to HTML");
	leftButtonLayout->addWidget(btnExportToCVS);
	leftButtonLayout->addWidget(btnExportToHTML);

	leftButtonWidget->setLayout(leftButtonLayout);
	leftVerticalLayout->addWidget(leftButtonWidget);

	layout->addWidget(leftWidget);

	QWidget* rightWidget = new QWidget;
	QVBoxLayout* rightLayout = new QVBoxLayout;
	rightWidget->setLayout(rightLayout);

	QWidget* formWidget = new QWidget;
	QFormLayout* formLayout = new QFormLayout;
	formWidget->setLayout(formLayout);
	txtTitle = new QLineEdit;
	txtNumber = new QLineEdit;
	txtFileName = new QLineEdit;
	formLayout->addRow(new QLabel("Title: "), txtTitle);
	formLayout->addRow(new QLabel("Number:"), txtNumber);
	formLayout->addRow(new QLabel("File:"), txtFileName);
	rightLayout->addWidget(formWidget);

	QWidget* rightManagerial = new QWidget;
	QVBoxLayout* rightLayoutManagerial = new QVBoxLayout;
	rightManagerial->setLayout(rightLayoutManagerial);
	btnGetCurrentActivities = new QPushButton("Get current activities");
	btnAddActivity = new QPushButton("Add activity");
	btnReset = new QPushButton("Reset");
	rightLayoutManagerial->addWidget(btnGetCurrentActivities);
	rightLayoutManagerial->addWidget(btnAddActivity);
	rightLayoutManagerial->addWidget(btnReset);
	rightLayout->addWidget(rightManagerial);

	rightLayout->addWidget(rightManagerial);

	QWidget* rightDownButtonWidget = new QWidget;
	QHBoxLayout* rightDownButtonLayout = new QHBoxLayout;

	btnMainWindow = new QPushButton("Go to Main Window");
	rightDownButtonLayout->addWidget(btnMainWindow);
	rightDownButtonWidget->setLayout(rightDownButtonLayout);

	rightLayout->addWidget(rightDownButtonWidget);



	layout->addWidget(rightWidget);

}

void CurrentWindowGUI::connectSignals() {

	QObject::connect(btnGetCurrentActivities, &QPushButton::clicked, this, [&]() {
		try {
			string number = txtNumber->text().toStdString();
			srv.generateCurrent(number);
			txtNumber->setText("");
			reloadCurrent(srv.getCurrent());
		}
		catch (ServiceException&ex) {
			QMessageBox::warning(this, "WARNING", QString::fromStdString(ex.getMsg()));
		}
	});

	QObject::connect(btnAddActivity, &QPushButton::clicked, this, &CurrentWindowGUI::addActivityToCurrent);

	QObject::connect(btnMainWindow, &QPushButton::clicked, this, &CurrentWindowGUI::goToMainWindow);

	QObject::connect(btnExportToCVS, &QPushButton::clicked, this, &CurrentWindowGUI::exportToCVS);

	QObject::connect(btnExportToHTML, &QPushButton::clicked, this, &CurrentWindowGUI::exportToHTML);

	QObject::connect(btnReset, &QPushButton::clicked, this, &CurrentWindowGUI::reset);
}
void CurrentWindowGUI::reloadCurrent(vector<string>rec) {
	lst->clear();
	for (auto &s : rec) {
		QListWidgetItem*item = new QListWidgetItem(QString::fromStdString(s), lst);
		item->setData(Qt::UserRole, QString::fromStdString(s));
	}
}

void CurrentWindowGUI::addActivityToCurrent() {
	try {
		string name = txtTitle->text().toStdString();
		srv.addCurrent(name);
		reloadCurrent(srv.getCurrent());
		txtTitle->setText("");
	}
	catch (RepositoryException& ex) {
		QMessageBox::warning(this, "WARNING", QString::fromStdString(ex.getMsg()));
	}
	catch (ServiceException& ex) {
		QMessageBox::warning(this, "WARNING", QString::fromStdString(ex.getMsg()));
	}
}

void CurrentWindowGUI::goToMainWindow() {
	//MainWindowGUI *mainWindow = new MainWindowGUI(srv);
	//mainWindow->show();
	this->hide();
}

void CurrentWindowGUI::exportToCVS() {
	string fileName = txtFileName->text().toStdString();
	if (fileName.empty())
		QMessageBox::warning(this, "WARNING", QString::fromStdString("Please enter a file!"));
	else {
		QMessageBox::information(this, "Succes!", QString::fromStdString("Succesfully exported to: " + fileName));
		srv.exportRepoCVS(fileName);
		txtFileName->setText("");
	}
}
void CurrentWindowGUI::exportToHTML() {
	string fileName = txtFileName->text().toStdString();
	if (fileName.empty())
		QMessageBox::warning(this, "WARNING", QString::fromStdString("Please enter a file!"));
	else {
		QMessageBox::information(this, "Succes!", QString::fromStdString("Succesfully exported to: " + fileName));
		srv.exportRepoHTML(fileName);
		txtFileName->setText("");
	}
}
void CurrentWindowGUI::reset() {
	srv.clearCurrent();
	this->reloadCurrent(srv.getCurrent());
}