#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_PILHA 50

typedef struct /*Declarando as variaveis da nossa Pilha*/
{
    double vet[MAX_PILHA];
    int topo;
} TPilha;

void TPilha_Inicia(TPilha *p)/*Funcao que cria uma pilha, e o topo da pilha aponta pra -1*/
{
    p->topo=0;
}

int TPilha_EhVazia(TPilha *p)/*Funcao que verifica se a pilha esta vazia, retornando 0*/
{
    return (p->topo==0);
}

int TamanhoPilha(TPilha *p)
{
    /*Funcao que verifica o tamanho da pilha*/
    return p->topo;
}

/*Funcao que empilha os dados na pilha*/
int TPilha_Empilha (TPilha *p, char val)
{
    if(p->topo==MAX_PILHA)//Pilha cheia
        return 0;
    p->vet[p->topo]=val; /*A posicao topo vai receber o valor digitado*/
    p->topo++; /*O topo da pilha aponta para uma posicao acima dele*/
    return 1;
}

/*Funcao que desempilha os dados da pilha*/
int TPilha_Desempilha (TPilha* p, char* val)
{
    if(TPilha_EhVazia(p))
    {
        return 0;//Pilha vazia
    }
    p->topo--; /*O topo da pilha vai apontar para uma posicao abaixo dele*/
    *val=p->vet[p->topo];/*A variavel vai recolher o valor que esta sendo apontado no topo da pilha*/
    return 1;
}

/*ESSAS DUAS FUNCOES DA PILHA ABAIXO SAO UTILIZADAS PARA ARMAZENAR O VALOR PARA REALIZAR A OPERACAO
(RECEBEM O VALOR DO TIPO DOUBLE, AS FUNCOES DE CIMA SERVEM PARA MUDAR O FORMATO DA EXPRESSAO DA CONTA*/
/*Funcao que empilha os dados na pilha*/
int TPilha_Empilha_Int (TPilha *p, double val)
{
    if(p->topo==MAX_PILHA)//Pilha cheia
        return 0;
    p->vet[p->topo]=val; /*A posicao topo vai receber o valor digitado*/
    p->topo++; /*O topo da pilha aponta para uma posicao acima dele*/
    return 1;
}

int TPilha_Desempilha_Int (TPilha* p, double* val)
{
    if(TPilha_EhVazia(p))
    {
        return 0;//Pilha vazia
    }
    p->topo--; /*O topo da pilha vai apontar para uma posicao abaixo dele*/
    *val=p->vet[p->topo];/*A variavel vai recolher o valor que esta sendo apontado no topo da pilha*/
    return 1;
}

/*Funcao que mostra a prioridade das operacoes da expressao*/
int Prioridade(char c)
{
    switch(c)
    {
    case '(':
    case ')':
        return 0;
    case '+':
    case '-':
        return 1;/*Ficam por ultimo na pilha*/
    case '*':
    case '/':
        return 2;/*Possuem a terceira maior prioridade*/
    case '^':
        return 3;/*'^' tem a segunda maior prioridade*/
    default:
        return 4;/*Os numeros tem maior prioridade, entram primeiro na pilha pos-fixa*/
    }
}

/*Funcao que transofrma a expressao infixa para pos-fixa*/
char *Infixa2Posfixa(TPilha *pPilha,char *operacao)
{
    /*Declara um ponteiro para a variavel de posicao do caractere*/
    char *pos;
    int i, j;
    /*A variavel vai receber o tamanho da expressao, e vai alocar espaco*/
    pos = malloc(strlen(operacao));
    for (i = 0, j = 0; i < strlen(operacao); i++)
    {
        switch (operacao[i])/*operacao[i] e o caractere no indice 'i' da minha string*/
        {
        /*Caso encontre um numero, a funcao vai ler uma variavel do tipo double e ira empilhar na variavel*/
        case '+':
        case '-':
        case '*':
        case '/':
        case '^': /*Caso encontre algum dos operadores, sera verificado a ordem de prioridade*/
            while (TPilha_Desempilha(pPilha, &pos[j]) && (Prioridade(pos[j]) >= Prioridade(operacao[i])))
                /*Desempilha o caracter na posicao 'j', se a prioridade da operacao for maior
                que a de 'operacao', aumenta 'j'*/
                j++;
            if (Prioridade(pos[j]) < Prioridade(operacao[i]))
                /*Caso a prioridade em 'j' seja menor que a da 'operacao[i]', empilha 'pos[j]'*/
                TPilha_Empilha(pPilha, pos[j]);
            /*Depois, empilha 'operacao[i]' na pilha*/
            TPilha_Empilha(pPilha, operacao[i]);
            break;
        case '(': /*Se aparecer '(', empilha na operacao[i]*/
            TPilha_Empilha(pPilha, operacao[i]);
            break;
        case ')': /*Se aparecer ')', desempilha ate achar '('*/
            while (TPilha_Desempilha(pPilha, &pos[j]) && (pos[j] != '('))
                j++;
                if ((pos[j]) == '(') /*Caso encontre '(', desempilhe ambos os parenteses*/
                    TPilha_Desempilha(pPilha,&pos[j++]);
            break;
        default:
            pos[j++] = operacao[i];/*pos[j] recebe os caracteres de algarismos*/
        }
    }
    while (!TPilha_EhVazia(pPilha))
        TPilha_Desempilha(pPilha, &pos[j]);/*Desempilha os operadores*/
    /*Sera impresso a versao pos-fixa, e vai ler a funcao que vai ler o resultado da expressao*/
    printf("A versao pos-fixa da expressao e: %s\n",pos);
    lerOperacao(pPilha,pos);
    /*Depois de obter o resultado, libera o espaco criado para a pilha*/
    free(pPilha);
    return 0;
}

