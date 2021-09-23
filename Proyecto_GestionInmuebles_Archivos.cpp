// GestionInmuebles.cpp : Defines the entry point for the console application.
//

/*Proyecto Final(entregable)
--A--
1. Realizar un sistema de venta de inmuebles en lenguaje C que maneje arreglos de
estructuras.
2. Se manejará una estructura con los datos de los inmuebles, por ejemplo ubicación, metros cuadrados de terreno, metros cuadrados de construcción, tipo de construcción(casa, condominio, departamento, etc.), precio, tipo de crédito, identificador del vendedor, estado(vendida o en venta).
3. Se manejará una estructura de datos de los vendedores, por ejemplo un identificador, nombre, domicilio, fecha de contrato, teléfonos de ubicación.
4. Las opciones que se tendrán son : Alta, baja, venta, consulta, y modificación de inmueble; alta, baja, modificación y consulta de vendedor.
5. Al dar de alta un inmueble, se deberá dar el identificador del vendedor encargado de la venta del mismo, el cual se debe verificar que existe en el sistema.
6. Guardar en un archivo los datos de inmueble y poderlos recuperar.
7. Guardar en un archivo(distinto) los vendedores dados de alta.
8. Si requiere de datos adicionales, que considere necesarios dentro del sistema puede agregarlos.
9. Se calificará : que cumpla con los puntos especificados, iniciativa para la programación y creatividad.
10. Se entrega : Código fuente, programa ejecutable, manual de usuario(como usar el sistema, mediante ejemplos de pantallas, explicado a los usuarios que no necesariamente tienen conocimiento de computación) y manual técnico(como se realizó el programa, algoritmos, explicación de las estructuras y funciones principales utilizadas).
11. Se entrega la documentación en un sobre, los códigos de manera digital, todo el equipo presente para su defensa.*/


#include "stdlib.h"
#include "stdio.h"
#include "iostream"
#include "string.h"
#include "conio.h"

using namespace std;

#define IM "inmueble.dat"
#define VD "Vendedores.dat"
#define TEMP1 "temporal1.dat"
#define TEMP2 "temporal2.dat"
#define T1 sizeOf(inmuebles);
#define T2 sizeOf(vendedores);

struct inmuebles
{
	int codigo;
	char ubicacion[50];
	float met_terre = 0;
	float met_constr = 0;
	int tipo_constr = 0;
	long int precio = 0;
	int tipo_cred = 0;
	long int iden_vend = 0;
	bool estado;
	bool activo;
};

struct vendedores
{
	long int Indetificador = 0;
	char Nombre[50];
	char domicilio[50];
	float fecha = 0;
	long int telefono;
};

#define IM "inmueble.dat"
#define VD "Vendedores.dat"
#define TEMP1 "temporal1.dat"
#define TEMP2 "temporal2.dat"
#define T1 sizeOf(inmuebles)
#define T2 sizeOf(vendedores)

long busqueda(int busca, FILE *m, int l);
void alta_Im();
void baja_im(int l);
void venta();
void consulta(int l);
void modificacion_im(int l);
long busqueda_ven(int busca2, FILE *o, int l);
void alta_Ven();
void baja_ven(int y);

int car_long();
int car_codigo();
float car_met_cuadr();
float car_met_const();
int car_tipo_const();
float car_precio();
int car_tip_cred();
long int car_iden_vend();
int car_est_vent();
long int car_iden();
float car_fecha();
long int car_tel();


int main()
{
	int opcion = 0;

	do
	{
		system("cls");
		cout << "Ingrese 1 para dar de ALTA un inmueble" << endl;
		cout << "Ingrese 2 para dar de BAJA un inmueble" << endl;
		cout << "Ingrese 3 para la VENTA de un inmueble" << endl;
		cout << "Ingrese 4 para la CONSULTA de un inmueble" << endl;
		cout << "Ingrese 5 para la MODIFICACION de un inmueble" << endl;
		cout << "Ingrese 6 para el ALTA a un vendedor" << endl;
		cout << "Ingrese 7 para dar de BAJA a un vendedor" << endl;
		cout << "Ingrese 8 para la CONSULTA a un vendedor" << endl;
		cout << "Ingrese 9 para la MODIFICACION a un vendedor" << endl;
		cout << "											Opcion: ";
		cin >> opcion;

		switch (opcion)
		{
		case 1:alta_Im();
			break;
		case 2:baja_im();
			break;
		case 3:venta();
			break;
		case 4:consulta(); 
			break;
		case 5: modificacion_im(); 
			break;
		case 6:alta_Ven(); 
			break;
		case 7:baja_ven();
			break;
		case 8:consulta2();
			break;
		case 9:Modificacion_ven();
			break;
		default:exit(0);
			break;
		}


	} while (opcion > 0 || opcion < 10);




	system("pause");
	return 0;
}

