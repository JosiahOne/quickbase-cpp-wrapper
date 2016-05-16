/*
 * Copyright Notice : Copyright 2015, Josiah Bruner, All Rights Reserved.
 */
#include "XMLGen.h"
#include <ctime>
#include <cstdlib>

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

inline bool file_exists(const std::string& name) {
  std::ifstream f(name.c_str());
  if (f.good()) {
    f.close();
    return true;
  }
  else {
    f.close();
    return false;
  }
}

std::string XMLGen::WriteOut() {
  if (_outStream != "") {
    std::string suffix = "";

    unsigned seed = time(0);
    srand(seed);
    char randomChar = 'a' + rand() % 26;

    while (file_exists("outputDataStream" + suffix + ".xml")) {
      suffix += "a";
    }

    std::string fileName = "outputDataStream" + suffix + randomChar + ".xml";
    remove(fileName.c_str());
    std::ofstream outFile;
    outFile.open(fileName.c_str());
    outFile << _outStream;
    outFile.close();
    return fileName;
  }
  return "ERROR";
}
