/*********************************************************************/
/**   ACH2024 - Algoritmos e Estruturas de Dados II                 **/
/**   EACH-USP - Primeiro Semestre de 2024                          **/
/**   Turma 04 - Prof. Luciano Digiampietri                         **/
/**                                                                 **/
/**   Primeiro Exercicio-Programa                                   **/
/**                                                                 **/
/**   <Wesley Gabriel Rosa Fernandes>               <13716893>      **/
/**                                                                 **/
/*********************************************************************/

// gcc completeERenomeie.c -lm

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define true 1
#define false 0

typedef int bool;

/* Estrutura para representar nosso grafo usando matriz binaria de adjacencias */
typedef struct {
  int numVertices;
  int numArestas;
  bool** matriz;
} Grafo;


/* Funcao auxiliar para o sistema de correcao automatica (nao mexer) */
void printf123(){
    // Funcao usada pelo sistema de correcao automatica (nao mexer)
}


/* Funcao que inicializa o grafo cujo endereco foi passado como parametro.
   Isto e, cria a matriz de adjacencias (preenchida com false),
   e atribui valor para numVertices (recebendo o valor passado por parametro)
   e numArestas igual a zero.
*/
bool inicializaGrafo(Grafo* g, int vertices){
  if (g==NULL || vertices<1) return false;
  g->numVertices = vertices;
  g->numArestas = 0;
  int x, y;
  g->matriz = (bool**) malloc(sizeof(bool*)*vertices);
  for (x=0; x<vertices; x++){
    g->matriz[x] = (bool*) malloc(sizeof(bool)*vertices);
    for (y=0; y<vertices; y++){
      g->matriz[x][y] = false;
    }
  }
  return true;
}


/* Funcao que libera a memoria da matriz de adjacencia do grafo cujo endereco
   foi passado como parametro.
*/
bool liberaGrafo(Grafo* g){
  if (g==NULL) return false;
  int x;
  for (x=0; x<g->numVertices; x++)
    free(g->matriz[x]);
  free(g->matriz);
  g->numVertices = 0;
  g->numArestas = 0;
  g->matriz = NULL;
  return true;
}

/* Funcao que retorna o numero de vertices do grafo apontado por g, caso o 
   endereco armazenado em g seja diferente de NULL. Caso contrario, retorna -1.
*/
int numeroDeVertices(Grafo* g){
  if (g != NULL) return g->numVertices;
  else return -1;
}


/* Funcao que retorna o numero de arestas do grafo apontado por g, caso o 
   endereco armazenado em g seja diferente de NULL. Caso contrario, retorna -1.
*/
int numeroDeArestas(Grafo* g){
  if (g != NULL) return g->numArestas;
  else return -1;
}


/* Funcao que retorna o grau do vertice v, caso ele exista.
   Caso contrario, retorna -1.
*/
int retornaGrauDoVertice(Grafo* g, int v){
  if (!g || v < 0 || v >= g->numVertices) return -1;
  int x, grau = 0;
  for (x=0;x<g->numVertices;x++){
    if (g->matriz[v][x]) grau++;
  }
  return grau;
}


/* Funcao que retorna true se o vertice v possui um ou mais
   vertices adjacentes (vizinhos).
*/
bool possuiVizinhos(Grafo* g, int v){
  if (!g || v < 0 || v >= g->numVertices) return false;
  int x;
  for (x=0;x<g->numVertices;x++)
    if (g->matriz[v][x]) return true;
  return false;
}


/* Funcao que insere uma nova aresta no grafo.
   Se os vertices passados como parametro forem validos, ha duas possibilidades:
   - a aresta nao existia;
   - a aresta existia. 
*/
bool insereAresta(Grafo* g, int v1, int v2){
  if (!g || v1 < 0 || v2 < 0 || v1 >= g->numVertices || v2 >= g->numVertices || v1 == v2) return false;
  if (g->matriz[v1][v2] == false){
      g->matriz[v1][v2] = true;
      g->matriz[v2][v1] = true;
      g->numArestas++;
  }
  return true;
}


/* Funcao que exclui a aresta entre v1 e v2 (caso exista uma aresta valida
   entre v1 e v2) e retorna true; ou retorna false, caso contrario.
*/
bool removeAresta(Grafo* g, int v1, int v2){
  if (!g || v1 < 0 || v2 < 0 || v1 >= g->numVertices || v2 >= g->numVertices || g->matriz[v1][v2] == false) return false;
  g->matriz[v1][v2] = false;
  g->matriz[v2][v1] = false;
  g->numArestas--;
  return true;
}


