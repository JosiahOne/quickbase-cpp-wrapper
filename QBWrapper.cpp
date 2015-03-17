#include "QBWrapper.h"

QBWrapper::QBWrapper() {

}

QBWrapper::~QBWrapper() {

}

void QBWrapper::SetAppLocation(string location) {
    _appLocation = location;
}

string QBWrapper::Authenticate(string username, string password, int hours, string udata) {
    XMLGen *gen = new XMLGen;
    gen->SetLocation(_appLocation + "/db/main");
    gen->SetQBAction("API_Authenticate");
    gen->AddParent("qbapi");
    gen->AddField("username", username);
    gen->AddField("password", password);
    gen->AddField("hours", _IntToString(hours));
    gen->AddField("udata", udata);
    gen->CloseParent("qbapi");
    gen->WriteOut();

    return "";
}

string QBWrapper::AddRecord(string fields[], bool disprec, bool ignoreError, string ticket, string apptoken, string udata, bool msInUTC) {

    return "";
}

string QBWrapper::EditRecord(int rid, int updateID, string fields[], bool disprec, bool ignoreError, string ticket, string apptoken, string udata, bool msInUTC) {
    return "";
}

string QBWrapper::GetSchema(string ticket, string apptoken, string udata) {
    return "";
}

string QBWrapper::GetDBInfo(string ticket, string apptoken, string udata) {
    return "";
}

string QBWrapper::AddField(bool addToForms, string apptoken, string label, string mode, string ticket, string type, string udata) {
    return "";
}

string QBWrapper::DeleteField(int fid, string ticket, string apptoken, string udata) {
    return "";
}

string QBWrapper::SetFieldProperties(string properties[], int fid, string ticket, string apptoken, string udata) {
    return "";
}

string QBWrapper::CreateTable(string tname, string pnoun, string ticket, string apptoken, string udata) {
    return "";
}

int QBWrapper::GetNumRecords(string ticket, string apptoken, string udata) {
    return 0;
}

string QBWrapper::GetRecordInfo(int rid, string ticket, string apptoken, string udata) {
    return "";
}

string QBWrapper::DeleteRecord(int rid, string ticket, string apptoken, string udata) {
    return "";
}

string QBWrapper::PurgeRecords(string query, int qid, string qname, string ticket, string apptoken, string udata) {
    return "";
}

bool QBWrapper::_PostWithFile(string file) {
    // Convert file to stream.

    ifstream aFile(file.c_str());

    if (aFile) {
        stringstream buffer;
        buffer << aFile.rdbuf();

        aFile.close();
        const string str = buffer.str();
        return (send(00, str.data(), str.size(), NULL) >= str.size());
    }
    return false;
}

string QBWrapper::_IntToString(int anInt) {
    stringstream ss;
    ss << anInt;
    string aString = ss.str();
    return aString;
}