#include <stdio.h>
#include <string.h>

typedef enum {
	RRHH=1,
	CONSULTORIA=2,
	DISENO=3,
	PRODUCCION=4,//departamento de trabajadores
	CALIDAD=5,
	DISTRIBUCION=6 
}departamento;

typedef enum cargos{
	GERENTE=1,
	SUPERVISOR=2,
	ANALISTA=3,
	DISENADOR=4,//cargos de trabajadores
	DESARROLLADOR=5,
	AUDITOR=6 
}cargos_t;

typedef struct 
{
	int dia;
	int mes; //fecha de ingreso
	int ano; 
}FECHA;

typedef struct {
	
	int CI;
	char nombre[20];
	char apellido[20];	//datos empleados   
	float sueldo;
	FECHA fecha;	
}empleado;

//prototipo; 1.modulo empresa
void ingresar(empleado empleados[], int empl, FILE* ARCH);
void departamentos(char* depar[]); // funcion que llena el campo departamento
void cargos (char* cargo[]); // funcion que llena el campo cargo
int validarFecha(int dia,int mes,int ano);

//pototipos; 2.modulo consulta
void menuDeOpciones();
void consultaPorCi();
void CONSULTAporDEPA();
void CONSULTAporCARGO();
void contarDepa(int* emple, float* sueldo, char depa[20]);
void contarCargo(int* eEMPLE, float* SUELDOS, char cargo[20]);
//void sueldoMayorMenor();
//programa principal
int main(){
	empleado empleados[2000];
	FILE* trabajadores;
	int lim;
	char op;
	if((trabajadores=fopen("trabajadores.in","a+"))==NULL){
		printf("\nError no se pudo abrir el archivo");
		return 0;
		
	}else{
		
		do{
			printf("\n===============================================\n\n");
			printf("\n  |     BIEN VENIDO A EL GESTOR DE EMPLEADOS    |\n");
			printf("  |           [1] INGRESAR                      |\n");
			printf("  |           [2] CONSULTAR                     |\n");
			printf("  |           [3] MODIFICAR                     |\n");
			printf("  |           [4] ELIMINAR                      |\n");
			printf("  |           [5] SALIR                         |\n");
			printf("\n===============================================\n\n");
			printf("OPCION: ");
			scanf("%s",&op); // se a puesto las opciones tipo caracter para que no hayan errores en caso que se ingrese un caracter en vez de un entero
			switch (op){
				case '1':
					//este caso ingresa los empleados a un archivo .in 
					do{
						printf("\nIngrese la cantidad de personas que desa ingresar: ");
						scanf("%d", &lim);	    
					}while(lim>2000);
					ingresar(empleados,lim,trabajadores);
					fclose(trabajadores);
				break;
				case '2':
					fclose(trabajadores);
					menuDeOpciones();
				break;
				case '3':
				break;
				case '4':
				break;
				case '5':
					printf("\n\n============================\n\n");
					printf("    |   ADIOS, VUELVA PRONTO :) |  ");
					printf("\n\n============================\n\n");
				
				break; 
			default:
					printf("\n\n\n===============================================\n\n");
					printf("     |   ESTOY SEGURO QUE ESTO %s NO ES UNA OPCION |  ",op);
					printf("\n\n=============================================\n\n\n");
				break;
			}

		}while(op!='5');
		fclose(trabajadores);
	}
	
	
	
	
	
	
	return 0;
}
/*
1. modulo ingresar
Permite registrar la informaci�n de nuevos trabajadores, de acuerdo a los datos indicados 
previamente, a partir de un n�mero n indicado por el usuario. Toda la informaci�n se almacena en un archivo 
llamado trabajadores.in, cada nuevo registro se ubica al final de este archivo
*/
void ingresar(empleado empleados[],int empl, FILE* ARCH){
	int i,valFecha=0;
	char cargo[20];
	char depa[20];
	for (i=1;i<=empl;i++){
		printf("\nIngresa CI del empleado: ");
		scanf("%d", &empleados[i].CI);
		fprintf(ARCH,"\n%d\t\t", empleados[i].CI); //ingresando en el archivo 
		
		printf("\nIngresa Nombre del empleado: ");
		scanf("%s", &empleados[i].nombre);
		fprintf(ARCH,"%s", empleados[i].nombre);
		
		printf("\nIngresa Apellido del empleado: ");
		scanf("%s", &empleados[i].apellido);
		fprintf(ARCH," %s\t\t", empleados[i].apellido);
		
		departamentos(&depa); // funcion que llena el campo departamento
		fprintf(ARCH,"%s\t\t", depa);
		cargos(&cargo); // funcion que llena el campo cargos
		fprintf(ARCH,"%s\t\t",cargo);

		do{
			printf("\nIngresa la fecha que ingreso a la empresa en formato DD/MM/AA: \n");
			printf("Dia: "); scanf("%d",&empleados[i].fecha.dia);
			printf("\nMes: "); scanf("%d",&empleados[i].fecha.mes);
			printf("\nAno: "); scanf("%d",&empleados[i].fecha.ano);
			valFecha=validarFecha(empleados[i].fecha.dia,empleados[i].fecha.mes,empleados[i].fecha.ano);
		}while(valFecha !=1);
		if (valFecha == 1){
			fprintf(ARCH,"%d/%d/%d\t\t", empleados[i].fecha.dia,empleados[i].fecha.mes,empleados[i].fecha.ano);
		}
		printf("Salario: ");scanf("%f",&empleados[i].sueldo);
		fprintf(ARCH," %.3f\t\t ", empleados[i].sueldo);
		
		
	}
}

