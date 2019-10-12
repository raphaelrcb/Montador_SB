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
    
    void addSimb(string simb, int end) {
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
            cout << olho_Simb->simb << "\t\t" << olho_Simb->end << "\t\t" << olho_Simb->def << "\t";
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

string PreProcess(string arq) {
    FILE *readFile, *writeFile;
    TabelaSimbPre preSimb;

    cout << "> Iniciando o pré-processamento do arquivo \'" << arq << "\'\n\n"; 

    readFile = fopen(arq.c_str(), "r");
    string outputFile = arq;
    outputFile.erase (outputFile.end()-4, outputFile.end());
    outputFile.append(".pre");
    writeFile = fopen(outputFile.c_str(), "w");

    char input;
    string label, dir, val_str, to_archive;
    int val;

    while((input = getc(readFile)) != EOF) {

        TabSimPre_Node* label_Node;
        label = "";
        dir = "";
        val_str = "";
        val = 0;

        if(input == '\t' || input == ' ') { // Se input for tab ou espaço
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
        } else if(input == ';') { // Se input for ponto e vírgula (comentário)
            while((input = getc(readFile)) != EOF) {
                if(input == '\n') break;
            }
            fwrite(&input, sizeof(char), sizeof(input), writeFile);
            while((input = getc(readFile)) != EOF) {
                    if(input != ' ' && input != '\t') break;
            }
            fseek(readFile, -1, SEEK_CUR);
            continue;
        } else {                    // Se input for um caracter 'normal'
            label+=toupper(input);
            while((input = getc(readFile)) != EOF) { // Procurando o label
                if(input == '\n') { // Se input for quebra de linha
                    to_archive = label + '\n';
                    while((input = getc(readFile)) != EOF) {
                        if(input != ' ' && input != '\t') break;
                    }
                    fseek(readFile, -1, SEEK_CUR);
                    break;
                } else if(input == ' ' || input == '\t' || input == ';') { // Se input for tab, espaço ou ponto e vírgula
                    to_archive = label;
                    if(to_archive == "IF") {
                        label = "";
                        while((input = getc(readFile)) != EOF) {
                            if(input != ' ' && input != '\t') break;
                        }
                        label+=toupper(input);
                        while((input = getc(readFile)) != EOF) {
                            if(input == '\n') break;
                            label+=toupper(input);
                        }
                        while((input = getc(readFile)) != EOF) {
                            if(input != ' ' && input != '\t') break;
                        }
                        label_Node = preSimb.find(label);
                        if(label_Node == NULL) {
                            cout << "< ERRO > " << (*label_Node).label << endl;
                            fclose(readFile);
                            fclose(writeFile);
                            return outputFile;
                        }
                        to_archive = "";
                        if((*label_Node).dir == "EQU") {
                            if((*label_Node).val == 0) {
                                while((input = getc(readFile)) != EOF) {
                                    if(input == '\n') break;
                                }
                                while((input = getc(readFile)) != EOF) {
                                    if(input != ' ' && input != '\t') break;
                                }

                            }
                        }
                    }
                    fseek(readFile, -1, SEEK_CUR);

                    break;
                } else if (input == ':') {
                    while((input = getc(readFile)) != EOF) { // Procurando o dir
                        if(input != ' ' && input != '\t') break;
                    }
                    dir+=input;
                    while((input = getc(readFile)) != EOF) {
                        if(input == '\n') {
                            while((input = getc(readFile)) != EOF) {
                                if(input != ' ' && input != '\t') break;
                            }
                            fseek(readFile, -1, SEEK_CUR);
                            if(dir == "EQU") preSimb.add(label,dir);
                            to_archive = label + ": " + dir + '\n';
                            break;
                        } else if(input == ' ' || input == '\t') {
                            while((input = getc(readFile)) != EOF) { // Procurando o oper
                                if(input != ' ' && input != '\t') break;
                            }
                            val_str +=input;
                            while((input = getc(readFile)) != EOF) { // Tratando o oper
                                if(input == '\n') {
                                    while((input = getc(readFile)) != EOF) {
                                        if(input != ' ' && input != '\t') break;
                                    }
                                    fseek(readFile, -1, SEEK_CUR);
                                    val = atoi(val_str.c_str());
                                    if(dir == "EQU") preSimb.add(label,dir,val);
                                    to_archive = label + ": " + dir + ' ' + val_str + '\n';
                                    break;
                                }
                                val_str+=input;
                            }
                            if(input == EOF) {
                                val = atoi(val_str.c_str());
                                if(dir == "EQU") preSimb.add(label,dir,val);
                                to_archive = label + ": " + dir + ' ' + val_str;
                            }
                            break;
                        }
                        dir+=input;
                    }
                    break;
                }
                label+=input;
            }
            if (dir != "EQU") fwrite(to_archive.c_str(), sizeof(char), to_archive.length(), writeFile);
        }
    }

    preSimb.print();

    fclose(readFile);
    fclose(writeFile);
    preSimb.~TabelaSimbPre();

    cout << "\n> Arquivo Pré-Processado (\'" << outputFile << "\' gerado)\n\n";

    return outputFile;
}

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

    vector<int> toArchive;
    int countEnd = 0;
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
    outputFile.erase (outputFile.end()-4, outputFile.end());
    outputFile.append(".obj");
    FILE* writeFile = fopen(outputFile.c_str(), "w");

    cout << "> Iniciando leitura das labels do arquivo fonte \'" << arq_PreProcess << "\'\n";
    cout << "> Iniciando montagem do arquivo objeto - \'" << outputFile << "\'\n";

    while(!feof(readFile)) {
        inputStr = "";
        while((inputChar = getc(readFile)) != EOF && inputChar != '\n') {
            inputStr+=inputChar;
        }

        if(inputStr == "SECTION TEXT") { // Montagem da section text (instruções e pendências)
            cout << "  > Iniciando montagem SECTION TEXT" << endl;
            while(!feof(readFile)) {
                inputStr = "";
                while((inputChar = getc(readFile)) != EOF && inputChar != '\n') inputStr+=inputChar; 
               
                cout << "> inputStr = " << inputStr << endl;
                int iter = 0;
                char *p = strtok(strdupa(inputStr.c_str()), " ");

                while(p != NULL) {

                    if(iter == 0) {
                        instNode = tabela_Inst.find(p);
                        if (instNode != NULL) { // Se achou a instrução na tabela
                            toArchive.push_back(instNode->opcode);
                            countEnd += instNode->size;
                        }
                        else cout << "! Instrução não encontrada ('" << p << "'). ERRO !" << endl;    
                    }
                    else { // é algum operando (label)
                        simbNode = tabela_Simb.find(p);
                        if(simbNode != NULL) {
                            tabela_Simb.addPend(simbNode, countEnd - iter);

                        }
                        else {
                            tabela_Simb.addSimb(p, countEnd - iter);
                        }

                        toArchive.push_back(-1);
                    }
                    
                    iter++;
                    p = strtok(NULL, " ");

                }

                if(inputStr == "STOP") break;

            }
        }
        else if(inputStr == "SECTION DATA") {  // // Montagem da section data (definição e resolução de pendências)
            cout << "  > Iniciando montagem SECTION DATA" << endl;
            while(!feof(readFile)) {
                inputStr = "";
                while((inputChar = getc(readFile)) != EOF && inputChar != '\n') inputStr+=inputChar; 
               
                cout << "> inputStr = " << inputStr << endl;
                int iter = 0;
                char *p = strtok(strdupa(inputStr.c_str()), " :");

                while(p != NULL) {

                    if(iter == 0) {
                        simbNode = tabela_Simb.find(p);
                        if (simbNode != NULL) { // Se achou a instrução na tabela
                            toArchive = tabela_Simb.resolvePend(simbNode, countEnd, toArchive);

                        }
                        else {
                            cout << "Novo símbolo ('" << p << "') sem  encontrado." << endl;
                            
                        } 
                    }
                    else if(iter == 1) { // é algum operando (label)

                        dirNode = tabela_Dir.find(p);
                        if(dirNode != NULL) {
                            if(dirNode->name == "SPACE") toArchive.push_back(0);
                            countEnd++;
                        }
                        else cout << "! Diretiva não encontrada ('" << p << "'). ERRO !" << endl;

                    } else if(iter == 2) {
                        if(dirNode->name == "SPACE") {
                            toArchive.push_back(0);
                            countEnd += atoi(p) - 1;
                        } else toArchive.push_back(atoi(p));
                    }
                    
                    iter++;
                    p = strtok(NULL, " ");

                }
            }
        }

        cout << endl;
    
    }

    tabela_Simb.print();
    cout << "--> Montagem finalizada <--" << endl;
    cout << "> toArchive =";

    unsigned int i = 0;
    while(i < toArchive.size()) {
        int num = toArchive.at(i);
        cout << ' ' << num;
        fprintf(writeFile, "%d", num);
        i++;
        if(i < toArchive.size()) fprintf(writeFile, "%c", ' ');
    }

    cout << endl;

    fclose(readFile);
    fclose(writeFile);

    return 0;
}