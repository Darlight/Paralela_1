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
	double tR = 100;			// temperatura en la frontera derecha
	double dt = 1000000;			
	double dx = L/ni;			
	double c = 0.000001;	// constante 10e-5

	printf("Ingrese el numero de itervalos: ");
	scanf("%d", &ni);
	printf("Ingrese la longitud: ");
	scanf("%lf", &L);
	printf("Ingrese a temperatura inicial de la barra: ");
	scanf("%lf", &t0);
	printf("Ingrese la temperatura de la frontera izquierda: ");
	scanf("%lf", &tL);
	printf("Ingrese la temperatura de la frontera derecha: ");
	scanf("%lf", &tR);

	printf("Calculando con %d intervalos discretos\n", ni);

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
	double tError;
	// while no llegamos a criterio de salida
	while (interv < 1000 && error >= 0.001 )
	{
		tError = 0;
		// Calcular nueva temperatura
		for (int j = 0; j < ni; j++)
		{
			next_t[j] = t[j] + ((c*dt)/pow(dx, 2)) * (t[j-1] - 2*t[j] + t[j+1]);
			
			// Calcular error
			double newError = fabs(next_t[j] - t[j]);
			if (newError > tError){
				tError = newError;
			}
		}
		error = tError;

		// Actualizar vectores
		for (int j = 0; j < ni; j++) {
				t[j] = next_t[j];
				next_t[j] = 0.0;
			}
		interv++;
	}
	printf("\nIteracion %d\n\n Vector solucion \n", interv);
	for (int j = 0; j < ni; j++) {
		printf("%f ", t[j]);
	}
	printf("\n\nError = %lf\n", error);

	
}
