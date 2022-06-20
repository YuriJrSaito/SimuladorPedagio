#include<conio2.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include<windows.h>

#include "FILAP.h"
//TA = tempo de atendimento
struct atendimento{
	char placa[50],fabricante[50],cor[50],categoria[50];
	int prioridade,ta,eixos;
	int moto=0, caminhao=0, passeio=0;
	boolean viaFacil = false;
};

void cabines4(){
	FILE *ptr = fopen("Veiculos.txt","r");
	tpElemento e;
	tpFilaPrioridade filas[4];
	
	tpFilaPrioridade h;
	
	for(int j; j<4; j++){
		Inicializar(filas[j]);
	}
	
	int i=0,cont=0;
		
	while(!feof(ptr)){
		if(i==4)
			i=0;
		fscanf(ptr,"%[^;];%[^;];%[^;];%d;%d;%[^;];%d\n",&e.placa,&e.cor,&e.fabricante,&e.Prioridade,&e.eixos,&e.categoria,&e.ta);
		Inserir(filas[i],e);
		printf("\n%s %s %s %d %d %s %d",e.placa,e.cor,e.fabricante,e.Prioridade,e.eixos,e.categoria,e.ta);
			
		cont++;
		i++;
	}
	
	Exibir(h);
	printf("\n=========");
	printf("\nCabine 0");
	Exibir(filas[0]);
	printf("\nCabine 1");
	Exibir(filas[1]);
	printf("\nCabine 2");
	Exibir(filas[2]);
	printf("\nCabine 3");
	Exibir(filas[3]);


	printf("\n\n%d",cont);
	getch();	
}

void simulacao(){
	clrscr();
	int flag = 1, UT=0, ativo, i=0, cont=0, tempoTotal=0, totalMoto=0, totalPasseio=0, totalCaminhao=0, totalHora=0, utEntrada;
	FILE *ptr = fopen("Veiculos.txt","r");	
	
	printf("\nNumero de cabines ativas [1,2,3,4...]: ");
	scanf("%d",&ativo);
	printf("UT para a entrada de um veiculo na fila: ");
	scanf("%d",&utEntrada);
	
	textcolor(6);
	printf("\n\t   Placa Cor Fabricante Pioridade Eixos Categoria TA\n");
	textcolor(15);
	tpElemento e,aux;
	tpFilaPrioridade filas[ativo];
	atendimento cabine[ativo];
	

	for(int f=0; f<ativo; f++){
		Inicializar(filas[f]);
		cabine[f].ta=0;
	}

	if(ativo>1)
		cabine[ativo-1].viaFacil = true;
	
	// A cabine de via facil o tempo de atendimento é igual a 1, não importando o ta que vem da fila
	printf("\nVia facil: CABINE[%d]\n",ativo);
	while(flag==1){
		
		if(UT>=utEntrada){
			
			if(!feof(ptr) && UT%utEntrada==0){
				if(i==ativo || ativo==1)
					i=0;
				fscanf(ptr,"%[^;];%[^;];%[^;];%d;%d;%[^;];%d\n",&e.placa,&e.cor,&e.fabricante,&e.Prioridade,&e.eixos,&e.categoria,&e.ta);
				Inserir(filas[i],e);
				textcolor(10);
				printf(" FILA[%d] Novo veiculo inserido: %s TA:%d Prioridade: %d\tUT=%d\n",i+1,e.placa,e.ta,e.Prioridade,UT);
				textcolor(15);
				i++;
			}
			
			for(int j=0;j<ativo;j++){
				if(cabine[j].ta==0){
					if(!Vazia(filas[j].cont)){
						aux = Retirar(filas[j]);
						//printf("\n%s %d %d  J=%d",aux.placa,aux.Prioridade,aux.ta,j);
						strcpy(cabine[j].placa,aux.placa);
						strcpy(cabine[j].cor,aux.cor);
						strcpy(cabine[j].fabricante,aux.fabricante);
						cabine[j].prioridade = aux.Prioridade;
						cabine[j].eixos = aux.eixos;
						strcpy(cabine[j].categoria,aux.categoria);
						cabine[j].ta = aux.ta;
						tempoTotal+=aux.ta;
						
						if(strcmp(aux.categoria,"caminhao")==0)
							cabine[j].caminhao++;
						else
						if(strcmp(aux.categoria,"moto")==0)
							cabine[j].moto++;
						else
						if(strcmp(aux.categoria,"passeio")==0)
							cabine[j].passeio++;	
							
						if(cabine[j].viaFacil == true)
							cabine[j].ta = 1;	
						cont++;
					}
				}
				else
					cabine[j].ta--;		
			}
			if(UT==60){
				for(int b=0;b<ativo;b++)
					totalHora+=cabine[b].caminhao + cabine[b].moto + cabine[b].caminhao;
			}
			
			int separar = 0;
			for(int g=0;g<ativo;g++){
				if(cabine[g].ta==1)
					textcolor(12);			
				if(cabine[g].ta >=1 && cabine[g].viaFacil == false){
					printf("\nCABINE[%d]: %s %s %s %d %d %s %d",g+1,cabine[g].placa,cabine[g].cor,cabine[g].fabricante,cabine[g].prioridade,cabine[g].eixos,cabine[g].categoria,cabine[g].ta);
					separar++;
				}
				if(cabine[g].viaFacil == true && cabine[g].ta >=1)
					printf("\nCABINE[%d][Sem parar]: %s %s %s %d %d %s %d",g+1,cabine[g].placa,cabine[g].cor,cabine[g].fabricante,cabine[g].prioridade,cabine[g].eixos,cabine[g].categoria,cabine[g].ta);
				textcolor(15);	
			}
			if(separar>0)
				printf("\n=========================================");
			
			int m=0;
			if(feof(ptr)){
				for(int v=0;v<ativo;v++){
					if(Vazia(filas[v].cont) && cabine[v].ta==0)
						m++;
				}
			
				if(m==ativo)
					flag=0;
				else
					flag=1; 
			}

		}	
		UT++;
	}
	
	for(int j=0;j<ativo;j++){
		printf("\nTotal de motos que passaram pela cabine %d: %d",j+1,cabine[j].moto);
		printf("\nTotal de caminhoes que passaram pela cabine %d: %d",j+1,cabine[j].caminhao);
		printf("\nTotal de carros que passaram pela cabine %d: %d",j+1,cabine[j].passeio);
		printf("\n------------------------------");
		totalCaminhao+=cabine[j].caminhao;
		totalPasseio+=cabine[j].passeio;
		totalMoto+=cabine[j].moto;
	}
	printf("\nTotal de motos que passaram pelo pedagio: %d",totalMoto);
	printf("\nTotal de caminhoes que passaram pelo pedagio: %d",totalCaminhao);
	printf("\nTotal de carros que passaram pelo pedagio: %d",totalPasseio);
	
	printf("\n\nTempo medio de espera para sair do pedagio: %d",(tempoTotal/cont));
	printf("\nTotal de veiculos que passaram pelo pedagio: %d",cont);
	printf("\nTotal de veiculos que passou pelo pedagio durante a primeira hora: %d",totalHora);
	printf("\n\t(1 hora e igual a 60 UTs)");
	fclose(ptr);
	getch();
}

int main(){
	char op;
	do
	{
		clrscr();
		printf("[S] Simular: \n");
		printf("[T] Cabines [4]: \n");
		
		
		op=toupper(getch());fflush(stdin);
		switch(op)
		{				
			case'S':clrscr();simulacao();break;
			case'T':clrscr();cabines4();break;
			case 27: printf("sair");break;
		}
		getch();
	}while(op!=27);
}
