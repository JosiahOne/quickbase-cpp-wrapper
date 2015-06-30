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

void init_string(struct curlString *s);
size_t _WriteStream(void *ptr, size_t size, size_t nmemb, struct curlString *s);

struct curlString {
    char *ptr;
    size_t len;
};

struct paramData {
    std::vector<std::string> bParams = {};
    std::vector<std::string> iParams = {};
    std::vector<std::string> sParams = {};
    std::vector<std::string> fParams = {};
    
    std::vector<bool> bValues = {};
    std::vector<int> iValues = {};
    std::vector<std::string> sValues = {};
    std::vector<float> fValues = {};
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
        void SetAppLocation(std::string location); // Required.

        /* SetAppToken
         * Parameters:
         *   string token: The app token for your app. You must supply this if your QB app requires application tokens.
         */
        void SetAppToken(std::string token); // Optional

        /* Authenticate -> API_Authenticate
         * Parameters:
         *   string username: The user's email address registered with QuickBase or the user name that was selected within QuickBase when the user registered.
         *   string password: The user's QuickBase password.
         *   int       hours: The number of hours that the ticket will be valid. If you pass NULL, this is equal to 12 hours.
         *   string    udata: A string value that you want returned. It will not be handled by QuickBase but it will be returned in the response.
         */
        QBXML Authenticate(std::string username, std::string password, int hours, std::string udata);

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
        QBXML AddRecord(std::vector<std::string> fields, std::vector<std::string> fieldContents, bool disprec, bool ignoreError, std::string ticket, std::string apptoken, std::string udata, bool msInUTC, std::string dbid);
        
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
        QBXML EditRecord(int rid, int updateID, std::vector<std::string> fields, std::vector<std::string> contents, bool disprec, bool ignoreError, std::string ticket, std::string apptoken, std::string udata, bool msInUTC, std::string dbid);
        
        /* GetSchema -> API_GetSchema
         * Parameters:
         *   string           ticket: Specifies the auth ticket you have obtained from Authenticate().
         *   string         apptoken: Specifies a valid application token.
         *   string            udata: A string value that you want returned. It will not be handled by QuickBase but it will be returned in the response.
         *   string             dbid: The DBID of a table.
         */
        QBXML GetSchema(std::string ticket, std::string apptoken, std::string udata, std::string dbid);

        /* GetDBInfo -> API_GetDBInfo
         * Parameters:
         *   string           ticket: Specifies the auth ticket you have obtained from Authenticate().
         *   string         apptoken: Specifies a valid application token.
         *   string            udata: A string value that you want returned. It will not be handled by QuickBase but it will be returned in the response.
         *   string             dbid: The DBID of an app or table.
         */
        QBXML GetDBInfo(std::string ticket, std::string apptoken, std::string udata, std::string dbid);

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
        QBXML AddField(bool addToForms, std::string apptoken, std::string label, std::string mode, std::string ticket, std::string type, std::string udata, std::string dbid);
        
        /* DeleteField -> API_DeleteField
         * Parameters:
         *   int           fid: The fid of the field you want to remove.
         *   string     ticket: Specifies the auth ticket you have obtained from Authenticate().
         *   string   apptoken: Specifies a valid application token.
         *   string      udata: A string value that you want returned. It will not be handled by QuickBase but it will be returned in the response.
         *   string       dbid: The DBID of an app or table.
         */
        QBXML DeleteField(int fid, std::string ticket, std::string apptoken, std::string udata, std::string dbid);

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
        QBXML SetFieldProperties(std::vector<std::string>propertyParams, std::vector<std::string>propertyValues, int fid, std::string ticket, std::string apptoken, std::string udata, std::string dbid);
        
        /* CreateTable -> API_CreateTable
         * Parameters:
         *   int           fid: The fid of the field you want to remove.
         *   string     ticket: Specifies the auth ticket you have obtained from Authenticate().
         *   string   apptoken: Specifies a valid application token.
         *   string      udata: A string value that you want returned. It will not be handled by QuickBase but it will be returned in the response.
         *   string       dbid: The DBID of an app.
         */
        QBXML CreateTable(std::string tname, std::string pnoun, std::string ticket, std::string apptoken, std::string udata, std::string dbid);
        
