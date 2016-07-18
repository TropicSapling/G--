#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

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
		vector<array<string, 4>> objects;
		if(argc >= 4) {
			unsigned short int debugMode = string(argv[2]) == "--debug" || string(argv[3]) == "--debug" || string(argv[4]) == "--debug" ? 1 : 0;
			unsigned short int hideInfo = string(argv[2]) == "--fast" || string(argv[3]) == "--fast" || string(argv[4]) == "--fast" ? 1 : 0;
		} else if(argc = 3) {
			unsigned short int debugMode = string(argv[2]) == "--debug" || string(argv[3]) == "--debug" ? 1 : 0;
			unsigned short int hideInfo = string(argv[2]) == "--fast" || string(argv[3]) == "--fast" ? 1 : 0;
		} else {
			unsigned short int debugMode = string(argv[2]) == "--debug" ? 1 : 0;
			unsigned short int hideInfo = string(argv[2]) == "--fast" ? 1 : 0;
		}

		if(debugMode && !hideInfo) {
			cout << "Reading file...\n";
		} else if(!hideInfo) {
			cout << "Reading file... ";
		}
		
		ifstream file(argv[1]);
		if(file.good()) {
			unsigned short int i = 0;
			unsigned short int file_chars = 0;
			char ch;
			
			if(!debugMode && !hideInfo) {
				while(file.get(ch)) {
					i++;
				}
				
				file_chars = i;
				i = 0;
			}
			
			string file_contents;
			bool objFound = false;
			unsigned short int delState = 0;
			string delObj;
			
			while (file.get(ch)) {
				
				if(file_contents.length() < 1) {
					file_contents = ch;
				} else {
					file_contents += ch;
				}
				
				if(hasEnding(file_contents, "new ")) {
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
					while(file_contents.at(j) != ' ' && file_contents.at(j) != ';' && j >= 0) {
						obj += string(1, file_contents.at(j));
						j--;
					}
					
					reverse(obj.begin(), obj.end());
					objects.push_back({obj, "delete", to_string(i), "false"});
					
					if(debugMode) {
						cout << "[DEBUG] obj: ";
						cout << obj << ", type: ";
						cout << "delete, char: ";
						cout << i << "\n";
					}
				} else if(hasEnding(file_contents, "malloc(")) {
					unsigned short int j = i;
					
					while(string(1, file_contents.at(j)) != "=") {
						j--;
					}
					j--;
					
					while(string(1, file_contents.at(j)) == " ") {
							j--;
					}
					
					string obj = string(1, file_contents.at(j));
					j--;
					while(file_contents.at(j) != ' ' && file_contents.at(j) != ';' && j >= 0) {
						obj += string(1, file_contents.at(j));
						j--;
					}
					
					reverse(obj.begin(), obj.end());
					objects.push_back({obj, "free", to_string(i)});
					
					if(debugMode) {
						cout << "[DEBUG] obj: ";
						cout << obj << ", type: ";
						cout << "free, char: ";
						cout << i << "\n";
					}
				} else if(hasEnding(file_contents, "delete") || hasEnding(file_contents, "free(")) {
					delState = 1;
				} else if(delState == 1) {
					if(ch == ' ') {
						delState = 2;
					}
				} else if(delState == 2) {
					if(ch == ';' || ch == ')') {
						delState = 0;
						for(j = 0; j < objects.size(); j++) {
							if(objects[j][0] == delObj) {
								objects.erase(j);
							}
						}
						delObj = "";
					} else {
						delObj += string(1, ch);
					}
				} else if(objFound) {
					if(ch == ';') {
						objFound = false;
					} else if(ch == '[') {
						objFound = false;
						objects[objects.size() - 1][3] = "true";
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
