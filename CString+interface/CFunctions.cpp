#include "CString.h"
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <string>

using namespace std;



CString CString::operator+(const CString&c) {
    CString temp;
    temp.n = c.n+n;
    temp.s = new char[temp.n];
    memcpy(temp.s, s, n);
    memcpy(temp.s + n, c.s, c.n);
    return temp;
}



ostream &operator<<(ostream &cout, const CString &o) {
    for (int i = 0; i < o.n; i++) 
        printf("%c", o.s[i]);
    return cout;
}

istream &operator>>(istream &cin, CString &o) {
    string s;
    cin >> ws;
    getline(cin, s);
    o = CString(s);
    return cin;
}
