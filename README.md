# Trabalho 1 - Montador de Passagem Única
Este trabalho foi desenvolvido pelos alunos 

**Mateus Freitas - 16/0137519** 

**Raphael Rodrigues - 14/0160281**

 para a matéria de Software Básico, turma B, do Departamento de Ciências de Computação na Universidade de Brasília

### Introdução 

  O trabalho consiste em implementar em C/C++ um método de tradução de uma linguagem de montagem simples para uma representação de código objeto. O tradutor a ser implementado será um Assembler da linguagem hipotética vista em sala de aula.

### Compilação

   O código foi desenvolvido no ambiente linux, utilizando o SO UBUNTU.
   Para a compilação do código foi usado o compilador g++, sendo que são dois códigos à serem compilados, o montador.cpp e o simulador.cpp.
     
  Para a compilação do simulador.cpp, utiliza-se o seguinte comando no terminal:

  `g++ -Wall -o simulador simulador.cpp`
    
  Enquando para a compilação do montador.cpp, utiliza-se o seguinte comando no terminal:

  `g++ -Wall -o montador montador.cpp`

  Caso o seu computador não possua suporte para o c++11 (ocorre com versões mais antigas do UBUNTU), adicione a seguinte diretiva de compilação ao comando dado acima:

  `-std=c++11`

### Execução

  O código tanto do montador quanto do simulador pedem que seja passado na hora da execução o nome de um arquivo, sendo sua extensão, respectivamente para o montador e simulador, ".asm" e ".obj". Logo, para a execução dos códigos utilizam-se os seguintes comandos no terminal:

  `./montador [nome_do_arquivo].asm`

  e 

   `./simullador [nome_do_arquivo].obj`
