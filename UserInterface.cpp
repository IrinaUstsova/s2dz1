#include "UserInterface.h"

std::vector<Database> databases;
auto root = fs::current_path();

void CreateDB()
{
    std::cout << "Enter database name: ";
    std::string name;
    std::cin.ignore();
    getline(std::cin, name);
    Database db(name);
    databases.push_back(db);
    std::cout << "Database '" << name << "' created.\n";
}

void UI_init(bool flag)
{
    if (flag) {
        system("pause");
        system("cls");
    }
    else { Get(); }
    std::cout << "   The list of available commands:\n";
    std::cout << "1) create \t(create new database)\n2) remove <db> \t(remove database)\n";
    std::cout << "3) list \t(show list of databases)\n4) print <db> \t(print database info)\n";
    std::cout << "5) add <db> \t(add new organization to the database)\n6) delete <db> \t(remove organization from a database)\n";
    std::cout << "7) save \t(save databases to a file)\n8) get \t(get databases from a file) Don't forget to save existing information!!!\n";
    std::cout << "9) sort <db>\n10) sample <db> (create a sample using special rule)\n11) rename <db>\n12) exit\n* <db> is a number of database in a list\n\n";
}

void UI_chat()
{
    std::cout << "> ";
    std::string command;
    std::cin >> command;
    if (command == "create") { CreateDB(); return; }
    else if (command == "add") {
        int db;
        std::cin >> db;
        if (db > databases.size() || db < 1)
        {
            std::cerr << "Wrong key! Try another one.\n"; return;
        }
        databases[db - 1].add();
    }
    else if (command == "save")
    {
        Save();
    }
    else if (command == "get") {
        Get();
    }
    else if (command == "remove") {
        int db;
        std::cin >> db;
        if (db > databases.size() || db < 1)
        {
            std::cerr << "Wrong key! Try another one.\n"; return;
        }
        std::vector<Database>::iterator it = databases.begin();
        for (size_t i = 1; i < db; i++)
        {
            it++;
        }
        databases.erase(it);
    }
    else if(command == "print"){
        int db;
        std::cin >> db;
        if (db > databases.size() || db < 1)
        {
            std::cerr << "Wrong key! Try another one.\n"; return;
        }
        std::cout << databases[db - 1];
    }
    else if (command == "list") {
        std::cout << "   Loaded databases:\n";
        size_t i = 0;
        for (auto pos: databases)
        {
            i++;
            std::cout << i << ") " << pos.getName() << std::endl;
        }
        std::cout << "   External databases (need to use 'get' to load them):\n";
        i = 0;
        fs::current_path(root);
        fs::current_path("db");
        auto cur = fs::current_path();
        for (const auto& entry : fs::directory_iterator(cur)) {
            std::ifstream fin(entry.path());
            if (!fin) {
                std::cerr << "Error!\n"; return;
            }
            std::string db_name;
            getline(fin, db_name);
            i++;
            std::cout << i << ") " << db_name << std::endl;
            fin.close();
        }
    }
    else if (command == "exit") {
        exit(EXIT_SUCCESS);
    }
    else if (command == "delete") {
        int db;
        std::cin >> db;
        if (db > databases.size() || db < 1)
        {
            std::cerr << "Wrong key! Try another one.\n"; return;
        }
        if (databases[db - 1].getData().size() == 0) {
            std::cerr << "Nothing to delete.\n"; return;
        }
        std::cout << databases[db - 1];
        std::cout << "Which organization should be deleted ? ";
        int n; std::cin >> n;
        try
        {
            databases[db - 1].remove(n);
        }
        catch (const std::exception& exc)
        {
            std::cerr << exc.what(); return;
        }
    }
    else if (command == "sort") {
        int db;
        std::cin >> db;
        if (db > databases.size() || db < 1)
        {
            std::cerr << "Wrong key! Try another one.\n"; return;
        }
        std::cout << "Choose method of sorting (0 - by name, 1 - number of staff (reverse)): ";
        bool b; std::cin >> b;
        databases[db - 1].sort(b);
    }
    else if (command == "sample") {
        int db;
        std::cin >> db;
        if (db > databases.size() || db < 1)
        {
            std::cerr << "Wrong key! Try another one.\n"; return;
        }
        std::cout << "Choose rule of sample (0 - aspirants/staff >= n, 1 - number of students(including aspirants) <= n): ";
        bool b; std::cin >> b;
        try
        {
            std::vector<Organization*> newdata = databases[db - 1].choose(b);
            std::cout << "Save as a new database ? [0 = no, 1 - yes] ";
            bool b; std::cin >> b;
            if (b) {
                std::string name;
                std::cout << "Name for a new database: ";
                std::cin.ignore();
                getline(std::cin, name);
                Database newdb(name);
                for (size_t i = 0; i < newdata.size(); i++)
                {
                    newdb.set(newdata[i]);
                }
                databases.push_back(newdb);
            }
        }
        catch (const std::exception& exc)
        {
            std::cerr << exc.what();
            return;
        }
    }
    else if (command == "rename") {
        int db;
        std::cin >> db;
        if (db > databases.size() || db < 1)
            {
                std::cerr << "Wrong key! Try another one.\n"; return;
            }
        std::cout << "Enter new database name: ";
        std::string name;
        std::cin.ignore();
        getline(std::cin, name);
        databases[db - 1].rename(name);
    }
    else {
        std::cerr << "Unknown command\n"; return;
    }
}

void Save() {
    fs::current_path(root);
    fs::create_directory("db");
    fs::current_path("db");
    auto cur = fs::current_path();
    for (const auto& entry : fs::directory_iterator(cur))
    {
        remove(entry.path());
    }
    for (size_t i = 0; i < databases.size(); i++)
    {
        std::ofstream fout("db" + std::to_string(i) + ".txt");
        if (!fout)
        { std::cerr << "Error!\n"; return; }

        fout << databases[i].getName() << std::endl;
        fout << databases[i].getData().size() << std::endl;
        for (size_t j = 0; j < databases[i].getData().size(); j++)
        {
            databases[i].getData()[j]->print(fout, 0);
        }
        fout.close();
    }
}

void Get() {
    databases.clear();
    fs::current_path(root);
    fs::current_path("db");
    auto cur = fs::current_path();
    for (const auto& entry : fs::directory_iterator(cur)) {
        std::ifstream fin(entry.path());
        if (!fin) {
            std::cerr << "Error!\n"; return;
        }
        std::string db_name, type, name, manager; int asp, staff, n, count;
        getline(fin, db_name);

        Database db(db_name);

        fin >> count;
        for (size_t i = 0; i < count; i++)
        {
            fin.ignore();
            getline(fin, type);

            getline(fin, name); getline(fin, manager);
            fin >> asp; fin >> staff; fin >> n;

            if (type == "sci") {
                std::vector<Project> pro;
                for (size_t i = 0; i < n; i++)
                {
                    std::string p_name; double cost;
                    fin.ignore();
                    getline(fin, p_name); fin >> cost;
                    Project p = { p_name, cost };
                    pro.push_back(p);
                }
                Organization* org = new Science(name, manager, asp, staff, pro);
                db.set(org);
            }
            else if (type == "edu") {
                std::vector<Course> cou;
                for (size_t i = 0; i < n; i++)
                {
                    size_t num; double cost;
                    fin >> num; fin >> cost;
                    Course c = { num, cost };
                    cou.push_back(c);
                }
                Organization* org = new Education(name, manager, asp, staff, cou);
                db.set(org);
            }
            else {
                std::cerr << "Error!\n"; return;
            }
        }
        databases.push_back(db);
    }
}