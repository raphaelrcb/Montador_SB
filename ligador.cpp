#include <stdio.h>
#include <iostream>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <vector>
#include <sstream>

using namespace std;

int main(int argc, char const *argv[]) {
FILE *moda, *modb, *outputFile;
int headerCountA = 1,dCountA = 1, uCountA = 1, realocA;
string modaArq = argv[1], mapBitsA;
char inputChar;

vector<string> d_simbA, u_simbA;
vector<int> d_valA, u_endA, t_codeA;

int headerCountB = 1,dCountB = 1, uCountB = 1, realocB;
string modbArq, mapBitsB;

vector<string> d_simbB, u_simbB;
vector<int> d_valB, u_endB, t_codeB;

vector<int> output_code;

moda = fopen(modaArq.c_str(), "r");

while(!feof(moda)) {
string inputStr = "";

	while((inputChar = getc(moda)) != EOF && inputChar != '\n') inputStr+=inputChar;

	char *p_atual = strtok(strdupa(inputStr.c_str()), " +:");
	string pString_inicio = " ";

	while(p_atual != NULL) {
		string pString_atual = p_atual;

		if(pString_atual == "H") pString_inicio = "H";
		else if(pString_atual == "D"){
			pString_inicio = "D";
			dCountA = 2;
		}
		else if(pString_atual == "U") {
			pString_inicio = "U";
			uCountA = 2;
		}
		else if(pString_atual == "T") pString_inicio = "T";

		if(pString_atual != pString_inicio) {
			if(pString_inicio == "H") {
				if(headerCountA == 2) {
					realocA = atoi(p_atual);
				}
				else if(headerCountA == 3) {
					mapBitsA = pString_atual;
				}
				headerCountA++;
			}
			else if(pString_inicio == "D") {
				if(dCountA == 2) {
					d_simbA.push_back(pString_atual);
					dCountA++;
				}
				else if(dCountA == 3) {
					d_valA.push_back(atoi(p_atual));
				}
			}
			else if(pString_inicio == "U") {
				if(uCountA == 2) {
					u_simbA.push_back(pString_atual);
					uCountA++;
				}
				else if(uCountA == 3) {
					u_endA.push_back(atoi(p_atual));
				}
			}
			else if(pString_inicio == "T") {
				t_codeA.push_back(atoi(p_atual));
			}
		}

		p_atual = strtok(NULL, " \t,");
	}

}

fclose(moda);

outputFile = fopen("saida.obj", "w");

if(argv[2] == NULL){
	for(unsigned int i = 0; i < t_codeA.size(); i++) {
            fprintf(outputFile, "%d ", t_codeA.at(i));
    }

    for(unsigned int i = 0; i < t_codeA.size(); i++) {
		cout << t_codeA[i] << ' ';
	}

	cout << endl;

} 
else {
	modbArq = argv[2];
	modb = fopen(modbArq.c_str(), "r");

	while(!feof(modb)) {
	string inputStr = "";

		while((inputChar = getc(modb)) != EOF && inputChar != '\n') inputStr+=inputChar;

		char *p_atual = strtok(strdupa(inputStr.c_str()), " +:");
		string pString_inicio = " ";

		while(p_atual != NULL) {
			string pString_atual = p_atual;

			if(pString_atual == "H") pString_inicio = "H";
			else if(pString_atual == "D"){
				pString_inicio = "D";
				dCountB = 2;
			}
			else if(pString_atual == "U") {
				pString_inicio = "U";
				uCountB = 2;
			}
			else if(pString_atual == "T") pString_inicio = "T";

			if(pString_atual != pString_inicio) {
				if(pString_inicio == "H") {
					if(headerCountB == 2) {
						realocB = atoi(p_atual);
					}
					else if(headerCountB == 3) {
						mapBitsB = pString_atual;
					}
					headerCountB++;
				}
				else if(pString_inicio == "D") {
					if(dCountB == 2) {
						d_simbB.push_back(pString_atual);
						dCountB++;
					}
					else if(dCountB == 3) {
						d_valB.push_back(atoi(p_atual));
					}
				}
				else if(pString_inicio == "U") {
					if(uCountB == 2) {
						u_simbB.push_back(pString_atual);
						uCountB++;
					}
					else if(uCountB == 3) {
						u_endB.push_back(atoi(p_atual));
					}
				}
				else if(pString_inicio == "T") {
					t_codeB.push_back(atoi(p_atual));
				}
			}

			p_atual = strtok(NULL, " \t,");
		}

}

fclose(modb);

}

if(argv[2] != NULL) {

	for(unsigned int i = 0; i < t_codeA.size(); i++) {
		output_code.push_back(t_codeA[i]);
	}

	for(unsigned int i = 0; i < t_codeB.size(); i++) {
		output_code.push_back(t_codeB[i]);
	}

	for(unsigned int i = 0; i < d_valB.size(); i++) {
		d_valB[i] = d_valB[i] + realocA;
	}

	for(unsigned int i = 0; i < u_endB.size(); i++) {
		u_endB[i] = u_endB[i] + realocA;
	}

	for(unsigned int i = 0; i < d_simbA.size(); i++) {
		for(unsigned int j = 0; j < u_simbB.size(); j++){
			if(d_simbA[i] == u_simbB[j]) {
				output_code[u_endB.at(j)] = output_code[u_endB.at(j)] + d_valA[i];
			}
		}
	}

	for(unsigned int i = 0; i < d_simbB.size(); i++) {
		for(unsigned int j = 0; j < u_simbA.size(); j++){
			if(d_simbB[i] == u_simbA[j]) {
				output_code[u_endA.at(j)] = output_code[u_endA.at(j)] + d_valB[i];
			}
		}
	}

	for(unsigned int i = 0; i < output_code.size(); i++) {
		fprintf(outputFile, "%d ", output_code.at(i));
	}

	for(unsigned int i = 0; i < output_code.size(); i++) {
		cout << output_code[i] << ' ';
	}

	cout << endl;


}

fclose(outputFile);

return 0;

}