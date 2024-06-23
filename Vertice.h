#pragma once
#include "Arista.h"

class Vertice
{
	int origen;
	Arista* adyacente;
	Vertice* sgteVertice;

public:
	Vertice(int _ori);

	friend class Grafo;
};

typedef Vertice* pvertice;

