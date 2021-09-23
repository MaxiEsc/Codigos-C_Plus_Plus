// AltaBajaClientes_archivos.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include <iostream>
using namespace std;
#define FD "clientes.dat"			
#define TEMP "temporal.dat”		   
#define T sizeof(Cliente)	
struct Cliente
{
	int codigo;
	char nombre[50];
	float saldo;
	bool activo;
};
void mensaje(const char mens[100]);
long search(int x, FILE *m);
void alta();
void baja();
void modificacion();
void listado();
void busqueda();
void ordenamiento();
void depuracion();

int main()
{
	int op;
	do
	{
		system("cls");
		cout << "---------------------MENU PRINCIPAL---------------------" << endl << endl;
		cout << "1. Alta de cliente." << endl;
		cout << "2. Baja de cliente." << endl;   // baja logica
		cout << "3. Modificacion de cliente." << endl;
		cout << "4. Listado de clientes. " << endl;
		cout << "5. Busqueda de clientes." << endl;
		cout << "6. Ordenamiento de clientes." << endl;
		cout << "7. Salir. " << endl;
		cout << "\t\tIngrese numero de opcion: ";
		cin >> op;
		system("cls");
		switch (op)
		{
		case 1: alta();
			break;
		case 2: baja();
			break;
		case 3: modificacion();
			break;
		case 4: listado();
			break;
		case 5: busqueda();
			break;
		case 6: ordenamiento();
			break;
		case 7:;
			break;
		}
	} while (op != 7);
	depuracion();    // baja fisica general
	return 0;
}
void mensaje(const char mens[100])
{
	cout << mens << endl;
	system("pause");
}
long search(int x, FILE*m)
{
	long pos = -1;

	long actual = ftell(m);
	fseek(m, 0, SEEK_SET);

	Cliente r;
	fread(&r, T, 1, m);
	while (!feof(m))
	{
		if (x == r.codigo && r.activo)
		{
			pos = ftell(m) - T;
			break;
		}
		fread(&r, T, 1, m);
	}

	fseek(m, actual, SEEK_SET);
	return pos;
}
void alta()
{
	FILE *m;
	int res = fopen_s(&m, FD, "a+b");

	if (res)
	{
		mensaje("error al abrir el archivo...");
		return;
	}

	Cliente r;
	cout << "Ingrese el dni del cliente a registrar: ";
	cin >> r.codigo;

	long p = search(r.codigo, m);
	if (p == -1)
	{
		// no existe el dni... darlo de alta...
		fflush(stdin);
		cout << "Nombre: ";
		fgets(r.nombre, 50, stdin);
		cout << "Saldo: ";
		cin >> r.saldo;
		r.activo = true;
		fwrite(&r, T, 1, m);
		cout << "Hecho... Cliente grabado... " << endl;
	}
	else
	{
		cout << "Ese DNI ya esta en uso" << endl;
	}

	fclose(m);
	cout << endl;
	system("pause");
}
void baja()
{
	FILE *m;
	int res = fopen_s(&m, FD, "r+b");
	if (res)
	{
		mensaje("error al arbrir el archivo...");
		return;
	}
	int x;
	cout << "DNI(codigo) del cliente a eliminar: ";
	cin >> x;

	long pos = search(x, m);
	if (pos == -1)
	{
		cout << "No existe ese cliente... " << endl;
	}

	else
	{
		Cliente r;
		fseek(m, pos, SEEK_SET);
		fread(&r, T, 1, m);
		cout << "Cliente encontrado.. " << endl;
		cout << "Cliente: " << r.nombre;
		cout << "\tSaldo: " << r.saldo;
		cout << endl;

		int resp;
		cout << "Seguro que desea borrar este cliente?  (0:No - 1:Si): ";
		cin >> resp;
		if (resp == 1)
		{
			r.activo = false;

			fseek(m, pos, SEEK_SET);
			fwrite(&r, T, 1, m);
			cout << "Hecho... cliente eliminado... " << endl;
		}
	}

	fclose(m);
	cout << endl;
	system("pause");
	return;
}
void modificacion()
{
	FILE *m;
	int res = fopen_s(&m, FD, "r+b");
	if (res)
	{
		mensaje("Error al abrir el archivo... ");
		return;
	}
	int x;
	cout << "Codigo del cliente a modificar: ";
	cin >> x;
	long pos = search(x, m);
	if (pos == -1)
	{
		cout << "No existe ese cliente... " << endl;
	}
	else
	{
		Cliente r;
		fseek(m, pos, SEEK_SET);
		fread(&r, T, 1, m);
		int op2;
		do
		{
			system("cls");
			cout << "Datos del cliente: " << endl;
			cout << "Nombre; " << r.nombre << "\tSaldo: " << r.saldo << endl;
			cout << endl;
			cout << endl << "1. Cambiar nombre: ";
			cout << endl << "2. Cambiar saldo: ";
			cout << endl << "3. Terminar y grabar ";
			cout << "\t\tIngrese opcion: ";
			cin >> op2;
			switch (op2)
			{
			case 1: fflush(stdin);
				cout << "Nuevo nombre: ";
				fgets(r.nombre, 50, stdin);
				break;

			case 2: cout << "Nuevo saldo";
				cin >> r.saldo;
				break;
			}
		} while (op2 != 3);

		fseek(m, pos, SEEK_SET);
		fwrite(&r, T, 1, m);
		cout << "Cambios guardados... " << endl;
	}
	fclose(m);
	cout << endl;
	system("pause");

}
void listado()
{
	FILE *m;
	int res = fopen_s(&m, FD, "rb");
	if (res)
	{
		mensaje("Error al abrir el archivo... ");
		return;
	}

	Cliente r;
	cout << "Listado de clientes" << endl;
	fread(&r, T, 1, m);
	while (!feof(m))
	{
		if (r.activo)
		{
			cout << endl;
			cout << "Codigo: " << r.codigo;
			cout << "\tNombre: " << r.nombre;
			cout << "\tSaldo: " << r.saldo;
		}
		fread(&r, T, 1, m);
	}
	fclose(m);
	cout << endl;
	system("pause");
}
void busqueda()
{
	FILE *m;
	int res = fopen_s(&m, FD, "rb");
	if (res)
	{
		mensaje("Error al abrir el archivo... ");
		return;
	}

	int x;
	cout << "DNI (Codigo) del cliente a buscar: ";
	cin >> x;

	long pos = search(x, m);
	if (pos == -1)
	{
		cout << "No existe ese cliente... " << endl;
	}
	else
	{
		Cliente r;
		fseek(m, pos, SEEK_SET);
		fread(&r, T, 1, m);
		cout << "Cliente encontrado... " << endl;
		cout << "Nombre: " << r.nombre << endl;
		cout << "Saldo: " << r.saldo << endl;
	}
	fclose(m);
	cout << endl;
	system("pause");
}
void ordenamiento()
{
	FILE *m;
	int r = fopen_s(&m, FD, "r+b");
	if (r)
	{
		mensaje("error al abrir el archivo...");
		return;
	}
	fseek(m, 0, SEEK_END);
	long t = ftell(m);
	long n = t / T;

	Cliente ri, rj;
	for (long i = 0; i < n - 1; i++)
	{
		fseek(m, i*T, SEEK_SET);
		fread(&ri, T, 1, m);
		for (long j = i + 1; j < n; j++)
		{
			fseek(m, j*T, SEEK_SET);
			fread(&rj, T, 1, m);

			if (ri.codigo > rj.codigo)
			{
				fseek(m, j*T, SEEK_SET);
				fwrite(&ri, T, 1, m);
				ri = rj;
			}
		}
		fseek(m, i*T, SEEK_SET);
		fwrite(&ri, T, 1, m);
	}

	fclose(m);
	cout << "Listo... archivo ordenado... " << endl;
	cout << endl;
	system("pause");

}
void depuracion()
{
	FILE *m, *t;
	int res = fopen_s(&m, FD, "rb");
	if (res)
	{
		mensaje("Error al abrir el archivo original... ");
		return;
	}

	int res2 = fopen_s(&t, TEMP, "wb");
	if (res2)
	{
		mensaje("Error al abrir el archivo temporal...");
		fclose(m);
		return;
	}

	Cliente r;
	fread(&r, T, 1, m);
	while (!feof(m))
	{
		if (r.activo)
		{
			fwrite(&r, T, 1, t);
		}
		fread(&r, T, 1, m);
	}
	fclose(m);
	fclose(t);

	remove(FD);
	rename(TEMP, FD);
}


