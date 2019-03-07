#include "exportActivities.h"

void exportToCVS(const std::string& fName, const std::vector<Activity>& activities) {
	std::ofstream out(fName, std::ios::trunc);
	for (const auto& p : activities) {
		out << p.getTitle() << ",";
		out << p.getDescription() << ",";
		out << p.getType() << std::endl;
		out << p.getDuration() << std::endl;
	}
	out.close();
}

void exportToHTML(const std::string& fName, const std::vector<Activity>& activities) {
	std::ofstream out(fName, std::ios::trunc);
	out << "<html><body>" << std::endl;
	out << "<table border=\"1\" style=\"width:100 % \">" << std::endl;
	for (const auto& p : activities) {
		out << "<tr>" << std::endl;
		out << "<td>" << p.getTitle() << "</td>" << std::endl;
		out << "<td>" << p.getDescription() << "</td>" << std::endl;
		out << "<td>" << p.getType() << "</td>" << std::endl;
		out << "<td>" << p.getDuration() << "</td>" << std::endl;
		out << "</tr>" << std::endl;
	}
	out << "</table>" << std::endl;
	out << "</body></html>" << std::endl;
	out.close();
}