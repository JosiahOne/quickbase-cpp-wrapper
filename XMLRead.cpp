#include "XMLRead.h"

XMLRead::XMLRead() {
    _xmlData = "";
}

XMLRead::~XMLRead() {
    _xmlData = "";
}

void XMLRead::Load(string xmlData) {
    if (xmlData != "") {
        _xmlData = xmlData;
    }
}

string XMLRead::GetFieldContents(string fieldName) {
    // _xmlData should be valid XML data.
    // To verify, we should find a <qdbapi> tag.

    if (_VerifyXML(_xmlData)) {
        string result = _GetStringBetween(_xmlData, _MakeTag(fieldName, true), _MakeTag(fieldName, false));
        if (result == "") {
            return "ERROR";
        }
        return result;
    }
    else {
        return "ERROR";
    }
}

string XMLRead::_GetStringBetween(string data, string startDelim, string endDelim) {
    unsigned first = data.find(startDelim);
    unsigned last = data.find(endDelim);
    if (first != string::npos && last != string::npos) {
        string strNew = data.substr(first + startDelim.length(), last - endDelim.length() - first + 1);
        return strNew;
    }
    else {
        return "ERROR";
    }
}

string XMLRead::_MakeTag(string name, bool open) {
    if (open) {
        return '<' + name + '>';
    }
    else {
        return "</" + name + ">";
    }
}

bool XMLRead::_VerifyXML(string data) {
    if (data.find_last_of("<qdbapi>") != string::npos) {
        return true;
    }
    else {
        return false;
    }
}