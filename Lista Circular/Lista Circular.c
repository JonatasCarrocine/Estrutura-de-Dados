#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct /*Struct que vai declarar as variaveis da nossa lista*/
{
    int jogador;
    int valorCarta;
    struct TLista *prox;
} TLista;

/*Funcao que vai iniciar a nossa lista circular, e criar espaco para os proximos conteudos*/
TLista *Novo(TLista *Primeiro,int jogador,int carta)
{
    TLista *aux; /*Chamamos a lista de 'aux'*/
    aux=(TLista*)malloc(sizeof(TLista)); /*Alocamos espaco para essa lista*/
    aux->jogador=jogador;
    aux->valorCarta=carta;
    aux->prox=Primeiro; /*Declaramos os valores e atribuimos o poteiro para o primeiro valor*/

    return aux;
}

/*Funcao que vai inserir um conteudo na lista circular*/
void Insere(TLista *Inicio, int jogador,int carta)
{
    TLista *aux=Inicio; /*Declaramos as variaveis auxiliares de ponteiro, 'aux' recebe o inicio da lista*/
    TLista *aux2;

    while(aux->prox!=Inicio)
        aux=aux->prox;/*percorre os elementos da lista ate alcancar o inicio da lista*/

    aux2=Novo(aux->prox, jogador,carta); /*'aux2' vai chamar a funcao que vai criar um espaco para a insercao*/
    aux->prox=aux2; /*O ponteiro recebe o conteudo de 'aux2', no qual esta apontando*/
    return;
}

/*Funcao que vai imprimir toda a lista*/
void imprime(TLista *Inicio,TLista *celula)
{
    /*Imprime na tela o conteudo do jogador e da pontuacao total, de cada espaco*/
    printf("Jogador = %d; pontuacao = %d.\n", celula->jogador,celula->valorCarta);
    if(celula->prox!=Inicio)
        /*Chama a funcao de imprimir enquanto ele nao retorna para o inicio da lista
        retornando para a tela todos os conteudos inseridos na lista*/
        imprime(Inicio,celula->prox);

}

/*Funcao que vai remover um determinado conteudo da lista*/
TLista *remocao(TLista *Inicio, int removeJogador)
{
    TLista *aux=Inicio;/*Declarando ponteiro auxiliares, que apontam para o Inicio*/
    TLista *ant=Inicio;

    if(removeJogador == Inicio->jogador)/*Caso o jogador removido esteja no inicio da fila*/
    {
        while(aux->prox!=Inicio)
            aux=aux->prox; /*Percorre toda a lista ate voltar novamente para o inicio*/

        aux->prox=Inicio->prox;
        free(Inicio); /*Libera o conteudo que esta no inicio da lista*/
        aux=aux->prox; /*Agora a variavel 'aux' aponta para o proximo conteudo da lista, o novo inicio*/
        printf("\nRemocao no inicio\n Novo Inicio :%d \n", aux->jogador);

        return aux;
    }
    while(aux->jogador!=removeJogador) /*Caso o numero do jogador nao seja igual ao que esteja querendo remover, pesquisa o proximo*/
    {
        if(aux!=Inicio) /*Se a busca nao estiver chegado no inicio, 'ant' recebe o conteudo do proximo campo*/
            ant=ant->prox;
        aux=aux->prox; /*'aux' recebe o conteudo do proximo campo*/
        if(aux==Inicio) /*Se 'aux eh igual ao inicio, significa que percorreu toda a lista, ou seja, o valor nao estah na lista*/
        {
            printf("\nValor %d nao esta na lista!!!\n", removeJogador);
            return Inicio;
        }
    }
    ant->prox=aux->prox; /*o proximo conetudo de 'ant' recebe o proximo conteudo de 'aux'*/
    free(aux); /*Libera o conteudo da lista*/
    return Inicio;
}

