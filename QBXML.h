/*
* Copyright Notice : Copyright 2015, Josiah Bruner, All Rights Reserved.
*/
#include "XMLRead.h"
#include <vector>

struct XMLResult {
    bool valid;
    std::string text;
    std::string type;
};

class QBXML
{
    public:
        QBXML(XMLRead *read);
        ~QBXML();
        void Dealloc();
        // API_Authenticate, API_AddRecord, API_AddField, API_EditRecord, API_DoQuery.
        XMLResult GetAction();           
        // API_Authenticate, API_AddRecord, API_AddField, API_EditRecord, API_DoQuery.
        XMLResult GetErrCode();          
        // API_Authenticate, API_AddRecord, API_AddField, API_EditRecord, API_DoQuery.
        XMLResult GetErrText();          
        // API_Authenticate, API_AddRecord, API_AddField, API_EditRecord, API_DoQuery.
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
        // API_CreateTable.
        XMLResult GetNewDBID();
        // API_DoQuery.    
        XMLResult GetRecord();
        // API_GetRecordInfo.
        XMLResult GetNumFields();
        // API_GetRecordInfo.
        XMLResult GetValue();
        // API_GetAncestorInfo
        XMLResult GetAncestorAppId();
        // API_GetAncestorInfo
        XMLResult GetOldEstancestorAppId();
        // API_UserRoles
        XMLResult GetUsers();

        std::vector<QBXML> GetFields();

    private:
        XMLRead *_xmlData;
        XMLResult _GetResult(std::string);
        std::string _RemoveSubstring(std::string mainString, std::string subString);
};

