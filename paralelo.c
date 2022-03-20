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
	double start; 
	double end; 

	// Input
	double error = 0;			// precision o diferencia requerida
	int ni = 10;				// numero de intervalos discretos
	double L = 100;
	double t0 = 40;			// temperatura inicial de toda la barra
	double tL = 40;			// temperatura en la frontera izquierda
	double tR = 100;			// temperatura en la frontera derecha
	double dt = 10000;			
	double dx = L/ni;			
	double c = 0.000001;	// constante 10e-5
    int threads = 2;

	printf("Ingrese la cantidad de threads: ");
	if (!(scanf("%d", &threads))){
        printf("\nEse valor no es valido\n");
        exit(0);
    };
    printf("Ingrese el numero de intervalos: ");
	if (!(scanf("%d", &ni))){
        printf("\nEse valor no es valido\n");
        exit(0);
    };
	printf("Ingrese la longitud: ");
	if (!(scanf("%lf", &L))){
        printf("\nEse valor no es valido\n");
        exit(0);
    };
	printf("Ingrese la temperatura inicial de la barra: ");
	if (!(scanf("%lf", &t0))){
        printf("\nEse valor no es valido\n");
        exit(0);
    };
	printf("Ingrese la temperatura de la frontera izquierda: ");
	if (!(scanf("%lf", &tL))){
        printf("\nEse valor no es valido\n");
        exit(0);
    };
	printf("Ingrese la temperatura de la frontera derecha: ");
	if (!(scanf("%lf", &tR))){
        printf("\nEse valor no es valido\n");
        exit(0);
    };

	printf("Calculando con %d intervalos discretos\n", ni);

	start = omp_get_wtime(); 

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
    int j;
	// while no llegamos a criterio de salida
	#pragma omp parallel num_threads(threads) shared(t, interv, tError, dt, dx)
	{
        
        while (interv < 100000 && error >= 0.0001 )
        {
            tError = 0;
            // Calcular nueva temperatura
            #pragma omp for schedule(static, 100000)
            for (j = 0; j < ni; j++)
            {     
                next_t[j] = t[j] + ((c*dt)/pow(dx, 2)) * (t[j-1] - 2*t[j] + t[j+1]);
                // Calcular error
                double newError = fabs(next_t[j] - t[j]);
            }

            #pragma omp single
            {
                
                for (j = 0; j < ni; j++)
                {     
                    // Calcular error
                    double newError = fabs(next_t[j] - t[j]);
                    if (newError > tError){
                        tError = newError;
                    }
                }
                error = tError;

                // Actualizar vectores
                for (j = 0; j < ni; j++) {
                    t[j] = next_t[j];
                    next_t[j] = 0.0;
                }

                interv++;

            }   
			
		}
        printf("\nsfsf %lf\n", t[1]);
	}
    
	printf("\nIteracion %d\n\n Vector solucion \n", interv);
	for (int j = 0; j < ni; j++) {
		printf("%f ", t[j]);
	}
	printf("\n\nError = %lf\n", error);

	end = omp_get_wtime(); 
  	printf("Tiempo =  %f s\n", end - start);
}