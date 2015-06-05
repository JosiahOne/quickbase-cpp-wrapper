/*
 * Copyright Notice : Copyright 2015, Josiah Bruner, All Rights Reserved.
 */
#include "XMLGen.h"

std::string GetStringBetween(std::string data, std::string startDelim, std::string endDelim);

XMLGen::XMLGen() {
    XMLGen::_ResetAll();
}

XMLGen::~XMLGen() {
    XMLGen::_ResetAll();
}

void XMLGen::aReset() {
    XMLGen::_ResetAll();
}

void XMLGen::_ResetAll() {
    _location = "";
    _QBAction = "";
    _outStream = "";
}

void XMLGen::SetLocation(std::string location) {
    if (location != "") {
        _location = location;
    }
}

void XMLGen::SetQBAction(std::string QBActName) {
    if (QBActName != "") {
        _QBAction = QBActName;
    }
}

void XMLGen::AddParent(std::string name) {
    _outStream = _outStream + '<' + name + ">\n";
}

void XMLGen::CloseParent(std::string name) {
    _outStream = _outStream + "</" + name + ">";
}

void XMLGen::AddField(std::string name, std::string data) {
    _outStream = _outStream + '<' + name + '>' + data + "</" + name + ">\n";
}

void XMLGen::AddFieldWithParam(std::string name, std::string data, std::string pName, std::string pData) {
    _outStream = _outStream + '<' + name + ' ' + pName + "='" + pData + "'>" + data + "</" + name + ">\n";
}

bool XMLGen::WriteOut() {
    if (_outStream != "") {
        std::string fileName = "outputDataStream.xml";
        remove(fileName.c_str());
        std::ofstream outFile;
        outFile.open(fileName.c_str());
        outFile << _outStream;
        outFile.close();
        return true;
    }
    return false;
}