//funcion que llena el campo de partamento
void departamentos(char* depar[]){
	
	int depa;
	do{
		printf("\nIngrese el departamento que pertenece: ");
		printf("\n1.RRHH");
		printf("\n2.CONSULTORIA");
		printf("\n3.DISENO");
		printf("\n4.PRODUCCION");
		printf("\n5.CALIDAD");
		printf("\n6.DISTRIBUCION\n");
		scanf("%d", &depa);
		switch(depa){
			case RRHH:
				strcpy(depar,"RRHH");
			break;
			case CONSULTORIA:
				strcpy(depar,"CONSULTORIA");
			break;
			case DISENO:
				strcpy(depar,"DISENO");
			break;
			case PRODUCCION:
				strcpy(depar,"PRODUCCION");
			break;
			case CALIDAD:
				strcpy(depar,"CALIDAD");
			break;
			case DISTRIBUCION:
				strcpy(depar,"DISTRIBUCION");
			break;
				
		}
			
	}while ((depa!=1) && (depa!=2) && (depa!=3) && (depa!=4) && (depa!=5) && (depa!=6));
}
//funcion que llena el campo cargo
void cargos(char* cargo[]){
	int CARGOS;
	do{
		printf("\nIngrese el cargo que pertene: ");
		printf("\n1.GERENTE");
		printf("\n2.SUPERVISOR");
		printf("\n3.ANALISTA");
		printf("\n4.DISENADOR");
		printf("\n5.DESARROLLADOR");
		printf("\n6.AUDITOR\n");
		scanf("%d",&CARGOS);
		switch(CARGOS){
			case GERENTE:
				strcpy(cargo,"GERENTE");
			break;
			case SUPERVISOR:
					strcpy(cargo,"SUPERVISOR");
			break;
			case ANALISTA:
					strcpy(cargo,"ANALISTA");
			break;
			case DISENADOR:
				strcpy(cargo,"DISENADOR");
			break;
			case DESARROLLADOR:
				strcpy(cargo,"DESARROLLADOR");
			break;
			case AUDITOR:
				strcpy(cargo,"AUDITOR");
			break;
			
		}
	}while ((CARGOS!=1) && (CARGOS!=2) && (CARGOS!=3) && (CARGOS!=4) && (CARGOS!=5) && (CARGOS!=6));
}

int validarFecha(int dia,int mes,int ano){
	if((mes>=1) && (mes<=12)){
		switch (mes){
			case  1 :
            case  3 :
            case  5 :
            case  7 :
            case  8 :
            case 10 :
            case 12 :
				if((dia>=1) && (dia<=31)){
					return 1;
				}
			break;
			case  4 :
            case  6 :
            case  9 :
            case 11 :
				if((dia>=1) && (dia<=31)){
					return 1;
				}
			break;
			case 2:
				if((ano % 4 == 0) && (ano % 100 !=0)){
					if((dia>=1) && (dia<=29)){
						return 1;
					}
				}else {
					if((dia>=1) && (dia<=28)){
						return 1;
					}
				}
			break;
		}
	}else{
		return 0;
	}


}


