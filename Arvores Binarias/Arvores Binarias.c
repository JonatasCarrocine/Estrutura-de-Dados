#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct arv /*Estrutura da nossa arvore binaria*/
{
    char info; /*letra do nosso no na arvore*/
    struct arv* esq; /*Aponta para a esquerda desse no na arvore*/
    struct arv* dir; /*Aponta para a direita desse no na arvore*/
} TArv;
typedef TArv *PArv;

/*Funcao que iremos criar a nossa arvore a partir de um no*/
PArv cria(char c,PArv sae, PArv sad)
{
    PArv p=(PArv)malloc(sizeof(TArv)); /*Aloca espaco para esse no*/
    p->info=c; /*Grava a letra 'c' do no*/
    p->esq=sae; /*Apontamos para a posicao da esquerda outro no*/
    p->dir=sad; /*Apontamos para a posicao da direita outro no*/
    return p;
}

/*Funcao que vai retornar os nos a direita, sendo considerados filhos ou irmaos*/
void imprimeDireita(PArv a)
{
    if(a!=NULL) /*Caso possua alguma informacao na posicao de 'a'*/
    {
        printf(" %c ",a->info); /*Imprime a sua letra*/
        imprimeDireita(a->dir); /*Chama a funcao, mas agora na sua posicao a direita*/
    }
}

/*Funcao que vai procurar os filhos de um determinado no*/
void procuraFilhos(char c, PArv a)
{
    if(a!=NULL) /*Caso possua alguma informacao na posicao de 'a'*/
    {
        if((c==a->info)&&(a->esq==NULL)) /*Caso o no encontrado nao tenha informacao a sua esquerda, nao tem filhos*/
        {
            printf("O no (%c) nao possui filhos!!",c);
        }
        else if(c==a->info) /*Se o no digitado for igual ao que esta localizado agora, e ter conteudo a esquerda*/
        {
            printf("Os filhos do no (%c) sao: ",c);
            imprimeDireita(a->esq); /*Chama a funcao que imprime os nos a direita, pois todos serao filhos*/
        }
        procuraFilhos(c,a->esq); /*Se nao for, ele vai para o no da esquerda, fazer a mesma verificacao*/
        procuraFilhos(c,a->dir); /*E por ultimo, ele vai para o no da direita, fazendo a mesma verificacao*/
    }
}

/*Funcao que vai procurar os irmaos de um determinado no*/
void procuraIrmaos(char c, PArv a)
{
    int valor; /*Utiliza uma variavel para recebe o valor da funcao 'searchIrmaos'*/
    if(a!=NULL) /*Caso possua alguma informacao na posicao de 'a'*/
    {
        if((c==a->info)&&(a->dir==NULL)) /*Caso o no encontrado nao tenha informacao a sua direita, nao tem irmaos*/
        {
            printf("O no (%c) nao possui irmaos a direita!!",c);
        }
        else if(c==a->info) /*Caso tenha, mostra os irmaos a sua direita*/
        {
            printf("Os irmaos a partir do no (%c) sao:",c);
            imprimeDireita(a->dir); /*Chama a funcao que vai retorna os irmaos conectados a direita dele*/
        }
        procuraIrmaos(c,a->esq); /*Se nao for, ele vai para o no da esquerda, fazer a mesma verificacao*/
        procuraIrmaos(c,a->dir); /*E por ultimo, ele vai para o no da direita, fazendo a mesma verificacao*/
    }
}

/*Funcao que vai imprimir em pre-ordem a nossa arvore*/
void imprimePre (PArv a)
{
    if(a!=NULL) /*Caso possua alguma informacao na posicao de 'a'*/
    {
        printf("%c ",a->info); /*Imprime a sua letra*/
        imprimePre(a->esq); /*Chama a funcao, mas agora na sua posicao a esquerda*/
        imprimePre(a->dir); /*Chama a funcao, mas agora na sua posicao a direita*/
    }
    /*Se nao tiver nenhuma informacao, ele volta para o seu no antecendente*/
}

