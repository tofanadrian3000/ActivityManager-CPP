#pragma once
#include <QAbstractListModel>
#include <vector>
#include "Activity.h"
#include "Service.h"
class MyListModel :public QAbstractListModel
{
private:
	vector<Activity> activities;
	Service serv;
public:

	MyListModel(vector<Activity> activities, Service serv) : activities{ activities }, serv{ serv } {};

	int rowCount(const QModelIndex &parent = QModelIndex()) const override {
		return  activities.size();
	};

	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole) {
			auto activity = activities[index.row()];
			auto title = activity.getTitle();
			auto description = activity.getDescription();
			return QString::fromStdString(title+" "+description);

		}
		return QVariant();
	};

	void setactivities(const vector<Activity> activity) {
		activities = activity;
		QModelIndex topLeft = createIndex(0, 0);
		QModelIndex bottomRight = createIndex(rowCount(), 1);
		emit dataChanged(topLeft, bottomRight);

	}


	Activity getActivity(int linie) {
		return serv.getActivities()[linie];
	}

	

	~MyListModel() = default;
};

