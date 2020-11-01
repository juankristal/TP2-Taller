#include <stack>
#include "Grafo.h"

#define PASS 0
#define LOOP 1
#define INVALID 2

int dfs(){
	return INVALID;
}

Grafo::Grafo(int size):
	size(size),
	nodos(){
		for (int i = 0; i < size; i++) nodos.push_back(Nodo());
	}

int Grafo::get_status(){
	return dfs();
}

void Grafo::connect(int nodo1, int nodo2){
	nodos[nodo1].add_adyacent(nodos[nodo2]);
}

Grafo::~Grafo(){}

