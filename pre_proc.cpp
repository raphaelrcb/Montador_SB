#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main(int argc, char const *argv[]) {
	ifstream readFile;
	readFile.open(argv[1]);

	char inputChar;

	while(readFile.get(inputChar)) {
		
		if(inputChar == '\n') {
			cout << "\\n" << endl;
			continue;
		}

		cout << inputChar;

	}

	cout << "(EOF)\n";

	return 0;
}
