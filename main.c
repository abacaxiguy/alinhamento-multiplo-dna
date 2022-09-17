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

// belle
#define ALPHA 2 // A + A
#define BETA 0 // A + T
#define DELTA -1 // A + - // - + -

// FUNÇÕES PARA FAZER

// Copia melhor alinhamento para uma variavel
char salvarMelhorAlinhamento(char alinhamento[][102], char melhorAlinhamento[][102]){
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 102; j++) {
      melhorAlinhamento[i][j] = alinhamento[i][j];
    }
  }
}

void calcular_score(char sequencias[10][102], int lin, int col) {
	// calcular colunas

	//   i0 i1 i2
	// j0 A, B, C
	// j1 D, E, F
	// j2 G, H, I

	for (int i = 0; i < col; i ++){
        for (int j = 0; j < lin; j++){
            int c = i;

            while(col > c){
                printf("%c + %c = 0\n", sequencias[j][i], sequencias[c][i]);
                c++;
            }
        }
	}
}

// FUNÇÕES FEITAS

// Percorre um vetor e verifica se este só contem letras.
int verificaCharValidos(char seq[]) {

  for (int i = 0; seq[i] != '\0'; i++) {

    if (i == 0 && seq[i] == '\n') {
      return 0;

    } else if (isalpha(seq[i]) == 0 && seq[i] != '\n') {
      return 0;
    }
  }

  return 1;
}

// Essa função recebe o índice da maior sequencia e preenche as sequecnias
// menores com gaps no FINAL
void preencheGapFinal(char sequencia[][100], int cont, int maxSize) {

  for (int x = 0; x < cont; x++) {
    for (int y = 0; y < maxSize; y++) {

      if (sequencia[x][y] == ' ' || sequencia[x][y] == '\n' ||
          sequencia[x][y] == '\0') {
        sequencia[x][y] = '-';
        sequencia[x][y + 1] = '\0';
      }
    }
  }
}

//Essa função recebe uma sequencia, o tamanho max da sequencia e um índice.
//coloca todos os gaps que estão no final da sequencia p/ uma posição específica.
void trocaPosicaoGapFinal(int indice, int max, char *vetor){

    int rodando = 1;
    
    do{
        
        for(int i = max-1; i > indice; i--){
            vetor[i] = vetor[i-1];
        }   

        vetor[indice] = '-';

        if(vetor[max-1] != '-'){
            rodando = 0;
        } 

        indice+=1;

    }while(rodando);
}

//(INCOMPLETA)
// Percorre a matriz de sequencias linha a linha, e compara a linha do índice
// atual com a de baixo.
void alinhaSequencias(char seq[][100], int max, int nSeq) {

  for (int x = 0; x < nSeq; x++) {

    for (int y = 0; y < max; y++) {

      // Se a proteina da sequencia atual, for igual a que está embaixo. Não faz
      // porra nenhuma.
      if (seq[x][y] == seq[x + 1][y]) {
        continue;

      } else {

        // verifica Se ao adicionar um gap a proteina do índice atual ocorre um
        // match com a proteina da sequecnia de baixo. Se sim, adiciona o gap.
        // Também verifica se há GAPS DISPONÍVEIS(Estão sempre no final da
        // sequencia). para realizar a operação

        // Verifica linha de cima:
        if (seq[x][y] == seq[x + 1][y + 1] && seq[x][max - 1] == '-') {
          trocaPosicaoGapFinal(y, max, seq[x]);

          // Verifica se há um match se adicionar gap no índice da linha de
          // baixo:
        } else if (seq[x + 1][y] == seq[x][y + 1] &&
                   seq[x + 1][max - 1] == '-') {
          trocaPosicaoGapFinal(y, max, seq[x + 1]);
        }
      }
    }
  }
}

int main() {
  int sequencias_count = 0;
  int max_string_size = 0;

  printf("Digite o tamanho do conjunto de sequencias (min - 2, max - 10): ");
  scanf("%d", &sequencias_count);

  while (sequencias_count < 2 || sequencias_count > 10) {
    printf("\nDigite o tamanho do conjunto de sequencias (min - 2, max - 10): ");
    scanf("%d", &sequencias_count);
  }

  char sequencias[sequencias_count][102];

  printf("\nLembre-se! Tamanho da sequência não pode ser maior que 100 caracteres!\n\n");

  for (int i = 0; i < sequencias_count; i++) {

    printf("Digite a sequencia %dº: ", i + 1);
    scanf("%s", sequencias[i]);

    if (verificaCharValidos(sequencias[i]) == 0) {
      printf("A sequencia deve conter apenas letras!\n");
      i -= 1;
      continue;
    }

    size_t sequencia_size = strlen(sequencias[i]);

    if (sequencia_size > 100){
        printf("Tamanho da sequencia %d maior que 100!\n", i + 1);
        return 0;
    }

    if (sequencia_size > max_string_size) max_string_size = sequencia_size;
  }

  printf("\nVocê digitou %d sequencias com tamanho máximo de %d caracteres\n\n", sequencias_count, max_string_size);

  char melhorAlinhamento[10][102];
  char (*pMelhorAlinhamento)[102] = melhorAlinhamento;

  salvarMelhorAlinhamento(sequencias, pMelhorAlinhamento);

  for (int i = 0; i < sequencias_count; i++) printf("Melhor %d: %s\n", i + 1, melhorAlinhamento[i]);

  printf("\nContando o alinhamento...\n");

  calcular_score(sequencias, sequencias_count, max_string_size);

  printf("\nScore: %c\n", '?');
	
  return 0;
}
