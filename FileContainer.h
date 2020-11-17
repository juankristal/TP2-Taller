#include <string>
#include <vector>
#include <mutex>

class FileContainer{
	private:
		std::vector<std::string> filenames;
		std::mutex m;

	public:
		FileContainer(const char ** filenames, int size);

		bool getArchivo(std::string &buffer);

		~FileContainer();
};
