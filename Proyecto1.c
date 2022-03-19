// Proyecto 1 OpenMP
// Ecuacion unidimensional de disipacion de calor
// Juan Diego Solorzano 18151
// Mario Perdomo 18029
// Jonathan Alvarez 15842

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

int main(int argc, char* argv[])
{

	// Input
	double error = 0;			// precision o diferencia requerida
	int ni = 10;				// numero de intervalos discretos (mini barras)
	double L = 100;
	double t0 = 40;			// temperatura inicial de toda la barra
	double tL = 40;			// temperatura en la frontera izquierda
	double tR = 70;			// temperatura en la frontera derecha
	double dt = 1000000;
	double dx = L/ni;  // intervalos a integrar
	double c = 0.000001;	// constante 10e-5

	// Vectores
	double t[ni];    // vector temperatura Actualizar
	double next_t[ni];  // vector temperatura siguiente T+1

	// inicializamos valores en el arreglo
	for (int i = 0; i < ni; i++)
	{
		t[i] = t0;
		next_t[i] = 0.0;
	}

	t[0] = tL;
	t[ni-1] = tR;

	error = 1000;
	int interv = 0; //intervalos temporales 1er criterio

	// while no llegamos a criterio de salida && interv < 1000
	while (error >= 0.0001 )
	{
		// Calcular nueva temperatura
		// Paralelizado con scheduling o con ompthreads clasico
		printf("_________________________ Iteracion %d ______________________\n", interv);

		for (int j = 0; j < ni; j++)
		{
			next_t[j] = t[j] + ((c*dt)/pow(dx, 2)) * (t[j-1] - 2*t[j] + t[j+1]);
		}

		// Calcular dif temperatura  3er criterio
		// Paralelizado con scheduling o con ompthreads clasico
		for (int i = 0; i <= ni - 1; i++)
		{
			double de = fabs(next_t[i] - t[i]);	//Absolute Error
			printf("Barra: %d\n", i);
			printf("%f - %f =  %.24f \n", next_t[i], t[i], de);

			printf("%f >= %f \n", error, de);

			if (error >= de)
				error = de;			//Maximum error

		}

		// PENSAR EN COMO DIVIDIR ARREGLOS PARA PARALELIZACION

		//Imprimir resultados parciales
		if (interv == ni - 1){
			printf("Iteracion %d :     ", interv);
			for (int j = 0; j < ni; j++) {
				printf("%f ", t[j]);
			}
			printf("\nVector solucion:  ");
			for (int j = 0; j < ni; j++) {
				printf("%f ", next_t[j]);
			}
			printf("\n\n");
		}

		// Actualizar vectores
		for (int j = 0; j < ni; j++) {
				t[j] = next_t[j];
				next_t[j] = 0.0;
			}
		interv++;
	}


}
