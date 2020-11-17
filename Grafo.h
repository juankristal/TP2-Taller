#include <vector>
#include "Nodo.h"

class Grafo{
	int size;
	std::vector <Nodo> nodos;
	public:
		/*	Se construye un grafo de tamanio size */
		explicit Grafo(int size);

		void connect(int nodo1, int nodo2);

		/* 	Devuelve 0 si el grafo no tiene ciclos y es conexo.
			Devuelve 1 si el grafo tiene un ciclo.
			Devuelve 2 si no tiene ciclos pero no es conexo. */
		int has_cycle_and_connected();

		int get_number_of_adyacents(int nodo);

		~Grafo();
};
