#include <stdio.h>
#include <stdlib.h>
#define MAX_FILA 200 /*Define o tamanho maximo da fila no valor de 200*/

typedef struct /*Declarando as variaveis da nossa Pilha*/
{
    int itens [MAX_FILA];
    int n;
    int inicio;
} TFila;
typedef TFila *pFila;

int incr_indice(int i)/*Funcao para incrementar o indice de posicao na fila*/
{
    return (i+1)%MAX_FILA;
}

pFila cria_fila()/*Funcao responsavel em criar a fila*/
{
    pFila fila=(pFila) malloc (sizeof(TFila));/*Aloca espaco para a fila*/
    fila->n=0; /*fila aponta para o fim da fila (0 no caso, pois acabou de ser criada*/
    fila->inicio=0; /*fila aponta para o inicio da fila na posicao 0*/
    return (fila);
}

/*Funcao responsavel em inserir um valor na fila*/
int TFila_Insere(pFila p, int val)
{
    int fim; /*Declara uma variavel para o fim da fila*/
    if(p==NULL) /*Caso 'p' esteja vazia, significa que ela nao foi inicializada*/
    {
        printf("Fila nao inicializada!\n");
        return -1;
    }
    if(p->n==MAX_FILA) /*Caso 'p' aponte para 'n', caso esteja na ultima posicao possivel, mostra que esta cheio*/
    {
        printf("Fila cheia!\n");
        return -1;
    }
    fim=(p->inicio+p->n)%MAX_FILA; /*fim recebe a proxima posicao que possui um espaco vazio*/
    p->itens[fim]=val; /*Essa posicao fim recebe o valor que foi digitado para colocar na fila*/
    p->n++; /*Incrementa a posicao de 'n', onde ira apontar para a proxima posicao vazia da fila*/
    return 0;
}

/*Funcao responsavel em remover um valor da fila*/
int TFila_Retira(pFila p, int* val)
{
    if(p==NULL) /*Caso 'p' esteja vazia, significa que ela nao foi inicializada*/
    {
        printf("Fila nao inicializada!\n");
        return -1;
    }
    if(p->n==0) /*Caso 'p' aponte para 'n', caso esteja na primeira posicao, mostra que esta vazio*/
    {
        printf("Fila vazia!\n");
        return -1;
    }
    *val = p->itens[p->inicio]; /*o endereco do valor recebe o primeiro valor inserido na fila*/
    p->inicio = incr_indice(p->inicio); /*o inicio aponta agora para a primeira posicao inserida na fila*/
    p->n--; /*Diminui o tamanho de n*/
    return 0;
}

/*Funcao responsavel em imprimir os candidatos na forma ordenada na fila*/
void imprimeOrdenado(pFila novaFila, int numCandidato[], int m[], int n)
{
    printf("Os numeros em ordem decrescente sao:\n");
    for(int i=0; i<n; i++)
    {
        printf("Candidato %d, nota: %d\n",numCandidato[i],m[i]);
        if(TFila_Insere(novaFila,numCandidato[i])==-1)
        {
            /*Sera realizada a insercao dos candidatos na fila, caso o valor de funcao
            retorne -1, mostra a mensagem de que nao foi possivel inserir o elemento*/
            printf("Nao foi possivel inserir o elemento");
            break;
        }
    }
}

