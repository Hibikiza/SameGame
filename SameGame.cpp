#include <iostream>
#include <windows.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define LINHA 12
#define COLUNA 16
#define MAX (LINHA*COLUNA)-1

/*             0     1    2     3   4      5      6      7         8  */
typedef enum{BLACK,BLUE,GREEN,CYAN,RED,MAGENTA,BROWN,LIGHTGRAY,DARKGRAY,   /* nome das cores */
LIGHTBLUE,LIGHTGREEN,LIGHTCYAN,LIGHTRED,LIGHTMAGENTA,YELLOW,WHITE} COLORS;
/*  9         10         11        12        13         14    15 */

static int __BACKGROUND = 1/*BLACK*/;/*pode ser o numero ou o nome da cor*/
static int __FOREGROUND = LIGHTGRAY;
using namespace std;
void textcolor (int letras, int fundo){/*para mudar a cor de fundo mude o background*/
    __FOREGROUND = letras;
    __BACKGROUND = fundo;
    SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE),
    letras + (__BACKGROUND << 4));
}
typedef struct{
	int inicio;
	int fim;					//definindo struct para usar na implementaçao de Filas 
	int elem[LINHA*COLUNA];
}tipoFila;
void inicializaFila(tipoFila *fila) //inicializa fila
{
	fila->fim=-1;					
	fila->inicio=-1;
}
bool filaVazia(tipoFila *fila)		//verifica se a fila esta vazia, ou seja, inicio e fim sao iguais
{
	if(fila->fim==fila->inicio)
	{
		return true;					
	}
	return false;
}
bool filaCheia(tipoFila *fila)		//verifica se a fila esta cheia, ou seja, inicio é -1 e fim é posiçao maxima
{
	if((fila->inicio==-1)&&(fila->fim==MAX))
	{
		return true;
	}
	return false;
}
void deslocaFila(tipoFila *fila)		//caso a fila nao esteja cheia mas fim seja MAX, entao deve-se deslocar os elementos para inserir mais elementos
{
	int i,desloc = fila->inicio + 1;
	for(i=fila->inicio+1;i<=fila->fim;i++)
	{
		fila->elem[i-desloc] = fila->elem[i];
	}
	fila->inicio = -1;
	fila->fim = fila->fim - desloc;
}
void insereFila(tipoFila *fila, int x)	//insere novos elementos na fila caso a mesma nao esteja cheia(elemento sempre é inserido na posiçao fim, pois se trata de uma fila)
{
	if(!filaCheia(fila))
	{
		if(fila->fim == MAX)
		{
			deslocaFila(fila);
		}
		fila->fim = fila->fim + 1;
		fila->elem[fila->fim] = x;
	}
}
void removeFila(tipoFila *fila,int *x)	//remove um elemento e o retorna caso a fila nao esteja vazia(elemento sempre é removido da posiçao inicio, pois se trata de uma fila)
{
	if(!filaVazia(fila))
	{
		fila->inicio = fila->inicio + 1;
		*x = fila->elem[fila->inicio];
		if(filaVazia(fila))
		{
			inicializaFila(fila);
		}
	}
}
void primeiroDaFila(tipoFila *fila)		//caso a fila nao esteja vazia, mostra o primeiro da fila
{
	if(!filaVazia(fila))
	{
		printf("%d",fila->elem[fila->inicio+1]);
	}else{
		printf("<ERRO>fila esta vazia");
	}
}
void geraMatrix(char tabuleiro[LINHA][COLUNA],int dificuldade )		//cria a matrix que sera usada no jogo,de forma aleatoria
{
	srand(time(NULL));  //funçao para gerar numeros random
	int i,j;
	for(i=0;i<LINHA;i++)
	{
		for(j=0;j<COLUNA;j++)	//usei numeros para preencher a matriz para facilitar as funçoes usadas
		{	
			switch(dificuldade)
			{
				case 1:
					tabuleiro[i][j]=rand()%3;  //colocando aleatoriamente 1 elemento a partir de 3 (0,1,2)
					break;
				case 2:
					tabuleiro[i][j]=rand()%4;	//colocando aleatoriamente 1 elemento a partir de 4 (0,1,2,3)
					break;
				case 3:
					tabuleiro[i][j]=rand()%5;	//colocando aleatoriamente 1 elemento a partir de 5 (0,1,2,3,4)
					break;
				default:						//usei numeros para preencher a matriz para facilitar as funçoes usadas
					break;
			}
		}
	}
}
void mostraMatrix(char matrix[LINHA][COLUNA])	//imprime a matrix para ser vizualizada pelo usuario
{
	int i,j;
	textcolor(0,8);
	printf("__| | | | | | | | | | |0|1|2|3|4|5|__|\n");
	printf("__|");
	for(i=0;i<COLUNA;i++)						
	{
		if(i<10){
			printf("%d|",i);
													//mostra as colunas para facilitar a visao do usuario
		}else{
			j=1;
			printf("%d|",i-(i-j));
			j++;
		}
	}
	printf("__|");
	printf("\n");
	for(i=0;i<LINHA;i++)
	{
		if(i<10){
			textcolor(0,8);
			printf("%d |",i);
		}else{									//mostras as linhas para facilitar a visao do usuario
			textcolor(0,8);
			printf("%d|",i);
		}
		for(j=0;j<COLUNA;j++)
		{
			if(matrix[i][j]==32)				//32 quando printado usando %c, torna-se " "(espaço)
												//usei o 32 para facilitar e padronizar, ja que todos os elementos sao numeros
			{
				textcolor(15,0);
				printf("%c ",matrix[i][j]);		//caso o elemento tenha sido retirado da matrix, ele printado como um espaço vazio, por isso seu background volta aser preto
			}else{
				if(matrix[i][j]==0){
					textcolor(1,1);					//definindo as cores de acordo com o nuemero
					printf("%d ",matrix[i][j]);
				}else if(matrix[i][j]==1){
					textcolor(2,2);				
					printf("%d ",matrix[i][j]);		//definindo as cores de acordo com o nuemero
				}else if (matrix[i][j]==2){
					textcolor(4,4);
					printf("%d ",matrix[i][j]);		//definindo as cores de acordo com o nuemero
				}else if (matrix[i][j]==3){
					textcolor(14,14);
					printf("%d ",matrix[i][j]);		//definindo as cores de acordo com o nuemero					
				}else if(matrix[i][j]==4){
					textcolor(5,5);
					printf("%d ",matrix[i][j]);
				}
			}
			
		}
		if(i<10){
			textcolor(0,8);
			printf("%d |",i);
		}else{						//novamente mostrando as linhas e colunas para deixar as posiçoes mais visiveis
			textcolor(0,8);
			printf("%d|",i);
		}
		printf("\n");			//novamente mostrando as linhas e colunas para deixar as posiçoes mais visiveis
	}
	textcolor(0,8);
	printf("__| | | | | | | | | | |0|1|2|3|4|5|__|\n");
	printf("__|");
	for(i=0;i<COLUNA;i++)
	{
		if(i<10){				//novamente mostrando as linhas e colunas para deixar as posiçoes mais visiveis
			printf("%d|",i);

		}else{
			j=1;				//novamente mostrando as linhas e colunas para deixar as posiçoes mais visiveis
			printf("%d|",i-(i-j));
			j++;
		}
	}
	printf("__|");
	printf("\n");
	textcolor(15,0);
	
}
bool Visitado(tipoFila *Filalinha,tipoFila *Filacoluna,int linha,int coluna)  //verifica se um elemento ja foi visitado, para evitar de colocar o mesmo elemento duas vezes na fila dos visitados
{
	int i,cont=0;
	for(i=0;i<=Filalinha->fim;i++)
	{
		if((linha==Filalinha->elem[i]) && (coluna==Filacoluna->elem[i]))
		{
			cont++;
		}
	}
	if(cont==0)
	{
		return false;
	}else{
		return true;
	}
}
int contaPontos(int n)  //conta os pontos do jogador
{
	int pontos=0;
	n=n+1;
	pontos = (n-2)*(n-2);  //formula retirada do site passado como exemplo
	return pontos;
	
}
void verificaVizinhos(char matrix[LINHA][COLUNA],int visiLinha, int visiColuna,tipoFila *visitadosLinha, tipoFila *visitadosColuna,tipoFila *filaLinha
						, tipoFila *filaColuna,int cima,int baixo, int direita, int esquerda) //verifica se os vizinhos do elemento sao iguais a ele
{
	if(cima==1)
	{
		if(matrix[visiLinha][visiColuna]==matrix[visiLinha-1][visiColuna])//verifica se o elemento de cima é vizinho
		{	
			if(!Visitado(visitadosLinha,visitadosColuna,visiLinha-1,visiColuna))
			{
				if(!Visitado(filaLinha,filaColuna,visiLinha-1,visiColuna))			//verifica se tal elemento ja foi colocado na fila de visitados ou na fila de nao visitados
				{
					insereFila(filaLinha,visiLinha-1);						
					insereFila(filaColuna,visiColuna);
				}
			}
		}
	}
	if(baixo==1)
	{
		if (matrix[visiLinha][visiColuna]==matrix[visiLinha+1][visiColuna])//verifica se o elemento de baixo é vizinho
		{	
			
			if(!Visitado(visitadosLinha,visitadosColuna,visiLinha+1,visiColuna))
			{																		//verifica se tal elemento ja foi colocado na fila de visitados ou na fila de nao visitados
				if(!Visitado(filaLinha,filaColuna,visiLinha+1,visiColuna))
				{
					insereFila(filaLinha,visiLinha+1);						
					insereFila(filaColuna,visiColuna);
				}
			}
		}
	}
	if(direita==1)
	{
		if (matrix[visiLinha][visiColuna]==matrix[visiLinha][visiColuna+1])//verifica se o elemento da direita é vizinho
		{      			
			if(!Visitado(visitadosLinha,visitadosColuna,visiLinha,visiColuna+1))
			{																		//verifica se tal elemento ja foi colocado na fila de visitados ou na fila de nao visitados
				if(!Visitado(filaLinha,filaColuna,visiLinha,visiColuna+1))
				{
					insereFila(filaLinha,visiLinha);						
					insereFila(filaColuna,visiColuna+1);
				}			
			}	
		}
	}
	if(esquerda==1)
	{
		if (matrix[visiLinha][visiColuna]==matrix[visiLinha][visiColuna-1])//verifica se o elemento da esquerda é vizinho
		{					
			if(!Visitado(visitadosLinha,visitadosColuna,visiLinha,visiColuna-1))
			{																	//verifica se tal elemento ja foi colocado na fila de visitados ou na fila de nao visitados
				if(!Visitado(filaLinha,filaColuna,visiLinha,visiColuna-1))
				{
					insereFila(filaLinha,visiLinha);						
					insereFila(filaColuna,visiColuna-1);
				}
			}
		}
	}
}
void buscaLargura(char matrix[LINHA][COLUNA],int linha,int coluna,int *teste,int *pontos)	//busca por todos os vizinhos na regiao do elemento escolhido
{
	int i,j;
	tipoFila filaLinha,filaColuna,visitadosLinha,visitadosColuna;	//como se trata de uma matrix, foram usadas duas filas para cada contexto
	inicializaFila(&filaLinha);									//duas filas(linha e coluna) para os nao visitados e, duas filas(linha e coluna) para os já visitados
	inicializaFila(&visitadosLinha);
	inicializaFila(&filaColuna);
	inicializaFila(&visitadosColuna);
	insereFila(&filaLinha,linha);
	insereFila(&filaColuna,coluna);
	int visiLinha,visiColuna;
	while(!(filaVazia(&filaLinha) && filaVazia(&filaColuna)))
	{
		removeFila(&filaLinha,&visiLinha);
		removeFila(&filaColuna,&visiColuna);
		if(!Visitado(&visitadosLinha,&visitadosColuna,visiLinha,visiColuna))
		{
			insereFila(&visitadosLinha,visiLinha);
			insereFila(&visitadosColuna,visiColuna);
		}		
		//caso o elemento esteja nas quinas da esquerda
		if(visiColuna==0)
		{
			if(visiLinha==0)
			{									//os ultimos quatro parametros representam qual "direçao" a funçao deve verificar se é vizinho
				verificaVizinhos(matrix,visiLinha,visiColuna,&visitadosLinha,&visitadosColuna,&filaLinha,&filaColuna,0,1,1,0);
			}	
			if(visiLinha==LINHA-1){
				verificaVizinhos(matrix,visiLinha,visiColuna,&visitadosLinha,&visitadosColuna,&filaLinha,&filaColuna,1,0,1,0);	
			}
		}		
			//caso o elemento esteja nas quinas da direita
		if(visiColuna==COLUNA-1)
		{
			if(visiLinha==0)
			{
				verificaVizinhos(matrix,visiLinha,visiColuna,&visitadosLinha,&visitadosColuna,&filaLinha,&filaColuna,0,1,0,1);
			}
			if (visiLinha==LINHA-1)
			{
				verificaVizinhos(matrix,visiLinha,visiColuna,&visitadosLinha,&visitadosColuna,&filaLinha,&filaColuna,1,0,0,1);
			}
		}		
			//caso o elemento esteja na borda esquerda
		if((visiLinha!=0)&&(visiLinha!=LINHA-1)&&(visiColuna==0))
		{
			verificaVizinhos(matrix,visiLinha,visiColuna,&visitadosLinha,&visitadosColuna,&filaLinha,&filaColuna,1,1,1,0);		
		}
		//caso elemento esteja na borda direita
		if((visiLinha!=0)&&(visiLinha!=LINHA-1)&&(visiColuna==COLUNA-1))
		{
			verificaVizinhos(matrix,visiLinha,visiColuna,&visitadosLinha,&visitadosColuna,&filaLinha,&filaColuna,1,1,0,1);
		}
		//caso elemento esteja na borda de cima
		if((visiLinha==0)&&(visiColuna!=0)&&(visiColuna!=COLUNA-1))
		{
			verificaVizinhos(matrix,visiLinha,visiColuna,&visitadosLinha,&visitadosColuna,&filaLinha,&filaColuna,0,1,1,1);
		}
		//caso o elemento esteja na borda de baixo
		if((visiLinha==LINHA-1)&&(visiColuna!=0)&&(visiColuna!=COLUNA-1))
		{
			verificaVizinhos(matrix,visiLinha,visiColuna,&visitadosLinha,&visitadosColuna,&filaLinha,&filaColuna,1,0,1,1);
		}
		//caso elemento possa ter 4 vizinhos
		if((visiColuna!=0)&&(visiColuna!=COLUNA-1)&&(visiLinha!=0)&&(visiLinha!=LINHA-1))
		{	
			verificaVizinhos(matrix,visiLinha,visiColuna,&visitadosLinha,&visitadosColuna,&filaLinha,&filaColuna,1,1,1,1);										
		}
	}
	int a;
	if((visitadosLinha.fim>0)&&(visitadosColuna.fim>0))		//verifica se a regiao escolhida tem pelo menos 2 vizinhos
	{
		if(*teste==0)//a variavel "teste"==0 serve para mostrar que a funçao de busca em largura foi chamada a partir de uma jogada e a matrix deve ser alterada
		{
			*pontos = (*pontos + (contaPontos(visitadosLinha.fim)));	//pega a fila de visitados para contabilizar os pontos de acordo com a quantidade de elementos visitados
			for(a=0;a<=visitadosLinha.fim;a++)
			{		
				matrix[visitadosLinha.elem[a]][visitadosColuna.elem[a]]=32;//elementos visitados recebem 32 para serem identificados como vazio
		
			}
		}
	}else{
		*teste=2;	//variavel "teste"==2 significa que o jogador escolheu uma regiao com apenas um elemento
	}
	
}

