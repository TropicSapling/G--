#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

ios_base::sync_with_stdio(false);

bool hasEnding (std::string const &fullString, std::string const &ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

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
			
			string file_contents;
			bool objFound = false;
			
			while (file.get(ch)) {
				
				if(file_contents.length < 1) {
					file_contents = ch;
				} else {
					file_contents += ch;
				}
				
				if(hasEnding(file_contents, "new")) {
					unsigned short int j = i;
					objFound = true;
					
					while(string(1, file_contents.at(j)) != "=") {
						j--;
					}
					j--;
					
					while(string(1, file_contents.at(j)) == " ") {
							j--;
					}
					
					string obj = string(1, file_contents.at(j));
					j--;
					while(string(1, file_contents.at(j)) != " " && string(1, file_contents.at(j)) != ";" && j >= 0) {
						obj += string(1, file_contents.at(j));
						j--;
					}
					
					reverse(obj.begin(), obj.end());
					objects.push_back({obj, "false", string(i)});
					
					if(debugMode) {
						cout << "[DEBUG] obj: ";
						cout << obj << ", objFound: ";
						cout << objFound << ", char: ";
						cout << i << "\n";
					}
				} else if(hasEnding(file_contents, "delete")) {
					
				} else if(objFound) {
					if(ch == ";") {
						objFound = false;
					} else if(hasEnding(file_contents, "[]")) {
						objFound = false;
						objects[objects.size() - 1][1] = string(i);
					}
				}
				
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
