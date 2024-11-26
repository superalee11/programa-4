#include <stdio.h>
#include <math.h>

#define MAX 100

void normalizarVector(double vector[], int n) {
    double norma = 0.0;
    for (int i = 0; i < n; i++) {
        norma += vector[i] * vector[i];
    }
    norma = sqrt(norma);
    if (fabs(norma - 1.0) > 1e-6) {
        printf("\tEl vector inicial no tiene norma espectral 1. Se normalizara automaticamente.\n");
        for (int i = 0; i < n; i++) {
            vector[i] /= norma;
        }
    }
}

double metodoPotencias(double matriz[MAX][MAX], double vector[], int n, double tol, int max_iter, int inverso, int *iteracion_final, double vector_resultante[MAX]) {
    double lambda_anterior = 0.0, lambda;
    double nuevo_vector[MAX];
    int iter;

    for (iter = 1; iter <= max_iter; iter++) {
        for (int i = 0; i < n; i++) {
            nuevo_vector[i] = 0.0;
            for (int j = 0; j < n; j++) {
                nuevo_vector[i] += matriz[i][j] * vector[j];
            }
        }

        double norma = 0.0;
        for (int i = 0; i < n; i++) {
            norma += nuevo_vector[i] * nuevo_vector[i];
        }
        norma = sqrt(norma);
        for (int i = 0; i < n; i++) {
            nuevo_vector[i] /= norma;
        }

        lambda = 0.0;
        for (int i = 0; i < n; i++) {
            lambda += nuevo_vector[i] * vector[i];
        }

        if (fabs(lambda - lambda_anterior) < tol) {
            *iteracion_final = iter;
            for (int i = 0; i < n; i++) {
                vector_resultante[i] = nuevo_vector[i];
            }
            return inverso ? 1.0 / lambda : lambda;
        }

        lambda_anterior = lambda;
        for (int i = 0; i < n; i++) {
            vector[i] = nuevo_vector[i];
        }
    }

    *iteracion_final = max_iter;
    for (int i = 0; i < n; i++) {
        vector_resultante[i] = nuevo_vector[i];
    }
    return inverso ? 1.0 / lambda : lambda;
}

int main() {
     printf("\n\t\t\t METODO DE POTENCIAS\n\n");
    printf("\t\t   Metodos numericos - Grupo 1301\n \n");
    printf("\t Alcantar Hernandez Jessica Esmeralda\n");
    printf("\t Fierro Ibanez Andrea Esteph\n");
    printf("\t Jaimes Molina Andrea\n");
    printf("\t Lopez Ramirez Mariana Alejandra\n \n \n");
    
    int n, max_iter, iter_max, iter_min;
    double matriz[MAX][MAX], vector[MAX], tol, vector_max[MAX], vector_min[MAX];

    printf("\tIngresa la dimension de la matriz cuadrada: ");
    scanf("%d", &n);

    printf("\tIngresa los elementos de la matriz:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("\tElemento [%d, %d]: ", i + 1, j + 1);
            scanf("%lf", &matriz[i][j]);
        }
    }

    printf("\tIngresa los elementos del vector inicial:\n");
    for (int i = 0; i < n; i++) {
        printf("\tElemento [%d]: ", i + 1);
        scanf("%lf", &vector[i]);
    }

    normalizarVector(vector, n);

    printf("\tIngresa la tolerancia deseada: ");
    scanf("%lf", &tol);
    printf("\tIngresa el numero maximo de iteraciones: ");
    scanf("%d", &max_iter);

    double vector_copia[MAX];
    for (int i = 0; i < n; i++) {
        vector_copia[i] = vector[i];
    }

    double lambda_max = metodoPotencias(matriz, vector, n, tol, max_iter, 0, &iter_max, vector_max);

    
    double lambda_min = metodoPotencias(matriz, vector_copia, n, tol, max_iter, 1, &iter_min, vector_min);

    
    printf("\nResultados finales:\n");
    printf("\tEl valor propio maximo es: %.6lf\n", lambda_max);
    printf("\tSe alcanzo en la iteracion: %d\n", iter_max);
    printf("\tEl vector propio correspondiente es:\n");
    for (int i = 0; i < n; i++) {
        printf("\t%.6lf\n", vector_max[i]);
    }

    printf("\n\tEl valor propio minimo es: %.6lf\n", lambda_min);
    printf("\tSe alcanzo en la iteracion: %d\n", iter_min);
    printf("\tEl vector propio correspondiente es:\n");
    for (int i = 0; i < n; i++) {
        printf("\t%.6lf\n", vector_min[i]);
    }

    return 0;
}
