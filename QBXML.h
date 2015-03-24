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
        void Dealloc();
        // API_Authenticate, API_AddRecord, API_AddField, API_EditRecord.
        XMLResult GetAction();           
        // API_Authenticate, API_AddRecord, API_AddField, API_EditRecord.
        XMLResult GetErrCode();          
        // API_Authenticate, API_AddRecord, API_AddField, API_EditRecord.
        XMLResult GetErrText();          
        // API_Authenticate, API_AddRecord, API_AddField, API_EditRecord.
        XMLResult GetUData();            
        // API_Authenticate, API_AddField.
        XMLResult GetUserID();
        // API_Authenticate.     
        XMLResult GetTicket();        
        // API_AddRecord, API_EditRecord.   
        XMLResult GetRID();          
        // API_AddRecord, API_EditRecord.    
        XMLResult GetUpdateID();         
        // API_AddField.
        XMLResult GetFID();             
        // API_AddField.
        XMLResult GetLabel();            
        // API_EditRecord.
        XMLResult GetNumFieldsChanged(); 
        // API_CreateTable
        XMLResult GetNewDBID();          
    private:
        XMLRead *_xmlData;
        XMLResult _GetResult(string);
};

