#include <stdio.h>
#include <iostream>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <vector>

using namespace std;

class TabSimPre_Node {
public:
    string label, dir;
    int val;
    bool oper;
    TabSimPre_Node* next;
};

class TabelaSimbPre {
public:
    TabSimPre_Node *head, *tail;

    TabelaSimbPre() {
        cout << "> Criando tabela de símbolos PRE ...\n";
        this->head = NULL;
        this->tail = NULL;
    }
    ~TabelaSimbPre(){}
    
    void add(string label, string dir) {
        TabSimPre_Node* new_Label = new TabSimPre_Node();
        new_Label->label = label;
        new_Label->dir = dir;
        new_Label->oper = false;
        new_Label->val = 0;
        new_Label->next = NULL;
        if(this->head == NULL) {this->head = new_Label; this->tail = new_Label;}
        else {this->tail->next = new_Label; this->tail = new_Label;}
        return;
    }

    void add(string label, string dir, int val) {
        TabSimPre_Node* new_Label = new TabSimPre_Node();
        new_Label->label = label;
        new_Label->dir = dir;
        new_Label->oper = true;
        new_Label->val = val;
        new_Label->next = NULL;
        if(this->head == NULL) {this->head = new_Label; this->tail = new_Label;}
        else {this->tail->next = new_Label; this->tail = new_Label;}
        return;
    }

    void print() {
        TabSimPre_Node* olho = this->head;
        cout << "Label\t\tDir\t\tVal\n";
        while(olho != NULL) {
            if(olho->label.length() > 7) cout << olho->label << "\t" << olho->dir << "\t\t" << olho->val << endl;
            else cout << olho->label << "\t\t" << olho->dir << "\t\t" << olho->val << endl;
            olho = olho->next;
        }
    }

    TabSimPre_Node* find(string label) {
        TabSimPre_Node* olho = this->head;
        while(olho != NULL) {
            if(label == olho->label) {
                return olho;
            }
            olho = olho->next;
        }
        return NULL;
    }
};

class Pend_Node {
public:
    int end;
    Pend_Node* next;
};

class TabSim_Node {
public:
    string simb;
    bool def;
    int end;
    TabSim_Node* next;
    Pend_Node* pendHead;
};

class TabelaSim {
public:
    TabSim_Node *head, *tail;

    TabelaSim() {
        cout << "> Criando tabela de símbolos ...\n";
        this->head = NULL;
        this->tail = NULL;
    }
    ~TabelaSim(){}
    
    void addSimbData(string simb, int end) {
        TabSim_Node* new_Simb = new TabSim_Node();
        new_Simb->simb = simb;
        new_Simb->def = true;
        new_Simb->end = end;
        new_Simb->next = NULL;
        if(this->head == NULL) {this->head = new_Simb; this->tail = new_Simb;}
        else {this->tail->next = new_Simb; this->tail = new_Simb;}
        new_Simb->pendHead = new Pend_Node();
        new_Simb->pendHead->end = -1;
        new_Simb->pendHead->next = NULL;
    }

    void AddSimbText(string simb, int end) {
        TabSim_Node* new_Simb = new TabSim_Node();
        new_Simb->simb = simb;
        new_Simb->def = false;
        new_Simb->end = -1;
        new_Simb->next = NULL;
        if(this->head == NULL) {this->head = new_Simb; this->tail = new_Simb;}
        else {this->tail->next = new_Simb; this->tail = new_Simb;}
        new_Simb->pendHead = new Pend_Node();
        new_Simb->pendHead->end = -1;
        new_Simb->pendHead->next = NULL;
        Pend_Node* second_Pend = new Pend_Node();
        second_Pend->end = end;
        second_Pend->next = new_Simb->pendHead;
        new_Simb->pendHead = second_Pend;
    }

    void addPend(TabSim_Node* simbNode, int end) {
        Pend_Node* new_Pend = new Pend_Node();
        new_Pend->end = end;
        new_Pend->next = simbNode->pendHead;
        simbNode->pendHead = new_Pend;
    }

    vector<int> resolvePend(TabSim_Node* simbNode, int newEnd, vector<int> toArchive){
        simbNode->end = newEnd;
        simbNode->def = true;
        Pend_Node* pendAtual = simbNode->pendHead;
        if(pendAtual->end == -1) {
            cout << " > Símbolo não possúi pendências <" << endl;
            return toArchive;
        }
        while(pendAtual->end != -1) {
            toArchive.at(pendAtual->end) = simbNode->end;
            pendAtual = pendAtual->next;
        }
        return toArchive;
    }

