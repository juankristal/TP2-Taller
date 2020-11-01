#include <vector>

class Nodo{
	std::vector <Nodo> adyacents;

	public:
		Nodo();

		void add_adyacent(Nodo other);

		std::vector <Nodo> get_adyacents()

		~Nodo();
};
