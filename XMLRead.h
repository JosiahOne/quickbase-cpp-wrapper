/*
 * Copyright Notice : Copyright 2015, Josiah Bruner, All Rights Reserved.
 */
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cctype>
using namespace std;

struct range {
    unsigned int start_pos;
    unsigned int length;
};

struct attribute {
    string name;
    string contents;
    range rangeValue;
};

class XMLRead {
    public:
        XMLRead();
        ~XMLRead();
        void Load(string xmlData);

        string GetFieldContents(string fieldName);
        string GetRawXML();

        void MoveAttributesIntoChildren(string fieldName);
    private:
        string _xmlData;
        string _MakeTag(string name, bool open);
        string _GetStringBetween(string data, string startDelim, string endDelim);
        bool _VerifyXML(string data);
        bool _HasAttributes(string fieldName);
        vector<attribute> _GetAttributes(string fieldName);
};

