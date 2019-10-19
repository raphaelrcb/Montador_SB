#include <string>
#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <cstdlib> 
#include <bits/stdc++.h> 

#define ADD     1
#define SUB     2
#define MULT    3
#define DIV     4
#define JMP     5
#define JMPN    6
#define JMPP    7
#define JMPZ    8
#define COPY    9
#define LOAD    10
#define STORE   11
#define INPUT   12
#define OUTPUT  13
#define STOP    14


std::vector<int> Get_memory(std::ifstream & file);

class memory_position
{
private:
    /* data */
public:
    memory_position(/* args */);
    ~memory_position();
    int position;
    int conteudo;

};

void System_Print(int, bool, memory_position);

memory_position::memory_position(/* args */)
{
}

memory_position::~memory_position()
{
}


int main(int argc, char const *argv[])
{
    // ------------------------------------- variáveis
   
    std::string file_name = argv[1];
   
    int pc = 0;//program counter, é incrementado a cada instrução;
   
    int acc = INT_MIN; //começa acumulador com valor mínimo para guncionar como "vazio"
   
    bool sai = false;   //flag que indica que o programa acabou
   
    std::vector< memory_position > var_in_memory; // vetor de variáveis em memória, para guardar posição na memória e conteúdo da variável

    memory_position input;//variável auxiliar para receber um input e adicioná-lo ao vetor de variáveis na memória
    memory_position dado;
   
    std::vector<int> saida;

    std::ifstream obj_file;

   
    //------------------------------------------------

    obj_file.open(file_name.c_str(), std::ifstream::in);//abre arquivo para leitura

    std::vector< int > memory = Get_memory(obj_file);//variável que funciona como a memória do computador, guardando as instruções do código objeto

    for (unsigned int i = 0; memory[i] != STOP;)
    {  
        // pc = i + 1;//pc para um antes do STOP, portanto pc + 1 dá a posição do stop
        switch (memory[i])
        {
        case COPY:
            i+=3;
            // pc = i+1;
            break;

        case STOP:
            pc = i+1;
            break;
        
        default:
            i+=2;
            // pc = i +1;
            break;
        }
        pc = i+1;
        // std::cout << i << std::endl;
    }
    // std::cout << "pc "<< pc << std::endl;
    
    if ((unsigned)pc < memory.size() )
    {

        for (unsigned int i = pc; i < memory.size(); i++)//i 'inicializado como pc+1 pois pc guarda stop e pc+1 é a instrução (dado) seguinte
        {
            dado.position = i;
            dado.conteudo = memory[i];
            var_in_memory.push_back(dado);   
        }
    }
    pc = 0;

    // for (unsigned int i = 0; i < var_in_memory.size(); i++)
    // {
    //     std::cout << "conteúdo " << var_in_memory[i].conteudo << " posição" << var_in_memory[i].position << std::endl;
    // }

    // while (getchar() != '\n' );

    while (sai != true)
    {
    std::cout << "\n\n\n\n\n" << std::endl;
    
        switch (memory[pc])
        {
        case ADD:
            std::cout << "ADD" << std::endl;

            for (unsigned int i = 0; i < var_in_memory.size(); i++)
            {
                if (memory[pc+1] == var_in_memory[i].position )
                {
                    acc = acc + var_in_memory[i].conteudo;
                }
            }

            System_Print(acc, false, input);
            pc+=2;
            break;

        case SUB:
            std::cout << "SUB" << std::endl;

            for (unsigned int i = 0; i < var_in_memory.size(); i++)
            {
                if (memory[pc+1] == var_in_memory[i].position )
                {
                    acc = acc - var_in_memory[i].conteudo;
                }
            }

            System_Print(acc, false, input);
            pc+=2;
            break;

        case MULT:
            std::cout << "MULT" << std::endl;

            for (unsigned int i = 0; i < var_in_memory.size(); i++)
            {
                if (memory[pc+1] == var_in_memory[i].position )
                {
                    acc = acc * var_in_memory[i].conteudo;
                }
            }

            System_Print(acc, false, input);
            pc+=2;
            break;
        
        case DIV:
            std::cout << "DIV" << std::endl;

            for (unsigned int i = 0; i < var_in_memory.size(); i++)
            {
                if (memory[pc+1] == var_in_memory[i].position )
                {
                    acc = acc / var_in_memory[i].conteudo;
                }
            }

            System_Print(acc, false, input);
            pc+=2;
            break;

        case JMP:
            std::cout << "JMP" << std::endl;
            // pc+=2;
            pc = memory[pc+1];
            System_Print(acc, false, input);
            break;
        
        case JMPN:
            std::cout << "JMPN" << std::endl;
            // pc+=2;

            if (acc < 0 && acc != INT_MIN)
            {
                pc = memory[pc+1];
            }
            else
            {
                pc += 2;
            }
            
            System_Print(acc, false, input);            
            break;
        
        case JMPP:
            std::cout << "JMPP" << std::endl;
            // pc+=2;

            if (acc > 0)
            {
                pc = memory[pc+1];
            }
            else
            {
                pc += 2;
            }
            System_Print(acc, false, input);
            break;

        case JMPZ:
            std::cout << "JMPP" << std::endl;
            // pc+=2;

            if (acc == 0)
            {
                pc = memory[pc+1];
            }
            else
            {
                pc += 2;
            }
            System_Print(acc, false, input);
            break;


        case COPY:
            std::cout << "COPY" << std::endl;
            for (unsigned int i = 0; i < var_in_memory.size(); i++)
            {
                if (var_in_memory[i].position == memory[pc+1] )
                {
                    for (unsigned int j = 0; j < var_in_memory.size(); j++)
                    {
                        if (var_in_memory[j].position == memory[pc+2] )
                        {
                            var_in_memory[j].conteudo = var_in_memory[i].conteudo;
                            input.conteudo = var_in_memory[j].conteudo;
                            input.position = var_in_memory[j].position;
                        }
                    }
                    
                }
                
            }
            System_Print(acc, true, input);
            
            pc+=3;
            break;
        
        case LOAD:
            std::cout << "LOAD" << std::endl;
            
            for (unsigned int i = 0; i < var_in_memory.size(); i++)
            {
                if (memory[pc+1] == var_in_memory[i].position )
                {
                    acc = var_in_memory[i].conteudo;
                }
            }

            System_Print(acc, false, input);
            pc+=2;

            break;

        case STORE:
            std::cout << "STORE" << std::endl;

            for (unsigned int i = 0; i < var_in_memory.size(); i++)
            {
                if (var_in_memory[i].position == memory[pc+1])
                {
                    var_in_memory[i].conteudo = acc;
                    input.conteudo = var_in_memory[i].conteudo;
                    input.position = var_in_memory[i].position;
                }
                
            }
            System_Print(acc, true, input);
            pc+=2;
            break;

        case INPUT:

            std::cout << "Insira um valor numérico" << std::endl;
            std::cin >> input.conteudo;
            input.position = memory[pc+1];
            pc += 2;
            for (unsigned int i = 0; i < var_in_memory.size(); i++)
            {
                if (input.position == var_in_memory[i].position)
                {
                    var_in_memory[i].conteudo = input.conteudo;
                }
                
            }
            // std::cout << "posição na memória: " << input.position << " ------ conteúdo da memória: " << input.conteudo << std::endl;
            // var_in_memory.push_back(input);
            System_Print(acc, true, input);

            break;

        case OUTPUT:
            std::cout << "O valor de saı́da é: ";
            for (unsigned int i = 0; i < var_in_memory.size(); i++)
            {
                if (var_in_memory[i].position == memory[pc+1])
                {
                    std::cout << var_in_memory[i].conteudo << std::endl;
                    saida.push_back(var_in_memory[i].conteudo);
                }
                
            }
            System_Print(acc, false, input);
            pc+=2;
            break;

        case STOP:
            std::cout << "STOP" << std::endl;
            System_Print(acc, false, input);
            pc+=1;            
            sai = true;
            break;
        
        default:
            break;
        }
    
        // while (getchar() != '\n' );
    }

    std::cout << "Histórico de saída: " << std::endl;
    for (unsigned int i = 0; i < saida.size(); i++)
    {
        std::cout << saida[i] << ", ";
    }
    std::cout << std::endl;
    obj_file.close();

    return 0;
}

std::vector< int > Get_memory(std::ifstream & file)
{
    std::vector< int > memory;
    std::vector< std::string > memory_string;
    std::string obj_conteudo;//string que vai guardar o conteúdo que está no arquivo objeto

    std::getline(file, obj_conteudo);

    char conteudo[obj_conteudo.size()];
    strcpy(conteudo, obj_conteudo.c_str());

    char * tokens = strtok( conteudo, " " );

    while (tokens != NULL) //separa a string em tokens 
    {
        // std::cout << tokens << '\n';
        memory.push_back(std::atoi(tokens));
        tokens = strtok(NULL, " ");
    }

    return memory;
}

void System_Print(int acc, bool memoria_modificada, memory_position modified)
{
    if (acc == INT_MIN)
    {
        std::cout << "ACC VAZIO " << std::endl;
    }
    else
    {
        std::cout << "ACC = " << acc << std::endl;
    }

    if (memoria_modificada)
    { 
        std::cout << "VARIÁVEL MODIFICADA" << std::endl;    
        std::cout << "ENDEREÇO: " << modified.position << std::endl;    
        std::cout << "CONTEÚDO: " << modified.conteudo << std::endl;    
    }
    
}