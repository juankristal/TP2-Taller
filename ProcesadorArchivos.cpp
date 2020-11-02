#include <string>
#include "Worker.h"
#include "ProcesadorArchivos.h"
#include <iostream>

void ProcesadorArchivos::run(){
	std::string filename;
	Worker worker; 
	while(!this->enviador.getArchivo(filename)) {
		int status = worker.procesarArchivo(filename);
		this->recibidor.storeArchivo(filename, status);
	}
}

ProcesadorArchivos::ProcesadorArchivos(Enviador &enviador, Recibidor &recibidor):
	recibidor(recibidor),
	enviador(enviador){
		this->start();
	}

ProcesadorArchivos::~ProcesadorArchivos(){}
