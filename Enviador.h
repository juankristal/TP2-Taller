#include <string>
#include <vector>
#include <mutex>

class Enviador{
	private:
		std::vector<std::string> filenames;
		std::mutex m;

	public:
		Enviador(const char ** filenames, int size);

		bool getArchivo(std::string &buffer);

		~Enviador();
};
