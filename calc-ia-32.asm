%define  SYS_EXIT   1
%define  SYS_READ   3
%define  SYS_WRITE  4
%define  STDIN      0
%define  STDOUT     1
%define  STDERR     2

global _start
section .data

    getname db "Digite seu nome: ", 0dH,0aH
    SIZE_GETNAME equ $-getname

    welcome_msg db "Hola Seja bem vindo ao programa CALC IA-32", 0dh,0ah
    SIZE_WELCOME_msg equ $-welcome_msg

    menu db "ESCOLHA UMA OPÇÃO: ",0dH,0ah,"- 1: SOMA", 0dH,0ah,"- 2: SUBTRAÇÂO", 0dH,0aH,"- 3: MULTIPLICAÇÂO", 0dH,0aH,"- 4: DIVISÃO", 0dH,0aH,"- 5: MOD", 0dH,0aH,"- 6: SAIR", 0dH,0aH 
    SIZE_MENU equ $-menu

    op_sum db "VOCE ESCOLHEU SOMA",0dH,0ah
    SIZE_SUM equ $-op_sum

    teste db "aaaaaaaaaaaaaaaaaaaaaa",0dh,0ah
    size_teste equ $-teste

    FIM_STRING equ 0

section .bss

    operation RESB 2
    user RESB 20
    string_int RESB 20
    int_string RESB 20
    number1 RESB 4
    number2 RESB 4

section .text

_start:

ask_name:

    ; pushad
    push DWORD getname          ;guarda posição de memoria de getname (mensagem que pergunta o nome) na pilha
    push DWORD SIZE_GETNAME     ;guarda o tamanho da mensagem na pilha (bytes a serem escritos)
    call write_string           ;chama função para escrever na tela
    ; popad

read_name:
    ; pushad
    push DWORD user             ;guarda posição de memória a guara bytes lidos na pilha
    push DWORD 20               ;guarda quantidade de bytes que podem ser lidos na pilha
    call read_string            ;chama função de ler string do teclado
    ; popad

welcome:

    push DWORD welcome_msg      ;guarda posição de memoria de welcome (mensagem de boas vindas) na pilha
    push DWORD 5                ;guarda quantidade de bytes a serem escritos (no caso apenas os bytes de "Hola ")
    call write_string           ;chama a função de escrever na tela
                                ;Nesse momento é escrito na tela apenas uma parte da mensadem de boas vindas "Hola "
    push DWORD user             ;guarda posição de user (nome do usuario) na pilha
    push DWORD 16               ;passa quantidade de bytes de user a serem escritos
    call write_string           ;chama função de escrever na tela
                                ;nesse momento é escrito na tela "Hola [user]\n"
    mov edx, SIZE_WELCOME_msg   ;passa para edx o tamanho da mensagem de boas vindas
    sub edx, 5                  ;subtrai 5 (quantidade de bytes já escritos antes)
    mov ecx, welcome_msg        ;move para ecx o ponteiro pra mensagem de boas vindas
    add ecx, 5                  ;soma 5 pra mover o início para os bytes que ainda não foram escritos
    push ecx                    ;guarda ecx na pilha 
    push edx                    ;guarda edx na pilha
    call write_string           ;chama função de escrita na tela
                                ;agora a mensagem completa está na tela, com o nome do usuário no meio
show_menu:
    
    push DWORD menu             ;guarda a posição de memoria de menu na pilha
    push DWORD SIZE_MENU        ;guarda o tamanho do menu na pilha
    call write_string           ;chama função para escrever na tela 
                                ;após mostrar o menu o usuário deve escolher uma das 6 opções
    call read_option            ;chama função para ler a opção do usuário

    cmp byte [operation], 1     ;compara a opção lida com o valor 1 (opção de soma)
    je sum                      ;se vor soma pula para a label sum

    cmp byte [operation], 6     ;compara a opção lida com o valor 6  (opção de saída)
    je _sair                    ;se for saída, pula para a label _sair qque é responsável por chamar a interrupção SYS_EXIT

end_cmp:                        ;label para o fim das comparações
    jmp show_menu               ;pula para a label show_menu para mostrar o menu novemente, após o fim das operações

_sair:                          ;rotina para sair do programa
    mov eax, SYS_EXIT           ;move para eax o código de SYS_EXI
    mov ebx, 0                  
    int 80h                     ;chama interrupção de sistema

read_option:

    mov eax, SYS_READ           ;diz pro sistema que é para ler 
    mov ebx, STDIN              ;standard input 
    mov ecx, operation          ;posição de memória onde vai ser guardado o valor lido
    mov edx, 2                  ;quantidade de bytes a serem lidos
    int 80h                     ;chama interrução de sistema

    sub byte [operation], 0x30  ;subtrai o valos 0x30 do valor lido para transformar de ASCI para inteiro

    ret                         ;retorna

read_string:                    ;retorna para a posição de memória passada o ponteiro pra string

    push EBP                    ;guarda na pilha o valor de EBP
    mov EBP, ESP                ;move para EBP o valor atual de ESP (base da pilha) para poder fazer operações com esse valor sem o risco de perder ESP
    mov eax, SYS_READ           ;diz pro sistema que é para ler 
    mov ebx, STDIN              ;standard input
    mov ecx, [EBP+12]           ;guarda em ecx o valor que está na posição de memória EBP+12 (no caso é a posição de memória onde vai ser armazenada a variável lida)
    mov edx, [EBP+8]            ;guarda em edx o valor que está na posição de memória EBP+8  (no caso é a quantidade de bytes a serem lidos)
    int 80h                     ;chama interrupção 80
    pop EBP                     ;retorna valor de EBP que estava guardado na pilha
    ret 8                       ;retorna desalocando 8 bytes da pilha        
                                ;***a chamada de sistema de leitura retorna em EAX a quantidade de bytes lidos

