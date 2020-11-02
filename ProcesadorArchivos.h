#include "Recibidor.h"
#include "Enviador.h"
#include "Thread.h"

class ProcesadorArchivos: public Thread {

	Recibidor &recibidor;
	Enviador &enviador;

	public:

		ProcesadorArchivos(Enviador &enviador, Recibidor &recibidor);

		virtual void run();

		~ProcesadorArchivos();
};
