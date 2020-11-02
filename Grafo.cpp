#include <stack>
#include <set>
#include "Grafo.h"
#include <iostream>

#define PASS 0
#define LOOP -1
#define INVALID -2

int dfs(Nodo &raiz, std::set <Nodo> &visited, std::set <Nodo> &path, int current_status);

int dfs(Nodo &raiz, std::set <Nodo> &visited, std::set <Nodo> &path, int current_status){

	visited.insert(raiz);
	path.insert(raiz);
	int status = current_status;

	//std::cout << "Inserted " << raiz.get_index() << " into Path and Visited\n";

	std::vector <Nodo*> adyacents = raiz.get_adyacents();

	//std::cout << "It has " << adyacents.size() << " adyacent nodes\n";

	for (unsigned long int i = 0; i < adyacents.size(); i++){
		Nodo adyacent = *adyacents[i];

		//std::cout << "Checking adyacent " << adyacent.get_index() << "\n";

		if (path.count(adyacent)) {
			std::cout << "LOOP FOUND!!\n";
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

int Grafo::get_status(){
	std::set <Nodo> visited;
	std::set <Nodo> path;

	std::cout << "Checking DFS\n";

	int status = dfs(this->nodos[1], visited, path, PASS);
	if (status == PASS && visited.size() != this->nodos.size()) return INVALID;
	return status;
}

void Grafo::connect(int nodo1, int nodo2){
	//std::cout << "Connecting " << nodo1 << " with " << nodo2 << "\n";
	this->nodos[nodo1].add_adyacent(this->nodos[nodo2]);
}

Grafo::~Grafo(){}

