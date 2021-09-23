// Proyecto_GestionAltaBajaClinica.cpp : Defines the entry point for the console application.
//

/*Práctica 1
1. Realizar un programa en lenguaje C que genere la estructura clínica, 
que contienen los datos de nombre del paciente, enfermedad, edad, peso y estatura.
2. Que tenga un menú con altas, consulta y modificaciones.*/


#include "stdlib.h"
#include "stdio.h"
#include "iostream"
#include "string.h"
#include "conio.h"

using namespace std;

#define PD "F:\\LOL\\Paciente.dat"
#define TamPD sizeof(Paciente)

struct Paciente
{
	char nom[50];
	char enf[50];
	int edad = 0;
	float peso = 0;
	float altura = 0;
	int N_cita = 0;

};

long busqueda_base(FILE *m, int &n, long busca);
void cargar(Paciente *v, int &n);
void consulta(Paciente *v, int &n);
void modificar(Paciente *v, int &n);
int car_edad();
float car_peso();
float car_alt();
int car_Ncita();

int main()
{
	Paciente *v = 0;
	int n, opcion;
	do
	{
		system("cls");
		cout << "___________________________________________________________________________" << endl;
		cout << "___________________________________________________________________________" << endl;
		cout << "________________________________Bienvenido_________________________________" << endl;
		cout << "________________________Ingrese lo que desee hacer_________________________" << endl;
		cout << "___________________________________________________________________________" << endl;
		cout << "___________________________________________________________________________" << endl;
		cout << endl;
		cout << "::1:: Para Cargar y dar de Alta los datos del PAciente" << endl;
		cout << "::2:: Para Consultar los datos del Paciente" << endl;
		cout << "::3:: Para Modificar los datos del paciente" << endl;
		cout << "___________________________________________________________________________" << endl;
		cout << "___________________________________________________________________________" << endl;
		cout << "___________________________________________________________________________" << endl;
		cout << "___________________________________________________________________________" << endl;
		cout << "___________________________________________________________________________" << endl;
		cout << "Opcion: ";
		cin >> opcion;
		switch (opcion)
		{
		case 1: cargar(v, n);
			break;
		case 2: consulta(v, n);
			break;
		case 3: modificar(v, n);
			break;
		default: exit(0);
			break;
		}

	} while (true);



	system("pause");
	return 0;
}

long busqueda_base(FILE *m, int &n, long busca)
{
	long pos = -1;

	long actual = ftell(m);
	fseek(m, 0, SEEK_SET);

	Paciente *r;
	fread(&r, TamPD, 1, m);
	while (!feof(m))
	{
		for (int  g = 0; g < n; g++)
		{
			if (busca == r[g].N_cita)
			{
				pos = ftell(m) - TamPD;
			}
		}
		
		fread(&r, TamPD, 1, m);
	}

	fseek(m, actual, SEEK_SET);
	return pos;
}

void cargar(Paciente *v, int &n)
{
	if (v)
	{
		delete[]v;
	}
	do
	{
		cout << "¿Cantidad de Pacientes que desea cargar?: ";
		cin >> n;

	} while (n<=0 );

	v = new(nothrow)Paciente[n];
	
	if (!v)
	{
		cout << "No se pudo crear un nuevo paciente;" << endl;
		system("pause");
		system("cls");
		exit(0);
	}
	else
	{
		FILE *m;
		int res = fopen_s(&m, PD, "ab");
		cout << "Cargue los pacientes que desea cargar" << endl;
		for (int  i = 0; i < n; i++)
		{
			cout << "Paciente Nº" << i + 1 << endl;
			cout << "Nombre: ";
			fflush(stdin);
			cin >> v[i].nom;
			system("cls");
			cout << "Enfermedad: ";
			fflush(stdin);
			cin >> v[i].enf;
			system("cls");
			v[i].edad = car_edad();
			v[i].peso = car_peso();
			v[i].altura = car_alt();			
			v[i].N_cita = car_Ncita();
		}
		fwrite(&v, TamPD, 1, m);
		fclose(m);
	}

}

