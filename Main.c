#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// 1. Enum com todos os Tokens
typedef enum {
    ATE, ATR, DOISP, E, ENTAO, ESCREVA, FIMPARA, FIMSE, ID,
    LEIA, LOGDIFF, LOGIGUAL, LOGMAIOR, LOGMAIORIGUAL, LOGMENOR,
    LOGMENORIGUAL, NAO, NUMINT, OPDIVI, OPMAIS, OPMENOS, OPMULTI,
    OU, PARA, PARAB, PARFE, PASSO, PVIR, SE, SENAO, STRING, TIPO,
    FIM_DE_ARQUIVO, ERRO_LEXICO
} TokenType;

// 2. Struct que representa o Token retornado (Faltava isso!)
typedef struct {
    TokenType tipo;
    char lexema[100];
} Token;

// 3. Estrutura e Tabela de Palavras Reservadas
typedef struct {
    char palavra[50];
    TokenType token;
} PalavraReservada;

PalavraReservada tabelaReservadas[] = {
    {"ate", ATE}, {"entao", ENTAO}, {"escreva", ESCREVA},
    {"fim_para", FIMPARA}, {"fim_se", FIMSE}, {"leia", LEIA},
    {"nao", NAO}, {"ou", OU}, {"para", PARA}, {"passo", PASSO},
    {"se", SE}, {"senao", SENAO}, {"inteiro", TIPO}, {"e", E}
};

// 4. Função que verifica se é palavra reservada
int verificarPalavraReservada(char* identificador) {
    int tamanho = sizeof(tabelaReservadas) / sizeof(PalavraReservada);
    for(int i = 0; i < tamanho; i++) {
        if(strcmp(identificador, tabelaReservadas[i].palavra) == 0) {
            return tabelaReservadas[i].token;
        }
    }
    return -1;    
}

// 5. A FUNÇÃO PRINCIPAL DO LÉXICO (Tudo precisa estar aqui dentro!)
Token proximo_token(FILE *arquivo) {
    Token t; // Aqui declaramos o 't'
    char c;

    // Ignora espaços em branco, quebras de linha e tabs
    do {
        c = fgetc(arquivo); 
    } while (isspace(c));

    // Verifica se chegou no fim do arquivo
    if (c == EOF) {
        t.tipo = FIM_DE_ARQUIVO;
        strcpy(t.lexema, "EOF");
        return t;
    }

    // Lê Identificadores e Palavras Reservadas
    if (isalpha(c)) {
        int i = 0;
        t.lexema[i++] = c;

        char prox = fgetc(arquivo);

        while (isalnum(prox) || prox == '_') {
            t.lexema[i++] = prox;
            prox = fgetc(arquivo);
        }
        t.lexema[i] = '\0';

        ungetc(prox, arquivo);

        int codigo = verificarPalavraReservada(t.lexema);
        if (codigo != -1) {
            t.tipo = codigo;
        } else {
            t.tipo = ID;    
        }
        
        return t;
    }

    // Lê os símbolos de menor (exemplo)
    if (c == '<') {
        char prox = fgetc(arquivo); 
        
        if (prox == '-') {
            t.tipo = ATR;             
            strcpy(t.lexema, "<-");
        } 
        else if (prox == '=') {
            t.tipo = LOGMENORIGUAL;   
            strcpy(t.lexema, "<=");
        } 
        else if (prox == '>') {
            t.tipo = LOGDIFF;         
            strcpy(t.lexema, "<>");
        } 
        else {
            ungetc(prox, arquivo);    
            t.tipo = LOGMENOR;
            strcpy(t.lexema, "<");
        }
        return t;
    }

    // Se não for nada que conhecemos, é erro léxico
    t.tipo = ERRO_LEXICO;
    t.lexema[0] = c;
    t.lexema[1] = '\0';
    return t;
}
