#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lista /*Declarando as variaveis da lista*/
{
    int info;
    char nomeProduto[128];
    int precoProduto;
    struct lista* prox;
} TLista;

static TLista *inicio =NULL;
static TLista *fim =NULL;
static TLista *nova =NULL;

/*Funcao que insere um produto na lista*/
void insere (int x, char nome[], int preco)
{
    /*Aloca memoria para o novo produto*/
    nova = calloc(1,sizeof(TLista));
    if(!nova)/*Caso nao consiga, mostra a mensagem de erro e sai do programa*/
    {
        printf("nao e possivel alocar memoria");
        exit(1);
    }
    /*Atribiu os novos valores nos seus respectivos campos*/
    nova->info=x;
    strcpy(nova->nomeProduto, nome);
    nova->precoProduto=preco;
    nova->prox=NULL;
    /*Caso nao tenha um produto inserido, o inicio dele eh declarado*/
    if(inicio==NULL)
    {
        inicio=nova;
    }
    else/*Caso contrario, o 'prox' aponta para o novo produto inserido*/
    {
        fim->prox=nova;
    }
    /*o fim da lista recebe o valor do ultimo produto inserido*/
    fim=nova;
    printf("Produto Inserido na lista!\n");
}

/*Funcao para buscar um produto pela pesquisa por nome*/
void busca (char nome[])
{
    /*Comeca a busca pelo inicio da lista*/
    TLista *produto =inicio;

    if(!inicio)/*Caso a lista nao tenha um conteudo no inicio, a lista esta vazia*/
    {
        printf("A lista esta vazia!!\n\n");
    }
    /*Declara uma variavel para verificar se achou um produto ou nao*/
    int achou=0;
    while(produto)
    {
        /*Caso o nome do produto pesquisado seja igual ao que esta na lista, encontra o produto*/
        if(strcmp(produto->nomeProduto,nome)==0)
        {
            achou=1; /*Atribui o valor de 'achou' como 1*/
            printf("PRODUTO ENCONTRADO!!\n\n");
            /*Mostra o preco do produto, como sugerido no enunciado da questao*/
            printf("Valor do produto: %d\n",produto->precoProduto);
            produto=produto->prox;/*Recebe o conteudo do proximo elemento da lista*/
        }
        else /*Caso o nome seja diferente, so faca o conteudo receber o proximo elemento*/
        {
            produto=produto->prox;
        }
    }
    if(!achou)/*Caso nao tenha encontrado, mostre a mensagem de que nao foi encontrado o produto*/
    {
        printf("O produto buscado nao foi encontrado na lista!\n\n");
    }
    produto=NULL; /*Declara o valor como nulo, apos terminar a pesquisa*/
}

/*Funcao para encontrar um produto pelo nome e deleta*/
void retira (char nome[])
{
    TLista *produto =inicio;
    TLista *aux = NULL;
    TLista *anterior = inicio;
    int achou =0; /*0 se nao achou, 1 se achou*/

    if(!inicio)/*Caso a lista nao tenha um conteudo no inicio, a lista esta vazia*/
    {
        printf("A lista esta vazia!!\n\n");
    }

    while(produto)
    {
        /*Caso o nome do produto pesquisado seja igual ao que esta na lista, achou o produto*/
        if(strcmp(produto->nomeProduto,nome)==0)
        {
            achou=1;
            /*Se o produto encontrado esta no inicio da lista, realiza a tarefa abaixo*/
            if(strcmp(inicio->nomeProduto,nome)==0)
            {
                aux=inicio;/*O ponteiro auxiliar recebe o conteudo do inicio*/
                inicio=inicio->prox; /*O ponteiro inicio recebe o conteudo do proximo elemento da lista*/
                free(aux); /*Libera o conteudo que esta na variavel auxiliar*/
            }
            /*Se o produto encontrado esta no fim da lista, realiza a tarefa abaixo*/
            if(strcmp(fim->nomeProduto,nome)==0)
            {
                aux=fim;/*O ponteiro auxiliar recebe o conteudo do final da lista*/
                fim=anterior; /*O ponteiro do fim da lista recebe o conteudo anterior da lista*/
                free(aux); /*Libera o conteudo que esta na variavel auxiliar*/
            }
            /*Caso esteja no meio da lista, faz as tarefas abaixo*/
            aux=produto; /*O ponteiro auxiliar recebe o conteudo do produto*/
            anterior->prox=produto->prox; /*O conteudo do produto anterior aponta para o produto seguinte ao encontrado*/
            free(aux); /*Libera o conteudo aux*/
            printf("Produto retirado da lista!\n\n");
        }
        /*O ponteiro anterior recebe o conteudo de 'produto', e ele aponta para o proximo da lista*/
        anterior=produto;
        produto=produto->prox;
    }
    /*Caso nao tenha encontrado, aparece a mensagem de que nao foi encontrado*/
    if(!achou)
    {
        printf("O produto nao foi encontrado\n\n");
    }
    /*Declara todos os ponteiros para nulo, apos a pesquisa*/
    produto=NULL;
    aux=NULL;
    anterior=NULL;
}

