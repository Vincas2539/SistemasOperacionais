/* Ana Clara Melo Senne - 32145101
Paulo Henrique Sousa Camargo - 32138121
Vincenzo Alberice - 32135661 */

#include <stdio.h>
#include <unistd.h>
int main(void) {
	int x;
	x = 0;
	fork();
	x = 1;
	printf("I am process %ld and my x is %d\n", (long)getpid(), x);
	return 0;
}