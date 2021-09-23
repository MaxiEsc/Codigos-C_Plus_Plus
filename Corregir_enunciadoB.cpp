// Corregir_enunciadoB.cpp : Defines the entry point for the console application.
//

/*Usar ABM para realizar el ejercicio que sigue.
Un hotel desea llevar registro de las reservas efectuadas por distintos huéspedes.Por cada huésped que hizo una reserva,
se registran en un archivo los siguientes datos : número de dni del huésped, nombre del mismo, importe pagado por la reserva de habitación, y
la cantidad de dias que se quedará en el hotel.Se pide un programa controlado con menú, que incluya opciones para las siguientes tareas :
1.	Cargar un huésped en el archivo tomando por teclado sus datos.No hay problema con que un cliente aparezca más de una vez en el archivo, ya que el mismo cliente podría haber realizado varias reservas.
2.	Mostrar el contenido del archivo.
3.	Dado el número de dni de un huésped, mostrar todos los registros del archivo referidos a reservas de ese cliente(no es una búsqueda de un sólo registro : muestre TODOS los registros que pertenezcan a ese cliente).
4.	Crear un arreglo en el cual se copien los datos de todos los huéspedes del archivo que se hayan registrado por una cantidad de días mayor a un valor k que se carga por teclado.
5.	Mostrar el vector generado en el punto anterior, ordenado por el nombre de los huéspedes.
6.	Generar un segundo archivo, en el cual se graben todos los clientes del vector anterior.En el registro de este segundo archivo, NO DEBE figurar el campo "cantidad de dias".Entienda: no se trata de grabar el registro dejando en 0 el campo cantidad de días, sino de declarar un segundo tipo de registro que NO INCLUYA el campo citado.
7.	Mostrar el segundo archivo.*/


#include "stdio.h"
#include "stdlib.h"
#include "iostream"
#include "string.h"
#include "conio.h"

using namespace std;


#define HA "F:\\transferencia1\\Huesped.dat"
#define TEMP "F:\\transferencia1\\TempHuesped.dat"
#define Tam sizeof(Huesped)

struct Huesped
{
	long int DNI = 0;
	char nom[50];
	float imp_res = 0;
	int cant_dias = 0;
};

struct Temp
{
	long int DNI1 = 0;
	char nom1[50];
	float imp_res1 = 0;

};

long bus_prin(int busca, FILE *m, int n);
void cargar(Huesped *&v, int &n);
void mostrar();
void busqueda_dni(Huesped *v, int n);
void Guar_arr_archivo(Huesped *v, int n);
void Grab_Part_arr_arch(Huesped *v, int n);
void ordenar(Huesped *v, int n);
long int car_DNI();
float car_imp();
int car_dias();


int main()
{
	int OPCION = 0, n = 0;
	Huesped *v = 0;

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
		cout << ". 1 para cargar los datos del huesped" << endl;
		cout << ". 2 para mostrar los datos cargados" << endl;
		cout << ". 3 para buscar huesped por DNI y sus tramites" << endl;
		cout << ". 4 para Organizar informacion de un cliente en un vector" << endl;
		cout << ". 5 para Mostrar el vector ordenado alfabeticamente" << endl;
		cout << ". 6 para generar otro vector con datos de clientes sin Cant. dias" << endl;
		cout << "___________________________________________________________________________" << endl;
		cout << "___________________________________________________________________________" << endl;
		cout << "___________________________________________________________________________" << endl;
		cout << "___________________________________________________________________________" << endl;
		cout << "___________________________________________________________________________" << endl;
		cout << "Opcion: ";
		cin >> OPCION;
		cout << endl;
		switch (OPCION)
		{
		case 1:cargar(v, n);
			break;
		case 2:mostrar();
			break;
		case 3:busqueda_dni(v, n);
			break;
		case 4:Guar_arr_archivo(v, n);
			break;
		case 5:ordenar(v, n);
			mostrar();
			break;
		case 6:Grab_Part_arr_arch(v, n);
			break;
		default:exit(0);
			break;
		}

	} while (OPCION > 0 || OPCION < 8);

	system("pause");
	return 0;
}

