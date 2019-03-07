#pragma once
#include <qwidget.h>
#include <qpushbutton.h>
#include <qlistwidget.h>
#include <qlineedit.h>
#include "Service.h"

class CurrentWindowGUI :public QWidget, public Observer
{
private:
	Service srv;
	QListWidget * lst;
	QPushButton * btnGetCurrentActivities;
	QPushButton * btnExportToCVS;
	QPushButton * btnExportToHTML;
	QPushButton * btnAddActivity;
	QPushButton * btnMainWindow;
	QPushButton * btnReset;
	QLineEdit * txtTitle;
	QLineEdit *txtNumber;
	QLineEdit *txtFileName;

	void initGUIComponents();
	void connectSignals();
	void reloadCurrent(vector<string> rec);
	void addActivityToCurrent();
	void goToMainWindow();
	void exportToCVS();
	void exportToHTML();
	void reset();
public:
	CurrentWindowGUI(Service srv) :srv{ srv } {
		initGUIComponents();
		reloadCurrent(srv.getCurrent());
		connectSignals();
	};

	void update() override {
		reloadCurrent(srv.getCurrent());
	}
};

