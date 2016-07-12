#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
	if(argc < 2) {
		cerr << string("Usage: ") + string(argv[0]) + string(" <file_name>\n") + string("Optional parameters: --debug\n");
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
					size_t ch = line.find("new");
					
					if(ch != string::npos) {
						string isArray = "false";
						
						if(line.find("[]") != string::npos) {
							isArray = "true";
						}
						
						while(string(1, line.at(ch)) != "=") {
							ch--;
						}
						ch--;
						
						while(string(1, line.at(ch)) == " ") {
							ch--;
						}
						
						string obj = string(1, line.at(ch));
						ch--;
						while(string(1, line.at(ch)) != " " && string(1, line.at(ch)) != ";" && ch > 0) {
							obj += string(1, line.at(ch));
							ch--;
						}
						
						reverse(obj.begin(), obj.end());
						objects.push_back({obj, isArray, i});
						
						if(argv[2] == "--debug" || argv[3] == "--debug") {
							cout << "[DEBUG] obj: ";
							cout << obj << ", isArray: ";
							cout << isArray << ", line: ";
							cout << i << endl;
						}
					}
				}
					
				for(unsigned j = 0; j < objects.length; j++) {
					if(line.find(objects[j][0])) {
						objects[j][1] = i;
					}
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
