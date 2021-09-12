
#include "Science.h"

double Science::getIncome() {
    double tmp = 0;
    for (auto pos : _projects) {
        tmp += pos._cost;
    }
    return tmp;
}

Science::Science(std::string name, std::string manager, size_t aspirants, size_t staff, std::vector<Project> projects) {
    _name = name;
    _manager = manager;
    _aspirants = aspirants;
    _staff = staff;
    _projects = projects;
}

void Science::print(std::ostream& out, bool flag) {
    if (flag) {
        out << " ~~~ Science organisation ~~~\n";
        out << "\t\tName: " << _name << "\n\t\tManager: " << _manager << "\n\t\tAspirants: " << _aspirants << "\n\t\tStaff: " << _staff << "\n\t\tProjects:\n" << _projects;
    }
    else {
        out << "sci\n";
        out << _name << "\n" << _manager << "\n" << _aspirants << "\n" << _staff << "\n" << _projects.size() << "\n";
        for ( size_t i = 0; i < _projects.size(); i++)
        {
            out << _projects[i]._project_name << "\n" << _projects[i]._cost << "\n";
        }
    }
}

std::ostream& operator<<(std::ostream& out, const std::vector<Project> p) {
    size_t i = 0;
    for (auto pos : p) { out << "\t\t\tProject " << ++i << ". Project name: " << pos._project_name << ", Cost: " << pos._cost << "\n"; }
    return out;
}