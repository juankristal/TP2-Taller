#include <string>

class Worker{
	std::string filename;
	public:
		Worker(std::string filename);

		int procesarArchivo();

		~Worker();
};
