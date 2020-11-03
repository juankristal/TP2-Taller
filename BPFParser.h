#include <fstream>
#include <iostream>
#include "Linea.h"
#include <string>

class BPFParser{
	std::ifstream lector;

	public:
		explicit BPFParser(std::string fileName);

		bool at_eof();

		Linea parsear_linea();

		~BPFParser();
};
