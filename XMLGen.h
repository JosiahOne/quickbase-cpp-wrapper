#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class XMLGen {
    public:
        XMLGen();
        ~XMLGen();
        void SetLocation(string location);
        void SetQBAction(string QBActName);
        void AddParent(string name);
        void CloseParent(string name);
        void AddField(string name, string data);
        void AddFieldWithParam(string name, string data, string pName, string pData);
        bool WriteOut();
        void aReset();
    private:
        string _location;
        string _QBAction;
        string _outStream;
        void _ResetAll();
};