//menu de opciones de el modulo dos
void menuDeOpciones(){
	char op;
	
	do{
		printf("\n===============================================================\n\n");
		printf("\n  |     	BIEN VENIDO A EL GESTOR DE EMPLEADOS          |\n");
		printf("  |           [a] CONSULTA POR CI                      		|\n");	
		printf("  |           [b] CONSULTA POR DEPARTAMNETO                    	|\n");
		printf("  |           [c] CONSULTA POR CARGO                     	|\n");
		printf("  |           [d] MENOR Y MAYOR SUELDO                    	|\n");
		printf("  |           [f] SALIR                         	        |\n");
		printf("\n===============================================================\n\n");
		printf("OPCION: ");
		scanf("%s",&op);
		switch (op){
		case 'a':
			consultaPorCi();
		break;
		case 'b':
			CONSULTAporDEPA();
		break;
		case 'c':
			CONSULTAporCARGO();
		break;
		case 'd':
			
		break;
		case 'f':
		break;
		default:
			printf("\n\n\n===============================================\n\n");
			printf("     |   ESTOY SEGURO QUE ESTO %s NO ES UNA OPCION |  ",op);
			printf("\n\n=============================================\n\n\n");
		}

	}while(op!='f');
			



}
/*consulta  por CI muestra al empleado que esta asociado con esa CI*/
void consultaPorCi(){
	FILE* ARCHConsulta;
	empleado empleados;
	int ci;
	char cargo[20], depa[20],fecha[20];
	ARCHConsulta=fopen("trabajadores.in","a+"); //se tuvo que abrir y cerrar el archivo en una nueva funcion porque me daba conflicto pasandolo por parametro
	if(ARCHConsulta == NULL){
		printf("NO SE ENCONTRO ARCHIVO");
		return 0;
	}
	printf("|   BUSCAR EMPLEADO\nINGRESE LA CI:   ");
	scanf("%d",&ci);
	while((!(feof(ARCHConsulta))) && (empleados.CI!=ci)){
		fscanf(ARCHConsulta,"%d", &empleados.CI);
		fscanf(ARCHConsulta,"%s",empleados.nombre);
		fscanf(ARCHConsulta,"%s",empleados.apellido);
		fscanf(ARCHConsulta,"%s",cargo);
		fscanf(ARCHConsulta,"%s",depa);
		fscanf(ARCHConsulta,"%s",fecha);
		fscanf(ARCHConsulta,"%f",&empleados.sueldo);
	}
	if(empleados.CI == ci){
		printf("La CI es: %d \n",empleados.CI);
		printf("El nombre es: %s \n",empleados.nombre);
		printf("El apellido es: %s \n",empleados.apellido);
		printf("El cargo es: %s \n",cargo);
		printf("El departamento es: %s \n",depa);
		printf("La fecha de ingreso es: %s \n",fecha);
		printf("El sueldo es: %.2f \n",empleados.sueldo);
	}else{
		printf("\nLA CI INDICADA NO ESTA ASOCIADA A NINGUN TRABAJADOR DE LA EMPRESA\n");
	}

	fclose(ARCHConsulta);


}

/*consulta  por numero de departamaneto y cuenta cuantos hay ahí 
genera un archivo con el total de trabajadores y sueldo que hay por todos los trabajadores*/

