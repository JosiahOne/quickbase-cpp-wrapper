#include "XMLGen.h"

using namespace std;
string GetStringBetween(string data, string startDelim, string endDelim);

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

void XMLGen::SetLocation(string location) {
    if (location != "") {
        _location = location;
    }
}
void XMLGen::SetQBAction(string QBActName) {
    if (QBActName != "") {
        _QBAction = QBActName;
    }
}
void XMLGen::AddParent(string name) {
    _outStream = _outStream + '<' + name + ">\n";
}
void XMLGen::CloseParent(string name) {
    _outStream = _outStream + "</" + name + ">\n";
}
void XMLGen::AddField(string name, string data) {
    _outStream = _outStream + '<' + name + '>' + data + "</" + name + ">\n";
}
bool XMLGen::WriteOut() {
    if (_outStream != "") {
        string fileName = "outputDataStream.xml";
        remove(fileName.c_str());
        ofstream outFile;
        outFile.open(fileName.c_str());
        // Header Information
        outFile << "POST " << _location << " HTTP/1.0" << endl;
        outFile << "Content-Type: application/xml" << endl;
        outFile << "Content-Length:\n";
        outFile << "QUICKBASE-ACTION: " << _QBAction << endl << endl;
        // Contents
        outFile << _outStream;
        outFile.close();
        return true;
    }
    return false;
}
