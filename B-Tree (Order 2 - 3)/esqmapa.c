#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "mapa.h"

enum minhaposicao { ESQ, MEIO, DIR };
typedef enum minhaposicao tpos;

enum resultadoretirada { OK, RETIRA_MENOR, RETIRA_MAIOR };
typedef enum resultadoretirada tresultret;

struct smapa
{
	int  kp, kg;   /* chaves: kp<kg, se kg existir. Se kg=-1, significa que ele n�o existe. */
	Mapa  *pai;
	Mapa  *esq;
	Mapa  *meio;
	Mapa  *dir;
};

Mapa* cria(void) {
	return NULL;
}

Mapa* novoNo(int chave) {
	Mapa *m = (Mapa*)malloc(sizeof(struct smapa));
	if (m == NULL) { printf("erro no malloc! \n"); exit(1); }
	m->pai = NULL;
	m->kp = chave;
	m->kg = -1;
	m->esq = m->meio = m->dir = NULL;
	return m;
}

Mapa* overflowQuebra(Mapa *m, int *valorainserir, Mapa* novofilho) {
	Mapa* novo;
	int temp;

	novo = (Mapa*)malloc(sizeof(struct smapa));
	if (novo == NULL) { printf("erro no malloc! \n"); exit(1); }

	if (*valorainserir > m->kg) {
		temp = m->kg;
		novo->kp = m->kp;
		novo->kg = -1;
		m->kp = *valorainserir;
		m->kg = -1;
		*valorainserir = temp;
	}

	if (*valorainserir < m->kp) {
		temp = m->kp;
		novo->kp = *valorainserir;
		novo->kg = -1;
		m->kp = m->kg;
		m->kg = -1;
		*valorainserir = temp;
	}

	if (*valorainserir < m->kg && *valorainserir > m->kp) {
		novo->kp = m->kp;
		novo->kg = -1;
		m->kp = m->kg;
		m->kg = -1;
	}

	/* COMPLETAR */

	return novo;
}

int insere2(Mapa* m, int chave, int* valorainserir, Mapa** novofilho) {

	int inseriraqui = 0; /* indica se deve inserir neste n� */

	if (m == NULL) {
		printf("erro! sub�rvore nula! \n"); exit(1);
	}

	if (m->esq != NULL) { /* n�o � folha, s� insere neste n� se subir um valor  */
		if (chave < m->kp) {
			inseriraqui = insere2(m->esq, chave, valorainserir, novofilho);
		}
		else if (((m->kg != -1) && (chave < m->kg)) || (m->kg == -1)) {
			/* ou est� entre as duas chaves ou s� tem uma chave no n� */
			inseriraqui = insere2(m->meio, chave, valorainserir, novofilho);
		}
		else { /* chave > m->kg */
			inseriraqui = insere2(m->dir, chave, valorainserir, novofilho);
		}
	}
	else { /* este n� � folha, tem que inserir nele de qq jeito */
		*valorainserir = chave;
		inseriraqui = 1;
		*novofilho = NULL;
	}

	if (!inseriraqui) return 0; /* inser��o j� est� completa */


	if (m->kg == -1) {
		/* tem  espa�o no n� */
		m->kg = chave;
		/* COMPLETAR */

		return 0; /* como havia espa�o, n�o sobem valores a serem inseridos */
	}

	*novofilho = overflowQuebra(m, valorainserir, *novofilho);

	return 1; /* quando h� quebra sempre sobe a mediana para nova inser��o */
}

Mapa* insere(Mapa* m, int chave) {
	int valorquesubiu;
	Mapa* novofilho;
	Mapa* novaraiz;

	if (m == NULL) {
		m = novoNo(chave);
		m->pai = novoNo(-1);
	}
	else {
		if (insere2(m, chave, &valorquesubiu, &novofilho)) {
			/* cria nova raiz */
			novaraiz = novoNo(valorquesubiu);
			novaraiz->pai = m->pai;
			novaraiz->esq = novofilho;
			novaraiz->esq->pai = novaraiz;
			novaraiz->meio = m;
			novaraiz->meio->pai = novaraiz;
			m = novaraiz;
		}
	}

	return m;
}

int busca(Mapa *m, int chave) {
	return 0;
}

tpos minhaposnopai(Mapa* pai, Mapa* filho) {
	if (filho == pai->esq)
		return ESQ;
	else if (filho == pai->meio) return  MEIO;
	else if (filho == pai->dir) return DIR;
	else return -1;
}

void preenche(Mapa *m, Mapa *nesq, int nkp, Mapa *nmeio, int nkg, Mapa *ndir) {
	m->esq = nesq;
	m->kp = nkp;
	m->meio = nmeio;
	m->kg = nkg;
	m->dir = ndir;
}

int maisaesquerda(Mapa *m) {
	while (m->esq != NULL) m = m->esq;
	return m->kp;
}

