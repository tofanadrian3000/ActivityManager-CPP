#pragma once
#include <qwidget.h>
#include <qlistwidget.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qboxlayout.h>
#include <vector>
#include <qlabel.h>
#include "Service.h"
#include "GUIActivityProgram.h"
#include "GUIActivitiesProgram.h"
#include "listModel.h"
#include "IstoricGUI.h"
class MainWindowGUI : public QWidget, public Observer {
private:
	Service srv;
	QListView* lst;
	QPushButton * btnAdd;
	QPushButton * btnRemove;
	QPushButton * btnUpdate;
	QPushButton * btnSortByTitle;
	QPushButton * btnSortByDescription;
	QPushButton * btnSortByTypeAndDuration;
	QPushButton * btnFilterByDescription;
	QPushButton * btnFilterByType;
	QPushButton * btnReset;
	QPushButton * btnCurrentActivities;
	QPushButton * btnUndo;
	QPushButton * btnAddCurrent;
	QPushButton * btnRemoveCurrent;
	QPushButton * btnGenerateCurrent;
	QPushButton * btnCurrentActivitiesDraw;
	QLineEdit * txtTitle;
	QLineEdit * txtDescription;
	QLineEdit * txtType;
	QLineEdit * txtDuration;
	MyListModel* myList;
	void initGUIComponents();
	void reloadList(vector<Activity> activities);
	void connectSignals();
	void gotToCurrentActivities();
	void gotToCurrentActivitiesDraw();
	void addActivity();
	void removeActivity();
	void updateActivity();
	void filterByDescription();
	void filterByType();
	void undo();
	void addCurrentActivity();
	void removeCurrentActivity();
	void generateCurrentActivity();
public:
	MainWindowGUI(Service srv) :srv{ srv } {
		initGUIComponents();
		myList = new MyListModel(srv.getActivities(), srv);
		lst->setModel(myList);
		connectSignals();
		reloadList(srv.getActivities());
	};
	void update()override {
		reloadList(srv.getActivities());
	}
};