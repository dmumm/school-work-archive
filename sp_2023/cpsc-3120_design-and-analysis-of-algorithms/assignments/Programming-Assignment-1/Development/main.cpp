#include <iostream>
#include <fstream>
#include <cmath>

#include "DynamicTable.h"
#include "Timer.h"


using namespace std;

int main() {
//    std::ofstream out("out.txt"); // debug
//    std::cout.rdbuf(out.rdbuf()); // debug
    //STEP 2
    int n_insertions = 3000;
    DynamicTable table1 = DynamicTable();
    for(int i=0; i<n_insertions; i++){
        table1.insert(i, true);
    }

    DynamicTable table2 = DynamicTable();
    for(int i=0; i<n_insertions; i++){
        table2.insert(i, false);
    }

    cout << table1.get_n_resize() << " " << table2.get_n_resize() << endl;

    // //STEP 3
    // //--------------------------------------------------------------
     Timer time;
     float total_time_from_resizedummy = 0;
     float total_time_from_resize = 0;

     for(int op=1; op<n_insertions; op++){
        
             DynamicTable table1 = DynamicTable();
             time.start();
             for(int i=0; i<op; i++){
                 table1.insert(i, true);
             }
             time.stop();
             total_time_from_resizedummy += time.getElapsedTime();

             DynamicTable table2 = DynamicTable();
             time.start();
             for(int i=1; i<op; i++){
                 table2.insert(i, false);
             }
             time.stop();
             total_time_from_resize += time.getElapsedTime();
     }
     cout << total_time_from_resizedummy << " " << total_time_from_resize << endl;
     // STEP 3 END
     // --------------------------------------------------------------
    
/*
     // STEP 4
     // --------------------------------------------------------------
     ofstream outFile1 = ofstream("results_dummy.txt");
     ofstream outFile2 = ofstream("results.txt");
    
     total_time_from_resizedummy = 0;
     total_time_from_resize = 0;

     for(int op=1; op<n_insertions; op++){
        
             DynamicTable table1 = DynamicTable();
             time.start();
             for(int i=0; i<op; i++){
                 table1.insert(i, true);
             }
             time.stop();
             outFile1 << time.getElapsedTime() << endl;

             DynamicTable table2 = DynamicTable();
             time.start();
             for(int i=1; i<op; i++){
                 table2.insert(i, false);
             }
             time.stop();
             outFile2 << time.getElapsedTime() << endl;
     }
    
     outFile1.close();
     outFile2.close();
     //STEP 4 END
    // //--------------------------------------------------------------
*/
    return 0;
}
