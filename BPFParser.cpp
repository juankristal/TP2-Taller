#include <string>
#include <list>
#include <cstddef>
#include "Linea.cpp"
#include <fstream>
#include <iostream>

class BPFParser{

	private:
		std::ifstream lector;

		void clean_whitespaces(std::string linea){
			std::string::size_type pos;
			while ((pos = linea.find("  ")) != std::string::npos)
				linea.replace(pos, 2, " ");
		}

		void fill_linked_labels(std::string &linea, std::list <std::string> &labels){
			int amount_of_labels = 0;
			std::string::size_type delimiter_pos;
			while ((delimiter_pos = linea.find(",")) != std::string::npos) amount_of_labels += 1;
			if (!amount_of_labels) amount_of_labels = 1;
			for (delimiter_pos = std::string::npos; amount_of_labels; amount_of_labels--){
				int next_pos = linea.find_last_of(" ", delimiter_pos);
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

		BPFParser(char* file_name){
			this->lector.open(file_name);
		}

		bool at_eof(){
			return this->lector.eof();
		}

		Linea parsear_linea(){

			std::string linea_leida;

			getline(this->lector, linea_leida);
			clean_whitespaces(linea_leida);
			std::list <std::string> labels;

			int label_pos = find_label_end_pos(linea_leida);
			bool has_jump = find_jump(linea_leida.substr(label_pos + 1, std::string::npos));
			bool has_ret = find_ret(linea_leida.substr(label_pos + 1, std::string::npos));
			if (has_ret) return Linea(linea_leida.substr(0, label_pos), has_ret, labels); // tiene salto a ningun lado es ret
			if (!has_jump) return Linea(linea_leida.substr(0, label_pos), has_jump, labels);

			fill_linked_labels(linea_leida, labels);
			return Linea(linea_leida.substr(0, label_pos), has_jump, labels);
		}

		~BPFParser(){
			this->lector.close();
		}

};
