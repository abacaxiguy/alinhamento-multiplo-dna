#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHA 2 // A + A
#define BETA -1 // A + T
#define DELTA 1 // A + - // - + -

// Para funcionar de uma maneira que seja mais fácil de visualizar o alinhamento, 
// troque BETA e DELTA para:
// #define BETA 1
// #define DELTA -1

typedef struct no{
    char varSeq[10]; //Variação da coluna
    struct no *primogenito; //Primeiro filho 
    struct no *irmao; //Irmão ao lado
    int score;

}No;

No* criaNovoNo(char seq[]){
    No* novo = (No*)malloc(sizeof(No)); //Alloca memória para o novo nó

    novo->primogenito = NULL; //o NÓ ainda não possui filhos
    novo->irmao = NULL; //O NÓ ainda não possui irmão
    strcpy(novo->varSeq, seq);
    novo->score = 0;
    return(novo);
}

//Cria a raiz da árvore
No* iniciaArvore(char seq[]){
    return(criaNovoNo(seq));
}

//A função inserir deve receber o primeiro nó, o valor a ser colocado na árvore e o valor do elemento pai(pai do novo nó que será criado)
int inserir(No* pai, char seq[]){

    No* filho = criaNovoNo(seq); //Cria o nó do filho
    No* p = pai->primogenito; //verifica se o pai já tem um filho

    if(!p){ //Se não tiver filho, o novo nó será o primogênito
        pai->primogenito = filho; 
    
    }else{//Se ja tiver um filho

        while(p->irmao){ //Passa pelos filhos até encontrar um que tenha irmão = NULL;
            p = p->irmao; //Enquanto isso, auxiliar vai passando de irmão em irmão até encontrar o que tenha valor NULL.
        }

        //Após encontrado:
        p->irmao = filho;
        return 1;
    }
}

//Preenche todos os espaços de um vetor com um valor padrão
void resetaVetor(char vet[]){
    for(int i = 0; i<10; i++){
        vet[i] = ' ';
    }
}

//Copia uma coluna especificada da matriz p/ um vetor
void copiaColuna(char seq[][103], char vetCopia[], int max, int nSeq, int numColuna){

    //Limpa o vetor
    resetaVetor(vetCopia);

    //Realiza a cópia
    for(int x = 0; x<nSeq; x++){
        vetCopia[x] = seq[x][numColuna];
    }

}

int calcScoreColuna(char vet[], int nCol){

    int score = 0;

    for(int i = 0; i < nCol - 1 ; i++ ){
        
        for(int j = i+1; j < nCol; j++){

            if(vet[i] == '-' && vet[j] == '-'){
                score += DELTA;
            }

            if((vet[i] == '-' && vet[j] != '-') || (vet[i] != '-' && vet[j] == '-')){
                score += DELTA;
            }

            if(vet[i] != '-' && vet[j] != '-'){

                if(vet[i] == vet[j]){
                      score += ALPHA;
                }
            }
        }
    }

    return score;
}

//Calcula o score de todos os filhos do nó especificado e retorna o maior nó encontrado
No* devolveMaiorScore(No * pai, int nSeq){

    No *filho = pai->primogenito;
    No *maior = filho;

    while(filho!=NULL){
        filho->score = calcScoreColuna(filho->varSeq, nSeq);
        
        //Guarda o endereço do nó de maior score:
        if(maior->score < filho->score){
            maior = filho;
        }

        //Vai para o proximo irmão
        filho = filho->irmao;
    }

    return maior;
}

// Essa função recebe uma sequencia, o tamanho max da sequencia e um índice.
// coloca todos os gaps que estão no final da sequencia p/ uma posição específica.
void trocaPosicaoGapFinal(char matriz[][103], int linha, int indice, int max){
  for(int i = max-1; i > indice; i--){
      matriz[linha][i] = matriz[linha][i-1]; 
  }

      matriz[linha][indice] = '-';
}

