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

Token proximo_token(FILE *arquivo) {
    Token t;
    char c;

    // --- IGNORAR ESPAÇOS ---
    do {
        c = fgetc(arquivo); 
    } while (isspace(c));

    // --- FIM DO ARQUIVO ---
    if (c == EOF) {
        t.tipo = FIM_DE_ARQUIVO;
        strcpy(t.lexema, "EOF");
        return t;
    }

    // --- IDENTIFICADORES E PALAVRAS RESERVADAS ---
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

    // --- NÚMEROS (NUMINT) ---
    if (isdigit(c)) {
        int i = 0;
        t.lexema[i++] = c;
        char prox = fgetc(arquivo);
        while (isdigit(prox)) {
            t.lexema[i++] = prox;
            prox = fgetc(arquivo);
        }
        t.lexema[i] = '\0';
        ungetc(prox, arquivo);
        
        t.tipo = NUMINT;
        return t;
    }

    // --- TEXTOS (STRING) ---
    if (c == '"') {
        int i = 0;
        t.lexema[i++] = c;
        char prox = fgetc(arquivo);
        
        while (prox != '"' && prox != EOF) {
            t.lexema[i++] = prox;
            prox = fgetc(arquivo);
        }
        if (prox == '"') {
            t.lexema[i++] = prox; 
        }
        t.lexema[i] = '\0';
        t.tipo = STRING;
        return t;
    }

    // --- SÍMBOLOS MENOR (<, <=, <>, <-) ---
    if (c == '<') {
        char prox = fgetc(arquivo); 
        if (prox == '-') { t.tipo = ATR; strcpy(t.lexema, "<-"); } 
        else if (prox == '=') { t.tipo = LOGMENORIGUAL; strcpy(t.lexema, "<="); } 
        else if (prox == '>') { t.tipo = LOGDIFF; strcpy(t.lexema, "<>"); } 
        else { ungetc(prox, arquivo); t.tipo = LOGMENOR; strcpy(t.lexema, "<"); }
        return t;
    }

    // --- SÍMBOLOS MAIOR (>, >=) ---
    if (c == '>') {
        char prox = fgetc(arquivo);
        if (prox == '=') { t.tipo = LOGMAIORIGUAL; strcpy(t.lexema, ">="); } 
        else { ungetc(prox, arquivo); t.tipo = LOGMAIOR; strcpy(t.lexema, ">"); }
        return t;
    }

    // --- SÍMBOLOS DE 1 CARACTERE ---
    if (c == '=') { t.tipo = LOGIGUAL; strcpy(t.lexema, "="); return t; }
    if (c == '+') { t.tipo = OPMAIS; strcpy(t.lexema, "+"); return t; }
    if (c == '-') { t.tipo = OPMENOS; strcpy(t.lexema, "-"); return t; }
    if (c == '*') { t.tipo = OPMULTI; strcpy(t.lexema, "*"); return t; }
    if (c == '/') { t.tipo = OPDIVI; strcpy(t.lexema, "/"); return t; }
    if (c == ':') { t.tipo = DOISP; strcpy(t.lexema, ":"); return t; }
    if (c == ';') { t.tipo = PVIR; strcpy(t.lexema, ";"); return t; }
    if (c == '(') { t.tipo = PARAB; strcpy(t.lexema, "("); return t; }
    if (c == ')') { t.tipo = PARFE; strcpy(t.lexema, ")"); return t; }

    // --- ERRO LÉXICO ---
    t.tipo = ERRO_LEXICO;
    t.lexema[0] = c;
    t.lexema[1] = '\0';
    return t;
}


// Array auxiliar só para a gente ver o NOME do token na tela em vez de um número
const char* nomesTokens[] = {
    "ATE", "ATR", "DOISP", "E", "ENTAO", "ESCREVA", "FIMPARA", "FIMSE", "ID",
    "LEIA", "LOGDIFF", "LOGIGUAL", "LOGMAIOR", "LOGMAIORIGUAL", "LOGMENOR",
    "LOGMENORIGUAL", "NAO", "NUMINT", "OPDIVI", "OPMAIS", "OPMENOS", "OPMULTI",
    "OU", "PARA", "PARAB", "PARFE", "PASSO", "PVIR", "SE", "SENAO", "STRING", "TIPO",
    "FIM_DE_ARQUIVO", "ERRO_LEXICO"
};



int main() {

    // 1. Tenta abrir o arquivo de código fonte
    FILE *arquivo_entrada = fopen("teste.POR", "r");
    if (arquivo_entrada == NULL) {
        printf("ERRO: Nao foi possivel abrir o arquivo 'teste.POR'.\n");
        printf("Crie um arquivo chamado teste.POR na mesma pasta do seu codigo!\n");
        return 1;
    }

    // 2. Cria o arquivo de saída pedido pelo PDF
    FILE *arquivo_saida = fopen("saida.OBJ", "w");
    if (arquivo_saida == NULL) {
        printf("ERRO: Nao foi possivel criar o arquivo 'saida.OBJ'.\n");
        return 1;
    }

    printf("Iniciando a Analise Lexica...\n\n");

    Token t;
    // 3. Fica chamando o Léxico até ele retornar FIM_DE_ARQUIVO
    do {
        t = proximo_token(arquivo_entrada);
        
        // Imprime na tela preta (Terminal) para você ver funcionando
        printf("Token: %-15s | Lexema: %s\n", nomesTokens[t.tipo], t.lexema);
        
        // Grava no arquivo *.OBJ como o professor pediu
        // O %d grava o código numérico do token
        fprintf(arquivo_saida, "%d %s\n", t.tipo, t.lexema);

    } while (t.tipo != FIM_DE_ARQUIVO);

    printf("\nAnalise concluida! Arquivo 'saida.OBJ' gerado com sucesso.\n");

    // 4. Fecha os arquivos
    fclose(arquivo_entrada);
    fclose(arquivo_saida);

    return 0;  

}  


    