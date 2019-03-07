#pragma once
#include <string>
#include<vector>
#include "Activity.h"
class ValidateException {
	std::vector<std::string> msg;
public:
	ValidateException(const std::vector<std::string>& errors) :msg{ errors } {}
	friend std::ostream& operator<<(std::ostream& out, const ValidateException& ex);
	std::string getMsg()const noexcept;
};
std::ostream& operator<<(std::ostream& out, const ValidateException& ex);

class Validator
{
public:
	void validate(std::string title, std::string description, std::string type, std::string duration);
};

