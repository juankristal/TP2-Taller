#include <vector>

class Nodo{
	std::vector <Nodo> adyacents;
	int index;

	public:
		Nodo(int index);

		void add_adyacent(Nodo other);

		bool operator<(const Nodo& other) const;

		int get_index();

		std::vector <Nodo> get_adyacents();

		~Nodo();
};
