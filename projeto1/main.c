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
  printf("pGapsFinais = (∑ posição dos gaps) + (nº de gaps): %d\n", pGapsFinais);
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

//Essa função realiza o shift um numero determinado de vezes
//linha = linha da matriz que será feito o shift
// indice = indice o primeiro gap será aplicado
// max = tamanho máximo das strings
// num gaps = Quantos vezes será realizado o shift a partir do índice inicial.
void trocaPosicaoGapFinal(char matriz[][103], int linha, int indice, int max, int num_gaps)
{
  for(int i = 0; i < num_gaps; i++){

    //passa todos os valores, a partir do ultimo índice uma casa pra frente:
    for(int j = max - 1; j > indice; j--){
      matriz[linha][j] = matriz[linha][j-1];
    } 

    //Aplica o gap no indice inicial informado
    matriz[linha][indice] = '-';

    //Atualiza o indice "inicial"
    indice+=1;

  }
}

//Preenche todos os índices de uma matriz 10x2 com -1;
void limpaMatriz(int matriz[][2]){

    
  for(int x = 0; x< 10; x++){
    for(int y = 0 ; y < 2; y++ ){
        matriz[x][y] = -1;
    }
  }

}

//Procura um índice vazio (== -1) na matriz e coloca nessas posições os valores passados.
void insereFinalMatriz(int matriz[][2], int valorX, int valorY){

    for(int x = 0; x < 10; x++){
      if(matriz[x][0] == -1){
          matriz[x][0] = valorX;
          matriz[x][1] = valorY; 
          break;
      }
    }
}