long busqueda(int busca, FILE *m, int l)
{
	long pos = -1;

	long actual = ftell(m);
	fseek(m, 0, SEEK_SET);

	inmuebles r[50];
	fread(&r, T1, 1, m);
	while (!feof(m))
	{
		for (int i = 0; i < l; i++)
		{
			if (busca == r[i].codigo)
			{
				pos = ftell(m) - T1;
				break;
			}

		}fread(&r, T1, 1, m);

	}
	fseek(m, actual, SEEK_SET);
	return pos;

}

void alta_Im()
{
	int l = 0, aux = 0;
	FILE *m, *w;
	int respIM = fopen_s(&m, IM, "a+b");

	if (respIM)
	{
		cout << "Error al abrir el archivo" << endl;
		return;
	}
	else
	{
		inmuebles r[50];
		cout << "Registre cuantos son los inmuebles para agregar" << endl;
		l = car_long();
		int busca;

		for (int i = 0; i < l; i++)
		{
			cout << "Carga de datos del inmueble " << i + 1 << endl;
			cout << "Ingrese el codigo de busqueda " << endl;
			cin >> busca;
			long p = busqueda(r[i].codigo, m, l);
			if (p == -1)
			{

				cout << endl;
				fflush(stdin);
				cout << "Por favor ingrese el nombre de la ubicacion " << endl;
				cin >> r[i].ubicacion;

				r[i].met_terre = car_met_cuadr();

				r[i].met_constr = car_met_const();

				r[i].tipo_constr = car_tipo_const();

				r[i].precio = car_precio();

				r[i].tipo_cred = car_tip_cred();

				r[i].iden_vend = car_iden_vend();

				aux = car_est_vent();

				switch (aux)
				{
				case 1: r[i].estado = false;
					break;
				case 2: r[i].estado = true;
					break;

					fwrite(&r, T1, 1, m);
					fwrite(&r, T1, 1, w);

				}

			}
			else
			{
				cout << "Ese codigo ya existe y esta en uso" << endl;
			}

		}
		fclose(m);
		cout << "finalizado... inmueble agregado... Se recomienda agregar al vendedor" << endl;
		cout << endl;
		system("pause");
	}
}

void baja_im()
{

	FILE *m;
	int respIM = fopen_s(&m, IM, "r+b");

	if (respIM)
	{
		cout << "Error al abrir el archivo" << endl;
		return;
	}
	else
	{
		inmuebles r[50];
		int busca;
		cout << "Ingrese el codigo de busqueda " << endl;
		cin >> busca;


		for (int i = 0; i < 50; i++)
		{

			long p = busqueda(r[i].codigo, m);
			if (p == -1)
			{
				cout << "el codigo no existe" << endl;

			}
			else
			{
				fseek(m, p, SEEK_SET);
				fread(&r, T1, 1, m);
				cout << "Ubicacion: " << r[i].ubicacion;
				cout << "Metros cuadrados del terreno: " << r[i].met_terre;
				cout << "Metros cuadrados construidos: " << r[i].met_constr;
				cout << "tipo de costruccion: ";

				switch (r[i].tipo_constr)
				{
				case 1: cout << " Casa" << endl;
					break;
				case 2: cout << " Codominio" << endl;
					break;
				case 3: cout << " Departamento" << endl;
					break;
				default: cout << " Otra categoria" << endl;
					break;
				}
				cout << "Precio: " << r[i].precio << endl;
				cout << "Tipo de Credito: ";
				switch (r[i].tipo_cred)
				{
				case 1: cout << " Credito Hipotecario" << endl;
					break;
				case 2: cout << " Credito de consumo" << endl;
					break;
				case 3: cout << " Credito Comercial" << endl;
					break;
				default: cout << " Otra categoria de credito" << endl;
					break;
				}
				cout << "Identificador del vendedor" << r[i].iden_vend << endl;

				int respuesta;

				cout << endl;
				cout << "¿Seguro que desea borrar este inmueble?(0 = SI / 1 = NO)" << endl;
				do
				{
					cin >> respuesta;

				} while (respuesta != 0 || respuesta != 1);

				if (respuesta == 0)
				{
					r[i].activo = false;
					fseek(m, p, SEEK_SET);
					fwrite(&r, T1, 1, m);
					cout << "inmueble eliminado " << endl;
				}
			}
		}
		fclose(m);
		cout << endl;
		system("pause");
		return;
	}
}

