#include <fstream>
#include <iostream>
#include "Linea.h"

class BPFParser{


	std::ifstream lector;

	public:

		BPFParser(std::string fileName);

		bool at_eof();

		Linea parsear_linea();

		~BPFParser();
};