#include <iostream>
using namespace std;
#define T sizeof(Materia)
#define FD "prueba.dat"	
struct Materia
{
	int codigo;
	char nombre[20];
};
void cargar(Materia *&v, int &n);
void mostrar(Materia *v, int n);
void mostrar();
void grabar1(Materia *v, int n);
void grabar2(Materia *v, int n);
void crear1(Materia *&v, int &n);
void crear2(Materia *&v, int &n);
int main()
{
	Materia *v = 0;
	int n = 0, op;

	do
	{
		system("cls");
		cout << "1. Cargar arreglo por teclado. " << endl;
		cout << "2. Mostrar el vector. " << endl;
		cout << "3. Grabar arreglo completo en un archivo. " << endl;
		cout << "4. Grabar parte del arreglo en un archivo." << endl;
		cout << "5. Mostrar archivo. " << endl;
		cout << "6. Crear arreglo desde el archivo completo." << endl;
		cout << "7. Crear arreglo con parte del archivo." << endl;
		cout << "8. Salir  " << endl;
		cout << "\t\t Ingrese opcion: ";
		cin >> op;
		system("cls");

		switch (op)
		{
		case 1: cargar(v, n);
			break;
		case 2: mostrar(v, n);
			break;
		case 3: grabar1(v, n);
			break;
		case 4: grabar2(v, n);
			break;
		case 5: mostrar();
			break;
		case 6:crear1(v, n);
			break;
		case 7:crear2(v, n);
			break;
		case 8:;
			break;
		}
	} while (op != 8);

	return 0;
}
void cargar(Materia *&v, int &n)
{
	if (v)
	{
		delete[]v;
	}

	do
	{
		cout << "N mayor a 0: ";
		cin >> n;
		if (n <= 0)
		{
			cout << "se pidio mayor a 0" << endl;
		}
	} while (n <= 0);

	v = new(nothrow)Materia[n];
	if (!v)
	{
		cout << "Error... falta memoria ... " << endl;
		system("pause");
		exit(1);
	}

	cout << "Cargue los datos de las materias: " << endl;
	for (int i = 0; i < n; i++)
	{
		cout << "Codigo[" << i << "]: ";
		cin >> v[i].codigo;

		fflush(stdin);
		cout << "Nombre: ";
		fgets(v[i].nombre, 20, stdin);
	}

}
void mostrar(Materia *v, int n)
{
	if (n == 0)
	{
		cout << "Carga datos primero " << endl;
		system("pause");
		return;
	}

	cout << "las materias que contiene el vector son: " << endl;

	for (int i = 0; i < n; i++)
	{
		cout << "Codigo [" << i << "]: " << v[i].codigo;
		cout << "\tnombre: " << v[i].nombre << endl;
	}

	system("pause");
}

