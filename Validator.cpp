#include "Validator.h"

void Validator::validate(std::string title, std::string description, std::string type, std::string duration) {
	std::vector<std::string> msg;
	if (title.size() == 0)
		msg.push_back("Titlul activitatii este vid! ");
	if (description.size() == 0)
		msg.push_back("Descrierea activitatii este vida! ");
	if (type.size() == 0)
		msg.push_back("Tipul activitatii este vid! ");
	if (atoi(duration.c_str()) <= 0)
		msg.push_back("Durata activitatii este gresita! ");
	if (msg.size() > 0)
		throw ValidateException(msg);
}
std::ostream& operator<<(std::ostream& out, const ValidateException& ex) {
	for (const auto&msg : ex.msg) {
		out << msg << " ";
	}
	return out;
}

std::string ValidateException::getMsg()const noexcept {
	std::string mg;
	for (std::string ms : this->msg)
		mg.append(ms);
	return mg;
}

