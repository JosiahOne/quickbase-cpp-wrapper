#include "QBWrapper.h"


using namespace QBWrapper;

QBWrapper() {

}

~QBWrapper() {

}

void SetAppLocation(string location) {
    _appLocation = location;
}

string Authenticate(string username, string password, int hours, string udata) {
    XMLGen *gen = new XMLGen;
    SetStandardXMLData(gen);
    gen->SetLocation(_appLocation + "/db/main");
    gen->AddParent("qbapi");
    gen->AddField("username", username);
    gen->AddField("password", password);
    gen->AddField("hours", hours);
    gen->AddField("udata", udata);
    gen->CloseParent("qbapi");
    gen->WriteOut();
}

string AddRecord(string fields[], bool disprec, bool ignoreError, string ticket, string apptoken, string udata, bool msInUTC) {

}

string EditRecord(int rid, int updateID, string fields[], bool disprec, bool ignoreError, string ticket, string apptoken, string udata, bool msInUTC) {

}

string GetSchema(string ticket, string apptoken, string udata) {

}

string GetDBInfo(string ticket, string apptoken, string udata) {

}

string AddField(bool addToForms, string apptoken, string label, string mode, string ticket, string type, string udata) {

}

string DeleteField(int fid, string ticket, string apptoken, string udata) {

}

string SetFieldProperties(string properties[], int fid, string ticket, string apptoken, string udata) {

}

string CreateTable(string tname, string pnoun, string ticket, string apptoken, string udata) {

}

int GetNumRecords(string ticket, string apptoken, string udata) {

}

string GetRecordInfo(int rid, string ticket, string apptoken, string udata) {

}

string DeleteRecord(int rid, string ticket, string apptoken, string udata) {

}

string PurgeRecords(string query, int qid, string qname, string ticket, string apptoken, string udata) {

}

bool _PostWithFile(string file) {
    // Convert file to stream.

    ifstream file("outputDataStream.xml");

    if (file) {
        stringstream buffer;
        buffer << file.rdbuf();

        file.close();
        const auto str = buffer.str();
        return (send(00, str.data(), str.size(), NULL) >= str.size());
    }
    return false;
}