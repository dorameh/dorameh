#include "CString.h"

CString::CString() {
    SetZero();
} 


CString::CString(const string& filename, const string& o) {

    outFilename = filename;
    n = o.size() +1; //тут
     s = new char[n]; 
      strcpy(s, o.c_str());
} 


CString::CString(const CString& o) {
    CopyOnly(o);
}


CString::~CString() {
    Clean();
}


void CString::Clean() {
     delete[] s;
    SetZero();
}


void CString::SetZero() {
    s = nullptr;

    n = 0;
    outFilename.clear();
}


void CString::CopyOnly(const CString& o) {
    //delete[] s; //здесь
    n = o.n;
    s = new char[n]; 
    strcpy(s, o.s);
    outFilename = o.outFilename;
}


CString& CString::operator=(const CString& o) {
    if (this != &o) {
    Clean();
    CopyOnly(o);
 }
     return *this;
}


CString* CString0::operator+(const CString& o) const {
     cout << "use operator of sum 0"<< endl ;
    string newStr(getS());
    newStr += o.getS();
    return new CString0(getFilename(), newStr);
}


CString* CString1::operator+(const CString& o) const {
     cout << "use operator of sum 1"<< endl ;
    string newStr(getS());
    newStr += o.getS();
    return new CString1(getFilename(), newStr);
}




ostream& operator<<(ostream& out, const CString& o) {
    out << o.s;
    return out;
}


istream& operator>>(istream& in, CString& o) {

    string temp;
    in >> temp;
    delete[] o.s; //здесь
     o.n = temp.size()+1;
     o.s = new char[o.n];
    strcpy(o.s, temp.c_str());
    return in;
}


int CString0::output() {
    ofstream out(outFilename, ios::app); 
    if (!out.is_open()) {
        cerr << "File opening failed" << endl;
     return -1;
    }
    out << "0 " << s << endl; 
    out.close();
    return 0;
}

int CString1::output() {
    ofstream out(outFilename, ios::app); 
    if (!out.is_open()) {
     cerr << " Failed to open outfile" << endl;
     //out.close();
     return -1;
    }
    out << "1 " << s << endl; 
    out.close();
    return 0;
}

CString* CreateString(const string& filename, int type, const string& value, CFabric** fabrics) {

    ofstream out_file(filename, ios::trunc);
    if (!out_file) {
        cerr << "Failed to  open file" << endl;
        exit(0);
    }
    out_file.close();
    return fabrics[type]->Create(filename, value);
}


 
