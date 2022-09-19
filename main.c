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

#define ALPHA 2 // A + A
#define BETA 0 // A + T
#define DELTA -1 // A + - // - + -

// FUNÇÕES FEITAS

// Imprime a sequencia atual
void imprimirSequencia(char sequencia[][103], int tamanhoSequencia)
{
  for (int i = 0; i < tamanhoSequencia; i++)
  {
    printf("%s\n", sequencia[i]);
  }
}

// Copia melhor alinhamento para uma variavel
char salvarMelhorAlinhamento(char alinhamento[][103], char melhorAlinhamento[][103])
{
  for (int i = 0; i < 10; i++)
  {
    for (int j = 0; j < 103; j++)
    {
      melhorAlinhamento[i][j] = alinhamento[i][j];
    }
  }
}

// Calcula o score da sequencia atual
void calcular_score(char sequencias[10][103], int lin, int col)
{
  int score = 0, alpha = 0, beta = 0, delta = 0;

  for (int i = 0; i < col; i++)
  {
    // coluna
    for (int j = 0; j < lin; j++)
    {
      // linha
      for (int k = j + 1; k < lin; k++)
      {
        // pares ordenados
        if (sequencias[j][i] == '-' || sequencias[k][i] == '-') {
          score += DELTA;
          delta += 1;
        }
        else if (sequencias[j][i] == sequencias[k][i]) {
          score += ALPHA;
          alpha += 1;
        }
        else {
          score += BETA;
          beta += 1;
        } 
      }
    }
  }

  printf("\nSCORE:\n(α * %d) + (β * %d) + (δ * %d)", alpha, beta, delta);
  score > 0 ? printf(" = +%d\n", score) : printf(" = %d\n", score);
}

// Percorre um vetor e verifica se este só contem letras.
int verificaCharValidos(char seq[])
{

  for (int i = 0; seq[i] != '\0'; i++)
  {

    if (i == 0 && seq[i] == '\n') return 0;

    else if (!isalpha(seq[i])) return 0;

  }

  return 1;
}

// Essa função recebe o índice da maior sequencia e preenche as sequecnias
// menores com gaps no FINAL
void preencheGapFinal(char seq[][103], int cont, int *maxSize){
  // checar se todas as sequencias possuem o mesmo tamanho

  // preencher dois gaps no final de cada sequencia
  for (int i = 0; i < cont; i++){
    seq[i][*maxSize] = '-';
    seq[i][*maxSize + 1] = '-';
    seq[i][*maxSize + 2] = '\0';
  }

  *maxSize += 2;
}

void preencherGapDiferente(char seq[][103], int cont, int *maxSize){
  for (int x = 0; x < cont; x++){
    for (int y = 0; y < *maxSize; y++){

      if (seq[x][y] == ' ' || seq[x][y] == '\0'){
        seq[x][y] = '-';
        seq[x][y + 1] = '\0';
      }

    }
  }
}

// Essa função recebe uma sequencia, o tamanho max da sequencia e um índice.
// coloca todos os gaps que estão no final da sequencia p/ uma posição específica.
void trocaPosicaoGapFinal(int indice, int *max, char *vetor)
{

  int rodando = 1;

  do
  {

    for (int i = *max - 1; i > indice; i--)
    {
      vetor[i] = vetor[i - 1];
    }

    vetor[indice] = '-';

    if (vetor[*max - 1] != '-')
    {
      rodando = 0;
    }

    indice += 1;

  } while (rodando);

}

