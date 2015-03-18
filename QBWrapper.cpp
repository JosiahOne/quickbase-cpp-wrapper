#include "QBWrapper.h"

QBWrapper::QBWrapper() {

}

QBWrapper::~QBWrapper() {

}

void QBWrapper::SetAppLocation(string location) {
    _appLocation = location;
}

/* Returns the ticket if the username and password is valid.
   Returns "AUTHERROR" if there was an error (i.e. <errcode> > 0)
 */
string QBWrapper::Authenticate(string username, string password, int hours, string udata) {
    XMLGen *gen = new XMLGen;
    gen->SetLocation(_appLocation + "/db/main");
    gen->SetQBAction("API_Authenticate");
    gen->AddParent("qdbapi");
    gen->AddField("username", username);
    gen->AddField("password", password);
    gen->AddField("hours", _IntToString(hours));
    gen->AddField("udata", udata);
    gen->CloseParent("qdbapi");
    gen->WriteOut();

    string result = _PostWithFile("outputDataStream.xml", "API_Authenticate", "main");
    if (result != "" && result != "ERROR") {
        // We need to parse this XML data now.
        XMLRead *xmlParser = new XMLRead;
        xmlParser->Load(result);
        string ticket = xmlParser->GetFieldContents("ticket");
        if (ticket != "" && ticket != "ERROR") {
            return ticket;
        }
    }
    return "AUTHERROR";
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

string QBWrapper::_PostWithFile(string file, string apiName, string dbid) {
    // Convert file to stream.

    ifstream aFile(file.c_str());
    struct curlString returnData;

    if (aFile) {
        stringstream buffer;
        buffer << aFile.rdbuf();

        aFile.close();
        string str = buffer.str();
        str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
        const char *str2 = str.c_str();
        if (!str2) {
            cout << "ERROR!";
            abort();
        }
        char *str3 = _strdup(str2);
        cout << str3;
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

            list = curl_slist_append(list, "Content-Type: application/xml");

            curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
            curl_easy_setopt(curl, CURLOPT_URL, otherData);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, FALSE);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, FALSE);
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, 135L);
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

        curl_global_cleanup();
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