/*
	Desarrollo primer parcial 
	Sistemas Operativos y Laboratorio
	Jorge Iván Zapata Cortínez
	correo: jorge_101995@hotmail.com	
	cedula : 1033655109
*/

#include <stdio.h>
#include <stdlib.h>
#define CHARS_MAX_NAME 20

//variables globales
int max_number_employees = 0;
float value_extra_hour = 0;
int num_employees = 0;
float total_abs  = 0;

//Declaracion de funciones
char getOption();
void registerEmployees(char (*_employees)[CHARS_MAX_NAME], float  *_salaries, int *_extra_hours);
void showEmployees(char (*_employees)[CHARS_MAX_NAME], float  *_salaries, int *_extra_hours);
void getSalaryEmployees(char (*_employees)[CHARS_MAX_NAME], float  *_salaries, int *_extra_hours);
float getSalaryTotal(char (*_employees)[CHARS_MAX_NAME], float  *_salaries, int *_extra_hours);

int main(){
	//variables locales
	char option;
	char (*employees)[CHARS_MAX_NAME];
	float *salaries;
	int *extra_hours;

//Capturando el max numero de trabajadores
	printf("Ingrese el numero maximo de trabadores que pueden ser registrados \n");
	setbuf(stdin, NULL);
	scanf("%d", &max_number_employees);
	if(max_number_employees <= 0){
		printf("El valor ingresado no es válido\n");
		printf("Ingrese un numero natural válido\n");
		exit(0);
	}

//Reservando espacio en memoria dinamica
	employees = (char (*)[CHARS_MAX_NAME])malloc(sizeof(char[CHARS_MAX_NAME]) *max_number_employees);
	salaries = (float *) malloc(sizeof(float) * max_number_employees);
	extra_hours = (int *) malloc(sizeof(int) * max_number_employees);

	printf("Ingrese el valor de la hora extra \n");
	setbuf(stdin, NULL);
	scanf("%f", &value_extra_hour);

	
	do{
		option = getOption();
			switch(option){
				case 'a':
					registerEmployees(employees, salaries, extra_hours);
					break;
				case 'b':
					showEmployees(employees, salaries, extra_hours);
					break;
				case 'c':
					getSalaryEmployees(employees, salaries, extra_hours);
					break;
				case 'q':
					printf("Saliendo del programa...\n");
					break;
				default:
					printf("No ha ingresado una opción válida\n");
					break;
			}	
	}while (option != 'q');

	return 0;
}


//Implementacion de funciones
	char getOption(){
		char option;
			printf("MENÚ DE OPCIONES.\n");
			printf("a)\tRegistrar trabajadores.\n");
			printf("b)\tVer lista trabajadores.\n");	
			printf("c)\tCalcular nomina.\n");	
			printf("q)\tSalir del programa.\n");
			printf("\nSeleccione una opción: ");
			setbuf(stdin, NULL);
			scanf("%c", &option);
		return option;
	}
	void registerEmployees(char (*_employees)[CHARS_MAX_NAME], float  *_salaries, int *_extra_hours){

	int num_employees2register = 0;
	int i;

	printf("Ingrese el numero de empleados a registrar\n");
	setbuf(stdin, NULL);
	scanf("%d", &num_employees2register);
	if(num_employees + num_employees2register > max_number_employees){
		printf("No es posible registrar %d trabajadores\n", num_employees2register);	
		printf("El maximo numero permitido es %d y actualmente hay registrado %d.\n", max_number_employees, num_employees);
		return;
		}
		
		for(i = num_employees; i < num_employees + num_employees2register; i++){
			printf("\nNombre del empleado #%d: ", i+1);
			setbuf(stdin, NULL);
			scanf("%s", (char *)(_employees+i));
			printf("\nSalario base: ");
			setbuf(stdin, NULL);
			scanf("%f", (float *)(_salaries+i));
			printf("\nHoras extras: ");
			setbuf(stdin, NULL);
			scanf("%d", (int *)(_extra_hours+i));
		}
		num_employees += num_employees2register;
		printf("Se han registrado %d empleados en la lista de trabajadores\n", num_employees2register);
	}
	
	void showEmployees(char (*_employees)[CHARS_MAX_NAME], float  *_salaries, int *_extra_hours){
		int i = 0;
		printf("|%-16s|%-16s|%-16s|\n", "Nombre", "Salario base", "Horas extras");
		for(i=0; i < num_employees;i++){
			printf("|%-16s |%-16.2f|%-16d|\n", *(_employees+i), *(_salaries+i), *(_extra_hours+i));
		
		}	
	}

	void getSalaryEmployees(char (*_employees)[CHARS_MAX_NAME], float  *_salaries, int *_extra_hours){
		float extra_salary = 0, total = 0;
		int i = 0;

		printf("|%-16s|%-16s|%-16s|%-16s|\n", "Nombre", "Salario base", "Salario extra", "Total");
		for(i = 0; i < num_employees; i++){
			extra_salary = value_extra_hour * *(_extra_hours+i);
			total = *(_salaries+i) + extra_salary;
			total_abs += total;	
			printf("|%-16s|%-16.2f|%-16.2f|%-16.2f|\n",*(_employees+i) ,*(_salaries+i),extra_salary,total);		
		}
		printf("|%-48s|%-16.2f", "Total", total_abs);
	}