void venta()
{
	FILE *m;
	int respIM = fopen_s(&m, IM, "r+b");

	if (respIM)
	{
		cout << "Error al abrir el archivo" << endl;
		return;
	}
	else
	{
		inmuebles r[50];
		int busca;
		cout << "Ingrese el codigo de busqueda " << endl;
		cin >> busca;


		for (int i = 0; i < 50; i++)
		{

			long p = busqueda(r[i].codigo, m);
			if (p == -1)
			{
				cout << "el codigo no existe" << endl;
			}
			else
			{
				if (r[i].estado == true)
				{
					cout >> "El inmueble esta listo para la venta " << endl;

					int op1;

					cout << "¿Desea venderlo? (0=SI / 1=NO) " << endl;
					do
					{


						switch (op1)
						{
						case 0: r[i].estado = false;
							break;
						case 1: r[i].estado = true;
							break;
						default:exit(0);
							break;
						}

					} while (op1 > -1 || op1 < 2);
				}
				else
				{
					cout >> "El inmueble esta vendido" << endl;
				}
				fwrite(&r, T1, 1, m);

			}
		}
		fclose(m);
		cout << endl;
	}

}

void consulta()
{
	FILE *m;
	int des = fopen_s(&m, IM, "rb");
	int k;

	if (des = NULL)
	{
		cout << "No se pudo leer el archivo" << endl;
	}
	else
	{

		inmuebles r[50];
		int busca;
		cout << "Ingrese el codigo de busqueda " << endl;
		cin >> busca;

		for (int i = 0; i < 50; i++)
		{
			long p = busqueda(r[i].codigo, m, busca);
			if (p == -1)
			{
				cout << "el codigo no existe" << endl;

			}
			else
			{
				fseek(m, p, SEEK_SET);
				fread(&r, T1, 1, m);
				cout << "Ubicacion: " << r[i].ubicacion;
				cout << "Metros cuadrados del terreno: " << r[i].met_terre;
				cout << "Metros cuadrados construidos: " << r[i].met_constr;
				cout << "tipo de costruccion: ";

				switch (r[i].tipo_constr)
				{
				case 1: cout << " Casa" << endl;
					break;
				case 2: cout << " Codominio" << endl;
					break;
				case 3: cout << " Departamento" << endl;
					break;
				default: cout << " Otra categoria" << endl;
					break;
				}
				cout << "Precio: " << r[i].precio << endl;
				cout << "Tipo de Credito: ";
				switch (r[i].tipo_cred)
				{
				case 1: cout << " Credito Hipotecario" << endl;
					break;
				case 2: cout << " Credito de consumo" << endl;
					break;
				case 3: cout << " Credito Comercial" << endl;
					break;
				default: cout << " Otra categoria de credito" << endl;
					break;
				}
				cout << "Identificador del vendedor" << r[i].iden_vend << endl;
			}
		}
	}
}

