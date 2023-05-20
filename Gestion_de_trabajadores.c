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

typedef enum{
	Traslado='1',
	Renuncia='2', // motivos de renuncia para los trabajadores
	Despido='3',
	Otro='4'
}motivoDespido;

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
void ingresar(empleado empleados[], int empl, FILE* ARCH);//funcion que ingresa los empleados
void departamentos(FILE* deparARCH); // funcion que llena el campo departamento
void cargos (FILE* cargARCH); // funcion que llena el campo cargo
int validarFecha(int dia,int mes,int ano); //funcion que valida las fechas
int verificarUsuario(int ci,FILE* archi); //funcion que valida la CI
//pototipos; 2.modulo consulta
void menuDeOpciones();
void consultaPorCi();
void CONSULTAporDEPA();
void CONSULTAporCARGO();
void contarDepa(int* emple, float* sueldo, char depa[20]);
void contarCargo(int* eEMPLE, float* SUELDOS, char cargo[20]);
void sueldoMayorMenor();
// prototipos: 3. modulo modificar
void modificar();
//prototipos: 4.modulo eliminar
void eliminar();
void exTrabajadores(empleado emple, char cargo[20],char depa[20]);
//programa principal
int main(){
	empleado empleados[2000];
	FILE* trabajadores;
	int lim;
	char op;
	//verificar que el documento abrio perfectamente
	if((trabajadores=fopen("trabajadores.in","a+"))==NULL){
		printf("\nError, no se pudo abrir el archivo");
		
	}else{
		//imprimir menu
		do{
			printf("\n===============================================\n\n");
			printf("\n  |     BIENVENIDO AL GESTOR DE EMPLEADOS    |\n");
			printf("  |           [1] INGRESAR                      |\n");
			printf("  |           [2] CONSULTAR                     |\n");
			printf("  |           [3] MODIFICAR                     |\n");
			printf("  |           [4] ELIMINAR                      |\n");
			printf("  |           [5] SALIR                         |\n");
			printf("\n===============================================\n\n");
			printf("OPCION: ");
			fflush(stdin);
			scanf("%s",&op); // se ha puesto las opciones tipo caracter para que no hayan errores en caso que se ingrese un caracter en vez de un entero
			switch (op){
				case '1':
					//este caso ingresa los empleados a un archivo .in 
					do{
						printf("\nIngrese la cantidad de personas que desea ingresar: ");
						scanf("%d", &lim);	    
					}while(lim>2000);
					ingresar(empleados,lim,trabajadores);
					fclose(trabajadores);
				break;
				case '2':
					//consulta a los trabajadores
					
					menuDeOpciones();
					fclose(trabajadores);
				break;
				case '3':
					//modificacion de los trabajadores
					fclose(trabajadores);
					modificar();
					remove("trabajadores.in");//eliminamos el archivo viejo
					rename("trabajadores2.in","trabajadores.in");//reasignamos el nombre del archivo principal al secundario
				break;
				case '4':
					//eliminar trabajadores
					fclose(trabajadores);
					eliminar();
					remove("trabajadores.in");
					rename("trabajadores3.in","trabajadores.in");
				break;
				case '5':
					printf("\n\n============================\n\n");
					printf("    |   ADIOS, VUELVA PRONTO :) |  ");
					printf("\n\n============================\n\n");
				
				break; 
			default:
					printf("\n\n\n===============================================\n\n");
					printf("     |   ESTOY SEGURO QUE ESTO %c NO ES UNA OPCION |  ",(char)op);
					printf("\n\n=============================================\n\n\n");
				break;
			}

		}while(op!='5');
		fclose(trabajadores);
	}
	
	
	
	
	
	
	
	return 0;
}
/*1. modulo ingresar
Permite registrar la informacion de nuevos trabajadores, de acuerdo a los datos indicados 
previamente, a partir de un numero n indicado por el usuario. Toda la informacion se almacena en un archivo 
llamado trabajadores.in, cada nuevo registro se ubica al final de este archivo
*/
void ingresar(empleado empleados[],int empl, FILE* ARCH){
	int i,valFecha=0;
	int band;
	for (i=1;i<=empl;i++){
		//guardamos la cedula del empleado en el archivo
		do{
			printf("\nIngresa CI del empleado: ");
			scanf("%d", &empleados[i].CI);  
			band=verificarUsuario(empleados[i].CI,ARCH); // verificar que la CI no está 
			if(band==1){
			printf("\n\nLA CI YA SE ENCUENTRA ASOCIADA A UN TRABAJADOR\n\n");
			}
		}while(band==1);
		fprintf(ARCH,"%d\t\t", empleados[i].CI);//ingresando en el archivo 
		
		//guardamos el nombre del empleado en el archivo
		printf("\nIngresa Nombre del empleado: ");
		scanf("%s", empleados[i].nombre);
		fprintf(ARCH,"%s", empleados[i].nombre);
		//guardamos el apellido del empleado en el archivo
		printf("\nIngresa Apellido del empleado: ");
		scanf("%s", empleados[i].apellido);
		fprintf(ARCH," %s\t\t", empleados[i].apellido);
		
		departamentos(ARCH); // funcion que llena el campo departamento
		cargos(ARCH); // funcion que llena el campo cargos

		//pedimos al usuario su fecha de ingreso y validamos que sea correcta, si es asi la guardamos en el archivo trabajadores.in
		do{
			printf("\nIngresa la fecha que ingreso a la empresa en formato DD/MM/AA: \n");
			printf("Dia: "); fflush(stdin);scanf("%d",&empleados[i].fecha.dia);
			printf("\nMes: "); fflush(stdin);scanf("%d",&empleados[i].fecha.mes);
			printf("\nAno: ");fflush(stdin); scanf("%d",&empleados[i].fecha.ano);
			valFecha=validarFecha(empleados[i].fecha.dia,empleados[i].fecha.mes,empleados[i].fecha.ano);
		}while(valFecha !=1);
		if (valFecha == 1){
			fprintf(ARCH,"%d/%d/%d\t\t", empleados[i].fecha.dia,empleados[i].fecha.mes,empleados[i].fecha.ano);
		}
		//pedimos el sueldo del trabajador para ingresarlo en trabajadores.in y sera formateada con 3 decimales
		printf("\nSalario: ");scanf("%f",&empleados[i].sueldo);
		fprintf(ARCH," %5.3f\n", empleados[i].sueldo);
		
		
	}
}
//verificar que el campo CI no este asociado
int verificarUsuario(int ci,FILE* archi){
	char depa[20],cargo[20],fecha[20];
	empleado emple;
	int band=0;
	while (!(feof(archi)) && (emple.CI!=ci)){
		fscanf(archi,"%d", &emple.CI);
		fscanf(archi,"%s", emple.nombre);
		fscanf(archi,"%s", emple.apellido);
		fscanf(archi,"%s", depa);
		fscanf(archi,"%s",cargo);
		fscanf(archi,"%s", fecha);
		fscanf(archi,"%f", &emple.sueldo);	
		if(emple.CI==ci){
		band=1;
		}
	}

	return band;
}

