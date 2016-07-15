#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

ios_base::sync_with_stdio(false);

int main(int argc, char* argv[]) {
	if(argc < 2) {
		cerr << string("Usage: ") + string(argv[0]) + string(" <file_name>\n") + string("Optional parameters: --debug\n");
		return 1;
	} else {
		vector<array<string, 3>> objects;
		unsigned short int debugMode = argv[2] == "--debug" || argv[3] == "--debug" || argv[4] == "--debug" ? 1 : 0;
		unsigned short int hideInfo = argv[2] == "--fast" || argv[3] == "--fast" || argv[4] == "--fast" ? 1 : 0;
		
		if(debugMode && !hideInfo) {
			cout << "Reading file...\n";
		} else if(!hideInfo) {
			cout << "Reading file... ";
		}
		
		ifstream file(argv[1]);
		if(file.good()) {
			unsigned short int i = 0;
			unsigned short int file_chars = 0;
			
			if(!debugMode && !hideInfo) {
				while(file.get(ch)) {
					i++;
				}
				
				file_chars = i;
				i = 0;
			}
			
			while (file.get(ch)) {
				
				
				
/*				if(line.find("new")) {
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
						objects.push_back({obj, isArray, string(i)});
						
						if(debugMode) {
							cout << "[DEBUG] obj: ";
							cout << obj << ", isArray: ";
							cout << isArray << ", line: ";
							cout << i << "\n";
						}
					}
				} else if(line.find("delete") {
					// WIP
				}
					
				for(unsigned j = 0; j < objects.size(); j++) {
					if(line.find(objects[j][0])) {
						objects[j][1] = i;
					}
				} */
				i++;
				if(!debugMode && !hideInfo) {
					cout << (i / file_chars) * 100 << "%\r";
					cout.flush();
				}
			}
			
			if(!debugMode && !hideInfo) {
				cout << "\n";
			}
		} else {
			cerr << "[!!] ERROR: Failed to read file. Perhaps you specified the wrong file name?\n";
			return 1;
		}
		
		return 0;
	}
}
