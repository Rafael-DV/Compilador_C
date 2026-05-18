inteiro: quantidade_alunos;
inteiro: nota_1;
inteiro: nota_2;
inteiro: media_final;
inteiro: contador_loop;
inteiro: variavel_auxiliar;
inteiro: x;

escreva("--- INICIANDO SISTEMA ESCOLAR ---");
escreva("Digite a quantidade de alunos:");
leia(quantidade_alunos);

media_final <- 0;
variavel_auxiliar <- 100;

se (quantidade_alunos <= 0 ou quantidade_alunos > 50) entao
    escreva("Quantidade invalida! Digite um valor entre 1 e 50");
senao
    escreva("Iniciando a leitura das notas...");
    
    para contador_loop <- 1 ate quantidade_alunos passo 1
        escreva("Lendo as notas do aluno");
        
        leia(nota_1);
        leia(nota_2);
        
        media_final <- (nota_1 + nota_2) / 2;
        
        se (media_final >= 6 e nao (nota_1 = 0)) entao
            escreva("Aluno aprovado com sucesso!");
        senao
            se (media_final = 5) entao
                escreva("Aluno em recuperacao");
            senao
                escreva("Aluno reprovado");
            fim_se
        fim_se
    fim_para
fim_se

escreva("Calculando formulas matematicas malucas de teste");
x <- (variavel_auxiliar * 2) - (media_final / 3) + 15;

se (x <> 0) entao
    escreva("X e diferente de zero!");
    
    para contador_loop <- 10 ate 0 passo -1
        escreva("Contagem regressiva do laco!");
        x <- x - 1;
    fim_para
fim_se

escreva("--- FIM DO TESTE DE ESTRESSE DO COMPILADOR ---");