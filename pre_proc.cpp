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

	char input;

	while((input = getc(readFile)) != EOF) {

		if(input == '\t' || input == ' ') {
			if(ftell(readFile) == 1) {
				continue;
			} else {
				while((input = getc(readFile)) != EOF) {
					if(input != ' ' && input != '\t') break;
				}
				input = ' ';
				fwrite(&input, sizeof(char), sizeof(input), writeFile);
				fseek(readFile, -1, SEEK_CUR);
				continue;
			}
		} else if(input == '\n') {
			fwrite(&input, sizeof(char), sizeof(input), writeFile);
			while((input = getc(readFile)) != EOF) {
					if(input != ' ' && input != '\t') break;
			}
			if(input != '\n') {
				input  = toupper(input);
				fwrite(&input, sizeof(char), sizeof(input), writeFile);
			}
			continue;
		
		} else if(input == ';') {
			while((input = getc(readFile)) != EOF) {
				if(input == '\n') break;
			}
			fwrite(&input, sizeof(char), sizeof(input), writeFile);
			continue;
		} else {
			input  = toupper(input);
			fwrite(&input, sizeof(char), sizeof(input), writeFile);
		}

	}

	fclose(readFile);
	fclose(writeFile);

	return 0;
}