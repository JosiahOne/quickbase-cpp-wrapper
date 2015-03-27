#include "QBWrapper.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char** argv) {
    // This is for enabling the features of the backend.
    // This is NOT the wrapper though.

    // Currently this is more or less a test host.

    QBWrapper *qb = new QBWrapper;
    qb->SetAppLocation("https://lathrupindustries.quickbase.com");
    QBXML result = qb->Authenticate("jbruner@lathrupindustries.com", "password123", 12, "test"); // PASS
    cout << "\n\nTICKET = " << result.GetTicket().text <<"\n\n";
    string ticket = result.GetTicket().text;

    vector<string> vec1 = { "9" };
    vector<string> vec2 = { "1" };
    vector<string> vec3 = { "2" };

    QBXML result2 = qb->AddRecord(vec1, vec2, NULL, NULL, ticket, "", "", NULL, "bjr9riz52"); // PASS

    cout << endl << result2.GetRID().text;

    QBXML result3 = qb->EditRecord(31, NULL, vec1, vec3, NULL, NULL, ticket, "", "", NULL, "bjr9riz52"); // PASS

    cout << endl << result3.GetNumFieldsChanged().text;

    return 0;
}
