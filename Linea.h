#include <string>
#include <cstddef>
#include <vector>

class Linea{
	std::string label;
	bool has_jump;
	bool has_ret;
	std::vector <std::string> linked_labels;
	public:
		Linea(std::string label,
				bool has_jump,
				bool has_ret,
				std::vector <std::string> linked_labels);

		std::vector <std::string> get_linked_labels();

		bool get_has_jump();

		bool get_has_ret();

		std::string get_label();

		~Linea();
};
