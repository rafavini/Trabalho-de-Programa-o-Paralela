#include <stdio.h>
#include <iostream>
#include <queue>
#define MAX 1000

using namespace std;

//funçao que imprime a fila.
//METODOS FILA.SIZE, FILA.PUSH, FILA.POP, FILA.FRONT, FILA.BACK
void imprime_fila(queue<int> fila){
    for(int i = fila.front(); i < fila.size();i++){
        printf("%d",i);
    }
}

void linhas_e_col(int mat[][MAX], int a, int b, int pos_l, int pos_c){
    for(int i=pos_l;i<a;i++){//preebche as linhas e colunas que possuem obstaculo com -1
        for(int j=pos_c;j<b;j++){
            mat[i][j]=-1;
        }
    }
}

void expansao(char *info){
    int a=7;
    int obstaculo = info[6]; //ARMAZENA QUANTIDADE DE OBSTACULOS info[6] 
    bool achou = false;
    queue<int> fila; //CRIA A FILA, PARA ENVIAR A FILA É SÓ O NOME.
    int grid[info[0]][info[1]]; //info[0] representa o n de linhas e info[1] representa o n de colunas

    int aux = 0;
    //inicializar as celulas do grid que possuem obstaculo com -1 
    while(aux < obstaculo){//executa enquanto for menos que a quantidade de obstaculos

        grid[info[a]][info[a+1]] = -1; //pega o indice do inicio do primeiro obstaculo e inicializa com -1
        a++;
        linhas_e_col(grid, info[a+1], info[a+2], a-1, a);//chama a funcao para preencher o numero de linhas e colunas com obstaculo a partir do indice de origem
        a=a+3;//pega proxima posicao com informacoes de outro obstaculo

        aux++;
        
    }

    grid[info[2]][info[3]] = 0; //inicializa o indice da origem com 0

    //INICIALIZAR POSICOES DIFERENTE DE O E -1 COM INFINITO

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
    //expansao(vetInfo);
    
    //implementar a impressão no arquivo de saida RESULTADO

     fclose(arq);
     //fclose(arqSaida);
}