void alinhaSequencias(char seq[][103], int max, int nSeq){

    // printf("Numero de sequencias:%d\n", nSeq);

    char vetTemp[10]; //Guarda a coluna atual

    //Copia a primeira coluna pro vetor temporário
    copiaColuna(seq, vetTemp, max, nSeq, 0);

    //Criar o primeiro nó da árvore:
    No* raiz = iniciaArvore(vetTemp);

    //Guarda o nó que possui o maior score
    No * paiAtual = raiz;

    //seq[linha][coluna]
    //percorre as colunas
    for(int y = 0; y< max; y++){
        
        // printf("y: %d\n", y);

        //Copia a coluna atual pra o vetor temporario
        //Se for a primeira coluna, vetTemp ja possui essa cópia
        if(y != 0){
            copiaColuna(seq, vetTemp, max, nSeq, y);
        }

        //Criação das variações:=================================================

        //A versão inserida pelo usuario também é uma variação válida
        inserir(paiAtual, vetTemp);

        //Define o numero de gaps:(1 - 10)-----------------------------------------------------------
        for(int n = 1; n <= nSeq; n++){

          // printf("n: %d\n", n);

          //Avança entre os indices da coluna pra aplicar as variações de gap:
          for(int i = 0; i< nSeq; i++){

            //Não tem gap no final da linha, vai pro próximo caracter
            if(seq[i][max-1] != '-'){
                continue;
            }

            //Reseta o vetor temporario
            copiaColuna(seq, vetTemp, max, nSeq, y);

            //variação 1: n Gaps em sequencia:-------------------------------------
            for(int j = i; j < (i+n); j++){
        
                //Verifica se há caracteres suficientes pra aplicar o numero de gaps desejado
                if(((i+n)-1) >= nSeq){
                  break;
                }

                //Verifica se há gaps no final pra aplicar nessa sequencia
                if(seq[j][max-1] != '-'){
                  continue;
                }

                vetTemp[j] = '-';
            }

            inserir(paiAtual, vetTemp);
            // printf("seq com n=%d gaps: %s\n", n, vetTemp);
            
             //Reseta o vetor temporario
            copiaColuna(seq, vetTemp, max, nSeq, y);

            //Variação 2: n Gaps alternados:-----------------------------------------
            //(pula uma posição pra aplicar o gap)
            for(int j = i; j <= (i+n)+1; j+=2){

                //gaps alternados só funciona a partir de 2 gaps
                if(n == 1){
                  break;
                }

                //Verifica se há caracteres suficientes pra aplicar o numero de gaps desejado
                if((((n-1)*2)+i) >= nSeq){
                  break;
                }

                //Verifica se há gaps no final pra aplicar nessa sequencia
                if(seq[j][max-1] != '-'){
                  continue;
                }

                vetTemp[j] = '-';
            }

            inserir(paiAtual, vetTemp);
            // printf("seq com n=%d gaps: %s\n", n, vetTemp);
          }
            
        }

        //Calcula o score e pega o nó de maior score:===================================
        paiAtual = devolveMaiorScore(paiAtual, nSeq);
        
        //Aplica os gaps do maior score na matriz:=============================================
        for(int i = 0; i<nSeq; i++){

          if(paiAtual->varSeq[i] == '-'){
              trocaPosicaoGapFinal(seq, i, y, max);
          }
            
        }

    }
}


//MATRIZ==============================================================


int verificaCharValidos(char seq[])
{
  for (int i = 0; seq[i] != '\0'; i++){
    if (i == 0 && seq[i] == '\n') return 0;
    else if (!isalpha(seq[i])) return 0;
  }
  return 1;
}

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

void imprimirSequencia(char sequencia[][103], int tamanhoSequencia)
{
    for (int i = 0; i < tamanhoSequencia; i++){
        printf("%s\n", sequencia[i]);
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

    printf("\nSequencia inicial: \n\n");
    imprimirSequencia(sequencias, sequencias_count);

    printf("\nAlinhamento com gaps no final:\n\n");

    preencheGapFinal(sequencias, sequencias_count, &max_string_size);
    imprimirSequencia(sequencias, sequencias_count);

    alinhaSequencias(sequencias, max_string_size, sequencias_count);

    printf("\nMelhor alinhamento:\n\n");

    imprimirSequencia(sequencias, sequencias_count);

    printf("\n");

    calcular_score(sequencias, sequencias_count, max_string_size);

    return 0;
}