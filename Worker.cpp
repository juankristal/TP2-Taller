#include "Worker.h"
#include "Grafo.h"
#include "BPFParser.h"
#include <vector>
#include <map>
#include <fstream>
#include <iostream>

std::vector<Linea> procesarLineas(BPFParser &parser){
	
	std::vector <Linea> lineas;

	while(!parser.at_eof()){
		Linea linea = parser.parsear_linea();
		if (linea.get_label() == "EMPTY") continue;
		lineas.push_back(linea);
	}
	return lineas;
}

std::map<std::string, int> generateLabelsMap(std::vector<Linea> lineas){
		
	std::map<std::string, int> map;

	for (long unsigned int i = 0; i < lineas.size(); i++){
		Linea linea = lineas[i];
		std::string label = linea.get_label();
		if (label == "") continue;
		map.insert(std::pair<std::string, int> (label, i + 1));
	}

	return map;
}

void connectGrafo(std::vector<Linea> lineas, std::map<std::string, int> labelsMap, Grafo &grafo){

	for (long unsigned int i = 0; i < lineas.size(); i++){

		//std::cout << "Checking nodo " << i + 1<< "\n";

		std::vector<std::string> linked_labels = lineas[i].get_linked_labels();

		//std::cout << "It must connect to " << linked_labels.size() << " nodes based on labels\n";

		for (long unsigned int j = 0; j < linked_labels.size(); j++){
			grafo.connect(i + 1, labelsMap[linked_labels[j]]);
		}

		if (lineas[i].get_has_ret()){
			grafo.connect(i + 1, 0);
		}

		if (grafo.get_number_of_adyacents(i + 1) == 0){
			grafo.connect(i + 1, i + 2);
		}
	}

}

Worker::Worker(std::string filename):
	filename(filename)
	{}

int Worker::procesarArchivo(){

	BPFParser parser(this->filename);

	std::vector<Linea> lineas = procesarLineas(parser);
	std::map<std::string, int> labelsMap = generateLabelsMap(lineas);

	std::cout << "It has this amount of lines: " << lineas.size() << "\n";


	Grafo grafo = Grafo(lineas.size());
	connectGrafo(lineas, labelsMap, grafo);

	return grafo.get_status();
}

Worker::~Worker(){}