void consulta(Paciente *v, int &n)
{
	FILE *m;
	int res = fopen_s(&m, PD, "rb");
	if (res)
	{
		cout << "No se pudo abrir el archivo" << endl;
		return;
	}
	else
	{
		int busca;
		cout << "Ingrese el Numero de cita: ";
		cin >> busca;

		long pos = busqueda_base(m, n , busca);
		if (pos == -1)
		{
			cout << "No existe el paciente registrado " << endl;
		}
		else
		{
			Paciente *v;
			fseek(m, TamPD, SEEK_SET);
			fread(&v, TamPD, 1, m);
			for (int  h = 0; h < n; h++)
			{
				system("cls");
				cout << "Nombre : " << v[h].nom << endl;
				cout << "Enfermedad: " << v[h].enf << endl;
				cout << "Edad: " << v[h].edad << endl;
				cout << "Peso: " << v[h].peso << endl;
				cout << "Altura: " << v[h].altura << endl;
				cout << "Nº Cita: " << v[h].N_cita << endl;

			}

		}
		fclose(m);
		
	}
	cout << endl;
	system("pause");

}

void modificar(Paciente *v, int &n)
{
	FILE *m;
	int res = fopen_s(&m, PD, "r+b");
	if (res)
	{
		cout << "No se pudo abrir el archivo" << endl;
		return;
	}
	else
	{
		int busca;
		cout << "Ingrese el Numero de cita del Paciente que desea modificar: ";
		cin >> busca;

		long pos = busqueda_base(m, n, busca);
		if (pos == -1)
		{
			cout << "No existe el paciente registrado " << endl;
		}
		else
		{
			Paciente *v;
			fseek(m, TamPD, SEEK_SET);
			fread(&v, TamPD, 1, m);

			for (int h = 0; h < n; h++)
			{
				int Opcion2;
				do
				{

					system("cls");
					cout << "Datos del paciente anterior..." << endl;
					cout << "Nombre : " << v[h].nom << endl;
					cout << "Enfermedad: " << v[h].enf << endl;
					cout << "Edad: " << v[h].edad << endl;
					cout << "Peso: " << v[h].peso << endl;
					cout << "Altura: " << v[h].altura << endl;
					cout << "Nº Cita: " << v[h].N_cita << endl;
					cout << endl;
					cout << "Modificacion..." << endl;
					cout << "1. Cambiar de Nombre" << endl;
					cout << "2. Cambiar de Enfermedad" << endl;
					cout << "3. Cambiar de Edad" << endl;
					cout << "4. Cambiar de Peso" << endl;
					cout << "5. Cambiar de Altura" << endl;
					cout << "6. Cambiar de Nº Cita" << endl;
					cout << "7. Para Guardar y Finalizar" << endl;
					cin >> Opcion2;
					switch (Opcion2)
					{
					case 1: 
							fflush(stdin);
							cout << "Nuevo Nombre: ";
							cin >> v[h].nom;
						break;
					case 2: 
							fflush(stdin);
							cout << "Nueva Enfermedad: ";
							cin >> v[h].enf;
						break;
					case 3: v[h].edad = car_edad();
						break;
					case 4: v[h].peso = car_peso();
						break;
					case 5: v[h].altura = car_alt();
						break;
					case 6: v[h].N_cita = car_Ncita();
						break;
					case 7: fseek(m, TamPD, SEEK_SET);
							fwrite(&v, TamPD, 1, m);
							cout << "Cambios guardados" << endl;
					default: exit(0);
						break;
					}
				} while (Opcion2 != 7);
			}

		}
		fclose(m);

	}

	cout << endl;
	system("pause");

}

int car_edad()
{
	int EDAD;
	cout << "Edad: ";
	do
	{
		cin >> EDAD;
		if (EDAD < 0)
		{
			cout << "Por favor Ingrese el numero correspondiente" << endl;
			system("pause");
			system("cls");
		}

	} while (EDAD < 0);

	return EDAD;

}

float car_peso()
{
	float PESO;
	cout << "Peso: ";
	do
	{
		cin >> PESO;

		if (PESO < 0)
		{
			cout << "Por favor ingrese el peso correspondiente " << endl;
			system("pause");
			system("cls");
		}

	} while (PESO < 0);

	return PESO;
}

float car_alt()
{
	float Altura;
	cout << "Altura: ";
	do
	{
		if (Altura < 0)
		{
			cout << "Por favor ingrese la altura correspondiente " << endl;
			system("pause");
			system("cls");
		}

	} while (Altura < 0);

	return Altura;
}

int car_Ncita()
{
	int CITA;
	cout << "Nº Cita: ";
	do
	{
		cin >> CITA;
		if (CITA < 0)
		{
			cout << "Por favor Ingrese el numero correspondiente" << endl;
			system("pause");
			system("cls");
		}

	} while (CITA < 0);

	return CITA;

}