#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class XMLRead {
    public:
        XMLRead();
        ~XMLRead();
        void Load(string xmlData);
        string GetFieldContents(string fieldName);
    private:
        string _xmlData;
        string _MakeTag(string name, bool open);
        string _GetStringBetween(string data, string startDelim, string endDelim);
        bool _VerifyXML(string data);
};

