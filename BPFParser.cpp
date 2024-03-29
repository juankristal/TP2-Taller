#include <string>
#include <vector>
#include <cstddef>
#include "BPFParser.h"
#include <fstream>
#include <iostream>

#define LABEL_INDICATOR ":"
#define DELIMITER ","

std::string clean_whitespaces(std::string &linea){
	std::string::size_type pos;
	while ((pos = linea.find("  ")) != std::string::npos)
		linea.replace(pos, 2, " ");
	return linea;
}

void fill_linked_labels(std::string &linea, std::vector <std::string> &labels){
	int amount_of_labels = 0;
	std::string::size_type delimiter_pos = linea.find(DELIMITER);
	while (delimiter_pos != std::string::npos){
		delimiter_pos = linea.find(DELIMITER, delimiter_pos + 1);
		amount_of_labels++;
	}
	if (amount_of_labels == 1) labels.push_back("NEXT");
	if (!amount_of_labels) amount_of_labels = 1;

	for (delimiter_pos = std::string::npos;
			amount_of_labels > 0;
		 	amount_of_labels--){
		int next_pos = linea.find_last_of(" ", delimiter_pos - 1);
		labels.push_back(linea.substr(next_pos + 1, delimiter_pos - next_pos - 2));
		delimiter_pos = next_pos;
	}
}

int find_label_end_pos(std::string linea){
	std::string::size_type pos = linea.find_first_of(LABEL_INDICATOR);
	return pos != std::string::npos ? pos : -1;
}

bool find_jump(std::string linea){
	int i = linea.find_first_of(" ") ? 0 : 1;
	return linea[i] == 'j';
}

bool find_ret(std::string linea){
	int i = linea.find_first_of(" ") ? 0 : 1;
	return linea[i] == 'r';
}

BPFParser::BPFParser(std::string fileName){
	this->lector.open(fileName);
}

bool BPFParser::at_eof(){
	return this->lector.eof();
}

Linea BPFParser::parsear_linea(){ 
	std::string linea_leida;
	std::vector <std::string> labels;

	getline(this->lector, linea_leida);

	if (linea_leida == "") return Linea("EMPTY", true, true, labels);

	linea_leida = clean_whitespaces(linea_leida);

	int label_pos = find_label_end_pos(linea_leida);
	bool has_jump = find_jump(
						linea_leida.substr(
							label_pos + 1, std::string::npos));
	bool has_ret = find_ret(
						linea_leida.substr(
							label_pos + 1, std::string::npos));
	std::string label = label_pos == -1 ?
						 "" : linea_leida.substr(0, label_pos);

	if (has_ret) return Linea(label, has_jump, has_ret, labels);
	if (!has_jump) return Linea(label, has_jump, has_ret, labels);

	fill_linked_labels(linea_leida, labels);
	return Linea(label, has_jump, has_ret, labels);
}

BPFParser::~BPFParser(){
	this->lector.close();
}
