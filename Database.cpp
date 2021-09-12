#include "Database.h"
#include <algorithm>


void Database::add() {
    std::cout << "Which type of organization? (sci / edu): ";
    std::string type; std::cin >> type;
    if (type == "sci")
    {
        std::string name, manager;
        size_t asp, staff, n;
        std::cout << "Organization name: "; std::cin.ignore(); getline(std::cin, name);
        std::cout << "Manager name: "; getline(std::cin, manager);
        std::cout << "Number of aspirants: "; std::cin >> asp;
        std::cout << "Number of staff: "; std::cin >> staff;
        std::cout << "Number of projects: "; std::cin >> n;
        std::vector<Project> projects;
        for (size_t i = 0; i < n; i++)
        {
            std::string pr_name; size_t cost;
            std::cout << "Project " << i + 1 << " name: "; std::cin.ignore(); getline(std::cin, pr_name);
            std::cout << "Project " << i + 1 << " cost: "; std::cin >> cost;
            Project pr = { pr_name, cost };
            projects.push_back(pr);
        }
        Organization* sci = new Science(name, manager, asp, staff, projects);
        _data.push_back(sci);
        return;
    }
    else if (type == "edu") {
        std::string name, manager;
        size_t asp, staff, n;
        std::cout << "Organization name: "; std::cin.ignore(); getline(std::cin, name);
        std::cout << "Manager name: "; getline(std::cin, manager);
        std::cout << "Number of aspirants: "; std::cin >> asp;
        std::cout << "Number of staff: "; std::cin >> staff;
        std::cout << "Number of cources: "; std::cin >> n;
        std::vector<Course> courses;
        for (size_t i = 0; i < n; i++)
        {
            size_t num, cost;
            std::cout << "Course " << i + 1 << ") Number of students: "; std::cin >> num;
            std::cout << "Course " << i + 1 << ") Cost: "; std::cin >> cost;
            Course c = { num, cost };
            courses.push_back(c);
        }
        Organization* edu = new Education(name, manager, asp, staff, courses);
        _data.push_back(edu); return;
    }
    else {
        std::cerr << "Wrong type!\n"; return;
    }
}

void Database::set(Organization* org)
{
    _data.push_back(org);
}

std::ostream& operator<<(std::ostream& out, const Database& db) {
    if (db._data.empty()) { out << "Empty database.\n"; return out; }
    std::cout << db._db_name << "\n";
    size_t i = 0;
    for (auto pos : db._data) {
        out << "\t" << ++i << ") ";
        (*pos).print(out, 1);
    }
    return out;
}

void Database::remove(size_t index) {
    if (index > _data.size())throw std::invalid_argument("There is no such database!\n");
    _data.erase(_data.begin() + index - 1);
}

void Database::sort(bool flag) {
    if (!flag) {
        std::sort(_data.begin(), _data.end(), [](Organization* a, Organization* b) { return (*a).getName() < (*b).getName(); });
    }
    else {
        std::sort(_data.begin(), _data.end(), [](Organization* a, Organization* b) { return (*a).getStaff() > (*b).getStaff(); });
    }
}

std::vector<Organization*> Database::choose(bool flag) {
    if (!flag) {
        size_t n; std::cout << "Enter N (staff / aspirants): "; std::cin >> n;
        std::vector<Organization*> tmp;
        for (auto pos : _data) {
            if ((*pos).getAsp() / (*pos).getStaff() >= n) {
                tmp.push_back(pos);
            }
        }
        if (tmp.empty()) { throw std::invalid_argument("No such databases!\n"); }
        else {
            std::cout << "Result: ";
            for (auto pos : tmp) { std::cout << (*pos).getName() << "; "; }
        }
        std::cout << std::endl;
        return tmp;
    }
    else {
        size_t n;
        std::cout << "Enter N: ";
        std::cin >> n;
        std::vector<Organization*> tmp;
        for (auto pos : _data) {
            if ((*pos).getStudents() <= n) {
                tmp.push_back(pos);
            }
        }
        if (tmp.empty()) {
            throw std::invalid_argument("No such databases!\n");
        }
        else {
            std::cout << "Result: ";
            for (auto pos : tmp) { std::cout << (*pos).getName() << "; "; }
        }
        std::cout << std::endl; return tmp;
    }
}

void Database::rename(std::string name)
{
    _db_name = name;
}
