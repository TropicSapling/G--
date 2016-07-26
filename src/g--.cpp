#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <array>

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
		cerr << string("Usage: ") + string(argv[0]) + string(" [options] <file>\n") + string("Options: \n  --help   Displays this information\n  --debug  Shows debugging information\n  --fast   Don't show any information, makes it run slightly faster\n");
		return 1;
	} else {
		vector<array<string, 4>> objects;
		bool debugMode = false;
		bool hideInfo = false;
		if(argc >= 4) {
			if(argc > 4) {
				cout << "[!] Note: Unexisting argument(s) used, or argument(s) may be duplicated.\n";
			}
			debugMode = string(argv[1]) == "--debug" || string(argv[2]) == "--debug" ? true : false;
			hideInfo = string(argv[1]) == "--fast" || string(argv[2]) == "--fast" ? true : false;
		} else if(argc == 2 || argc == 3) {
			debugMode = string(argv[1]) == "--debug" ? true : false;
			hideInfo = string(argv[1]) == "--fast" ? true : false;
			if(string(argv[1]) == "--help") {
				cout << string("Usage: ") + string(argv[0]) + string(" [options] <file>\n") + string("Options: \n  --help   Displays this information\n  --debug  Shows debugging information\n  --fast   Don't show any information, makes it run slightly faster\n");
				return 0;
			}
		}

		if(debugMode && !hideInfo) {
			cout << "Reading file...\n";
		} else if(!hideInfo) {
			cout << "Reading file... ";
		}
		
		ifstream file(argv[argc - 1]);
		if(file.good()) {
			unsigned long i = 0;
			unsigned long file_chars = 0;
			char ch;
			
			if(!debugMode && !hideInfo) {
				while(file.get(ch)) {
					i++;
				}
				
				file_chars = i;
				i = 0;
				file.close();
			}
			
			string file_contents;
			bool objFound = false;
			char delState = 0;
			float prevProgress;
			string delObj;
			
			if(!debugMode && !hideInfo) {
				file.open(argv[argc - 1]);
			}
			while (file.get(ch)) {
				
				if(file_contents.length() < 1) {
					file_contents = ch;
				} else {
					file_contents += ch;
				}
				
				if(hasEnding(file_contents, "new ")) {
					unsigned long j = i;
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
					while(file_contents.at(j) != ' ' && file_contents.at(j) != '	' && file_contents.at(j) != ';' && j >= 0) {
						obj += string(1, file_contents.at(j));
						j--;
					}
					
					reverse(obj.begin(), obj.end());
					objects.push_back({obj, "delete", to_string(i), "false"});
					
					if(debugMode) {
						cout << "[DEBUG] obj: ";
						cout << obj << ", type: ";
						cout << "delete" << ", char: ";
						cout << i << ", array: ";
					}
				} else if(hasEnding(file_contents, "malloc(")) {
					unsigned long j = i;
					
					while(string(1, file_contents.at(j)) != "=") {
						j--;
					}
					j--;
					
					while(string(1, file_contents.at(j)) == " ") {
							j--;
					}
					
					string obj = string(1, file_contents.at(j));
					j--;
					while(file_contents.at(j) != ' ' && file_contents.at(j) != '	' && file_contents.at(j) != ';' && j >= 0) {
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
						unsigned short int j = 0;
						for(j = 0; j < objects.size(); j++) {
							if(objects[j][0] == delObj) {
								objects.erase(objects.begin() + j);
							}
						}
						delObj = "";
					} else {
						delObj += string(1, ch);
					}
				} else if(objFound) {
					if(ch == ';') {
						objFound = false;
						if(debugMode) {
							cout << objFound << "\n";
						}
					} else if(ch == '[') {
						objFound = false;
						objects[objects.size() - 1][3] = "true";
						if(debugMode) {
							cout << objFound << "\n";
						}
					}
				}
				
				i++;
				
				if(!debugMode && !hideInfo) {
					if(i / file_chars) {
						cout << "100%\n";
					} else {
						float progress = round(((float)i / (float)file_chars) * 100);
						if(progress != prevProgress) {
							string remover = " ";
							string mover = "\b";
							cout << progress << "%\b";
							for(char k = 0; k < to_string(progress).length(); k++) {
								cout << "\b";
								remover += " ";
								mover += "\b";
							}
							cout << remover << mover;
						}
						prevProgress = progress;
					}
				}
			}
			
			if(!debugMode && !hideInfo) {
				cout << "\n";
			}
		} else {
			if(debugMode) {
				cerr << "[!!] ERROR: Failed to read file. Perhaps you specified the wrong file name?\n";
			} else {
				cerr << "\n[!!] ERROR: Failed to read file. Perhaps you specified the wrong file name?\n";
			}
			return 1;
		}
		
		return 0;
	}
}
