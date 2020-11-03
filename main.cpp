#include "ProcesadorArchivos.h"
#include <cstdlib>
#include <iostream>
#define THREAD_COUNT 1
#define MIN_ARGC 3

int main(int argc, char const *argv[]){
	if (argc < MIN_ARGC) return -1;

	Recibidor recibidor;
	Enviador enviador(argv + 2, argc - 2);
	std::vector<ProcesadorArchivos*> threads;

	for (int i = 0; i < atoi(argv[THREAD_COUNT]); i++) 
		threads.push_back(new ProcesadorArchivos(enviador, recibidor));

	for (int i = 0; i < atoi(argv[THREAD_COUNT]); i++){
		threads[i]->join();
		delete threads[i];
	}

	recibidor.imprimirResultado();
	return 0;
}
