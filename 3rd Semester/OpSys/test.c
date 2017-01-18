#include <fcntl.h>

int main(){
	ftruncate(1, 1);
	return 0;
}
