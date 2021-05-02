#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINHA 1000 /*Define o tamanho maximo de linhas no valor de 1000*/

typedef struct no *pme; /*Declarando as variaveis da nossa matriz*/
struct no
{
    char genero; /*Variaveis da nossa lista e um ponteiro para apontar pro proximo elemento da matriz*/
    int col, val;
    pme prox;
};
typedef pme matriz[MAX_LINHA];

/*Funcao que inicializa a nossa matriz*/
void inicializa(matriz m, int l)
{
    int i;
    for(i=0;i<l;i++)
        m[i]=NULL;/*Linha toda gerada, com um espaco vazio*/
}

/*Funcao que insere elementos na nossa matriz*/
void insere(matriz m, int i, int j[], int val, char generoFilme)
{
    pme novo,p;
    novo=(pme)malloc(sizeof(struct no)); /*Aloca espaco na nossa matriz*/
    novo->val=val; /*Atribui os elementos na nossa matriz*/
    novo->col=j;
    novo->genero=generoFilme;
    novo->prox=NULL;
    if(m[i]==NULL) /*Caso a matriz de uma linha esteja vazia, aloca um novo espaco e insere os elementos*/
        m[i]=novo;
    else{ /*Caso tenha uma linha com conteudo, o elemento atual aponta para o proximo e insere os elementos*/
        for(p=m[i];p->prox!=NULL;p=p->prox)
            ;
        p->prox=novo;
    }
}

/*Funcao que imprime os elementos na matriz*/
void imprime(matriz m, int tlin, int tcol)
{
    int i,j;
    pme p;
    for(i=0;i<tlin;i++)
    {
        p=m[i];
        for(j=0;j<tcol;j++)
            if((p!=NULL)&&(p->col==j)) /*Caso a linha nao esteja vazia e seja igual ao da coluna, imprime*/
            {
                printf(" %d ",p->val); /*Imprime o valor existente na posicao*/
                p = p->prox;
            }
            else /*Caso nao tenha nada inserido em uma determinada linha e coluna, mostra 0 nessa posicao*/
                printf(" 0 ");
        printf("\n"); /*Pula a linha*/
    }
    printf("\n\n");
}

/*Funcao que libera o conteudo de toda a matriz*/
void libera(matriz m, int l)
{
    pme p,q; /*Utiliza dois auxiliares para remover o conteudo da matriz*/
    int i;
    for(i=0;i<l;i++) /*Varre todas as linhas da matriz*/
    {
        p=m[i]; /*Declaramos o auxiliar como uma linha da matriz m*/
        while(p!=NULL) /*Enquanto a llinha 'p' nao estiver vazia, ela vai liberando o conteudo*/
        {
            q=p; /*'q' recebe o conteudo de 'p'*/
            p=p->prox; /*'p' aponta para o proximo elemento da sua lista*/
            free(q); /*Libera o conteudo de 'q'*/
        }
    }
}

/*Funcao que vai imprimir a matriz condensada e retornar o genero mais assistido*/
void matrizCond(matriz m, int tlin, int tcol)
{
    int i,j,genero,maior=0; /*Variaveis da funcao*/
    int contGenero[8]={0,0,0,0,0,0,0,0}; /*Vetor de inteiros para contabilizar o genero de cada filme*/
    char* nome[]={"Açao","Romance","Suspense","Comedia","Musical","Drama","Ficcao","Policial"}; /*Nome dos generos*/
    pme p; /*auxiliar 'p' da matriz*/
    for(i=0;i<tlin;i++) /*Vai imprimir o numero do cliente (linha)*/
    {
        printf("Cliente: %d\n",i+1);
        printf(" Filmes assitidos (filme e genero):\n");
        p=m[i]; /*Atribui 'p' que recebe uma linha de informacoes*/
        for(j=0;j<tcol;j++)
        {
            if((p!=NULL)&&(p->col==j))
            {   /*Caso o conteudo nao esteja vazio e seja igual ao da coluna, mostra o numero da coluna e o genero*/
                printf("  %d  %c\n",(p->col)+1,p->genero);
                if(p->genero=='A')
                {   /*Verifica se a letra na lista eh igual ao que esta comparando, se for, incrementa o valor*/
                    contGenero[0]++;
                }
                else if(p->genero=='R')
                {
                    contGenero[1]++;
                }
                else if(p->genero=='S')
                {
                    contGenero[2]++;
                }
                else if(p->genero=='C')
                {
                    contGenero[3]++;
                }
                else if(p->genero=='M')
                {
                    contGenero[4]++;
                }
                else if(p->genero=='D')
                {
                    contGenero[5]++;
                }
                else if(p->genero=='F')
                {
                    contGenero[6]++;
                }
                else if(p->genero=='P')
                {
                    contGenero[7]++;
                }
                p=p->prox; /*Verifica o proximo elemento da lista dessa linha*/
            }
        }
        printf("\n"); /*Pula a linha, verificando o proximo cliente*/
    }
    for(i=0;i<8;i++) /*Verifica o vetor 'contGenero' para ver qual que foi mais assistido*/
    {
        if(contGenero[i]>maior)
        {
            genero=i; /*A variavel armazena o valor de posicao do 'i'*/
            maior=contGenero[i]; /*'maior recebe o valor dentro de vetor, na posicao 'i'*/
        }
    }
    for(i=0;i<8;i++) /*Utiliza outro 'for', mas agora para verificar se o 'i' vai ser igual ao valor*/
    {
        if(i==genero) /*Se 'i' for igual ao valor de 'genero', imprime o nome do genero, contido na posicao 'i' do vetor 'nome'*/
        {
            printf("O genero de filme mais assistido foi: %s\n",nome[i]);
        }
    }
}

