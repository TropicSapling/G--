#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
	if(argc < 2) {
		cerr << "Usage: " + argv[0] + " <file_name>";
		return 1;
	} else {
		cout << "Reading file...";
		
		ifstream file(argv[1]);
    		string line;
    		while (getline(file, line)) {
        		// Process line
    		}
		
		return 0;
	}
}
