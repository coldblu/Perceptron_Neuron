#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Para usar a função time()

void iniciarPesos(float pesos[3]){
    srand(time(NULL)); // Inicializa a seed com o tempo atual
	int i = 0;
	while(i < 3){
		pesos[i] = rand() % 2;
		i++;
	}
}

int funcaoAtivacao(float soma) {
    if(soma > 0)
        return 1;
    else 
		return 0;
}

void corrigirPesos(float pesos[3], int ativado, int entrada1, int entrada2, int entrada3){
	if(ativado == 0){
		pesos[0] += entrada1;
		pesos[1] += entrada2;
		pesos[2] += entrada3;
	}else {
		if(pesos[0] != 0)
			pesos[0] -= entrada1;
		if(pesos[1] != 0)
			pesos[1] -= entrada2;
		if(pesos[2] != 0)
			pesos[2] -= entrada3;
	}
}

float soma(float pesos[3], int entrada1, int entrada2, int entrada3){
    float total = 0;
    total += pesos[0] * entrada1;
    total += pesos[1] * entrada2;
    total += pesos[2] * entrada3;
	return total;
}

void treinamento(float pesos[3], int dados[4][4]){
	int i, erros = 0, ciclos = 0, ativado, todosErros = 0;
	float somado = 0;
	printf("\n********** TREINAMENTO **********\n");
	while (erros > 0 || ciclos == 0) {
        erros = 0;
        for(i = 0; i < 4; i++){
            somado = soma(pesos, dados[i][0], dados[i][1], dados[i][2]);
            ativado = funcaoAtivacao(somado);
            if(ativado != dados[i][3]){
                corrigirPesos(pesos, ativado, dados[i][0], dados[i][1], dados[i][2]);
                erros++;
				todosErros++;
            }
        }
        ciclos++;
		printf("Ciclo: %d - Erros: %d \n",ciclos,erros);
    }
	
	printf("\n********** Treinamento finzalizado **********!");
	printf("\nTotal de erros: %d ",todosErros);
	printf("\nTotal de ciclos: %d \n",ciclos);
	//debug
	/*printf("\npeso 1: %.2f \n",pesos[0]);
	printf("\npeso 2: %.2f \n",pesos[1]);
	printf("\npeso 3: %.2f \n",pesos[2]);*/
}

void testes(float pesos[3]){
	int option, ent1, ent2, ent3, ativado;
	float somado = 0;
	printf("\n********** TESTES **********\n");
	do{
		printf("As Estacas são Rasas(0) ou Profundas(1)?");
		scanf("%d",&ent1);
		printf("A Alvenaria é Convencional(0) ou Estrutural(1)?");
		scanf("%d",&ent2);
		printf("A Cobertura é Telhado(0) ou Lage(1)?");
		scanf("%d",&ent3);
		somado = soma(pesos, ent1, ent2, ent3);
		ativado = funcaoAtivacao(somado);
		if(ativado == 0)
			printf("\nA Edificação é do tipo Casa!\n");
		else
			printf("\nA Edificação é do tipo Predio(15 andares)!\n");
		
		printf("\nDigite 0 para sair ou outro numero para continuar: ");
		scanf("%d",&option);
	}while(option != 0);
}

int main(){
	float pesos[3];
	//Inicializar os pesos
	iniciarPesos(pesos);
	printf("Pesos iniciados:\n");
	printf("\npeso 1: %.2f ",pesos[0]);
	printf("\npeso 2: %.2f ",pesos[1]);
	printf("\npeso 3: %.2f \n",pesos[2]);
	//Preenche os dados do treino
	int dadosParaTreino[4][4] = {
        {0,0,1,0},
		{0,1,0,0},
		{1,1,1,1},
		{1,0,1,1}
    };
	//Realizar o treino
	treinamento(pesos,dadosParaTreino);
	//Realizar testes
	testes(pesos);
	return 0;
}

