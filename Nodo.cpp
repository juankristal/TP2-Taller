#include "Nodo.h"
#include <vector>

Nodo::Nodo(){}

void Nodo::add_adyacent(Nodo other){
	adyacents.push_back(other);
}

std::vector <Nodo> Nodo::get_adyacents(){
	return this->adyacents;
}

Nodo::~Nodo(){}

