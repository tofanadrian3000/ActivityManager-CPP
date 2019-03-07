#pragma once
#include <string>
#include <fstream>
#include <vector>
using namespace std;
class Activity
{
private:
	string title;
	string description;
	string type;
	double duration;
	vector<Activity> stariAnterioare;
public:
	Activity() = default;
	Activity(string title, string description, string type, double duration);
	string getTitle()const noexcept;
	string getDescription()const noexcept;
	string getType()const noexcept;
	double getDuration()const noexcept;
	void setTitle(string title);
	void setDescription(string description);
	void setType(string type);
	void setDuration(double duration);
	void addStare(Activity stare) {
		this->stariAnterioare.push_back(stare);
	}
	vector<Activity> getStariAnterioare() {
		return stariAnterioare;
	}
	void operator =(Activity other);
	bool operator ==(Activity other);
	bool operator !=(Activity other);
	static vector<Activity> readFromFile(string filename);
	static void writeToFile(vector<Activity> activities, string filename);
	~Activity() = default;
};

