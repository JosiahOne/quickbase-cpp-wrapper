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
    qb->Authenticate("josiah", "awesomePW", 12, "test");
}
