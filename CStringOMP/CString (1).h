
#include <iostream>
#include <fstream>
#include <cstring>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include <omp.h>
#include <chrono>
using namespace std;

class CString {
protected:
    size_t n; 
    char* s; 
    string outFilename;

public:
    
     const char* getS() const { return s; }
     int getN() const {return n;}             

    CString();
    CString( const string& str); 
    CString(const CString& o);   
    virtual ~CString();         
    void Clean();
    void SetZero();
    void CopyOnly(const CString& o);  // можно убрать

    CString& operator=(const CString& o);
   
    virtual CString* operator+(const CString& o) const = 0; 

    virtual int output(const string& outFilename) = 0;
    friend ostream& operator<<(ostream& os, const CString& o);
    friend istream& operator>>(istream& is, CString& o);
};

class CString0 : public CString {
public:
 CString0( const string& str): CString( str) {};
  CString0(const CString& str);
  int output(const string& outFilename) override;
  CString* operator+(const CString& o) const override;
};

class CString1 : public CString {
public:
CString1( const string& str): CString(str) {};
 CString1(const CString& str);
  CString* operator+(const CString& o) const override;
  int output(const string& outFilename) override;
};

class CFabric
{
	
	public:
    virtual CString* Create( string value) = 0;
    virtual ~CFabric() {}
};

class CFabric0 : public CFabric
{
	public:
  CString* Create(string value) override {
      return new CString0( value);
  }  
};

class CFabric1 : public CFabric
{
  public:
  CString* Create( string value) override {
      return new CString1(value);
  }    
};


