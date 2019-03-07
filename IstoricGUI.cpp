#include "IstoricGUI.h"
#include <qformlayout.h>
#include <qlistview.h>

void IstoricGUI::loadAll() {
	QVBoxLayout* layout = new QVBoxLayout;
	lst = new QListView;
	layout->addWidget(lst);
	setLayout(layout);

}