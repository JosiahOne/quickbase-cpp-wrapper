/*
 * Copyright Notice : Copyright 2015, Josiah Bruner, All Rights Reserved.
 */
#include "QBWrapper.h"

QBWrapper::QBWrapper() {

}

QBWrapper::~QBWrapper() {

}

void QBWrapper::SetAppLocation(std::string location) {
    _appLocation = location;
}

void fix_utf8_string(std::string& str)
{
    std::cout << str;
    std::string temp;
    utf8::replace_invalid(str.begin(), str.end(), back_inserter(temp));
    str = temp;
    std::cout << std::endl << str;
}

bool valid_utf8_file(const char* file_name)
{
    std::ifstream ifs(file_name);
    if (!ifs)
        return false; // even better, throw here

    std::istreambuf_iterator<char> it(ifs.rdbuf());
    std::istreambuf_iterator<char> eos;

    return utf8::is_valid(it, eos);
}

QBXML QBWrapper::Authenticate(std::string username, std::string password, int hours, std::string udata) {
    std::vector<std::string> paramVector = { "username", "password", "hours", "udata" };
    std::vector<std::string> valueVector = { username, password, _IntToString(hours), udata };
    std::string result = _XMLDataPrelim("API_Authenticate", "main", paramVector, valueVector);
    XMLRead *xmlParser = new XMLRead;

    if (result != "" && result != "ERROR") {
        // We need to parse this XML data now.
        xmlParser->Load(result);
    }

    return QBXML(xmlParser);
}

QBXML QBWrapper::AddRecord(std::vector<std::string> fields, std::vector<std::string> fieldContents, bool disprec, bool ignoreError, std::string ticket, std::string apptoken, std::string udata, bool msInUTC, std::string dbid) {
    if (fields.size() != fieldContents.size()) {
        return NULL;
    }
    
    std::vector<std::string> paramVector = { "ticket", "apptoken", "udata" };
    std::vector<std::string> valueVector = { ticket, apptoken, udata };
    std::vector<std::string> altParams = { "", "", "" };
    std::vector<std::string> altValues = { "", "", "" };

    paramData optionalData;
    optionalData.bParams = { "disprec", "ignoreError", "msInUTC" };
    optionalData.bValues = { disprec, ignoreError, msInUTC };
    _AddOptionalParams(&paramVector, &valueVector, optionalData);

    for (unsigned int i = 0; i < fields.size(); i++) {
        altParams.push_back("fid");
        altValues.push_back(fields[i]);
        paramVector.push_back("field");
        valueVector.push_back(fieldContents[i]);
    }

    std::string result = _XMLDataPrelim("API_AddRecord", dbid, paramVector, valueVector, altParams, altValues);
    XMLRead *xmlParser = new XMLRead;

    if (result != "" && result != "ERROR") {
        // We need to parse this XML data now.
        xmlParser->Load(result);
    }

    return QBXML(xmlParser);
}

QBXML QBWrapper::EditRecord(int rid, int updateID, std::vector<std::string> fields, std::vector<std::string> contents, bool disprec, bool ignoreError, std::string ticket, std::string apptoken, std::string udata, bool msInUTC, std::string dbid) {
    if (fields.size() != contents.size()) {
        return NULL;
    }

    std::vector<std::string> paramVector = { "rid", "ticket", "apptoken", "udata" };
    std::vector<std::string> valueVector = { _IntToString(rid), ticket, apptoken, udata};
    std::vector<std::string> altParams = { "", "", "", "" };
    std::vector<std::string> altValues = { "", "", "", "" };

    paramData optionalData;
    optionalData.bParams = { "disprec", "ignoreError", "msInUTC" };
    optionalData.bValues = { disprec, ignoreError, msInUTC };
    optionalData.iParams = { "update_id" };
    optionalData.iValues = { updateID };
    _AddOptionalParams(&paramVector, &valueVector, optionalData);

    for (unsigned int i = 0; i < fields.size(); i++) {
        altParams.push_back("fid");
        altValues.push_back(fields[i]);
        paramVector.push_back("field");
        valueVector.push_back(contents[i]);
    }

    std::string result = _XMLDataPrelim("API_EditRecord", dbid, paramVector, valueVector, altParams, altValues);
    XMLRead *xmlParser = new XMLRead;

    if (result != "" && result != "ERROR") {
        // We need to parse this XML data now.
        xmlParser->Load(result);
    }

    return QBXML(xmlParser);
}

