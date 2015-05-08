/*
* Copyright Notice : Copyright 2015, Josiah Bruner, All Rights Reserved.
*/
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
#include "UTF-8\utf8.h"

using namespace std;

void init_string(struct curlString *s);
size_t _WriteStream(void *ptr, size_t size, size_t nmemb, struct curlString *s);

struct curlString {
    char *ptr;
    size_t len;
};

struct paramData {
    vector<string> bParams = {};
    vector<string> iParams = {};
    vector<string> sParams = {};
    vector<string> fParams = {};
    
    vector<bool> bValues = {};
    vector<int> iValues = {};
    vector<string> sValues = {};
    vector<float> fValues = {};
};

class QBWrapper {
    public:
        QBWrapper();
        ~QBWrapper();
        /* SetAppLocation
         * Parameters:
         *   string location: The URL pointing to the root. E.G. https://yourhostname.quickbase.com
         * Notes:
         *   USE HTTPS! Not HTTP.
         */
        void SetAppLocation(string location); // Required.

        /* SetAppToken
         * Parameters:
         *   string token: The app token for your app. You must supply this if your QB app requires application tokens.
         */
        void SetAppToken(string token); // Optional

        /* Authenticate -> API_Authenticate
         * Parameters:
         *   string username: The user's email address registered with QuickBase or the user name that was selected within QuickBase when the user registered.
         *   string password: The user's QuickBase password.
         *   int       hours: The number of hours that the ticket will be valid. If you pass NULL, this is equal to 12 hours.
         *   string    udata: A string value that you want returned. It will not be handled by QuickBase but it will be returned in the response.
         */
        QBXML Authenticate(string username, string password, int hours, string udata);

        /* AddRecord -> API_AddRecord
         * Parameters:
         *   vector<string>        fields: A vector array of field FIDs. (Field names will NOT work).
         *   vector<string> fieldContents: A vector array containing the contents of each field.
         *   bool                 disprec: Set to true if you display the record in QuickBase.
         *   bool             ignoreError: Set to true if you want to return no error.
         *   string                ticket: Specifies the auth ticket you have obtained from Authenticate().
         *   string              apptoken: Specifies a valid application token.
         *   string                 udata: A string value that you want returned. It will not be handled by QuickBase but it will be returned in the response.
         *   bool                 msInUTC: Set this parameter to 1 if you want to use Coordinated Universal Time.
         *   string                  dbid: The DBID of a table.
         * Notes:
         *   - fields and fieldContents MUST have equal lengths.
         */
        QBXML AddRecord(vector<string> fields, vector<string> fieldContents, bool disprec, bool ignoreError, string ticket, string apptoken, string udata, bool msInUTC, string dbid);
        
        /* EditRecord -> API_EditRecord
         * Parameters:
         *   int                 rid: The RID of the record to edit. Required.
         *   int            updateID: Specifies the latest record state.
         *   vector<string>   fields: A vector array of field FIDs. (Field names will NOT work).
         *   vector<string> contents: A vector array containing the contents of each field.
         *   bool            disprec: Set to true if you display the record in QuickBase.
         *   bool        ignoreError: Set to true if you want to return no error.
         *   string           ticket: Specifies the auth ticket you have obtained from Authenticate().
         *   string         apptoken: Specifies a valid application token.
         *   string            udata: A string value that you want returned. It will not be handled by QuickBase but it will be returned in the response.
         *   bool            msInUTC: Set this parameter to 1 if you want to use Coordinated Universal Time.
         *   string             dbid: The DBID of a table.
         * Notes:
         *   - fields and contents MUST have equal lengths.
         */
        QBXML EditRecord(int rid, int updateID, vector<string> fields, vector<string> contents, bool disprec, bool ignoreError, string ticket, string apptoken, string udata, bool msInUTC, string dbid);
        
        /* GetSchema -> API_GetSchema
         * Parameters:
         *   string           ticket: Specifies the auth ticket you have obtained from Authenticate().
         *   string         apptoken: Specifies a valid application token.
         *   string            udata: A string value that you want returned. It will not be handled by QuickBase but it will be returned in the response.
         *   string             dbid: The DBID of a table.
         */
        QBXML GetSchema(string ticket, string apptoken, string udata, string dbid);

