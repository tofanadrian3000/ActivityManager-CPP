#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "Activity.h"
/*
Scrie in fisierul fName lista de animale
in format Comma Separated Values
arunca ActivityException daca nu poate crea fisierul
*/
void exportToCVS(const std::string& fName, const std::vector<Activity>& activities);
/*
Scrie in fisierul fName lista de animale
in format HTML
arunca ActivityException daca nu poate crea fisierul
*/
void exportToHTML(const std::string& fName, const std::vector<Activity>& activities);