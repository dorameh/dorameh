#pragma once
#include <iostream>
#include <stdio.h>
#include <string.h>  
#include <iostream>
using namespace std;
class CString;

class CString {
    int n; 
    char*s;
	
public:
    
	CString() {
		SetZero();
		}
     void SetZero() {
        s = NULL;n=0;
         }
	

    CString(const CString& o) { std::cout << "Copy-constructor\n" << std::endl; CopyOnly(o);}   
	  void CopyOnly(const CString& o) {
         n = o.n;
         s = new char[n];
         memcpy(s,o.s,n);
     }


    CString(const string o) {
        n = o.size();
        s = new char[n];
        for (int i = 0; i < n; ++i) {
            s[i] = o[i];
           }
        }

     ~CString() {
         Clean();
         }
     void Clean() {
        delete[] s;
        SetZero();
      }
   

    CString operator+(const CString& o);

    CString operator=(const CString& o) {
        std::cout << "Copy-assignment\n" << std::endl;
        if (this != &o) {
            Clean();
            CopyOnly(o);
        }
        return *this;
    }

    CString operator=(const string& o) {std::cout << "operator=str\n" << std::endl;
        return CString(o);
    }
 
CString(CString&& o) noexcept{
    std::cout << "Move-constructor\n" << std::endl;
      n = o.n;
    s = o.s;
    o.s = nullptr;
    o.n = 0;
    
    
}
 CString& operator=(CString&& o) noexcept{
     if(this != &o){
         Clean();
    std::cout << "Move-assignment operator\n" << std::endl;
    n = o.n;
    s = o.s;
    o.s = nullptr;
    o.n = 0;
     }
     return *this;
   
 }
  

 

    friend ostream &operator<<(ostream &cout,const CString&o);
    friend istream &operator>>(istream &cin, CString &o);
   
};
