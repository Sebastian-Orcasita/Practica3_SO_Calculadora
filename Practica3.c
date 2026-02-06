#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX 10
#define EPS 1e-6
#define PI 3.14159265358979323846

double stack[MAX];
int top = -1;
int hasResult = 0;

// PANTALLA 
void clearScreen() { system("clear"); }

// PILA
int isFull() { return top == MAX - 1; }
int isEmpty() { return top == -1; }

void push(double value) {
    if (isFull()) {
        printf("Error: Pila llena.\n");
        return;
    }
    for (int i = top + 1; i > 0; i--)
        stack[i] = stack[i - 1];

    stack[0] = value;
    top++;
}

double pop() {
    if (isEmpty()) {
        printf("Error: Pila vacía.\n");
        return 0;
    }
    double val = stack[0];
    for (int i = 0; i < top; i++)
        stack[i] = stack[i + 1];
    top--;
    return val;
}

void clearStack() {
    top = -1;
    hasResult = 0;
}

// MOSTRAR PILA
void showStack() {
    printf("=========== PILA RPN ===========\n");
    for (int i = MAX - 1; i >= 0; i--) {
        if (i <= top)
            printf("Pos %2d: [ %.6lf ]\n", i + 1, stack[i]);
        else
            printf("Pos %2d: [      ]\n", i + 1);
    }

    if (hasResult)
        printf("\nResultado actual: %.6lf\n", stack[0]);
    else
        printf("\nResultado actual: ---\n");

    printf("================================\n");
}

// CONVERSIÓN
double toRadians(double degrees) {
    return degrees * PI / 180.0;
}

// OPERACIONES
void performOperation(int op) {
    double a, b, result;

    if (op >= 1 && op <= 5) {
        if (top < 1) {
            printf("Se necesitan 2 valores.\n");
            return;
        }
        b = pop();
        a = pop();
    }

    switch (op) {
        case 1: result = a + b; break;
        case 2: result = a - b; break;
        case 3: result = a * b; break;
        case 4:
            if (fabs(b) < EPS) { printf("División por cero.\n"); return; }
            result = a / b; break;
        case 5: result = pow(a, b); break;

        case 6:
            if (isEmpty()) return;
            a = pop();
            if (a < 0) { printf("Raíz negativa.\n"); return; }
            result = sqrt(a); break;

        case 7:  // SENO EN GRADOS
            if (isEmpty()) return;
            a = pop();
            result = sin(toRadians(a));
            break;

        case 8:  // COSENO EN GRADOS
            if (isEmpty()) return;
            a = pop();
            result = cos(toRadians(a));
            break;

        case 9:  // TANGENTE EN GRADOS
            if (isEmpty()) return;
            a = pop();
            double rad = toRadians(a);
            if (fabs(cos(rad)) < EPS) {
                printf("Tangente indefinida (cos=0 en %lf°).\n", a);
                push(a);
                return;
            }
            result = tan(rad);
            break;

        default:
            printf("Operación inválida.\n");
            return;
    }

    push(result);
    hasResult = 1;
}

// MENU
void menu() {
    printf("\n1. Ingresar número\n");
    printf("2. Seleccionar operación\n");
    printf("3. Limpiar último número/operación\n");
    printf("4. Limpiar todo\n");
    printf("5. Salir\n");
    printf("Seleccione opción: ");
}

void operationsMenu() {
    printf("\nOperaciones disponibles:\n");
    printf("1. Suma\n2. Resta\n3. Multiplicación\n4. División\n");
    printf("5. Potencia\n6. Raíz\n7. Seno\n8. Coseno\n9. Tangente\n");
    printf("Seleccione: ");
}

// MAIN
int main() {
    int option, op;
    double num;
    char input[50];

    while (1) {
        clearScreen();
        showStack();
        menu();

        fgets(input, sizeof(input), stdin);
        if (sscanf(input, "%d", &option) != 1) {
            printf("Entrada inválida.\n");
        }
        else if (option == 1) {
            clearScreen();
            showStack();
            printf("\nIngrese número: ");
            fgets(input, sizeof(input), stdin);
            if (sscanf(input, "%lf", &num) == 1) {
                push(num);
                hasResult = 0;
            }
        }
        else if (option == 2) {
            clearScreen();
            showStack();
            operationsMenu();
            fgets(input, sizeof(input), stdin);
            if (sscanf(input, "%d", &op) == 1 && op >= 1 && op <= 9)
                performOperation(op);
            else
                printf("Operación inválida.\n");
        }
        else if (option == 3) { pop(); hasResult = 0; }
        else if (option == 4) { clearStack(); }
        else if (option == 5) break;
        else printf("Opción inválida del menú.\n");

        printf("\nPresione Enter para continuar...");
        fgets(input, sizeof(input), stdin);
    }

    return 0;
}



