#include"Huffmantree.h"
#include"Compress.h"
#include<iostream>
#include<fstream>
#include<stdlib.h>

int main() {
	
	while (1) {
		Compress c;
		c.compress();
		system("pause");
		c.uncompress();
	}
	
	return 0;
}