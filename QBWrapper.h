#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <sys/types.h>
#include <sys/socket.h>
#include "XMLGen.h"

using namespace std;

class QBWrapper {
    public:
        QBWrapper();
        ~QBWrapper();
        void SetAppLocation(string location); // Required.
        void SetAppToken(string token); // Optional

        string Authenticate(string username, string password, int hours, string udata);
        string AddRecord(string fields[], bool disprec, bool ignoreError, string ticket, string apptoken, string udata, bool msInUTC);
        string EditRecord(int rid, int updateID, string fields[], bool disprec, bool ignoreError, string ticket, string apptoken, string udata, bool msInUTC);
        string GetSchema(string ticket, string apptoken, string udata);
        string GetDBInfo(string ticket, string apptoken, string udata);
        string AddField(bool addToForms, string apptoken, string label, string mode, string ticket, string type, string udata);
        string DeleteField(int fid, string ticket, string apptoken, string udata);
        string SetFieldProperties(string properties[], int fid, string ticket, string apptoken, string udata);
        string CreateTable(string tname, string pnoun, string ticket, string apptoken, string udata);
        int GetNumRecords(string ticket, string apptoken, string udata);
        string GetRecordInfo(int rid, string ticket, string apptoken, string udata);
        string DeleteRecord(int rid, string ticket, string apptoken, string udata);
        string PurgeRecords(string query, int qid, string qname, string ticket, string apptoken, string udata);
    private:
        string _apptoken;
        string _ticket;
        string _appLocation;
        bool _PostWithFile(string file);
};
