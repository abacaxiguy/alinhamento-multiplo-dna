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

    // Alinhar as sequencias com arvore n-aria

    // A arvore n-aria deve ser construida a partir das possibilidades de alinhamento das sequencias
    // A raiz da arvore deve ser a primeira coluna das sequencias
    // Cada filho da raiz deve ser uma das possibilidades de alinhamento com gap ou com a segunda coluna das sequencias

    return 0;
}