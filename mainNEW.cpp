#include <stdio.h>
#include <iostream>
#include <queue>
#include <stack>
#include <omp.h>
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


int main(int argc, char *argv[]){

    double tini, tfin, texec;
    tini = omp_get_wtime(); // Na 1a. região sequencial do programa 
    FILE *arq;
    char *nomeUm; //arquivo entrada
    char *nomeDois; //arquivo saida
    FILE *arqSaida;
    int aux2=0;
    queue<int> fila; //CRIA A FILA, PARA ENVIAR A FILA É SÓ O NOME.
    bool achou = false;
    
   int vetInfo[10000]; //vetor com os dados do arquivo

    nomeUm = argv[1];
    nomeDois = argv[2];

    printf("nome do arquivo: %s\n", nomeUm);
    arq = fopen(nomeUm, "rt");
    arqSaida = fopen(nomeDois, "wt");
    
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
   //EXPANSÃO

   int minimo=0;
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
   s.distancia=1; 
   //COLOCANDO ELA NA PILHA
   q.push(s);
 

   while(!q.empty() && achou == false){
       novo curr = q.front();//PEGANDO O INDICE I E J DA ORIGEM E DAS POSIÇÕES ADJACENTES
       celula pt = curr.cel; //COLOCA ESSE INDICE EM PT PARA FAZER VERIFICAÇÃO
        
        q.pop();//TIRA ELE DA FILA POR CAUSA QUE JÁ VISITO
        //LAÇO PARA CRIAR OS ADJACENTES
        for(int u = 0; u < 4; u++){
            int linha = pt.i + l[u];
            int coluna = pt.j + c[u];

            if(linha == destino.i && coluna == destino.j){
            achou = true;
            minimo = curr.distancia;
        }
            if(grid[linha][coluna] == INT_MAX  ){
                grid[linha][coluna] = curr.distancia ;//MARCA NO GRID AS EXPANSÃO
                novo adjacente = {{linha,coluna}, curr.distancia + 1};//CRIA O ADJACENTE COM AScler POSIÇÕES CORRETAS
                q.push(adjacente);//COLOCA ELE NA FILA 
            }
        }
   }
  
   //BACKTRACKING
 
     novo t = {destino};
    queue<novo> u;
    queue<celula> caminho;
    int menor,menor1;//VARIAVEIS PARA COMPARAÇÃO PARA SABER QUEM DEVE IR PARA FILA
   

    u.push(t);
   if(achou){
       while(destino.i != origem.i || destino.j != origem.j){
            novo curr = u.front();
            celula pt = curr.cel;

            menor1= grid[pt.i][pt.j];


            
            if(menor1 < menor){
                caminho.push(pt);
            }
             
            
            //COLOCA NA FILA OS INDICE I E J 
            //VERIFICA SE CHEGOU NA ORIGEM
           
             u.pop();

           for(int v = 0; v < 4; v++){
                int linha = pt.i + l[v];
                int coluna = pt.j + c[v]; 

                if(pt.i == origem.i && pt.j == origem.j){
                destino.i = origem.i;
                destino.j = origem.j;
            }      
                //VERIFICA SE O ADJACENTE O VALOR É MENOR QUE O ANTERIOR NO GRID E SE NÃO É UM OBSTACULO
                if(grid[linha][coluna] < grid[pt.i][pt.j] && grid[linha][coluna] != -1  ){
                    menor = grid[pt.i][pt.j];
                    
                    novo adjacente = {{linha,coluna}};
                    u.push(adjacente);
                    
                }
                
           }
       }
   }
    FILE *arqtest;
    arqtest = fopen("grid.txt", "wt");

    //IMPRESSÃO DO GRID EM ARQUIVO DEBUG    
   for(int a=0;a<vetInfo[0];a++){
       for(int b=0;b<vetInfo[1];b++){
           fprintf(arqtest, "%d \n\t", grid[a][b]); 
       }
   }

    //INVERTE FILA
   stack<celula> Stack; 
    while (!caminho.empty()) { 
        Stack.push(caminho.front()); 
        caminho.pop(); 
    } 
    while (!Stack.empty()) { 
        caminho.push(Stack.top()); 
        Stack.pop(); 
    }

   //IMPRIMIR O TAMANHO DO CAMINHO MINIMO 
   fprintf(arqSaida,"%d\n",minimo);

    //IMPRIME A FILA COM OS INDICE ATÉ A ORIGEM NO MENOR CAMINHO 
    while(!caminho.empty()){
        celula pos = caminho.front();
        fprintf(arqSaida,"%d %d \n",pos.i,pos.j);
        
        caminho.pop();
    }

    fprintf(arqSaida, "%d %d", vetInfo[4], vetInfo[5]);
    tfin = omp_get_wtime(); // Na ultima região sequencial do programa
	texec = tfin - tini;
	printf("Tempo de execução: %f\n", texec);
    

     fclose(arq);
     fclose(arqSaida);
     fclose(arqtest);
}
