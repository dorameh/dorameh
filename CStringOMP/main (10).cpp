#include "CString.h"
#include <vector>

 CString* CreateString(int type, size_t str_size, CFabric** fabrics,int unique_seed);
void getRandStr(string& str, size_t str_size,int unique_seed);
int main() {

//работает

    #ifdef _OPENMP
    cout << "OpenMP is enabled! Max threads: " << omp_get_max_threads() << endl;
#else
    cout << "OpenMP is NOT enabled!" << endl;
#endif



    ofstream("data1.txt").close();
    ofstream("data2.txt").close();
    ofstream("res.txt").close();
    ofstream("res_omp.txt").close();
   //вроде работает
    vector<CString*> strings1, strings2;
    size_t num, str_size;
    cout << "Enter the number of strings" << endl;
    cin >> num;
    cout << "Enter the size of one string" << endl;
    cin >> str_size;
    CFabric* fabrics[2];
    fabrics[0] = new CFabric0();
    fabrics[1] = new CFabric1();

        try {  
            for (size_t i = 0; i < num; ++i) {
               CString* str = CreateString(0,str_size,fabrics,i);
               strings1.push_back(str);
            }
         
            for (size_t i = 0; i < num; ++i) {
              CString* str = CreateString(1,str_size,fabrics,i+1000);
                strings2.push_back(str);
            }
        } catch (const exception& e) {
            cerr << "Error creating vector of strings: " << e.what() << endl;
        }


    for (auto str : strings1) {
        str->output("data1.txt");
    }
    for (auto str : strings2) {
        str->output("data2.txt");
    }

    cout << "Output and generate done" << endl;

    if (strings1.size() != strings2.size()) {
    cerr << "Error: vectors have different sizes!" << endl;
    return 1;
   }
   //omp
    auto start = chrono::high_resolution_clock::now(); 
    #pragma omp parallel for 
    for (size_t i = 0; i < strings1.size(); ++i) {
      CString* sum_omp = *strings1[i]+ *strings2[i];

             
}
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;


    //without
     auto start1 = chrono::high_resolution_clock::now();

    CString* sum = nullptr;
    for (size_t i = 0; i < strings1.size(); ++i) {
     sum = *strings2[i]+ *strings1[i]; 
	}
       auto end1 = chrono::high_resolution_clock::now();
       chrono::duration<double> duration1 = end1 - start1;




   cout << "Adding done" << endl;


   cout.precision(9);
   cout << "Time with omp: " << fixed << duration.count() << " seconds\n";
   cout << "Time: " << fixed << duration1.count() << " seconds\n";
   cout << "Speedup: " << duration1.count() / duration.count() << "x\n";



     for (auto str : strings1) 
     {
         delete str;
     }
    
     for (auto str : strings2)
     {
     delete str;
     }
   
     strings1.clear();
     strings2.clear();
    delete fabrics[0];
    delete fabrics[1];
   

}