        /* GetNumRecords -> API_GetNumRecords
         * Parameters:
         *   string     ticket: Specifies the auth ticket you have obtained from Authenticate().
         *   string   apptoken: Specifies a valid application token.
         *   string      udata: A string value that you want returned. It will not be handled by QuickBase but it will be returned in the response.
         *   string       dbid: The DBID of a table.
         */
        QBXML GetNumRecords(std::string ticket, std::string apptoken, std::string udata, std::string dbid);

        /* GetRecordInfo -> API_GetRecordInfo
         * Parameters:
         *   int           rid: The RID of the record you want information on.
         *   string     ticket: Specifies the auth ticket you have obtained from Authenticate().
         *   string   apptoken: Specifies a valid application token.
         *   string      udata: A string value that you want returned. It will not be handled by QuickBase but it will be returned in the response.
         *   string       dbid: The DBID of a table.
         */
        QBXML GetRecordInfo(int rid, std::string ticket, std::string apptoken, std::string udata, std::string dbid);
        
        /* DeleteRecord -> API_DeleteRecord
         * Parameters:
         *   int           rid: The RID of the record you want information on.
         *   string     ticket: Specifies the auth ticket you have obtained from Authenticate().
         *   string   apptoken: Specifies a valid application token.
         *   string      udata: A string value that you want returned. It will not be handled by QuickBase but it will be returned in the response.
         *   string       dbid: The DBID of a table.
         */
        QBXML DeleteRecord(int rid, std::string ticket, std::string apptoken, std::string udata, std::string dbid);
        
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
        QBXML PurgeRecords(std::string query, int qid, std::string qname, std::string ticket, std::string apptoken, std::string udata, std::string dbid);

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
        QBXML DoQuery(std::string query, int qid, std::string qname, std::string clist, std::string slist, bool fmt, bool returnPercentage, std::string options, bool includeRids, std::string ticket, std::string apptoken, std::string udata, std::string dbid);

        /* GetFieldContents
         * Parameters:
         *   int          fid: The field id of the field you want to obtain contents.
         *   string    ticket: Specifies the auth ticket you have obtained from Authenticate().
         *   string  apptoken: Specifies a valid application token.
         *   string     udata: A string value that you want returned. It will not be handled by QuickBase but it will be returned in the response.
         *   string      dbid: The DBID of a table.
         *   string       rid: The RID of a record.
         */
        std::string GetFieldContents(int fid, std::string ticket, std::string apptoken, std::string udata, std::string dbid, int rid);
       
       /* SignOut
        * Parameters:
        *   string    ticket: Specifies the auth ticket you have obtained from Authenticate().
        *   string  apptoken: Specifies a valid application token.
        *   string     udata: A string value that you want returned. It will not be handled by QuickBase but it will be returned in the response.
        *   string      dbid: The DBID of a table.
        */
        QBXML SignOut(std::string ticket, std::string apptoken, std::string udata, std::string dbid);

        /* Cleanup
         * Notes:
         *   Removes the outputDataStream and self-destructs this object.
         */
        void Cleanup();
    private:
        std::string _apptoken;
        std::string _ticket;
        std::string _appLocation;
        std::string _XMLDataPrelim(std::string apiAction, std::string dbid, std::vector<std::string> params, std::vector<std::string> values, std::vector<std::string> altParams = std::vector<std::string>(), std::vector<std::string> altValues = std::vector<std::string>());
        std::string _PostWithFile(std::string file, std::string apiName, std::string dbid);
        std::string _IntToString(int anInt);
        std::string _FloatToString(float aFloat);
        std::string _BoolToString(bool aBool);
        int _CURLSend(std::string inputStream);
        std::string _GetStringBetween(std::string data, std::string startDelim, std::string endDelim);
        std::string _SizetToString(size_t aSizeT);
        void _AddOptionalParams(std::vector<std::string>*paramArray, std::vector<std::string>*valueArray, paramData data);
};
