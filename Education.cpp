#include "Education.h"

Education::Education(std::string name, std::string manager, size_t aspirants, size_t staff, std::vector<Course> courses) {
    _name = name;
    _manager = manager;
    _aspirants = aspirants;
    _staff = staff;
    _courses = courses;
}

double Education::getIncome() {
    double tmp = 0;
    for (auto pos : _courses) {
        tmp += (pos._student_cost * pos._student_num);
    }
    return tmp;
}

void Education::print(std::ostream& out, bool flag) {
    if (flag) {
        out << " ~~~ Educational organisation ~~~\n";
        out << "\t\tName: " << _name << "\n\t\tManager: " << _manager << "\n\t\tAspirants: " << _aspirants << "\n\t\tStaff: " << _staff << "\n\t\tCourses:\n" << _courses;
    }
    else {
        out << "edu\n";
        out << _name << "\n" << _manager << "\n" << _aspirants << "\n" << _staff << "\n" << _courses.size() << "\n";
        for (size_t i = 0; i < _courses.size(); i++)
        {
            out << _courses[i]._student_num << "\n" << _courses[i]._student_cost << "\n";
        }
    }
}

size_t Education::getStudents() {
    size_t tmp = _aspirants;
    for (auto pos : _courses) {
        tmp += pos._student_num;
    }
    return tmp;
}

std::ostream& operator<<(std::ostream& out, const std::vector<Course> c) {
    size_t i = 0;
    for (auto pos : c) { out << "\t\t\tCourse " << ++i << ". Students: " << pos._student_num << ", Cost: " << pos._student_cost << "\n"; }
    return out;
}