#include <string>
#include <vector>
#include <cstddef>
#include "Linea.cpp"
#include <fstream>
#include <iostream>

class BPFParser{

	private:
		std::ifstream lector;

		std::string clean_whitespaces(std::string linea){
			std::string::size_type pos;
			while ((pos = linea.find("  ")) != std::string::npos)
				linea.replace(pos, 2, " ");
			return linea;
		}

		void fill_linked_labels(std::string &linea, std::vector <std::string> &labels){
			int amount_of_labels = 0;
			std::string::size_type delimiter_pos = linea.find(",");
			while (delimiter_pos != std::string::npos){
				delimiter_pos = linea.find(",", delimiter_pos + 1);
				amount_of_labels++;
			}
			if (!amount_of_labels) amount_of_labels = 1;


			for (delimiter_pos = std::string::npos; amount_of_labels > 0; amount_of_labels--){
				int next_pos = linea.find_last_of(" ", delimiter_pos - 1);
				labels.push_back(linea.substr(next_pos, delimiter_pos));
				delimiter_pos = next_pos;
			}
		}

		int find_label_end_pos(std::string &linea){
			std::string::size_type pos = linea.find_first_of(":");
			return pos != std::string::npos ? pos : -1;
		}

		bool find_jump(std::string linea){
			return linea[0] == 'j';
		}

		bool find_ret(std::string linea){
			return linea[0] == 'r';
		}

	public:

		BPFParser(const char* file_name){
			this->lector.open(file_name);
		}

		bool at_eof(){
			return this->lector.eof();
		}

		Linea parsear_linea(){

			std::string linea_leida;
			std::vector <std::string> labels;

			getline(this->lector, linea_leida);

			std::cout << linea_leida + "\n";
			if (linea_leida == "") return Linea("EMPTY", true, labels);

			linea_leida = clean_whitespaces(linea_leida);

			int label_pos = find_label_end_pos(linea_leida);
			bool has_jump = find_jump(linea_leida.substr(label_pos + 1, std::string::npos));
			bool has_ret = find_ret(linea_leida.substr(label_pos + 1, std::string::npos));
			std::string label = label_pos == -1 ? "" : linea_leida.substr(0, label_pos);

			if (has_ret) return Linea(label, has_ret, labels); // tiene salto a ningun lado es ret
			if (!has_jump) return Linea(label, has_jump, labels);

			fill_linked_labels(linea_leida, labels);
			return Linea(label, has_jump, labels);
		}

		~BPFParser(){
			this->lector.close();
		}

};


int main(){
	BPFParser parser("all_jmps.bpf");
	int i = 1;
	while (!parser.at_eof()){
		Linea linea = parser.parsear_linea();
		std::cout << "Linea:" << i <<"\nLabel: " + linea.get_label() + "\nHas jump:";
		std::cout << linea.get_has_jump() << "\n";
		std::vector <std::string> linked_labels = linea.get_linked_labels();
		for (std::string::size_type i = 0; i < linked_labels.size(); i++) std::cout << "Labels Vinculados:" + linked_labels[i] + "\n";
		std::cout << "\n";
		i++;
	}
	return 0;
}