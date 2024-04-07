/*********************************************************************/
/**   ACH2024 - Algoritmos e Estruturas de Dados II                 **/
/**   EACH-USP - Primeiro Semestre de 2024                          **/
/**   Turma 04 - Prof. Luciano Digiampietri                         **/
/**                                                                 **/
/**   Segundo Exercicio-Programa                                    **/
/**                                                                 **/
/**   <Wesley Gabriel Rosa Fernandes>           <13716893>          **/
/**                                                                 **/
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0

#define INFINITO 999999999

typedef int bool;
typedef float Peso;

/* Estrutura para representar elementos de uma lista ligada de vertices */
typedef struct aux{
  int vertice;
  Peso peso;
  struct aux* prox;
} ElemLista, *PONT;


/* Estrutura para representar nosso grafo usando matriz de adjacencia binaria */
typedef struct {
  int numVertices;
  int numArestas;
  ElemLista** A;
} Grafo;


/* Funcao que inicializa o grafo cujo endereco foi passado como parametro.
   Isto e, cria o arranjo de listas de adjacencias (preenchido com NULL),
   e atribui valor para numVertices (recebendo o valor passado por parametro)
   e numArestas igual a zero.
*/
bool inicializaGrafo(Grafo* g, int vertices){
  if (g==NULL || vertices<1) return false;
  g->numVertices = vertices;
  g->numArestas = 0;
  int x, y;
  g->A = (ElemLista**) malloc(sizeof(ElemLista*)*vertices);
  for (x=0; x<vertices; x++){
    g->A[x] = NULL;
  }
  return true;
}


/* Funcao que libera a memoria da matriz de adjacencia do grafo cujo endereco
   foi passado como parametro.
*/
bool liberaGrafo(Grafo* g){
  if (g==NULL) return false;
  int x;
  ElemLista *atual, *apagar;
  for (x=0; x<g->numVertices; x++){
    atual = g->A[x];
    while (atual){
      apagar = atual;
      atual = atual->prox;
      free(apagar);
    }
  }
  free(g->A);
  g->numVertices = 0;
  g->numArestas = 0;
  g->A = NULL;
  return true;
}

/* Funcao que retorna o numero de nos do grafo apontado por g, caso o endereco 
   armazenado em g seja diferente de NULL. Caso contrario, retorna -1.
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
  for (x=0; x<g->numVertices; x++){
    ElemLista* atual = g->A[x];
    while (atual){
      if (x == v) grau++;
      if (atual->vertice == v) grau++;
      atual = atual->prox;
    }
  }
  return grau;
}

/* Funcao que retorna verdadeiro se o vertice v possui um ou mais
   vertices adjacentes (vizinhos).
*/
bool possuiVizinhos(Grafo* g, int v){
  if (!g || v < 0 || v >= g->numVertices || !(g->A[v])) return false;
  return true;
}

/* Funcao que retorna uma lista ligada de vizinhos do vertice v 
   (mais especificamente, o endereco do primeiro elemento da lista).
   Se o vertice nao existir ou nao possuir vizinhos retorna NULL.
*/
PONT listaDeVizinhos(Grafo* g, int v){
  if (!g || v < 0 || v >= g->numVertices) return NULL;
  return g->A[v];
}



/* Funcao auxiliar que cria um elemento do tipo ElemLista com os valores 
   recebidos como parametros e retorna o endereco desse elemento.   
*/
ElemLista* novoElemento(int vertice, ElemLista* prox){
  ElemLista* novo = (ElemLista*) malloc(sizeof(ElemLista));
  novo->vertice = vertice;
  novo->prox = prox;
  return novo;
}



/* Funcao que insere uma nova aresta no grafo ou atualiza o valor de uma aresta existente.
   Se os vertices passados como parametro forem validos, ha duas possibilidades:
   a aresta nao existia ou a aresta existia (atualizacao de peso).
*/
bool insereAresta(Grafo* g, int v1, int v2, Peso peso){
  if (!g || v1 < 0 || v2 < 0 || v1 >= g->numVertices || v2 >= g->numVertices) return false;
  ElemLista *novo, *ant = NULL;
  ElemLista* atual = g->A[v1];
  while (atual && atual->vertice<v2){
    ant = atual;
    atual = atual->prox;
  }
  if (atual && atual->vertice==v2) { // ja existe
    atual->peso = peso;
    return true;
  }
  novo = (ElemLista*)malloc(sizeof(ElemLista));
  novo->vertice = v2;
  novo->peso = peso;
  novo->prox = atual;
  if (ant) ant->prox = novo;
  else g->A[v1] = novo;
  g->numArestas++;
  return true;
}


