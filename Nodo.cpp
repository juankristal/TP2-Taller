#include "Nodo.h"
#include <vector>
#include <iostream>

Nodo::Nodo(int index):
	index(index){}

void Nodo::add_adyacent(Nodo &other){
	this->adyacents.push_back(&other);
}

bool Nodo::operator<(const Nodo& other) const{
	return this->index < other.index;
}

int Nodo::get_index(){
	return this->index;
}

std::vector <Nodo*> Nodo::get_adyacents(){
	std::cout << "Getting adyacents for " << this->index << ". It has " << this->adyacents.size() << " adyacent nodes\n";
	return this->adyacents;
}

Nodo::~Nodo(){}

