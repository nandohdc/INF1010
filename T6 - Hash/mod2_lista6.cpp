#include "mod2_lista6.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <utility>

Hash::Hash( int tableSize )
    : _table( new std::pair< std::string, int >[tableSize] )
{
	this->_size = tableSize;
    //Inicializa cada posicao com <"",0>
    for( int i = 0; i < tableSize; ++i )
        _table[i] = std::make_pair("",0);
}


Hash::~Hash()
{	
    delete[] _table;
	std::cout << "The hash table has been deleted." << std::endl;
}


void Hash::insert(const std::string& word)
{
	int index = hash(word);

	if (this->_table[index].first != word && this->_table[index].second != 0) { //Caso da colisao, funcao vai procurar a proxima possicao livre para inserir o par.
		while (this->_table[index].second == 0 && index < this->_size) {
			index++;
		}
		if (index == this->_size) {
			return;
		}
		this->_table[index].first = word;
		this->_table[index].second = this->_table[index].second + 1;
	}

	else if (this->_table[index].second != 0) {
		this->_table[index].second = this->_table[index].second + 1;
	}

	else {
		this->_table[index].first = word;
		this->_table[index].second = this->_table[index].second + 1;
	}
}

int Hash::countWordsFile(const std::string& inputPath) {
	std::ifstream input;
	input.open(inputPath);
	int counter = 0;
	if (input.is_open())
	{
		std::string word;
		while (input >> word)
		{
			counter++;
		}
		input.close();
	}
	return counter;
}

void Hash::countWords(const std::string& inputPath,
	const std::string& outputPath)
{
	// Abre o arquivo para leitura
	std::cout << inputPath << " " << outputPath << std::endl;

	std::ifstream input;
	input.open(inputPath.c_str());
	if(input.is_open()) // Se conseguiu abrir o arquivo
	{
		// Inicializa a Hash
		int counter = this->countWordsFile(inputPath);
		Hash wordCounter(counter);
		std::string word;
		while(input >> word) // Le p a l a v r a p o r p a l a v r a
		{
			auto it = word.begin();
			while (it != word.end())
			{
				if (!isalpha(*it))
					it = word.erase(it); //A função erase retorna o iterador para o próximo item
				else ++it;
			}

			std::transform(word.begin(), word.end(), word.begin(), tolower);

			if (!word.empty())
				wordCounter.insert(word);
		}
		// F e c ha o a r q u i v o
		input.close();
		// E s c r e v e o r e s u l t a d o em a r q u i v o
		wordCounter.writeCSV(outputPath);
	}
}


int Hash::getCount(const std::string& word)
{
	int index = hash(word);

    return this->_table[index].second;
}


bool Hash::writeCSV(const std::string& filePath)
{
	std::ofstream outputCSV;
	outputCSV.open(filePath.c_str());

	if (outputCSV.is_open()) {
		for (int i = 0; i < this->_size; i++){
			if (this->_table[i].second != 0){
				outputCSV << this->_table[i].first << "," << this->_table[i].second << std::endl;
			}
		}
		outputCSV.close();
		return true; 
	}
	return false;
}

int Hash::hash(const std::string& word)
{
	int sum = 0;

	for (int i = 0; i < word.length(); i++) {
		sum = sum + word.at(i);
	}
    return sum % this->_size;
}