    void print() {
        TabSim_Node* olho_Simb = this->head;
        Pend_Node* olho_Pend = olho_Simb->pendHead;
        cout << "Simb\t\tEnd\t\tDef\tPend\n";
        while(olho_Simb != NULL) {
            if(olho_Simb->simb.length() > 7) cout << olho_Simb->simb << "\t" << olho_Simb->end << "\t\t" << olho_Simb->def << "\t";
            else cout << olho_Simb->simb << "\t\t" << olho_Simb->end << "\t\t" << olho_Simb->def << "\t";
            while(olho_Pend != NULL) {
                cout << olho_Pend->end << ',';
                olho_Pend = olho_Pend->next;
            }
            cout << endl;
            olho_Simb = olho_Simb->next;
            if(olho_Simb != NULL) olho_Pend = olho_Simb->pendHead;
        }
    }

    TabSim_Node* find(string simb) {
        TabSim_Node* olho = this->head;
        while(olho != NULL) {
            if(simb == olho->simb) {
                return olho;
            }
            olho = olho->next;
        }
        return NULL;
    }
};

class Tabela_Node {
public:
    string name;
    int opcode, oper, size;
    Tabela_Node* next;
};

class Tabela {
public:
    Tabela_Node *head, *tail;

    Tabela() {
        cout << "> Criando tabela ...\n";
        this->head = NULL;
        this->tail = NULL;
    }
    ~Tabela(){}
    
    void add(string name, int oper, int opcode, int size) {
        Tabela_Node* new_Instruc = new Tabela_Node();
        new_Instruc->name = name;
        new_Instruc->oper = oper;
        new_Instruc->opcode = opcode;
        new_Instruc->size = size;
        new_Instruc->next = NULL;
        if(this->head == NULL) {this->head = new_Instruc; this->tail = new_Instruc;}
        else {this->tail->next = new_Instruc; this->tail = new_Instruc;}
        return;
    }

    void print() {
        Tabela_Node* olho = this->head;
        cout << "Inst\tOper\tCód\tSize\n";
        while(olho != NULL) {
            cout << olho->name << "\t" << olho->oper << "\t" << olho->opcode << "\t" << olho->size << endl;
            olho = olho->next;
        }
    }

    Tabela_Node* find(string inst) {
        Tabela_Node* olho = this->head;
        while(olho != NULL) {
            if(inst == olho->name) {
                return olho;
            }
            olho = olho->next;
        }
        return NULL;
    }
};

/* ------------------------------------------------------------------------- */

string PreProcess(string arq) {
    FILE *readFile, *writeFile;
    TabelaSimbPre preSimb;
    TabSimPre_Node* label_Node;

    cout << "> Iniciando o pré-processamento do arquivo \'" << arq << "\'\n"; 

    readFile = fopen(arq.c_str(), "r");
    char inputChar;
    int val;
    string to_Archive, inputStr, label, dir, outputFile = arq;
    outputFile.append(".pre");
    writeFile = fopen(outputFile.c_str(), "w");

    while(!feof(readFile)) { 
        inputStr = "";

        label = "";
        dir = "";
        val = 0;

        while((inputChar = getc(readFile)) != EOF && inputChar != '\n') inputStr+=inputChar;

        to_Archive = "";
        int iter = 0;
        char *p = strtok(strdupa(inputStr.c_str()), " \t,");

        while(p != NULL) {
            string p_String = p;

            if (iter == 0) {
                if(p_String.find(':') != string::npos || p_String == "IF") {
                    label = p_String;
                }
                else if (p_String == "STOP") to_Archive = p_String + '\n';
                else to_Archive = p_String + ' ';
            }
            else if (iter == 1) {
                if(label.find(':') != string::npos) {
                    dir = p_String;
                    if(dir != "EQU") to_Archive = label + ' ' + dir + '\n';
                    label = label.substr(0,label.find(':'));
                }
                else if (label == "IF") {
                    label_Node = preSimb.find(p_String);
                    if (label_Node == NULL) {
                        cout << "< ERRO > '" << p_String << "' não encontrado" << endl << endl;
                        fclose(readFile);
                        fclose(writeFile);
                        return outputFile;
                    }
                    if((*label_Node).dir == "EQU") {
                        if((*label_Node).val == 0) {
                            while((inputChar = getc(readFile)) != EOF) if(inputChar == '\n') break;
                        }
                    }
                }
                else to_Archive = to_Archive + p_String + '\n';
            }
            else if (iter == 2) {
                val = atoi(p_String.c_str());
                if(dir != "EQU") {
                    to_Archive = to_Archive.substr(0,to_Archive.find('\n'));
                    to_Archive = to_Archive + ' ' + p_String + '\n';
                }
                if(dir == "EQU") {
                    preSimb.add(label,dir,val);
                }
            }

            p = strtok(NULL, " \t,");
            iter++;
        }

        if(inputChar == EOF) to_Archive = to_Archive.substr(0,to_Archive.find('\n'));

        fwrite(to_Archive.c_str(), sizeof(char), to_Archive.length(), writeFile);

    }

    //preSimb.print();

    fclose(readFile);
    fclose(writeFile);
    preSimb.~TabelaSimbPre();

    cout << "\n> Arquivo Pré-Processado (\'" << outputFile << "\' gerado)\n\n";

    return outputFile;

}

