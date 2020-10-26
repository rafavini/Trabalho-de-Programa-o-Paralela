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

/*void linhas_e_col(int mat[][], int a, int b, int pos_l, int pos_c){
    for(int i=pos_l;i<a;i++){//preebche as linhas e colunas que possuem obstaculo com -1
        for(int j=pos_c;j<b;j++){
            mat[i][j]=-1;
        }
    }
}
*/

/*void expansao(int *info){
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
*/

int main(int argc, char *argv[]){
    FILE *arq;
    char *nomeUm; //arquivo entrada
    char *nomeDois; //arquivo saida
    char Linha[100];
    char *result;
    FILE *arqSaida;
    int aux2=0;
    queue<int> fila; //CRIA A FILA, PARA ENVIAR A FILA É SÓ O NOME.

   int vetInfo[100]; //vetor com os dados do arquivo
   

    

    nomeUm = argv[1];
    nomeDois = argv[2];

    printf("nome do arquivo: %s\n", nomeUm);
    arq = fopen(nomeUm, "rt");
    //arqSaida = fopen(nomeDois, "wt");
    
    if(arq == NULL){
        printf("PROBLEMA PARA ABRIR O ARQUIVO!\n");
        return 0;
    }
    
    
    while (!feof(arq))
    { 
       fscanf(arq,"%d",&vetInfo[aux2]); //Le o arquivo e adiciona para o vetor já tranformado para int
       aux2++;
    }

    int grid[vetInfo[0]][vetInfo[1]]; // criar o grid com o tamanho de pos 0 e pos 1 no vetor;


    //ZERANDO MATRIZ 
     for(int t=0; t < vetInfo[0];t++){
        for(int v =0; v < vetInfo[1];v++){
            grid[t][v] = 0;
        }
    }
    
    
    int obstaculo = vetInfo[6];//pega a quantidade de obstaculo do vetor;
    int aux=0,aux1;
    int i,j,lin,col,pos_i,pos_j,pos_lin,pos_col;
    int count=0;
    i = vetInfo[7]; // GUARDA O VALOR DO VETOR
    pos_i = 7; //GUARDA O NUMERO DA POSIÇÃO DO VETOR 
    j = vetInfo[8];
    pos_j = 8;
    lin = vetInfo[9];
    pos_lin = 9;
    col = vetInfo[10];
    pos_col = 10;
    

    while(aux < obstaculo){
        grid[i][j] = -1; //INICIA O I,J DO PRIMEIRO OBSTACULO COM -1


        //VERIFICA SE O OBSTACULO TEM QUE ANDAR NA LINHA
        if(lin != 1){
            aux1 = i;
            for(count  = 0; count < lin;count++){
                //FIXA A COLUNA E ANDA NA LINHA
                grid[aux1][j] = -1;
                aux1++;
            }
        }
    
    
    aux1=0;

        //VERIFICA SE O OBSTACULO TEM QUE ANDAR NA COLUNA
        if(col != 1){
            aux1 = j;
            for(count = 0; count < col;count++){
                //FIXA A LINHA E ANDA NA COLUNA
                grid[i][aux1] = -1;
                aux1++;
            }
        }


        aux1=0;
        aux++;

        //ATUALIZANDO OS INDICES 
        pos_i = pos_i + 4;
        pos_j = pos_j + 4;
        pos_lin = pos_lin + 4;
        pos_col = pos_col +4;
        i = vetInfo[pos_i];
        j = vetInfo[pos_j];
        lin = vetInfo[pos_lin];
        col = vetInfo[pos_col];
     
    }
    printf("\n");
   for(int t=0; t < vetInfo[0];t++){
        for(int v =0; v < vetInfo[1];v++){
            printf("%d \t",grid[t][v]);
        }
        printf("\n");
    }
    

    //0BS: chamar o alg
    //espancao(vetInfo);
    //implementar a impressão no arquivo de saida RESULTADO

     fclose(arq);
     //fclose(arqSaida);
}
