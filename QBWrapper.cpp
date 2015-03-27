#include "QBWrapper.h"

QBWrapper::QBWrapper() {

}

QBWrapper::~QBWrapper() {

}

void QBWrapper::SetAppLocation(string location) {
    _appLocation = location;
}

void fix_utf8_string(std::string& str)
{
    cout << str;
    std::string temp;
    utf8::replace_invalid(str.begin(), str.end(), back_inserter(temp));
    str = temp;
    cout << endl << str;
}

bool valid_utf8_file(const char* file_name)
{
    ifstream ifs(file_name);
    if (!ifs)
        return false; // even better, throw here

    istreambuf_iterator<char> it(ifs.rdbuf());
    istreambuf_iterator<char> eos;

    return utf8::is_valid(it, eos);
}

QBXML QBWrapper::Authenticate(string username, string password, int hours, string udata) {
    vector<string> paramVector = { "username", "password", "hours", "udata" };
    vector<string> valueVector = { username, password, _IntToString(hours), udata };
    string result = _XMLDataPrelim("API_Authenticate", "main", paramVector, valueVector);
    XMLRead *xmlParser = new XMLRead;

    if (result != "" && result != "ERROR") {
        // We need to parse this XML data now.
        xmlParser->Load(result);
    }
    return QBXML(xmlParser);
}

QBXML QBWrapper::AddRecord(vector<string> fields, vector<string> fieldContents, bool disprec, bool ignoreError, string ticket, string apptoken, string udata, bool msInUTC, string dbid) {
    if (fields.size() != fieldContents.size()) {
        return NULL;
    }
    
    vector<string> paramVector = { "ticket", "apptoken", "udata" };
    vector<string> valueVector = { ticket, apptoken, udata };
    vector<string> altParams = { "", "", "" };
    vector<string> altValues = { "", "", "" };
    vector<string> optionalParams = { "disprec, ignoreError, msInUTC" };
    vector<bool> optionalValues = { disprec, ignoreError, msInUTC };

    // Optional Parameters
    for (int i = 0; i < 3; i++) {
        if (optionalValues[i] == true) {
            paramVector.push_back(optionalParams[i]);
            valueVector.push_back(_BoolToString(optionalValues[i]));
        }
    }

    for (unsigned int i = 0; i < fields.size(); i++) {
        altParams.push_back("fid");
        altValues.push_back(fields[i]);
        paramVector.push_back("field");
        valueVector.push_back(fieldContents[i]);
    }

    string result = _XMLDataPrelim("API_AddRecord", dbid, paramVector, valueVector, altParams, altValues);
    XMLRead *xmlParser = new XMLRead;

    if (result != "" && result != "ERROR") {
        // We need to parse this XML data now.
        xmlParser->Load(result);
    }
    return QBXML(xmlParser);
}

QBXML QBWrapper::EditRecord(int rid, int updateID, vector<string> fields, vector<string> contents, bool disprec, bool ignoreError, string ticket, string apptoken, string udata, bool msInUTC, string dbid) {
    if (fields.size() != contents.size()) {
        return NULL;
    }

    vector<string> paramVector = { "rid", "update_id", "disprec", "fform", "ignoreError", "ticket", "apptoken", "udata", "msInUTC" };
    vector<string> valueVector = { _IntToString(rid), _IntToString(updateID), _BoolToString(disprec), _BoolToString(ignoreError), ticket, apptoken, udata, _BoolToString(msInUTC) };
    vector<string> altParams = { "", "", "", "", "", "", "", "", "" };
    vector<string> altValues = { "", "", "", "", "", "", "", "", "" };

    for (unsigned int i = 0; i < fields.size(); i++) {
        altParams.push_back("fid");
        altValues.push_back(fields[i]);
        paramVector.push_back("field");
        valueVector.push_back(contents[i]);
    }

    string result = _XMLDataPrelim("API_EditRecord", dbid, paramVector, valueVector, altParams, altValues);
    XMLRead *xmlParser = new XMLRead;

    if (result != "" && result != "ERROR") {
        // We need to parse this XML data now.
        xmlParser->Load(result);
    }
    return QBXML(xmlParser);
}