void deslocaMatrix(char matrix[LINHA][COLUNA])		//descola os elementos da matrix, evitando elementos flutuantes ou separados por colunas vazias
{
	int i,j,cont=0,a=0,aux,ultvazia=0;
	char vetor[LINHA];			//vetor que guardara temporariamente os elementos de cada coluna
	for(i=COLUNA-1;i>=0;i--)
	{
		for(j=LINHA-1;j>=0;j--)
		{
			if(matrix[j][i]!=32)
			{	
				vetor[cont]=matrix[j][i];//pega apenas os elementos nao vazios
				cont++;
			}
		}
		if(cont==0)	//se o contador for igual a zero, significa que a coluna inteira esta vazia
		{
			
			if(i<COLUNA-1)
			{
				for(aux=i;aux<COLUNA-1;aux++)
				{
					for(j=LINHA-1;j>=0;j--)	//"puxa" as colunas da frente, evitando colunas inteiras vazias separando os elementos
					{
						matrix[j][aux]=matrix[j][aux+1];						
					}
				}
			}
			if(ultvazia==0)
			{
				for(aux=0;aux<LINHA;aux++)
				{							//serve para zerar a ultima coluna, na primeira vez que uma coluna ficar vazia
					matrix[aux][COLUNA-1]=32;
					ultvazia++;	//dessa forma o condicional só é executado uma vez
				}
			}
		}else
		{
			a=LINHA-1;
			for(j=0;j<cont;j++)
			{							// "puxa" para baixo os elementos flutuando
				matrix[a][i]=vetor[j];//matrix recebe os elementos da coluna na ordem, de cima para baixo
				a--;
			}
			for(j=a;j>=0;j--)
			{
				matrix[j][i]=32;//o resto das posiçoes nao preenchidas da matriz recebem 32,ou seja, vazio(" ")
			}
			cont=0;
		}
	}
}
bool verificaJogo(char matrix[LINHA][COLUNA],int pontos)	//verifica se ainda há jogadas possiveis
{
	int i,j,ligado=1;	//variavel ligado é passada como parametro, desta forma a variavel "teste"na funçao de busca recebe 1, assim nenhuma alteraçao é feita na matrix
	for(i=0;i<COLUNA;i++)
	{
		for(j=0;j<LINHA;j++)
		{
			if(matrix[j][i]!=32)
			{
				ligado=1;
				buscaLargura(matrix,j,i,&ligado,&pontos);
				if(ligado==1)
				{
					return true;	//se a variavel voltar com o valor ==1, significa que existe pelo menos uma regiao com pelo menos 2 vizinhos
				}
				
			}
		}
	}
	return false;
}
void megalovania(void)		//musica megalovania(Undertale),toca ao final do jogo para dar um "chan"  xD
{							// foi feita na raça u.u
	Beep(294,150);/* re */
	Beep(294,150);/* re */
	Beep(588,300);/* re+*/
	Sleep(300);
	Beep(440,400);/* la */
	Sleep(200);
	Beep(415,300);/* sol b */
	Sleep(150);
	Beep(392,300);/* sol */
	Sleep(150);
	Beep(349,300);/* fa */
	Sleep(150);
	Beep(294,150);/* re */
	Beep(349,150);/* fa */
	Beep(392,150);/* sol */
	Sleep(150);
	Beep(261,150);/* do */
	Beep(261,150);/* do */
	Beep(588,300);/* re+*/
	Sleep(300);
	Beep(440,400);/* la */
	Sleep(300);
	Beep(415,300);/* sol b */
	Sleep(150);
	Beep(392,300);/* sol */
	Sleep(150);
	Beep(349,300);/* fa */
	Sleep(150);
	Beep(294,150);/* re */
	Beep(349,150);/* fa */
	Beep(392,150);/* sol */
	Sleep(150);
	Beep(247,150); //si
	Beep(247,150); //si
	Beep(588,300);/* re+*/
	Sleep(300);
	Beep(440,400);/* la */
	Sleep(200);
	Beep(415,300);/* sol b */
	Sleep(150);
	Beep(392,300);/* sol */
	Sleep(150);
	Beep(349,300);/* fa */
	Sleep(150);
	Beep(294,150);/* re */
	Beep(349,150);/* fa */
	Beep(392,150);/* sol */
	Sleep(150);
	Beep(233,150); //si b
	Beep(233,150); //si b
	Beep(588,300);/* re+*/
	Sleep(300);
	Beep(440,400);/* la */
	Sleep(200);
	Beep(415,300);/* sol b */
	Sleep(150);
	Beep(392,300);/* sol */
	Sleep(150);
	Beep(349,300);/* fa */
	Sleep(150);
	Beep(294,150);/* re */
	Beep(349,150);/* fa */
	Beep(392,150);/* sol */
	Sleep(150);

}
int main(){
	int valor=0,linha,coluna,pontos = 0,nivel;
	char mesa[LINHA][COLUNA];
	printf("1-Facil(3cores)\n2-Normal(4cores)\n3-Dificil(5cores)\nEscolha a dificuldade do jogo digitando o numero correspondente: ");
	scanf("%d",&nivel);
	if((nivel>=1)&&(nivel<4)) //evita de travar o programa caso o usuario digite o numero do nivel errado
	{
		system("cls");
		geraMatrix(mesa,nivel);
		while(verificaJogo(mesa,pontos))
		{
			mostraMatrix(mesa);
			printf("Digite uma linha: ");
			scanf("%d",&linha);
			printf("\nDigite uma Coluna: ");
			scanf("%d",&coluna);
			valor=0;
			if(((linha>=0)&&(linha<LINHA))&&((coluna>=0)&&(coluna<COLUNA)))	//evita de travar o programa caso o usuario digite uma linha ou/e uma coluna errada(nao existe)
			{
				buscaLargura(mesa,linha,coluna,&valor,&pontos);
				if(valor==2)
				{
					system("cls");
					textcolor(0,4);
					printf("Escolha uma regiao com pelo menos 2 elementos vizinhos!\n");
					textcolor(15,0);
				}else{
					deslocaMatrix(mesa);
					system("cls");
				}				
			}else{
				system("cls");
				printf("linha ou coluna nao existente\n");
			}
		}
		mostraMatrix(mesa);
		valor=0;
		for(linha=0;linha<LINHA;linha++)
		{
			for(coluna=0;coluna<COLUNA;coluna++)
			{
				if(mesa[linha][coluna]!=32)
				{			//ao sair do laço while, significa que nao há mais jogadas possiveis
					valor++;//nesse momento é verificado se o jogador ganhou(matrix totalmente vazia) ou perdeu(ainda há elementos na matrix)
				}
			}
		}
		if(valor==0)
		{
			printf("PARABENS VOCE GANHOU!\n");
			printf("Pontuacao: %d",pontos);
		}else
		{
			printf("VOCE PERDEU! :C \n");
			printf("Pontuacao: %d",pontos);
		}
		megalovania();
	}else{
		system("cls");
		printf("Digite corretamente o numero de acordo com o nivel");
	}
	return 0;
}
