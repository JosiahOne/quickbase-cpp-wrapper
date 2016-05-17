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

XMLResult QBXML::GetAncestorAppId() {
  return _GetResult("ancestorappid");
}

XMLResult QBXML::GetOldEstancestorAppId() {
  return _GetResult("oldestancestorappid");
}

XMLResult QBXML::GetUsers() {
  return _GetResult("users");
}

XMLResult QBXML::GetID()
{
  return _GetResult("id");
}

XMLResult QBXML::GetFieldType()
{
  return _GetResult("field_type");
}

std::vector<std::string> QBXML::GetChildDBIDs()
{
  std::string children = _GetResult("chdbids").text;
  std::vector<std::string> dbids;

  while (children.find("\">") != -1 && children.find("</") != -1) {
    unsigned first = children.find("\">");
    unsigned last = children.find("</");
    std::string result = children.substr(first + 2, last - first - 2);
    dbids.push_back(result);
    children.erase(first - 1, last - first + 3);
  }

  return dbids;
}

std::vector<QBXML> QBXML::GetFields() {
  std::vector<QBXML> results;
  std::string originalData = _xmlData->GetRawXML();
  
  bool flag = true;
  while (flag) {
    _xmlData->MoveAttributesIntoChildren("field");
    XMLResult aRes = _GetResult("field");
    if (aRes.valid) {
      XMLRead *reducedRead = new XMLRead;
      reducedRead->Load(aRes.text);
      QBXML newXML(reducedRead);
      results.push_back(newXML);
      // Strip remainingData for repeat
      _xmlData->Load(_RemoveSubstring(_xmlData->GetRawXML(), "<field>" + aRes.text + "</field>"));
    }
    else {
      flag = false;
    }
  }
  _xmlData->Load(originalData);
  return results;
}

std::vector<QBXML> QBXML::GetRecords() {
  std::vector<QBXML> results;
  std::string originalData = _xmlData->GetRawXML();

  bool flag = true;
  while (flag && originalData != "") {
    _xmlData->MoveAttributesIntoChildren("record");
    XMLResult aRes = _GetResult("record");
    if (aRes.valid) {
      XMLRead *reducedRead = new XMLRead;
      reducedRead->Load(aRes.text);
      QBXML newXML(reducedRead);
      results.push_back(newXML);
      // Strip remainingData for repeat
      _xmlData->Load(_RemoveSubstring(_xmlData->GetRawXML(), "<record>" + aRes.text + "</record>"));
    }
    else {
      flag = false;
    }
  }
  _xmlData->Load(originalData);
  return results;
}

XMLResult QBXML::_GetResult(std::string type) {
  XMLResult xmlRes;
  std::string result = _xmlData->GetFieldContents(type);
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
std::string QBXML::_RemoveSubstring(std::string mainString, std::string subString) {
  std::string t = mainString;
  std::string s = subString;

  size_t i = t.find(s);

  if (i != std::string::npos) {
    t.erase(i, s.length());
  }

  return t;
}