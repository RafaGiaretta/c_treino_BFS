#include <stdio.h>
#include <stdlib.h>

#define TVETOR 12 // tamanho dos vetores p se precisar alterar fica facil

typedef struct no {
    int vertice;
    struct no *aresta;
    int visitado; // para verificacao da visita 
} no; // atributos do grafo

typedef no* grafo[TVETOR]; // grafo do tamanho definido ^

void iniciarGrafo(grafo g) { // anula todos os vetores do grafo
	int i = 0;
    for (i = 0; i < TVETOR; i++) {
        g[i] = NULL;
    }
}

void preencher(grafo g, int v, int a) { // preenche.. padrao
    no *novo = (no*)malloc(sizeof(no)); // malloc de um no "novo" para receber os valores do parametro da func
    novo->vertice = a;  // preenche o valor do vertice com o parametro da aresta
    novo->aresta = NULL; // anula a aresta do "novo"
    novo->visitado = 0; // nao foi visitado
    if (g[v] == NULL) { // se for primeira vez
        g[v] = novo; // grafo no vetor do vertice 'v' recebe o "novo"
    } else {
        no *atual = g[v]; // cria um no "atual" para conseguir percorrer sem alterar o original
        while (atual->aresta != NULL) {
            atual = atual->aresta; // looping ate chegar no final
        }
        atual->aresta = novo; // aresta do final recebe o novo
    }
}

void mostrarGrafo(grafo g) { // mostrar grafo bonitinho
	int i = 0;
    for (i = 0; i < TVETOR; i++) {
        printf("Vertice: %d", i);
        no *atual = g[i];
        while (atual != NULL) {
            printf(" -> | %d |", atual->vertice);
            atual = atual->aresta;
        }
        printf("\n\n");
    }
}

void BFS(grafo g, int origem, int dist[]) { // recebe o grafo, o valor de inicio/origem e vetor de distancia
    int fila[TVETOR]; // cria um vetor para ser utilizado como fila
    int final = 0, ini = 0; // variaveis para fila para controle do primeiro e ultimo num do vetor da fila
    int i = 0; 

    for (i = 0; i < TVETOR; i++) {
        dist[i] = 999; // cada indice do vetor dist recebe "infinito"
    }
    dist[origem] = 0; // distancia no vetor de origem recebe 0
    g[origem]->visitado = 1; // altera o visitado do grafo para identificar que ja foi visitado.. 
    fila[final++] = origem; // fila na posição +1 recebe o parametro de origem
    

    while (ini < final) { // enquanto  inicio for menor que final
        int u = fila[ini++]; // u recebe o valor da fila inicial +1
        no *atual = g[u]; // atual para receber o grafo na posicao do "u" 
        while (atual != NULL) { // enquanto ele nao for nulo
            if (g[atual->vertice]->visitado == 0) { // verifica se ja foi vizitado, se nao foi
                g[atual->vertice]->visitado = 1; // altera para saber que foi
                fila[final++] = atual->vertice; // preenche o final da fila com o valor do vertice atual
                dist[atual->vertice] = dist[u] + 1; // soma mais 1 na distancia 
            }
            atual = atual->aresta; // looping ate chegar no final, igual no preencher
        }
	}
}

int main() {
	
    grafo g; // cria o grafo
    iniciarGrafo(g); // inicia ele
    int dist[TVETOR]; // vetor de distancia
    int o, f; // origem e final
    
    preencher(g, 0, 1);
    preencher(g, 0, 3);
    preencher(g, 1, 0);
    preencher(g, 1, 2);
    preencher(g, 2, 1);
    preencher(g, 2, 5);
    preencher(g, 2, 6);
    preencher(g, 3, 0);
    preencher(g, 3, 5);
    preencher(g, 4, 5);
    preencher(g, 5, 4);
    preencher(g, 5, 2);
    preencher(g, 6, 2);
    preencher(g, 6, 7);
    preencher(g, 6, 8);
    preencher(g, 7, 6);
    preencher(g, 7, 8);
    preencher(g, 8, 6);
    preencher(g, 8, 7);
    preencher(g, 8, 9);
    preencher(g, 9, 10);
    preencher(g, 9, 11);
    preencher(g, 10, 9);
    preencher(g, 11, 9); // prenche o grafo de acordo com o desenho
		
    mostrarGrafo(g); // mostra ele para verificar se esta tudo ok
    
    printf("ENTRE COM VERTICE DE ORIGEM: "); // solicita origem
    scanf("%d", &o);
    printf("\nENTRE COM VERTICE FINAL: "); // solitica final
    scanf("%d", &f);
    
    BFS(g, o, dist); // chama a funcao BFS
    
    printf("\n\nDistancia do vertice %d ao vertice %d: %d\n", o, f, dist[f]); // printa o resultado

    return 0;
}

