#include <stdio.h>

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

    int g=0;
    while(vetInfo[g] != '\0'){
        printf("\n%c iteracao = %d\n", vetInfo[g], g); //imprime os dados retirados do arquivo
        g++;
    }
    
    //0BS: chamar o alg
    

    //implementar a impressão no arquivo de saida RESULTADO

     fclose(arq);
     //fclose(arqSaida);
}
