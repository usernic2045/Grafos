#pragma once

class Arista
{
	int datoDestino;
	int peso;
	Arista* sgteArista;

public:
	Arista(int _destino);

friend class Grafo;
};
typedef Arista* parista;

