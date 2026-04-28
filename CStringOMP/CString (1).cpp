#include "CString.h"

CString::CString() {
    SetZero();
} 


CString::CString( const string& o) {
    n = o.size() +1; 
     s = new char[n]; 
      strcpy(s, o.c_str());
} 


CString::CString(const CString& o) {
    CopyOnly(o);
}


CString::~CString() {
     if (s) {
       
        delete[] s;
        s = nullptr;  
}
}


void CString::Clean() {
     delete[] s;
    SetZero();
}



void CString::SetZero() {
    s = nullptr;
    n = 0;

}


void CString::CopyOnly(const CString& o) {
    n = o.n;
    s = new char[n]; 
    strcpy(s, o.s);
   
}

CString1::CString1(const CString& str){
   
   n = str.getN()+1;
    s = new char[n];  
    strcpy(s, str.getS());  
}

CString0::CString0(const CString& str){
    
    n = str.getN()+1;
    s = new char[n];  
    strcpy(s, str.getS());  

}


CString& CString::operator=(const CString& o) {
    if (this != &o) {
    Clean();
    CopyOnly(o);
 }
     return *this;
}



CString* CString0::operator+(const CString& o) const {
    string newStr = getS();
    string otherStr = o.getS();
    
    #pragma omp parallel for
    for (size_t i = 0; i < newStr.size(); ++i) {
        newStr[i] = (newStr[i] * 31 + 17) % 256;
    }
    
    #pragma omp parallel for
    for (size_t i = 0; i < otherStr.size(); ++i) {
        otherStr[i] = (otherStr[i] * 13 + 29) % 256;
    }
    
    for (char c : otherStr) {
        newStr += (c ^ 0x55);
    }
    
    return new CString0(newStr);
}
CString* CString1::operator+(const CString& o) const {
    string newStr = getS();
    string otherStr = o.getS();
   
    for (size_t i = 0; i < newStr.size(); ++i) {
        newStr[i] = (newStr[i] * 31 + 17) % 256;
    }
   

    for (size_t i = 0; i < otherStr.size(); ++i) {
        otherStr[i] = (otherStr[i] * 13 + 29) % 256;
    }
 
    for (char c : otherStr) {
        newStr += (c ^ 0x55);
    }
    
    return new CString1(newStr);
}

ostream& operator<<(ostream& out, const CString& o) {
    out << o.s;
    return out;
}


istream& operator>>(istream& in, CString& o) {

    string temp;
    in >> temp;
    delete[] o.s; 
     o.n = temp.size()+1;
     o.s = new char[o.n];
    strcpy(o.s, temp.c_str());
    return in;
}


int CString0::output(const string& outFilename) {
     ofstream file(outFilename, ios::app);
    if (!file) {
        cerr << "ERROR: Cannot open " << outFilename << endl;
        return -1;
    }
    file << s << "\n";
    file.close();  
    return 0;
}

int CString1::output(const string& outFilename) {
     ofstream file(outFilename, ios::app);
    if (!file) {
        cerr << "ERROR: Cannot open " << outFilename << endl;
        return -1;
    }
    file << s << "\n";
    file.close();  
    return 0;
}

void getRandStr(string& str, size_t str_size,int unique_seed) {
    srand(time(NULL)+unique_seed);
    for (size_t i = 0; i < str_size; ++i) {
         char c = rand() % 95 + 32; 
        str += c;
    }

}
CString* CreateString(int type,size_t str_size, CFabric** fabrics,int unique_seed) {

string str;
//int type = rand() % 2;  
getRandStr(str, str_size, unique_seed);
return fabrics[type]->Create(str);
      
}

 
