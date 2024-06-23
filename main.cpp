#include <iostream>
#include "Grafo.h"

using namespace std;

int main() {
	system("color E1");
	Grafo g;

	/*g.insertarVertice(0);
	g.insertarVertice(1);
	g.insertarVertice(2);
	g.insertarVertice(3);
	g.insertarVertice(4);
	g.insertarVertice(5);
	g.insertarVertice(6);
	g.insertarVertice(7);
	g.insertarVertice(7);
	g.insertarVertice(6);
	g.insertarVertice(5);
	g.insertarVertice(4);
	g.insertarVertice(3);
	g.insertarVertice(2);
	g.insertarVertice(1);
	g.insertarVertice(0);
	g.insertarAristas(0, 2, 32);
	g.insertarAristas(0, 7, 18);
	g.insertarAristas(2, 6, 21);
	g.insertarAristas(1, 7, 20),
	g.insertarAristas(7, 4, 32);
	g.insertarAristas(6, 4, 18);
	g.insertarAristas(4, 3, 21);
	g.insertarAristas(4, 5, 40);
	g.insertarAristas(5, 0, 30);
	g.insertarAristas(3, 5, 30);*/

	/*g.insertarVertice(0);
	g.insertarVertice(1);
	g.insertarVertice(3);
	g.insertarVertice(4);
	g.insertarAristas(0, 1, 32);
	g.insertarAristas(0, 3, 18);
	g.insertarAristas(0, 4, 21);
	g.insertarAristas(1, 3, 20),
	g.insertarAristas(1, 4, 32);
	*/

	// DFS
	g.insertarVertice(4);
	g.insertarVertice(3);
	g.insertarVertice(1);
	g.insertarVertice(0);
	g.insertarAristas(0, 1, 32);
	g.insertarAristas(0, 3, 18);
	g.insertarAristas(0, 4, 21);
	g.insertarAristas(1, 3, 20),
	g.insertarAristas(1, 4, 32);
	

	/*g.insertarVertice(7);
	g.insertarVertice(6);
	g.insertarVertice(5);
	g.insertarVertice(4);
	g.insertarVertice(3);
	g.insertarVertice(2);
	g.insertarVertice(1);
	g.insertarVertice(0);
	g.insertarAristas(0, 2, 10);
	g.insertarAristas(0, 7, 12);
	g.insertarAristas(0, 5, 7);
	g.insertarAristas(2, 6, 19);
	g.insertarAristas(7, 1, 14);
	g.insertarAristas(5, 3, 21);
	g.insertarAristas(5, 4, 16);
	g.insertarAristas(3, 4, 27);*/

	/*g.insertarVertice(5);
	g.insertarVertice(4);
	g.insertarVertice(3);
	g.insertarVertice(2);
	g.insertarVertice(1);
	g.insertarVertice(0);
	g.insertarAristas(0, 4, 10);
	g.insertarAristas(0, 1, 12);
	g.insertarAristas(1, 2, 7);
	g.insertarAristas(3, 4, 19);
	g.insertarAristas(2, 4, 14);
	g.insertarAristas(4, 5, 21);
	g.insertarAristas(5, 1, 16);*/

	cout << "---------------------------\n";
	cout << "Recorrido DFS" << endl;
	//g.algBusqueda(0);
	//g.existeCircuito();
	/*cout << "Recorrido BFS" << endl;
	g.BFS(0);*/

	//if (g.bicolorable()) cout << "El grafo es bicolorable" << endl;
	//if (g.existeCircuito()) cout << "Existe circuito" << endl;
	//cout << endl;
	//g.algoritmoBoruvka();
	////g.listarAristas();
	//cout << "------------------------------------------" << endl;
	g.algoritmoKruskal();
}