void mostrar()
{
	FILE *m;
	int p = fopen_s(&m, FD, "rb");
	if (p)
	{
		cout << "Error al abrir el archivo" << endl;
		system("pause");
		return;
	}

	Materia r;
	cout << "contenido del archivo: " << endl;
	fread(&r, T, 1, m);
	while (!feof(m))
	{
		cout << "Codigo: " << r.codigo << endl;;
		cout << "\t Nombre: " << r.nombre << endl;
		fread(&r, T, 1, m);
	}

	fclose(m);
	cout << endl;
	system("pause");
}
void grabar1(Materia *v, int n)
{
	if (n == 0)
	{
		cout << "Carga datos primero... " << endl;
		system("pause");
		return;
	}

	FILE *m;
	int r = fopen_s(&m, FD, "wb");
	if (r)
	{
		cout << "Error, el archivo no se pudo abrir" << endl;
		system("pause");
		return;
	}

	fwrite(v, n*T, 1, m);
	fclose(m);

	cout << "Listo, arreglo grabado completo en el archivo.." << endl;
	cout << endl;
	system("pause");
}
void grabar2(Materia *v, int n)
{
	if (n == 0)
	{
		cout << "Carga datos primero " << endl;
		system("pause");
		return;
	}

	FILE *m;
	int r = fopen_s(&m, FD, "wb");
	if (r)
	{
		cout << "Error, el archivo no se pudo abrir" << endl;
		system("pause");
		return;
	}

	int x;
	cout << "Ingrese un codigo para filtrar el archivo: ";
	cin >> x;
	cout << "Se graban en el archivo las materias con codigo mayor a " << x << "... " << endl;
	for (int i = 0; i < n; i++)
	{
		if (v[i].codigo > x)
		{
			fwrite(&v[i], T, 1, m);
		}
	}
	fclose(m);
	cout << "Hecho... " << endl;
	cout << endl;
	system("pause");
}
void crear1(Materia *&v, int &n)
{
	FILE*m;
	int r = fopen_s(&m, FD, "rb");
	if (r)
	{
		cout << "No se pudo abrir el archivo... " << endl;
		system("pause");
		return;
	}
	fseek(m, 0, SEEK_END);
	long t = ftell(m) / T;
	if (t == 0)
	{
		cout << "archivo vacio...se deja como estaba el vector.... " << endl;
		cout << endl;
		fclose(m);
		system("pause");
		return;
	}

	Materia *z = new (nothrow)Materia[t];
	if (!z)
	{
		cout << "Memoria insuficiente para copiar el archivo .. " << endl;
		system("pause");
		fclose(m);
		return;
	}
	fseek(m, 0, SEEK_SET);
	fread(z, t*T, 1, m);
	if (v)
	{
		delete[]v;
	}

	v = z;
	n = t;

	cout << "Hecho... archivo copiado al vector v en memoria " << endl;
	cout << endl;
	system("pause");
	return;
}
void crear2(Materia *&v, int &n)
{
	FILE *m;
	int r = fopen_s(&m, FD, "rb");
	if (r)
	{
		cout << "No se pudo abrir el archivo... " << endl;
		system("pause");
		return;
	}

	int x;
	cout << "Ingrese codigo para filtrado de materias: ";
	cin >> x;

	Materia reg;
	long t = 0;
	fread(&reg, T, 1, m);
	while (!feof(m))
	{
		if (reg.codigo > x)
		{
			t++;
		}
		fread(&reg, T, 1, m);
	}
	if (t == 0)
	{
		cout << "no hay materias con codigo mayor a " << x << "... se deja el vector como estaba... " << endl;
		system("pause");
		fclose(m);
		return;
	}

	Materia *z = new (nothrow)Materia[t];
	if (!z)
	{
		cout << "memoria insuficiente para copiar el archivo... " << endl;
		system("pause");
		fclose(m);
		return;
	}

	fseek(m, 0, SEEK_SET);
	t = 0;
	fread(&reg, T, 1, m);
	while (!feof(m))
	{
		if (reg.codigo > x)
		{
			z[t] = reg;
			t++;
		}
		fread(&reg, T, 1, m);
	}

	fclose(m);
	if (v)
	{
		delete[]v;
	}

	v = z;
	n = t;

	cout << "Hecho... materias con codigo mayor a " << x << " copiadas en el vector" << endl;
	cout << endl;
	system("pause");
	return;
}


