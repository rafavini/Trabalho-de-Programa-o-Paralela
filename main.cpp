#include <stdio.h>
#include <iostream>
#include <queue>
#define MAX 1000
#define INT_MAX 2147483647

using namespace std;

struct celula{
    int i;
    int j;
};

struct novo{
    celula cel;
    int distancia;
};

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
    //char Linha[100];
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
     

    //COLOCANDO O MAXIMO INTEIRO POSSIVEL NA MATRIZ 
     for(int t=0; t < vetInfo[0];t++){
        for(int v =0; v < vetInfo[1];v++){
            grid[t][v] = INT_MAX;
        }
    }
    grid[vetInfo[2]][vetInfo[3]] = 0;//COLOCANDO 0 NA ORIGEM
    
    
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

   //EXPANSÃO

   int teste=0;
   celula origem,destino;//CRIANDO ORIGEM E DESTINO COM CAMPOS I E J
   //VETORES PARA CORRER NAS DIREÇÕES
   int l[] = {-1,0,0,1}; 
   int c[] = {0,-1,1,0};
   queue<novo> q; // CRIANDO UMA FILA ONDE CADA POSIÇÃO TEM I E J
   //CARREGANDO OS CAMPO I,J DA ORIGEM E DESTINO
   origem.i = vetInfo[2];
   origem.j = vetInfo[3];
   destino.i = vetInfo[4];
   destino.j = vetInfo[5]; 
   //CARREGANDO O CAMPO CEL DA STRUCT NOVO COM OS INDICE I E J DA ORIGEM
   novo s = {origem}; 
   //COLOCANDO ELA NA PILHA
   q.push(s);
 

   while(!q.empty() && achou == false){
       novo curr = q.front();//PEGANDO O INDICE I E J DA ORIGEM E DAS POSIÇÕES ADJACENTES
       celula pt = curr.cel; //COLOCA ESSE INDICE EM PT PARA FAZER VERIFICAÇÃO
        //VERIFICAÇÃO DOS INDICES ATUAIS COM O DESTINO
        if(pt.i == destino.i && pt.j == destino.j){
            achou = true;
            teste = curr.distancia;
        }
        q.pop();//TIRA ELE DA FILA POR CAUSA QUE JÁ VISITO
        //LAÇO PARA CRIAR OS ADJACENTES
        for(int u = 0; u < 4; u++){
            int linha = pt.i + l[u];
            int coluna = pt.j + c[u];

            if(grid[linha][coluna] == INT_MAX){
                grid[linha][coluna] = curr.distancia + 1;//MARCA NO GRID AS EXPANSÃO
                novo adjacente = {{linha,coluna}, curr.distancia + 1};//CRIA O ADJACENTE COM AS POSIÇÕES CORRETAS
                q.push(adjacente);//COLOCA ELE NA FILA 
            }
        }
   }
   //BACKTRACKING
 
     novo t = {destino};
    queue<novo> u;
    queue<celula> caminho;
   

    u.push(t);
   if(achou){
       while(destino.i != origem.i || destino.j != origem.j){
            novo curr = u.front();
            celula pt = curr.cel;
            caminho.push(pt);//COLOCA NA FILA OS INDICE I E J 

            //VERIFICA SE CHEGOU NA ORIGEM
            if(pt.i == origem.i && pt.j == origem.j){
                destino.i = origem.i;
                destino.j = origem.j;
            }
            u.pop();
            printf("ANTES DO FOR %d%d\n",pt.i,pt.j);
           for(int v = 0; v < 4; v++){
                int linha = pt.i + l[v];
                int coluna = pt.j + c[v]; 
                //printf("%d < %d \n",grid[linha][coluna],grid[pt.i][pt.j]);
                //VERIFICA SE O ADJACENTE O VALOR É MENOR QUE O ANTERIOR NO GRID E SE NÃO É UM OBSTACULO
                if(grid[linha][coluna] < grid[pt.i][pt.j] && grid[linha][coluna] != -1){
                    novo adjacente = {{linha,coluna}};
                    u.push(adjacente);
                }
                
           }


       }
   }

    //IMPRIME A FILA COM OS INDICE DO DESTINO ATÉ A ORIGEM NO MENOR CAMINHO
    while(!caminho.empty()){
        celula testa = caminho.front();
        printf("%d %d \n",testa.i,testa.j);
        
        caminho.pop();
    }
     for(int t=0; t < vetInfo[0];t++){
        for(int v =0; v < vetInfo[1];v++){
            printf("%d \t",grid[t][v]);
        }
        printf("\n");
    }

   printf("TESTE ==== %d",teste);
  //0BS: chamar o alg
   
    //implementar a impressão no arquivo de saida RESULTADO

     fclose(arq);
     //fclose(arqSaida);
}
