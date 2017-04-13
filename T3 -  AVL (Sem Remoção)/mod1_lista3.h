#ifndef MOD1_LISTA3
#define MOD1_LISTA3

#include <string>

struct AvlNode 
{
	int _key;

	//fator de balanceamento = hd-he
	int _balance_factor; 

	AvlNode* _up;
	AvlNode* _left;
	AvlNode* _right;
};

class Avl
{
public:
	//Cria uma arvore vazia
	Avl();

	//Cria uma arvore com um primeiro elemento
	Avl(int key);

	//Cria uma arvore a partir de outra
	Avl(const Avl& orig);

	//Destroi a arvore
	virtual ~Avl();

	//Retorna a altura da arvore
	int height();

	//Insere um elemento na arvore
	void insert(int key);

	//Exibe a arvore no formato
	//<raiz<sub-arvore esquerda><sub-arvore direita>>
	void show(const std::string& title);

	/** Funcoes para percorrer a arvore em ordem: **/  

	//Posiciona o cursor no primeiro elemento
	bool first();

	//Posiciona o cursor no ultimo elemento
	bool last();

	//Atualiza o no cursor para o proximo elemento
	bool next();

	//Atualiza o no cursor para o elemento anterior
	bool prev();

	//Exibe o valor do no cursor atual
	int value();

private:
  
	/* Mantenha as funcoes privadas necessarias 
	* criadas para a Abb e crie as funcoes 
	* (recursivas ou nao) que julgar necessarias
	* para a Avl */

	//Funcao recursiva para exibir a arvore
	void show_rec(AvlNode* node);

	//Copia uma arvore recursivamente
	AvlNode* Avl::CopiaArvore(AvlNode* oldRoot);

	//Deleta uma arvore recursivamente
	void Avl::deleterec(AvlNode* root);

	//Devolve qual o inteiro eh maior
	int Avl::Max(int a, int b);

	//Calcula a altura da arvore recursivamente
	int Avl::heightrec(AvlNode* root);

	//Calcula o fator de balanceamento de acordo com as alturas
	int Avl::getBalance(AvlNode* Node);

	//Faz uma rotacao do no para direita
	AvlNode* rightRotate(AvlNode* Node);

	//Faz uma rotacao do no para esquerda
	AvlNode* leftRotate(AvlNode* Node);

	//insere um no recursivamente
	AvlNode* insertrec(AvlNode* node, int key, int& delta_h);
   
private:
	AvlNode* _root;
	AvlNode* _cursor;
};

#endif
