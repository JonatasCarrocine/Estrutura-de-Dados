#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_PALAVRA 50
/*Tamanho maximo da palavra definida: 50*/

typedef struct
{
    char letra;
    struct TLista *prox;
    struct TLista *ant;
}TLista; /*Struct da nossa lista duplamente encadeada*/

/*Funcao que cria um espaco para armazenar os valores da struct em um bloco da lista*/
TLista *Novo(char letra,TLista *ant)
{
    TLista *Elemento=(TLista*)malloc(sizeof(TLista)); /*Aloca espaco para armazenar o valor*/
    if(Elemento==NULL) /*Caso seja nulo, significa que nao foi possivel alocar o espaco*/
    {
        printf("Nao foi possivel alocar memoria!");
        exit(0);
    }
    /*Declarando os valores iniciais para o primeiro elemento da nossa lista*/
    Elemento->prox=NULL; /*Como ele nao possui um elemento seguinte a ele, declaramos 'prox' como nulo*/
    Elemento->ant=ant; /*'Ant' aponta para ele mesmo, por ser o primeiro elemento da nossa lista*/
    Elemento->letra=letra; /*Armazena a primeira letra da nossa palavra*/
    return Elemento;
}

/*Funcao que insere um elemento na nossa lista, feito de forma recursiva*/
void Insere(TLista *Lista, char letra)
{
    TLista *aux=Lista;

    /*Enquanto ele nao chega ateh o ultimo elemento da lista, ele percorre a lista*/
    while(aux->prox!=NULL)
        aux=aux->prox;

    aux->prox=Novo(letra, aux);
    /*Depois de chegar no ultimo, chama a funcao que ira criar mais um espaco na lista*/
}

/*Funcao que imprime toda a nossa lista*/
void imprime(TLista *Lista,int numero)
{
    if(Lista==NULL) /*Caso a lista esteja vazia, mostra mensagem e sai do programa*/
    {
        printf("Nao foi possivel imprimir a lista!!");
        exit(0);
    }
    /*Mostra as informacoes armazenadas na nossa lista*/
    printf("%c ",Lista->letra);

    /*Enqaunto ela nao chega no final, ela vai percorrendo ate chegar no fim da lista, imprimindo as informacoes*/
    if(Lista->prox!=NULL)
    {
        imprime(Lista->prox, numero+1);
    }
}

/*Funcao que ira trocar os caracteres da nossa lista*/
void trocaLetras(TLista *Lista, char letra1, char letra2)
{
    TLista *v1=NULL, *v2=NULL; /*Teremos dois ponteiros auxiliares para trocar os elementos de posicao*/
    TLista *p; /*Usamos um ponteiro p para varrer a lista*/

    int achou1=0, achou2=0;

    for(p=Lista;p!=NULL;p=p->prox)/*A lista toda sera verificada*/
    {
        if(p->letra==letra1)
        {   /*Caso o conteudo de p apontado seja igual a primeira letra inserida para trocar, encontrou ela*/
            achou1++;
            if(achou1==1)
            /*Se for a primeira letra igual a encotrada na lista, armazena esse elemento em um ponteiro auxiliar v1*/
            {
                v1=p;
            }
        }
        else if(p->letra==letra2)
        {   /*Caso o conteudo de p apontado seja igual a segunda letra inserida para trocar, encontrou ela*/
            achou2++;
            /*Se for a primeira letra igual a encotrada na lista, armazena esse elemento em um ponteiro auxiliar v1*/
            if(achou2==1)
            {
                v2=p;
            }
        }
        /*Termina a verificacao da lista se achar ambas as letras, sendo desnecessario verificar o resto dela*/
        if(achou1>=1 && achou2>=1)
            break;
    }
    /*Caso alguma dessas letras nao tenham sido encontradas na lista, nao sera possivel realizar a troca,
    e o programa fecha*/
    if(achou1==0||achou2==0)
    {
        printf("Nao sera possivel realizar a troca!!!");
        exit(0);
    }

    /*Ponteiro auxiliar que sera utilizado para trocar as letras de posicao dentro da lista,
    sem a necessidade de inserir ou remover elementos */
    TLista aux=*v1;
    *v1=*v2;
    *v2=aux;

    v2->prox=v1->prox; /*O campo 'prox' e 'ant' de v2 vai recebe os respectivos campos de v1*/
    v2->ant=v1->ant;
    v1->prox=aux.prox; /*O campo 'prox' e 'ant' de v1 vai recebe os respectivos campos da variavel auxiliar*/
    v1->ant=aux.ant;
}

int main()
{
    TLista *Lista=NULL; //Inicia a Lista
    TLista *Comeco=NULL;
    char palavra[MAX_PALAVRA]; /*Armazena a palavra para inserir na nossa lista*/
    char letra1, letra2; /*Guarda os caracteres para trocar as letras de posicao da lista*/
    int i;

    printf("Digite a palavra para trocar 2 letras de lugar:\n");
    scanf("%s",&palavra);
    for(i=0;i<strlen(palavra);i++) /*Varre o tamanho da palavra e insere na lista, uma por uma*/
    {
        if(Lista==NULL) /*Caso a lista nao tenha sido iniciada, chama a funcao que cria a lista*/
        {
            Lista=Novo(palavra[i],NULL);
            Comeco=Lista;
        }
        else /*Caso ja tenha sido iniciada, so chama a funcao que insere o elemento na lista*/
        {
            Insere(Comeco,palavra[i]);
        }
    }

    /*Imprime toda a lista, desde o inicio ate o fim da palavra*/
    imprime(Comeco,1);

    printf("\nDigite a primeira letra:\n");
    scanf(" %c",&letra1);
    printf("Digite a segunda letra:\n");
    scanf(" %c",&letra2);
    /*A leitura das letras esta sendo feita com ' %c', apresenta um espaco em branco
    antes para ler somente o espaco inserido*/

    /*Chama a funcao que vai trocar as letras de posicao dentro da palavra*/
    trocaLetras(Comeco,letra1,letra2);

    /*Depois, vai imprimir a lista novamente, depois de trocar as letras de posicao*/
    imprime(Comeco,1);

    free(Comeco); /*Libera todo o conteudo da lista*/

    return 0;
}