QBXML QBWrapper::GetSchema(std::string ticket, std::string apptoken, std::string udata, std::string dbid) {
    std::vector<std::string> paramVector = { "ticket", "apptoken", "udata" };
    std::vector<std::string> valueVector = { ticket, apptoken, udata };

    std::string result = _XMLDataPrelim("API_GetSchema", dbid, paramVector, valueVector);
    XMLRead *xmlParser = new XMLRead;
    xmlParser->Load(result);
    if (result != "" && result != "ERROR") {
        // We need to parse this XML data now.
        xmlParser->Load(result);
    }

    delete xmlParser;
    return QBXML(xmlParser);
}

QBXML QBWrapper::GetDBInfo(std::string ticket, std::string apptoken, std::string udata, std::string dbid) {
    std::vector<std::string> paramVector = { "ticket", "apptoken", "udata" };
    std::vector<std::string> valueVector = { ticket, apptoken, udata };

    std::string result = _XMLDataPrelim("API_GetDBInfo", dbid, paramVector, valueVector);
    XMLRead *xmlParser = new XMLRead;
    xmlParser->Load(result);
    if (result != "" && result != "ERROR") {
        // We need to parse this XML data now.
        xmlParser->Load(result);
    }
    return QBXML(xmlParser);
}

QBXML QBWrapper::AddField(bool addToForms, std::string apptoken, std::string label, std::string mode, std::string ticket, std::string type, std::string udata, std::string dbid) {
    std::vector<std::string> paramVector = { "add_to_forms", "apptoken", "label", "mode", "ticket", "type", "udata" };
    std::vector<std::string> valueVector = { _BoolToString(addToForms), apptoken, label, mode, ticket, type, udata };

    paramData optionalData;
    optionalData.bParams = { "add_to_forms" };
    optionalData.bValues = { addToForms };
    _AddOptionalParams(&paramVector, &valueVector, optionalData);

    std::string result = _XMLDataPrelim("API_AddField", dbid, paramVector, valueVector);
    XMLRead *xmlParser = new XMLRead;
    xmlParser->Load(result);
    if (result != "" && result != "ERROR") {
        // We need to parse this XML data now.
        xmlParser->Load(result);
    }

    return QBXML(xmlParser);
}

QBXML QBWrapper::DeleteField(int fid, std::string ticket, std::string apptoken, std::string udata, std::string dbid) {
    std::vector<std::string> paramVector = { "fid", "ticket", "apptoken", "udata" };
    std::vector<std::string> valueVector = { _IntToString(fid), ticket, apptoken, udata };

    std::string result = _XMLDataPrelim("API_DeleteField", dbid, paramVector, valueVector);
    XMLRead *xmlParser = new XMLRead;
    xmlParser->Load(result);
    if (result != "" && result != "ERROR") {
        // We need to parse this XML data now.
        xmlParser->Load(result);
    }

    return QBXML(xmlParser);
}

QBXML QBWrapper::SetFieldProperties(std::vector<std::string>propertyParams, std::vector<std::string>propertyValues, int fid, std::string ticket, std::string apptoken, std::string udata, std::string dbid) {
    if (propertyParams.size() != propertyValues.size()) {
        return NULL;
    }
    
    std::vector<std::string> paramVector = { "fid", "ticket", "apptoken", "udata" };
    std::vector<std::string> valueVector = { _IntToString(fid), ticket, apptoken, udata };

    for (unsigned int i = 0; i < propertyParams.size(); i++) {
        paramVector.push_back(propertyParams[i]);
        valueVector.push_back(propertyValues[i]);
    }

    std::string result = _XMLDataPrelim("API_SetFieldProperties", dbid, paramVector, valueVector);
    XMLRead *xmlParser = new XMLRead;
    xmlParser->Load(result);
    if (result != "" && result != "ERROR") {
        // We need to parse this XML data now.
        xmlParser->Load(result);
    }

    return QBXML(xmlParser);
}

