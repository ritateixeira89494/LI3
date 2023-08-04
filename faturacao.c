//
// Created by Sara Queiros on 31/03/2020.
//
#include <stdlib.h>
#include "faturacao.h"
#include "vendas.h"
#include <stdio.h>


typedef struct info{
    char* tipo;
    double fat;
    int filial;
    int qtd;
}Info;

typedef struct prod{
    Info mes[12];
    int numProd;
}Prod;

typedef struct faturacao{
    Prod ***prods;
    int posicoes[26][26];
    int cap[26][26];
    
} *Faturacao;

Faturacao initFaturacao();

void faturacao(Produtos  prods,Vendas vendas ){
Faturacao faturacao = initFaturacao();
}



void atualizaFat(int qtd, char* produto, char* tipo, double preco,  int mes,  int filial,  Faturacao fat){
for(int i = 0; i< fat->posicoes[produto[0]-'A'][produto[1]-'A']; i++){
    if(fat->prods[produto[0]-'A'][produto[1]-'A'][i] .numProd == (int)strtol(&produto[2], (char **)NULL, 10)) {
        fat->prods[produto[0] - 'A'][produto[1] - 'A'][i].mes[mes - 1].tipo = tipo;
        fat->prods[produto[0] - 'A'][produto[1] - 'A'][i].mes[mes - 1].qtd = qtd;
        fat->prods[produto[0] - 'A'][produto[1] - 'A'][i].mes[mes - 1].filial = filial;
        fat->prods[produto[0] - 'A'][produto[1] - 'A'][i].mes[mes - 1].fat = qtd * preco;

    }

    }

}


void addFat(char buf[6], Faturacao fat){

    int primeiro = buf[0]-'A';
    int segundo = buf[1]-'A';
   if (fat->posicoes[primeiro][segundo] == fat->cap[primeiro][segundo]) {
        fat->cap[primeiro][segundo] *= 2;
        Prod *temp = realloc(fat->prods[primeiro][segundo],fat->cap[primeiro][segundo] * (sizeof(struct prod)));
        fat->prods[primeiro][segundo] = temp;
    }

   fat->prods[primeiro][segundo][fat->posicoes[primeiro][segundo]].numProd = (int)strtol(&buf[2], (char **)NULL, 10);
   // printf("%d\n", fat->prods[primeiro][segundo][fat->posicoes[primeiro][segundo]].numProd);
   fat->posicoes[primeiro][segundo]++;

}


Faturacao initFaturacao(){
    Faturacao fat = malloc(sizeof(struct faturacao));
    fat->prods = malloc(26* sizeof(struct prod** ));
    for (int i = 0; i< 26; i++) {
        fat->prods[i] = malloc(26 * sizeof(struct prod *));
        for (int j = 0; j < 26; j++) {
            fat->prods[i][j] = malloc(50 * sizeof(struct prod));
            fat->posicoes[i][j] = 0;
            fat->cap[i][j] = 50;

        }
    }
    return fat;
}