/* Funcao que retorna true se existe uma aresta valida entre v1 e v2 
   e false caso contrario.
*/
bool arestaExiste(Grafo* g, int v1, int v2){
  if (!g || v1 < 0 || v2 < 0 || v1 >= g->numVertices || v2 >= g->numVertices || g->matriz[v1][v2] == false) return false;
  return true;
}


/* Funcao que cria um grafo com o numero de vertices e
   numero de arestas passados como parametro e retorna seu endereco.
*/
Grafo* criaGrafoAleatorio(int numVertices, int numArestas){
  printf("################# Criando grafo com %i vertice(s) e com %i aresta(s). #################\n",numVertices, numArestas);
  int x, y, a = 0;
  if (numVertices < 1 || numArestas >= numVertices*(numVertices-1)/2) {
    printf("Parametros invalidos, o grafo nao sera gerado.\n");
    return NULL;  
  }
  Grafo* g = (Grafo*)malloc(sizeof(Grafo));
  inicializaGrafo(g,numVertices);
  while(a<numArestas){
    x = rand()%numVertices;
    y = rand()%numVertices;
    if (x!=y && g->matriz[x][y] == false){
      g->matriz[x][y] = true;
      g->matriz[y][x] = true;
      a++;
    }
  }
  g->numArestas = numArestas;
  return g;
}


/* Funcao desenvolvida para exibir um grafo, no formato de uma matriz
   de adjacencia.
*/
void exibeGrafo(Grafo* g){
  if(!g) return;
  int x, y;
  printf("\nImprimindo grafo (vertices: %i; arestas: %i).\n   ", g->numVertices, g->numArestas);
  for (x=0;x<g->numVertices;x++) printf(" %3i",x);
  printf("\n");
  for (x=0;x<g->numVertices;x++){
    printf("%3i",x);
    for (y=0;y<g->numVertices;y++)
      printf(" %3i",g->matriz[x][y]);  
    printf("\n");
  }
  printf("\n");
}


/* Funcao que exibe os valores de um arranjo de numeros reais */
void exibeArranjoReais(float* arranjo, int n){
  int x;
  for (x=0; x<n; x++) printf("  v%i\t", x);
  printf("\n");
  for (x=0; x<n; x++){
    printf("%3.2f\t",arranjo[x]);
  }
  printf("\n\n");
}


/* Funcao que exibe os valores de um arranjo de numeros inteiros */
void exibeArranjoInteiros(int* arranjo, int n){
  int x;
  for (x=0; x<n; x++) printf(" v%i\t", x);
  printf("\n");
  for (x=0; x<n; x++){
    printf("%3i\t",arranjo[x]);
  }
  printf("\n\n");
}



/* FUNCOES QUE DEVEM SER COMPLETADAS PARA RESOLVER O EP.
   A DESCRICAO DE CADA FUNCAO ESTA NO ENUNCIADO DO EP.
   www.each.usp.br/digiampietri/ACH2024/ep1/ep1.pdf        */

/* Vizinhos em Comum */
void vizinhosEmComum(Grafo* g, int v, int* vizinhos){

  if(!possuiVizinhos(g, v)){ //utilizamos a funcao possui vizinhos para verificar se o vertice possui vizinhos
    return;
  }

  //passando pela verificação se possui vizinhos, o seguimos com o seguinte calculo
  for (int i = 0; i < g->numVertices; i++) {
        vizinhos[i] = 0;
  } //Aqui, inicializamos o Array de vizinhos

  for (int i = 0; i < g->numVertices; i++) {
    if (g->matriz[v][i]) { //Se v eh vizinho de i, então verificaremos os vizinhos de i
      for (int j = 0; j < g->numVertices; j++) {
        if (g->matriz[i][j]) { //
          // Se i eh vizinho de j incrementa a contagem de vizinhos em comum entre v e j
            vizinhos[j]++;
        }
      }
    }
  }
}//Em resumo, usamos o primeiro for para ter i como vizinho simultaneo de v e j, por isso incrementamos a posição j do array vizinhos