tresultret retirarec(Mapa *m, int chave) {

	tresultret res;
	tpos minhapos;
	Mapa *filhoqueficou, *irmao;

	if (m == NULL) {
		printf("erro! sub�rvore nula! \n"); exit(1);
	}

	if (m->esq != NULL) { /* n�o � folha */
		if (chave < m->kp) {
			res = retirarec(m->esq, chave);
		}
		else if (m->kp == chave) { /* achou - troca por succ */
			m->kp = maisaesquerda(m->meio);
			res = retirarec(m->meio, m->kp);
		}
		else if (((m->kg != -1) && (chave < m->kg)) || (m->kg == -1)) {
			/* ou est� entre as duas chaves ou s� tem uma chave no n� */
			res = retirarec(m->meio, chave);
		}
		else if (m->kg == chave) { /* achou - troca por succ */
			m->kg = maisaesquerda(m->dir);
			res = retirarec(m->dir, m->kg);
		}
		else { /* chave > m->kg */
			res = retirarec(m->dir, chave);
		}
		if (res == OK) return OK;
	}
	else { /* este n� � folha, chave tem que estar nele de qq jeito */
		if (chave == m->kp) res = RETIRA_MENOR;
		else if (chave == m->kg) res = RETIRA_MAIOR;
		else /* chave n�o est� na �rvore!!! */
			return OK;
	}

	/* retirada */
	/* pode ser porque estamos em uma folha ou porque "caiu" uma das chaves */

	if (res == RETIRA_MAIOR) { /* caso mais simples */
		preenche(m, m->esq, m->kp, m->meio ? m->meio : m->dir, -1, NULL);
		return OK;
	}

	/* RETIRAMENOR */
	if (m->kg != -1) {
		/* ainda vai ficar um no n�, tb simples */
		preenche(m, m->esq ? m->esq : m->meio, m->kg, m->dir, -1, NULL);
		return OK;
	}

	/* RETIRAMENOR: essa � a �nica chave! combinar ou distribuir */

	minhapos = minhaposnopai(m->pai, m);

	/* se ainda tiver algum filho peg�-lo para reposicionar */
	filhoqueficou = m->esq ? m->esq : m->meio;

	if (minhapos == ESQ) {
		/* sempre tem irmao no meio - pegar */
		irmao = m->pai->meio;
		if (irmao->kg == -1) { /* combinar */
			preenche(irmao, filhoqueficou, m->pai->kp, irmao->esq, irmao->kp, irmao->meio);
			if (irmao->esq) irmao->esq->pai = irmao;
			m->pai->esq = NULL;
			free(m);
			res = RETIRA_MENOR;
		}
		else { /* irm�o tem duas chaves, redistribuir  */
			preenche(m, filhoqueficou, m->pai->kp, irmao->esq, -1, NULL);
			if (m->esq) m->esq->pai = m;
			if (m->meio) m->meio->pai = m;
			preenche(m->pai, m->pai->esq, irmao->kp, m->pai->meio, m->pai->kg, m->pai->dir);
			preenche(irmao, irmao->meio, irmao->kg, irmao->dir, -1, NULL);
			res = OK;
		}
	}
	else if (minhapos == MEIO) {
		/* sempre tem irmao a esquerda - pegar */
		/* COMPLETAR */
	}
	else if (minhapos == DIR) {
		/* sempre tem irmao a esquerda - pegar */
		/* COMPLETAR */
	}
	return res;
}


Mapa* retira(Mapa *m, int chave) {
	tresultret res;
	Mapa* novaraiz;


	res = retirarec(m, chave);

	if (res == RETIRA_MAIOR) { /* caso mais simples */
		preenche(m, m->esq, m->kp, m->meio ? m->meio : m->dir, -1, NULL);
	}

	else if (res == RETIRA_MENOR) {

		if (m->kg != -1) {
			/* ainda vai ficar um no n�, tb simples */
			preenche(m, m->esq ? m->esq : m->meio, m->kg, m->dir, -1, NULL);
		}

		else {
			/* vai acabar com a raiz */
			/* um dos filhos virou nulo - pegar o outro */
			novaraiz = (m->esq) ? m->esq : m->meio;
			novaraiz->pai = m->pai;
			free(m);
			m = novaraiz;
		}
	}

	return m;
}

void destroi(Mapa *m) {
	if (m != NULL) {
		destroi(m->esq);
		destroi(m->meio);
		destroi(m->dir);
		free(m);
	}
}

void debug_mostra_mapa_int(Mapa *m) {
	printf("[");
	if (m != NULL) {
		printf("%d:%d/%d ", m->kp, m->kg, m->pai->kp);
		debug_mostra_mapa_int(m->esq);
		debug_mostra_mapa_int(m->meio);
		if (m->kg != -1) debug_mostra_mapa_int(m->dir);
	}
	printf("]");
}

void debug_mostra_mapa(Mapa *m) {
	debug_mostra_mapa_int(m);
	printf("\n");
}