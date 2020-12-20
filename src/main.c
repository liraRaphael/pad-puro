#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define posicao(I, J, COLUNAS) ((I)*(COLUNAS) + (J))


/**
 *
 *  - TRABALHO DE PAD - C�digo puro sem �s devidas otimiza��es
 *  TELEPROG
 *    - Raphael Lira dos Santos 223865
 *    - Elziele Da Rocha 196396
 *
**/





/***
 *
 *
 *
 * - CABE�ALHO DAS FUN��ES
 *
 *
**/
float random_number();
float * alocar(int dimensaoA,int dimensaoB);
float * gerarMatriz(char * path,int dimensaoA,int dimensaoB);
float * lerArquivo(char * path,int dimensaoA,int dimensaoB);
float * calculaMatriz(float * matrizA, float * matrizB,int dimensaoA,int dimensaoB,int dimensaoC);
double reducaoMatriz(float * matriz, int dimensaoA, int dimensaoB);


/***
 *
 *
 *
 * - Declara��o das variaveisVariavies 
 *
 *
**/

  //aloca e le os arquivos do vetor
  float 
  	* matrizA, 
  	* matrizB, 
  	* matrizC, 
  	* matrizD,
  	* matrizAB;

int 
    y,w,v, //variavel que guardar� os valores da coluna
	i,j,k; // variaveis de controle

double
  	reducao;	//salvara o resultado da redu��o

/***
 *
 *
 *
 * - FUN��ES
 *
 *
**/
//gerador de numeros aleat�rios
float random_number(){
	return ((float) (rand() % 2000)/100)  - 10;
}


// aloca dinamicamente como proposto pelo professor
float * alocar(int dimensaoA,int dimensaoB){
	float * ponteiro;
	ponteiro = calloc(sizeof(float), dimensaoA * dimensaoB);	
	return ponteiro;
}


// gera a matriz de forma aleat�ria
float * gerarMatriz(char * path,int dimensaoA,int dimensaoB){
	
  	// manipula o arquivo para escrita
	FILE * arquivo;
	arquivo = fopen(path,"w");
	
  	//aloca e define o tamanho total
	float * matriz = alocar(dimensaoA,dimensaoB);	
	int MAX = dimensaoA * dimensaoB;
	
	int i = 0;
		
  	//faz o loop, atribuindo valor aleat�rio e salva o arquivo
	for(i = 0;i<MAX;i++){
		matriz[i] = random_number();
		fprintf(arquivo,"%.2f\n",matriz[i]);
	}
	
	fclose(arquivo);
	
	return matriz;
	
}


// le o arquivo 
float * lerArquivo(char * path,int dimensaoA,int dimensaoB){
	
  	//abre o arquivo para leitura
	FILE * arquivo;
	arquivo = fopen(path,"r");
	
  	//caso o arquivo n�o exista, gera um novo
	if(!arquivo){		
		return NULL;
	}
		
		
  	// aloca a matriz dinamicamente
	float * matriz = alocar(dimensaoA,dimensaoB);	
	int MAX = dimensaoA * dimensaoB;
	
	int i = 0;
	
 
   	// faz o loop de leitura
	for(i = 0;i<MAX;i++){
		fscanf(arquivo,"%f\n", &matriz[i]);	
	}
	
	fclose(arquivo);
	
	return matriz;
	
}



/**
*
*
* - Calcula a matriz (A x B)
*
*/
float * calculaMatriz(float * matrizA, float * matrizB,int dimensaoA,int dimensaoB,int dimensaoC){
	
	float
		* matriz = alocar(y,v);
   
	for(i=0;i<dimensaoA;i++){	       							
		for(j=0;j<dimensaoB;j++){	         						
			for(k=0;k<dimensaoC;k++){	
				matriz[posicao(i,k,dimensaoC)] += (matrizA[posicao(i,j,dimensaoB)] * matrizB[posicao(j,k,dimensaoC)]) ;		 								
			}      	
		}			
	}
	
	return matriz;
	
}

double reducaoMatriz(float * matriz, int dimensaoA, int dimensaoB){
    
    int
    	MAX = dimensaoA * dimensaoB;
    
	double
		resultado = 0;
    
	for(i=0;i<MAX;i++){             
		resultado += matriz[i];     
	}

	return resultado;
 
}


/***
 *
 *
 *
 * - MAIN
 *
 *
**/
int main(int argc,char ** argv){
	
  	// verifica se todos os argumentos est�o
	if(argc != 8){
		printf("argumentos invalidos!\n");
		return 1;
	}	
 
	clock_t 
		tIni,tFim;  	
		
	// atribui os valores de dimens�o da matriz
   	y = atoi(argv[1]);
  	w = atoi(argv[2]);
  	v = atoi(argv[3]);
	  
	// aloca os dados nas matrizes  	
	matrizA = lerArquivo(argv[4],y,w); 
	matrizB = lerArquivo(argv[5],w,v); 
	matrizC = lerArquivo(argv[6],v,1); 
 		
	if(y == 0 || w == 0 || v == 0){
		printf("Valor(es) y,w e/ou v invalido(s)!\n");
		return 1;
	}
	
  	// caso falhe algum arquivo
	if(matrizA == NULL || matrizB == NULL || matrizC == NULL){	
		printf("Matriz(es) n�o carregada(s)!\n");	
		return 1;
	} 

   	//grava o tempo incial
   	tIni = clock();  
	
	matrizAB = calculaMatriz(matrizA,matrizB,y,w,v);
	matrizD = calculaMatriz(matrizAB,matrizC,y,v,1);  
	reducao = reducaoMatriz(matrizD,y,1);	
	  
	//grava o tempo final
	tFim = clock();
	
  	// printa a redu��o e o tempo
	printf("o resultado da reducao foi: %f - o tempo exercido foi de %f segundos\n",reducao,(double) (tFim - tIni)/CLOCKS_PER_SEC);
	
  	// abre o arquivo para grava��o da matriz D
	FILE * arquivo;
	arquivo = fopen(argv[7],"w");
	
  	//faz o loop de grava��o
	for(i=0;i<y;i++){
		fprintf(arquivo,"%.2f\n",matrizD[i]);
	}
	
	fclose(arquivo);	
	
	return 0;  
   
}
