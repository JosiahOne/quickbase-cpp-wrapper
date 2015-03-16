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
        bool WriteOut();
        void aReset();
    private:
        string _location;
        string _QBAction;
        string _outStream;
        void _ResetAll();
};