write_string:;escreve na tela a string passada

    push EBP                    ;guarda na pilha o valor de EBP
    mov EBP, ESP                ;move para ABP o valor atual de ESP (base da pilha) para poder fazer operações com esse valor sem o risco de perder ESP
    mov edx, [EBP+8]            ;guarda em edx o valor que está na posição de memória EBP+8  (no caso é a quantidade de bytes a serem escritos)
    mov ecx, [EBP+12]           ;guarda em ecx o valor que está na posição de memória EBP+12 (no caso é a posição de memória do primeiro elemento da string á ser escrita)
    mov ebx, STDOUT             ;standard output
    mov eax, SYS_WRITE

    int 80h                     ;chama interrupção 80
    pop EBP                     ;retorna o valor de ebp que estava guardado na pilha

    ret 8                       ;retorna desalocando 8 bytes da pilha
    ;ao fim de read string, ecx guarda o ponteiro da string e edx a quantidade de bytes lida


read_int:;retorne em eax o valor em inteiro

    push string_int             ;guarda posiçao de memóra onde vai ser lida a string 
    push DWORD 20               ;guarda quantidade de bytes a serem lidos como um número de 32bits
    call read_string            ;chama função para ler string 

    ; cmp string_int, '-'
    ; je negative_int
    
    convert_int:
    mov ecx, eax                ;move para ecx a quantidade de bytes lidos (eax vai conter o valor em inteiro)
    dec ecx                     ;retira o '\n' da contagem de caracteres lidos
    ; lea esi, [string_int]         ;move para esi (source index) o ponteiro de string int (primeiro digito )
    mov esi, string_int
    xor ebx, ebx                ;zera ebx
    xor edx, edx                ;zera edx

    check_sign:
    mov byte bl, '-'
    cmp byte [esi], bl                ;vê se o primeiro digito é um sinal de menos
    jne loop_ebx             ;se não for, pula para o loop para iniciar a conversão
    inc esi                     ;muda o esi para o próximo caracter, que deverá ser o primeiro dígito
    dec ecx                     ;diminui em 1 o valor de ecx (tira da contagem de dígitos o caracter de '-')
    mov edx, -1                 ;guarda em edx "-1" para saber que deve inverter o inteiro no final

    loop_ebx:
    xor ebx, ebx                ;zera ebx
    loop_digito:
    movzx eax, BYTE [esi]       ;move para eax o byte de string_int
    sub byte al, 0x30           ;converte de ASCI pra inteiro
    inc esi                     ;incrementa o ponteiro para o próximo digito
    imul ebx, 10                ;multiplica ebx por 10
    add ebx, eax                ;ebx = 10*ebx + eax
    loop loop_digito            ;se ecx > 0, volta pra loop_digito ou seja, enquanto não forem todos os digitos, repete o procedimento
    mov eax, ebx

    cmp edx, -1                 ;se edx for -1, significa que deve inverter o sinal do número lido
    jne fim_convert             ;se não for -1, pula para o fim da conversão
    neg eax                     ;se for igual, inverte eax

    fim_convert: 
    ; cmp eax, -80
    ; je _sair
    ret                         ;retorna 

write_int:

    push EBP                    ;guarda na pilha o valor atual de EBP
    mov EBP, ESP                ;move para EBP o valor atual de ESP (base da pilha) para poder fazer operações com esse valor sem o risco de perder ESP
    mov eax, [EBP+8]            ;move para EBP o valor guardado na pilha (valor do número a ser impresso)
    
    mov ecx, 20                 ;move para ecx a quantidade maxima de bytes a serem escritos
    lea esi, [int_string]       ;move para esi o valor da posição de memória onde guardar a string convertida
    add esi, 19                 ;adiciona o max de bytes (pra chegar à última posição)
    mov BYTE [esi], FIM_STRING  ;coloca na ultima posição o valor de fim da string?******
    cmp eax, 0                  ;compara o valor que queremos imprimir com 0
    mov ebx, 10                 ;pra ser usado em divisão
    ja loop_dig_write           ;se for maior que zero, pula pro loop
    neg eax                     ;se for menor que zero, inverte o sinal (com complemento de 2)

loop_dig_write:
    xor edx, edx                ;limpa edx antes da divisão edx:eax por ebx 
    div ebx                     ;eax = edx:eax/10 edx = edx:eax mod 10
    add dl, 0x30                ;converte de inteiro para ASCI
    mov [esi], dl               ;guarda no buffer apontado por esi o número convertido
    cmp eax, 0                  ;compara se eax é zero
    jne loop_dig_write          ;se não, repete o loop (repete até eax ser 0)

    push esi
    push ecx
    call write_string
    ret 4

sum:

    push op_sum
    push SIZE_SUM
    call write_string

    call read_int               ;retorna em eax o valor inteiro lido
    mov [number1], eax            ;move o valor lido para a posição de memória de nunmber1

    pushad
    push teste
    push size_teste
    call write_string
    popad

    push number1
    call write_int

    jmp end_cmp
    ; jmp show_menu