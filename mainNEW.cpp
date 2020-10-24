#include <stdio.h>

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

   char vetInfo[100]; //vetor com os dados do arquivo

    

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
        char ch;
        ch = fgetc(arq);

        printf("%c", ch);

        if(ch == '\n'){
            i++;
        }

        if(ch != ' '){
            if (ch != '\n')
            {
                vetInfo[j] = ch;
                j++;
            }
        }
    }


    //0BS: chamar o alg
    espancao(vetInfo);
    

    //implementar a impressão no arquivo de saida RESULTADO

     fclose(arq);
     //fclose(arqSaida);
}
