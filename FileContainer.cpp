#include "FileContainer.h"

FileContainer::FileContainer(const char ** filenames, int size){
	for (int i = 0; i < size; i++) 
		this->filenames.push_back(std::string(filenames[i]));
}

bool FileContainer::getArchivo(std::string &buffer){
	std::unique_lock<std::mutex> lock(this->m);

	if (this->filenames.size() == 0) return 0;

	buffer = this->filenames.back();
	this->filenames.pop_back();
	return 1;
}

FileContainer::~FileContainer() {}
