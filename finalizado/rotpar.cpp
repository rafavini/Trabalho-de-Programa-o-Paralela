/*
Nomes: Rafael Vinicius e Calebe Lemos
comando para compilação: g++ rotseq.cpp -fopenmp -o rotseq
Comando de executação: ./rotseq entrada.txt saida.txt 
*/
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




    int p = vetInfo[2];
    int k = vetInfo[3];
  
    grid[p][k] = 0;

    //COLOCANDO OBSTACULOS NO GRID
 	int cont = 7;
	for (x = 0; x < obstaculo; x++){
		for (i = 0; i < vetInfo[cont + 2]; i++){
			for (j = 0; j < vetInfo[cont + 3]; j++){
				grid[vetInfo[cont] + i][vetInfo[cont + 1] + j] = -1;
			}
		}
		cont+= 4;
	}


    

    //EXP VARIAVEIS
    int minimo=0;
    bool achou = false;
    celula origem = {vetInfo[2], vetInfo[3]};
    celula destino = {vetInfo[4], vetInfo[5]};
    int l[] = {-1,0,1,0};
    int c[] = {0,-1,0,1};
    queue<celula> fila;
    fila.push(origem);

    int taml = vetInfo[0];
    int tamc = vetInfo[1];

    tini = omp_get_wtime();
    //EXP
    while(!fila.empty() && !achou){
        celula pt = fila.front();
        fila.pop();

        if(pt.i == destino.i && pt.j == destino.j){
            achou = true;
            minimo = grid[pt.i][pt.j];
        }else{
            //INICIANDO AREA PARALELA
            #pragma omp prallel
           for(int count = 0; count < 4; count++){
               int linha = pt.i + l[count];
               int coluna = pt.j + c[count];

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


;


//BACKTRACKING
queue<celula> caminho;
if(achou){
    
    queue<celula> fila2;
    fila2.push(destino);
     celula pt;
    int menor1,menor=max;
    while(pt.i != origem.i || pt.j!= origem.j){
        pt = fila2.front();
        fila2.pop();
        menor1 = grid[pt.i][pt.j];
        if(menor1 < menor){
            caminho.push(pt);
        }
        for(int count = 0; count < 4; count++){
            int linha = pt.i + l[count];
            int coluna = pt.j + c[count];
        
            
                if(OK(linha,coluna,taml,tamc)){
                    if(grid[linha][coluna] == grid[pt.i][pt.j]-1 && grid[linha][coluna] != -1){
                        menor = grid[pt.i][pt.j];
                        pt = par(linha,coluna);
                        fila2.push(pt);
                        count = 4;
                    }
                }
            
        }
}
}

//INVERTENDO A FILA PARA COLOCAR NO ARQUIVA
stack<celula> Stack; 
    while (!caminho.empty()) { 
        Stack.push(caminho.front()); 
        caminho.pop(); 
    } 
    while (!Stack.empty()) { 
        caminho.push(Stack.top()); 
        Stack.pop(); 
    }

//IMPRIMINDO NO ARQUIVO
 fprintf(arqSaida,"%d\n",minimo);
  fprintf(arqSaida,"%d %d\n",origem.i,origem.j);
while(!caminho.empty()){
        celula pos = caminho.front();
        fprintf(arqSaida,"%d %d \n",pos.i,pos.j);
        
        caminho.pop();
    }



   tfin = omp_get_wtime();
   texec = tfin - tini;
   printf("tempo de exec %f\n", texec);

    
    
    printf("minimo = %d\n",minimo);

    free(grid);    

     fclose(arq);
     fclose(arqSaida);

    




}