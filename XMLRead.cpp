#include "XMLRead.h"

string GetStringBetween(string data, string startDelim, string 
endDelim);

using namespace XMLRead;

XMLRead::XMLRead() {
    _xmlData = "";
}

XMLRead::~XMLRead() {
    _xmlData = "";
}

void XMLRead::Load(string xmlData) {
    if (xmlData) {
        _xmlData = xmlData;
    }
}

string XMLRead::GetFieldContents(string fieldName) {
    string data = GetStringBetween(_xmlData, '<' + fieldName + '>', "</" + fieldName + '>');
    return data;
}

string GetStringBetween(string data, string startDelim, string endDelim) 
{
    unsigned first = data.find(startDelim);
    unsigned last = data.find(endDelim);
    if (first != npos && last != npos) {
        string strNew = data.substr(first, last - first);
        return strNew;
    }
    else {
        return null;
    }
}
