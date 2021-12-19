
#include "xmlconsistency.h"

int FileParser(string XML, string* XMLlines)
{
    int size = 0;
    ifstream XMLfile;
    XMLfile.open(XML, ios::in);
    if (XMLfile.is_open())
    {
        string line;
        while (getline(XMLfile, line))
        {
            XMLlines[size] = line;
            size++;
        }
    }
    return size;
}

bool IsConsistentFile( string* XMLlines,int size)
{


    stack <string> tags;
    bool open = true;

    bool lineparsed = false;
    int errors = 0;


        int x = 0;
        while (x < size)
        {
            lineparsed = false;
            string lines = XMLlines[x];
            int index = 0;
            for (; lines[index] != NULL; index++)
            {
                if ((lines[index] == '<' || lines[index] == '/' || lines[index] == '>')&&((lines.find("<") != std::string::npos) || (lines.find(">") != std::string::npos)))
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
                                errors++;
                                lines = lines + '>';
                                XMLlines[x] = lines;
                                cout << " (>) insereted automaticly" << endl;
                                //return false;
                            }
                            if (lines[start] == ' ')
                            {
                                cout << "ERROR,missed '>' at line: " << x << endl;
                                errors++;
                                lines[start] = '>';
                                cout << " (>) insereted automaticly" << endl;
                            }
                        }
                    }
                    else if (lines[index] == '/')
                    {
                        lines.insert(index, "<");
                        open = false;
                        start = index + 1;
                        index++;
                        while (lines[start] != '>')
                        {
                            start++;
                            if (lines[start] == NULL)
                            {

                                cout << "ERROR,missed '>' at line: " << x << endl;
                                errors++;

                                lines = lines + '>';
                                XMLlines[x] = lines;
                                cout << " (>) insereted automaticly" << endl;
                                //return false;
                            }
                            if (lines[start] == ' ')
                            {
                                cout << "ERROR,missed '>' at line: " << x << endl;
                                errors++;
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
                            start = index + 1;
                            index = tempindex;
                            open = true;
                            cout << "ERROR,missed '<' at line: " << x << endl;
                            cout << " (<) insereted automaticly" << endl;
                            errors++;
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
                            cout << "opening Tag added automaticly" << endl;
                            x--;
                        }
                    }

                    //index = start;


                }

                else {
                    continue;
                }
            }

            x++;
        }



    while (!tags.empty())
    {
        cout << "No closing Tag for Tag: " << tags.top() << endl;
        errors++;
        XMLlines[size - 1] = "</" + tags.top() + '>';
        size++;
        tags.pop();
        cout << "Closing Tag added automaticly" << endl;
    }

    int y = 0;
    cout << "Total Errors: " << errors << endl;
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


