#ifndef XML2JSON_H
#define XML2JSON_H

#include <algorithm>
#include <locale>
#include <iostream>
#include <fstream>
#include <queue>
using namespace std;



//string FormattedXML_str="<users><user><id>1</id><name>Ahmed Ali</name><posts><post><body>batates</body><topics><topic>economy</topic><topic>finance</topic></topics></post></posts></user></users>";


void getChildrenjson(string Xml,queue <string>& children);
bool isArray(queue <string> children);
string x2json(string XMLStr,int level);







#endif // XML2JSON_H
