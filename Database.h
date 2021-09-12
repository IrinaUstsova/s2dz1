#ifndef DATABASE_H
#define DATABASE_H
#include "Education.h"
#include "Science.h"

class Database {
    std::vector<Organization*> _data;
    std::string _db_name;
public:
    Database(std::string name) : _db_name(name) {}
    void add();
    void set(Organization* org);
    void remove(size_t index);
    friend std::ostream& operator<<(std::ostream& out, const Database& db);
    void sort(bool flag);
    std::vector<Organization*> choose(bool flag);
    std::string getName() { return _db_name; }
    std::vector<Organization*>& getData() { return _data; }
    void rename(std::string name);
};

#endif