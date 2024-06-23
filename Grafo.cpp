#include "Grafo.h"
#include <iostream>
#include <queue>

using namespace std;

Grafo::Grafo() {
	pGrafo = NULL;
}

Grafo::~Grafo() {
	pvertice p, rp;
	parista r, ra;
	p = pGrafo;
	while (p != NULL) {
		r = p->adyacente;
		while (r != NULL) {
			ra = r;
			r = r->sgteArista;
			delete ra;
		}
		rp = p;
		p = p->sgteVertice;
		delete rp;
	}
}

void Grafo::insertarVertice(int x) {
	pvertice p = new Vertice(x);	//ya se inicializo el x como dato origen por el constructor
	p->adyacente = NULL;
	p->sgteVertice = pGrafo;	
	pGrafo = p;
}

void Grafo::insertarArista(int x, int y, int peso) {
	pvertice p;
	parista a;
	p = pGrafo;
	if (p != NULL) {
		while (p!=NULL && p->origen != x)
			p = p->sgteVertice;
		if (p != NULL) {
			a = new Arista(y);
			a->sgteArista = p->adyacente;
			a->peso = peso;
			p->adyacente = a;
		}
	}
}

void Grafo::insertarAristas(int x, int y, int peso) {
	insertarArista(x, y, peso);
	insertarArista(y, x, peso);
}

void Grafo::imprimirGrafoDirigido() {
	pvertice p;
	parista a;
	p = pGrafo;
	cout << "-------------Impresion del grafo------------" << endl;
	while (p!= NULL) {
		a = p->adyacente;
		if (a == NULL)
			cout << p->origen << " (sin aristas)" << endl;
		else {
			cout << p->origen << ": ";
			while (a != NULL) {
				cout << a->datoDestino << " (" << a->peso << ")  ";
				a = a->sgteArista;
			}
			cout << endl;
		}
		p = p->sgteVertice;
	}
	cout << endl;
}

void Grafo::eliminarArista(int x, int y) {
	pvertice p = pGrafo;
	parista a = NULL, ra = NULL;
	if (p == NULL)
		return;
	while (p != NULL && p->origen != x) {
		p = p->sgteVertice;
	}
	if (p == NULL) {
		cout << "El vertice de origen no existe" << endl;
		return;
	}

	a = p->adyacente;

	if (a == NULL) {
		cout << "No existen aristas con ese vertice de origen" << endl;
		return;
	}

	//si hay que eliminar la primera arista
	if (a->datoDestino == y) {
		p->adyacente = a->sgteArista;
		//cout << "Se elimino la arista " << p->origen << "->" << a->datoDestino << ": Peso (" << a->peso << ")" << endl;
		delete a;
		return;
	}

	while (a != NULL && a->datoDestino != y) {
		ra = a;
		a = a->sgteArista;
	}
	if (a == NULL) {
		cout << "No se encontro el vertice de destino" << endl;
		return;
	}
	cout << "Se elimino la arista " << p->origen << "->" << a->datoDestino << ": Peso (" << a->peso << ")" << endl;
	ra->sgteArista = a->sgteArista;
	delete a;
}
void Grafo::eliminarAristaDestino(int x) {
	pvertice p = pGrafo;
	parista a = NULL;
	if (p == NULL) {
		cout << "Grafo Vacio" << endl;
		return;
	}
	while (p != NULL) {
		a = p->adyacente;
		while (a != NULL) {
			if (a->datoDestino == x) {
				parista ra = a->sgteArista;
				eliminarArista(p->origen, x);
				a = ra;
			}
			else {
				a = a->sgteArista;
			}
		}
		p = p->sgteVertice;
	}
}

void Grafo::eliminarVertice(int x) {
	pvertice p = pGrafo, rp = NULL;
	parista a = NULL;

	if (p == NULL) {
		cout << "Grafo vacio" << endl;
		return;
	}

	// Primero eliminamos todas las aristas del vértice x
	while (p != NULL) {
		if (p->origen == x) {
			a = p->adyacente;
			while (a != NULL) {
				parista temp = a->sgteArista;
				eliminarArista(x, a->datoDestino);
				a = temp;
			}
			eliminarAristaDestino(x);
			break;
		}
		p = p->sgteVertice;
	}
	//Inicializamos nuevamente el grafo para hacer la bsuqueda
	p = pGrafo;
	while (p != NULL && p->origen != x) {
		rp = p;
		p = p->sgteVertice;
	}

	if (p != NULL) {
		if (rp == NULL) {	//si eliminamos el primer vertice en la lista
			pGrafo = p->sgteVertice;
		}
		else {
			rp->sgteVertice = p->sgteVertice;
		}
		cout << "Se elimino el vertice " << p->origen << endl;
		delete p;
	}
	else {
		cout << "El vertice " << x << " no se encontro en el grafo" << endl;
	}
}