void alinhaSequencias(char seq[][103], int max, int nSeq){

    //Guardam temporariamente a posição que o caracter deu match.
    int xi, yi; 
    int pula_caracter;
    int quebra_loop;
    int num_gaps = 0, num_gaps2 = 0;

    //Esse vetor guardará temporariamente as coordenadas que deram match na matriz
    int posicoesMatch[10][2];

    //Percorre cada uma das colunas, exceto a última.
    for(int x = 0; x < (max - 1); x++){

      //Perocrre linha a linha da coluna
      for(int y = 0; y < nSeq; y++){

        //Reseta os temporarios:
        num_gaps = 0;
        pula_caracter = 0;
        limpaMatriz(posicoesMatch);

        //Verifica se há gaps para realizar o shift
        //Se não tem, vai pra prox linha.
        if(seq[y][max-1] != '-') continue;
          

        //Verifica se o caracter deu match com alguém na mesma coluna que ele
        //Se sim, não faz nada.
        for(int i = 0; i < nSeq; i++){
            
          //Verifica se o caracter atual, é o mesmo que está sendo ussado pra comparar;
          if(i == y) continue;

          if(seq[y][x] == '-') continue;
          
          if(seq[i][x] == seq[y][x]){
              pula_caracter = 1;
            break;
          }
          
        }

        // //Se o caracter atual deu match com alguém na coluna, vai pro prox caracter da mesma coluna.
        if(pula_caracter) continue;

        pula_caracter = 1;

        //Se o caracter não deu match na coluna, procura na matriz se existe outro caracter igual para dar match
        //Percorre as colunas:
        for(int x0 = (x+1); x0 < max; x0++){
          
          //percorre as linhas:
          for(int y0 = 0; y0 < nSeq; y0++){

            quebra_loop = 0;
            printf("%c ", seq[y0][x0]);

            //Se for a mesma linha do caracter que estamos verificando, pula pra prox linha:
            if(y0 == y) continue;

            //Verifica se os caracteres são iguais:
            if(seq[y0][x0] == seq[y][x]){
              printf("\n%c é igual %c\n", seq[y0][x0], seq[y][x] );

              //Se forem, guarda as coordenadas desse possível match;
              xi = x0;
              yi = y0;


              //Verifica se os caracteres subsequentes estão dando match com algum caracter
              //Pois, se algum caracter der match na mesma linha do possível match, não aplicaremos gaps
              //Se algum caracter der match, porém for em uma linha diferente do nosso possível match, da gap nas duas linhas p/manter o alinhamento.
              //Percorre a coluna:
              for(int x1 = (x+1); x1< max; x1++){
                
                //percorre a linha:
                for(int y1 = 0; y1<nSeq; y1++){

                  if(y1 == y) continue;

                  //Se tiver gap na posição, pula para a próxima
                  if( seq[y][x1] == '-' || seq[y1][x1] == '-' ) continue;

                  //Se encontrou algum algum caracter na mesma linha que deu match:
                  if(seq[y][x1] == seq[y1][x1] && seq[y][x1] != '-' && seq[y1][x1] ){
                    printf("OS PROXIMOS CARACTERES DÃO MATCH");

                    //Se esse match foi na mesma posição do possível match, descarta essa posição.
                    if(y1 == yi ){
                      printf("O MATCH DO PROX É NA PROX LINHA\n");
                      quebra_loop = 1;
                      pula_caracter = 0;
                      break;
                    }

                    //Se não for na mesma linha, guarda essa posição para saber quem vai andar junto depois.
                    insereFinalMatriz(posicoesMatch, x1, y1);
                  } 

                  pula_caracter = 1;

                }

                  if(quebra_loop) break;
              }

            }

          }

          printf("\n");

        }

        //Caso não encontre nenhum caracter que atenda das condições estabelecidas acima
        //vai pro prox caracter
        if(!pula_caracter) continue;

        //Se encontrou caracter pra dar match:
        //Verifica se há gaps suficientes p/ realizar o shift
        // //Contabiliza quantos gaps tem disponíveis:
        for(int i = 0; i < max; i++){ 
          if(seq[y][i] == '-') num_gaps++;

          if(seq[y][i] != '-' && num_gaps > 0) num_gaps--;
        }

        printf("num gaps: %d\n", num_gaps);

        printf("xi: %d\n", xi);

        printf("x: %d\n", x);

        int gapsNecessarios = xi - x;

        printf("gps necessários: %d\n", gapsNecessarios);

        //Verificar se o numero de gaps é suficiente p/ dar o match:
        if(gapsNecessarios <= num_gaps){
          printf("TEM GAPS SUFICIENTES\n");

          pula_caracter = 0;

          //Verifica se as posições subsequentes que deram match possuem a quantidade de gaps necessários:
          //Pois, se não possuirem, não será realizado o shift em nenhuma das linhas.
          for(int j = 0 ; j < 10; j++){
            
            printf("%d\n", posicoesMatch[0][j]);
            if(posicoesMatch[j][0] == -1){
              printf("BREAK\n");
              break;
            }
          

              for(int i = 0; i<max; i++){

                if(seq[posicoesMatch[j][1]][i] == '-') num_gaps2++;

                if(seq[y][i] != '-' && num_gaps2 > 0) num_gaps2--;
                
              }

              printf("numgaps2: %d\n", num_gaps2);
              
              //Se não tiverem gaps suficientes no final, não realiza nenhum shift
              if(gapsNecessarios > num_gaps2){
                  pula_caracter = 1;
                  break;
              }

          }

          //Se está tudo correto, realiza o shift, em todas as posições necessárias:
          if(!pula_caracter){
              
            trocaPosicaoGapFinal(seq, y, x, max, num_gaps);

            for(int j = 0; j < 10; j++){
              if(posicoesMatch[j][0] == -1){
                break;
              }

              trocaPosicaoGapFinal(seq, posicoesMatch[j][1], posicoesMatch[j][0], max, num_gaps);

            }

          }
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

  preencheGapFinal(sequencias, sequencias_count, &max_string_size);
  imprimirSequencia(sequencias, sequencias_count);

  printf("\n");

  printf("\nMelhor alinhamento:\n\n");

  alinhaSequencias(sequencias, max_string_size, sequencias_count); 

  imprimirSequencia(sequencias, sequencias_count);

  printf("\n");

  calcular_score(sequencias, sequencias_count, max_string_size);

  return 0;
}