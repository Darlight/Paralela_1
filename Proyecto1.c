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
	int ni = 10;				// numero de intervalos discretos
	double L = 100;
	double t0 = 40;			// temperatura inicial de toda la barra
	double tL = 40;			// temperatura en la frontera izquierda
	double tR = 70;			// temperatura en la frontera derecha
	double dt = 100000;			
	double dx = L/ni;			
	double c = 0.000001;	// constante 10e-5

	// Vectores
	double t[ni];
	double next_t[ni];

	for (int i = 0; i < ni; i++)
	{
		t[i] = t0;
		next_t[i] = 0.0;
	}

	t[0] = tL;
	t[ni-1] = tR;

	error = 1000;
	int interv = 0;
	// while no llegamos a criterio de salida
	while (interv < ni && error >= 0.0001 )
	{
		// Calcular nueva temperatura
		for (int j = 0; j < ni; j++)
		{
			next_t[j] = t[j] + ((c*dt)/pow(dx, 2)) * (t[j-1] - 2*t[j] + t[j+1]);
		}

		// Calcular error

		for (int i = 0; i <= ni - 1; i++)
		{
			double de = abs(next_t[i] - t[i]);	//Absolute Error
			if (de > error)
				error = de;			//Maximum error

		}
		if (interv == ni-1){
			printf("Iteracion %d \n", interv);
			for (int j = 0; j < ni; j++) {
				printf("%f ", t[j]);
			}
			printf("\n");
			for (int j = 0; j < ni; j++) {
				printf("%f ", next_t[j]);
			}
			printf("\n\n");
		}
		for (int j = 0; j < ni; j++) {
				t[j] = next_t[j];
				next_t[j] = 0.0;
			}
		interv++;
	}

	
}