QBXML QBWrapper::CreateTable(std::string tname, std::string pnoun, std::string ticket, std::string apptoken, std::string udata, std::string dbid) {
    std::vector<std::string> paramVector = { "tname", "pnoun", "ticket", "apptoken", "udata" };
    std::vector<std::string> valueVector = { tname, pnoun, ticket, apptoken, udata };

    std::string result = _XMLDataPrelim("API_CreateTable", dbid, paramVector, valueVector);
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
QBXML QBWrapper::GetNumRecords(std::string ticket, std::string apptoken, std::string udata, std::string dbid) {
    std::vector<std::string> paramVector = { "ticket", "apptoken", "udata" };
    std::vector<std::string> valueVector = { ticket, apptoken, udata };
    XMLRead *xmlParser = new XMLRead;
    std::string result = _XMLDataPrelim("API_GetNumRecords", dbid, paramVector, valueVector);
    if (result != "" && result != "ERROR") {
        // We need to parse this XML data now.
        xmlParser->Load(result);
    }

    return QBXML(xmlParser);
}

QBXML QBWrapper::GetRecordInfo(int rid, std::string ticket, std::string apptoken, std::string udata, std::string dbid) {
    std::vector<std::string> paramVector = { "rid", "ticket", "apptoken", "udata" };
    std::vector<std::string> valueVector = { _IntToString(rid), ticket, apptoken, udata };

    std::string result = _XMLDataPrelim("API_GetRecordInfo", dbid, paramVector, valueVector);
    XMLRead *xmlParser = new XMLRead;
    xmlParser->Load(result);
    if (result != "" && result != "ERROR") {
        // We need to parse this XML data now.
        xmlParser->Load(result);
    }

    return QBXML(xmlParser);
}

QBXML QBWrapper::DeleteRecord(int rid, std::string ticket, std::string apptoken, std::string udata, std::string dbid) {
    std::vector<std::string> paramVector = { "rid", "ticket", "apptoken", "udata" };
    std::vector<std::string> valueVector = { _IntToString(rid), ticket, apptoken, udata };

    std::string result = _XMLDataPrelim("API_DeleteRecord", dbid, paramVector, valueVector);
    XMLRead *xmlParser = new XMLRead;
    xmlParser->Load(result);
    if (result != "" && result != "ERROR") {
        // We need to parse this XML data now.
        xmlParser->Load(result);
    }

    return QBXML(xmlParser);
}

QBXML QBWrapper::PurgeRecords(std::string query, int qid, std::string qname, std::string ticket, std::string apptoken, std::string udata, std::string dbid) {
    // According to the Quickbase API, attaching an empty query causes every record in a table to be deleted.
    // You must supply a non-empty query to delete specific things. This is entirely stupid, and so we require a specific "ALL"
    // param to delete everything, otherwise we leave without purging.
    if (query == "" && qid == NULL && qname == "") {
        return NULL;
    }

    std::vector<std::string> paramVector(4);
    std::vector<std::string> valueVector(4);

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
    
    std::string result = _XMLDataPrelim("API_PurgeRecords", dbid, paramVector, valueVector);
    XMLRead *xmlParser = new XMLRead;
    xmlParser->Load(result);
    if (result != "" && result != "ERROR") {
        // We need to parse this XML data now.
        xmlParser->Load(result);
    }

    return QBXML(xmlParser);
}

QBXML QBWrapper::DoQuery(std::string query, int qid, std::string qname, std::string clist, std::string slist, bool fmt, bool returnPercentage, std::string options, bool includeRids, std::string ticket, std::string apptoken, std::string udata, std::string dbid) {
    std::vector<std::string> paramVector = { "clist", "slist", "options", "ticket", "apptoken", "udata" };
    std::vector<std::string> valueVector = { clist, slist, options, ticket, apptoken, udata };

    paramData optionalData;
    optionalData.bParams = { "fmt", "returnpercentage", "includeRids" };
    optionalData.bValues = { fmt, returnPercentage, includeRids };
    _AddOptionalParams(&paramVector, &valueVector, optionalData);

    if (query == "ALL") {
        paramVector.push_back("query");
        valueVector.push_back("");
    }
    else if (query != "") {
        paramVector.push_back("query");
        valueVector.push_back(query);
    }
    else if (qid != NULL && qid >= 0) {
        paramVector.push_back("qid");
        valueVector.push_back(_IntToString(qid));
    }
    else if (qname != "") {
        paramVector.push_back("qname");
        valueVector.push_back(qname);
    }

    std::string result = _XMLDataPrelim("API_DoQuery", dbid, paramVector, valueVector);
    XMLRead *xmlParser = new XMLRead;
    xmlParser->Load(result);
    if (result != "" && result != "ERROR") {
        // We need to parse this XML data now.
        xmlParser->Load(result);
    }

    return QBXML(xmlParser);
}

std::string QBWrapper::GetFieldContents(int fid, std::string ticket, std::string apptoken, std::string udata, std::string dbid, int rid) {
    std::vector<std::string> paramVector = { "fid", "ticket", "apptoken", "udata", "dbid", "rid" };
    std::vector<std::string> valueVector = { _IntToString(fid), ticket, apptoken, udata, dbid, _IntToString(rid) };
    std::string result = _XMLDataPrelim("API_GetRecordInfo", dbid, paramVector, valueVector);

    XMLRead *xmlParser = new XMLRead;
    xmlParser->Load(result);

    QBXML qbxml = QBXML(xmlParser);

    std::vector<QBXML> results = qbxml.GetFields();

    for (unsigned i = 0; i < results.size(); i++) {
        if (results[i].GetFID().text == _IntToString(fid)) {
            return results[i].GetValue().text;
        }
    }

    return "ERROR";
}

QBXML QBWrapper::SignOut(std::string ticket, std::string apptoken, std::string udata, std::string dbid) {
    std::vector<std::string> paramVector = { "ticket", "apptoken", "udata" };
    std::vector<std::string> valueVector = { ticket, apptoken, udata };

    std::string result = _XMLDataPrelim("API_SignOut", dbid, paramVector, valueVector);
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

std::string QBWrapper::_XMLDataPrelim(std::string apiAction, std::string dbid, std::vector<std::string> params, std::vector<std::string> values, std::vector<std::string> altParams, std::vector<std::string> altValues) {
    if (params.size() != values.size() || altParams.size() != altValues.size()) {
        std::cout << "(alt)params and (alt)values are not of equal size";
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

    std::string result = _PostWithFile("outputDataStream.xml", apiAction, dbid);
    return result;
}

std::string QBWrapper::_PostWithFile(std::string file, std::string apiName, std::string dbid) {
    // Convert file to stream.
    std::ifstream aFile(file.c_str());
    struct curlString returnData;

    if (aFile) {
        std::stringstream buffer;
        buffer << aFile.rdbuf();

        aFile.close();
        std::string str = buffer.str();
        str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
        fix_utf8_string(str);
        const char *str2 = str.c_str();
        if (!str2) {
            std::cout << "ERROR!";
            abort();
        }
        char *str3 = _strdup(str2);
        std::cout << std::endl << "\n===================\n" << str3 << "\n===================\n";
        std::cout << "API NAME: " << apiName << "\n DBID: " << dbid << std::endl;
        CURL *curl;
        CURLcode res;
        curl_slist *list = NULL;
        char* curlData = new char[256];
        size_t (*writeStream) (void*, size_t, size_t, struct curlString*);
        writeStream = &_WriteStream;
        curl = curl_easy_init();
        if (curl) {
            init_string(&returnData);
            std::string data = _appLocation + "/db/" + dbid.c_str() + "?act=" + apiName.c_str();
            const char *otherData = data.c_str();

            std::cout << "DATA: " << otherData << std::endl;

            list = curl_slist_append(list, "Content-Type: application/xml");

            curl_easy_setopt(curl, CURLOPT_VERBOSE, FALSE);
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
        std::cout << std::string(returnData.ptr);
        return std::string(returnData.ptr);
    }
    else {
        return "ERROR";
    }
}

std::string QBWrapper::_IntToString(int anInt) {
    std::stringstream ss;
    ss << anInt;
    std::string aString = ss.str();
    return aString;
}

std::string QBWrapper::_FloatToString(float aFloat) {
    std::stringstream ss;
    ss << aFloat;
    std::string aString = ss.str();
    return aString;
}

std::string QBWrapper::_BoolToString(bool aBool) {
    if (aBool) {
        return "1";
    }
    else {
        return "0";
    }
}

std::string QBWrapper::_SizetToString(size_t aSizeT) {
    std::stringstream ss;

    ss << aSizeT;
    return ss.str();
}

std::string QBWrapper::_GetStringBetween(std::string data, std::string startDelim, std::string endDelim) {
    unsigned first = data.find(startDelim);
    unsigned last = data.find(endDelim);
    if (first != std::string::npos && last != std::string::npos) {
        std::string strNew = data.substr(first + startDelim.length(), last - first);
        return strNew;
    }
    else {
        return NULL;
    }
}

void QBWrapper::_AddOptionalParams(std::vector<std::string>*paramArray, std::vector<std::string>*valueArray, paramData data) {
    // Booleans
    for (unsigned i = 0; i < data.bParams.size(); i++) {
        if (data.bValues[i] == TRUE) {
            paramArray->push_back(data.bParams[i]);
            valueArray->push_back(_BoolToString(data.bValues[i]));
        }
    }

    // Integers
    for (unsigned i = 0; i < data.iParams.size(); i++) {
        if (data.iValues[i] > 0) {
            paramArray->push_back(data.iParams[i]);
            valueArray->push_back(_IntToString(data.iValues[i]));
        }
    }

    // Strings
    for (unsigned i = 0; i < data.sParams.size(); i++) {
        if (data.sParams[i] != "") {
            paramArray->push_back(data.sParams[i]);
            valueArray->push_back(data.sValues[i]);
        }
    }

    // Floats
    for (unsigned i = 0; i < data.fParams.size(); i++) {
        if (data.fParams[i] != "") {
            paramArray->push_back(data.fParams[i]);
            valueArray->push_back(_FloatToString(data.fValues[i]));
        }
    }
}

void QBWrapper::Cleanup() {
    remove("outputDataStream.xml");

    delete this;
}