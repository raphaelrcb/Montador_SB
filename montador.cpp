#include <stdio.h>
#include <iostream>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <vector>
#include <sstream>

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
    bool def, jmpble, ext = false;
    int end;
    TabSim_Node* next;
    Pend_Node* pendHead;
};

class TabelaSim {
public:
    TabSim_Node *head, *tail;

    TabelaSim() {
        this->head = NULL;
        this->tail = NULL;
    }
    ~TabelaSim(){}
    
    void addSimbSemPend(string simb, int end, bool jmpble, bool ext = false) {
        TabSim_Node* new_Simb = new TabSim_Node();
        new_Simb->simb = simb;
        new_Simb->def = true;
        new_Simb->end = end;
        new_Simb->jmpble = jmpble;
        new_Simb->next = NULL;
        new_Simb->ext = ext;
        if(this->head == NULL) {this->head = new_Simb; this->tail = new_Simb;}
        else {this->tail->next = new_Simb; this->tail = new_Simb;}
        new_Simb->pendHead = new Pend_Node();
        new_Simb->pendHead->end = -1;
        new_Simb->pendHead->next = NULL;
    }

    void addSimbComPend(string simb, int end, bool jmpble) {
        TabSim_Node* new_Simb = new TabSim_Node();
        new_Simb->simb = simb;
        new_Simb->def = false;
        new_Simb->end = -1;
        new_Simb->jmpble = jmpble;
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

    void addPend(TabSim_Node* simbNode, int end, int gambiarra = 0) {
        Pend_Node* new_Pend = new Pend_Node();
        new_Pend->end = end;
        // new_Pend->end = end+gambiarra;
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
            // if (simbNode->simb == "N"){
            //     std::cout << simbNode->simb << ", " << simbNode->end << ", " << pendAtual->end  << ", " << newEnd << std::endl;
            // }
            // if (pendAtual->end == simbNode->end){
            //     cout << "algo" << endl;
            // }            
            // if ((unsigned)pendAtual->end >= toArchive.size()){
            //     cout << "algo" << endl;
            //     if(toArchive.at(pendAtual->end-1) == -1) toArchive.at(pendAtual->end-1) = simbNode->end;
            //     else toArchive.at(pendAtual->end-2) += simbNode->end;
            // }
            // else {
                if(toArchive.at(pendAtual->end) == -1) toArchive.at(pendAtual->end) = simbNode->end;
                else toArchive.at(pendAtual->end) += simbNode->end;
            // }
            pendAtual = pendAtual->next;
        }
        return toArchive;
    }

    void print() {
        TabSim_Node* olho_Simb = this->head;
        Pend_Node* olho_Pend = olho_Simb->pendHead;
        cout << "Simb\t\tEnd\t\tDef\tPend\text\n";
        while(olho_Simb != NULL) {
            if(olho_Simb->simb.length() > 7) cout << olho_Simb->simb << "\t" << olho_Simb->end << "\t\t" << olho_Simb->def << "\t" << olho_Simb->ext << "\t";
            else cout << olho_Simb->simb << "\t\t" << olho_Simb->end << "\t\t" << olho_Simb->def << "\t"<< olho_Simb->ext << "\t";
            while(olho_Pend != NULL) {
                cout << olho_Pend->end << ',';
                olho_Pend = olho_Pend->next;
            }
            cout << endl;
            olho_Simb = olho_Simb->next;
            if(olho_Simb != NULL) olho_Pend = olho_Simb->pendHead;
        }
    }