/* Funcao que exclui a aresta entre v1 e v2 (caso exista uma aresta valida
   entre v1 e v2) e retorna true; ou retorna false, caso contrario.
*/
bool removeAresta(Grafo* g, int v1, int v2){
  if (!g || v1 < 0 || v2 < 0 || v1 >= g->numVertices || v2 >= g->numVertices) return false;
  ElemLista* ant = NULL;
  ElemLista* atual = g->A[v1];
  while (atual && atual->vertice<v2){
    ant = atual;
    atual = atual->prox;
  }
  if (atual && atual->vertice==v2){
    if (ant) ant->prox = atual->prox;
    else g->A[v1] = atual->prox;
    free(atual);
    g->numArestas--;
    return true;
  }
  return false;
}



/* Funcao que retorna true se existe uma aresta valida entre v1 e v2 
   e false caso contrario.
*/
bool arestaExiste(Grafo* g, int v1, int v2){
  if (!g || v1 < 0 || v2 < 0 || v1 >= g->numVertices || v2 >= g->numVertices) return false;
  ElemLista* atual = g->A[v1];
  while (atual && atual->vertice<v2)
    atual = atual->prox;
  if (atual && atual->vertice==v2) return true;
  return false;
}


/* Funcao que retorna o peso da aresta, se existe uma aresta valida entre v1 e v2 
   e -1 caso contrario.
*/
Peso pesoAresta(Grafo* g, int v1, int v2){
  if (!g || v1 < 0 || v2 < 0 || v1 >= g->numVertices || v2 >= g->numVertices) return false;
  ElemLista* atual = g->A[v1];
  while (atual && atual->vertice<v2)
    atual = atual->prox;
  if (atual && atual->vertice==v2) return atual->peso;
  return -1;
}


/* Funcao que cria um grafo com o numero de vertices e
   numero de arestas passados como parametro e retorna seu endereco.
*/
Grafo* criaGrafoAleatorio(int numVertices, int numArestas){
  printf("################# Criando grafo com %i vertice(s) e com %i aresta(s). #################\n",numVertices, numArestas);
  int x, y, a;
  Peso matriz[numVertices][numVertices]; // utilizaremos esta matriz auxiliar
  for (x=0;x<numVertices;x++)
    for (y=numVertices-1;y>=0;y--)
      matriz[x][y]=-1;
  if (numVertices < 1 || numArestas >= numVertices*(numVertices-1)/2) {
    printf("Parametros invalidos, o grafo nao sera gerado.\n");
    return NULL;  
  }
  Grafo* g = (Grafo*)malloc(sizeof(Grafo));
  inicializaGrafo(g,numVertices);

  a = 0;
  while(a<numArestas){
    x = rand()%numVertices;
    y = rand()%numVertices;
    if (matriz[x][y] == -1){
      matriz[x][y] = rand()%99 + 1;
      matriz[y][x] = matriz[x][y];
      a++;
    }
  }
  ElemLista* novo;
  for (x=0;x<numVertices;x++)
    for (y=numVertices-1;y>=0;y--)
      if (matriz[x][y]!=-1){
        novo = (ElemLista*)malloc(sizeof(novo));
        novo->prox = g->A[x];
        novo->vertice = y;
        novo->peso = matriz[x][y];
        g->A[x] = novo;         
      }
  g->numArestas = numArestas;
  return g;
}



/* Funcao desenvolvida para exibe um grafo, no formato de uma matriz
   de adjacencia.
*/
void exibeGrafo(Grafo* g){
  if (!g) return;
  printf("\nImprimindo grafo (vertices: %i; arestas: %i).\n", g->numVertices, g->numArestas);
  ElemLista* atual;
  int x;
  for (x=0;x<g->numVertices;x++){
    printf("[%2i]",x);
    atual = g->A[x];
    while (atual){
      printf(" ->%3i (%5.2f)",atual->vertice,atual->peso);  
      atual = atual->prox;
    }
    printf("\n");
  }
}


/* Funcao que exibe os vertices de uma lista ligada de vertices iniciada
   pelo endereco do parametro 'atual'.
*/
void exibeLista(PONT atual){
  printf("Imprimindo lista ligada de vertices (vizinhos).\n");
  while (atual != NULL){
    printf(" %i ", atual->vertice);
    atual = atual->prox;
  }
  printf("\n");
}

/* Funcao que libera a memoria de uma lista ligada iniciada em 'atual'.
*/
void liberaLista(PONT atual){
  PONT apagar;
  while (atual != NULL){
    apagar = atual;
    atual = atual->prox;
    free(apagar);
  }
}


/* Funcao que exibe um arranjo, representando um ciclo.
*/
void exibeCiclo(int* arranjo, int n){
  printf("Ordem das cidades:");
  int x, y;
  for (x=0; x<n; x++){
    printf(" %i",arranjo[x]);
  }
  printf("\n\n");
}


/* Variaveis Globais usadas para resolver o problema */
int* cicloAtual;
int* melhorCiclo;
bool* visitado;
Peso melhorValor;
Peso valorAtual;


/* Funcao auxiliar, potencialmente recursiva, que ira resolver
   o problema do caixeiro viajante.
   Esta funcao eh inicialmente chamada pela funcao caixeiroViajante */
void caixeiroAux(Grafo*g, int atual, int numVisitados){

/* Complete o codigo desta funcao */  
  
}


