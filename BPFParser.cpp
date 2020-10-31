class BPFParser{

	private:
		void clean_whitespaces(std::string linea){
			std::string::size_type pos;
			while ((pos = linea.find("  ")) != std::string::npos)
				linea.replace(pos, 2, " ");
		}

		void fill_linked_labels(std::string linea, std::list <string> labels){
			int amount_of_labels = 0;
			while ((pos = linea.find(",")) != std::string::npos) amount_of_labels += 1;
			if (!amount_of_labels) amount_of_labels = 1;
			for (int delimiter_pos = std::string::npos; amount_of_labels; amount_of_labels--){
				int next_pos = linea.find_last_of(" ", delimiter_pos);
				labels.append(linea.substr(next_pos, delimiter_pos));
				delimiter_pos = next_pos;
			}
		}

		int find_label(std::string &linea){
			std::string::size_type pos = *linea.find_first_of(":");
			return pos != std::string::npos ? pos : -1;
		}

		bool find_jump(std::string &linea){
			return linea[0] == 'j';
		}

	public:
		Linea parsear_linea(){

			std::string linea_leida = this->lector.leer_linea();
			if (!linea_leida) return NULL;
			this.clean_whitespaces(linea_leida);

			int label_pos = this.find_label_end_pos(linea_leida);
			bool has_jump = this.find_jump(linea_leida + label_pos + 1);
			if (!has_jump) return Linea(linea_leida.substr(0, label_pos), has_jump, NULL);

			std::list <string> labels;
			this.fill_linked_labels(linea_leida, labels);
			return Linea(linea_leida.substr(0, label_pos), has_jump, labels);
		}

};