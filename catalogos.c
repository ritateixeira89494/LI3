//
// Created by Sara Queiros on 05/03/2020.
//
#include "faturacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "vendas.h"
#include "main.h"
#include "filiais.h"

#define BUF_SIZE 6
typedef struct clientes{
    char*** a;
    int pos[26];
} *Clientes;

Clientes initclientes ();
int valida(char *buf);
void ordemAlf ( Clientes clientes, char * buf, int posicoes[], int capac[]);
Filiais initFiliais(SGV sgv);
void addFiliais(char buf[6], Filiais filiais);
void setFiliais(Filiais fil, SGV sgv);

Clientes tclientes(SGV sgv) {
    Filiais filiais = initFiliais(sgv);
    FILE *fclientes = NULL;
    char buf[BUF_SIZE];
    int tam = 0;             //tamanho do array
    Clientes clientes = initclientes();
    int i;
    fclientes = fopen("../grupo72/projC/docs/Clientes.txt", "r");
    int capac[26];
    for (i = 0; i< 26; i++) { capac[i] = 100;}

    while (fgets(buf, BUF_SIZE, fclientes) != NULL) {
        buf[5]= '\0';

        if (valida(strdup(buf)) == 0) {
            ordemAlf(clientes, strdup(buf), clientes->pos, capac);
            tam ++;
            addFiliais(buf, filiais);}}
    printf("%d\n", tam);
    setFiliais(filiais, sgv);
    fclose(fclientes);

    return clientes;

}

void ordemAlf (Clientes clientes, char * buf, int posicoes[], int capac[]){

    if(posicoes[buf[0] - 'A'] == capac[buf[0] - 'A']){
        capac[buf[0] - 'A'] *=2;
        char **temp = realloc(clientes->a[buf[0] - 'A'], capac[buf[0] - 'A'] * sizeof(char*));
        clientes->a[buf[0] - 'A'] = temp;
    }
    clientes->a[buf[0] - 'A'][posicoes[buf[0] - 'A']] =  strdup(buf);
    posicoes[buf[0] - 'A']++;
}

int valida(char buf[]) {
    if(buf[0] - 'A' >= 0 && buf[0] - 'A' <= 25  && atoi(&buf[1])>= 1000 && atoi(&buf[1]) <= 9999)

        return 0;
    else return 1;
}

Clientes initclientes (){
    Clientes nova = malloc(sizeof(struct clientes));
    nova->a = malloc(26 * sizeof(char *));
    for (int i = 0 ; i < 26; i++ ) {
        nova->pos[i] = 0;
        nova->a[i] = malloc(100* sizeof(char **));
        for(int j = 0; j<100; j++)
            nova->a[i][j] = malloc(100* sizeof(char *));
    }
    return nova;
}



int validarCliente(Clientes clientes, char* c){

    for (int i = 0; i < clientes->pos[c[0]- 'A'] ; i++)
        if (strcmp(c,clientes->a[c[0]- 'A'][i]) == 0)
            return 0;
    return 1;
}













#define BUF 7

typedef struct produtos{
    char**** a;
    int posicoes[26][26];
} *Produtos;

Produtos initProdutos();
int validaP(char buf[]);
Faturacao getFaturacao(SGV sgv);
void ordemAlfP(Produtos produtos, char buf[64], int posicoes[26][26], int capacidade[26][26]);
void addFat(char* buf, Faturacao fat);
void setFaturacao(Faturacao fat, SGV sgv);

Produtos tprodutos(SGV sgv) {
    Faturacao fat= getFaturacao(sgv);
    Produtos produtos = initProdutos();
    FILE *fprodutos = NULL;
    char bufP[BUF];
    int capacidade[26][26];
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            capacidade[i][j] = 50;
        }
    }

    fprodutos = fopen("../grupo72/projC/docs/Produtos.txt", "r");

    int total = 0;
    while (fgets(bufP, BUF, fprodutos) != NULL) {

        bufP[6]='\0';
        if (validaP(bufP) == 0){
            ordemAlfP( produtos, strdup(bufP), produtos->posicoes, capacidade);
            // addFat(bufP, fat);
            total++;
        }


    }
    int fim = 0;
    setFaturacao(fat, sgv);
    printf("total prods %d\n", total);

    return produtos;
}





Produtos initProdutos(){
    Produtos novo = malloc(sizeof(struct produtos));
    novo->a = malloc(26* sizeof(char ***));
    for (int i = 0; i < 26; i++) {
        novo->a[i] = malloc(26 * sizeof(char **));
        for (int j = 0; j < 26; j++) {
            novo->a[i][j] = malloc(100000 * sizeof(char *));
            novo->posicoes[i][j] = 0;

        }
    }
    return novo;

}

void ordemAlfP(Produtos produtos, char * buf, int posicoes[26][26], int capacidade[26][26]) {

    if (posicoes[buf[0] - 'A'][buf[1] - 'A'] == capacidade[buf[0] - 'A'][buf[1] - 'A']) {
        capacidade[buf[0] - 'A'][buf[1] - 'A'] *= 2;
        char *temp = realloc(produtos->a[buf[0] - 'A'][buf[1] - 'A'][posicoes[buf[0] - 'A'][buf[1] - 'A']],capacidade[buf[0] - 'A'][buf[1] - 'A'] * (sizeof(char*)));
        produtos->a[buf[0] - 'A'][buf[1] - 'A'][posicoes[buf[0] - 'A'][buf[1] - 'A']] = temp;
    }

    produtos->a[buf[0] - 'A'][buf[1] - 'A'][posicoes[buf[0] - 'A'][buf[1] - 'A']] = buf;
    posicoes[buf[0] - 'A'][buf[1] - 'A']++;
}


int validaP(char bufP[]) {
    if((isupper(bufP[0]) && (isupper(bufP[1])) && atoi(&bufP[2])<=9999 && atoi(&bufP[2])>=1000 )){
        return 0;}
    else return 1;
}

int validarProduto(Produtos produtos, char* p){
    for (int i = 0; i < produtos->posicoes[p[0] - 'A'][p[1] - 'A'] ; i++)
        if (strcmp(produtos->a[p[0] - 'A'][p[1] - 'A'][i], p) == 0) return 0;
    return 1;
}