/*Funcao que ira limpar todos os conteudos da lista*/
void limpaTudo()
{
    /*O ponteiro auxiliar recebe o valor nulo*/
    TLista *aux =NULL;
    /*Enquanto ele faz a pesquisa do inicio da lista, ele vai liberando os conteudos da lista*/
    while(inicio)
    {
        aux=inicio; /*O ponteiro aux recebe o conteudo do inicio*/
        inicio=inicio->prox; /*Inicio recebe o conteudo que aponta para o proximo*/
        free(aux); /*Libera o conteudo auxiliar*/
    }
    /*Declara os ponteiro para nulo, apos a pesquisa*/
    inicio=NULL;
    aux=NULL;
    /*Sai do programa*/
    exit(0);
}

/*Area principal do programa*/
int main (void)
{
    /*Declaracao das variaveis*/
    int i=0, opcao=0, codigo, precoProduto=0;
    char nomeProduto[128]= {0};

    do
    {
        /*Menu interativo da programa, cada valor realiza uma acao diferente*/
        printf("======MENU INTERATIVO DE UMA LISTA DE PRODUTOS=======\n");
        printf("Digite [1] para inserir um novo produto\n");
        printf("Digite [2] para buscar um produto e mostrar o preco\n");
        printf("Digite [3] para excluir um produto a partir do nome informado\n");
        printf("Digite [4] para excluir toda a lista\n");
        printf("Digite a sua opcao:\n");
        scanf("%d",&opcao);

        switch(opcao)
        {
        case 1: /*A opcao realizara uma insercao na lista*/
            codigo=i++;
            printf("Codigo do produto: %d\n",codigo+1);
            printf("Digite o nome do produto: ");
            scanf("%s",nomeProduto);
            printf("Digite o preco do produto: ");
            scanf("%d",&precoProduto);
            insere(codigo,nomeProduto,precoProduto); /*Funcao que insere na lista os valores armazenados*/
            break;

        case 2: /*A opcao realizara uma busca na lista a partir de uma pesquisa por nome, e retornar o preco*/
            printf("Digite o nome do produto: ");
            scanf("%s",nomeProduto);
            busca(nomeProduto); /*Chama a funcao de busca*/
            break;

        case 3: /*A opcao vai retirar um conteudo da lista a partir de uma pesquisa por nome*/
            printf("Digite o nome do produto: ");
            scanf("%s",nomeProduto);
            retira(nomeProduto); /*Chama a funcao de retirar uma produto*/
            break;

        case 4: /*A opcao vai limpar todo o conteudo da lista*/
            limpaTudo();
            break;

        default: /*Caso digite qualquer outro valor, sera invalido*/
            printf("Opcao incorreta!");
            break;
        }
    }
    while(opcao!=4); /*O laco ira se repetir enquanto o valor digitado nao for 4*/

    return 0;
}