long bus_prin(int busca, FILE *m, int n)
{
	long pos = -1;

	long actual = ftell(m);
	fseek(m, 0, SEEK_SET);

	Huesped *v;
	fread(&v, Tam, 1, m);
	while (!feof(m))
	{
		for (int i = 0; i < n; i++)
		{
			if (busca == v[i].DNI)
			{
				pos = ftell(m) - Tam;
				break;
			}
			fread(&v, Tam, 1, m);

		}

	}

	fseek(m, actual, SEEK_SET);
	return pos;

}

void cargar(Huesped *&v, int &n)
{
	if (v)
	{
		delete[]v;
	}

	do
	{
		system("cls");
		cout << "ingrese un numero mayor a cero: ";
		cin >> n;
		if (n >= 0)
		{
			cout << "Ingrese un numero mayor a 0" << endl;
		}


	} while (n <= 0);
	v = new(nothrow)Huesped[n];
	if (!v)
	{
		cout << "Error inesperado..." << endl;
	}
	system("cls");

	for (int i = 0; i < n; i++)
	{
		
		cout << "Cargue los datos del Huesped " << i + 1 << endl;
		v[i].DNI = car_DNI();
		v[i].imp_res = car_imp();
		v[i].cant_dias = car_dias();
		cout << "Ingrese el nombre del huesped: ";
		fflush(stdin);
		cin >> v[i].nom;
		

	}
	system("pause");

}

void mostrar()
{
	FILE *m;
	int res = fopen_s(&m, HA, "rb");
	if (res)
	{
		cout << "Error al abrir el archivo " << endl;
		system("pause");
		return;
	}
	Huesped r;
	cout << "Contenido del archivo" << endl;
	fread(&r, Tam, 1, m);
	while (!feof(m))
	{
		cout << "Dni: " << r.DNI << endl;
		cout << "Nombre: " << r.nom << endl;
		cout << "Importe por Reserva: " << r.imp_res << endl;
		cout << "Cantidad de dias: " << r.cant_dias << endl;

	}


}

void busqueda_dni(Huesped *v, int n)
{
	if (n == 0)
	{
		cout << "Cargue los datos primero " << endl;
		system("pause");
		return;
	}
	else
	{
		FILE *m;
		int e = fopen_s(&m, HA, "wb");
		if (e)
		{
			cout << "Error al abrir el archivo" << endl;
			return;

		}
		else
		{
			long int buscaDNI = 0;
			int busca;
			cout << "Ingresar el DNI para la busqueda" << endl;
			cin >> busca;
			long por = bus_prin(busca, m, n);
			cout << "Ingrese el DNi del cliente para buscar sus reservas" << endl;
			cout << "DNI: ";
			cin >> buscaDNI;
			if (por == -1)
			{
				cout << "No existe determinada identidad" << endl;
			}
			else
			{
				Huesped *v;
				fseek(m, por, SEEK_SET);
				fread(&v, Tam, 1, m);
				for (int i = 0; i < n; i++)
				{
					cout << "Dni: " << v[i].DNI << endl;
					cout << "Nombre: " << v[i].nom << endl;
					cout << "Importe por Reserva: " << v[i].imp_res << endl;
					cout << "Cantidad de dias: " << v[i].cant_dias << endl;

				}

			}
			fclose(m);
			cout << endl;
			system("pause");

		}
	}

}

void Guar_arr_archivo(Huesped *v, int n)
{
	if (n == 0)
	{
		cout << "Cargue los datos primero " << endl;
		system("pause");
		return;
	}
	else
	{
		FILE *m;
		int e = fopen_s(&m, HA, "wb");
		if (e)
		{
			cout << "no se pudo abrir el archivo" << endl;
			system("pause");
			return;
		}
		fwrite(v, n*Tam, 1, m);
		fclose(m);

		cout << "Listo, arreglado grabado completo en el archivo " << endl;
		cout << endl;
		system("pause");
	}

}