/*Funcao que vai ler o valor da carta*/
int lerOp(char cartas[2])
{

    if(strcmp(cartas,"2")==0 ||strcmp(cartas,"3")==0 ||strcmp(cartas,"4")==0 ||strcmp(cartas,"5")==0 ||strcmp(cartas,"6")==0
            ||strcmp(cartas,"7")==0||strcmp(cartas,"8")==0||strcmp(cartas,"9")==0)
        /*Caso o valor da carta digitado seja qualquer numero de 2 ate 9*/
    {
        return cartas[0]-'0';
    }
    else if(strcmp(cartas,"10")==0||strcmp(cartas,"J")==0||strcmp(cartas,"Q")==0||strcmp(cartas,"K")==0)
        /*Caso o valor da carta digitado seja 10, ou as letras 'J', 'Q' e 'K'*/
    {
        return 10;
    }
    else if(strcmp(cartas,"A")==0) /*Caso o valor da carta digitado seja 'A', retorna 11*/
    {
        return 11;
    }
    else /*Caso o valor da carta seja qualquer outro diferente, retorna 0*/
    {
        return 0;
    }
    return;
}

int main()
{
    int numJogadores; /*Declarando as variaveis do nosso programa*/
    int i=1, soma;
    TLista *Lista=NULL; /*A nossa lista sera inicialmente vazia*/
    TLista *Inicio; /*Ponteiro que vai apontar para o Inicio da Lista*/
    int aux, numJogando; /*Variaveis auxiliares utilizadas na main*/
    char valor[2]; /*A variavel eh um vetor de caracteres para conseguir ler o valor '10'*/

    printf("Digite o numero de jogadores: "); /*Sera solicitado o numero de jogadores que irao participar do jogo*/
    scanf("%d",&numJogadores);

    if(numJogadores<=0) /*Se o numero digitado for 0, sai do programa*/
        return 0;
    numJogando=numJogadores; /*Variavel recebe numJogadores*/

    do
    {
        printf("Digite uma carta (numero de 2 a 10 ou as letras A, J, K ou Q):\n");
        scanf("%s",&valor); /*Usuario digita o valor da carta para o primeiro jogador*/
        aux=lerOp(valor); /*aux vai receber o valor da funcao que vai ler a carta*/
        if(aux==0)/*Caso seja 0, o valor digitado eh invalido e nao sai do laco de repeticao*/
        {
            printf("Valor Invalido!! Digite novamente um novo valor\n\n");
        }
    }
    while(aux==0);

    Lista=(TLista*)malloc(sizeof(TLista)); /*Aloca espaco para inserir o conteudo*/
    Lista->jogador=i; /*A variavel 'jogador' da lista recebe o numero do jogador ('i' no caso)*/
    Lista->valorCarta=aux; /*A variavel 'valorCarta da lista recebe o numero da carta, armazenada em 'aux'*/
    Lista->prox=Lista; /*A lista gera o 'prox'*/

    Inicio=Lista; /*O inicio da lista recebe os conteudos inseridos*/

    i=2;
    while(i<=numJogando)/*Vai solicitar o valor das cartas para o resto dos jogadores na partida*/
    {
        printf("Digite uma carta (numero de 2 a 10 ou as letras A, J, K ou Q):\n");
        scanf("%s",valor);
        aux=lerOp(valor); /*Recebe o valor da carta*/
        if(aux==0) /*Caso o valor de aux seja 0, o valor da carta digitada eh incorreta, e nao sai da vez desse jogador x*/
        {
            printf("Valor Invalido!! Digite novamente um novo valor\n\n");
            i--;
        }
        else
        {
            Insere(Inicio,i,aux); /*Insere na lista o jogador e a sua pontuacao*/
        }
        i++; /*Incrementa i*/
    }
    /*No fim da rodada, mostra a situacao da pontuacao dos jogadores*/
    printf("\n\n----Situacao da Lista:----\n");
    printf("Jogador = %d; Pontuacao = %d.\n",Inicio->jogador, Inicio->valorCarta);/*Imprime o conteudo do inicio da lista*/
    imprime(Inicio,Inicio->prox); /*Funcao que ira imprimir o resto da lista*/
    printf("--------------------------\n\n");

    while(soma!=21)/*A partida continuara rodando enquanto a soma da pontuacao de algum jogador nao for 21*/
    {
        i=1;
        int saiu=0; /*Cria uma variavel para ver a quantidade de jogadores queirao sair da rodada*/
        int jogador; /*Cria uma variavel 'jogador' para recebe o conteudo presente da variavel 'jogador' da Lista*/
        printf("-----JOGADORES RESTANTES: %d-----\n",numJogando);
        for(i; i<=numJogando; i++)
        {
            printf("Digite uma carta (numero de 2 a 10 ou as letras A, J, K ou Q):\n");
            scanf("%s",valor);
            jogador=Inicio->jogador; /*Recebe o numero do jogador*/
            aux=lerOp(valor); /*'aux' recebe o valor da carta */
            if(aux==0) /*Caso o valor de aux seja 0, o valor da carta digitada eh incorreta, e nao sai da vez desse jogador x*/
            {
                printf("Valor Invalido!! Digite novamente um novo valor\n\n");
                i--;
            }
            else
            {
                soma=aux+Inicio->valorCarta; /*Soma o valor da carta dessa rodada com a pontuacao armazenada na rodada anterior*/
                Inicio=Inicio->prox; /*Aponta o inicio para o proximo campo da lista*/
                Insere(Inicio,jogador,soma); /*Insere esse campo no meio da lista, e remover a anterior com a pontuacao antiga*/
                Inicio=remocao(Inicio,jogador);
                if(soma>21) /*Caso a pontuacao do jogador fique mais que 21, ele eh eliminado do jogo*/
                {
                    printf("\n-----------------------------------\n");
                    printf("O jogador %d estourou o limite de pontos, fez %d pontos\n",jogador,soma); /*Mostra o jogador e a pontuacao*/
                    printf("-----------------------------------\n");
                    Inicio=remocao(Inicio,jogador); /*Remove esse jogador da lista*/
                    saiu++;
                }
                else if(soma==21) /*Caso a pontuacao seja exatamente 21, ele eh o vencedor da partida*/
                {
                    printf("\n-----------------------------------\n");
                    printf("Jogador vencedor: %d, pontuacao: %d\n",jogador,soma); /*Mostra que ganhou e a sua pontuacao*/
                    printf("-----------------------------------\n");
                    free(Inicio); /*Libera todos os conteudos da lista*/
                    exit(0); /*Sai do programa*/
                }
                if((numJogando-saiu)==1)
                {
                    printf("\n----------------------------------------------\n");
                    printf("\nO jogador %d eh o utlimo na partida e fez %d pontos, eh o vencedor!!\n",Inicio->jogador,Inicio->valorCarta);
                    printf("----------------------------------------------\n");
                    free(Inicio); /*Libera todos os conteudos da lista*/
                    exit(0); /*Sai do programa*/
                }
                soma=0; /*Declaramos o valor de soma como '0', toda vez que pega a pontuacao de cada jogador*/
            }

        }
        if(saiu!=0)/*Se algum jogador saiu da rodada, substrai da variavel 'numJogando', que armazena a quantidade de jogadores*/
        {
            numJogando-=saiu;
            saiu=0; /*A variavel recebe 0 novamente, para repetir o processo de eliminacao na proxima rodada*/
        }
        if(numJogando==1) /*Caso tenha sobrado somente um jogador, esse acaba vencendo a partida*/
        {
            printf("\n-----------------------------------\n");
            printf("%d eh o ultimo jogador na partida e fez %d pontos, eh o vencedor!!\n",Inicio->jogador,Inicio->valorCarta);
            printf("-----------------------------------\n");
            free(Inicio); /*Libera todos os conteudos da lista*/
            exit(0); /*Sai do programa*/
        }
        printf("\n\n----Situacao da Lista:----\n"); /*Apos o fim da rodada, mostra a situacao dos jogadores*/
        printf("Jogador = %d; Pontuacao = %d. \n",Inicio->jogador, Inicio->valorCarta);
        imprime(Inicio,Inicio->prox);
        printf("--------------------------\n\n");
    }

    free(Inicio); /*Libera o conteudo*/

    return 0;
}
