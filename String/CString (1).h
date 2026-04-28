#include <iostream>
#include <fstream>
#include <cstring>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
using namespace std;

class CString {
protected:
    size_t n; 
    char* s; 
    string outFilename;

public:
    
     const char* getS() const { return s; }
     string getFilename() const { return outFilename; }

    CString();
    CString(const string& filename, const string& str);
    CString(const CString& o);
    virtual ~CString();

    void Clean();
    void SetZero();
    void CopyOnly(const CString& o); 

    CString& operator=(const CString& o);
   
    virtual CString* operator+(const CString& o) const = 0; 

    virtual int output() = 0;
    friend ostream& operator<<(ostream& os, const CString& o);
    friend istream& operator>>(istream& is, CString& o);
};

class CString0 : public CString {
public:
 CString0(const string& filename, const string& str): CString(filename, str) {};
  // using CString::CString;
  int output() override;
  CString* operator+(const CString& o) const override;
};

class CString1 : public CString {
public:
CString1(const string& filename, const string& str): CString(filename, str) {};
 // using CString::CString; 
  CString* operator+(const CString& o) const override;
  int output() override;
};

class CFabric
{
	
	public:
    virtual CString* Create(string file, string value) = 0;
    virtual ~CFabric() {}
};

class CFabric0 : public CFabric
{
	public:
  CString* Create(string file, string value) override {
      return new CString0(file, value);
  }  
};

class CFabric1 : public CFabric
{
  public:
  CString* Create(string file, string value) override {
      return new CString1(file, value);
  }    
};


