#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "catalogos.h"
#include "vendas.h"
#include "main.h"
#include "faturacao.h"
#include "filiais.h"

#define BUF_SIZE 64

Vendas* initVendas();

typedef struct vendas{
    int qtd;
    char* produto;
    char* cliente;
    char* tipo;
    double preco;
    int mes;
    int filial;
} * Vendas;

int validarProduto(Produtos provp, char* p);
int validarCliente(Clientes provc, char* c);
int validarQnt(char *q);
int validarPreco(char *pre);
int validarMes(char *m);
int validarFilial(char *f);
int validarTipo(char *tp);
Filiais getFiliais (SGV sgv);
void setFaturacao(Faturacao fat, SGV sgv);
Clientes initclientes();
Produtos initProdutos();
Clientes getClientes(SGV sgv);
Produtos getProdutos(SGV sgv);
Faturacao getFaturacao(SGV sgv);
void atualizaFat(int qtd, char* produto, char* tipo, double preco, int mes, int filial,  Faturacao fat);
void atualizaFil(int qtd, char* cliente, char* tipo, double preco, int mes, int filial,  Filiais fil);



Vendas* tvendas(SGV sgv) {
    Clientes provc = getClientes(sgv);
    Produtos provp = getProdutos(sgv);
    Faturacao fat = getFaturacao(sgv);
    Filiais fil = getFiliais(sgv);
    char *q;
    char *p;
    char *c;
    char *tp;
    char *pre;
    char *m;
    char *f;

    FILE *fvendas = NULL;
    char bufP[BUF_SIZE];

    int capacidade = 50;
    Vendas * venda = initVendas();

    int t = 0; //tamanho do array
    int i = 0;
    int v = 0;

    fvendas = fopen("../grupo72/projC/docs/Vendas_1M.txt", "r");

    while (fgets(bufP, BUF_SIZE, fvendas) != NULL) {
        if (t == capacidade) {
            capacidade *=2;
            Vendas *temp = realloc(venda,capacidade*sizeof(venda));
            venda=temp;
        }

        p = strdup(strtok(bufP," "));
        pre = strdup(strtok(NULL," "));
        q = strdup(strtok(NULL," "));
        tp = strdup(strtok(NULL," "));
        c =strdup(strtok(NULL," "));
        m = strdup(strtok(NULL," "));
        f =strdup(strtok(NULL," "));

        if ((validarPreco(pre)+validarFilial(f) + validarMes(m) + validarTipo(tp) + validarQnt(q)) +
            validarCliente(provc, c) + validarProduto(provp, p) == 0) {
            venda[i] = malloc(sizeof(struct vendas));
            venda[i]->produto = p;
            venda[i]->preco = atof(pre);
            venda[i]->qtd = atoi(q);
            venda[i]->tipo = tp;
            venda[i]->cliente = c;
            venda[i]->mes = atoi(m);
            venda[i]->filial = atoi(f);
            // setFilial(filial1, filial2, filial3, (venda[i]));
            //atualizaFat(venda[i]->qtd, venda[i]->produto, venda[i]->tipo, venda[i]->preco,  venda[i]->mes,  venda[i]->filial,  fat);
            atualizaFil(venda[i]->qtd, venda[i]->cliente, venda[i]->tipo, venda[i]->preco,  venda[i]->mes,  venda[i]->filial,  fil);
            v++;
        }
        i++;
        t++;
    }
    setFaturacao(fat, sgv);
    printf("vendas validas:%d", v);
    fclose(fvendas);
    return venda;
}

Vendas* initVendas(){
    int capacidade = 50;
    Vendas *vendas = malloc(capacidade * sizeof(Vendas));
    return vendas;
}
/*
void setFilial(Vendas *filial1, Vendas *filial2, Vendas *filial3, Vendas venda) {
    int tam[3];
    int cap[3];
    for (int i = 0; i< 3; i ++) {tam[i] = 0; cap[i] = 50;}

    if((venda->filial) == 1){
        if (tam[0] == cap[0]) {
        cap[0] *= 2;
        Vendas *tempf1 = realloc(filial1, cap[0] * sizeof(filial1));
        filial1 = tempf1;}
    filial1[tam[0]] = venda;
    tam[0]++;}

    if(venda->filial == 2){
        if (tam[1] == cap[1]) {
            cap[1] *= 2;
            Vendas *tempf2 = realloc(filial2, cap[1] * sizeof(filial2));
            filial2 = tempf2;}
        filial2[tam[1]] = venda;
        tam[1]++;}

    if(venda->filial == 3){
            if (tam[2] == cap[2]) {
                cap[2] *= 2;
                Vendas *tempf3 = realloc(filial3, cap[2] * sizeof(filial3));
                filial3 = tempf3;}
            filial3[tam[2]] = venda;
            tam[2]++;}
}
*/

int validarPreco(char* pre) {
    if((atof(pre) >= 0.00) && (atof(pre)<= 999.99)) return 0;
    else return 1;
}

int validarQnt(char* q){
    if((atoi(q) >=1) && (atoi(q)<=200)) return 0;
    else return 1;
}

int validarTipo(char* tp){
    if(strcmp(tp,"P")==0 || strcmp( tp, "N")== 0) return 0;
    else {return 1;}
}

int validarMes(char* m){
    if((atoi(m) >=1) && (atoi(m))<=12) return 0;
    else return 1;
}

int validarFilial(char * f) {
    if((atoi(f) ==1) || ((atoi(f))==2)|| ((atoi(f))==3)) return 0;
    else return 1;
}


