/*
* Copyright Notice : Copyright 2015, Josiah Bruner, All Rights Reserved.
*/
#include <string>
#include <iostream>
#include <fstream>

class XMLGen {
    public:
        XMLGen();
        ~XMLGen();
        void SetLocation(std::string location);
        void SetQBAction(std::string QBActName);
        void AddParent(std::string name);
        void CloseParent(std::string name);
        void AddField(std::string name, std::string data);
        void AddFieldWithParam(std::string name, std::string data, std::string pName, std::string pData);
        
        // Returns "ERROR" when something fails.
        // Returns file name otherwise.
        std::string WriteOut();
        void aReset();
    private:
        std::string _location;
        std::string _QBAction;
        std::string _outStream;
        void _ResetAll();
};