void CONSULTAporDEPA(){
	FILE* ARCHdepa;
	empleado empleados;
	int depa;
	int conTrabajadores=0;
	float sueldos=0;
	
	ARCHdepa=fopen("departamentos.txt","a+");
	if(ARCHdepa == NULL){
		printf("NO SE ENCONTRO ARCHIVO");
		return;
	}
	do{	
		printf("\nIngrese el departamento que pertenece: ");
		printf("\n1.RRHH");
		printf("\n2.CONSULTORIA");
		printf("\n3.DISENO");
		printf("\n4.PRODUCCION");
		printf("\n5.CALIDAD");
		printf("\n6.DISTRIBUCION");
		printf("\n7.SALIR\n");
		scanf("%d",&depa);
		switch (depa){
			case RRHH:
				contarDepa(&conTrabajadores,&sueldos,"RRHH");		
				printf("\n\nPersonal RRHH: %d\nTotal sueldos: %.2f",conTrabajadores,sueldos);
				fprintf(ARCHdepa,"departamento RRHH: %d \nsueldos %.2f",conTrabajadores,sueldos);
				fprintf(ARCHdepa,"%s","\n==================================\n");
				conTrabajadores=0;
				sueldos=0;
			break;
			case CONSULTORIA:
				contarDepa(&conTrabajadores,&sueldos,"CONSULTORIA");		
				printf("\n\nPersonal CONSULTORIA: %d\nTotal sueldos: %.2f",conTrabajadores,sueldos);
				fprintf(ARCHdepa,"departamento CONSULTORIA: %d \nsueldos %.2f",conTrabajadores,sueldos);
				fprintf(ARCHdepa,"%s","\n==================================\n");
				conTrabajadores=0;
				sueldos=0;
			break;
			case DISENO:
				contarDepa(&conTrabajadores,&sueldos,"DISENO");
				printf("\n\nPersonal DISENO: %d\nTotal sueldos: %.2f",conTrabajadores,sueldos);
				fprintf(ARCHdepa,"departamento DISENO: %d \nsueldos %.2f",conTrabajadores,sueldos);
				fprintf(ARCHdepa,"%s","\n==================================\n");
				conTrabajadores=0;
				sueldos=0;

			break;
			case PRODUCCION:
				contarDepa(&conTrabajadores,&sueldos,"PRODUCCION");
				printf("\n\nPersonal PRODUCCION: %d\nTotal sueldos: %.2f",conTrabajadores,sueldos);
				fprintf(ARCHdepa,"departamento PRODUCCION: %d \nsueldos %.2f",conTrabajadores,sueldos);
				fprintf(ARCHdepa,"%s","\n==================================\n");
				conTrabajadores=0;
				sueldos=0;

			break;
			case CALIDAD:
				contarDepa(&conTrabajadores,&sueldos,"CALIDAD");
				printf("\n\nPersonal CALIDAD: %d\nTotal sueldos: %.2f",conTrabajadores,sueldos);
				fprintf(ARCHdepa,"departamento CALIDAD: %d \nsueldos %.2f",conTrabajadores,sueldos);
				fprintf(ARCHdepa,"%s","\n==================================\n");
				conTrabajadores=0;
				sueldos=0;
			break;
			case DISTRIBUCION:
				contarDepa(&conTrabajadores,&sueldos,"DISTRIBUCION");
				printf("\n\nPersonal DISTRIBUCION: %d\nTotal sueldos: %.2f",conTrabajadores,sueldos);
				fprintf(ARCHdepa,"departamento DISTRIBUCION: %d \nsueldos %.2f",conTrabajadores,sueldos);
				fprintf(ARCHdepa,"%s","\n==================================\n");
				conTrabajadores=0;
				sueldos=0;

			break;
			default:
				printf("\nOPCION INVALIDA");
			
		}

	}while (depa!=7);

	fclose(ARCHdepa);

}
void contarDepa(int* emple, float* sueldo,char depa[20]){

	FILE* ARCHConsulta;
	empleado empleados;
	int sueldos=0;
	char cargo[20],fecha[20],departa[20];
	ARCHConsulta=fopen("trabajadores.in","a+");
	if(ARCHConsulta==NULL){
		printf("\NO SE ENCONTRO ARCHIVO\N");
		return ;
	}
	while(!(feof(ARCHConsulta))){
			fscanf(ARCHConsulta,"%d", &empleados.CI);
			fscanf(ARCHConsulta,"%s",empleados.nombre);
			fscanf(ARCHConsulta,"%s",empleados.apellido);
			fscanf(ARCHConsulta,"%s",departa);	
			fscanf(ARCHConsulta,"%s",cargo);
			fscanf(ARCHConsulta,"%s",fecha);
			fscanf(ARCHConsulta,"%f",&empleados.sueldo);
			if(strcmp(depa,departa)==0){ //comparamos cadenas para saber hacer el conteo;
				*emple+=1;
				sueldos=empleados.sueldo;
				*sueldo+=sueldos;
			}
	}
	fclose(ARCHConsulta);

}
void CONSULTAporCARGO(){
	FILE* ARCHcargo;
	empleado empleados;
	int CARGOS;
	int conTrabajadores=0;
	float sueldos=0;
	ARCHcargo=fopen("cargo.txt","a+");
	if(ARCHcargo == NULL){
		printf("NO SE ENCONTRO ARCHIVO");
		return;
	}
	
	do{
		printf("\nIngrese el cargo que pertene: ");
		printf("\n1.GERENTE");
		printf("\n2.SUPERVISOR");
		printf("\n3.ANALISTA");
		printf("\n4.DISENADOR");
		printf("\n5.DESARROLLADOR");
		printf("\n6.AUDITOR");
		printf("\n7.SALIR\n");
		scanf("%d",&CARGOS);
		switch(CARGOS){
			case GERENTE:
				contarCargo(&conTrabajadores,&sueldos,"GERENTE");
				printf("\nPersonal GERENTE: %d\nTotal de sueldo es: %.2f",conTrabajadores,sueldos);
				fprintf(ARCHcargo,"\nCargo GERENTE: %d\SUELDOS: %.2f",conTrabajadores,sueldos);
				fprintf(ARCHcargo,"%s","\n==================================\n");
				conTrabajadores=0;
				sueldos=0;
			break;
			case SUPERVISOR:
				contarCargo(&conTrabajadores,&sueldos,"SUPERVISOR");
				printf("\nPersonal SUPERVISOR: %d\nTotal de sueldo es: %.2f",conTrabajadores,sueldos);
				fprintf(ARCHcargo,"\nCargo SUPERVISOR: %d\SUELDOS: %.2f",conTrabajadores,sueldos);
				fprintf(ARCHcargo,"%s","\n==================================\n");
				conTrabajadores=0;
				sueldos=0;
			break;
			case ANALISTA:
				contarCargo(&conTrabajadores,&sueldos,"ANALISTA");
				printf("\nPersonal ANALISTA: %d\nTotal de sueldo es: %.2f",conTrabajadores,sueldos);
				fprintf(ARCHcargo,"\nCargo ANALISTA: %d\SUELDOS: %.2f",conTrabajadores,sueldos);
				fprintf(ARCHcargo,"%s","\n==================================\n");
				conTrabajadores=0;
				sueldos=0;

			break;
			case DISENADOR:
				contarCargo(&conTrabajadores,&sueldos,"DISENADOR");
				printf("\nPersonal DISENADOR: %d\nTotal de sueldo es: %.2f",conTrabajadores,sueldos);
				fprintf(ARCHcargo,"\nCargo DISENADOR: %d\SUELDOS: %.2f",conTrabajadores,sueldos);
				fprintf(ARCHcargo,"%s","\n==================================\n");
				conTrabajadores=0;
				sueldos=0;
			break;
			case DESARROLLADOR:
				contarCargo(&conTrabajadores,&sueldos,"DESARROLLADOR");
				printf("\nPersonal DESARROLLADOR: %d\nTotal de sueldo es: %.2f",conTrabajadores,sueldos);
				fprintf(ARCHcargo,"\nCargo DESARROLLADOR: %d\SUELDOS: %.2f",conTrabajadores,sueldos);
				fprintf(ARCHcargo,"%s","\n==================================\n");
				conTrabajadores=0;
				sueldos=0;
				
			break;
			case AUDITOR:
				contarCargo(&conTrabajadores,&sueldos,"AUDITOR");
				printf("\nPersonal AUDITOR: %d\nTotal de sueldo es: %.2f",conTrabajadores,sueldos);
				fprintf(ARCHcargo,"\nCargo AUDITOR: %d\SUELDOS: %.2f",conTrabajadores,sueldos);
				fprintf(ARCHcargo,"%s","\n==================================\n");
				conTrabajadores=0;
				sueldos=0;
			break;
			default:
				printf("\nOPCION INVALIDA");
			
		}
	}while (CARGOS!=7);

	fclose(ARCHcargo);
}

void contarCargo(int* EMPLE, float* sueldos, char cargo[20]){
	FILE* ARCHcargo;
	empleado empleados;
	int sueldo=0;
	char E_cargo[20],fecha[20],departa[20];
	ARCHcargo=fopen("trabajadores.in","a+");
	if(ARCHcargo == NULL){
		printf("\nNO SE ENCONTRO ARCHIVO\n");
	}
	while(!(feof(ARCHcargo))){
		fscanf(ARCHcargo,"%d", &empleados.CI);
		fscanf(ARCHcargo,"%s",empleados.nombre);
		fscanf(ARCHcargo,"%s",empleados.apellido);
		fscanf(ARCHcargo,"%s",departa);	
		fscanf(ARCHcargo,"%s",E_cargo);
		fscanf(ARCHcargo,"%s",fecha);
		fscanf(ARCHcargo,"%f",&empleados.sueldo);
		if(strcmp(cargo,E_cargo)==0){
			*EMPLE+=1;
			sueldo=empleados.sueldo;
			*sueldos+=sueldo;
		}
	}
	fclose(ARCHcargo);

}


