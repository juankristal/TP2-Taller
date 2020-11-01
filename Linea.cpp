#include <string>
#include <cstddef>
#include <vector>

class Linea{
	private:
		std::string label;
		bool has_jump;
		std::vector <std::string> linked_labels;
	public:
		Linea(std::string label, bool has_jump, std::vector <std::string> linked_labels) :
			label(label),
			has_jump(has_jump),
			linked_labels(linked_labels)
		{}

		std::vector <std::string> get_linked_labels(){
			return this->linked_labels;
		}

		bool get_has_jump(){
			return this->has_jump;
		}

		std::string get_label(){
			return this->label;
		}

		~Linea(){}
};
