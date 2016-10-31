#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "mapa.h"

/*
void quebraAbstracao(Mapa* m){

if( m == NULL)
return;
quebraAbstracao(m->esq);
printf("Chave: %d\n", m->kp);

if(m->kg != -1){
printf("Chave: %d\n", m->kg);
}

if(m->dir !=NULL){
quebraAbstracao(m->dir);
}

}*/

int main(int argc, char** argv) {

	int i;
	int tam;

	//if (argc < 2) { printf("uso: %s <qtos_inserir>\n", argv[0]); exit(1);}
	tam = 10; //atoi(argv[1]);

	Mapa *mapa1 = cria();
	Mapa *mapa2 = cria();
	Mapa *mapa3 = cria();

	printf("inserção sempre �  esquerda:\n");
	for (i = tam - 1; i >= 0; i--) {
		mapa1 = insere(mapa1, i);
	}
	debug_mostra_mapa(mapa1);

	printf("inserção sempre �  direita:\n");
	for (i = 0; i<tam; i++) {
		mapa2 = insere(mapa2, i);
	}
	debug_mostra_mapa(mapa2);

	printf("inserção variada:\n");
	for (i = 0; i<2 * tam; i++) {
		mapa3 = (i % 2) ? insere(mapa3, 2 * tam - i) : insere(mapa3, i);
	}
	debug_mostra_mapa(mapa3);

	/*
	quebraAbstracao(mapa1);
	quebraAbstracao(mapa2);
	quebraAbstracao(mapa3);
	*/
	destroi(mapa1);
	destroi(mapa2);
	destroi(mapa3);

	return 0;
}



