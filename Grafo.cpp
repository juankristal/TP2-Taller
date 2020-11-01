#include <stack>
#include <set>
#include "Grafo.h"

#define PASS 0
#define LOOP -1
#define INVALID 2

int dfs(Nodo raiz){
	std::set <Nodo> visited;
	std::set <Nodo> path;
	std::stack <Nodo> stack {raiz};

	while (!stack.empty()){
		Nodo actual = stack.top();
		visited.insert(actual);
		path.insert(actual);
		for each(Nodo adyacent in actual.get_adyacents()){
			if (path.count(adyacent)) return LOOP;
			if (!visited.count(adyacent)) visited.insert(adyacent);
		}
	}




	return INVALID;
}

Grafo::Grafo(int size):
	size(size),
	nodos(){
		for (int i = 0; i < size + 1; i++) nodos.push_back(Nodo());
	}

int Grafo::get_status(){
	return dfs(nodos[1]);
}

void Grafo::connect(int nodo1, int nodo2){
	nodos[nodo1].add_adyacent(nodos[nodo2]);
}

Grafo::~Grafo(){}

