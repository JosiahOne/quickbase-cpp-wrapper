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