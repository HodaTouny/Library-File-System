#include <iostream>
#include <vector>
#include "PrimaryIndex.h"
using namespace std;

int main() {
    PrimaryIndex x;
    cout<<x.previousRecordSize("Books.txt");
    return 0;
}
