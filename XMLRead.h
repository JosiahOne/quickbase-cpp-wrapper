/*
 * Copyright Notice : Copyright 2015, Josiah Bruner, All Rights Reserved.
 */
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cctype>

struct attribute {
    std::string name;
    std::string contents;
};

class XMLRead {
    public:
        XMLRead();
        ~XMLRead();
        void Load(std::string xmlData);

        std::string GetFieldContents(std::string fieldName);
        std::string GetRawXML();

        void MoveAttributesIntoChildren(std::string fieldName);
    private:
        std::string _xmlData;
        std::string _MakeTag(std::string name, bool open);
        std::string _GetStringBetween(std::string data, std::string startDelim, std::string endDelim);
        bool _VerifyXML(std::string data);
        bool _HasAttributes(std::string fieldName);
        std::vector<attribute> _GetAttributes(std::string fieldName);
        bool _CreateChild(std::string name, std::string content, std::string parentTagName);
        void _DeleteAttributes(std::string fieldName);
};

