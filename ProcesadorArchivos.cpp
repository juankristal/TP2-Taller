#include <string>
#include "Worker.h"
#include "ProcesadorArchivos.h"
#include <iostream>

void ProcesadorArchivos::run(){
	std::string filename;
	Worker worker; 
	while(this->file_container.getArchivo(filename)) {
		int status = worker.procesarArchivo(filename);
		this->results.storeArchivo(filename, status);
	}
}

ProcesadorArchivos::ProcesadorArchivos(
			AnalysisResultsStorer &results,
			FileContainer &file_container):
	file_container(file_container),
	results(results){
		this->start();
	}

ProcesadorArchivos::~ProcesadorArchivos(){}