//funcion que llena el campo de partamento
void departamentos(FILE* deparARCH){
	
	int depa;
	//menu para llenar los datos del departamento del empleado

	do{
		printf("\nIngrese el departamento que pertenece: ");
		printf("\n1.RRHH");
		printf("\n2.CONSULTORIA");
		printf("\n3.DISENO");
		printf("\n4.PRODUCCION");
		printf("\n5.CALIDAD");
		printf("\n6.DISTRIBUCION\n");
		fflush(stdin);
		scanf("%d", &depa);
		switch(depa){
			case RRHH:
				fprintf(deparARCH,"%s\t", "RRHH");
			break;
			case CONSULTORIA:
				fprintf(deparARCH,"%s\t", "Consultoria");
			break;
			case DISENO:
				fprintf(deparARCH,"%s\t", "Diseno");
			break;
			case PRODUCCION:
				fprintf(deparARCH,"%s\t", "Produccion");
			break;
			case CALIDAD:
				fprintf(deparARCH,"%s\t", "Calidad");
			break;
			case DISTRIBUCION:
				fprintf(deparARCH,"%s\t", "Distribucion");
			break;
				
		}
			
	}while ((depa!=1) && (depa!=2) && (depa!=3) && (depa!=4) && (depa!=5) && (depa!=6));
}
//funcion que llena el campo cargo
void cargos(FILE* cargARCH){
	int CARGOS;
	//menu para llenar los datos del cargo del empleado
	do{
		printf("\nIngrese el cargo que pertenece: ");
		printf("\n1.GERENTE");
		printf("\n2.SUPERVISOR");
		printf("\n3.ANALISTA");
		printf("\n4.DISENADOR");
		printf("\n5.DESARROLLADOR");
		printf("\n6.AUDITOR\n");
		fflush(stdin);
		scanf("%d",&CARGOS);
		switch(CARGOS){
			case GERENTE:
				fprintf(cargARCH,"%s\t","Gerente");
			break;
			case SUPERVISOR:
				fprintf(cargARCH,"%s\t","Supervisor");
			break;
			case ANALISTA:
					fprintf(cargARCH,"%s\t","Analista");
			break;
			case DISENADOR:
				fprintf(cargARCH,"%s\t","Disenador");
			break;
			case DESARROLLADOR:
				fprintf(cargARCH,"%s\t","Desarrollador");
			break;
			case AUDITOR:
				fprintf(cargARCH,"%s\t","Auditor");
			break;
			
		}
	}while ((CARGOS!=1) && (CARGOS!=2) && (CARGOS!=3) && (CARGOS!=4) && (CARGOS!=5) && (CARGOS!=6));
}
//validamos la fecha
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
				if((dia>=1) && (dia<=30)){
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
	}

		return 0;
}


