#pragma once
#include "Activity.h"
#include "Repository.h"
class ActiuneUndo {
public:
	virtual void doUndo() = 0;
	//destructorul e virtual pentru a ne asigura ca daca dau delete se apeleaza destructorul din clasa care trebuie
	//virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo {
	Activity addedActivity;
	Repository<Activity>& rep;
public:
	UndoAdauga(Repository<Activity>& rep, const  Activity& p) :rep{ rep }, addedActivity{ p } {}
	void doUndo() override {
		rep.remove(addedActivity);
	}
};

class UndoSterge : public ActiuneUndo {
	Activity removedActivity;
	Repository<Activity>& rep;
public:
	UndoSterge(Repository<Activity>& rep, const  Activity& p)noexcept : rep{ rep }, removedActivity{ p } {}
	void doUndo() override {
		rep.add(removedActivity);
	}
};

class UndoUpdate :public ActiuneUndo {
	Activity updatedActivity;
	Activity oldActivity;
	Repository<Activity>& rep;
public:
	UndoUpdate(Repository<Activity>& rep, const Activity&updatedActivity, const Activity& oldActivity)noexcept : rep{ rep }, updatedActivity{ updatedActivity }, oldActivity{ oldActivity } {};
	void doUndo() override {
		rep.update(updatedActivity, oldActivity);
	}
};