void modificacion_im()
{
	FILE *m;
	int otro = fopen_s(&m, IM, "r+b");
	if (otro)
	{
		cout << "Error al abrir el archivo" << endl;
	}
	else
	{
		inmuebles r[50];
		int busca;
		cout << "Ingrese el codigo de busqueda " << endl;
		cin >> busca;

		for (int i = 0; i < 50; i++)
		{

			long p = busqueda(r[i].codigo, m, busca);
			if (p == -1)
			{
				cout << "el codigo no existe" << endl;

			}
			else
			{
				fseek(m, p, SEEK_SET);
				fread(&r, T1, 1, m);
				int Nop, Aux;
				do
				{


					system("cls");
					cout << "datos del inmueble:" << endl;
					cout << "Ubicacion: " << r[i].ubicacion << endl;
					cout << "Metros cuadrados del terreno: " << r[i].met_terre << endl;
					cout << "Metros cuadrados construidos: " << r[i].met_constr << endl;
					cout << "Tipo de construccion: ";
					switch (r[i].tipo_constr)
					{
					case 1: cout << " Casa" << endl;
						break;
					case 2: cout << " Codominio" << endl;
						break;
					case 3: cout << " Departamento" << endl;
						break;
					default: cout << " Otra categoria" << endl;
						break;
					}
					cout << "Precio: " << r[i].precio << endl;
					cout << "Tipo de Credito: ";
					switch (r[i].tipo_cred)
					{
					case 1: cout << " Credito Hipotecario" << endl;
						break;
					case 2: cout << " Credito de consumo" << endl;
						break;
					case 3: cout << " Credito Comercial" << endl;
						break;
					default: cout << " Otra categoria de credito" << endl;
						break;
					}
					cout << "Identificador del vendedor" << r[i].iden_vend << endl;

					cout << "____________________________________________________________________________" << endl;

					cout << "Ingrese la opcion que desea moficiar" << endl;

					cout << "Ingrese 1 para cambiar la ubicacion" << endl;
					cout << "Ingrese 2 para cambiar el tamaño del terreno" << endl;
					cout << "Ingrese 3 para cambiar el tamaño del terreno construido" << endl;
					cout << "Ingrese 4 para cambiar el tipo de construccion" << endl;
					cout << "Ingrese 5 para cambiar el precio" << endl;
					cout << "Ingrese 6 para cambiar el tipo de credito" << endl;
					cout << "Ingrese 7 para cambiar la identificacion del vendedor" << endl;
					cout << "Ingrese 8 para cambiar el estado de venta" << endl;

					cin >> Nop;

					switch (Nop)
					{
					case 1: cout << "Nueva Modificacion:" << endl;
						cout << "Por favor ingrese el nombre de la ubicacion " << endl;
						cin >> r[i].ubicacion;
						break;
					case 2: cout << "Nueva Modificacion:" << endl;
						r[i].met_terre = car_met_cuadr();
						break;
					case 3: cout << "Nueva Modificacion:" << endl;
						r[i].met_constr = car_met_const();
						break;

					case 4: cout << "Nueva Modificacion:" << endl;
						r[i].tipo_constr = car_tipo_const();
						break;
					case 5: cout << "Nueva Modificacion:" << endl;
						r[i].precio = car_precio();
						break;
					case 6: cout << "Nueva Modificacion:" << endl;
						r[i].tipo_cred = car_tip_cred();
						break;
					case 7: cout << "Nueva Modificacion:" << endl;
						r[i].iden_vend = car_iden_vend();
						break;
					case 8: cout << "Nueva Modificacion:" << endl;
						Aux = car_est_vent();

						switch (Aux)
						{
						case 1: r[i].estado = false;
							break;
						case 2: r[i].estado = true;
							break;
							break;
						}
					default: exit(0);
					}

				} while (Nop < 0 || Nop > 8);

				fseek(m, p, SEEK_SET);
				fwrite(&r, T1, 1, m);
			}
		}
		fclose(m);
		cout << endl;
		system("pause");

	}

}

long busqueda_ven(int busca2, FILE *o, int y)
{
	long pos2 = -1;

	long actual2 = ftell(o);
	fseek(o, 0, SEEK_SET);

	vendedores rv[50];
	fread(&rv, T2, 1, o);
	while (!feof(o))
	{
		for (int i = 0; i < l; i++)
		{
			if (busca2 == rv[i].Indetificador)
			{
				pos2 = ftell(o) - T2;
				break;
			}

		}fread(&rv, T2, 1, o);

	}
	fseek(o, actual2, SEEK_SET);
	return pos2;

}

void alta_Ven()
{
	int l = 0, aux = 0;
	FILE *o, *q;
	int respIM = fopen_s(&o, VD, "a+b");

	if (respIM)
	{
		cout << "Error al abrir el archivo" << endl;
		return;
	}
	else
	{
		vendedores rv[50];
		int y;
		cout << "Registre cuantos son los vendedores para agregar" << endl;
		y = car_long();
		int busca2;

		for (int i = 0; i < y; i++)
		{
			cout << "Carga de datos del vendedor " << i + 1 << endl;
			cout << "Ingrese la identificacion del vendedor " << endl;
			cin >> busca2;
			long p = busqueda(rv[i].Indetificador, o, busca2);
			if (p == -1)
			{

				cout << endl;
				fflush(stdin);
				cout << "Por favor ingrese el nombre de la ubicacion del vendedor" << endl;
				cin >> rv[i].Nombre;

				rv[i].fecha = car_fecha();

				cout << "Ingrese el Domicilio del vendedor" << endl;
				cin >> rv[i].domicilio;

				rv[i].telefono = car_tel();

				fwrite(&rv, T2, 1, o);
				fwrite(&rv, T2, 1, q);

			}
			else
			{
				cout << "Ese codigo ya existe y esta en uso" << endl;
			}

		}
		fclose(o);
		fclose(q);
		cout << "finalizado... vendedor agregado..." << endl;
		cout << endl;
		system("pause");
	}
}

