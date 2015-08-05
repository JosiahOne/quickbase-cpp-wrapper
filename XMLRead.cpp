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

void XMLRead::Load(std::string xmlData) {
    if (xmlData != "") {
        _xmlData = xmlData;
    }
}

std::string XMLRead::GetFieldContents(std::string fieldName) {
    // _xmlData should be valid XML data.
    // To verify, we should find a <qdbapi> tag.

    if (_VerifyXML(_xmlData)) {
        std::string result = _GetStringBetween(_xmlData, _MakeTag(fieldName, true), _MakeTag(fieldName, false));
        std::cout << "TICKET = " << result << std::endl;
        std::cout << "XMLData = \n" << _xmlData << std::endl;
        if (result == "") {
            return "ERROR";
        }
        return result;
    }
    else {
        return "ERROR";
    }
}

std::string XMLRead::GetRawXML() {
    return _xmlData;
}

void XMLRead::MoveAttributesIntoChildren(std::string fieldName) {
    if (_VerifyXML(_xmlData)) {
        if (_HasAttributes(fieldName)) {
            std::vector<attribute> attributes = _GetAttributes(fieldName);
            
            _DeleteAttributes(fieldName);

            for (unsigned int i = 0; i < attributes.capacity(); i++) {
                _CreateChild(attributes[i].name, attributes[i].contents, fieldName);
            }

        }
    }
}

std::string XMLRead::_GetStringBetween(std::string data, std::string startDelim, std::string endDelim) {
    unsigned int first = data.find(startDelim);
    unsigned int last = data.find(endDelim, first);
    if (first != std::string::npos && last != std::string::npos) {
        std::string strNew = data.substr(first + startDelim.length(), last - startDelim.length() - first);
        return strNew;
    }
    else {
        return "ERROR";
    }
}

std::string XMLRead::_MakeTag(std::string name, bool open) {
    if (open) {
        return '<' + name + '>';
    }
    else {
        return "</" + name + ">";
    }
}

bool XMLRead::_VerifyXML(std::string data) {
    if (data.find_last_of("<qdbapi>") != std::string::npos) {
        return true;
    }
    else {
        return false;
    }
}

bool XMLRead::_HasAttributes(std::string fieldName) {
    std::string attributeContents = _GetStringBetween(_xmlData, "<" + fieldName, ">");
    if (attributeContents != "") {
        return true;
    }

    return false;
}

std::vector<attribute> XMLRead::_GetAttributes(std::string fieldName) {
    std::string attributeContents = _GetStringBetween(_xmlData, "<" + fieldName, ">");
    attribute anAttribute;
    std::vector<attribute> attributeArray;
    bool collectingContents = false;
    int marksFound = 0;
    if (attributeContents != "") {
        for (unsigned int i = 0; i < attributeContents.length(); i++) {
            char theChar = attributeContents[i];

            if (collectingContents) {
                if (theChar == '"') {
                    if (marksFound != 1) {
                        marksFound++;
                    }
                    else {
                        std::cout << "***** FOUND *****";
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

bool XMLRead::_CreateChild(std::string name, std::string content, std::string parentTagName) {
    std::cout << "Name = " << name << ", content = " << content << ", parentTagName = " << parentTagName << std::endl;
    unsigned int loc = _xmlData.find(_MakeTag(parentTagName, true)) + parentTagName.length() + 2;
    _xmlData.insert(loc, _MakeTag(name, true) + content + _MakeTag(name, false));

    return true;
}

void XMLRead::_DeleteAttributes(std::string fieldName) {
    unsigned int loc = _xmlData.find("<" + fieldName) + fieldName.length();
    std::string attributeContents = _GetStringBetween(_xmlData, "<" + fieldName, ">");
    if (attributeContents.length() > 0) {
        std::cout << "ATT LENGTH = " << attributeContents.length() << "|";
        _xmlData.erase(loc + 1, attributeContents.length());
    }

    std::cout << std::endl << std::endl << _xmlData << std::endl << std::endl;
}