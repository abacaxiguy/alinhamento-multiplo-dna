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
      if (sequencias[i][j] == '-') {
        gaps++;
        sum_pos_gaps += j;
        gaps_linha++;
        while (sequencias[i][j+1] == '-') {
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
  printf("pGapsFinais = (∑ posição dos gaps) * (nº de gaps): %d\n", pGapsFinais);
  score = score + pGapsFinais - pGapsJuntos;
  printf("\nFÓRMULA = score + pGapsFinais - pGapsJuntos\n");
  printf("\nSCORE FINAL: ");
  score > 0 ? printf("+%d\n", score) : printf("%d\n", score);
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
void preencheGapFinal(char seq[][103], int cont, int *maxSize)
{
  // checar se todas as sequencias possuem o mesmo tamanho
  int mesmoTamanho = 1;
  for (int i = 0; i < cont; i++)
  {
    if (strlen(seq[i]) != *maxSize)
    {
      mesmoTamanho = 0;
      break;
    }
  }
  if (mesmoTamanho)
  {
    // preencher dois gaps no final de cada sequencia
    for (int i = 0; i < cont; i++)
    {
      seq[i][*maxSize] = '-';
      seq[i][*maxSize + 1] = '-';
      seq[i][*maxSize + 2] = '\0';
    }

    *maxSize += 2;
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
}

// Essa função recebe uma sequencia, o tamanho max da sequencia e um índice.
// coloca todos os gaps que estão no final da sequencia p/ uma posição específica.
void trocaPosicaoGapFinal(int indice, int max, char *vetor)
{

  int rodando = 1;

  do
  {

    for (int i = max - 1; i > indice; i--)
    {
      vetor[i] = vetor[i - 1];
    }

    vetor[indice] = '-';

    if (vetor[max - 1] != '-')
    {
      rodando = 0;
    }

    indice += 1;

  } while (rodando);

}

//Preenche todos os índices do vetor com -1;
void limpaVetor(int *vetor, int tamanho){

    for(int i =0; i < tamanho; i++){
      vetor[i] = -1;
    }
}

//Verifica se um valor ja foi salvo no vetor.
int verificaValor(int vetor[], int tamanho, int valor){

    for(int i = 0; i < tamanho; i++){
        if(vetor[i] == valor){
            return 0;
        }
    }

    return 1;
}

//Procura um índice vazio (== -1) no vetor e preenche com o valor informado.
void insereFinalVetor(int *vetor, int tamanho, int valor){

  for(int i = 0; i < tamanho; i++){
      if(vetor[i] == -1){
          vetor[i] = valor;
          break;
      } 
  }
}

//Recebe uma sequencia e retorna quantos matchs ela conseguiu dar.
//Salva os índices que não deram match.
int comparaSequencias(char seq[][103], char seqAtual[], int indice, int numSeq, int max, int *dismatchs){

  int numMatchs = 0;
  int verificacao = 0;

  if(dismatchs[0] == -1){ //Só atualiza dismatchs se for a sequencia inserida pelo usuário.
      verificacao = 1;
  }

  for(int y = 0; y < max; y++){ //Percorre os caracteres da sequencia atual (colunas)

    for(int j = 0; j < numSeq; j++){ //percorre as sequencias (linhas) pra comparar os caracteres (colunas)

        if(j == indice){ //pulamos a sequencia atual. Não comparamos uma sequencia com ela mesma.
          continue;
        }

        if(seqAtual[y] == '-'){ //pulamos p/ o prox caracter.
          continue;
        }

        if(seqAtual[y] == seq[j][y]){ //Se der match com alguém finaliza. Não damos shift (por enquanto) se ja tiver dado um match
          numMatchs +=1;
          break;
        }

        // Se a posição não deu match, ela está eletiva a receber gaps.
        //Salvamos a posição no vetor caso essa posição já não tenha sido salva.
        if(verificacao && verificaValor(dismatchs, max, y)){
          insereFinalVetor(dismatchs, max, y);
        }
    }
  }

  return numMatchs;
}

// (Versão 2)
// Percorre a matriz de sequencias linha a linha, e compara a linha do índice atual com a de baixo.
// Se dois alinhamentos tiverem match's diferentes, mantém o que tiver mais match.
void alinhaSequencias(char seq[][103], int max, int nSeq){

    int numMatchs = 0;
    int numMatchs2 = 0;
    int dismatchs[max];
    char seqTemp[103];
    char seqTemp2[103];
    
    for(int x = 0; x < nSeq; x++){ //Percorre as sequencias (linhas)

      if(seq[x][max-1] != '-'){   // verificar se há gaps p/ realizar o shift;
          continue;
      }

      //Reseta os temporários:
      limpaVetor(dismatchs, max); 
      numMatchs = 0;

      //Verifica quantos matchs a sequencia deu e quais os índices dos dismatchs:
      numMatchs = comparaSequencias(seq, seq[x], x, nSeq, max, dismatchs);

       strcpy(seqTemp2,seq[x]);

      if(dismatchs[0] != -1){ 

        for(int i = 0; dismatchs[i] != -1; i++){   //testa todas as posições que não deram match.
          
          //Passa a sequencia atual p/ um vetor temporário.
          strcpy(seqTemp, seq[x]); 

          // Dá o gap nessa posição, mas passando o vetor temporário.
          trocaPosicaoGapFinal(dismatchs[i], max, seqTemp);

          //Verifica quantos gaps eu consegui com esse alinhamento:
          numMatchs2 = comparaSequencias(seq, seqTemp, x, nSeq, max, dismatchs);
          
          if(numMatchs2 > numMatchs){ //Se eu consegui mais gaps, mantém esse alinhamento e atualiza numMatchs;
              strcpy(seqTemp2, seqTemp); 
              numMatchs = numMatchs2;
          }
        }
      }

      strcpy(seq[x], seqTemp2); //Substitui pelo melhor alinhamento
    
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

  printf("\nAlinhamento final:\n\n");

  preencheGapFinal(sequencias, sequencias_count, &max_string_size);
  alinhaSequencias(sequencias, max_string_size, sequencias_count); 

  imprimirSequencia(sequencias, sequencias_count);

  calcular_score(sequencias, sequencias_count, max_string_size);

  return 0;
}