QBXML QBWrapper::GetSchema(string ticket, string apptoken, string udata, string dbid) {
    vector<string> paramVector = { "ticket", "apptoken", "udata" };
    vector<string> valueVector = { ticket, apptoken, udata };

    string result = _XMLDataPrelim("API_GetSchema", dbid, paramVector, valueVector);
    XMLRead *xmlParser = new XMLRead;
    xmlParser->Load(result);
    if (result != "" && result != "ERROR") {
        // We need to parse this XML data now.
        xmlParser->Load(result);
    }
    return QBXML(xmlParser);
}

QBXML QBWrapper::GetDBInfo(string ticket, string apptoken, string udata, string dbid) {
    vector<string> paramVector = { "ticket", "apptoken", "udata" };
    vector<string> valueVector = { ticket, apptoken, udata };

    string result = _XMLDataPrelim("API_GetDBInfo", dbid, paramVector, valueVector);
    XMLRead *xmlParser = new XMLRead;
    xmlParser->Load(result);
    if (result != "" && result != "ERROR") {
        // We need to parse this XML data now.
        xmlParser->Load(result);
    }
    return QBXML(xmlParser);
}

QBXML QBWrapper::AddField(bool addToForms, string apptoken, string label, string mode, string ticket, string type, string udata, string dbid) {
    vector<string> paramVector = { "add_to_forms", "apptoken", "label", "mode", "ticket", "type", "udata" };
    vector<string> valueVector = { _BoolToString(addToForms), apptoken, label, mode, ticket, type, udata };

    string result = _XMLDataPrelim("API_AddField", dbid, paramVector, valueVector);
    XMLRead *xmlParser = new XMLRead;
    xmlParser->Load(result);
    if (result != "" && result != "ERROR") {
        // We need to parse this XML data now.
        xmlParser->Load(result);
    }
    return QBXML(xmlParser);
}

QBXML QBWrapper::DeleteField(int fid, string ticket, string apptoken, string udata, string dbid) {
    vector<string> paramVector = { "fid", "ticket", "apptoken", "udata" };
    vector<string> valueVector = { _IntToString(fid), ticket, apptoken, udata };

    string result = _XMLDataPrelim("API_DeleteField", dbid, paramVector, valueVector);
    XMLRead *xmlParser = new XMLRead;
    xmlParser->Load(result);
    if (result != "" && result != "ERROR") {
        // We need to parse this XML data now.
        xmlParser->Load(result);
    }
    return QBXML(xmlParser);
}

QBXML QBWrapper::SetFieldProperties(vector<string>propertyParams, vector<string>propertyValues, int fid, string ticket, string apptoken, string udata, string dbid) {
    if (propertyParams.size() != propertyValues.size()) {
        return NULL;
    }
    
    vector<string> paramVector = { "fid", "ticket", "apptoken", "udata" };
    vector<string> valueVector = { _IntToString(fid), ticket, apptoken, udata };

    for (unsigned int i = 0; i < propertyParams.size(); i++) {
        paramVector.push_back(propertyParams[i]);
        valueVector.push_back(propertyValues[i]);
    }

    string result = _XMLDataPrelim("API_SetFieldProperties", dbid, paramVector, valueVector);
    XMLRead *xmlParser = new XMLRead;
    xmlParser->Load(result);
    if (result != "" && result != "ERROR") {
        // We need to parse this XML data now.
        xmlParser->Load(result);
    }
    return QBXML(xmlParser);
}

QBXML QBWrapper::CreateTable(string tname, string pnoun, string ticket, string apptoken, string udata, string dbid) {
    vector<string> paramVector = { "tname", "pnoun", "ticket", "apptoken", "udata" };
    vector<string> valueVector = { tname, pnoun, ticket, apptoken, udata };

    string result = _XMLDataPrelim("API_CreateTable", dbid, paramVector, valueVector);
    XMLRead *xmlParser = new XMLRead;
    xmlParser->Load(result);
    if (result != "" && result != "ERROR") {
        // We need to parse this XML data now.
        xmlParser->Load(result);
    }
    return QBXML(xmlParser);
}

/* Returns the number of records in a table.
   Returns -1 if there was an error
 */