int Grafo::numVertices() {
	pvertice p = pGrafo;
	int num = 0;
	while (p != NULL) {
		p = p->sgteVertice;
		num++;
	}
	return num;
}

int Grafo::numAristas() {
	pvertice p = pGrafo;
	parista a;
	int num = 0;
	while (p != NULL) {
		a = p->adyacente;
		while (a != NULL) {
			num++;
			a = a->sgteArista;
		}
		p = p->sgteVertice;
	}
	return num;
}

/*-----------------Algoritmo para encontrar los vertices adyacentes a un vertice--------------*/

bool Grafo::esVecino(pvertice v, pvertice w) {	//para grafos "no dirigidos"
	parista va, wa;
	va = v->adyacente;
	wa = w->adyacente;
	while (va != NULL) {
		if (va->datoDestino == w->origen)
			return true;
		va = va->sgteArista;
	}
	while (wa != NULL) {
		if (wa->datoDestino == v->origen)
			return true;
		wa = wa->sgteArista;
	}
	return false;
}

/*------------------------Algoritmo DFS------------------------*/
int Grafo::encontrarIndiceVertice(int valor, pvertice* v, int nronodos) {
	for (int i = 0; i < nronodos; i++) {
		if (v[i]->origen == valor) {
			return i;
		}
	}
	return -1;
}

void Grafo::algBusqueda(int valorVerticeInicial) {
	pvertice p = pGrafo;
	int cont = 0, k = 0;
	int nronodos = numVertices();
	pvertice* v = new pvertice[nronodos];

	if (p == NULL || nronodos == 0) {
		cout << "Grafo vacio" << endl;
		delete[] v;
		return;
	}
	while (p != NULL && k<nronodos) {
		v[k] = p;
		k++;
		p = p->sgteVertice;
	}
	int* pre = new int[nronodos];
	for (int i = 0; i < nronodos; i++) {
		pre[i] = -1;

	}


	// Buscar el índice del vértice inicial
	int verticeInicial = encontrarIndiceVertice(valorVerticeInicial, v, nronodos);
	if (verticeInicial == -1) {
		cout << "Vertice inicial no encontrado" << endl;
		delete[] pre;
		delete[] v;
		return;
	}

	// Comenzar DFS desde el vértice inicial especificado
	if (pre[verticeInicial] == -1) {
		DFS(verticeInicial, cont, pre, nronodos, v);
	}
	//Podemos ignorar la instruccion anterior y comenzara por defecto en el 
	//vertice que apunte pGrafos
	for (int j = 0; j < nronodos; j++) {
		if (pre[j] == -1)
			DFS(j, cont, pre, nronodos, v);
	}
	for (int i = 0; i < nronodos; i++) {
		cout << "pre[" << i << "] = " << pre[i] << " , " << "v: " << v[i]->origen << endl;
	}
	delete[] pre;
	delete[] v;
}

void Grafo::DFS(int j, int& cont, int* pre, int nronodos, pvertice* v) {
	pre[j] = ++cont;
	cout << v[j]->origen << endl;
	for (int i = 0; i < nronodos; i++) {
		if (esVecino(v[i], v[j])) {
			if (pre[i] == -1)
				DFS(i, cont, pre, nronodos, v);
		}
	}
}

/*---------------------Existencia de circuitos----------------------*/

int Grafo::existeCircuito() {
	pvertice p = pGrafo;
	int nronodos = numVertices(), k = 0;
	pvertice* vertices = new pvertice[nronodos];
	if (p == nullptr || nronodos == 0) {
		cout << "Grafo vacio" << endl;
		delete[] vertices;
		return 0;
	}
	vertices = listarVertices();
	int* visit = new int[nronodos];
	for (int i = 0; i < nronodos; i++) {
		visit[i] = -1; // Inicializar todos los vértices como no visitados
	}

	// Buscar ciclos en cada componente conexa del grafo
	for (int v = 0; v < nronodos; v++) {
		if (visit[v] == -1) { // Si el vértice no ha sido visitado
			if (buscaCircuitoDFS(v, -1, visit, vertices)) {
				//cout << "Se encontro un circuito" << endl;
				delete[] visit;
				delete[] vertices;
				return 1;
			}
		}
	}

	cout << "No se encontro ningun circuito" << endl;
	delete[] visit;
	delete[] vertices;
	return 0;
}

