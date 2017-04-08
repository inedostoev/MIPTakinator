#include <stdio.h>
#include <stdlib.h>
#include "TREE.h"

int main()
{
	TREE s;
	s.inputFile_ = fopen("configFile.txt", "r");
	s.outputFile_ = fopen("exit.txt", "w");
	s.execute();	
	return 0;
}
