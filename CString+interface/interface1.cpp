#include "CString.h"
#include "interface.h"

using namespace std;

void interface(void) {
        int act;
        cout << "Enter action:" << endl; 
        cout << "1. Enter in terminal\t" << "2. Random generate\n" << endl;
        cin >> act;
        if (act != 1 && act != 2) {
                cout << "Incorrect format of action" << endl;
                return;
        }
        if (act == 1) {
                try {
                        cout << "\nTest1:\n";
                       
                        CString cStr1, cStr2;
                        cout << "Enter the first string:\n" << endl;
                        cin >> cStr1;
                        cout << endl;
                        cout<<"Enter the second string:\n"<<endl;
                        cin >> cStr2;
                        cout << endl;
                        cout << "CString_1 = " << cStr1 << endl;
                        cout << "CString_2 = " << cStr2 << endl;
                        CString cStr3(cStr1 + cStr2);
                        cStr3 = cStr1 + cStr2;
                        cout << "CSsring3 = CString1 + CString2 = " << cStr3 << endl;

                }catch(int err){printf("error \n");}
            return;
            }

        else {
                srand(time(NULL));
                try
                {
                    int len1 = rand()%50 + 1;
                    int len2 = rand()%50 + 1;
                    string str1, str2;
                    getRandStr(str1, len1);
                    getRandStr(str2, len2);
                    CString cStr1(str1);
                    CString cStr2(str2);
                    CString cStr3;
                    cout << "CString_1 = " << cStr1 << endl;
                    cout << "CString_2 = " << cStr2 << endl;
                    cStr3 = cStr1 + cStr2;
                    cout << "CSsring3 = CString1 + CString2 = " << cStr3 << endl;
                        

                 }
                 catch(int err){cout << "error =: " <<err<<endl;}

                return;

        }
    return;
}

void getRandStr(string& str, int len) {
    for (int i = 0; i < len; ++i) {
        char c = rand() % 127;
     
        str += c;
    }
}
