#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include "XMLGen.h"
#include <curl/curl.h>
#include <algorithm>
#include <vector>
#include "QBXML.h"

using namespace std;

void init_string(struct curlString *s);
size_t _WriteStream(void *ptr, size_t size, size_t nmemb, struct curlString *s);
struct curlString {
    char *ptr;
    size_t len;
};

class QBWrapper {
    public:
        QBWrapper();
        ~QBWrapper();
        void SetAppLocation(string location); // Required.
        void SetAppToken(string token); // Optional

        QBXML Authenticate(string username, string password, int hours, string udata);
        QBXML AddRecord(vector<string> fields, vector<string> fieldContents, bool disprec, bool ignoreError, string ticket, string apptoken, string udata, bool msInUTC, string dbid);
        QBXML EditRecord(int rid, int updateID, vector<string> fields, vector<string> contents, bool disprec, bool ignoreError, string ticket, string apptoken, string udata, bool msInUTC, string dbid);
        QBXML GetSchema(string ticket, string apptoken, string udata, string dbid);
        QBXML GetDBInfo(string ticket, string apptoken, string udata, string dbid);
        QBXML AddField(bool addToForms, string apptoken, string label, string mode, string ticket, string type, string udata, string dbid);
        QBXML DeleteField(int fid, string ticket, string apptoken, string udata, string dbid);
        QBXML SetFieldProperties(vector<string>propertyParams, vector<string>propertyValues, int fid, string ticket, string apptoken, string udata, string dbid);
        QBXML CreateTable(string tname, string pnoun, string ticket, string apptoken, string udata, string dbid);
        QBXML GetNumRecords(string ticket, string apptoken, string udata, string dbid);
        QBXML GetRecordInfo(int rid, string ticket, string apptoken, string udata, string dbid);
        QBXML DeleteRecord(int rid, string ticket, string apptoken, string udata, string dbid);
        QBXML PurgeRecords(string query, int qid, string qname, string ticket, string apptoken, string udata, string dbid);
    private:
        string _apptoken;
        string _ticket;
        string _appLocation;
        string _XMLDataPrelim(string apiAction, string dbid, vector<string> params, vector<string> values, vector<string> altParams = vector<string>(), vector<string> altValues = vector<string>());
        string _PostWithFile(string file, string apiName, string dbid);
        string _IntToString(int anInt);
        string _BoolToString(bool aBool);
        int _CURLSend(string inputStream);
        string _GetStringBetween(string data, string startDelim, string endDelim);
};
