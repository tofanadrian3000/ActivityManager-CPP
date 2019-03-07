#include "GUIMainWindow.h"
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>

void MainWindowGUI::initGUIComponents() {

	QHBoxLayout* layout = new QHBoxLayout;
	setLayout(layout);

	QWidget* widgetLeft = new QWidget;
	QVBoxLayout* leftLayout = new QVBoxLayout;
	widgetLeft->setLayout(leftLayout);
	lst = new  QListView;
	leftLayout->addWidget(lst);

	QWidget* filterLeftButtons = new QWidget;
	QHBoxLayout* filterLeftButtonsLayout = new QHBoxLayout;

	leftLayout->addWidget(new QLabel("Filter by:"));
	//add filter by price button
	btnFilterByDescription = new QPushButton("Description");
	filterLeftButtonsLayout->addWidget(btnFilterByDescription);

	//add filter by active substance button
	btnFilterByType = new QPushButton("Type");
	filterLeftButtonsLayout->addWidget(btnFilterByType);

	filterLeftButtons->setLayout(filterLeftButtonsLayout);

	leftLayout->addWidget(filterLeftButtons);

	QWidget* sortLeftButtons = new QWidget;
	QHBoxLayout* sortLeftButtonsLayout = new QHBoxLayout;

	leftLayout->addWidget(new QLabel("Sort by:"));
	btnSortByTitle = new QPushButton("Name");
	btnSortByDescription = new QPushButton("Description");
	btnSortByTypeAndDuration = new QPushButton("Type and Duration");
	sortLeftButtonsLayout->addWidget(btnSortByTitle);
	sortLeftButtonsLayout->addWidget(btnSortByDescription);
	sortLeftButtonsLayout->addWidget(btnSortByTypeAndDuration);

	sortLeftButtons->setLayout(sortLeftButtonsLayout);
	leftLayout->addWidget(sortLeftButtons);


	layout->addWidget(widgetLeft);


	//setting up de right part
	QWidget* rightWidget = new QWidget;
	rightWidget->setStyleSheet("background-color: grey");
	QVBoxLayout* rightLayout = new QVBoxLayout;

	QWidget* formWidget = new QWidget;
	QFormLayout* formLayout = new QFormLayout;

	txtTitle = new QLineEdit;
	txtDescription = new QLineEdit;
	txtType = new QLineEdit;
	txtDuration = new QLineEdit;
	formLayout->addRow(new QLabel("Title:"), txtTitle);
	formLayout->addRow(new QLabel("Description:"), txtDescription);
	formLayout->addRow(new QLabel("Type:"), txtType);
	formLayout->addRow(new QLabel("Duration:"), txtDuration);
	btnAdd = new QPushButton("Add");
	btnAdd->setStyleSheet("background-color: green");
	btnRemove = new QPushButton("Remove");
	btnRemove->setStyleSheet("background-color: blue");
	btnUpdate = new QPushButton("Update");
	btnUpdate->setStyleSheet("background-color: orange");
	btnReset = new QPushButton("Reset list");
	btnReset->setStyleSheet("background-color: yellow");
	btnUndo = new QPushButton("Undo");
	btnUndo->setStyleSheet("background-color: red");
	btnCurrentActivities = new QPushButton("Go to current activities");
	btnAddCurrent = new QPushButton("Add current");
	btnRemoveCurrent = new QPushButton("Remove current");
	btnGenerateCurrent = new QPushButton("Generate current");
	btnCurrentActivitiesDraw = new QPushButton("Draw");
	formLayout->addWidget(btnAdd);
	formLayout->addWidget(btnRemove);
	formLayout->addWidget(btnUpdate);
	formLayout->addWidget(btnUndo);
	formLayout->addWidget(btnReset);
	formLayout->addWidget(btnCurrentActivities);
	formLayout->addWidget(btnAddCurrent);
	formLayout->addWidget(btnRemoveCurrent);
	formLayout->addWidget(btnGenerateCurrent);
	formLayout->addWidget(btnCurrentActivitiesDraw);
	formWidget->setLayout(formLayout);
	rightLayout->addWidget(formWidget);


	rightWidget->setLayout(rightLayout);
	layout->addWidget(rightWidget);


}

