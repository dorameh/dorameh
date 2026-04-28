#include "CString.h"
#include <vector>

CString* CreateString(const string& filename, int type, const string& value, CFabric** fabrics);
void CheckConcat(const vector<CString*>& strings);

void CheckConcat(const vector<CString*>& strings){
    if (strings.size() >= 2) {
        CString* sum = nullptr;
        try {
          //  CString* sum = *strings[1] + *strings[0];
            sum = *strings[0] + *strings[1];
             cout << "Sum of 1st and 2nd strings: " << *sum << endl;
           // delete sum; тут
    }
        catch (const exception& e)
        {
            cout << "Error adding: " << e.what() << endl;
        }
        delete sum;
    }
    else
    {
        cout << "Not enough strings to add" << endl;
    }
}


int main() {

    vector<CString*> strings;
    CFabric* fabrics[2];
    fabrics[0] = new CFabric0();
    fabrics[1] = new CFabric1();

    ifstream in("input.txt");
    if (!in.is_open()) {
        cerr << "Failed to open input.txt file" << endl;
        delete fabrics[0];
        delete fabrics[1];
        return -1;
    }

    string filename, value;
    int type;
    while (in >> filename >> type >> value)
    {
        if (type != 0 && type != 1) {
            cerr << " Invalid type" << endl;
            delete fabrics[0];
            delete fabrics[1];
            for (auto str : strings) {
                delete str;
            }
            strings.clear();
            return -1;
            }
        try {

            CString* newStr = CreateString(filename, type, value, fabrics);
            strings.push_back(newStr);
        } catch (const exception& e) {
            cerr << "Error creating string: " << e.what() << endl;
        }
    }

    cout << "check concatenation (1 or 0)" << endl;
    bool answer;
    cin >> answer;
  if (answer) {
      CheckConcat(strings);
  }
  
    for (auto str : strings) {
        str->output();
    }

   
    for (auto str : strings) {
        delete str;
    }
    strings.clear();

    delete fabrics[0];
    delete fabrics[1];
  
    
    return 0;
}
