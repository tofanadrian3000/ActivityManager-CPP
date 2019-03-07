#include "Activity.h"
#include <assert.h>

Activity::Activity(string title, string description, string type, double duration) {
	this->title = title;
	this->description = description;
	this->type = type;
	this->duration = duration;
}
string Activity::getTitle() const noexcept {
	return this->title;
}
string Activity::getDescription() const noexcept {
	return this->description;
}
string Activity::getType()const noexcept {
	return this->type;
}
double Activity::getDuration() const noexcept {
	return this->duration;
}
void Activity::setTitle(string title) {
	this->title = title;
}
void Activity::setDescription(string description) {
	this->description = description;
}
void Activity::setType(string type) {
	this->type = type;
}
void Activity::setDuration(double duration) {
	this->duration = duration;
}
void Activity::operator =(Activity other) {
	this->title = other.title;
	this->description = other.description;
	this->type = other.type;
	this->duration = other.duration;
	this->stariAnterioare = other.stariAnterioare;
	//assert(stariAnterioare.size() == 0);
}
bool Activity::operator ==(Activity other) {
	return this->title == other.title;
}
bool Activity::operator !=(Activity other) {
	return this->title != other.title;
}
vector<Activity> Activity::readFromFile(string filename) {
	ifstream f(filename);
	vector<Activity> activities;
	string title, description, type;
	double duration;
	Activity activity;
	while (f >> title >> description >> type >> duration) {
		activity = Activity(title, description, type, duration);
		activities.push_back(activity);
	}
	return activities;
}
void Activity::writeToFile(vector<Activity> activities, string filename) {
	ofstream g(filename);
	for (Activity activity : activities)
		g << activity.title << " " << activity.description << " " << activity.type << " " << activity.duration << "\n";
}