void Grab_Part_arr_arch(Huesped *v, int n)
{
	if (n == 0)
	{
		cout << "Cargue datos primero" << endl;
	}
	FILE *m;
	int res = fopen_s(&m, HA, "wb");
	if (res)
	{
		cout << "no se pudo cargar el archivo" << endl;
		system("pause");
		return;
	}



	for (int i = 0; i < n; i++)
	{
		fwrite(&v[i].nom, Tam, 1, m);
		fwrite(&v[i].DNI, Tam, 1, m);
		fwrite(&v[i].imp_res, Tam, 1, m);
	}
	fclose(m);
	cout << "Finalizado..." << endl;
	cout << endl;
	system("pause");
}

void ordenar(Huesped *v, int n)
{
	FILE *m, *q;
	int res = fopen_s(&m, HA, "rb");
	if (res)
	{
		cout << "El archivo no existe" << endl;
		return;
	}
	else
	{
		int res2 = fopen_s(&m, TEMP, "wb");
		if (res2)
		{
			cout << "El archivo no existe" << endl;
			fclose(m);
			return;
		}
		else
		{

			Huesped *v;
			fread(&v, Tam, 1, m);
			while (!feof(m))
			{
				fwrite(&v, Tam, 1, q);
				fread(&v, Tam, 1, m);
			}
			fclose(m);
			fclose(q);

		}

		int rar = fopen_s(&m, HA, "r+b");
		if (rar)
		{
			cout << "El archivo no existe" << endl;
			return;
		}
		else
		{
			fseek(m, 0, SEEK_SET);
			long t = ftell(m);
			long g = t / Tam;

			Huesped *R1, *R2;
			for (long i = 0; i < n - 1; i++)
			{
				fseek(m, i*Tam, SEEK_SET);
				fread(&R1, Tam, 1, m);
				for (long j = i + 1; i < n; i++)
				{
					fseek(m, j*Tam, SEEK_SET);
					fread(&R2, Tam, 1, m);

					for (int g = 0; g < n; g++)
					{
						if (strcmp(R1[g].nom, R2[g].nom) == 0)
						{
							fseek(m, j*Tam, SEEK_SET);
							fwrite(&R1, Tam, 1, m);

							R1 = R2;
						}
					}

				}
				fseek(m, i*Tam, SEEK_SET);
				fwrite(&R2, Tam, 1, m);
			}

			fclose(m);

			cout << "listo ... ordenado" << endl;
			cout << endl;
			system("pause");

		}

	}
}

long int car_DNI()
{
	long int NDNI = 0;

	cout << "DNI del huesped: ";
	do
	{
		cin >> NDNI;

		if (NDNI < 0)
		{
			cout << "Ingrese un numero DNI por favor" << endl;
			system("pause");
			system("cls");
		}
	} while (NDNI < 0);
	system("cls");
	return NDNI;
}

float car_imp()
{
	float IMPORTE = 0 ;
	cout << "Importe: ";
	do
	{
		cin >> IMPORTE;
		if (IMPORTE < 0)
		{
			cout << "Por favor ingrese un numero de importe" << endl;
			system("pause");
			system("cls");
		}

	} while (IMPORTE < 0);
	system("cls");
	return IMPORTE;
}

int car_dias()
{
	int DIAS = 0;

	cout << "Numero de dias en el Hotel: ";
	do
	{
		cin >> DIAS;
		if (DIAS < 0)
		{
			cout << "Por favor ingrese corectamente los dias" << endl;
			system("pause");
			system("cls");
		}

	} while (DIAS < 0);
	system("cls");
	return DIAS;
}
