#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include "XMLGen.h"
#include "XMLRead.h"
#include <curl/curl.h>
#include <algorithm>
#include <vector>

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

        string Authenticate(string username, string password, int hours, string udata);
        string AddRecord(vector<string> fields, vector<string> fieldContents, bool disprec, bool ignoreError, string ticket, string apptoken, string udata, bool msInUTC, string dbid);
        string EditRecord(int rid, int updateID, string fields[], bool disprec, bool ignoreError, string ticket, string apptoken, string udata, bool msInUTC);
        string GetSchema(string ticket, string apptoken, string udata, string dbid);
        string GetDBInfo(string ticket, string apptoken, string udata, string dbid);
        string AddField(bool addToForms, string apptoken, string label, string mode, string ticket, string type, string udata, string dbid);
        string DeleteField(int fid, string ticket, string apptoken, string udata, string dbid);
        string SetFieldProperties(string properties[], int fid, string ticket, string apptoken, string udata);
        string CreateTable(string tname, string pnoun, string ticket, string apptoken, string udata, string dbid);
        int GetNumRecords(string ticket, string apptoken, string udata, string dbid);
        string GetRecordInfo(int rid, string ticket, string apptoken, string udata, string dbid);
        string DeleteRecord(int rid, string ticket, string apptoken, string udata, string dbid);
        string PurgeRecords(string query, int qid, string qname, string ticket, string apptoken, string udata, string dbid);
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
