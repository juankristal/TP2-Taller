#include <string>
#include <vector>
#include <mutex>

class AnalysisResultsStorer{
	private:
		std::vector<std::string> results;
		std::mutex m;

	public:
		AnalysisResultsStorer();

		void storeArchivo(const std::string &filename, int status);

		void imprimirResultado();

		~AnalysisResultsStorer();
};
