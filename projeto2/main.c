/*
Implemente um programa que realiza a operação de alinhamento múltiplo de DNA com
uma estrutura que permita a o alinhamento de 10 sequências com tamanho igual à
100. O alinhamento de múltiplos DNA pode ser resumido da seguinte forma: dado um
conjunto de DNA (cadeias de bases nitrogenadas) Sinput ={s1,s2,..,si,..} de
tamanhos variando de 1 até m∈N (Números Naturais), e os pesos α,β,δ∈Q (Números
Racionais) para expressar as seguintes situações:
α expressa a relevância do alinhamento de x pares de bases nitrogenadas iguais
ocupando a mesma posição nas cadeias do conjunto de entrada
β para o alinhamento de y pares de bases nitrogenadas diferentes ocupando a
mesma posição nas cadeias do conjunto de entrada
• δ para o alinhamento de z pares formados por um gap (buraco representado pelo
símbolo “-”) e uma base nitrogenada ocupando a mesma posição nas cadeias do
conjunto de entrada.
O alinhamento de Sinput é um conjunto Soutput = { r1, r2,.., ri,..}, formado por
seqüências de tamanho m, construídas pela inserção de buracos nas seqüências dos
elementos do conjunto Sinput, tal que para toda posição i variando de 1 à m, o
valor da fórmula score = αx+βy+δz seja máximo, e que para cada seqüência sj
pertencente ao conjunto Sinput exista uma única seqüência rj no conjunto
Soutput, cuja remoção dos gaps de rj reproduza a seqüência sj dada.
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHA 2  // A + A
#define BETA 0   // A + T
#define DELTA -1 // A + - // - + -

#define DIF 0 // AB / ABA = DIFERENTES TAMANHOS
#define IGUAL 1 // AB / AB = IGUAIS TAMANHOS

// Projeto 2
// Alinhamento multiplo de sequencias usando programacao dinamica e estrutura de árvore n-ária

// Estrutura de dados para representar uma arvore n-aria
typedef struct arvore {
    struct arvore *pai;
    struct arvore *filho;
    struct arvore *irmao;
    char *sequencia;
} Arvore;

// O alinhamento deve ser feito com 10 sequencias de tamanho 100

// Funcao para criar uma arvore n-aria
Arvore *criarArvore(char *sequencia) {
    Arvore *arvore = (Arvore *)malloc(sizeof(Arvore));
    arvore->pai = NULL;
    arvore->filho = NULL;
    arvore->irmao = NULL;
    arvore->sequencia = sequencia;
    return arvore;
}

// Funcao para inserir um filho em uma arvore n-aria
void inserirFilho(Arvore *arvore, char *sequencia) {
    Arvore *filho = criarArvore(sequencia);
    filho->pai = arvore;
    filho->irmao = arvore->filho;
    arvore->filho = filho;
}

// Funcao para inserir um irmao em uma arvore n-aria
void inserirIrmao(Arvore *arvore, char *sequencia) {
    Arvore *irmao = criarArvore(sequencia);
    irmao->pai = arvore->pai;
    irmao->irmao = arvore->irmao;
    arvore->irmao = irmao;
}

// Funcao para imprimir uma arvore n-aria
void imprimirArvore(Arvore *arvore) {
    if (arvore != NULL) {
        printf("%s", arvore->sequencia);
        imprimirArvore(arvore->filho);
        imprimirArvore(arvore->irmao);
    }
}

// Percorre um vetor e verifica se este só contem letras.
int verificaCharValidos(char seq[])
{

    for (int i = 0; seq[i] != '\0'; i++)
    {

        if (i == 0 && seq[i] == '\n')
            return 0;

        else if (!isalpha(seq[i]))
            return 0;
    }

    return 1;
}

// Pega a sequencia enviada pelo usuario e verifica se é valida
void pegandoSequencia(char sequencias[][103], int sequencias_count, int *max_string_size)
{
    system("clear");
    for (int i = 0; i < sequencias_count; i++)
    {
        printf("Digite a sequencia %dº (max: 100 caracteres): \n", i + 1);
        scanf("%s", sequencias[i]);

        if (!verificaCharValidos(sequencias[i]))
        {
            printf("Sequencia invalida! A sequencia deve conter apenas letras!\n");
            i -= 1;
            continue;
        }

        size_t sequencia_size = strlen(sequencias[i]);

        while (sequencia_size > 100)
        {
            system("clear");
            printf("Sequencia invalida! A sequencia deve conter no maximo 100 caracteres!\n");
            printf("Digite a sequencia %dº (max: 100 caracteres): \n", i + 1);
            scanf("%s", sequencias[i]);
            sequencia_size = strlen(sequencias[i]);
        }

        if (sequencia_size > *max_string_size)
            *max_string_size = sequencia_size;
    }
}

// Calcula o score da sequencia atual
void calcular_score(char sequencias[10][103], int lin, int col)
{
    int score = 0, alpha = 0, beta = 0, delta = 0;

    int gaps = 0, sum_pos_gaps = 0;

    for (int i = 0; i < col; i++)
    {
        // coluna
        for (int j = 0; j < lin; j++)
        {
            // linha
            for (int k = j + 1; k < lin; k++)
            {
                // pares ordenados
                if (sequencias[j][i] == '-' || sequencias[k][i] == '-')
                {
                    score += DELTA;
                    delta += 1;
                }
                else if (sequencias[j][i] == sequencias[k][i])
                {
                    score += ALPHA;
                    alpha += 1;
                }
                else
                {
                    score += BETA;
                    beta += 1;
                }
            }
        }
    }

    printf("\nSCORE INICIAL:\n(α * %d) + (β * %d) + (δ * %d)", alpha, beta, delta);
    score > 0 ? printf(" = +%d\n", score) : printf(" = %d\n", score);

    // Fórmula de peso para gaps no final
    // (somatório posição gaps) * (quantidade gaps)

    // Fórmula de peso para gaps juntos
    // insipiração = xadrez =)
    // quanto mais ilhas de gaps, menos gaps juntos temos
    // (quantidade gaps * ilhas gaps)

    int pGapsJuntos = 0;

    for (int i = 0; i < lin; i++)
    {
        int gaps_linha = 0;
        int ilhas_gaps = 0;
        for (int j = 0; j < col; j++)
        {
            if (sequencias[i][j] == '-')
            {
                gaps++;
                sum_pos_gaps += j;
                gaps_linha++;
                while (sequencias[i][j + 1] == '-')
                {
                    gaps_linha++;
                    gaps++;
                    j++;
                    sum_pos_gaps += j;
                }
                ilhas_gaps++;
            }
        }
        pGapsJuntos += gaps_linha * (ilhas_gaps - 1);
    }

    int pGapsFinais = gaps + sum_pos_gaps;

    printf("\nPesos:\n");
    printf("pGapsJuntos = nº de gaps * (ilhas de gaps - 1): %d\n", pGapsJuntos);
    printf("pGapsFinais = (∑ posição dos gaps) + (nº de gaps): %d\n", pGapsFinais);
    score = score + pGapsFinais - pGapsJuntos;
    printf("\nFÓRMULA = score + pGapsFinais - pGapsJuntos\n");
    printf("\nSCORE FINAL: ");
    score > 0 ? printf("+%d\n", score) : printf("%d\n", score);
}

// Preenche a matriz com gaps no final, se for do mesmo tamanho coloca um gap a mais
int preencheGapFinal(char seq[][103], int cont, int *maxSize)
{
    // checar se todas as sequencias possuem o mesmo tamanho
    int tamanho = IGUAL;
    for (int i = 0; i < cont; i++)
    {
        if (strlen(seq[i]) != *maxSize)
        {
            tamanho = DIF;
            break;
        }
    }
    if (tamanho == IGUAL)
    {
        // adicionar um gap a mais
        for (int i = 0; i < cont; i++)
        {
            seq[i][*maxSize] = '-';
            seq[i][*maxSize + 1] = '\0';
        }

        *maxSize += 1;
    }

    else
    {
        for (int x = 0; x < cont; x++)
        {
            for (int y = 0; y < *maxSize; y++)
            {
                if (seq[x][y] == ' ' || seq[x][y] == '\0')
                {
                    seq[x][y] = '-';
                    seq[x][y + 1] = '\0';
                }
            }
        }
    }

    return tamanho;
}

int main(){
    int sequencias_count = 0;
    int max_string_size = 0;

    char temp_sequencias_count[3];

    printf("\n\t******** Alinhamento multiplo de DNA  ********\n\n");
    printf("Por favor, digite o tamanho do conjunto de sequencias (min: 2, max: 10): ");

    scanf("%s", temp_sequencias_count);

    while ((strlen(temp_sequencias_count) > 1 && temp_sequencias_count == "10") || isdigit(atoi(&temp_sequencias_count[0])) != 0 || atoi(&temp_sequencias_count[0]) < 2 || atoi(&temp_sequencias_count[0]) > 10)
    {
        system("clear");
        printf("Tamanho invalido! Escolha outro tamanho (min: 2, max: 10):\n");
        scanf("%s", temp_sequencias_count);
    }

    sequencias_count = atoi(&temp_sequencias_count[0]);

    char sequencias[sequencias_count][103];

    pegandoSequencia(sequencias, sequencias_count, &max_string_size);

    system("clear");
    printf("\nVocê digitou %d sequencias com tamanho máximo de %d caracteres\n", sequencias_count, max_string_size);

    printf("\nSequencia inicial: \n\n");
    imprimirSequencia(sequencias, sequencias_count);

    printf("\nAlinhamento com gaps no final:\n\n");

    int tamanho = preencheGapFinal(sequencias, sequencias_count, &max_string_size);
    imprimirSequencia(sequencias, sequencias_count);

    printf("\n");

    // Alinhar as sequencias com arvore n-aria

    // A arvore n-aria deve ser construida a partir das possibilidades de alinhamento das sequencias
    // A raiz da arvore deve ser a primeira coluna das sequencias
    // Cada filho da raiz deve ser uma das possibilidades de alinhamento da primeira coluna

    // exemplo:
    // sequencias: ABCD, CA, AA
    // raiz1: ACA
    // possibilidades:
    // ACA
    // A-A
    // AC-
    // A--

    // calcular o score de cada possibilidade
    // escolher a possibilidade com maior score
    // adicionar a possibilidade escolhida na arvore
    

    return 0;
}