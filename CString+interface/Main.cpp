#include "CString.h"
#include "interface.h"

using namespace std;

int main (void) {
    CString cStr1, cStr2, cStr3;

    std::cout<<"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
     cStr3 = cStr1 + cStr2;//move op+ move con
    CString cStr4(cStr1);//copy
    cStr4 = cStr3;// op=

    interface();
    return 0;
}