/*Funcao responsavel em mostrar se o candidato quer ou nao aceitar a vaga*/
void simOuNao(pFila novaFila, int idCandidato[], int n, int v)
{
    int i,j=0,x; /*Declarando as variaveis*/
    pFila filaAprovados; /*Cria outra fila, para armazenar os candidatos aprovados*/
    filaAprovados =cria_fila(); /*Inicia a fila*/
    char resposta; /*Resposta do candidato*/
    int id; /*Numero dos candidatos que serao retirados da nova fila de aprovados*/
    for(i=0; i<n; i++)
    {
        if(TFila_Retira(novaFila,&idCandidato)==-1)
        {
            /*Retira o indice de cada candidato da fila, se a funcao retornar -1, mostra a mensagem de erro*/
            printf("Nao foi posssivel retirar o elemento da fila");
            break;
        }
        printf("Resposta recebida do candidato de id %d (s/n): ",idCandidato);
        scanf("%s",&resposta); /*Recebe a resposta do candidato ('s' se sim ou 'n' se nao)*/
        if(resposta=='s')
        {
            if(TFila_Insere(filaAprovados,idCandidato)==-1)
            {
                printf("Nao foi possivel inserir o elemento");
                break;
            }/*Caso sim, insere na fila de aprovados*/
            printf("Inserido na fila!!\n");
            j++; /*Incrementa o valor de 'j', que sera utilizado para mostrar os candidatos aprovados*/
            v--; /*Diminui o valor de v, que mostra a quantidade de vagas disponiveis*/
            if(v==0) /*Caso v=0, acabou a quantidade de vagas disponiveis, assim termina a convocacao dos alunos*/
            {
                printf("Todas as vagas foram preenchidas!!\n");
                break; /*O break eh utilizado para sair do laco 'for'*/
            }
        }
        else if(resposta=='n') /*Caso o candidato negue a vaga, so mostra que saiu da fila*/
        {
            printf("Saiu da fila!!\n");
        }

    }
    if(v!=0) /*Se v for diferente de 0, significa que sobrou vaga, mas todos os candidatos foram verificados*/
    {
        printf("Sobrou vagas! Todos os candidatos foram chamados!\n");
    }

    if(j!=0){
        printf("\n-Lista de Novos Alunos-\n");
        for(i=0; i<j; i++)
        {
            if(TFila_Retira(filaAprovados,&id)==-1)/*Retira os indices dos candidatos aprovados*/
            {
                /*Caso o valor da funcao retorne -1, mostra que nao foi possivel retirar o elemento*/
                printf("Nao foi possivel retirar o elemento da fila");
                break;
            }
            printf("Candidato id: %d\n",id); /*Mostra o indice de cada candidato aprovado*/
        }
    }
    free(filaAprovados); /*Libera o espaco alocado dessa fila*/
}

/*Area principal do programa*/
int main (void)
{
    pFila novaFila; /*Declarando a Fila*/
    int n, v,i=0,j,aux,aux2; /*Declarando as variaveis do tipo inteiro*/
    /*n-> quantidade de candidatos; v-> quantidade de vagas; i-> identificacao do vestibulando;
    aux e aux2-> variaveis auxilixares*/
    printf("Quantidade de candidatos: \n");
    scanf("%d",&n); /*Armazena a quantidade de candidatos*/
    printf("Quantidade de vagas: \n");
    scanf("%d",&v); /*Armazena a quantidade de vagas*/
    int m[n]; /*Declara um vetor 'm' para armazenar a nota de 'n' candidatos */
    int numCandidato[n]; /*Declara um vetor 'numCandidato' para armazenar a identificacao de 'n' candidatos*/
    novaFila =cria_fila(); /*Inicia a fila*/

    while(i<n)
    {
        numCandidato[i]=i+1;
        printf("Numero Identificador do candidato: %d\n",i+1);
        printf("Nota do candidato:\n");
        scanf("%d",&m[i]); /*Armazena a nota do candidato*/
        if(m[i]>100 || m[i]<0)
        {
            /*Caso a nota inserida seja menor que 0 ou maior que 100, nota incorreta,
              e pede que seja digitado outro valor*/
            printf("Nota incorreta!!! Digite novamente!\n");
        }
        else
        {
            printf("Candidato inserido!\n");
            i++; /*Mostra que o candidato foi inserido, e aumenta o valor e i*/
        }
    }
    /*Varre a pesquisa de i ate n, verificando todos os candidatos*/
    for(i=0; i<n; i++)
    {
        for(j=i+1; j<n; j++) /*Utilizamos tambem j, para verificar um vetor com outro*/
        {
            if(m[i]<m[j])/*Caso a nota do candidato na posicao i seja menor que a do candidato j*/
            {
                aux=m[i];/*A variavel auxiliar recebe o valor de vet[i]*/
                m[i]=m[j]; /*Vet[i] recebe o valor de vet[j]*/
                m[j]=aux; /*E Vet[j] recebe o valor da variavel auxiliar*/
                aux2=numCandidato[i]; /*Fazemos o mesmo com o numero de identificacao do candidato*/
                numCandidato[i]=numCandidato[j];
                numCandidato[j]=aux2;
            }
        }
    }

    imprimeOrdenado(novaFila,numCandidato,m,n); /*Chama a funcao que mostra os dados de forma ordenada*/

    simOuNao(novaFila,numCandidato,n,v); /*Chama a funcao que retorna os novos alunos da universidade*/

    free(novaFila);/*Libera o espaco alocado para a fila criada*/
    return 0;
}
