#ifndef ORGANIZATION_H
#define ORGANIZATION_H
#include <iostream>
#include <string>
#include <vector>

class Organization {
protected:
    std::string _name;
    std::string _manager;
    size_t _aspirants;
    size_t _staff;
public:
    virtual double getIncome() = 0;
    virtual void print(std::ostream& out, bool flag) = 0;
    virtual std::string getName() = 0;
    virtual size_t getStaff() = 0;
    virtual size_t getAsp() = 0;
    virtual size_t getStudents() = 0;
};

#endif