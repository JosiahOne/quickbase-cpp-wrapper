#include "QBWrapper.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char** argv) {
    // This is for enabling the features of the backend.
    // This is NOT the wrapper though.

    QBWrapper *qb = new QBWrapper;
    qb->SetAppLocation("https://lathrupindustries.quickbase.com");
    string result = qb->Authenticate("jbruner@lathrupindustries.com", "password123", 12, "test");
    cout << "TICKET = " << result;
    return 0;
}