QBXML QBWrapper::GetNumRecords(string ticket, string apptoken, string udata, string dbid) {
    vector<string> paramVector = { "ticket", "apptoken", "udata" };
    vector<string> valueVector = { ticket, apptoken, udata };
    XMLRead *xmlParser = new XMLRead;
    string result = _XMLDataPrelim("API_GetNumRecords", dbid, paramVector, valueVector);
    if (result != "" && result != "ERROR") {
        // We need to parse this XML data now.
        xmlParser->Load(result);
    }

    return QBXML(xmlParser);

}

QBXML QBWrapper::GetRecordInfo(int rid, string ticket, string apptoken, string udata, string dbid) {
    vector<string> paramVector = { "rid", "ticket", "apptoken", "udata" };
    vector<string> valueVector = { _IntToString(rid), ticket, apptoken, udata };

    string result = _XMLDataPrelim("API_GetRecordInfo", dbid, paramVector, valueVector);
    XMLRead *xmlParser = new XMLRead;
    xmlParser->Load(result);
    if (result != "" && result != "ERROR") {
        // We need to parse this XML data now.
        xmlParser->Load(result);
    }
    return QBXML(xmlParser);
}

QBXML QBWrapper::DeleteRecord(int rid, string ticket, string apptoken, string udata, string dbid) {
    vector<string> paramVector = { "rid", "ticket", "apptoken", "udata" };
    vector<string> valueVector = { _IntToString(rid), ticket, apptoken, udata };

    string result = _XMLDataPrelim("API_DeleteRecord", dbid, paramVector, valueVector);
    XMLRead *xmlParser = new XMLRead;
    xmlParser->Load(result);
    if (result != "" && result != "ERROR") {
        // We need to parse this XML data now.
        xmlParser->Load(result);
    }
    return QBXML(xmlParser);
}

QBXML QBWrapper::PurgeRecords(string query, int qid, string qname, string ticket, string apptoken, string udata, string dbid) {
    // According to the Quickbase API, attaching an empty query causes every record in a table to be deleted.
    // You must supply a non-empty query to delete specific things. This is entirely stupid, and so we require a specific "ALL"
    // param to delete everything, otherwise we leave without purging.
    if (query == "" && qid == NULL && qname == "") {
        return NULL;
    }

    vector<string> paramVector(4);
    vector<string> valueVector(4);

    if (query == "ALL") {
        paramVector[0] = "query";
        valueVector[0] = "";
    }
    else if (query != "") {
        paramVector[0] = "query";
        valueVector[0] = query;
    }
    else if (qid != NULL && qid >= 0) {
        paramVector[0] = "qid";
        valueVector[0] = qid;
    }
    else if (qname != "") {
        paramVector[0] = "qname";
        valueVector[0] = qname;
    }
    else {
        return NULL;
    }

    paramVector[1] = "ticket";
    valueVector[1] = ticket;
    paramVector[2] = "apptoken";
    valueVector[2] = apptoken;
    paramVector[3] = "udata";
    valueVector[3] = udata;
    
    string result = _XMLDataPrelim("API_PurgeRecords", dbid, paramVector, valueVector);
    XMLRead *xmlParser = new XMLRead;
    xmlParser->Load(result);
    if (result != "" && result != "ERROR") {
        // We need to parse this XML data now.
        xmlParser->Load(result);
    }
    return QBXML(xmlParser);
}

void init_string(struct curlString *s) {
    s->len = 0;
    s->ptr = (char*)malloc(s->len + 1);
    if (s->ptr == NULL) {
        fprintf(stderr, "malloc() failed\n");
        exit(EXIT_FAILURE);
    }
    s->ptr[0] = '\0';
}

size_t _WriteStream(void *ptr, size_t size, size_t nmemb, struct curlString *s)
{
    size_t new_len = s->len + size*nmemb;
    s->ptr = (char*)realloc(s->ptr, new_len + 1);
    if (s->ptr == NULL) {
        fprintf(stderr, "realloc() failed\n");
        exit(EXIT_FAILURE);
    }
    memcpy(s->ptr + s->len, ptr, size*nmemb);
    s->ptr[new_len] = '\0';
    s->len = new_len;
    size_t returnValue = size*nmemb;
    return returnValue;
}