    void Check_Def() {
        TabSim_Node* olho_Simb = this->head;
        while (olho_Simb != NULL)
        {
            if (!olho_Simb->def)
            {
                std::cout << "ERRO SINTÁTICO - Definição de  " << olho_Simb->simb << " ausente!" << std::endl;
            }
            
            olho_Simb = olho_Simb->next;            
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

class TabUso_Node {
public:
    string simb;
    int offs;
    TabUso_Node* next;
};

class TabelaUso {
public:
    TabUso_Node *head, *tail;

    TabelaUso() {
        this->head = NULL;
        this->tail = NULL;
    }
    ~TabelaUso(){}
    
    void addSimb(string simb, int offs) {
        TabUso_Node* new_Simb = new TabUso_Node();
        new_Simb->simb = simb;
        new_Simb->offs = offs;    
        if(this->head == NULL) {this->head = new_Simb; this->tail = new_Simb;}
        else {this->tail->next = new_Simb; this->tail = new_Simb;}   
    }


    void print() {
        TabUso_Node* olho_Uso = this->head;
        cout << "Simb\t\tOffs\n";
        while(olho_Uso != NULL) {
            cout << olho_Uso->simb << "\t\t" << olho_Uso->offs << "+" << "\t";
            cout << endl;
            olho_Uso = olho_Uso->next;
        }
        std::cout << std::endl;
    }

    TabUso_Node* find(string simb) {
        TabUso_Node* olho = this->head;
        while(olho != NULL) {
            if(simb == olho->simb) {
                return olho;
            }
            olho = olho->next;
        }
        return NULL;
    }

    void addVal(string simb, int val){
    }
};

class TabDef_Node {
public:
    string simb;
    int val;
    TabDef_Node* next;
};

class TabelaDef {
public:
    TabDef_Node *head, *tail;

    TabelaDef() {
        this->head = NULL;
        this->tail = NULL;
    }
    ~TabelaDef(){}
    
    void addSimb(string simb) {
        TabDef_Node* new_Simb = new TabDef_Node();
        new_Simb->simb = simb;
        // new_Simb->val = val;    
        if(this->head == NULL) {this->head = new_Simb; this->tail = new_Simb;}
        else {this->tail->next = new_Simb; this->tail = new_Simb;}   
    }


    void print() {
        TabDef_Node* olho_Def = this->head;
        cout << "Simb\t\tVal\n";
        while(olho_Def != NULL) {
            cout << olho_Def->simb << "\t\t" << olho_Def->val << "\t";
            cout << endl;
            olho_Def = olho_Def->next;
        }
    }

    TabDef_Node* find(string simb) {
        TabDef_Node* olho = this->head;
        while(olho != NULL) {
            if(simb == olho->simb) {
                return olho;
            }
            olho = olho->next;
        }
        return NULL;
    }

    void addVal(string simb, int val){
        // TabDef_Node* olho = this->head;
        TabDef_Node* new_Val;
        new_Val = find(simb);
        if (new_Val == NULL)
            std::cout << "símbolo não existe, impossível atribuir valor" << std::endl;
        else
            new_Val->val = val;
    }
};

int ConverteHex(std::string &s){
    int numero;
    std::stringstream ajuda;

    if(s.find("0x") != std::string::npos){
        if(s.find("-") != std::string::npos){
            s= s.replace(1,2,"");
        }else{
            s = s.replace(0, 2, "");
        }
        ajuda << std::hex << s;
        ajuda >> numero;
        return numero;
    }

    if(!(std::istringstream(s) >> numero)){
        numero = 0;
    }
    return numero;
}

string PreProcess(string arq) {
    FILE *readFile, *writeFile;
    TabelaSimbPre preSimb;
    TabSimPre_Node* label_Node;

    readFile = fopen(arq.c_str(), "r");
    char inputChar;
    int val;
    string to_Archive, inputStr, label, dir, aux, outputFile = arq;
    outputFile.erase(outputFile.end()-4, outputFile.end());
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
            for(unsigned int i = 0; i < p_String.length(); i++) {
                p_String[i] = toupper(p_String[i]);
            }

            if (iter == 0) {
                label = p_String;
                if(p_String == "STOP" || p_String == "SPACE" || p_String == "CONST") to_Archive = p_String + '\n';
                else if(label.find(':') != string::npos) to_Archive = p_String + ' ';
                else if(label.find(':') == string::npos && p_String != "IF") to_Archive = p_String + ' ';
            }
            else if (iter == 1) {
                if(label.find(':') != string::npos) {
                    dir = p_String;
                    if(dir != "EQU") to_Archive = label + ' ' + dir + '\n';
                    else to_Archive = "";
                    label = label.substr(0,label.find(':'));
                }
                else if (label == "IF") {
                    label_Node = preSimb.find(p_String);
                    if (label_Node == NULL) {
                        cout << "< ERRO SINTÁTICO > '" << p_String << "' não encontrado" << endl << endl;
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
                else if(label == "SPACE" || label == "CONST") {
                    to_Archive = to_Archive.substr(0,to_Archive.find('\n'));
                    to_Archive = to_Archive + ' ' + p_String + '\n';
                }
                else {
                    to_Archive = to_Archive + p_String + '\n';
                }
            }
            else if (iter == 2) {

                if(p_String.find('X') == string::npos) val = atoi(p_String.c_str());
                else {
                    for(unsigned int i = 0; i < p_String.length(); i++) {
                        p_String[i] = tolower(p_String[i]);
                    }
                }

                if(dir != "EQU") {
                    to_Archive = to_Archive.substr(0,to_Archive.find('\n'));
                    if(dir == "COPY") to_Archive = to_Archive + ' ' + p_String;
                    else if(label == "COPY") to_Archive = to_Archive + ',' + p_String + '\n';
                    else to_Archive = to_Archive + ' ' + p_String + '\n';
                }
                if(dir == "EQU") {
                    preSimb.add(label,dir,val);
                }
            }
            else if (iter == 3) {
                if(dir == "COPY") to_Archive = to_Archive + ',' + p_String + '\n';
            }

            p = strtok(NULL, " \t,");
            iter++;
        }

        if(inputChar == EOF) to_Archive = to_Archive.substr(0,to_Archive.find('\n'));

        fwrite(to_Archive.c_str(), sizeof(char), to_Archive.length(), writeFile);

    }

    fclose(readFile);
    fclose(writeFile);
    preSimb.~TabelaSimbPre();

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
        tabela.add("BEGIN"  ,  1, -1,  0);
        tabela.add("END"    ,  1, -1,  0);
        tabela.add("EXTERN" ,  1, -1,  0);
        tabela.add("PUBLIC" ,  1, -1,  0);
    }

    return tabela;
}

bool verify_token(std::string token) 
{
    // std::cout << "verify" << std::endl;
    char num = '0';
    bool error = false;

    if ((token.find("!") != std::string::npos) || (token.find("@") != std::string::npos) || 
        (token.find("#") != std::string::npos) || (token.find("$") != std::string::npos) || 
        (token.find("%") != std::string::npos) || (token.find("&") != std::string::npos) || 
        (token.find("*") != std::string::npos) || (token.find("(") != std::string::npos) || 
        (token.find(")") != std::string::npos) || (token.find("-") != std::string::npos) || 
        (token.find("=") != std::string::npos) || (token.find("{") != std::string::npos) || 
        (token.find("}") != std::string::npos) || (token.find("[") != std::string::npos) || 
        (token.find("]") != std::string::npos) || (token.find("~") != std::string::npos) || 
        (token.find("^") != std::string::npos) || (token.find(";") != std::string::npos) || 
        (token.find(".") != std::string::npos) || (token.find("<") != std::string::npos) || 
        (token.find(">") != std::string::npos) || (token.find("?") != std::string::npos) || 
        (token.find("/") != std::string::npos) || (token.find("|") != std::string::npos) || 
        (token.find("\"") != std::string::npos) || (token.find("\'") != std::string::npos) )
    {
        error = true;
    }

    if ( token.find_first_not_of("0123456789") != std::string::npos && token.find("0x") == std::string::npos) //se existir um caracter diferente de número, é uma instrução/diretiva/operador/label
    {                                                                //se for uma sequência apenas numérica é um const ou um vetor (space)
        for (int i = 0; i < 10; i++)
        {
            num = i + '0';
            if (token.find(num) == 0)//se uma instrução/diretiva/operador/label começa com número, é erro léxico
                error = true;
        }
        
    }
    
    return error;
}

int verify_line(std::string line, int linha) 
{
    std::vector < std::string> token;
    // char line_char[line.size()];
    // string line_str;
    // line_str = line;
    // strcpy(line_char, line.c_str());
    
    char * tok = strtok(strdupa(line.c_str()), " ," );

    while (tok != NULL) //separa a string em tokens
    {
        // std::cout << tokens << '\n';
        token.push_back(tok);
        tok = strtok(NULL, " ,");
    }

    for (size_t i = 0; i < token.size(); i++)
    {            
        if(verify_token(token[i]))//para cada token verifica se tem erro léxico
            std::cout << "ERRO LEXICO NA LINHA:" << linha << std::endl;
    }
    return linha;
}

int main(int argc, char const *argv[]) {
    
    if(argv[1] == NULL) {
        cout << "Arquivo de entrada não fornecido !\n";
        return 0;
    }

    for (int mod = 1; mod < argc ; mod++)
    {

        std::cout << "--------------------------------------------------------" << std::endl;        
        vector<int> toArchiveText, toArchiveData, linha, desloc_Vec, simbSpace, linhaJump, linhaDiv, linhaMod, constValues;
        vector<string> label_Vec, simb, destJumps, divs, labelsConst, modConst;

        int countEnd = 0, countLinha = 1, section = 0;
        bool section_text = false;
        int pulo_Vetor;
        char inputChar;
        int EndOffset = 0;
        bool Data_Before_Text = false;
        int text_end = 0;
        vector<int> Fix_Offset_At;
        string inputStr, label_Vetor;
        string arq_PreProcess = PreProcess(argv[mod]);

        Tabela tabela_Inst = CriaTabela("instrucoes");
        Tabela tabela_Dir = CriaTabela("diretivas");
        Tabela_Node *instNode1, *instNode2, *dirNode;
        TabelaSim tabela_Simb;
        TabSim_Node* simbNode;
        TabelaDef tabela_Def;
        TabDef_Node* defNode;
        TabelaUso tabela_Uso;
        int begin = -1;
        int end = -1;
        // TabUso_Node* usoNode;
        // cout << "aaaaaaaaaaaaaaaaaaaa" << endl;
        FILE* readFile = fopen(arq_PreProcess.c_str(), "r");
        string outputFile = argv[mod];
        outputFile.erase (outputFile.end()-4, outputFile.end());
        outputFile.append(".obj");
        FILE* writeFile = fopen(outputFile.c_str(), "w");

        while(!feof(readFile)) {
            inputStr = "";
            while((inputChar = getc(readFile)) != EOF && inputChar != '\n') {
                inputStr+=inputChar;
            }
            verify_line(inputStr, countLinha);
            int iter = 0;
            char *p = strtok(strdupa(inputStr.c_str()), " ,");

            while(p != NULL) {

                string p_String = p;

                if(iter == 0) { // Se for a primeira palavra da linha
                    if(p_String.find(':') != string::npos) {
                        bool ext = false;
                        if (p_String.rfind(':') != p_String.find(':'))
                        {
                            std::cout << "ERRO SINTÁTICO - dupla declaração de rótulo na linha " << countLinha << std::endl;
                        }
                        instNode1 = NULL;
                        p_String = p_String.substr(0,p_String.find(':'));
                        simb.push_back(p_String);
                        labelsConst.push_back(p_String);
                        simbNode = tabela_Simb.find(p_String);
                        if (inputStr.find("BEGIN") != std::string::npos){
                            p_String = p_String.substr(0,p_String.find(':'));
                            simb.push_back(p_String);
                            labelsConst.push_back(p_String);
                            simbNode = tabela_Simb.find(p_String);
                            tabela_Simb.addSimbSemPend(p_String, countEnd, true);
                            begin = countEnd;
                        }
                        if (inputStr.find("EXTERN") != std::string::npos)
                            ext = true;
                        if(simbNode != NULL) {
                            if(!simbNode->def) {
                                toArchiveText = tabela_Simb.resolvePend(simbNode, countEnd, toArchiveText);
                            }
                            else cout << " ERRO SINTÁTICO - Label já definida !!! ( Linha " << countLinha << " ) " << endl;
                        }
                        else { // se label n foi mencionada ainda
                                if(section == 1) tabela_Simb.addSimbSemPend(p_String, countEnd, true, ext);
                                else if(section == 2) tabela_Simb.addSimbSemPend(p_String, countEnd, false, ext);
                        }
                    }
                    else {
                        if(p_String == "SECTION") {
                            p = strtok(NULL, " ,");
                            p_String = p;
                            if(p_String == "TEXT") {
                                section = 1;
                                section_text = true;
                                text_end = countEnd;
                            } else if(p_String == "DATA") {
                                if (section_text == false) Data_Before_Text = true;
                                else Data_Before_Text = false;
                                section = 2;
                            }
                            else {
                                cout << "< ERRO SINTÁTICO - Section inválida '" << p_String << "' ( Linha " << countLinha << " ) >" << endl;
                                section = 0;
                            }
                        }
                        else if(p_String == "PUBLIC") {
                            p = strtok(NULL, " ,");
                            p_String = p;
                            defNode = tabela_Def.find(p_String);
                            if (defNode == NULL)
                            {
                                tabela_Def.addSimb(p_String);
                            }
                        }
                        else if (p_String == "END"){
                            end = countEnd - 1;
                        }
                        else {
                            instNode1 = tabela_Inst.find(p);
                            if(instNode1 != NULL) { // Se achou a instrução na tabela
                                if(section == 0) section = 1;
                                toArchiveText.push_back(instNode1->opcode);
                                countEnd += instNode1->size;
                                if (instNode1->opcode == 14 && Data_Before_Text == true) EndOffset = countEnd;
                                if (section != 1){
                                    std::cout << "ERRO SINTÁTICO- Instrução na Seção errada! linha: " << countLinha << std::endl;
                                }
                            }
                            else {
                                cout << "! Instrução não encontrada ('" << p << "'). ERRO SINTÁTICO(linha " << countLinha << ") !" << endl; 
                                break; // Vai pra próxima linha    
                            }
                        }
                    }
                }
                else if(iter == 1) { // // Se for a segunda palavra da linha
                    if(instNode1 != NULL) { // Se a instrução for a PRIMEIRA palavra
                        instNode2 = NULL;
                        if(p_String.find('+') != string::npos) {
                            label_Vetor = p_String.substr(0,p_String.find('+'));
                            label_Vec.push_back(label_Vetor);
                            pulo_Vetor = stoi(p_String.substr(p_String.find('+')));
                            desloc_Vec.push_back(pulo_Vetor);
                            linha.push_back(countLinha);
                            simbNode = tabela_Simb.find(label_Vetor);
                            if (simbNode != NULL) {
                                if(!simbNode->def) {
                                    tabela_Simb.addPend(simbNode, countEnd - (instNode1->size - iter));
                                    toArchiveText.push_back(pulo_Vetor);
                                }
                                if(simbNode->ext){
                                    tabela_Uso.addSimb(simbNode->simb, countEnd);
                                }
                                else{
                                    toArchiveText.push_back(simbNode->end + pulo_Vetor);
                                    if (Data_Before_Text) Fix_Offset_At.push_back(countEnd - text_end);
                                } 
                            }
                            else {
                                tabela_Simb.addSimbComPend(p, countEnd - (instNode1->size - iter), false);
                                toArchiveText.push_back(pulo_Vetor);
                            }
                        }
                        else {
                            if(instNode1->name == "JMP" || instNode1->name == "JMPN" || instNode1->name == "JMPP" || instNode1->name == "JMPZ") {
                                    destJumps.push_back(p_String);
                                    linhaJump.push_back(countLinha);
                            }
                            else if(instNode1->name == "DIV") {
                                divs.push_back(p_String);
                                linhaDiv.push_back(countLinha);
                            }
                            else if (instNode1->name == "STORE") {
                                modConst.push_back(p_String);
                                linhaMod.push_back(countLinha);
                            }
                            simbNode = tabela_Simb.find(p_String);
                            if (simbNode != NULL) {
                                if(simbNode->ext){
                                    tabela_Uso.addSimb(simbNode->simb, countEnd);
                                }
                                // if(instNode1->name == "ADD" || instNode1->name == "SUB" || instNode1->name == "MULT" || instNode1->name == "DIV" || instNode1->name == "COPY" || instNode1->name == "LOAD" || instNode1->name == "STORE" || instNode1->name == "INPUT" || instNode1->name == "OUTPUT") {
                                //     if(simbNode->jmpble == true) {
                                //         cout << " < ERRO SEMANTICO - Instrução com tipo de operando inválido ( linha " << countLinha << " ) >" << endl;
                                //         break;
                                //     }
                                // }
                                // else if(instNode1->name == "JMP" || instNode1->name == "JMPP" || instNode1->name == "JMPN" || instNode1->name == "JMPZ") {
                                //     if(simbNode->jmpble == false) {
                                //         cout << " < ERRO SEMANTICO- Instrução com tipo de operando inválido ( linha " << countLinha << " ) >" << endl;
                                //         break;
                                //     }
                                // }
                                if(!simbNode->def) {
                                    tabela_Simb.addPend(simbNode, countEnd - (instNode1->size - iter));
                                    toArchiveText.push_back(-1);
                                }
                                else {
                                    toArchiveText.push_back(simbNode->end);
                                    if (Data_Before_Text) Fix_Offset_At.push_back(countEnd - text_end);
                                }
                            }
                            else {
                                tabela_Simb.addSimbComPend(p, countEnd - (instNode1->size - iter), false);
                                toArchiveText.push_back(-1);
                            }
                        }
                    }
                    else {
                        dirNode = tabela_Dir.find(p);
                        instNode2 = tabela_Inst.find(p);
                        if(dirNode != NULL && dirNode->name != "EXTERN" && dirNode->name != "BEGIN") {
                            // if (section != 2){
                            //     std::cout << "ERRO SINTÁTICO - Diretiva na Seção errada! linha: " << countLinha << std::endl;
                            // }
                            if(section == 0) section = 2;
                            if(dirNode->name == "SPACE") {
                                toArchiveData.push_back(0);
                                simbSpace.push_back(1);
                                labelsConst.pop_back();
                            } 
                            else {
                                simb.pop_back();
                            }
                            countEnd++;
                        }
                        else if(instNode2 != NULL) {
                            if(section == 0) section = 1;
                            simb.pop_back();
                            labelsConst.pop_back();
                            toArchiveText.push_back(instNode2->opcode);
                            countEnd += instNode2->size;
                            if (section != 1){
                                    std::cout << "ERRO SINTÁTICO- Instrução na Seção errada! linha: " << countLinha << std::endl;
                            }
                        }
                        else {
                            if (dirNode->name != "EXTERN" && dirNode->name != "BEGIN") 
                                cout << "< ERRO SINTÁTICO - Instrução/Diretiva inválida '" << p_String << "' ( Linha " << countLinha << " ) >" << endl;
                            break; // vai pra próxima linha
                        }
                    }
                }
                else if(iter == 2) { // Se for a terceira palavra da linha
                    if(dirNode != NULL) {
                        if(dirNode->name == "SPACE") {
                            for(int i = 1; i < atoi(p); i++) {
                                toArchiveData.push_back(0);
                            }
                            simbSpace.pop_back();
                            simbSpace.push_back(atoi(p));
                            countEnd += atoi(p) - 1;
                        } else {
                            int convertido = ConverteHex(p_String);
                            toArchiveData.push_back(convertido);
                            constValues.push_back(convertido);
                        }
                    }
                    else if(instNode2 != NULL || (instNode1 != NULL && instNode1->name == "COPY")) { // Se a instrução for a SEGUNDA palavra
                        if(p_String.find('+') != string::npos) {
                            label_Vetor = p_String.substr(0,p_String.find('+'));
                            label_Vec.push_back(label_Vetor);
                            pulo_Vetor = stoi(p_String.substr(p_String.find('+')));
                            desloc_Vec.push_back(pulo_Vetor);
                            linha.push_back(countLinha);
                            if (simbNode != NULL) {
                                if(!simbNode->def) {
                                    tabela_Simb.addPend(simbNode, countEnd - (instNode1->size - iter));
                                    toArchiveText.push_back(pulo_Vetor);
                                }
                                else {
                                        toArchiveText.push_back(simbNode->end + pulo_Vetor);
                                        if (Data_Before_Text) Fix_Offset_At.push_back(countEnd - text_end);
                                    }
                            }
                            else {
                                tabela_Simb.addSimbComPend(p, countEnd - (instNode1->size - iter), false);
                                toArchiveText.push_back(pulo_Vetor);
                            }
                        }
                        else {
                            if(instNode2 != NULL && (instNode2->name == "JMP" || instNode2->name == "JMPN" || instNode2->name == "JMPP" || instNode2->name == "JMPZ")) {
                                destJumps.push_back(p_String);
                                linhaJump.push_back(countLinha);
                            }
                            else if(instNode2 != NULL && instNode2->name == "DIV") {
                                divs.push_back(p_String);
                                linhaDiv.push_back(countLinha);
                            }
                            else if((instNode2 != NULL && instNode2->name == "STORE") || (instNode1 != NULL && instNode1->name == "COPY")) {
                                modConst.push_back(p_String);
                                linhaMod.push_back(countLinha);
                            }
                            simbNode = tabela_Simb.find(p_String);
                            if(simbNode != NULL) {
                                if(simbNode->ext){
                                    tabela_Uso.addSimb(simbNode->simb, countEnd);
                                }
                                if(instNode2 != NULL && (instNode2->name == "ADD" || instNode2->name == "SUB" || instNode2->name == "MULT" || instNode2->name == "DIV" || instNode2->name == "COPY" || instNode2->name == "LOAD" || instNode2->name == "STORE" || instNode2->name == "INPUT" || instNode2->name == "OUTPUT")) {
                                    if(simbNode->jmpble == true) {
                                        cout << " < ERRO SEMANTICO- Instrução com tipo de operando inválido ( linha " << countLinha << " ) >" << endl;
                                        break;
                                    }
                                }
                                else if(instNode2 != NULL && (instNode2->name == "JMP" || instNode2->name == "JMPP" || instNode2->name == "JMPN" || instNode2->name == "JMPZ")) {
                                    if(simbNode->jmpble == false) {
                                        cout << " < ERRO SEMANtiCO- Instrução com tipo de operando inválido ( linha " << countLinha << " ) >" << endl;
                                        break;
                                    }
                                }
                                else if(instNode1 != NULL  && instNode1->name == "COPY") {
                                    if(simbNode->jmpble == true) {
                                        cout << " < ERRO SEMANTICO- Instrução com tipo de operando inválido ( linha " << countLinha << " ) >" << endl;
                                        break;
                                    }
                                }

                                if(!simbNode->def) {
                                    // cout << " asssadsadas " << p_String << "    " << countEnd << endl; 
                                    if(instNode1 != NULL && instNode1->name == "COPY") tabela_Simb.addPend(simbNode, countEnd - (instNode1->size - iter));
                                    else {tabela_Simb.addPend(simbNode, countEnd - (instNode2->size - iter), 1);
                                        // cout << " addpend " << simbNode->simb << countEnd - (instNode2->size - iter -1)  << endl;                                
                                    }
                                    toArchiveText.push_back(-1);
                                }
                                else {
                                    toArchiveText.push_back(simbNode->end);
                                    if (Data_Before_Text){
                                        if(instNode1 != NULL && instNode1->name == "COPY") Fix_Offset_At.push_back(countEnd -1 - text_end); 
                                        else Fix_Offset_At.push_back(countEnd - text_end);
                                    } 
                                }
                            }
                            else {
                                if(instNode1 != NULL && instNode1->name == "COPY") tabela_Simb.addSimbComPend(p, countEnd - (instNode1->size - iter), false);
                                else tabela_Simb.addSimbComPend(p, countEnd - 1, false);
                                toArchiveText.push_back(-1);
                            }
                        }
                    }
                    else {
                        cout << " < ERRO SINTÁTICO- Instrução com quantidade de operandos inválida ( linha " << countLinha << " ) >" << endl;
                        break; // vai pra próxima linha
                    }
                }
                else if(iter == 3) { // Se for a quarta palavra da linha
                    if(instNode2 != NULL && instNode2->name == "COPY") {
                        if(p_String.find('+') != string::npos) {
                            label_Vetor = p_String.substr(0,p_String.find('+'));
                            label_Vec.push_back(label_Vetor);
                            pulo_Vetor = stoi(p_String.substr(p_String.find('+')));
                            desloc_Vec.push_back(pulo_Vetor);
                            linha.push_back(countLinha);
                            if (simbNode != NULL) {
                                if(!simbNode->def) {
                                    tabela_Simb.addPend(simbNode, countEnd - (instNode1->size - iter));
                                    toArchiveText.push_back(pulo_Vetor);
                                }
                                else toArchiveText.push_back(simbNode->end + pulo_Vetor);
                            }
                            else {
                                tabela_Simb.addSimbComPend(p, countEnd - (instNode1->size - iter), false);
                                toArchiveText.push_back(pulo_Vetor);
                            }
                        }
                        else {
                            modConst.push_back(p_String);
                            linhaMod.push_back(countLinha);
                            simbNode = tabela_Simb.find(p_String);
                            if (simbNode != NULL) {
                                if(simbNode->ext){
                                    tabela_Uso.addSimb(simbNode->simb, countEnd);
                                }
                                if(instNode2 != NULL  && instNode2->name == "COPY") {
                                    if(simbNode->jmpble == true) {
                                        cout << " < ERRO SEMANTICO- Instrução com tipo de operando inválido ( linha " << countLinha << " ) >" << endl;
                                        break;
                                    }
                                }
                                if(!simbNode->def) {
                                    tabela_Simb.addPend(simbNode, countEnd - (instNode2->size - iter));
                                    toArchiveText.push_back(-1);
                                }
                                else {
                                    toArchiveText.push_back(simbNode->end);
                                    if (Data_Before_Text) Fix_Offset_At.push_back(countEnd - text_end);
                                }
                            }
                            else {
                                tabela_Simb.addSimbComPend(p, countEnd - (instNode2->size - iter), false);
                                toArchiveText.push_back(-1);
                            }
                        }
                    } else {
                        cout << " < ERRO SINTÁTICO - Instrução com quantidade de operandos inválida ( linha " << countLinha << " ) >" << endl;
                        break; // vai pra próxima linha
                    }
                }
                        
                iter++;
                p = strtok(NULL, " ,");

            }

            countLinha++;
            
        }

        tabela_Simb.Check_Def();
        if (!section_text){
            std::cout << "ERRO SINTÁTICO - seção TEXT faltante!" << std::endl;
        }

        cout << endl;
        
        cout << endl;

        // for(unsigned int i = 0; i < modConst.size(); i++) {
        //     for (unsigned int j = 0; j < labelsConst.size(); j++) {
        //         if(modConst[i] == labelsConst[j]) {
        //             cout << " < ERRO SEMÂNTICO- Modificação de um valor constante ( linha " << linhaMod[i] << " ) >" << endl;
        //         }
        //     }
        // }

        EndOffset -= text_end;
        for(unsigned int i = 0; i < divs.size(); i++) {
            for (unsigned int j = 0; j < labelsConst.size(); j++) {
                if(divs[i] == labelsConst[j] && constValues[j] == 0) {
                    cout << " < ERRO SEMÂNTICO- Divisão por zero ( linha " << linhaDiv[i] << " ) >" << endl;
                }
            }
        }

        // for (unsigned int i = 0; i < destJumps.size(); i++) {
        //     TabSim_Node* simbNode = tabela_Simb.find(destJumps[i]);
        //     if(simbNode == NULL || simbNode->def == false) {
        //         cout << " < ERRO SEMÂNTICO- Pulo para rótulo não definido ( linha " << linhaJump[i] << " ) >" << endl;
        //     }
        //     else if(simbNode->jmpble == false) {
        //         cout << " < ERRO SEMÂNTICO - Pulo para seção errada ( linha " << linhaJump[i] << " ) >" << endl;
        //     }
        // }

        for(unsigned int i = 0; i < label_Vec.size(); i++) {
            for (unsigned int j = 0; j < simb.size(); j++) {
                if(label_Vec[i] == simb[j] && (desloc_Vec[i] < 0 || desloc_Vec[i] >= simbSpace[j])) {
                    cout << " < ERRO SEMÂNTICO- Acesso de posição não reservada ( linha " << linha[i] << " ) >" << endl;
                }
            }
        }

        TabDef_Node* olho = tabela_Def.head;
        while (olho != NULL)
        {
            // std::cout << olho->simb << std::endl;
            simbNode = tabela_Simb.find(olho->simb);
            if (simbNode != NULL)
                tabela_Def.addVal( simbNode->simb,simbNode->end);
            olho = olho->next;
        }

        tabela_Def.print();
        std::cout << std::endl;
        tabela_Simb.print();
        std::cout << std::endl;
        tabela_Uso.print();
        std::cout << std::endl;
        std::cout << "begin = " << begin << std::endl;
        std::cout << "end = " << end << std::endl;

        if (argc >= 2 && end != -1 && begin != -1 )
        {   
            fprintf(writeFile, "%d", begin);
            fprintf(writeFile, "%c", ' ');
            fprintf(writeFile, "%d", end);
            fprintf(writeFile, "%c", '\n');
        }

        while (getchar()!= '\n');

        cout << "> toArchive =";

        unsigned int i = 0;
        int fix = 0;
        
        if (Data_Before_Text == false){
            while(i < toArchiveText.size()) {
                int num = toArchiveText.at(i);
                cout << ' ' << num;
                fprintf(writeFile, "%d", num);
                i++;
                if(i < toArchiveText.size()) fprintf(writeFile, "%c", ' ');
            }
        } 
        else
        {
            while(i < toArchiveText.size()) {
                int num = toArchiveText.at(i);
                for (size_t j = 0; j < Fix_Offset_At.size(); j++){
                    if ((signed)i+1 == Fix_Offset_At[j]){
                        fix  = 1;
                        break;
                    }
                }
                if (num > text_end && fix == 1){
                    fprintf(writeFile, "%d", num - text_end);
                    cout << ' ' << num - text_end;
                }
                else if (num < text_end && fix == 1) {
                    fprintf(writeFile, "%d", num + EndOffset);  
                    cout << ' ' << num + EndOffset*fix;
                }
                else if (fix == 0){
                    fprintf(writeFile, "%d", num);  
                    cout << ' ' << num;
                }
                i++;
                fix = 0;
                if(i < toArchiveText.size()) fprintf(writeFile, "%c", ' ');
            }       
        }

        i = 0;
        fprintf(writeFile, "%c", ' ');
        while(i < toArchiveData.size()) {
            int num = toArchiveData.at(i);
            cout << ' ' << num;
            fprintf(writeFile, "%d", num);
            i++;
            if(i < toArchiveData.size()) fprintf(writeFile, "%c", ' ');
        }
        cout << endl << endl;    

        fclose(readFile);
        fclose(writeFile);
    }

    return 0;
}
