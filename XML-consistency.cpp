// XML-consistency.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stack>
#include <fstream>
#include <string>
using namespace std;

bool IsConsistentFile(string XMLfile);

int main()
{
    string fileName = "sample.xml";
    cout << IsConsistentFile(fileName);
}

bool IsConsistentFile(string XML)
{
    ifstream XMLfile;
    XMLfile.open(XML, ios::in);
    string XMLlines[1000];
    stack <string> tags;
    bool open = true;
    int size = 0;
    bool lineparsed = false;

    if (XMLfile.is_open())
    {
        string line;
        while (getline(XMLfile, line))
        {
            XMLlines[size] = line;
            size++;
        }
        int x = 0;
        while (x < size)
        {
            lineparsed = false;
            string lines = XMLlines[x];
            int index = 0;
            for (; lines[index] != NULL; index++)
            {
                if (lines[index] == '<'||lines[index]=='/'||lines[index]=='>')
                {
                    int start;
                    if (lines[index] == '<')
                    {
                        if (lines[index + 1] == '/')
                        {
                            index++;
                            open = false;
                        }
                        else
                        {
                            open = true;
                        }

                        start = index;
                        while (lines[start] != '>')
                        {
                            start++;
                            if (lines[start] == NULL)
                            {

                                cout << "ERROR,missed '>' at line: " << x << endl;

                                lines = lines + '>';
                                XMLlines[x] = lines;
                                cout << " (>) insereted automaticly" << endl;
                                //return false;
                            }
                            if (lines[start] == ' ')
                            {
                                cout << "ERROR,missed '>' at line: " << x << endl;
                                lines[start] = '>';
                                cout << " (>) insereted automaticly" << endl;
                            }
                        }
                    }
                    else if (lines[index] == '/')
                    {
                        lines.insert(index, "<");
                        open = false;
                        start = index+1;
                        index++;
                        while (lines[start] != '>')
                        {
                            start++;
                            if (lines[start] == NULL)
                            {

                                cout << "ERROR,missed '>' at line: " << x << endl;

                                lines = lines + '>';
                                XMLlines[x] = lines;
                                cout << " (>) insereted automaticly" << endl;
                                //return false;
                            }
                            if (lines[start] == ' ')
                            {
                                cout << "ERROR,missed '>' at line: " << x << endl;
                                lines[start] = '>';
                                cout << " (>) insereted automaticly" << endl;
                            }
                        }
                        XMLlines[x] = lines;
                        

                    }
                    else if (lines[index] == '>')
                    {
                        if (!lineparsed)
                        {
                            int tempindex = 0;
                            for (; isspace(lines[tempindex]); tempindex++);
                            lines.insert(tempindex, "<");
                            XMLlines[x] = lines;
                            start = index+1;
                            index = tempindex;
                            open = true;
                            lineparsed = true;

                        }

                    }
                    string tag = lines.substr(index + 1, start - index - 1);
                    index = start++;
                    if (open)
                    {

                        tags.push(tag);
                    }
                    else
                    {
                        if (tag == tags.top())
                        {
                            tags.pop();
                        }
                        else
                        {




                            cout << "No opening tag for: " << tag << "at line: " << x << endl;
                           // return false;
                            int tempindex = 0;
                            for (; isspace(XMLlines[x][tempindex]); tempindex++);
                            XMLlines[x].insert(tempindex, "<" + tag + ">");
                            x--;
                        }
                    }
                    cout << tag << endl;
                    //index = start;


                }

                else {
                    continue;
                }
            }

            x++;
        }
    }


    while (!tags.empty())
    {
        cout << "No closing Tag for Tag: " << tags.top() << endl;
        XMLlines[size-1] = "</" + tags.top() + '>';
        size++;
        tags.pop();
        cout << "Closing Tag added automaticly" << endl;
    }

    int y = 0;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << "AFTER correction" << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    while (y < size)
    {
        cout << XMLlines[y] << endl;
        y++;
    }
    return true;
}


