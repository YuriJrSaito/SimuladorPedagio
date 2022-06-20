#define maxfila 50

struct tpElemento{
	char placa[50],fabricante[50],cor[50],categoria[50];
	int Prioridade,ta=0,eixos;
};

struct tpFilaPrioridade{
	int inicio, fim, cont;
	tpElemento fila[maxfila];
};

void Inicializar(tpFilaPrioridade &FP){
	FP.inicio = 0;
	FP.fim = -1;
	FP.cont = 0;
}

void Inserir(tpFilaPrioridade &FP, tpElemento elemento){
	tpElemento aux;
	int i;
	FP.fila[++FP.fim] = elemento;
	i = FP.fim;
	while(i > FP.inicio && FP.fila[i].Prioridade < FP.fila[i-1].Prioridade){
		aux = FP.fila[i];
		FP.fila[i] = FP.fila[i-1];
		FP.fila[i-1] = aux;
		i--;
	}
	FP.cont++;
}


tpElemento Retirar(tpFilaPrioridade &FP){
	FP.cont--;
	return FP.fila[FP.inicio++];
}

tpElemento elementoInicio(tpFilaPrioridade FP){
	return FP.fila[FP.inicio];
}

tpElemento elementoFim(tpFilaPrioridade FP){
	return FP.fila[FP.fim];
}

char Cheia(int cont){
	return (cont==maxfila);
}

char Vazia(int cont){
	return(cont==0);
}

void Exibir(tpFilaPrioridade FP){
	tpElemento aux;
	while(!Vazia(FP.cont)){
		aux = Retirar(FP);
		printf("\nElemento: %s - Prioridade: %d - TA: %d",aux.placa,aux.Prioridade,aux.ta);
	}
}

