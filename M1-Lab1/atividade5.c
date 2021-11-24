/* Disciplina: Computação concorrente */
/* Aluno Nicolas Padre de Lima DRE:118093872 */
/* Laboratório 1 - Atividade 5 */

#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define TAM 10000 //Tamanho do vetor

int VETOR[TAM]; //Vetor que vamos calcular o quadrado
int VETORORIGINAL[TAM]; //Vetor aux que vai ser usado só para fins de mostrar que o codigo funcionou

//Nossa Thread recebe como argumento 0 ou 1 e esse numero vamos andar no vetor de 2 em 2
//De forma que vamos ter duas threads, uma calculando todos os vetores de posição impar
//A outra thread vai calcular todos os vetores de posição par
//ex: uma thread vai calcular os vet[0], vet[2] ...e a outra vet[1], vet[3]...
void * quadrado(void *arg){
	int i= *(int *) arg;//Vamos receber o primeiro iterador, 0 ou 1
	for(;i<TAM;i+=2){
		VETOR[i]*=VETOR[i];//calcula o quadrado e guarda nele mesmo
	}
	pthread_exit(NULL);
}

//Função Principal
int main(void){
	//Vamos usar o rand para preencher o vetor com numeros entre 1 e 10
	srand(time(NULL));
	//Vamos então preencher o VETOR, vamos tambem copiar ele, para verificar resultado mais tarde
	for(int aux=0;aux<TAM;aux++){
		VETOR[aux]=(rand()%10)+1;
		//Esse VETORORIGINAL vai guardar os numeros originais
		VETORORIGINAL[aux]=VETOR[aux];
	}
	
	pthread_t tid[2];//identificador das 2 Threads no sistema
	int i=0;//Primeira thread vai começar no vetor[0]
	int j=1;//Primeira thread vai começar no vetor[1]
	//Chamada da primeira Thread
	if(pthread_create(&tid[0], NULL, quadrado, (void *)&i))
		puts("Erro na primeira pthread_create");
	//Chamada da segunda Thread
	if(pthread_create(&tid[1], NULL, quadrado, (void *)&j))
		puts("Erro na segunda pthread_create");


	//Esperamos as duas Threads acabarem
	for(int aux=0; aux<2;aux++){
		if(pthread_join(tid[aux], NULL))
			puts("Erro join");
	}

	//Percorremos os vetores e verificamos se o vetor está com o quadrado correto
	for(int aux=0;aux<TAM;aux++){
		//Vamos comparar o vetor original e o depois do quadrado
		//Caso tenha erro, imprime na tela
		if(!(VETOR[aux]==VETORORIGINAL[aux]*VETORORIGINAL[aux])){
			puts("Erro no quadrado");
			break;
		}
		//Essa linha de baixo imprimiria na tela todos os resultados para verificação manual
		//printf("%d -> %d\n", VETORORIGINAL[aux], VETOR[aux]);
	}

	pthread_exit(NULL);

	//Fim da main
	return 0;
}

	
