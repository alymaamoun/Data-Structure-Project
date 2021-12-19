#include "Minifying.h"


void Minify(string* XML_file) {
    XML_file->erase(remove(XML_file->begin(), XML_file->end(), '\n'), XML_file->end());
    XML_file->erase(remove(XML_file->begin(), XML_file->end(), ' '), XML_file->end());

}
