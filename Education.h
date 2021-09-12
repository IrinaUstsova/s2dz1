#ifndef EDUCATION_H
#define EDUCATION_H
#include "Organization.h"

struct Course {
    size_t _student_num;
    double _student_cost;
};

class Education : public Organization {
    std::vector<Course> _courses;
public:
    Education(std::string name, std::string manager, size_t aspirants, size_t staff, std::vector<Course> courses);
    double getIncome() override;
    void print(std::ostream& out, bool flag) override;
    std::string getName() override { return _name; }
    size_t getStaff() override { return _staff; }
    size_t getAsp() override { return _aspirants; }
    size_t getStudents() override;
};

std::ostream& operator<<(std::ostream& out, const std::vector<Course> c);

#endif