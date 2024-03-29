#include "Worker.h"
#include "Grafo.h"
#include "BPFParser.h"
#include <vector>
#include <map>
#include <utility>

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


void connectLinkedLabels(Grafo &grafo, 
							std::vector<std::string> linked_labels,
							const std::map<std::string, int> &labelsMap, 
							int line_number) {
		for (long unsigned int j = 0; j < linked_labels.size(); j++){
			if (linked_labels[j] == "NEXT"){
				grafo.connect(line_number, line_number + 1);
				continue;
			}
			grafo.connect(line_number, labelsMap.at(linked_labels[j]));
		}	
}

void connectGrafoBPF(std::vector<Linea> &lineas,
					const std::map<std::string, int> &labelsMap,
					Grafo &grafo){
	for (long unsigned int i = 0; i < lineas.size(); i++){
		if (lineas[i].get_has_ret()) grafo.connect(i + 1, 0);

		std::vector<std::string> linked_labels = lineas[i].get_linked_labels();

		connectLinkedLabels(grafo,
				lineas[i].get_linked_labels(),
				labelsMap, i + 1);

		if (grafo.get_number_of_adyacents(i + 1) == 0){
			grafo.connect(i + 1, i + 2);
		}
	}
}

Worker::Worker(){}

int Worker::procesarArchivo(std::string filename){
	BPFParser parser(filename);

	std::vector<Linea> lineas = procesarLineas(parser);
	std::map<std::string, int> labelsMap = generateLabelsMap(lineas);

	Grafo grafo = Grafo(lineas.size());
	connectGrafoBPF(lineas, labelsMap, grafo);

	return grafo.verify_status();
}

Worker::~Worker(){}
