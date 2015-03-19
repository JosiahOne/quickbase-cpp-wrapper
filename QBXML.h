#pragma once
#include "XMLRead.h"
#include <string>
#include <iostream>

struct XMLResult {
    bool valid;
    string text;
    string type;
};

class QBXML
{
    public:
        QBXML(XMLRead *read);
        ~QBXML();
        void Dealloc();                  /*   Valid For:   */
        XMLResult GetAction();           // API_Authenticate, API_AddRecord, API_AddField, API_EditRecord.
        XMLResult GetErrCode();          // API_Authenticate, API_AddRecord, API_AddField, API_EditRecord.
        XMLResult GetErrText();          // API_Authenticate, API_AddRecord, API_AddField, API_EditRecord.
        XMLResult GetUData();            // API_Authenticate, API_AddRecord, API_AddField, API_EditRecord.
        XMLResult GetUserID();           // API_Authenticate, API_AddField.
        XMLResult GetTicket();           // API_Authenticate.
        XMLResult GetRID();              // API_AddRecord, API_EditRecord.
        XMLResult GetUpdateID();         // API_AddRecord, API_EditRecord.
        XMLResult GetFID();              // API_AddField.
        XMLResult GetLabel();            // API_AddField.
        XMLResult GetNumFieldsChanged(); // API_EditRecord.
    private:
        XMLRead *_xmlData;
        XMLResult _GetResult(string);
};

