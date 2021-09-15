#include "msh.h"
#include <stdlib.h>

int main(void)
{
	msh_reader_start();
	system("leaks msh");
}
