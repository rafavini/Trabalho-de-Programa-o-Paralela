#include <stdio.h>
#include <iostream>
#include <queue>

using namespace std;

//funçao que imprime a fila.
//METODOS FILA.SIZE, FILA.PUSH, FILA.POP, FILA.FRONT, FILA.BACK
void imprime_fila(queue<int> fila){
    for(int i = fila.front(); i < fila.size();i++){
        printf("%d",i);
    }
}

void espancao(char *info){
    int i=0;
    int j=0;
    int obstaculo = info[6]; //ARMAZENA QUANTIDADE DE OBSTACULOS info[6] 
    bool achou = false;
    queue<int> fila; //CRIA A FILA, PARA ENVIAR A FILA É SÓ O NOME.
    int grid[info[0]][info[1]]; //info[0] representa o n de linhas e info[1] representa o n de colunas

    grid[info[2]][info[3]] = 0; //inicializa o indice da origem com 0

    //insere a origem na fila
    fila.push(grid[info[2]][info[3]]);

    //A PARTIR DAQUI IMPLEMENTAR O WHILE DA ESPANCAO

}


int main(int argc, char *argv[]){
    FILE *arq;
    char *nomeUm; //arquivo entrada
    char *nomeDois; //arquivo saida
    char Linha[100];
    char *result;
    FILE *arqSaida;
    //queue<int> fila; //CRIA A FILA, PARA ENVIAR A FILA É SÓ O NOME.

   int vetInfo[10000]; //vetor com os dados do arquivo 

    

    nomeUm = argv[1];
    nomeDois = argv[2];

    printf("nome do arquivo: %s\n", nomeUm);
    arq = fopen(nomeUm, "rt");
    //arqSaida = fopen(nomeDois, "wt");
    
    if(arq == NULL){
        printf("PROBLEMA PARA ABRIR O ARQUIVO!\n");
        return 0;
    }

    int j=0;
    int i = 1;
    
    while (!feof(arq))
    { 
       fscanf(arq,"%d",&vetInfo[j]); //Le o arquivo e adiciona para o vetor já tranformado para int
       j++;
    }
    for(int i =0; i < j;i++){
        printf("posição[%d] = %d\n",i,vetInfo[i]);
    }
    //0BS: chamar o alg
    //espancao(vetInfo);
    
    //implementar a impressão no arquivo de saida RESULTADO

     fclose(arq);
     //fclose(arqSaida);
}