/* Coeficiente de Jaccard */
void coeficienteDeJaccard(Grafo* g, int v, float* coeficientes){

  int* intersection = (int*)malloc(sizeof(int) * g->numVertices);//a interseccao de vizinhos
  vizinhosEmComum(g, v, intersection);//Armazenando a quantidade de vizinhos em comum de v para cada vertice em seu indice

  //laco de iteracao para calcular o coeficiente para cada posicao do vetor
  for(int i= 0; i<g->numVertices; i++){

    //inicializando o vetor
    coeficientes[i] = 0;

    //Calculamos o divisor da operacao (uniao de v com i menos a interseccao de v com i para eliminar contagens duplicadas [T(vUi) - T(v^i)] )
    int divisor = retornaGrauDoVertice(g, v) + retornaGrauDoVertice(g,i) - intersection[i];
    if(divisor == 0){

      //Caso o denominador seja igual a 0, atribuimos o valor de -1
      coeficientes[i] = -1.0;
    } else{

    //calculamos o coeficiente para cada i em relacao a v e armazenamos no array
      coeficientes[i] = (float)intersection[i]/(float)divisor;
    }
  }
  free(intersection);//liberando a memoria alocada dinamicamente
}


/* Medida Adamic Adar */
void AdamicAdar(Grafo* g, int v, float* coeficientes){

  //inicializamos o array
  for(int i = 0; i<g->numVertices; i++){
    coeficientes[i] = 0;//inicializa as posicoes do array com 0
  }

  for(int i=0; i<g->numVertices; i++){//iterando os vizinhos i em relacao a v
    if(g->matriz[v][i]){//verificando de v eh vizinho de i
      for(int j = 0; j<g->numVertices; j++){//iterando os vizinhos j em relacao a i
        if(g->matriz[i][j]){//verificando se i eh vizinho de j
          coeficientes[j] += 1/log(retornaGrauDoVertice(g, i));//incrementando ao vetor do array + 1/log(grau(i))
        }
      }
    }
  }
}


/* Alocacao de Recursos */
void alocacaoDeRecursos(Grafo* g, int v, float* coeficientes){

  // Inicializamos o array
  for(int i = 0; i<g->numVertices; i++){//iterando as posicoes do array
    coeficientes[i] = 0;//inicializando o array
  }

  for(int i=0; i<g->numVertices; i++){//iterando os vizinhos i de v
    if(g->matriz[v][i]){//checando de i eh vizinho de v
      for(int j = 0; j<g->numVertices; j++){//iterando os vizinhos de i em relacao a j
        if(g->matriz[i][j]){//verificando se i e j sao vizinhos
          coeficientes[j] += 1/(float)retornaGrauDoVertice(g, i);//somando a alocacao de recursos 1/|grau|
        }
      }
    }
  }

}


/* Similaridade Cosseno */
void similaridadeCosseno(Grafo* g, int v, float* coeficientes){

  int* intersection = (int*)malloc(sizeof(int)*g->numVertices);//inicializando um array auxiliar da intersecao de v em relacao a cada vizinho i
  vizinhosEmComum(g, v, intersection);//armazenando o modulo da interseccao

  for(int i = 0; i<g->numVertices; i++){//iterando a interseccao dos vizinho de v em relacao a i

    coeficientes[i] = 0;//inicializando as posicoes do vetor de pontos flutantes
    if(sqrt(retornaGrauDoVertice(g,v)*retornaGrauDoVertice(g,i)) == 0){//verificando se o denominador eh igual a 0
      coeficientes[i] = -1;
    }else {
      coeficientes[i] = (float)intersection[i]/sqrt(retornaGrauDoVertice(g,v)*retornaGrauDoVertice(g,i));//atribuindo o valor da similaridade
    }
  }
  free(intersection);//liberando a memoria alocada dinamicamente
}


/* Coeficiente de Dice */
void coeficienteDeDice(Grafo* g, int v, float* coeficientes){

  const float two = 2;//criando a constante contida no calculo de dice
  int* intersection = (int*)malloc(sizeof(int)*g->numVertices);//alocando memoria dinamicamente para a nossa variavel local
  vizinhosEmComum(g, v, intersection);//armazenando o valor dos vizinhos em comum

  for(int i = 0; i<g->numVertices; i++){//iterando novamente o array
    coeficientes[i] = 0;//inicalizando posicoes 
    if(retornaGrauDoVertice(g, v) + retornaGrauDoVertice(g, i) == 0){//checando se o denominador eh igual a zero
      coeficientes[i] = -1;//armazena -1 caso o denominador seja igual a zero
    }else {
      //armazena o coeficiente de dice
      coeficientes[i] = (two*(float)intersection[i])/((float)retornaGrauDoVertice(g, v) +(float)retornaGrauDoVertice(g, i));
    }
  }
  free(intersection);//libera memoria alocada dinamicamente
}


