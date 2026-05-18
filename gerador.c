#include <stdio.h>

int main() {
    // Isso vai criar (ou sobrescrever) o seu arquivo teste.POR
    FILE *f = fopen("teste.POR", "w"); 
    if(f == NULL) {
        printf("Erro ao criar arquivo!\n");
        return 1;
    }

    // Cabecalho do arquivo
    fprintf(f, "inteiro: loop_principal;\n");
    fprintf(f, "inteiro: calculo_pesado;\n\n");
    fprintf(f, "calculo_pesado <- 1;\n");
    fprintf(f, "escreva(\"Iniciando MEGA teste de 6000 linhas...\");\n\n");
    
    // Abre um laço de repetição no PORTUGOL
    fprintf(f, "para loop_principal <- 1 ate 1000 passo 1\n");
    
    // Aqui é a mágica! O C vai escrever 1000 vezes um bloco de 6 linhas de código Portugol
    for(int i = 0; i < 10000; i++) {
        fprintf(f, "    calculo_pesado <- calculo_pesado + %d;\n", i);
        fprintf(f, "    se (calculo_pesado >= 10000 e nao (calculo_pesado = 0)) entao\n");
        fprintf(f, "        calculo_pesado <- calculo_pesado / 2;\n");
        fprintf(f, "    senao\n");
        fprintf(f, "        calculo_pesado <- calculo_pesado * 2;\n");
        fprintf(f, "    fim_se\n");
    }
    
    // Fecha o laço do PORTUGOL
    fprintf(f, "fim_para\n\n");
    fprintf(f, "escreva(\"Fim do teste de estresse!!! A maquina sobreviveu.\");\n");
    
    fclose(f);
    printf("SUCESSO: Arquivo 'teste.POR' com mais de 6000 linhas gerado!\n");
    return 0;
}