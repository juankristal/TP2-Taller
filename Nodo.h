#include <vector>

class Nodo{
	std::vector <Nodo*> adyacents;
	int index;
	public:
		explicit Nodo(int index);

		void add_adyacent(Nodo &other);

		bool operator<(const Nodo& other) const;

		std::vector <Nodo*> get_adyacents();

		~Nodo();
};
