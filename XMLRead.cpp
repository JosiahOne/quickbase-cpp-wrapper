/*
* Copyright Notice : Copyright 2015, Josiah Bruner, All Rights Reserved.
*/
#include "XMLRead.h"

XMLRead::XMLRead() {
    _xmlData = "";
}

XMLRead::~XMLRead() {
    _xmlData = "";
}

inline std::string trim(const std::string &s)
{
    auto wsfront = std::find_if_not(s.begin(), s.end(), [](int c){return std::isspace(c); });
    auto wsback = std::find_if_not(s.rbegin(), s.rend(), [](int c){return std::isspace(c); }).base();
    return (wsback <= wsfront ? std::string() : std::string(wsfront, wsback));
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
        cout << "TICKET = " << result << endl;
        cout << "XMLData = \n" << _xmlData << endl;
        if (result == "") {
            return "ERROR";
        }
        return result;
    }
    else {
        return "ERROR";
    }
}

string XMLRead::GetRawXML() {
    return _xmlData;
}

void XMLRead::MoveAttributesIntoChildren(string fieldName) {
    if (_VerifyXML(_xmlData)) {
        if (_HasAttributes(fieldName)) {
            vector<attribute> attributes = _GetAttributes(fieldName);
            
            _DeleteAttributes(fieldName);

            for (unsigned int i = 0; i < attributes.capacity(); i++) {
                _CreateChild(attributes[i].name, attributes[i].contents, fieldName);
            }

        }
    }
}

string XMLRead::_GetStringBetween(string data, string startDelim, string endDelim) {
    unsigned first = data.find(startDelim);
    unsigned last = data.find(endDelim);
    if (first != string::npos && last != string::npos) {
        string strNew = data.substr(first + startDelim.length(), last - startDelim.length() - first);
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

bool XMLRead::_HasAttributes(string fieldName) {
    string attributeContents = _GetStringBetween(_xmlData, "<" + fieldName, ">");
    if (attributeContents != "") {
        return true;
    }

    return false;
}

vector<attribute> XMLRead::_GetAttributes(string fieldName) {
    string attributeContents = _GetStringBetween(_xmlData, "<" + fieldName, ">");
    attribute anAttribute;
    vector<attribute> attributeArray = {};
    bool collectingContents = false;
    int marksFound = 0;
    if (attributeContents != "") {
        for (unsigned int i = 0; i < attributeContents.length(); i++) {
            char theChar = attributeContents[i];

            if (collectingContents) {
                if (theChar == '"') {
                    if (marksFound != 2) {
                        marksFound++;
                    }
                    else {
                        collectingContents = false;
                        marksFound = 0;
                        attributeArray.push_back(anAttribute);
                        anAttribute.contents = "";
                        anAttribute.name = "";
                    }
                }
                else {
                    anAttribute.contents += theChar;
                }
            }
            else if (theChar == '=') {
                collectingContents = true;
            }
            else if (theChar != ' ') {
                anAttribute.name += theChar;
            }

        }
    }

    return attributeArray;
}

bool XMLRead::_CreateChild(string name, string content, string parentTagName) {
    try {
        unsigned int loc = _xmlData.find(_MakeTag(parentTagName, true)) + parentTagName.length();

        _xmlData.insert(loc, _MakeTag(name, true) + content + _MakeTag(name, false));
    }
    catch (int e) {
        return false;
    }

    return true;
}

void XMLRead::_DeleteAttributes(string fieldName) {
    unsigned int loc = _xmlData.find("<" + fieldName) + fieldName.length();
    string attributeContents = _GetStringBetween(_xmlData, "<" + fieldName, ">");
    if (attributeContents.length() > 0) {
        cout << "ATT LENGTH = " << attributeContents.length() << "|";
        _xmlData.erase(loc + 1, attributeContents.length());
    }

    cout << endl << endl << _xmlData << endl << endl;
}