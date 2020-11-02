#include <iostream>
#include "Recibidor.h"

#define GOOD 0
#define CYCLE -1
#define UNUSED -2

Recibidor::Recibidor(){}

void Recibidor::storeArchivo(std::string filename, int status){
	std::unique_lock<std::mutex> lock(this->m);

	if (status == GOOD) this->results.push_back(filename + " GOOD\n");
	if (status == CYCLE) this->results.push_back(filename + " FAIL: cycle detected\n");
	if (status == UNUSED) this->results.push_back(filename + " FAIL: unused instructions detected\n");
}

void Recibidor::imprimirResultado(){
	for (unsigned long int i = 0; i < this->results.size(); i++){
		std::cout << this->results[i];
	}
}

Recibidor::~Recibidor(){}