bool Grafo::buscaCircuitoDFS(int v, int padrev, int* &visit, pvertice* vertices) {
	visit[v] = 1; // Marcamos el vértice como visitado
	//cout << "visit[" << v << "] (" << vertices[v]->origen << ") = 1" << endl;
	int nronodos = numVertices();
	//cout << "------------------------" << endl;
	//imprimirGrafoDirigido();
	for (int w = 0; w < nronodos; w++) {
		//cout << "w: " << w << endl;
		//cout << "Fuera::padrev - w:: " << padrev << " - " << w << endl;
		if (esVecino(vertices[w], vertices[v])) { // Verifica si hay una arista de vertices[i] a v
			//cout << "w-v: " << vertices[w]->origen << " - " << vertices[v]->origen << endl;
			if (visit[w] == -1) { // Si el vértice i no ha sido visitado
				if (buscaCircuitoDFS(w, v, visit, vertices))
					return true; // Se encontró un ciclo
			}
			else if (padrev != w) {
				//cout << "padrev - w: " << padrev << "  -  " << w << endl;
				return true; // Hay un ciclo (arista de retorno)
			}
		}
	}
	return false; // No se encontró ciclo desde el vértice j
}


/*--------------------------Algoritmo BFS-------------------------*/

void Grafo::BFS(int inicial) {
	pvertice p = pGrafo;
	queue<pvertice> cola;
	int nronodos = numVertices(), k = 0;
	pvertice* vertices = new pvertice[nronodos];
	int* ord = new int[nronodos];
	for (int i = 0; i < nronodos; i++) {
		ord[i] = -1;
	}
	if (p == NULL) {
		cout << "El grafo esta vacio" << endl;
		delete[] ord;
		return;
	}
	while (p != NULL && k < nronodos) {
		vertices[k] = p;
		k++;
		p = p->sgteVertice;
	}
	int inic = encontrarIndiceVertice(inicial, vertices, nronodos);
	int ind, cont = 0;
	pvertice v;
	cola.push(vertices[inic]);
	while (!cola.empty()) {
		v = cola.front();
		cola.pop();
		ind = encontrarIndiceVertice(v->origen, vertices, nronodos);
		if (ord[ind] == -1) {
			ord[ind] = ++cont;
			cout << vertices[ind]->origen << endl;
			for (int j = 0; j < nronodos; j++) {
				if (esVecino(vertices[j], vertices[ind])) {
					cola.push(vertices[j]);
				}
			}
		}
	}
	for (int i = 0; i < nronodos; i++) {
		cout << "v: " << vertices[i]->origen << " , ord[" << i << "] = " << ord[i] << endl;
	}

	delete[] vertices;
	delete[] ord;
}

bool Grafo::bicolorable() {
	int nronodos = numVertices();
	int* color = new int[nronodos];
	for (int i = 0; i < nronodos; i++) {
		color[i] = -1;
	}
	for (int i = 0; i < nronodos; i++) {
		if (color[i] == -1) {
			if (!bfsColor(i, 0, color))
				return false;
		}
	}
	return true;
	delete[] color;
}

bool Grafo::bfsColor(int valor, int col, int* color) {
	pvertice p = pGrafo;
	queue<pvertice> cola;
	int nronodos = numVertices(), k = 0;
	pvertice* vertices = new pvertice[nronodos];
	if (p == NULL) {
		cout << "El grafo esta vacio" << endl;
		delete[] color;
		return false;
	}
	while (p != NULL && k < nronodos) {
		vertices[k] = p;
		k++;
		p = p->sgteVertice;
	}
	//int inic = encontrarIndiceVertice(valor, vertices, nronodos);
	int ind, cont = 0;
	pvertice u;
	cola.push(vertices[valor]);
	color[valor] = col;
	while (!cola.empty()) {
		u = cola.front();
		cola.pop();
		ind = encontrarIndiceVertice(u->origen, vertices, nronodos);
		for (int i = 0; i < nronodos; i++) {
			if (esVecino(vertices[i], vertices[ind])) {
				if (color[i] == -1) {
					color[i] = 1 - color[ind];
					cola.push(vertices[i]);
				}
				else if (color[i] == color[ind])
					return false;
			}
		}
	}
	for (int i = 0; i < nronodos; i++) {
		cout << "v: " << vertices[i]->origen << " , color[" << i << "] = " << color[i] << endl;
	}

	delete[] vertices;
	delete[] color;
	return true;
}