/*Funcao que vai imprimir na ordem infixa a nossa arvore*/
void imprimeIn(PArv a)
{
    if(a!=NULL) /*Caso possua alguma informacao na posicao de 'a'*/
    {
        imprimeIn(a->esq); /*Chama a funcao, mas agora na sua posicao a esquerda*/
        printf("%c ",a->info); /*Imprime a sua letra*/
        imprimeIn(a->dir); /*Chama a funcao, mas agora na sua posicao a direita*/
    }
    /*Se nao tiver nenhuma informacao, ele volta para o seu no antecendente*/
}

/*Funcao que vai liberar os espacos alocados da nossa arvore*/
PArv libera (PArv a)
{
    if(a!=NULL) /*Caso possua alguma informacao na posicao de 'a'*/
    {
        libera(a->esq); /*Libera o seu descendente a esquerda*/
        libera(a->dir); /*Libera o seu descendente a direita*/
        free(a); /*Depois de liberar os seu descendentes, libera ele mesmo*/
    }
    return NULL;
}

/*Funcao que vai inserir os nos na nossa arvore*/
void insereArvore(char c[22], PArv a,int tam)
{
    int i=6;
    while(i<tam)/*Sera inserido os nos enquanto o 'i' nao tiver o mesmo tamanho que a quantidade de caracteres da linha*/
    {
        a->dir=cria(c[i],NULL,NULL);/*A direita do no cria um novo, na posicao 'i'*/
        a=a->dir; /*Esse mesmo no vai para a direita*/
        i=i+2; /*Incrementa o valor de 'i' duas vezes (consideramos que o prox possui um espaco, sem caractere)*/
    }
}

/*Funcao que vai verificar onde pode inserir os proximos nos*/
void verifica(PArv a,char c[22],int tam)
{
    if(a!=NULL) /*Caso possua alguma informacao na posicao de 'a'*/
    {
        if(c[0]==a->info) /*Verfica se o primeiro caractere (o atual da linha) eh igual ao do no 'a' localizado no momento*/
        {
            a->esq=cria(c[4],NULL,NULL); /*Se for, insere o filho na posicao a esquerda*/
            if(tam>=4) /*Caso ele tenha mais outro filho*/
            {
                insereArvore(c,a->esq,tam);
                /*Chama a funcao que vai inserir os nos para a direita, representando os irmaos do no que acabou de criar*/
            }
        } /*Caso nao tenha informacao, chama novamente a funcao abaixo*/
        verifica(a->esq,c,tam); /*Chama a funcao, verificando o no da esquerda (o filho do no anterior)*/
        verifica(a->dir,c,tam); /*Por ultimo chama a mesma funcao pelo no da direita (o irmao do no anterior)*/
    }
}

