//
// Created by Sara Queiros on 03/04/2020.
//
#include <stdlib.h>
#include "faturacao.h"
#include "vendas.h"
#include <stdio.h>
#include "filiais.h"
#include "main.h"

typedef struct infofilial{
    char* tipo;
    double fat;
    int filial;
    int qtd;
    int preco;
}*InfoFilial;

typedef struct cli{
    InfoFilial mes[12];
    int numCliente;
}*Cli;

typedef struct subFilial{
    Cli **clientes;
    int posicoes[26];
    int cap[26];

} *SubFilial;
typedef struct filiais{
    SubFilial filiais[3];
}*Filiais;

Filiais initFiliais();

void filiais(SGV sgv ){
    Filiais f = initFiliais();

}
void atualizaFil(int qtd,  char* c, char * tipo, double preco,  int mes,  int filial, Filiais fil){

    for (int i =0; i < fil->filiais[filial-1]->posicoes[c[0]-'A']; i++) {
        /*  if (fil->filiais[filial-1]->clientes[c[0]-'A'][i]->numCliente == (int)strtol(&c[1], (char **)NULL, 10)){
               fil->filiais[filial-1]->clientes[c[0]-'A'][i]->mes[mes-1]->tipo = tipo;
               fil->filiais[filial-1]->clientes[c[0]-'A'][i]->mes[mes-1]->fat = preco * qtd;
               fil->filiais[filial-1]->clientes[c[0]-'A'][i]->mes[mes-1]->qtd = qtd;
               fil->filiais[filial-1]->clientes[c[0]-'A'][i]->mes[mes-1]->preco = preco;

               }
       }*/
        printf("%d\n", fil->filiais[filial - 1]->clientes[c[0] - 'A'][i]->numCliente);
    }}

void addFiliais(char c[6], Filiais f ){
    int primeiro = c[0] - 'A';
    for(int i = 0; i <3; i++) {
        if (f->filiais[i]->posicoes[primeiro] == f->filiais[i]->cap[primeiro]) {
            f->filiais[i]->cap[primeiro] *=2;
            Cli *temp = realloc(f->filiais[i]->clientes[primeiro], f->filiais[i]->cap[primeiro] * sizeof( struct cli));
            f->filiais[i]->clientes[primeiro] = temp;

        }
        f->filiais[i]->clientes[primeiro][f->filiais[i]->posicoes[primeiro]]->numCliente = (int)strtol(&c[1], (char **)NULL, 10);
        f->filiais[i]->posicoes[primeiro]++;
    }


};

Filiais initFiliais(){
    Filiais f = malloc(sizeof(struct filiais));

    for (int i = 0; i< 3; i++) {
        f->filiais[i]=malloc(sizeof(struct subFilial));
        f->filiais[i]->clientes = malloc(sizeof(struct cli));
        for(int j =0; j<26; j++){
            f->filiais[i]->clientes[i] = malloc(sizeof(struct cli));
            f->filiais[i]->posicoes[i] = 0;
            f->filiais[i]->cap[i] = 50;

        }
    }
    return f;
}