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
		vector<string> objects;
		
		cout << "Reading file...\n";
		ifstream file(argv[1]);
		if(file.good()) {
			string line;
			unsigned short int i = 0;
			while (getline(file, line)) {
				if(line.find("new")) {
					unsigned short int ch = line.find("new");
					
					while(line.at(ch) != "=") {
						ch--;
					}
					ch--;
					
					while(line.at(ch) == " ") {
						ch--;
					}
					
					string obj = line.at(ch);
					ch--;
					while(line.at(ch) != " " && line.at(ch) != ";" && ch > 0) {
						obj += line.at(ch);
						ch--;
					}
					
					objects.push_back([obj, i]);
				}
				i++;
			}
		} else {
			cerr << "[!!] ERROR: Failed to read file. Perhaps you specified the wrong file name?\n";
			return 1;
		}
		
		return 0;
	}
}
