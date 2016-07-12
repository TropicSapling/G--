#include <iostream>
using namespace std;

int main () {
   double* pvalue = NULL; // Pointer initialized with null
   pvalue = new double; // Request memory for the variable, g-- registers the pointer
 
   *pvalue = 29494.99; // Store value at allocated address
   cout << "Value of pvalue : " << *pvalue << endl; // Prints the value, g-- detects the latest use of the pointer here
   delete pvalue; // Therefore g-- deletes the pointer right after, freeing the memory

   return 0;
}