        /* GetDBInfo -> API_GetDBInfo
         * Parameters:
         *   string           ticket: Specifies the auth ticket you have obtained from Authenticate().
         *   string         apptoken: Specifies a valid application token.
         *   string            udata: A string value that you want returned. It will not be handled by QuickBase but it will be returned in the response.
         *   string             dbid: The DBID of an app or table.
         */
        QBXML GetDBInfo(string ticket, string apptoken, string udata, string dbid);

        /* AddField -> API_AddField
         * Parameters:
         *   bool           addToForms: Set to true if this field should appear automatically to forms with "Auto-Add new fields" set.
         *   string           apptoken: Specifies a valid application token.
         *   string              label: Allows you to enter the name of the new field.
         *   string               mode: "virtual" (formula), "lookup", or "" are valid values.
         *   string             ticket: Specifies the auth ticket you have obtained from Authenticate().
         *   string               type: The QuickBase field type. The eligible type names differ slightly from their counterparts in the QuickBase UI:
         *   string              udata: A string value that you want returned. It will not be handled by QuickBase but it will be returned in the response.
         *   string               dbid: The DBID of a table.
         * Notes:
         *   Field Type         Quickbase API field type
              Checkbox         	      checkbox
              Date	                  date
              Duration	              duration
              Email Address	          email
              File Attachment	        file
              Formula	                (see the "mode" param)
              Lookup	                (see the "mode" param)
              Numeric	                float
              Numeric - Currency	    currency
              Numeric - Rating	      rating
              Phone Number	          phone
              Report Link	            dblink
              Text                   	text
              Time Of Day	            timeofday
              URL	                    url
         */
        QBXML AddField(bool addToForms, string apptoken, string label, string mode, string ticket, string type, string udata, string dbid);
        
        /* DeleteField -> API_DeleteField
         * Parameters:
         *   int           fid: The fid of the field you want to remove.
         *   string     ticket: Specifies the auth ticket you have obtained from Authenticate().
         *   string   apptoken: Specifies a valid application token.
         *   string      udata: A string value that you want returned. It will not be handled by QuickBase but it will be returned in the response.
         *   string       dbid: The DBID of an app or table.
         */
        QBXML DeleteField(int fid, string ticket, string apptoken, string udata, string dbid);

        /* SetFieldProperties -> API_SetFieldProperties
         * Parameters:
         *   vector<string>  propertyParams: Vector array of property tags.
         *   vector<string>  propertyValues: Vector array of property values.
         *   int                        fid:
         *   string                  ticket: Specifies the auth ticket you have obtained from Authenticate().
         *   string                apptoken: Specifies a valid application token.
         *   string                   udata: A string value that you want returned. It will not be handled by QuickBase but it will be returned in the response.
         *   string                    dbid: The DBID of an app or table.
         * Notes:
         *   propertyParams and propertyValues must have equal length.
         *   See http://www.quickbase.com/api-guide/index.html#setfieldproperties.html for property tags and valid values.
         */
        QBXML SetFieldProperties(vector<string>propertyParams, vector<string>propertyValues, int fid, string ticket, string apptoken, string udata, string dbid);
        
        /* CreateTable -> API_CreateTable
         * Parameters:
         *   int           fid: The fid of the field you want to remove.
         *   string     ticket: Specifies the auth ticket you have obtained from Authenticate().
         *   string   apptoken: Specifies a valid application token.
         *   string      udata: A string value that you want returned. It will not be handled by QuickBase but it will be returned in the response.
         *   string       dbid: The DBID of an app.
         */
        QBXML CreateTable(string tname, string pnoun, string ticket, string apptoken, string udata, string dbid);
        
        /* GetNumRecords -> API_GetNumRecords
         * Parameters:
         *   string     ticket: Specifies the auth ticket you have obtained from Authenticate().
         *   string   apptoken: Specifies a valid application token.
         *   string      udata: A string value that you want returned. It will not be handled by QuickBase but it will be returned in the response.
         *   string       dbid: The DBID of a table.
         */
        QBXML GetNumRecords(string ticket, string apptoken, string udata, string dbid);

        /* GetRecordInfo -> API_GetRecordInfo
         * Parameters:
         *   int           rid: The RID of the record you want information on.
         *   string     ticket: Specifies the auth ticket you have obtained from Authenticate().
         *   string   apptoken: Specifies a valid application token.
         *   string      udata: A string value that you want returned. It will not be handled by QuickBase but it will be returned in the response.
         *   string       dbid: The DBID of a table.
         */
        QBXML GetRecordInfo(int rid, string ticket, string apptoken, string udata, string dbid);
        
