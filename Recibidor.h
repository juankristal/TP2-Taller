#include <string>
#include <vector>
#include <mutex>

class Recibidor{
	private:
		std::vector<std::string> results;
		std::mutex m;

	public:
		Recibidor();

		void storeArchivo(std::string filename, int status);

		void imprimirResultado();

		~Recibidor();
};