/*Funcao para ler o resultado da operacao*/
void lerOperacao(TPilha *Pilha, char posfixa[])
{
    int i; /*Declarando as variaveis*/
    double x=0,x1=0,x2=0;
    for(i=0; i<strlen(posfixa); i++)
    {
        /*Sera verificado todos os campos da expressao pos-fixa*/
        switch(posfixa[i])
        {
        case '+': /*Caso '+', desempilha dois valores, atribui nas variaveis e realiza a soma*/
            TPilha_Desempilha_Int(Pilha, &x1);
            TPilha_Desempilha_Int(Pilha, &x2);
            x=x2+x1;
            TPilha_Empilha_Int(Pilha,x); /*Depois, empilha na pilha o resultado*/
            break;
        case '-': /*Se tiver '-', desempilha dois valores, atribui nas variaveis e realiza a subtracao*/
            TPilha_Desempilha_Int(Pilha, &x1);
            TPilha_Desempilha_Int(Pilha, &x2);
            x=x2-x1;
            TPilha_Empilha_Int(Pilha,x); /*Depois, empilha na pilha o resultado*/
            break;
        case '/': /*Se tiver '/', desempilha dois valores, atribui nas variaveis e realiza a divisao*/
            TPilha_Desempilha_Int(Pilha, &x1);
            TPilha_Desempilha_Int(Pilha, &x2);
            x=x2/x1;
            TPilha_Empilha_Int(Pilha,x); /*Depois, empilha na pilha o resultado*/
            break;
        case '*': /*Se tiver '*', desempilha dois valores, atribui nas variaveis e realiza a multiplicacao*/
            TPilha_Desempilha_Int(Pilha, &x1);
            TPilha_Desempilha_Int(Pilha, &x2);
            x=x2*x1;
            TPilha_Empilha_Int(Pilha,x); /*Depois, empilha na pilha o resultado*/
            break;
        case '^': /*Se tiver '^', desempilha dois valores, atribui nas variaveis e realiza a potenciacao*/
            TPilha_Desempilha_Int(Pilha, &x1);
            TPilha_Desempilha_Int(Pilha, &x2);
            x=pow(x2,x1);
            TPilha_Empilha_Int(Pilha,x); /*Depois, empilha na pilha o resultado*/
            break;
        default:
            /*Caso sejam numeros, sera atribuido o valor na variavel e ira empilhar esse valor
            OBS: Utiliza -'0' para tranformar a variavel 'char' em 'int'*/
            x=posfixa[i]-'0';
            TPilha_Empilha(Pilha,x);
            break;
        }
    }
    /*Desempliha o ultimo valor, para mostrar o resultado*/
    TPilha_Desempilha(Pilha, &x);
    printf("Resultado: %.2lf\n",x); /*Imprime o resultado*/
}

/*Area principal do programa*/
int main (void)
{
    /*Obs: o parenteses nao funciona na expressao se colocar ele como primeiro caractere*/
    TPilha *pPilha; /*Declarando a variavel de uma pilha*/
    pPilha = (TPilha *) malloc(sizeof(TPilha)); /*Alocando espaco na memoria pra Pilha*/
    TPilha_Inicia(pPilha); /*Inicia a Pilha*/
    char operacao[MAX_PILHA];
    printf("Digite a expressao infixa:");
    scanf("%s",operacao); /*A expressao fica armazenada no vetor*/
    printf("Expressao infixa: %s\n",operacao);
    /*Chama a funcao que ira retornar a expressao pos-fixa e depois o resultado dela*/
    printf("%s\n",Infixa2Posfixa(pPilha,operacao));
    return 0;
}
