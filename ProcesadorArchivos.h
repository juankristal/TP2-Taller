#include "FileContainer.h"
#include "AnalysisResultsStorer.h"
#include "Thread.h"

class ProcesadorArchivos: public Thread {
	FileContainer &file_container;
	AnalysisResultsStorer &results;

	public:
		ProcesadorArchivos(AnalysisResultsStorer &results,
							FileContainer &file_container);

		virtual void run() override;

		~ProcesadorArchivos();
};
