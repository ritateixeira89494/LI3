#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "catalogos.h"
#include "vendas.h"
#include "faturacao.h"
#include "filiais.h"
#define BUF_SIZE 6

typedef struct sgv {
    Clientes clientes;
    Produtos produtos;
    Vendas vendas;
    Faturacao faturacao;
    Filiais filiais;
} * SGV;



Clientes tclientes(SGV sgv);
Produtos tprodutos(SGV sgv);
Vendas  tvendas(SGV sgv);
void faturacao(SGV sgv);
Clientes initclientes();
Produtos initProdutos();
Vendas initVendas();
SGV initSGV();
Faturacao initFaturacao();
Filiais initFiliais();



int main() {

    SGV sgv = initSGV();

    sgv->clientes = tclientes(sgv);
    sgv->produtos = tprodutos(sgv);
    sgv->vendas =  tvendas(sgv);
    faturacao(sgv);


    return 0;

}

SGV initSGV (){
    SGV sgv = malloc(sizeof(struct sgv));
    sgv->clientes = initclientes();
    sgv->produtos = initProdutos();
    sgv->vendas = initVendas();
    sgv->faturacao = initFaturacao();
    sgv->filiais = initFiliais();
    return sgv;
}


Clientes getClientes (SGV sgv){
    return sgv->clientes;
}

Produtos getProdutos(SGV sgv){
    return sgv->produtos;
}

Vendas getVendas(SGV sgv){
    return sgv->vendas;
}

Faturacao getFaturacao(SGV sgv){
    return sgv->faturacao;
}

Filiais getFiliais (SGV sgv){
    return sgv->filiais;
}

void setFaturacao(Faturacao fat, SGV sgv){
    sgv->faturacao = fat;
}

void setFiliais(Filiais fil, SGV sgv){
    sgv->filiais = fil;
}