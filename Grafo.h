#include <vector>
#include "Nodo.h"

class Grafo{
	int size;
	std::vector <Nodo> nodos;
	public:
		Grafo(int size);

		void connect(int nodo1, int nodo2);

		int get_status();

		int get_number_of_adyacents(int nodo);

		~Grafo();

};
