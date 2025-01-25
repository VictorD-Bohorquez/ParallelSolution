#include <iostream>
#include <omp.h>
#include <random>
using namespace std;

// Definimos las variables globales
#define N 50000
#define CHUNK 500
#define SHOW 20

void printArray(float* d);

int main()
{
	std::cout << "Sumando Arreglos en Paralelo \n";
	float a[N];
	float b[N];
	float c[N];
	int i;
	int min = 1;
	int max = 10000;
	int parts = CHUNK;

	//Inicializamos la semilla para nuestro generador de números aleatorios
	random_device rd;

	// Utilizamos el generador de numeros pseudo aleatorios Mersenne Twister
	mt19937 gen(rd());

	// Creamos una distribución pseudo random uniforme en un rango de 1 a 10000
	uniform_int_distribution<> dis(1, 10000);

	for (i=0 ; i<N ; i++) 
	{
		// Asignamos los números aleatorios
		a[i] = dis(gen);
		b[i] = dis(gen);
	}
	
	// Creamos nuetros for paralelo con la librería OMP
	#pragma omp parallel for shared(a,b,c,parts) private(i) schedule(static, parts)
	for (i = 0; i < N; i++)
	{
		c[i] = a[i] + b[i];
	}

	// Imprimimos información relevante de cada ejecución, así como parte de los arreglos.
	std::cout << "Ejecucion con un total de " << N << " valores en cada arreglo" << std::endl;
	std::cout << "Cada hilo de trabajo proceso " << CHUNK << " sumas" << std::endl;
	std::cout << "Imprimiendo " << SHOW << " valores del arreglo a:" << std::endl;
	printArray(a);
	std::cout << "Imprimiendo " << SHOW << " valores del arreglo b:" << std::endl;
	printArray(b);
	std::cout << "Imprimiendo " << SHOW << " valores resultantes del arreglo c:" << std::endl;
	printArray(c);
}	

// Función que imprime una parte de un arreglo
void printArray(float *d)
{
	for (int i = 0; i < SHOW; i++)
	{
		std::cout << d[i] << "-";
	}
	std::cout << std::endl;
}