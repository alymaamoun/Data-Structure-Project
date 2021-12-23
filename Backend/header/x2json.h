#ifndef X2JSON_H
#define X2JSON_H

#include <algorithm>
#include <locale>
#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

void getChildren(string Xml,queue <string>& children);
bool isArray(queue <string> children);
string x2json(string XMLStr,int level);

#endif 