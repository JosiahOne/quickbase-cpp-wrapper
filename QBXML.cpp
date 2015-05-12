/*
* Copyright Notice : Copyright 2015, Josiah Bruner, All Rights Reserved.
*/
#include "QBXML.h"

QBXML::QBXML(XMLRead *read) {
    if (read) {
        _xmlData = read;
    }
    else {
        _xmlData = new XMLRead;
        _xmlData->Load("");
    }
}

QBXML::~QBXML() {
}

void QBXML::Dealloc() {
    if (_xmlData) {
        delete _xmlData;
    }

    delete this;
}

XMLResult QBXML::GetAction() {
    return _GetResult("action");
}

XMLResult QBXML::GetErrCode() {
    return _GetResult("errcode");
}

XMLResult QBXML::GetErrText() {
    return _GetResult("errtext");
}

XMLResult QBXML::GetTicket() {
    return _GetResult("ticket");
}

XMLResult QBXML::GetUserID() {
    return _GetResult("userid");
}

XMLResult QBXML::GetUData() {
    return _GetResult("udata");
}

XMLResult QBXML::GetRID() {
    return _GetResult("rid");
}

XMLResult QBXML::GetUpdateID() {
    return _GetResult("update_id");
}

XMLResult QBXML::GetFID() {
    return _GetResult("fid");
}

XMLResult QBXML::GetLabel() {
    return _GetResult("label");
}

XMLResult QBXML::GetNumFieldsChanged() {
    return _GetResult("num_fields_changed");
}

XMLResult QBXML::GetNewDBID() {
    return _GetResult("newdbid");
}

XMLResult QBXML::GetRecord() {
    // Unfortunately, due to poor API design, <record> tags may or may not possess an rid attribute.
    // Since these attributes are much harder to parse, we instead move the attribute into an <rid> child.

    _xmlData->MoveAttributesIntoChildren("record");
    return _GetResult("record");
}

XMLResult QBXML::GetNumFields() {
    return _GetResult("num_fields");
}

XMLResult QBXML::GetValue() {
    return _GetResult("value");
}

vector<QBXML> QBXML::GetFields() {
    vector<QBXML> results = { };
    string remainingData = _xmlData->GetRawXML();

    bool flag = true;
    while (flag) {
        XMLRead *xmlData = new XMLRead;
        xmlData->Load(remainingData);
        XMLResult aRes = _GetResult("field");
        if (aRes.valid) {
            XMLRead *reducedRead = new XMLRead;
            reducedRead->Load(aRes.text);
            QBXML newXML(reducedRead);
            results.push_back(newXML);
            delete reducedRead;
            // Strip remainingData for repeat
            remainingData = _RemoveSubstring(remainingData, aRes.text);
        }
        else {
            flag = false;
        }

        delete xmlData;
    }

    return results;
}

XMLResult QBXML::_GetResult(string type) {
    XMLResult xmlRes;
    string result = _xmlData->GetFieldContents(type);
    if (result != "ERROR") {
        xmlRes.valid = true;
    }
    else {
        xmlRes.valid = false;
    }
    xmlRes.type = type;
    xmlRes.text = result;

    return xmlRes;
}

// Removes first occurance of substring.
string QBXML::_RemoveSubstring(string mainString, string subString) {
    string t = mainString;
    std::string s = subString;

    std::string::size_type i = t.find(s);

    if (i != std::string::npos) {
        t.erase(i, s.length());
    }

    return mainString;
}