//menu de opciones de el modulo dos
void menuDeOpciones(){
	char op;
	//imprimimos menu para preguntar al usuario que tipo de busqueda quiere hacer

	do{
		printf("\n===============================================================\n\n");
		printf("\n  |     	BIENVENIDO A EL GESTOR DE EMPLEADOS          |\n");
		printf("  |           [a] CONSULTA POR CI                      		|\n");	
		printf("  |           [b] CONSULTA POR DEPARTAMNETO                    	|\n");
		printf("  |           [c] CONSULTA POR CARGO                     	|\n");
		printf("  |           [d] MENOR Y MAYOR SUELDO                    	|\n");
		printf("  |           [f] SALIR                         	        |\n");
		printf("\n===============================================================\n\n");
		printf("OPCION: ");
		fflush(stdin);
		scanf("%s",&op);
		switch (op){
		case 'a':
			//opcion para consultar por la cedula del empleado
			consultaPorCi();
		break;
		case 'b':
			//opcion para consultar por el departamento del empleado
			CONSULTAporDEPA();
		break;
		case 'c':
			//opcion para consultar por el cargo del empleado
			CONSULTAporCARGO();
		break;
		case 'd':
			//consultar empleado con mayor y menor sueldo 
			sueldoMayorMenor();
		break;
		case 'f':
		 //salir
		 return;
		break;
		default:
			printf("\n\n\n===============================================\n\n");
			printf("     |   ESTOY SEGURO QUE ESTO %c NO ES UNA OPCION |  ",(char)op);
			printf("\n\n=============================================\n\n\n");
		}

	}while(op!='f');
			



}
/*consulta  por CI muestra al empleado que esta asociado con esa CI*/
void consultaPorCi(){
	//abrimos el archivo y la estructura empleados y variables para los demas datos de dicha estructura
	FILE* ARCHConsulta;
	empleado empleados;
	int ci;
	char cargo[20], depa[20],fecha[20];
	ARCHConsulta=fopen("trabajadores.in","a+"); //se tuvo que abrir y cerrar el archivo en una nueva funcion porque me daba conflicto pasandolo por parametro
	if(ARCHConsulta == NULL){
		printf("NO SE ENCONTRO ARCHIVO");
		return ;
	}
	//pedimos al usuario la cedula
	printf("|   BUSCAR EMPLEADO\nINGRESE LA CI:   ");
	scanf("%d",&ci);
	//iniciamos el ciclo de busqueda mientras no sea el final del archivo y no haya una ocurrencia en la cedula

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
		//si encuentra la cedula la imprimimos por pantalla
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

/*consulta por numero de departamento y cuenta cuantos hay ahí,
genera un archivo con el total de trabajadores y sueldo que hay por todos los trabajadores*/
void CONSULTAporDEPA(){
	//abrimos el archivo y las variables que vamos a utilizar
	FILE* ARCHdepa;
	int depa;
	int conTrabajadores=0;
	float sueldos=0;
	
	ARCHdepa=fopen("departamentos.txt","a+");
	if(ARCHdepa == NULL){
		printf("NO SE ENCONTRO ARCHIVO");
		return;
	}
	//menu para preguntar en cual departamento quiere buscar

	do{	
		printf("\nIngrese el departamento que pertenece: ");
		printf("\n1.RRHH");
		printf("\n2.CONSULTORIA");
		printf("\n3.DISENO");
		printf("\n4.PRODUCCION");
		printf("\n5.CALIDAD");
		printf("\n6.DISTRIBUCION\n");
		fflush(stdin);
		scanf("%d",&depa);
		switch (depa){
			case RRHH:
				contarDepa(&conTrabajadores,&sueldos,"RRHH");		
				printf("\n\nPersonal RRHH: %d\nTotal sueldos: %.2f\n",conTrabajadores,sueldos);
				fprintf(ARCHdepa,"Departamento RRHH: %d \nTotal sueldos: %5.3f",conTrabajadores,sueldos);
				fprintf(ARCHdepa,"%s","\n==================================\n");
				conTrabajadores=0;
				sueldos=0;
			break;
			case CONSULTORIA:
				contarDepa(&conTrabajadores,&sueldos,"Consultoria");		
				printf("\n\nPersonal CONSULTORIA: %d\nTotal sueldos: %.2f\n",conTrabajadores,sueldos);
				fprintf(ARCHdepa,"Departamento CONSULTORIA: %d \nTotal sueldos: %5.3f",conTrabajadores,sueldos);
				fprintf(ARCHdepa,"%s","\n==================================\n");
				conTrabajadores=0;
				sueldos=0;
			break;
			case DISENO:
				contarDepa(&conTrabajadores,&sueldos,"Diseno");
				printf("\n\nPersonal DISENO: %d\nTotal sueldos: %.2f\n",conTrabajadores,sueldos);
				fprintf(ARCHdepa,"Departamento DISENO: %d \nTotal sueldos: %5.3f",conTrabajadores,sueldos);
				fprintf(ARCHdepa,"%s","\n==================================\n");
				conTrabajadores=0;
				sueldos=0;

			break;
			case PRODUCCION:
				contarDepa(&conTrabajadores,&sueldos,"Produccion");
				printf("\n\nPersonal PRODUCCION: %d\nTotal sueldos: %.2f\n",conTrabajadores,sueldos);
				fprintf(ARCHdepa,"Departamento PRODUCCION: %d \nTotal sueldos: %5.3f",conTrabajadores,sueldos);
				fprintf(ARCHdepa,"%s","\n==================================\n");
				conTrabajadores=0;
				sueldos=0;

			break;
			case CALIDAD:
				contarDepa(&conTrabajadores,&sueldos,"Calidad");
				printf("\n\nPersonal CALIDAD: %d\nTotal sueldos: %.2f\n",conTrabajadores,sueldos);
				fprintf(ARCHdepa,"Departamento CALIDAD: %d \nTotal sueldos: %5.3f",conTrabajadores,sueldos);
				fprintf(ARCHdepa,"%s","\n==================================\n");
				conTrabajadores=0;
				sueldos=0;
			break;
			case DISTRIBUCION:
				contarDepa(&conTrabajadores,&sueldos,"Distribucion");
				printf("\n\nPersonal DISTRIBUCION: %d\nTotal sueldos: %.2f\n",conTrabajadores,sueldos);
				fprintf(ARCHdepa,"Departamento DISTRIBUCION: %d \nTotal sueldos: %5.3f",conTrabajadores,sueldos);
				fprintf(ARCHdepa,"%s","\n==================================\n");
				conTrabajadores=0;
				sueldos=0;

			break;
			default:
				printf("\nOPCION INVALIDA");
			
			break;
		}

	}while ((depa!=1) && (depa!=2) && (depa!=3) && (depa!=4) && (depa!=5) && (depa!=6));

	fclose(ARCHdepa);

}
void contarDepa(int* emple, float* sueldo,char depa[20]){
	//abrimos el archivo de consulta y la estructura empleados

	FILE* ARCHConsulta;
	empleado empleados;
	int sueldos=0,data=0;
	char cargo[20],fecha[20],departa[20];
	ARCHConsulta=fopen("trabajadores.in","a+");
	if(ARCHConsulta==NULL){
		printf("\nNO SE ENCONTRO ARCHIVO\n");
		return ;
	}
	//iniciamos el ciclo de lectura del archivo
	while(((data=fgetc(ARCHConsulta))!=EOF) && (!(feof(ARCHConsulta)))){
			fscanf(ARCHConsulta,"%d", &empleados.CI);
			fscanf(ARCHConsulta,"%s",empleados.nombre);
			fscanf(ARCHConsulta,"%s",empleados.apellido);
			fscanf(ARCHConsulta,"%s",departa);	
			fscanf(ARCHConsulta,"%s",cargo);
			fscanf(ARCHConsulta,"%s",fecha);
			fscanf(ARCHConsulta,"%f",&empleados.sueldo);
			if(strcmp(depa,departa)==0){ //comparamos cadenas para saber hacer el conteo
				//cada vez que encuentre un empleado en este departamento incrementamos el acumulador de empleados y de sueldos
				*emple+=1;
				sueldos=empleados.sueldo;
				*sueldo+=sueldos;
			}
	}
	fclose(ARCHConsulta);

}
void CONSULTAporCARGO(){
	//abrimos el archivo de consulta
	FILE* ARCHcargo;
	int CARGOS;
	int conTrabajadores=0;
	float sueldos=0;
	ARCHcargo=fopen("cargo.txt","a+");
	if(ARCHcargo == NULL){
		printf("NO SE ENCONTRO ARCHIVO");
		return;
	}
	//menu para preguntar por cual cargo quiere buscar

	do{
		printf("\nIngrese el cargo que pertene: ");
		printf("\n1.GERENTE");
		printf("\n2.SUPERVISOR");
		printf("\n3.ANALISTA");
		printf("\n4.DISENADOR");
		printf("\n5.DESARROLLADOR");
		printf("\n6.AUDITOR");
		fflush(stdin);
		scanf("%d",&CARGOS);
		switch(CARGOS){
				case GERENTE:
				contarCargo(&conTrabajadores,&sueldos,"Gerente");
				printf("\nPersonal GERENTE: %d\nTotal de sueldo es: %.2f\n",conTrabajadores,sueldos);
				fprintf(ARCHcargo,"Cargo GERENTE: %d\nSUELDOS: %5.3f",conTrabajadores,sueldos);
				fprintf(ARCHcargo,"%s","\n==================================\n");
				conTrabajadores=0;
				sueldos=0;
			break;
			case SUPERVISOR:
				contarCargo(&conTrabajadores,&sueldos,"Supervisor");
				printf("\nPersonal SUPERVISOR: %d\nTotal de sueldo es: %.2f\n",conTrabajadores,sueldos);
				fprintf(ARCHcargo,"Cargo SUPERVISOR: %d\nSUELDOS: %5.3f",conTrabajadores,sueldos);
				fprintf(ARCHcargo,"%s","\n==================================\n");
				conTrabajadores=0;
				sueldos=0;
			break;
			case ANALISTA:
				contarCargo(&conTrabajadores,&sueldos,"Analista");
				printf("\nPersonal ANALISTA: %d\nTotal de sueldo es: %.2f\n",conTrabajadores,sueldos);
				fprintf(ARCHcargo,"Cargo ANALISTA: %d\nSUELDOS: %5.3f",conTrabajadores,sueldos);
				fprintf(ARCHcargo,"%s","\n==================================\n");
				conTrabajadores=0;
				sueldos=0;

			break;
			case DISENADOR:
				contarCargo(&conTrabajadores,&sueldos,"Disenador");
				printf("\nPersonal DISENADOR: %d\nTotal de sueldo es: %.2f\n",conTrabajadores,sueldos);
				fprintf(ARCHcargo,"Cargo DISENADOR: %d\nSUELDOS: %5.3f\n",conTrabajadores,sueldos);
				fprintf(ARCHcargo,"%s","\n==================================\n");
				conTrabajadores=0;
				sueldos=0;
			break;
			case DESARROLLADOR:
				contarCargo(&conTrabajadores,&sueldos,"Desarrollador");
				printf("\nPersonal DESARROLLADOR: %d\nTotal de sueldo es: %.2f\n",conTrabajadores,sueldos);
				fprintf(ARCHcargo,"Cargo DESARROLLADOR: %d\nSUELDOS: %5.3f",conTrabajadores,sueldos);
				fprintf(ARCHcargo,"%s","\n==================================\n");
				conTrabajadores=0;
				sueldos=0;
				
			break;
			case AUDITOR:
				contarCargo(&conTrabajadores,&sueldos,"Auditor");
				printf("\nPersonal AUDITOR: %d\nTotal de sueldo es: %.2f\n",conTrabajadores,sueldos);
				fprintf(ARCHcargo,"Cargo AUDITOR: %d\nSUELDOS: %5.3f",conTrabajadores,sueldos);
				fprintf(ARCHcargo,"%s","\n==================================\n");
				conTrabajadores=0;
				sueldos=0;
			break;
			default:
				printf("\nOPCION INVALIDA");
			break;
		}
	}while ((CARGOS!=1) && (CARGOS!=2) && (CARGOS!=3) && (CARGOS!=4) && (CARGOS!=5) && (CARGOS!=6));

	fclose(ARCHcargo);
}

void contarCargo(int* EMPLE, float* sueldos, char cargo[20]){
	//abrimos el archivo y la estructura empleados
	FILE* ARCHcargo;
	empleado empleados;
	int sueldo=0,data=0;
	char E_cargo[20],fecha[20],departa[20];
	ARCHcargo=fopen("trabajadores.in","a+");
	if(ARCHcargo == NULL){
		printf("\nNO SE ENCONTRO ARCHIVO\n");
	}
	//iniciamos el ciclo de lectura del archivo
	while((data=fgetc(ARCHcargo))!=EOF){
		fscanf(ARCHcargo,"%d", &empleados.CI);
		fscanf(ARCHcargo,"%s",empleados.nombre);
		fscanf(ARCHcargo,"%s",empleados.apellido);
		fscanf(ARCHcargo,"%s",departa);	
		fscanf(ARCHcargo,"%s",E_cargo);
		fscanf(ARCHcargo,"%s",fecha);
		fscanf(ARCHcargo,"%f",&empleados.sueldo);
		if(strcmp(cargo,E_cargo)==0){
			//cada vez que encuentre un empleado en este cargo incrementamos el acumulador de empleados y de sueldos

			*EMPLE+=1;
			sueldo=empleados.sueldo;
			*sueldos+=sueldo;
		}
		
	}
	fclose(ARCHcargo);

}
//trabajador con menor y mayor sueldo
void sueldoMayorMenor(){
	FILE* ARCHmayorMenor;
	empleado empleados;
	float sueldoMayor=0,sueldoMenor=99999999999;
	int data=0;
	char departa[20],E_cargo[20],fecha[20],nombreSueldoMayor[20],nombreSueldoMenor[20];
	//abrimos el archivo
	ARCHmayorMenor=fopen("trabajadores.in","a+");
	//veificamos que el archivo abrio correctamente
	if(ARCHmayorMenor == NULL){ 
		printf("\nNO SE HA ENCONTRADO ARCHIVO\n");
		return;
	}
	//comenzamos la lectura del archivo secuencialmente
	while ((data=fgetc(ARCHmayorMenor))!=EOF){
		//capturamos todos los elementos de la linea
		fscanf(ARCHmayorMenor,"%d", &empleados.CI);
		fscanf(ARCHmayorMenor,"%s",empleados.nombre);
		fscanf(ARCHmayorMenor,"%s",empleados.apellido);
		fscanf(ARCHmayorMenor,"%s",departa);
		fscanf(ARCHmayorMenor,"%s",E_cargo);
		fscanf(ARCHmayorMenor,"%s",fecha);
		fscanf(ARCHmayorMenor,"%f",&empleados.sueldo);
		//verificamos el sueldo mayor y lo actualizamos de ser necesario
		if(empleados.sueldo > sueldoMayor){
			sueldoMayor=empleados.sueldo;
			strcpy(nombreSueldoMayor,empleados.nombre);
		}
		//verificamos el sueldo menor y lo actualizamos de ser necesario
		if(empleados.sueldo < sueldoMenor){
			sueldoMenor=empleados.sueldo;
			strcpy(nombreSueldoMenor,empleados.nombre);
		}
	}
	//imprimimos nombre del trabajador con sueldo mayor y menor
	printf("\n\n==========================\n\n");
	printf("SUELDO MAYOR\n");
	printf("\n%s: %.2f\n\n",nombreSueldoMayor,sueldoMayor);
	printf("SUELDO MENOR\n");
	printf("\n%s: %.2f ",nombreSueldoMenor,sueldoMenor);
	printf("\n\n==========================\n\n");
}
void modificar(){
	//abrimos el archivo y la estructura empleados y las variables necesarias
	int ci,valiFecha,exits=0;
	empleado empleados;
	char depa[20],cargo[20],fecha[20];
	FILE* archiempleado, *modifiARCH;
	archiempleado=fopen("trabajadores.in","a+");
	modifiARCH=fopen("trabajadores2.in","a+"); //archivo temporal que reemplazara el viejo 
	if(archiempleado == NULL){
		printf("\nNO SE ENCONTRO ARCHIVO\n");
		return;
	}
	if(modifiARCH == NULL){
		printf("\nNO SE ENCONTRO ARCHIVO\n"); // verificamos que se crea 
		return;
	}
	
	printf("\nINGRESE LA CI DEL USUARIO QUE DESEA MODIFICAR: ");
	scanf("%d",&ci); //ingresamos CI el usuario a modificar

	while(!feof(archiempleado)){
		
		fscanf(archiempleado,"%d",&empleados.CI);
		fscanf(archiempleado,"%s",empleados.nombre);
		fscanf(archiempleado,"%s",empleados.apellido);
		fscanf(archiempleado,"%s",depa);//recorremos toda las casillas 
		fscanf(archiempleado,"%s",cargo);
		fscanf(archiempleado,"%s",fecha);
		fscanf(archiempleado,"%f",&empleados.sueldo);
		if((ci==empleados.CI) && (!feof(archiempleado))){ //si encontramos la CI modificamos los datos
			
			fprintf(modifiARCH,"%d\t\t",empleados.CI);

			printf("\nINGRESA NUEVO NOMBRE: ");
			scanf("%s",empleados.nombre);
			fprintf(modifiARCH,"%s",empleados.nombre);

			printf("\nINGRESA NUEVO APELLIDO: ");
			scanf("%s",empleados.apellido);
			fprintf(modifiARCH," %s\t",empleados.apellido);
			departamentos(modifiARCH);
			cargos(modifiARCH);
			do{
				printf("\nIngresa la fecha que ingreso a la empresa en formato DD/MM/AA: \n");
				printf("Dia: "); scanf("%d",&empleados.fecha.dia);
				printf("\nMes: "); scanf("%d",&empleados.fecha.mes);
				printf("\nAno: "); scanf("%d",&empleados.fecha.ano);
				valiFecha=validarFecha(empleados.fecha.dia,empleados.fecha.mes,empleados.fecha.ano);
			}while(valiFecha !=1);
			if (valiFecha == 1){
				fprintf(modifiARCH,"%d/%d/%d\t", empleados.fecha.dia,empleados.fecha.mes,empleados.fecha.ano);
			}
			printf("\nINGRESE NUEVO SALARIO: ");
			scanf("%f",&empleados.sueldo);
			fprintf(modifiARCH," %5.3f\n",empleados.sueldo);
			exits=1; //verifica que se encontro empleado 

		}else if(!feof(archiempleado)){ //sino encontramos la CI almacenamos los datos en el archivo nuevo 
			fprintf(modifiARCH,"%d\t",empleados.CI);
			fprintf(modifiARCH,"%s",empleados.nombre);
			fprintf(modifiARCH," %s\t",empleados.apellido);
			fprintf(modifiARCH,"%s\t",depa);
			fprintf(modifiARCH,"%s\t",cargo);
			fprintf(modifiARCH,"%s\t",fecha);
			fprintf(modifiARCH," %5.3f\n",empleados.sueldo);
		}

	}
	if(exits==0){
		printf("\nNO SE ENCONTRO EMPLEADO\n ");
	}
	fclose(archiempleado);
	fclose(modifiARCH);
}


//modulo eliminar
void eliminar(){
	FILE* trabajador;
	FILE*  trabajador3;
	int ci;
	empleado empleados;
	char cargo[20],depa[20],fecha[20], op;
	trabajador=fopen("trabajadores.in","a+");
	trabajador3=fopen("trabajadores3.in","a+");
	if(trabajador3==NULL){
		printf("\nERROR NO SE PUDO ENCONTRAR EL ARCHIVO\n");
		return;
	}
	if(trabajador==NULL){
		printf("\nERROR NO SE PUDO ENTONTRAR EL ARCHIVO\n");
		return;
	}
	printf("\nIngrese la CI que quiere eliminar: ");
	scanf("%d",&ci);
	while ((!feof(trabajador)) && (ci!=empleados.CI)){
		fscanf(trabajador,"%d",&empleados.CI);
		fscanf(trabajador,"%s",empleados.nombre);
		fscanf(trabajador,"%s",empleados.apellido);
		fscanf(trabajador,"%s",depa);
		fscanf(trabajador,"%s",cargo);
		fscanf(trabajador,"%s",fecha);
		fscanf(trabajador,"%f",&empleados.sueldo);
	}
	if(ci==empleados.CI){
		printf("Nombre: %s",empleados.nombre);
		printf("\nApellido: %s",empleados.apellido);
		printf("\nDepartamento: %s",depa);
		printf("\nCargo: %s",cargo);
		printf("\nFecha de ingreso: %s",fecha);
		printf("\nSueldo: %.3f",empleados.sueldo);
		
		printf("\n=======================================\n");
		printf(" |    ESTA SEGURO QUE DESEA ELIMINARLO? |\n ");
		printf("|    [1]. SI                          |\n ");
		printf("|    [2]. NO                          |\n ");
		printf("\n=======================================\n");
		printf("OPCION: ");
		scanf("%s",&op);
		do{
			 switch (op){
			 	case '1':
					exTrabajadores(empleados,cargo,depa);
					fclose(trabajador);
					trabajador=fopen("trabajadores.in","a+");
					while(!feof(trabajador) ){
						fscanf(trabajador,"%d",&empleados.CI);
						fscanf(trabajador,"%s",empleados.nombre);
						fscanf(trabajador,"%s",empleados.apellido);
						fscanf(trabajador,"%s",depa);
						fscanf(trabajador,"%s",cargo);
						fscanf(trabajador,"%s",fecha);
						fscanf(trabajador,"%f",&empleados.sueldo);
						if(empleados.CI==ci){
								fprintf(trabajador3,"%s","");
								fprintf(trabajador3,"%s","");
								fprintf(trabajador3,"%s","");
								fprintf(trabajador3,"%s","");
								fprintf(trabajador3,"%s","");
								fprintf(trabajador3,"%s","");
								fprintf(trabajador3,"%s","");

						}else if(!feof(trabajador)){
							fprintf(trabajador3,"%d\t",empleados.CI);
							fprintf(trabajador3,"%s",empleados.nombre);
							fprintf(trabajador3," %s\t",empleados.apellido);
							fprintf(trabajador3,"%s\t",depa);
							fprintf(trabajador3,"%s\t",cargo);
							fprintf(trabajador3,"%s\t",fecha);
							fprintf(trabajador3,"%5.3f\n",empleados.sueldo);

						}
					}
				break;
			 case '2':
			 	fclose(trabajador);
				trabajador=fopen("trabajadores.in","a+");
				while(!feof(trabajador) ){
					fscanf(trabajador,"%d",&empleados.CI);
					fscanf(trabajador,"%s",empleados.nombre);
					fscanf(trabajador,"%s",empleados.apellido);
					fscanf(trabajador,"%s",depa);
					fscanf(trabajador,"%s",cargo);
					fscanf(trabajador,"%s",fecha);
					fscanf(trabajador,"%f",&empleados.sueldo);
					if(!(feof(trabajador))){
						fprintf(trabajador3,"%d\t",empleados.CI);
						fprintf(trabajador3,"%s",empleados.nombre);
						fprintf(trabajador3," %s\t",empleados.apellido);
						fprintf(trabajador3,"%s\t",depa);
						fprintf(trabajador3,"%s\t",cargo);
						fprintf(trabajador3,"%s\t",fecha);
						fprintf(trabajador3," %5.3f\n",empleados.sueldo);
					}
				}	
			 break;
			 default:
				break;
			 }
		}while((op!='2') && (op!='1'));
		

	}else{
		printf("\nNo se encontro CI asociada a un empleado\n");
	}
	fclose(trabajador);
	fclose(trabajador3);
	
}


void exTrabajadores(empleado emple, char cargo[20],char depa[20]){
	FILE* EXtrabajadores; 
	EXtrabajadores=fopen("extrabajadores.txt","a+");	
	char opDespido;
	char motivo[20];
	int valFecha;
	empleado empleados;

	if(EXtrabajadores==NULL){
		printf("\nERROR NO SE ENCONTRO ARCHIVO\n");
		return;
	}
	fprintf(EXtrabajadores,"%d\t",emple.CI);
	fprintf(EXtrabajadores,"%s ",emple.nombre);
	fprintf(EXtrabajadores,"%s\t",emple.apellido);
	fprintf(EXtrabajadores,"%s\t",depa);
	fprintf(EXtrabajadores,"%s\t",cargo);
	fprintf(EXtrabajadores," %5.3f",emple.sueldo);

	do{
		printf("\n=======================================\n");
		printf("|    INDIQUE MOTIVO DE ELIMINACION      |\n");
		printf("|    [1]. TRASLADO     				|\n");
		printf("|    [2]. RENUNCIA    			  	|\n");
		printf("|    [3]. DESPIDO                   |\n");
		printf("|    [4]. OTRO                      |\n");
		printf("\n=======================================\n");
		printf("OPCION: ");
		scanf("%s",&opDespido);
		switch (opDespido){
			case '1':
				fprintf(EXtrabajadores,"%s","TRASLADO\t");
				strcpy(motivo,"TRASLADO");
			break;
			case '2':
				fprintf(EXtrabajadores,"%s","RENUNCIA\t");
				strcpy(motivo,"RENUNCIA");
			break;
			case '3':
				fprintf(EXtrabajadores,"%s","DESPIDO\t");
				strcpy(motivo,"DESPIDO");
			break;
			case '4':
				fprintf(EXtrabajadores,"%s","OTRO\t");
				strcpy(motivo,"OTRO");
			break;
			default:
				printf("\n\n\n===============================================\n\n");
				printf("     |   ESTOY SEGURO QUE ESTO %c NO ES UNA OPCION |  ",(char)opDespido);
				printf("\n\n=============================================\n\n\n");
			
			break;
		}

	}while((opDespido!='1') && (opDespido!='2') && (opDespido!='3') && (opDespido!='4'));

	do{
		printf("\nIngresa la fecha de %s en formato DD/MM/AA: \n",motivo);
		printf("Dia: "); scanf("%d",&empleados.fecha.dia);
		printf("\nMes: "); scanf("%d",&empleados.fecha.mes);
		printf("\nAno: "); scanf("%d",&empleados.fecha.ano);
		valFecha=validarFecha(empleados.fecha.dia,empleados.fecha.mes,empleados.fecha.ano);
	}while(valFecha!=1);
	fprintf(EXtrabajadores,"%d/%d/%d\n",empleados.fecha.dia,empleados.fecha.mes,empleados.fecha.ano);
	fclose(EXtrabajadores);
}