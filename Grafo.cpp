#include <stack>
#include <set>
#include "Grafo.h"

#define PASS 0
#define LOOP -1
#define INVALID -2

int dfs(Nodo &raiz, 
		std::set <Nodo> &visited,
		std::set <Nodo> &path,
		int current_status);

int dfs(Nodo &raiz,
		std::set <Nodo> &visited,
		std::set <Nodo> &path,
		int current_status){
	visited.insert(raiz);
	path.insert(raiz);
	int status = current_status;
	std::vector <Nodo*> adyacents = raiz.get_adyacents();

	for (unsigned long int i = 0; i < adyacents.size(); i++){
		Nodo adyacent = *adyacents[i];

		if (path.count(adyacent)) {
			status = LOOP;
			break;
		}
		if (!visited.count(adyacent)){
			status = dfs(adyacent, visited, path, status);
		}
	}
	path.erase(raiz);
	return status;
}

Grafo::Grafo(int size):
	size(size){
		for (int i = 0; i < size + 1; i++) this->nodos.push_back(Nodo(i));
	}

int Grafo::get_number_of_adyacents(int nodo){
	return this->nodos[nodo].get_adyacents().size();
}

int Grafo::has_cycle_and_connected(){
	std::set <Nodo> visited;
	std::set <Nodo> path;

	int status = dfs(this->nodos[1], visited, path, PASS);
	if (status == PASS && visited.size() != this->nodos.size()) return INVALID;
	return status;
}

void Grafo::connect(int nodo1, int nodo2){
	this->nodos[nodo1].add_adyacent(this->nodos[nodo2]);
}

Grafo::~Grafo(){}

