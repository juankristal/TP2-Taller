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

std::vector <Nodo*> Nodo::get_adyacents(){
	return this->adyacents;
}

Nodo::~Nodo(){}

