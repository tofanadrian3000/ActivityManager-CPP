#pragma once
#include <QtWidgets>
#include <qpoint.h>
#include <QPainter>
#include "Observer.h"
#include "Service.h"

class ActivitiesProgram :public QWidget, public Observer
{
private:
	Service srv;

	void paintEvent(QPaintEvent* ev) override {
		QPainter p{ this };
		for (int i = 0; i < srv.getCurrent().size(); ++i) {
			p.drawEllipse(QPointF(rand() %400 , rand() %400), 50, 50);
		}
	}


public:
	ActivitiesProgram(Service srv) :srv{ srv } {};
	void update()override {
		QWidget::update();
	}
	ActivitiesProgram() = default;
};

