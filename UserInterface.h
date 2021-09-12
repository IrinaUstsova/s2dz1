#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "Database.h"
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

void CreateDB();

void UI_init(bool flag);

void UI_chat();

void Save();

void Get();

#endif