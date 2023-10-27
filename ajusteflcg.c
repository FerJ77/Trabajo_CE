#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define PI 3.14159265358979323846
#define POPULATION_SIZE 100
#define NUM_GENERATIONS 500
#define PXOVER 0.65
#define PMUTATION 0.003

 //Evaluación de la función aptitud
double evaluateFitness(double v, double sigma, double* v_obs, double* r, int dataSize) {   
    double chi_squared = 0;
    for (int i = 0; i < dataSize; ++i) {
        double m0 = 0;
        double B = ((v_obs[i] - m0) * (v_obs[i] - m0)) / (5 * sigma * sigma);
        double t5 = 8 / (3 * sqrt(5) * PI * sigma) * pow(1 + B, -3);  //función t5
        chi_squared += pow((r[i] - t5), 2);    //función chi cuadrado
    }
    return chi_squared;
}

 //Selección y cruce
void crossover(double* parent1, double* parent2, double* child1, double* child2) {
    int crossoverPoint = rand() % 2; // Elegir un punto de cruce (0 o 1)

    // Generar descendencia cruzando los padres en el punto de cruce
    for (int i = 0; i <= crossoverPoint; ++i) {
        child1[i] = parent1[i];
        child2[i] = parent2[i];
    }
    for (int i = crossoverPoint + 1; i < 2; ++i) {
        child1[i] = parent2[i];
        child2[i] = parent1[i];
    }
}

 //Mutación
void mutate(double* individual) {
    double mutationRate = 0.1; // Tasa de mutación gaussiana
    double mutationStrength = 0.5; // Fuerza de la mutación gaussina

    for (int i = 0; i < 2; ++i) {
        if ((double)rand() / RAND_MAX < mutationRate) {
            // Aplicar mutación gaussiana al gen individual[i]
            double mutation = mutationStrength * ((double)rand() / RAND_MAX * 2 - 1); // Valor aleatorio en el rango [-mutationStrength, mutationStrength]
            individual[i] += mutation;
        }
    }
}

 //Lectura e iteraciones 
int main() {
    FILE *file;
    file = fopen("Lfgc.txt", "r");
    if (file == NULL) {
        printf("No se pudo abrir el archivo data.txt\n");
        return 1;
    }

    int dataSize;
    fscanf(file, "%d", &dataSize);

    double *v_obs = malloc(dataSize * sizeof(double));
    double *r = malloc(dataSize * sizeof(double));

    for (int i = 0; i < dataSize; ++i) {
        fscanf(file, "%lf %lf", &v_obs[i], &r[i]);
    }

    fclose(file);

    srand(time(NULL));

    // Inicializar la población con valores aleatorios para V y sigma
    double fitness[POPULATION_SIZE]; // Declarar un arreglo para almacenar los valores de aptitud
    double population[POPULATION_SIZE][2];
    for (int i = 0; i < POPULATION_SIZE; ++i) {
      population[i][0] = 22 + ((double)rand() / RAND_MAX) * 5; // Rango para V: entre 22 y 25
      population[i][1] = ((double)rand() / RAND_MAX) * 2;     // Rango para sigma: entre 0 y 2
    }

    // Algoritmo genético
    for (int generation = 0; generation < NUM_GENERATIONS; ++generation) {
        // Evaluación de la aptitud
        double fitness[POPULATION_SIZE];
        for (int i = 0; i < POPULATION_SIZE; ++i) {
            fitness[i] = evaluateFitness(population[i][0], population[i][1], r, v_obs, dataSize);
        }

        // Selección y cruce
        double newPopulation[POPULATION_SIZE][2];
        for (int i = 0; i < POPULATION_SIZE; ++i) {
            int parent1 = rand() % POPULATION_SIZE;
            int parent2 = rand() % POPULATION_SIZE;

            if ((double)rand() / RAND_MAX < PXOVER) {
                crossover(population[parent1], population[parent2], newPopulation[i], newPopulation[i + 1]);
            } else {
                newPopulation[i][0] = population[parent1][0];
                newPopulation[i][1] = population[parent1][1];
                newPopulation[i + 1][0] = population[parent2][0];
                newPopulation[i + 1][1] = population[parent2][1];
            }

            i++;
        }

        // Mutación
        for (int i = 0; i < POPULATION_SIZE; ++i) {
            if ((double)rand() / RAND_MAX < PMUTATION) {
                mutate(newPopulation[i]);
            }
        }

        // Reemplazar la población antigua con la nueva
        for (int i = 0; i < POPULATION_SIZE; ++i) {
            population[i][0] = newPopulation[i][0];
            population[i][1] = newPopulation[i][1];
        }
    }

    // Encontrar el mejor individuo
    int bestIndividual = 0;
    double bestFitness = fitness[0];
    for (int i = 1; i < POPULATION_SIZE; ++i) {
        if (fitness[i] < bestFitness) {
            bestFitness = fitness[i];
            bestIndividual = i;
        }
    }

    printf("Mejor ajuste:\n");
    printf("V = %lf\n", population[bestIndividual][0]);
    printf("sigma = %lf\n", population[bestIndividual][1]);
    printf("Chi cuadrado = %lf\n", bestFitness);

    // Liberar memoria
    free(v_obs);
    free(r);

    return 0;
}

                                   
                                                                                                                         