#include <string>
#include <cstddef>
#include "Linea.h"
#include <vector>

Linea::Linea(std::string label, bool has_jump, std::vector <std::string> linked_labels) :
	label(label),
	has_jump(has_jump),
	linked_labels(linked_labels){}

std::vector <std::string> Linea::get_linked_labels(){
	return this->linked_labels;
}

bool Linea::get_has_jump(){
	return this->has_jump;
}

std::string Linea::get_label(){
	return this->label;
}

Linea::~Linea(){}
