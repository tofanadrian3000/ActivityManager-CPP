#pragma once
#include <FileRepository.h>
#include "ActiuneUndo.h"
#include <memory>
#include "Activity.h"
#include "Validator.h"
#include <string>
#include <vector>
#include <algorithm>
#include "exportActivities.h"
#include "Observer.h"

class Service : public Observable
{
private:
	FileRepository<Activity> repo;
	Validator validator;
	Repository<string>* currentActivities = new Repository<string>();
	vector<ActiuneUndo* > undoActions;
public:

	Service() {
		this->repo = FileRepository<Activity>("");
	}
	Service(string filename) :repo{ FileRepository<Activity>(filename) } {};

	/*
	Description:- adds a valid activity to the repo from service
	Input:	- title (the name of the activity)
	- description (the description of the activity)
	- type (the type of the activity)
	- duration (the duration of the activity)
	Output:-
	*/
	void addActivity(string title, string description, string type, string duration);

	/*
	Description:- removes a valid activity to the repo from service
	Input:	- title (the name of the activity)
	Output:-
	*/
	void removeActivity(string title);

	/*
	Description:- modifies a valid activity from service
	Input:	- title (the name of the activity)
	- newDescription (the new description of the activity)
	- newType (the new type of the activity)
	- newDuration (the new duration of the activity)
	Output:-
	*/
	void updateActivity(string title, string newDescription, string newType, string newDuration);

	/*
	Description:- gets the number of activities from service
	Input:-
	Output:	- returns the number of activities from service
	*/
	size_t size() noexcept;

	/*
	Description:- gets all the activities from service
	Input:-
	Output:	- returns a vector with all activities from service
	*/
	vector<Activity> getActivities() noexcept;

	/*
	Description:-gets the activity with the given title
	Input:	- title (the name of the activity)
	Output:	- returns the activity which have the same title
	*/
	Activity getActivity(string title);

	/*
	Description:- filters the list of activities by description
	Input:	- description (the description of the activities)
	Output:	- returns all the activities that have the given description
	*/
	vector<Activity> descriptionFilter(string description) noexcept;

	/*
	Description:- fiters the list of activities by type
	Input:	- type (the type of the activities)
	Output:	- returns all the activities that have the given type
	*/
	vector<Activity> typeFilter(string type) noexcept;

	/*
	Description:- gets a sorted list by title
	Input:-
	Output:	- returns all the activities sorted by title
	*/
	vector<Activity> titleSort()noexcept;

	/*
	Description:- gets a sorted list by the description
	Input:	-
	Output:	- returns all the activities sorted by description
	*/
	vector<Activity> descriptionSort()noexcept;

	/*
	Description:- gets a sorted list by the type and duration
	Input:	-
	Output:	- returns all the activities sorted by type and duration
	*/
	vector<Activity> typeDurationSort()noexcept;

	/*
	*/
	void addCurrent(string title);

	/*
	*/
	void removeCurrentActivity(string title);


	/*
	*/
	void clearCurrent()noexcept;

	/*
	*/
	void generateCurrent(string lenght);

	/*
	*/
	vector<string> getCurrent()noexcept;

	/*
	*/
	void undo();

	/*
	*/
	void exportRepoCVS(string fName) const;

	/*
	*/
	void exportRepoHTML(string fName)const;

	//~Service() {};
};

class ServiceException {
	string msg;
public:
	ServiceException(string m) :msg{ m } {}
	string getMsg() { return msg; }
	friend std::ostream& operator<<(std::ostream& out, const ServiceException& ex);
};
std::ostream& operator<<(std::ostream& out, const ServiceException& ex);