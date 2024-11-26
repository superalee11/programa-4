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

void metodoPotencias(double matriz[MAX][MAX], double vector[], int n, double tol, int max_iter) {
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
            printf("\tConvergencia alcanzada en iteracion: %d\n", iter);
            printf("\tEl mayor valor propio aproximado es: %.6lf\n", lambda);
            printf("\tEl vector propio correspondiente es:\n");
            for (int i = 0; i < n; i++) {
                printf("\t%.6lf\n", nuevo_vector[i]);
            }
            return;
        }

        lambda_anterior = lambda;
        for (int i = 0; i < n; i++) {
            vector[i] = nuevo_vector[i];
        }
    }

    printf("\tNo se alcanzo convergencia en el numero maximo de iteraciones.\n");
    printf("\tEl mayor valor propio aproximado es: %.6lf\n", lambda);
    printf("\tEl vector propio correspondiente es:\n");
    for (int i = 0; i < n; i++) {
        printf("%.6lf\n", nuevo_vector[i]);
    }
}

int main() {
    
    printf("\n\t\t\t METODO DE POTENCIAS\n\n");
    printf("\t\t   Metodos numericos - Grupo 1301\n \n");
    printf("\t Alcantar Hernandez Jessica Esmeralda\n");
    printf("\t Fierro Ibanez Andrea Esteph\n");
    printf("\t Jaimes Molina Andrea\n");
    printf("\t Lopez Ramirez Mariana Alejandra\n \n \n");
    
    int n, max_iter, fila, columna;
    double matriz[MAX][MAX], vector[MAX], tol;

    printf("\tIngresa la dimension de la matriz cuadrada: ");
    scanf("%d", &n);

    printf("\tIngresa los elementos de la matriz:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("\tElemento [%d, %d]: ", i + 1, j + 1);
            scanf("%lf", &matriz[i][j]);
        }
    }

    char respuesta;
    while (1) {
        printf("\t¿Deseas corregir algun coeficiente de la matriz? (s/n): ");
        scanf(" %c", &respuesta);
        if (respuesta == 's' || respuesta == 'S') {
            printf("\tIngresa la fila del coeficiente incorrecto: ");
            scanf("%d", &fila);
            printf("\tIngresa la columna del coeficiente incorrecto: ");
            scanf("%d", &columna);
            printf("\tIngresa el nuevo valor: ");
            scanf("%lf", &matriz[fila - 1][columna - 1]);
            printf("\tCoeficiente actualizado exitosamente.\n");
        } else {
            break;
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

    metodoPotencias(matriz, vector, n, tol, max_iter);

    return 0;
}
