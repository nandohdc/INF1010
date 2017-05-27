#include "..\..\..\..\..\Downloads\mod2_lista6\mod2_lista6.h"
#include <iostream>
#include <fstream>
#include <utility>



int main(void) {

	std::string inputPath("C:\\Users\\nando\\Downloads\\mod2_lista6\\texto1.txt");
	std::string outputPath("C:\\Users\\nando\\Downloads\\mod2_lista6\\example.csv");
	Hash hashishe(0);
	hashishe.countWords(inputPath, outputPath);




	return  0;
}