#include <string>
#include <cstddef>
#include "Linea.h"
#include <vector>

Linea::Linea(const std::string &label, 
				bool has_jump,
				bool has_ret,
				const std::vector <std::string> &linked_labels):
	label(label),
	has_jump(has_jump),
	has_ret(has_ret),
	linked_labels(linked_labels){}

std::vector <std::string> Linea::get_linked_labels(){
	return this->linked_labels;
}

bool Linea::get_has_ret(){
	return this->has_ret;
}

std::string Linea::get_label(){
	return this->label;
}

Linea::~Linea(){}
