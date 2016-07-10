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
					size_t ch = line.find("new");
					
					if(ch != string::npos) {
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
						
						objects.push_back({obj, i});
						cout << obj << ", ";
						cout << i << endl;
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
