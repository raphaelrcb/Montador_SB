#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

// le o nome de um arquivo .txt (ex: arquivo_nome)
// e retorna pré-processado (ex: arquivo_nome.pre)

// ex: 	g++ -Wall -ansi pre_proc.cpp -o trab
// 		./trab ret -> gera ret.pre (pré-processado)
int main(int argc, char const *argv[]) {
	FILE *readFile, *writeFile;

	readFile = fopen(argv[1], "r");
	string outputFile = argv[1];
	outputFile.append(".pre");
	writeFile = fopen(outputFile.c_str(), "w");

	int countSpace = 0;
	char input;

	while((input = getc(readFile)) != EOF) {

		if(input == '\t' || input == ' ') {
			if(countSpace != 0 || ftell(readFile) == 1) {
				continue;
			} else {
				if(input == '\t') input = ' ';
				fwrite(&input, sizeof(char), sizeof(input), writeFile);
				countSpace++;
			}
		} else if(input == '\n') {
			countSpace = 0;
			fwrite(&input, sizeof(char), sizeof(input), writeFile);

			while((input = getc(readFile)) != EOF) {
				if(input != ' ' && input != '\t') break;
			}

			if (input != '\n') {
				input = toupper(input);
				fwrite(&input, sizeof(char), sizeof(input), writeFile);
			}
		
		} else {
			countSpace = 0;
			input  = toupper(input);
			fwrite(&input, sizeof(char), sizeof(input), writeFile);
		}

	}

	fclose(readFile);
	fclose(writeFile);

	return 0;
}