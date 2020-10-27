#include <stdio.h>
#include <iostream>
#include <queue>
#define MAX 1000
#define INT_MAX 2147483647

using namespace std;

//funçao que imprime a fila.
//METODOS FILA.SIZE, FILA.PUSH, FILA.POP, FILA.FRONT, FILA.BACK
void imprime_fila(queue<int> fila){
    while(!fila.empty()){
        printf("%d",fila.front());
        fila.pop();
    }
}


int main(int argc, char *argv[]){
    FILE *arq;
    char *nomeUm; //arquivo entrada
    char *nomeDois; //arquivo saida
    char Linha[100];
    char *result;
    FILE *arqSaida;
    int aux2=0;
    queue<int> fila; //CRIA A FILA, PARA ENVIAR A FILA É SÓ O NOME.
    bool achou = false;
    

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
    grid[vetInfo[2]][vetInfo[3]] = 0; //COLOCANDO 0 NA ORIGEM

    //COLOCANDO O MAXIMO INTEIRO POSSIVEL NA MATRIZ 
     for(int t=0; t < vetInfo[0];t++){
        for(int v =0; v < vetInfo[1];v++){
            grid[t][v] = INT_MAX;
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

    
    


    // COLOCANDO OS OBSTACULOS NA MATRIZ
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
    //IMPRIMINDO A MATRIZ
    printf("\n");
   /*for(int t=0; t < vetInfo[0];t++){
        for(int v =0; v < vetInfo[1];v++){
            printf("%d \t",grid[t][v]);
        }
        printf("\n");
    }
    */

    
    

    //0BS: chamar o alg
    printf("teste\n");
   fila.push(vetInfo[2]);
   fila.push(vetInfo[3]);
    imprime_fila(fila);

    
    //implementar a impressão no arquivo de saida RESULTADO

     fclose(arq);
     //fclose(arqSaida);
}