/* ------------------------------------------------------------------------- */

Tabela CriaTabela(string c) {

    Tabela tabela;

    if(c == "instrucoes") {
        tabela.add("ADD"   , 1,  1, 2);
        tabela.add("SUB"   , 1,  2, 2);
        tabela.add("MULT"  , 1,  3, 2);
        tabela.add("DIV"   , 1,  4, 2);
        tabela.add("JMP"   , 1,  5, 2);
        tabela.add("JMPN"  , 1,  6, 2);
        tabela.add("JMPP"  , 1,  7, 2);
        tabela.add("JMPZ"  , 1,  8, 2);
        tabela.add("COPY"  , 2,  9, 3);
        tabela.add("LOAD"  , 1, 10, 2);
        tabela.add("STORE" , 1, 11, 2);
        tabela.add("INPUT" , 1, 12, 2);
        tabela.add("OUTPUT", 1, 13, 2);
        tabela.add("STOP"  , 0, 14, 1);
    } else if(c == "diretivas") {
        tabela.add("SECTION",  1, -1,  0);
        tabela.add("SPACE"  , -1, -1, -1);
        tabela.add("CONST"  ,  1, -1,  1);
        tabela.add("EQU"    ,  1, -1,  0);
        tabela.add("IF"     ,  1, -1,  0);
    }

    tabela.print();
    cout << endl;
    return tabela;
}