/* Hub Promoted Index */
void HPI(Grafo* g, int v, float* coeficientes){

  int* intersection = (int*)malloc(sizeof(int)*g->numVertices);//aloca memoria dinamicamente para a nossa variavel local
  vizinhosEmComum(g, v, intersection);//armazena o valor da interseccao na posicao do array

  for(int i = 0; i<g->numVertices; i++){//itera novamente a
    coeficientes[i] = 0;//inicializa a posicao do array  
    if(retornaGrauDoVertice(g, v) + retornaGrauDoVertice(g, i) == 0){//verifica se o denominador eh igual a zero
      coeficientes[i] = -1;//atribui o valor -1 par ao denominador igual a 0
    }else {
      //atribui o valor do Promoted Index
      coeficientes[i] = (float)intersection[i]/fmin(retornaGrauDoVertice(g, v), retornaGrauDoVertice(g, i));
    }
  }
  free(intersection);//libera a memoria alocada dinamicamente na funcao
}


/* Hub Depressed Index */
void HDI(Grafo* g, int v, float* coeficientes){

  int* intersection = (int*)malloc(sizeof(int)*g->numVertices);//aloca memoria dinamicamente para nossa variavel local
  vizinhosEmComum(g, v, intersection);//armazena a intersecao dos vizinhos de v em relacao a cada vertice i

  for(int i = 0; i<g->numVertices; i++){//itera as posicoes dos coeficientes
    coeficientes[i] = 0;//inicializa as posicoes do vetor 
    if(retornaGrauDoVertice(g, v) + retornaGrauDoVertice(g, i) == 0){//verifica se o denominador eh igual a 0
      coeficientes[i] = -1;//retorna o valor -1 caso o denominador seja igual a 0
    }else {
      //Armazena o Depressed Index
      coeficientes[i] = (float)intersection[i]/fmax(retornaGrauDoVertice(g, v), retornaGrauDoVertice(g, i));
    }
  }
  free(intersection);
}