string QBWrapper::_XMLDataPrelim(string apiAction, string dbid, vector<string> params, vector<string> values, vector<string> altParams, vector<string> altValues) {
    if (params.size() != values.size() || altParams.size() != altValues.size()) {
        cout << "(alt)params and (alt)values are not of equal size";
        abort();
    }
    XMLGen *gen = new XMLGen;
    gen->SetLocation(_appLocation + "/db/" + dbid);
    gen->SetQBAction(apiAction);
    gen->AddParent("qdbapi");

    if (altParams.size() == params.size()) {
        for (unsigned int i = 0; i < altParams.size(); i++) {
            if (altParams[i] != "" && values[i] != "") {
                gen->AddFieldWithParam(params[i], values[i], altParams[i], altValues[i]);
            }
            else if (values[i] != "") {
                gen->AddField(params[i], values[i]);
            }
        }
    }
    else {
        for (unsigned int i = 0; i < params.size(); i++) {
            gen->AddField(params[i], values[i]);
        }
    }
    gen->CloseParent("qdbapi");
    gen->WriteOut();
    delete gen;

    string result = _PostWithFile("outputDataStream.xml", apiAction, dbid);
    return result;
}

string QBWrapper::_PostWithFile(string file, string apiName, string dbid) {
    // Convert file to stream.
    cout << "Valid? " << valid_utf8_file(file.c_str());
    ifstream aFile(file.c_str());
    struct curlString returnData;

    if (aFile) {
        stringstream buffer;
        buffer << aFile.rdbuf();

        aFile.close();
        string str = buffer.str();
        //string str = "<qdbapi><ticket>7_bjtq8h4ix_b2djnw_erbr_a_fz3cn4dkurq3mcze8dqbbremmc8cgws8jcbjfg3nnbmxtdaqdt78ezn</ticket><field fid='9'>1</field></qdbapi>";
        str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
        fix_utf8_string(str);
        const char *str2 = str.c_str();
        if (!str2) {
            cout << "ERROR!";
            abort();
        }
        char *str3 = _strdup(str2);
        cout << endl << "\n===================\n" << str3 << "\n===================\n";
        cout << "API NAME: " << apiName << "\n DBID: " << dbid << endl;
        CURL *curl;
        CURLcode res;
        curl_slist *list = NULL;
        char* curlData = new char[256];
        size_t (*writeStream) (void*, size_t, size_t, struct curlString*);
        writeStream = &_WriteStream;
        curl = curl_easy_init();
        if (curl) {
            init_string(&returnData);
            string data = _appLocation + "/db/" + dbid.c_str() + "?act=" + apiName.c_str();
            const char *otherData = data.c_str();

            cout << "DATA: " << otherData << endl;

            list = curl_slist_append(list, "Content-Type: application/xml");
            string lengthString = string("Content-Length:" + _SizetToString(strlen(str3)));
            cout << "STUIFF" <<  strlen(str3);
            //list = curl_slist_append(list, lengthString.c_str());

            curl_easy_setopt(curl, CURLOPT_VERBOSE, TRUE);
            curl_easy_setopt(curl, CURLOPT_URL, otherData);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, FALSE);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, FALSE);
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, str3);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeStream);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &returnData);
            curl_easy_setopt(curl, CURLOPT_POST, 1L);

            res = curl_easy_perform(curl);
            if (res != CURLE_OK) {
                fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
            }
            curl_easy_cleanup(curl);
        }

        curl_slist_free_all(list);
    }
    if (returnData.ptr) {
        cout << string(returnData.ptr);
        return string(returnData.ptr);
    }
    else {
        return "ERROR";
    }
}

string QBWrapper::_IntToString(int anInt) {
    stringstream ss;
    ss << anInt;
    string aString = ss.str();
    return aString;
}

string QBWrapper::_BoolToString(bool aBool) {
    if (aBool) {
        return "1";
    }
    else {
        return "0";
    }
}

string QBWrapper::_SizetToString(size_t aSizeT) {
    stringstream ss;

    ss << aSizeT;
    return ss.str();
}

string QBWrapper::_GetStringBetween(string data, string startDelim, string endDelim) {
    unsigned first = data.find(startDelim);
    unsigned last = data.find(endDelim);
    if (first != string::npos && last != string::npos) {
        string strNew = data.substr(first + startDelim.length(), last - first);
        return strNew;
    }
    else {
        return NULL;
    }
}