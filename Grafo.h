#pragma once
#include "Vertice.h"

class Grafo
{
    pvertice pGrafo;

public:
    Grafo();
    ~Grafo();
    void insertarArista(int x, int y, int peso);
    void insertarAristas(int x, int y, int peso);
    void insertarVertice(int x);
    void imprimirGrafoDirigido();
    void imprimirGrafo();
    void eliminarArista(int x, int y);
    void eliminarAristaDestino(int x);
    void eliminarVertice(int x);
    int numVertices();
    int numAristas();
    bool esVecino(pvertice v, pvertice w);
    int encontrarIndiceVertice(int valor, pvertice* v, int nronodos);
    void algBusqueda(int vrtcinicial);
    void DFS(int j, int& cont, int* pre, int nronodos, pvertice* v);
    int existeCircuito();
    bool buscaCircuitoDFS(int v, int padrev, int*& visit, pvertice* vertices);
    void BFS(int inicial);
    bool bicolorable();
    bool bfsColor(int v, int col, int* color);
    void algoritmoBoruvka();
    void algoritmoKruskal();
    pvertice* listarVertices();
    void algoritmoDijkstra(pvertice s);

    struct edge {
        int ori;
        int dest;
        int peso;
    };

    edge* listarAristas();

private:
    static int compararAristas(const void* a, const void* b);
};