void MainWindowGUI::gotToCurrentActivities() {
	CurrentWindowGUI* CurrentWindow = new CurrentWindowGUI(srv);
	srv.addObserver(CurrentWindow);
	CurrentWindow->show();

}
void MainWindowGUI::reloadList(vector<Activity> activities) {
	/*lst->clear();
	for (auto&m : activities) {
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(m.getTitle()), lst);
		item->setData(Qt::UserRole, QString::fromStdString(m.getTitle()));
		/*if (rand() % 2) {
		item->setForeground(Qt::yellow);
		item->setBackgroundColor(Qt::red);
		}
		else {
		item->setForeground(Qt::yellow);
		item->setBackgroundColor(Qt::blue);
		}
	}*/
	myList->setactivities(srv.getActivities());
}
void MainWindowGUI::connectSignals() {

	QObject::connect(btnCurrentActivities, &QPushButton::clicked, this, &MainWindowGUI::gotToCurrentActivities);
	QObject::connect(btnSortByTitle, &QPushButton::clicked, this, [&]() {reloadList(srv.titleSort()); });
	QObject::connect(btnSortByDescription, &QPushButton::clicked, this, [&]() {
		reloadList(srv.descriptionSort()); });
	QObject::connect(btnSortByTypeAndDuration, &QPushButton::clicked, this, [&]() {
		reloadList(srv.typeDurationSort()); });
	QObject::connect(btnUndo, &QPushButton::clicked, this, &MainWindowGUI::undo);
	QObject::connect(btnAdd, &QPushButton::clicked, this, &MainWindowGUI::addActivity);
	QObject::connect(btnRemove, &QPushButton::clicked, this, &MainWindowGUI::removeActivity);
	QObject::connect(btnUpdate, &QPushButton::clicked, this, &MainWindowGUI::updateActivity);
	QObject::connect(btnAddCurrent, &QPushButton::clicked, this, &MainWindowGUI::addCurrentActivity);
	QObject::connect(btnRemoveCurrent, &QPushButton::clicked, this, &MainWindowGUI::removeCurrentActivity);
	QObject::connect(btnGenerateCurrent, &QPushButton::clicked, this, &MainWindowGUI::generateCurrentActivity);
	QObject::connect(btnCurrentActivitiesDraw, &QPushButton::clicked, this, &MainWindowGUI::gotToCurrentActivitiesDraw);
	QObject::connect(btnFilterByDescription, &QPushButton::clicked, this, &MainWindowGUI::filterByDescription);
	QObject::connect(btnFilterByType, &QPushButton::clicked, this, &MainWindowGUI::filterByType);
	QObject::connect(btnReset, &QPushButton::clicked, [&]() {
		reloadList(srv.getActivities());
	});
	
	QObject::connect(lst->selectionModel(), &QItemSelectionModel::selectionChanged, this, [&]() {
		auto sel = lst->selectionModel()->selectedIndexes();
		if (sel.isEmpty())
		{
			txtTitle->setText("");
			txtDescription->setText("");
			txtType->setText("");
			txtDuration->setText("");
			return;
		}
		else {
			auto first = sel.at(0);
			Activity act = myList->getActivity(first.row());
			assert(act.getStariAnterioare().size() == 0);
			IstoricGUI* istoric = new IstoricGUI(act.getStariAnterioare(),srv);
			srv->addObserver(istoric);
			istoric->show();
			}
		}
	);
	
}

void MainWindowGUI::gotToCurrentActivitiesDraw() {
	ActivitiesProgram* activitiesDraw= new ActivitiesProgram{ srv };
	srv.addObserver(activitiesDraw);
	activitiesDraw->show();
}

void MainWindowGUI::addActivity() {
	try {
		string title, description, type, duration;
		title = txtTitle->text().toStdString();
		description = txtDescription->text().toStdString();
		type = txtType->text().toStdString();
		duration = txtDuration->text().toStdString();
		srv.addActivity(title, description, type, duration);
		reloadList(srv.getActivities());
		txtTitle->setText("");
		txtDescription->setText("");
		txtType->setText("");
		txtDuration->setText("");
	}
	catch (ServiceException&ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
	}
	catch (RepositoryException&ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
	}
	catch (ValidateException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
	}
}

void MainWindowGUI::addCurrentActivity() {
	try {
		string title;
		title = txtTitle->text().toStdString();
		srv.addCurrent(title);
		reloadList(srv.getActivities());
		txtTitle->setText("");
		txtDescription->setText("");
		txtType->setText("");
		txtDuration->setText("");
	}
	catch (ServiceException&ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
	}
	catch (RepositoryException&ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
	}
	catch (ValidateException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
	}
}

void MainWindowGUI::removeActivity() {
	try {
		string name;
		name = txtTitle->text().toStdString();
		srv.removeActivity(name);
		reloadList(srv.getActivities());
		txtTitle->setText("");
		txtDescription->setText("");
		txtType->setText("");
		txtDuration->setText("");
	}
	catch (ServiceException&ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
	}
	catch (RepositoryException&ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
	}
	catch (ValidateException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
	}

}

void MainWindowGUI::removeCurrentActivity() {
	try {
		string name;
		name = txtTitle->text().toStdString();
		srv.removeCurrentActivity(name);
		reloadList(srv.getActivities());
		txtTitle->setText("");
		txtDescription->setText("");
		txtType->setText("");
		txtDuration->setText("");
	}
	catch (ServiceException&ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
	}
	catch (RepositoryException&ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
	}
	catch (ValidateException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
	}

}

void MainWindowGUI::generateCurrentActivity() {
	try {
		string number;
		number = txtDuration->text().toStdString();
		srv.generateCurrent(number);
		//reloadList(srv.getActivities());
		txtTitle->setText("");
		txtDescription->setText("");
		txtType->setText("");
		txtDuration->setText("");
	}
	catch (ServiceException&ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
	}
}

void MainWindowGUI::updateActivity() {
	try {
		string title, description, type, duration;
		title = txtTitle->text().toStdString();
		description = txtDescription->text().toStdString();
		type = txtType->text().toStdString();
		duration = txtDuration->text().toStdString();
		srv.updateActivity(title, description, type, duration);
		reloadList(srv.getActivities());
		txtTitle->setText("");
		txtDescription->setText("");
		txtType->setText("");
		txtDuration->setText("");
	}
	catch (ServiceException&ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
	}
	catch (RepositoryException&ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
	}
	catch (ValidateException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
	}
}
void MainWindowGUI::undo() {
	srv.undo();
	reloadList(srv.getActivities());
}
void MainWindowGUI::filterByDescription() {
	string description;
	description = txtDescription->text().toStdString();
	reloadList(srv.descriptionFilter(description));
}
void MainWindowGUI::filterByType() {
	string type;
	type = txtType->text().toStdString();
	reloadList(srv.typeFilter(type));
}
