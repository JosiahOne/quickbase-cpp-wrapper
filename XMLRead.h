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
};