/* Funcao principal / inicial para a resolucao do problema do Caixeiro
   Viajante. Esta funcao inicializa as variaveis globais e chama a funcao 
   caixeiroAux ja indicando que a cidade atual corresponde ao vertice 0 (zero)
   e que este vertice ja esta visitado, sendo a primeira cidade do ciclo.
*/
bool caixeiroViajante(Grafo* g){
  int n = g->numVertices;
  cicloAtual = (int*) malloc(sizeof(int)*n);
  melhorCiclo = (int*) malloc(sizeof(int)*n);
  visitado = (bool*) malloc(sizeof(bool)*n);
  int x;
  bool resultado;
  for (x=0;x<n;x++) visitado[x] = 0;
  melhorValor = INFINITO;
  valorAtual = 0;
  cicloAtual[0] = 0;
  visitado[0] = true;
  caixeiroAux(g, 0, 1);
  if (melhorValor < INFINITO) return true;
  else return false;
}


/* Funcao main para realizar alguns testes iniciais sobre o EP 2.
*/
int main() {
  Grafo g1;
  inicializaGrafo(&g1, 1);
  printf("\n##### Primeiro problema: uma cidade e nenhuma aresta (nao ha solucao).\n");
  exibeGrafo(&g1);
  if (caixeiroViajante(&g1)){
    printf("Custo encontrado: %.2f\n", melhorValor); 
    exibeCiclo(melhorCiclo, g1.numVertices);
  }else printf("Nenhuma solucao foi encontrada.\n");

  printf("\n##### Segundo problema: uma cidade e uma aresta (ha solucao).\n");
  insereAresta(&g1, 0, 0, 5);
  exibeGrafo(&g1);
  if (caixeiroViajante(&g1)){
    printf("Custo encontrado: %.2f\n", melhorValor); 
    exibeCiclo(melhorCiclo, g1.numVertices);
  }else printf("Nenhuma solucao foi encontrada.\n");


  Grafo g2;
  inicializaGrafo(&g2, 2);
  insereAresta(&g2, 0, 1, 3);
  insereAresta(&g2, 1, 1, 5);
  printf("\n##### Terceiro problema: duas cidades (nao ha solucao).\n");
  exibeGrafo(&g2);
  if (caixeiroViajante(&g2)){
    printf("Custo encontrado: %.2f\n", melhorValor); 
    exibeCiclo(melhorCiclo, g2.numVertices);
  }else printf("Nenhuma solucao foi encontrada.\n");

  printf("\n##### Quarto problema: duas cidades (ha solucao).\n");
  insereAresta(&g2, 1, 0, 7);
  exibeGrafo(&g2);
  if (caixeiroViajante(&g2)){
    printf("Custo encontrado: %.2f\n", melhorValor); 
    exibeCiclo(melhorCiclo, g2.numVertices);
  }else printf("Nenhuma solucao foi encontrada.\n");


  printf("\n##### Quinto problema: tres cidades (ha mais de uma solucao, mas apenas uma otima).\n");
  Grafo g3;
  inicializaGrafo(&g3, 3);
  insereAresta(&g3, 0, 1, 32);
  insereAresta(&g3, 0, 2, 16);
  insereAresta(&g3, 1, 0, 8);
  insereAresta(&g3, 1, 2, 4);
  insereAresta(&g3, 2, 0, 2);
  insereAresta(&g3, 2, 1, 1);
  exibeGrafo(&g3);
  if (caixeiroViajante(&g3)){
    printf("Custo encontrado: %.2f\n", melhorValor); 
    exibeCiclo(melhorCiclo, g3.numVertices);
  }else printf("Nenhuma solucao foi encontrada.\n");


  printf("\n##### Sexto problema: quatro cidades (ha mais de uma solucao, mas apenas uma otima).\n");
  Grafo g4;
  inicializaGrafo(&g4, 4);
  insereAresta(&g4, 0, 1, 25);
  insereAresta(&g4, 0, 2, 12);
  insereAresta(&g4, 1, 2, 15);
  insereAresta(&g4, 1, 0, 10);
  insereAresta(&g4, 2, 3, 4);
  insereAresta(&g4, 3, 1, 6);
  insereAresta(&g4, 3, 0, 9);
  insereAresta(&g4, 2, 0, 7);
  exibeGrafo(&g4);
  if (caixeiroViajante(&g4)){
    printf("Custo encontrado: %.2f\n", melhorValor); 
    exibeCiclo(melhorCiclo, g4.numVertices);
  }else printf("Nenhuma solucao foi encontrada.\n");


  printf("\n##### Setimo problema: grafo gerado aleatoriamente (pode ou nao ter solucoes).\n");
  Grafo* g5 = criaGrafoAleatorio(10, 30);
  exibeGrafo(g5);
  if (caixeiroViajante(g5)){
    printf("Custo encontrado: %.2f\n", melhorValor); 
    exibeCiclo(melhorCiclo, g5->numVertices);
  }else printf("Nenhuma solucao foi encontrada.\n");



  return 0;  
}