/*Funcao que vai ler a letra do genero, retornando 1 (caso seja alguma letra correta) ou 0 (caso contrario)*/
int lerGenero(char genero)
{
    if(genero=='A'||genero=='R'||genero=='S'||genero=='C'||genero=='M'||genero=='D'||genero=='F'||genero=='P')
    {   /*Se for digitado alguma dessas letras, retorna 1*/
        return 1;
    }
    else
    {   /*Senao, retorna 0*/
        return 0;
    }
}

/*Funcao que vai verificar se algum filme ja foi inserido anteriormente pelo cliente*/
int lerFilme(matriz m,int numeroFilme, int linha)
{
    pme p;
    int repete=0; /*Variavel que mostra a quantidade de vezes que um filme igual ao digitado possui na lista do cliente*/
    for(p=m[linha];p!=NULL;p=p->prox) /*Varre toda a lista de filmes do cliente ateh o momento*/
    {
        if((numeroFilme)==p->col+1) /*Caso o numero do filme digitado seja igual ao que esta na lista, incrementa a variavel*/
        {
            repete++;
        }
    }
    if(repete>0) /*Caso a variavel tenha um valor maior que 0, retorna 1*/
    {
        return 1;
    }
    else /*Caso contrario, retorna 0*/
    {
        return 0;
    }
}

/*Area principal do programa*/
int main (void)
{
    matriz m; /*Declaramos um variavel matriz de 'm'*/
    int F,C,i,j,assistiu,numfilme; /*Declaramos as variaveis (F-filmes;C-cliente;i-linha;j-coluna*/
    int aux=0,aux2=0; /*Variaveis auxiliares que vao guardar os valores da funcao 'lerGenero' e 'lerFilme'*/
    char genero; /*Vai armazenar a letra*/
    printf("Digite a quantidade de filmes disponiveis no catalogo: ");
    scanf("%d",&F);
    printf("Digite a quantidade de clientes do servico: ");
    scanf("%d",&C);

    inicializa(m,C); /*Inicia a nossa matriz com a quantidade de linhas indicadas por 'C'*/
    for(i=0;i<C;i++)
    {
        printf("\nQuantos filmes o cliente %d ja assitiu? ",i+1);
        scanf("%d",&assistiu);
        for(j=0;j<assistiu;j++)/*Sera utilizado um laco de repeticao para ler todos os filmes*/
        {
            do
            {
                printf("Digite o numero do %do. filme assistido: ",j+1);
                scanf("%d",&numfilme);
                if(j>0) /*Se tiver algum filme inserido, char a funcao que vai verificar se repetiu o filme*/
                {
                    aux2=lerFilme(m,numfilme,i); /*'aux2' recebe o valor da funcao 'lerFilme'*/
                    if(aux2==1) /*Se ele for 1, significa que o nº digitado for repetido, pede para inserir outro*/
                    {
                        printf("Filme ja inserido\n Insira outro filme!\n");
                    }
                }
                if((numfilme<=0)||(numfilme>F))
                {
                    printf("FILME INVALIDO!!!\n Insira o valor correto\n");
                }
            } /*Enquanto o nº do filme digitado for menor que 0, maior que F ou tenha repetido o nº do filme, nao sai do laco*/
            while((numfilme<=0)||(numfilme>F)||(aux2==1));

            do
            {
                printf("Digite o genero do filme: ");
                scanf(" %c",&genero);
                aux=lerGenero(genero); /*Recebe o valor da funcao lerGenero*/
                if(aux==0)
                {
                    printf("\nGenero Invalido!!\n");
                }
            }/*Enquanto esse valor for 0, nao vai sair do laco*/
            while(aux==0);

            insere(m,i,numfilme-1,1,genero);/*Insere o valor na respectiva linha da nossa matriz*/
        }
    }
    printf("\nMatriz inteira:\n");
    imprime(m,C,F); /*Chama a funcao que vai imprimir o grafico da nossa matriz*/

    printf("\nMatriz condensada:\n");
    matrizCond(m,C,F); /*Chama a funcao que vai imprimir a matriz condensada, alem de mostrar o genero mais assistido*/

    libera(m,C); /*Libera todos os conteudos da nossa matriz, de todas as linhas*/

    return 0;
}