/* Funcao main para testar as funcoes implementadas neste EP.
   Esta parte do codigo nao sera usada na correcao do EP e nao contempla
   todos os testes possiveis.
   Fique a vontade para realizar testes adicionais.
*/
int main() {

  int n = 5;
  int* vComum = (int*)malloc(sizeof(int)*n);
  float* coeficientes = (float*)malloc(sizeof(float)*n);
  
  Grafo g1;

  printf("PRIMEIRO EXEMPLO\n");

  inicializaGrafo(&g1, n);
  insereAresta(&g1,0,1);
  insereAresta(&g1,0,2);
  insereAresta(&g1,1,4);
  insereAresta(&g1,1,3);
  insereAresta(&g1,2,3);

  exibeGrafo(&g1);

  printf("Vizinhos em Comum de v0:\n");
  vizinhosEmComum(&g1, 0, vComum);
  exibeArranjoInteiros(vComum, n);

  printf("Coeficientes de Jaccard de v0:\n");
  coeficienteDeJaccard(&g1, 0, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Medida de Adamic-Adar de v0:\n");
  AdamicAdar(&g1, 0, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Medida de Alocacao de Recursos de v0:\n");
  alocacaoDeRecursos(&g1, 0, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Similaridade Cosseno de v0:\n");
  similaridadeCosseno(&g1, 0, coeficientes);
  exibeArranjoReais(coeficientes, n);

  coeficienteDeDice(&g1, 0, coeficientes);
  printf("Coeficiente de Dice de v0:\n");
  exibeArranjoReais(coeficientes, n);

  HPI(&g1, 0, coeficientes);
  printf("Indice HPI de v0:\n");
  exibeArranjoReais(coeficientes, n);

  HDI(&g1, 0, coeficientes);
  printf("Indice HDI de v0:\n");
  exibeArranjoReais(coeficientes, n);

  printf("\n\nSEGUNDO EXEMPLO\n");

  // Excluindo duas arestas do grafo
  removeAresta(&g1,0,2);
  removeAresta(&g1,2,3);


  exibeGrafo(&g1);

  printf("Vizinhos em Comum de v0:\n");
  vizinhosEmComum(&g1, 0, vComum);
  exibeArranjoInteiros(vComum, n);

  printf("Coeficientes de Jaccard de v0:\n");
  coeficienteDeJaccard(&g1, 0, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Medida de Adamic-Adar de v0:\n");
  AdamicAdar(&g1, 0, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Medida de Alocacao de Recursos de v0:\n");
  alocacaoDeRecursos(&g1, 0, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Similaridade Cosseno de v0:\n");
  similaridadeCosseno(&g1, 0, coeficientes);
  exibeArranjoReais(coeficientes, n);

  coeficienteDeDice(&g1, 0, coeficientes);
  printf("Coeficiente de Dice de v0:\n");
  exibeArranjoReais(coeficientes, n);

  HPI(&g1, 0, coeficientes);
  printf("Indice HPI de v0:\n");
  exibeArranjoReais(coeficientes, n);

  HDI(&g1, 0, coeficientes);
  printf("Indice HDI de v0:\n");
  exibeArranjoReais(coeficientes, n);


  /* Grafo gerado aleatoriamente - pode ficar diferente
     de acordo com o compilador usado.                 */
  printf("\nTERCEIRO EXEMPLO\n");
  n = 6;
  int arestas = 8;
  
  free(vComum);
  free(coeficientes);
  vComum = (int*)malloc(sizeof(int)*n);
  coeficientes = (float*)malloc(sizeof(float)*n);
  
  Grafo* g2 = criaGrafoAleatorio(n,arestas);
  exibeGrafo(g2);
  
  printf("Vizinhos em Comum de v0:\n");
  vizinhosEmComum(g2, 0, vComum);
  exibeArranjoInteiros(vComum, n);

  printf("Vizinhos em Comum de v1:\n");
  vizinhosEmComum(g2, 1, vComum);
  exibeArranjoInteiros(vComum, n);

  printf("Vizinhos em Comum de v5:\n");
  vizinhosEmComum(g2, 5, vComum);
  exibeArranjoInteiros(vComum, n);


  printf("Coeficientes de Jaccard de v0:\n");
  coeficienteDeJaccard(g2, 0, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Coeficientes de Jaccard de v1:\n");
  coeficienteDeJaccard(g2, 1, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Coeficientes de Jaccard de v5:\n");
  coeficienteDeJaccard(g2, 5, coeficientes);
  exibeArranjoReais(coeficientes, n);


  printf("Medida de Adamic-Adar de v0:\n");
  AdamicAdar(g2, 0, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Medida de Adamic-Adar de v1:\n");
  AdamicAdar(g2, 1, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Medida de Adamic-Adar de v5:\n");
  AdamicAdar(g2, 5, coeficientes);
  exibeArranjoReais(coeficientes, n);


  printf("Medida de Alocacao de Recursos de v0:\n");
  alocacaoDeRecursos(g2, 0, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Medida de Alocacao de Recursos de v1:\n");
  alocacaoDeRecursos(g2, 1, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Medida de Alocacao de Recursos de v5:\n");
  alocacaoDeRecursos(g2, 5, coeficientes);
  exibeArranjoReais(coeficientes, n);


  printf("Similaridade Cosseno de v0:\n");
  similaridadeCosseno(g2, 0, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Similaridade Cosseno de v1:\n");
  similaridadeCosseno(g2, 1, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Similaridade Cosseno de v5:\n");
  similaridadeCosseno(g2, 5, coeficientes);
  exibeArranjoReais(coeficientes, n);


  coeficienteDeDice(g2, 0, coeficientes);
  printf("Coeficiente de Dice de v0:\n");
  exibeArranjoReais(coeficientes, n);

  printf("Coeficiente de Dice de v1:\n");
  coeficienteDeDice(g2, 1, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Coeficiente de Dice de v5:\n");
  coeficienteDeDice(g2, 5, coeficientes);
  exibeArranjoReais(coeficientes, n);


  HPI(g2, 0, coeficientes);
  printf("Indice HPI de v0:\n");
  exibeArranjoReais(coeficientes, n);

  printf("Indice HPI de v1:\n");
  HPI(g2, 1, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Indice HPI de v5:\n");
  HPI(g2, 5, coeficientes);
  exibeArranjoReais(coeficientes, n);
  
  
  HDI(g2, 0, coeficientes);
  printf("Indice HDI de v0:\n");
  exibeArranjoReais(coeficientes, n);

  printf("Indice HDI de v1:\n");
  HDI(g2, 1, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Indice HDI de v5:\n");
  HDI(g2, 5, coeficientes);
  exibeArranjoReais(coeficientes, n);

  return 0;  
}