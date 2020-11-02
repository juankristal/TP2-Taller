#include "Worker.h"
#define MIN_ARGC 3

int main(int argc, char const *argv[]){

	if (argc < MIN_ARGC) return -1;

	for (int i = 2; i < argc; i++){
		Worker worker(argv[i]);
		printf("%d\n", worker.procesarArchivo());
	}
	return 0;
}