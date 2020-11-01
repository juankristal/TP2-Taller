#include <stack>
#include <set>
#include "Grafo.h"

#define PASS 0
#define LOOP -1
#define INVALID -2

int dfs(Nodo raiz, std::set <Nodo> visited, std::set <Nodo> path){

	visited.insert(raiz);
	path.insert(raiz);
	int status = PASS;

	std::vector <Nodo> adyacents = raiz.get_adyacents();

	for (std::vector<Nodo>::size_type i = 0; i < adyacents.size(); i++){
		Nodo adyacent = adyacents[i];
		if (path.count(adyacent)) return LOOP;
		if (!visited.count(adyacent)){
			status = dfs(adyacent, visited, path);
		}
	}
	path.erase(raiz);
	return status;
}

Grafo::Grafo(int size):
	size(size),
	nodos(){
		for (int i = 0; i < size + 1; i++) nodos.push_back(Nodo(i));
	}

int Grafo::get_status(){
	std::set <Nodo> visited;
	std::set <Nodo> path;
	int status = dfs(nodos[1], visited, path);
	if (status == PASS && visited.size() != nodos.size()) return INVALID;
	return status;
}

void Grafo::connect(int nodo1, int nodo2){
	nodos[nodo1].add_adyacent(nodos[nodo2]);
}

Grafo::~Grafo(){}

