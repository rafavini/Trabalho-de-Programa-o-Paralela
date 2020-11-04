#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <queue>
#include <stack>
#include <omp.h>
#define max 100000

using namespace std;

struct celula
{
    int i;
    int j;
};

celula par(int i, int j){
    celula par;
    par.i = i;
    par.j = j;
    return par;
}


bool OK(int linha, int coluna,int m, int n){
    if((linha >= 0) && (linha < m) && (coluna >= 0) && (coluna < n)){
        return true;
    }else 
        return false;
    
}

int main(int argc, char *argv[]){
    //PEGANDO TEMPO INICIAL DO PROGRAMA
     double  tini,tfin,texec;
    tini = omp_get_wtime();

    int i=0;

    //ARQUIVOS
    FILE *arq;
    FILE *arqSaida;
    char *nomeUm; //arquivo entrada
    char *nomeDois; //arquivo saida
    nomeUm = argv[1];
    nomeDois = argv[2];
    printf("nome do arquivo: %s\n", nomeUm);
    arq = fopen(nomeUm, "rt");
    arqSaida = fopen(nomeDois, "wt");
    if(arq == NULL){
        printf("PROBLEMA PARA ABRIR O ARQUIVO!\n");
        return 0;
    }

    //VETOR COM AS INFORMAÇÕES DO ARQUIVO
    int vetInfo[200000];
    //ARMAZENANDO AS INFORMAÇÕES DO ARQUIVO NO VETOR
    while (!feof(arq))
    { 
       fscanf(arq,"%d",&vetInfo[i]);
        i++;
    }

     //VARIAVEIS PARA USO DO PROGRAMA
    
    int j=0;
    int x=0;
    int obstaculo = vetInfo[6];


    //CRIADO GRID
    int **grid = (int **)malloc(vetInfo[0] * sizeof(int *));

    for( i=0; i < vetInfo[0];i++){
         grid[i] = (int *)malloc(vetInfo[1] * sizeof(int));
    }

    for( i=0; i < vetInfo[0];i++){
        for( j=0; j < vetInfo[1];j++){
            grid[i][j] = max;
        }
    }


    //COLOCANDO 0 NA ORIGEM;
    
    int p = vetInfo[2];
    int k = vetInfo[3];
    bool visitado[p][k];
    for(i = 0; i < p;i++){
        for(j =0; j < k;j++){
            visitado[i][j] = false;
        }
    }
    grid[p][k] = 0;

    int m,n,aux,lin,col,pos_lin,pos_col,pos_m,pos_n,cont;
    m = vetInfo[7];
    n = vetInfo[8];
    lin = vetInfo[9];
    col = vetInfo[10];
    pos_m = 7;
    pos_n = 8;
    pos_lin = 9;
    pos_col = 10;

 	aux = 7;
	for (k = 0; k < obstaculo; k++){
		for (i = 0; i < vetInfo[aux + 2]; i++){
			for (j = 0; j < vetInfo[aux + 3]; j++){
				grid[vetInfo[aux] + i][vetInfo[aux + 1] + j] = -1;
			}
		}
		aux = aux + 4;
	}
/*
    for( i=0; i < vetInfo[0];i++){
        for( j=0; j < vetInfo[1];j++){
            printf("%d \t",grid[i][j]);
        }
        printf("\n");
    }*/
    

    //EXP VARIAVEIS
    int minimo=0;
    bool achou = false;
    celula origem = {vetInfo[2], vetInfo[3]};
    celula destino = {vetInfo[4], vetInfo[5]};
    int l[] = {-1,0,0,1};
    int c[] = {0,-1,1,0};
    
    queue<celula> fila;
    fila.push(origem);

    int taml = vetInfo[0];
    int tamc = vetInfo[1];
    //EXP
    while(!fila.empty() && !achou){
        celula pt = fila.front();
        fila.pop();

        if(pt.i == destino.i && pt.j == destino.j){
            achou = true;
            minimo = grid[pt.i][pt.j];
        }else{
           for(int count = 0; count < 4; count++){
               int linha = pt.i + l[count];
               int coluna = pt.j + c[count];

               //printf("linha %d coluna %d p %d k %d\n", linha, coluna, taml, tamc);
               if(OK(linha, coluna, taml, tamc)){
                    if(grid[linha][coluna] == max){
                        grid[linha][coluna] = grid[pt.i][pt.j] + 1;
                        celula adjacente = {linha,coluna};
                        fila.push(adjacente);
                    }
               }
               
           }
        }
    
}

 /* for( i=0; i < vetInfo[0];i++){
        for( j=0; j < vetInfo[1];j++){
            printf("%d \t",grid[i][j]);
        }
        printf("\n");
    }
    */

    
    
    printf("minimo = %d\n",minimo);

    




}
