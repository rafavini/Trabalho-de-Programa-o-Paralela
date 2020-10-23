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

#include <stdio.h>

int main(int argc, char *argv[]){
    FILE *arq;
    char *nomeUm; //arquivo entrada
    char *nomeDois; //arquivo saida
    char Linha[100];
    char *result;
    FILE *arqSaida;
    queue<int> fila; //CRIA A FILA, PARA ENVIAR A FILA É SÓ O NOME.
    

    nomeUm = argv[1];
    nomeDois = argv[2];

    printf("nome do arquivo: %s\n", nomeUm);
    arq = fopen(nomeUm, "rt");
    //arqSaida = fopen(nomeDois, "wt");
    
    if(arq == NULL){
        printf("PROBLEMA\n");
        return 0;
    }

    int i = 1;
    while (!feof(arq))
    {
	    // Lê uma linha (inclusive com o '\n')
        result = fgets(Linha, 100, arq);  // o 'fgets' lê até 99 caracteres ou até o '\n'
        if (result)  // Se foi possível ler
	    printf("Linha %d : %s\n",i,Linha);
        i++;
    }

    //chamar o alg


    //implementar a impressão no arquivo de saida RESULTADO
       
	
	
   
   
	

     fclose(arq);
     //fclose(arqSaida);
}



 

 
