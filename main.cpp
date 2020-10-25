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

    while(info[i] != '\0'){
        if(info[i] == ' '){
            i++;
        }
        printf("TESTE VET: %c\n", info[i]);
        i++;
    }
}


int main(int argc, char *argv[]){
    FILE *arq;
    char *nomeUm; //arquivo entrada
    char *nomeDois; //arquivo saida
    char Linha[100];
    char *result;
    FILE *arqSaida;
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
