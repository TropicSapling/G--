#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
	if(argc < 2) {
		cerr << string("Usage: ") + string(argv[0]) + string(" <file_name>\n");
		return 1;
	} else {
		cout << "Reading file...\n";
		ifstream file(argv[1]);
		if(file.good()) {
			string line;
			while (getline(file, line)) {
				// Process line
				cout << line << endl;
			}
		} else {
			cerr << "[!!] ERROR: Failed to read file. Perhaps you specified the wrong file name?\n";
			return 1;
		}
		
		return 0;
	}
}
