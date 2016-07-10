#include <iostream>
using namespace std;

int main () {
   double* pvalue = NULL; // Pointer initialized with null
   pvalue = new double; // Request memory for the variable
 
   *pvalue = 29494.99; // Store value at allocated address
   cout << "Value of pvalue : " << *pvalue << endl;

   delete pvalue; // Free up the memory, this is added by the garbage collector

   return 0;
}