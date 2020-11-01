#include <vector>

class Nodo{
	std::vector <Nodo> adyacents;

	public:
		Nodo();

		void add_adyacent(Nodo other);

		~Nodo();
};
