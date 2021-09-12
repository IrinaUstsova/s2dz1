#ifndef SCIENCE_H
#define SCIENCE_H
#include "Organization.h"

struct Project {
    std::string _project_name;
    double _cost;
    bool operator<(const Project& other) { return _project_name < other._project_name; }
};

class Science : public Organization {
    std::vector<Project> _projects;
public:
    Science(std::string name, std::string manager, size_t aspirants, size_t staff, std::vector<Project> projects);
    double getIncome() override;
    void print(std::ostream& out, bool flag) override;
    std::string getName() override { return _name; }
    size_t getStaff() override { return _staff; }
    size_t getAsp() override { return _aspirants; }
    size_t getStudents() override { return _aspirants; }
};

std::ostream& operator<<(std::ostream& out, const std::vector<Project> p);

#endif