/*Area principal do programa*/
int main (void)
{
    FILE *pont_arq; /*Variavel que vai pegar o arquivo contendo o texto da arvore*/
    int opcao; /*Variavel utilizada para o menu de interacao*/
    char linha[100]; /*Quantidade de linhas para ler no nosso arquivo texto*/
    char str[22]; /*Tamanho da nossa string de cada linha*/
    int d,x,nfilhos; /*'d' verifica a qtd de filhos no texto e 'x' na funcao de verificar*/

    PArv a=cria(NULL,NULL,NULL); /*Inicializamos a nossa arvore 'a'*/
    pont_arq=fopen("arv.txt","r"); /*Abre o arquivo para a leitura da informacoes*/

    if(pont_arq==NULL) /*Caso nao seja possivel, mostra a mensagem de erro e sai*/
    {
        printf("Erro na abertura do arquivo!");
        exit(1);
    }
    while(fgets(linha,sizeof(linha),pont_arq))/*Sera verificado linha por linha inserida no nosso arquivo*/
    {
        x=strlen(linha); /*Armazena o tamanho da nossa linha de caracteres*/
        nfilhos=linha[2]-'0'; /*'nfilhos' recebe o caractere que sempre estah na terceira posicao do vetor 'str'*/
        if(nfilhos==0) /*Caso o numero de filhos seja 0*/
        {
            if(a->info==NULL) /*Se a arvore estiver vazia, cria esse no*/
            {
                a=cria(linha[0],NULL,NULL);
            }
        }
        else if(nfilhos==1) /*Caso o numero de filhos seja 1*/
        {
            if(a->info==NULL) /*Se a arvore estiver vazia, cria esse no com o filho*/
            {
                a=cria(linha[0],
                       cria(linha[4],NULL,NULL),NULL);
            }
            else /*Caso ja possua algum conteudo inserido na arvore*/
            {
                verifica(a,linha,x); /*Chama a funcao que ira verificar o caractere em todos os nos, para inserir*/
            }
        }
        else if(nfilhos==2) /*Caso o numero de filhos seja 2*/
        {
            if(a->info==NULL) /*Se a arvore estiver vazia, cria esse no com os filhos*/
            {
                a=cria(linha[0],
                       cria(linha[4],NULL,
                            cria(linha[6],NULL,NULL)),NULL);
            }
            else /*Caso ja possua algum conteudo inserido na arvore*/
            {
                verifica(a,linha,x); /*Chama a funcao que ira verificar o caractere em todos os nos, para inserir*/
            }
        }
        else
        {
            /*Caso o numero de filhos seja 3 ou mais*/
            if(a->info==NULL) /*Caso a arvore esteja vazia, significa que vai criar o primeiro no nela*/
            {
                a=cria(linha[0],
                       cria(linha[4],NULL,NULL),NULL);

                insereArvore(linha,a->esq,x); /*Chama a funcao que vai inserir o resto dos nos na arvore*/
            }
            else /*Caso ja possua algum conteudo inserido na arvore*/
            {
                verifica(a,linha,x); /*Chama a funcao que ira verificar o caractere em todos os nos, para inserir*/
            }
        }
    }
    char no; /*Variavel utilizada para guardar o caractere de um no, para pesquisa*/
    do /*Menu de interacao*/
    {
        printf("\n-------MENU DE INTERACAO DA NOSSA ARVORE-------\n");
        printf("Digite: \n");
        printf("1) Para imprimir a arvore resultante em pre-ordem\n");
        printf("2) Para imprimir a arvore resultante em ordem infixa\n");
        printf("3) Para imprimir os filhos de um determinado no\n");
        printf("4) Para imprimir os irmaos de um determinado no\n");
        printf("5) Para sair do programa\n");
        printf("-----------------------------------------------\n");
        scanf("%d",&opcao);
        if(opcao==1) /*Se digitar 1, mostra a arvore em pre-ordem*/
        {
            printf("A arvore em pre-ordem eh: \n");
            imprimePre(a); /*Funcao que imprime a arvore em pre-ordem*/
        }
        else if(opcao==2) /*Se digitar 2, mostra a arvore na ordem infixa*/
        {
            printf("A arvore em ordem infixa eh: \n");
            imprimeIn(a); /*Funcao que imprime a arvore infixa*/
        }
        else if(opcao==3) /*Se digitar 3, mostra os filhos de um determinado no a ser digitado*/
        {
            printf("Digite o no desejado para mostrar os filhos: ");
            scanf(" %c",&no); /*Armazena a letra em 'no'*/
            procuraFilhos(no,a); /*Chama a funcao que vai procurar os filhos deste no*/
        }
        else if(opcao==4) /*Se digitar 4, mostra os irmaos de um determinado no a ser digitado*/
        {
            printf("Digite o no desejado para mostrar os seus irmaos: ");
            scanf(" %c",&no); /*Armazena a letra em 'no'*/
            procuraIrmaos(no,a); /*Chama a funcao que vai procurar os irmaos deste no*/
        }
        else if(opcao==5) /*Se digitar 5, encerra o programa e libera todo o conteudo da arvore*/
        {
            printf("PROGRAMA ENCERRADO!!");
            libera(a);
        }
        else /*Se digitar qualquer outro valor, mostra mensagem de erro*/
        {
            printf("OPCAO INVALIDA!!!\n");
        }
        printf("\n");
    }
    while(opcao!=5);

    fclose(pont_arq); /*Fecha o arquivo texto*/

    return 0; /*Retorna 0*/
}
