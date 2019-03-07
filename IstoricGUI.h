#pragma once
#include <qwidget.h>
#include <qlistview.h>
#include "listModel.h"
#include "Activity.h"
#include <vector>
#include "Service.h"

class IstoricGUI: public QWidget
{
private:
	Service serv;
	QListView* lst;
	vector<Activity> activities;
	MyListModel* model = new MyListModel(activities, serv);
	void loadAll();

public:
	IstoricGUI(vector<Activity> acts, Service serv) {
		this->serv = serv;
		this->activities = acts;
		loadAll();
		lst->setModel(model);
		model->setactivities(activities);
	}
	~IstoricGUI()=default;
};