/*-----------------Listado de las aristas sin direccion---------------------*/
Grafo::edge* Grafo::listarAristas() {
	int nroaristas = numAristas(), i = 0;
	edge* vectaristas = new edge[nroaristas];
	pvertice p = pGrafo;
	parista a;

	while (p != NULL) {
		a = p->adyacente;
		while (a != NULL && i < nroaristas) {
			vectaristas[i].ori = p->origen;
			vectaristas[i].dest = a->datoDestino;
			vectaristas[i].peso = a->peso;
			i++;
			a = a->sgteArista;
		}
		p = p->sgteVertice;
	}

	int num = nroaristas / 2, k = 0;
	edge* ari = new edge[num];
	for (int i = 0; i < nroaristas - 1; i++) {
		for (int j = i + 1; j < nroaristas; j++) {
			if (vectaristas[i].ori == vectaristas[j].dest && vectaristas[i].dest == vectaristas[j].ori) {
				ari[k] = vectaristas[i];
				k++;
			}
		}
	}

	delete[] vectaristas; // Liberar la memoria dinámica usada
	return ari;
}

/*-------------------------------------------------------------------*/

pvertice* Grafo::listarVertices() {
	pvertice p = pGrafo;
	int nrovertices = numVertices(), k = 0;
	pvertice* T = new pvertice[nrovertices];
	if (p == NULL) {
		cout << "El grafo esta vacio" << endl;
		return nullptr;
	}
	//Inicialmente el bosque T esta formado unicamente por los vertices del grafo
	while (p != NULL && k < nrovertices) {
		T[k] = p;
		k++;
		p = p->sgteVertice;
	}
	return T;
}

/*---------------------IMPRESION GRAFO NO DIRIGIDO--------------------*/
void Grafo::imprimirGrafo() {
	pvertice p = pGrafo;
	parista a;
	if (p == NULL) {
		cout << "El grafo esta vacio" << endl;
		return;
	}
	cout << "-------------Impresion del grafo------------" << endl;
	edge* aristas = listarAristas();
	pvertice* vertices = listarVertices();
	int nroaristas = numAristas() / 2;
	int nrovertices = numVertices(), i = 0;
	while (p != NULL) {
		a = p->adyacente;
		if (a == NULL) {
			cout << p->origen << "-> NULL" << endl;
		}
		for (i = 0; i < nroaristas; i++) {
			cout << aristas[i].ori << " - " << aristas[i].dest << endl;
		}
		if (i == nroaristas - 1) break;
		p = p->sgteVertice;
	}
	cout << endl;
}

/*-----------------------Algoritmo de Boruvka------------------------*/


void Grafo::algoritmoBoruvka() {
	Grafo T; // Grafo vacío para construir el MST
	pvertice p = pGrafo;
	edge* lista = listarAristas();
	int num = numAristas() / 2;
	int vert = numVertices();

	qsort(lista, num, sizeof(lista[0]), Grafo::compararAristas);


}


/*-----------------------Algoritmo de Kruskal------------------------*/


/*bool compararPorPeso(const edge& a, const edge& b) {
    return a.peso < b.peso;
}
    // Ordenar las aristas utilizando std::sort y la función de comparación
    sort(lista, lista + num, compararPorPeso);

	se puede usar sort en lugar de qsort es mas facil y eficiente, pero requiere
	incluir la libreria algorithm
}*/

int Grafo::compararAristas(const void* a, const void* b) {
	const edge* a1 = static_cast<const edge*>(a);
	const edge* a2 = static_cast<const edge*>(b);
	return a1->peso - a2->peso;
}

//Algoritmo para Kruskal terminado

void Grafo::algoritmoKruskal() {
	Grafo T; // Grafo vacío para construir el MST
	pvertice p = pGrafo;
	edge* lista = listarAristas();
	int num = numAristas() / 2;
	int vert = numVertices();

	qsort(lista, num, sizeof(lista[0]), Grafo::compararAristas);

	pvertice* vertices = new pvertice[vert];
	int k = 0;
	
	pvertice* nodos = listarVertices();
	for (int i = 0; i < vert; i++) {
		T.insertarVertice(nodos[i]->origen);
	}

	for (int i = 0; i < num; i++) {
		T.insertarAristas(lista[i].ori, lista[i].dest, lista[i].peso);
		if (T.existeCircuito()) {
			T.eliminarArista(lista[i].ori, lista[i].dest);
			T.eliminarArista(lista[i].dest, lista[i].ori);
		}
		else {
			cout << "Se agrego la arista " << lista[i].ori << " - " << lista[i].dest << endl;
		}
	}
	T.imprimirGrafoDirigido();

	delete[] vertices;
}


/*------------------------Algoritmo de Prim--------------------------*/



/*-----------------------Algoritmo de Dijkstra------------------------*/

void Grafo::algoritmoDijkstra(pvertice s) {
	
}