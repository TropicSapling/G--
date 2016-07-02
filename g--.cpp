#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
	if(argc < 2) {
		cerr << "Usage: " + argv[0] + " <file_name>";
		return 1;
	} else {
		cout << "Reading file...";
		return 0;
	}
}