int main(int argc, char const *argv[]) {
    
    if(argv[1] == NULL) {
        cout << "Arquivo de entrada não fornecido !\n";
        return 0;
    }

    vector<int> toArchiveText, toArchiveData;
    int countEnd = 0, countLinha = 1;
    char inputChar;
    string inputStr;
    string arq_PreProcess = PreProcess(argv[1]);

    Tabela tabela_Inst = CriaTabela("instrucoes");
    Tabela tabela_Dir = CriaTabela("diretivas");
    Tabela_Node *instNode, *dirNode;
    TabelaSim tabela_Simb;
    TabSim_Node* simbNode;

    FILE* readFile = fopen(arq_PreProcess.c_str(), "r");
    string outputFile = argv[1];
    outputFile.append(".obj");
    FILE* writeFile = fopen(outputFile.c_str(), "w");

    cout << "> Iniciando leitura das labels do arquivo fonte \'" << arq_PreProcess << "\'\n";
    cout << "> Iniciando montagem do arquivo objeto - \'" << outputFile << "\'\n\n";

    while(!feof(readFile)) {
        inputStr = "";
        while((inputChar = getc(readFile)) != EOF && inputChar != '\n') {
            inputStr+=inputChar;
        }

        if(inputStr == "SECTION TEXT") { // Montagem da section text (instruções e pendências)
            countLinha++;
            cout << "  > Iniciando montagem SECTION TEXT" << endl;
            while(!feof(readFile)) {
                inputStr = "";
                while((inputChar = getc(readFile)) != EOF && inputChar != '\n') inputStr+=inputChar; 
               
                cout << "> inputStr = " << inputStr << endl;
                int iter = 0;
                char *p = strtok(strdupa(inputStr.c_str()), " ,");
                string p_String = p;

                while(p != NULL) {

                    if(iter == 0) {
                        if(p_String.find(':') != string::npos) {
                            p_String = p_String.substr(0,p_String.find(':'));
                            simbNode = tabela_Simb.find(p_String);
                            if(simbNode != NULL) {
                                if(!simbNode->def) {
                                    tabela_Simb.addPend(simbNode, countEnd - (instNode->size - iter));
                                }
                            }
                            else {
                                tabela_Simb.addSimbData(p_String, countEnd);
                            }
                            iter--;
                        }
                        else {
                            instNode = tabela_Inst.find(p);
                            if (instNode != NULL) { // Se achou a instrução na tabela
                                toArchiveText.push_back(instNode->opcode);
                                countEnd += instNode->size;
                            }
                            else {
                                cout << "! Instrução não encontrada ('" << p << "'). ERRO (linha " << countLinha << ") !" << endl; 
                                break; // Vai pra próxima linha    
                            }
                        }
                    }
                    else if(iter == 1) { // é algum operando (label)
                        simbNode = tabela_Simb.find(p);
                        if(simbNode != NULL) {
                            if(!simbNode->def) {
                                tabela_Simb.addPend(simbNode, countEnd - (instNode->size - iter));
                                toArchiveText.push_back(-1);
                            }
                            else toArchiveText.push_back(simbNode->end);
                        }
                        else {
                            tabela_Simb.AddSimbText(p, countEnd - (instNode->size - iter));
                            toArchiveText.push_back(-1);
                        }

                    } else { // é segundo operando do COPY
                        if(instNode->name != "COPY") {
                            cout << "! ERRO SINTÁTICO (linha "<< countLinha << ") !" << endl;
                        } else {
                            simbNode = tabela_Simb.find(p);
                            if(simbNode != NULL) {
                                if(!simbNode->def) {
                                    tabela_Simb.addPend(simbNode, countEnd - (instNode->size - iter));
                                    toArchiveText.push_back(-1);
                                }
                                else toArchiveText.push_back(simbNode->end);
                            }
                            else {
                                tabela_Simb.AddSimbText(p, countEnd - (instNode->size - iter));
                                toArchiveText.push_back(-1);
                            }
                        }
                    }
                    
                    iter++;
                    p = strtok(NULL, " ,");

                }

                if(inputStr == "STOP") break;

                countLinha++;
            }
        }
        else if(inputStr == "SECTION DATA") {  // // Montagem da section data (definição e resolução de pendências)
            countLinha++;
            cout << "  > Iniciando montagem SECTION DATA" << endl;
            while(!feof(readFile)) {
                inputStr = "";
                while((inputChar = getc(readFile)) != EOF && inputChar != '\n') inputStr+=inputChar; 
               
                if(inputStr == "SECTION TEXT") {
                    fseek(readFile, -13, SEEK_CUR);
                    break;
                }

                cout << "> inputStr = " << inputStr << endl;
                int iter = 0;
                char *p = strtok(strdupa(inputStr.c_str()), " :");

                while(p != NULL) {

                    if(iter == 0) {
                        simbNode = tabela_Simb.find(p);
                        if (simbNode != NULL) { // Se achou a instrução na tabela
                            toArchiveText = tabela_Simb.resolvePend(simbNode, countEnd, toArchiveText);

                        }
                        else {
                            cout << "Novo simbolo sem pendencias ('" << p << "') encontrado." << endl;
                            tabela_Simb.addSimbData(p,countEnd);
                            
                        } 
                    }
                    else if(iter == 1) { // é algum operando (label)

                        dirNode = tabela_Dir.find(p);
                        if(dirNode != NULL) {
                            if(dirNode->name == "SPACE") toArchiveData.push_back(0);
                            countEnd++;
                        }
                        else cout << "! Diretiva não encontrada ('" << p << "'). ERRO !" << endl;

                    } else if(iter == 2) {
                        if(dirNode->name == "SPACE") {
                            toArchiveData.push_back(0);
                            countEnd += atoi(p) - 1;
                        } else toArchiveData.push_back(atoi(p));
                    }
                    
                    iter++;
                    p = strtok(NULL, " ");

                }
                countLinha++;
            }
        }

        cout << endl;
    
    }

    tabela_Simb.print();
    cout << "--> Montagem finalizada <--" << endl;
    cout << "> toArchive =";

    unsigned int i = 0;
    while(i < toArchiveText.size()) {
        int num = toArchiveText.at(i);
        cout << ' ' << num;
        fprintf(writeFile, "%d", num);
        i++;
        if(i < toArchiveText.size()) fprintf(writeFile, "%c", ' ');
    }

    i = 0;
    while(i < toArchiveData.size()) {
        int num = toArchiveData.at(i);
        cout << ' ' << num;
        fprintf(writeFile, "%d", num);
        i++;
        if(i < toArchiveData.size()) fprintf(writeFile, "%c", ' ');
    }

    cout << endl;

    fclose(readFile);
    fclose(writeFile);

    return 0;
}