void baja_ven()
{

	FILE *o;
	int respIM = fopen_s(&o, VD, "r+b");

	if (respIM)
	{
		cout << "Error al abrir el archivo" << endl;
		return;
	}
	else
	{
		vendedores rv[50];
		int busca;
		cout << "Ingrese el numero del identificador" << endl;
		cin >> busca;

		for (int i = 0; i < 50; i++)
		{

			long p2 = busqueda(rv[i].Indetificador, o, busca);
			if (p2 == -1)
			{
				cout << "el codigo no existe" << endl;

			}
			else
			{
				fseek(o, p2, SEEK_SET);
				fread(&rv, T1, 1, o);
				cout << "Nombre: " << rv[i].Nombre;
				cout << "Domicilio: " << rv[i].domicilio;
				cout << "Fecha: " << rv[i].fecha;
				cout << "Telefono: " << rv[i].telefono;


				int respuesta2;

				cout << endl;
				cout << "¿Seguro que desea borrar este Vendedor?(0 = SI / 1 = NO)" << endl;
				do
				{
					cin >> respuesta2;

				} while (respuesta2 != 0 || respuesta2 != 1);

				if (respuesta2 == 0)
				{

					fseek(o, p2, SEEK_SET);
					fwrite(&rv, T1, 1, o);
					cout << "Vendedor eliminado " << endl;
				}
			}
		}
		fclose(o);
		cout << endl;
		system("pause");
		return;
	}

}

void consulta2()
{
	FILE *o;
	int des = fopen_s(&o, VD, "rb");

	if (des = NULL)
	{
		cout << "No se pudo leer el archivo" << endl;
	}
	else
	{

		vendedores rv[50];
		int busca2;
		cout << "Ingrese el codigo de busqueda " << endl;
		cin >> busca2;


		for (int i = 0; i < 50; i++)
		{

			long p2 = busqueda(rv[i].Indetificador, o, busca2);
			if (p2 == -1)
			{
				cout << "el codigo no existe" << endl;

			}
			else
			{
				fseek(o, p2, SEEK_SET);
				fread(&rv, T2, 1, o);
				cout << "Nombre: " << rv[i].Nombre;
				cout << "Domicilio: " << rv[i].domicilio;
				cout << "Fecha: " << rv[i].fecha;
				cout << "Telefono: " << rv[i].telefono;

			}
		}
	}

}

void Modificacion_ven()
{
	FILE *o;
	int otro = fopen_s(&o, VD, "r+b");
	if (otro)
	{
		cout << "Error al abrir el archivo" << endl;
	}
	else
	{
		vendedores rv[50];
		int busca2;
		cout << "Ingrese el codigo de busqueda " << endl;
		cin >> busca2;

		for (int i = 0; i < 50; i++)
		{

			long p = busqueda(rv[i].Indetificador, o, busca2);
			if (p == -1)
			{
				cout << "el codigo no existe" << endl;

			}
			else
			{
				fseek(o, p, SEEK_SET);
				fread(&rv, T2, 1, o);
				int NOP, Aux;
				do
				{


					system("cls");
					cout << "Datos del vendedor" << endl;
					cout << "Domicilio del vendedor: " << rv[i].domicilio << endl;
					cout << "Nombre: " << rv[i].Nombre << endl;
					cout << "Fecha: " << rv[i].fecha << endl;
					cout << "Telefono: " << rv[i].telefono << endl;
					cout << "identificador: " << rv[i].Indetificador << endl;


					cout << "____________________________________________________________________________" << endl;

					cout << "Ingrese la opcion que desea moficiar" << endl;

					cout << "Ingrese 1 para cambiar Domicilio del vendedor" << endl;
					cout << "Ingrese 2 para cambiar Nombre del vendedor" << endl;
					cout << "Ingrese 3 para cambiar la Fecha" << endl;
					cout << "Ingrese 4 para cambiar el Telefono" << endl;
					cout << "Ingrese 5 para cambiar identificador" << endl;

					cin >> NOP;

					switch (NOP)
					{
					case 1: cout << "Nueva Modificacion:" << endl;
						cout << "Por favor ingrese el nuevo domicilio " << endl;
						cin >> rv[i].domicilio;
						break;
					case 2: cout << "Nueva Modificacion:" << endl;
						cout << "Por favor ingrese el nuevo nombre " << endl;
						cin >> rv[i].Nombre;
						break;
					case 3: cout << "Nueva Modificacion:" << endl;
						rv[i].fecha = car_fecha();
						break;
					case 4: cout << "Nueva Modificacion:" << endl;
						rv[i].telefono = car_tel();
						break;
					case 5: cout << "Nueva Modificacion:" << endl;
						rv[i].Indetificador = car_iden_vend();
						break;
					default: exit(0);
						break;
					}

				} while (NOP > 0 || NOP < 6);

				fseek(o, p, SEEK_SET);
				fwrite(&rv, T2, 1, o);
			}
		}
		fclose(o);
		cout << endl;
		system("pause");

	}
}