// (Versão 1)
// Percorre a matriz de sequencias linha a linha, e compara a linha do índice
// atual com a de baixo.
// Se dois alinhamentos tiverem o mesmo numero de match's fica com o segundo
// Se dois alinhamentos tiverem match's diferentes, mantém o que tiver mais.
void alinhaSequencias(char seq[][103], int *max, int nSeq){

    int nomatches = 0; // variável de verificação.
    char seqTemp[103];

    for(int x = 0; x < nSeq; x++){ //Percorre as sequencias (linhas)
    
        // 1 - verifica se tem gap no final
        // 2 - testar a partir da posição que não tem match  
        // 3 - se conseguir mais match que o original, salva essa posição.
        // 4 - tenta em outra posição no anterior, se conseguir mais match, mantém até acabar os numeros.
        // 5 - vai pra proxima sequencia e repete

        // tentar da match a partir da 1 sequencia se conseguir para
        // verificar se ta melhor agora do que antes

          // verificar se há gaps p/ realizar o shift;
          if(seq[x][*max-1] != '-'){
              continue;
          }

        for(int y = 0; y < *max; y++){ //Percorre os caracteres da sequencia atual (colunas)

            for(int j = 0; j < *max; j++){ //percorre as sequencias (linhas) pra comparar os caracteres (colunas)
                  // printf("\n j : %d\n", j);
                if(j == x){ //pulamos a sequencia atual. Não comparamos uma sequencia com ela mesma.
                  // printf("\nj: %d é igual a x: %d\n", j, x);
                  continue;
                }

                if(seq[x][y] == seq[j][y]){ //Se der match com alguém finaliza. Não damos shift (por enquanto) se ja tiver dado um match
                    // printf("\ndeu match caracter j: %c y:%c\n", seq[j][x], seq[j][y]);
                    break;
                }

                // Se a posição não deu match, ela está eletiva a receber gaps.
                // modificamos a variável de verificação (no matches) e encerramos as comparações.

                // printf("\nn deu match :c\n");
                nomatches = 1;
                break;
            }

            // Se o caracter não deu match, então damos um gap.
            if(nomatches){

              // Passa a sequencia p/um vetor temporário
              strcpy(seqTemp, seq[x]);

              // Dá o gap nessa posição, mas passando o vetor temporário.
              trocaPosicaoGapFinal(y, max, seqTemp);

              // verifica se a nova configuração conseguiu um match.
              // Se conseguir, usa essa nova organização
              // Se não, não faz nada
              for(int k = y; k < *max; k++){
                  for(int x2 = 0; x2 < nSeq; x2++){

                      if(x2 == x) continue;

                      if(seqTemp[k] == seq[x2][k]){
                            strcpy(seq[x], seqTemp);
                            break;
                      }

                  }
              }
              nomatches = 0; // Reseta a variável de verificação
              break;
           }
        }
    }
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

    if (sequencia_size > *max_string_size) *max_string_size = sequencia_size;
  }
}

int main() {
  int sequencias_count = 0;
  int max_string_size = 0;

  printf("\n\t******** Alinhamento multiplo de DNA  ********\n\n");
  printf("Por favor, digite o tamanho do conjunto de sequencias (min: 2, max: 10): ");

  scanf("%d", &sequencias_count);
  
  while((sequencias_count < 2) || (sequencias_count > 10)){
      system("clear");
      printf("Tamanho invalido! Escolha outro tamanho (min: 2, max: 10):\n");
      scanf("%d", &sequencias_count);
  }

  char sequencias[sequencias_count][103];
  
  pegandoSequencia(sequencias, sequencias_count, &max_string_size);

  system("clear");
  printf("\nVocê digitou %d sequencias com tamanho máximo de %d caracteres\n", sequencias_count, max_string_size);

  printf("\nSequencia inicial: \n\n");
  imprimirSequencia(sequencias, sequencias_count);

  printf("\nAlinhamento final:\n\n");

  int mesmoTamanho = 1;
  
  for (int i = 0; i < sequencias_count; i++)
  {
    if (strlen(sequencias[i]) != max_string_size)
    {
      mesmoTamanho = 0;
      break;
    }
  }

  if (mesmoTamanho) preencheGapFinal(sequencias, sequencias_count, &max_string_size);

  else preencherGapDiferente(sequencias, sequencias_count, &max_string_size); // em manutenção

  alinhaSequencias(sequencias, &max_string_size, sequencias_count); 

  imprimirSequencia(sequencias, sequencias_count);

  calcular_score(sequencias, sequencias_count, max_string_size);

  return 0;
}