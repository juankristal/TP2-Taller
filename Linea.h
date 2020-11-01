#include <string>
#include <cstddef>
#include <vector>

class Linea{
	std::string label;
	bool has_jump;
	std::vector <std::string> linked_labels;
	public:
		Linea(std::string label, bool has_jump, std::vector <std::string> linked_labels);

		std::vector <std::string> get_linked_labels();

		bool get_has_jump();

		std::string get_label();

		~Linea();
};
