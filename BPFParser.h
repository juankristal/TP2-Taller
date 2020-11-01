#include <fstream>
#include <iostream>
#include "Linea.h"

class BPFParser{

	std::ifstream lector;

	public:
		BPFParser(const char* fileName);

		bool at_eof();

		Linea parsear_linea();

		~BPFParser();
};
