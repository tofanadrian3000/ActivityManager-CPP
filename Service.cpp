#include "Service.h"
#include <string>
#include <vector>
#include <algorithm>

void Service::addActivity(string title, string description, string type, string duration) {
	try {
		this->validator.validate(title, description, type, duration);
		Activity activity = Activity(title, description, type, atof(duration.c_str()));
		try {
			this->repo.add(activity);
			this->notifyAll();
			undoActions.push_back(new UndoAdauga(repo, activity));
		}
		catch (RepositoryException) {
			throw ServiceException("Activitate existenta!");
		}
	}
	catch (const ValidateException& exception) {
		throw ServiceException(exception.getMsg());
	}
}

void Service::removeActivity(string title) {
	try {
		this->validator.validate(title, "asd", "asd", "1");
		Activity activity = Activity(title, "default", "default", 1);
		try {
			auto act = repo.find(activity);
			this->repo.remove(activity);
			this->notifyAll();
			undoActions.push_back(new UndoSterge(repo, act));
		}
		catch (const RepositoryException) {
			throw ServiceException("Activitate inexistenta!");
		}
	}
	catch (const ValidateException& exception) {
		throw ServiceException(exception.getMsg());
	}
}

void Service::updateActivity(string title, string newDescription, string newType, string newDuration) {
	try {
		this->validator.validate(title, newDescription, newType, newDuration);
		Activity activity = Activity(title, "asd", "asd", 1);
		Activity newActivity = Activity(title, newDescription, newType, atof(newDuration.c_str()));
		try {
			auto act = repo.find(activity);
			for (auto elem : act.getStariAnterioare())
				newActivity.addStare(elem);
			newActivity.addStare(act);
			//assert(newActivity.getStariAnterioare().size() == 0);
			this->repo.update(activity, newActivity);
			this->notifyAll();
			undoActions.push_back(new UndoUpdate(repo, newActivity, act));
		}
		catch (const RepositoryException) {
			throw ServiceException("Activitate inexistenta!");
		}
	}
	catch (const ValidateException& exception) {
		throw ServiceException(exception.getMsg());
	}
}

size_t Service::size() noexcept {
	return this->repo.size();
}

vector<Activity> Service::getActivities() noexcept {
	return this->repo.getAll();
}

Activity Service::getActivity(string title) {
	Activity activity = Activity(title, "default", "default", 1);
	try {
		return repo.find(activity);
	}
	catch (RepositoryException&) {
		throw ServiceException("Activitate inexistenta!");
	}
}

vector<Activity> Service::descriptionFilter(string description)noexcept {
	vector<Activity> activities = this->repo.getAll();
	vector<Activity> filtered;
	std::copy_if(activities.begin(), activities.end(), std::back_inserter(filtered), [description](Activity activity)noexcept {return activity.getDescription() == description; });
	return filtered;
}

vector<Activity> Service::typeFilter(string type)noexcept {
	vector<Activity> activities = this->repo.getAll();
	vector<Activity> filtered;
	std::copy_if(activities.begin(), activities.end(), std::back_inserter(filtered), [type](Activity activity)noexcept {return activity.getType() == type; });
	return filtered;
}

vector<Activity> Service::titleSort()noexcept {
	vector<Activity> activities = this->repo.getAll();
	std::sort(activities.begin(), activities.end(), [](Activity activity1, Activity activity2)noexcept {return activity1.getTitle() < activity2.getTitle(); });
	return activities;
}

vector<Activity> Service::descriptionSort()noexcept {
	vector<Activity> activities = this->repo.getAll();
	std::sort(activities.begin(), activities.end(), [](Activity activity1, Activity activity2)noexcept {return activity1.getDescription() < activity2.getDescription(); });
	return activities;
}

vector<Activity> Service::typeDurationSort()noexcept {
	vector<Activity> activities = this->repo.getAll();
	std::sort(activities.begin(), activities.end(), [](Activity activity1, Activity activity2)noexcept {if (activity1.getType() < activity2.getType())
		return true;
	if (activity1.getType() == activity2.getType() && activity1.getDuration() < activity2.getDuration())
		return true;
	return false; });
	return activities;
}

void Service::addCurrent(string title) {
	try {
		this->validator.validate(title, "asd", "asd", "1");
		try {
			repo.find(Activity(title, "asd", "asd", 1));
			try {
				this->currentActivities->add(title);
				this->notifyAll();
			}
			catch (RepositoryException) {
				throw ServiceException("Activitatea existenta!");
			}
		}
		catch (RepositoryException) {
			throw ServiceException("Activitatea nu este disponibila!");
		}
	}
	catch (ValidateException& exception) {
		throw ServiceException(exception.getMsg());
	}
}

void Service::removeCurrentActivity(string title) {
	try {
		this->validator.validate(title, "asd", "asd", "1");
		try {
			repo.find(Activity(title, "asd", "asd", 1));
			try {
				this->currentActivities->remove(title);
				this->notifyAll();
			}
			catch (RepositoryException) {
				throw ServiceException("Activitatea existenta!");
			}
		}
		catch (RepositoryException) {
			throw ServiceException("Activitatea nu este disponibila!");
		}
	}
	catch (ValidateException& exception) {
		throw ServiceException(exception.getMsg());
	}
}


void Service::clearCurrent()noexcept {
	for (string activity : this->currentActivities->getAll())
		this->currentActivities->remove(activity);
	this->notifyAll();
}

void Service::generateCurrent(string lenght) {
	int actualLenght = atoi(lenght.c_str());
	if (actualLenght != 0 && actualLenght < this->repo.size()) {
		vector<Activity> activities = this->repo.getAll();
		std::random_shuffle(activities.begin(), activities.end());
		this->clearCurrent();
		while (actualLenght) {
			this->currentActivities->add(activities[actualLenght].getTitle());
			actualLenght--;
			this->notifyAll();
		}
	}
	else throw ServiceException("Lungimea este eronata!");
}

vector<string> Service::getCurrent() noexcept {
	return this->currentActivities->getAll();
}

void Service::undo() {
	if (undoActions.empty()) {
		throw ServiceException("Nu se mai poate efectua undo!");
	}
	undoActions.back()->doUndo();
	this->notifyAll();
	undoActions.pop_back();
}

void Service::exportRepoCVS(string fName) const {
	exportToCVS(fName, repo.getAll());
}

void Service::exportRepoHTML(string fName) const {
	exportToHTML(fName, repo.getAll());
}

std::ostream& operator<<(std::ostream& out, const ServiceException& ex) {
	out << ex.msg;
	return out;
}