void depuracion()
{

}

int car_long()
{
	int p;
	cout << "Ingrese la cantidad deseada: ";
	cin >> p;
	cout << endl;

	return p;
}

int car_codigo()
{
	int codigo;
	cout << "Ingrese el codigo del inmueble: ";
	cin >> codigo;
	cout << endl;
	system("cls");
	return codigo;
}

float car_met_cuadr()
{
	float u;
	cout << "Ingresar los metros cuadrados del terreno:";
	cin >> u;
	cout << endl;
	system("cls");
	return u;
}

float car_met_const()
{
	float r;
	cout << "Ingresar los metros cuadrados construidos:";
	cin >> r;
	cout << endl;
	system("cls");
	return r;
}

int car_tipo_const()
{
	int p;
	cout << "Ingresar tipo de construccion" << endl;
	cout << "Ingrese 1 para construir casa " << endl;
	cout << "Ingrese 2 para construir codominio " << endl;
	cout << "Ingrese 3 para construir departamento " << endl;
	cout << "Ingrese 4 para construir otro tipo de construccion" << endl;
	cout << "Opcion: ";
	do
	{
		cin >> p;

		if (p > 0 || p < 5)
		{
			cout << "Ingrese correctamente siguiendo el menu de opciones" << endl;
		}

	} while (p > 0 || p < 5);

	cout << endl;
	system("cls");
	return p;
}

float car_precio()
{
	float precio;
	cout << "Ingresar el precio: ";
	cin >> precio;
	cout << endl;
	system("cls");
	return precio;
}

int car_tip_cred()
{
	int credito;
	cout << "Ingresar tipo de construccion" << endl;
	cout << "Ingrese 1 para credito Hipotecario " << endl;
	cout << "Ingrese 2 para consumo" << endl;
	cout << "Ingrese 3 para comerciales " << endl;
	cout << "Ingrese 4 para otro tipo de credito" << endl;
	cout << "Ingrese tipo de credito";
	do
	{
		cin >> credito;

		if (credito > 0 || credito < 5)
		{
			cout << "Ingrese correctamente siguiendo el menu de opciones" << endl;
		}

	} while (credito > 0 || credito < 5);

	cin >> credito;
	cout << endl;
	system("cls");
	return credito;
}

long int car_iden_vend()
{
	long int vendedor;
	cout << "Ingresar el numero de identificacion del vendedor: ";
	cin >> vendedor;
	cout << endl;
	system("cls");
	return vendedor;
}

int car_est_vent()
{
	int cosa;
	cout << "Ingresar 0: Para marcar inmueble como vendido			Ingresar 1: Para marcar inmueble en venta " << endl;
	cout << "Inmueble en : ";
	cin >> cosa;
	cout << endl;
	system("cls");
	return cosa;
}

long int car_iden()
{
	long int vendedor;
	cout << "Ingresar el numero de identificacion : ";
	cin >> vendedor;
	cout << endl;
	system("cls");
	return vendedor;
}

float car_fecha()
{
	float u;
	cout << "Ingresar la fecha:";
	cin >> u;
	cout << endl;
	system("cls");
	return u;
}

long int car_tel()
{
	long int telefono;
	cout << "Ingresar el numero de telefono del vendedor: ";
	do
	{
		cin >> telefono;
		if (telefono > 0 || telefono < 1000000000)
		{
			cout << "Ingrese correctamente un numero de telefono" << endl;
		}

	} while (telefono > 0 || telefono < 1000000000);

	cout << endl;
	system("cls");
	return telefono;
}


