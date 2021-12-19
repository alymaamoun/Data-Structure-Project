#ifndef XMLCONSISTENCY_H
#define XMLCONSISTENCY_H
#include <string>
#include <fstream>
#include <stack>
#include <iostream>
using namespace std;
int FileParser(string XMLfile, string* XMLlines);
string IsConsistentFile(string* XMLlines,int size,string *error);


#endif // XMLCONSISTENCY_H