        /* DeleteRecord -> API_DeleteRecord
         * Parameters:
         *   int           rid: The RID of the record you want information on.
         *   string     ticket: Specifies the auth ticket you have obtained from Authenticate().
         *   string   apptoken: Specifies a valid application token.
         *   string      udata: A string value that you want returned. It will not be handled by QuickBase but it will be returned in the response.
         *   string       dbid: The DBID of a table.
         */
        QBXML DeleteRecord(int rid, string ticket, string apptoken, string udata, string dbid);
        
        /* PurgeRecords -> API_PurgeRecords
         * Parameters:
         *   string      query: Specificies the query string. E.G. {myfid.operator.value}
         *   int           qid: The query id of a saved query.
         *   string      qname: The name of a saved query.
         *   string     ticket: Specifies the auth ticket you have obtained from Authenticate().
         *   string   apptoken: Specifies a valid application token.
         *   string      udata: A string value that you want returned. It will not be handled by QuickBase but it will be returned in the response.
         *   string       dbid: The DBID of a table.
         * Notes:
         *   The first three parameters are used in order. If one is NULL then the next is used.
         */
        QBXML PurgeRecords(string query, int qid, string qname, string ticket, string apptoken, string udata, string dbid);

        /* DoQuery -> API_DoQuery
         * Parameters:
         *   string             query: Specificies the query string. E.G. {myfid.operator.value}
         *   int                  qid: The query id of a saved query.
         *   string             qname: The name of a saved query.
         *   string             clist: A period-delimited list of field IDs to be returned. QuickBase will return values for these field IDs in the order in which you enter them here.
         *   string             slist: A period-delimited list of field IDs used to determine sorting.
         *   bool                 fmt: Set this parameter to structured to specify that the query should return structured data.
         *   bool    returnPercentage: Specifies whether Numeric - Percent values in the returned data will be percentage format (10% is shown as 10).
         *   string           options: Specifies return options for the query. You can use any or all of the options, separating the options with a period.
         *   bool         includeRids: To return record IDs for each record, set this parameter to 1. 
         *   string            ticket: Specifies the auth ticket you have obtained from Authenticate().
         *   string          apptoken: Specifies a valid application token.
         *   string             udata: A string value that you want returned. It will not be handled by QuickBase but it will be returned in the response.
         *   string              dbid: The DBID of a table.
         * Notes:
         *   The first three parameters are used in order. If one is NULL then the next is used.
         *   options:
         *     num-n --specifies a maximum of n records in the return
         *     onlynew --returns only those records marked with new or updated flags
         *     skp-n --skips the first n records returned by the query
         *     sortorder-A --specifies an ascending order
         *     sortorder-D --specifies a descending order
         *     nosort --returns unsorted records, ignoring the sortorder option, the slist parameter, and the default sort for the table
         */
        QBXML DoQuery(string query, int qid, string qname, string clist, string slist, bool fmt, bool returnPercentage, string options, bool includeRids, string ticket, string apptoken, string udata, string dbid);

        /* GetFieldContents
         * Parameters:
         *   int          fid: The field id of the field you want to obtain contents.
         *   string    ticket: Specifies the auth ticket you have obtained from Authenticate().
         *   string  apptoken: Specifies a valid application token.
         *   string     udata: A string value that you want returned. It will not be handled by QuickBase but it will be returned in the response.
         *   string      dbid: The DBID of a table.
         *   string       rid: The RID of a record.
         */
        string GetFieldContents(int fid, string ticket, string apptoken, string udata, string dbid, int rid);

        /* Cleanup
         * Notes:
         *   Removes the outputDataStream and self-destructs this object.
         */
        void Cleanup();
    private:
        string _apptoken;
        string _ticket;
        string _appLocation;
        string _XMLDataPrelim(string apiAction, string dbid, vector<string> params, vector<string> values, vector<string> altParams = vector<string>(), vector<string> altValues = vector<string>());
        string _PostWithFile(string file, string apiName, string dbid);
        string _IntToString(int anInt);
        string _FloatToString(float aFloat);
        string _BoolToString(bool aBool);
        int _CURLSend(string inputStream);
        string _GetStringBetween(string data, string startDelim, string endDelim);
        string _SizetToString(size_t aSizeT);
        void _AddOptionalParams(vector<string>*paramArray, vector<string>*valueArray, paramData data);
};
