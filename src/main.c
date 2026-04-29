#include <stdio.h>
#include <string.h>

#define MAX_ATTEMPTS 3

typedef struct {
    char username[20];
    char password[20];
    double balance;
} User;

void mostrarMenu(void) {
    printf("\n1. Consultar saldo\n");
    printf("2. Depositar dinero\n");
    printf("3. Retirar dinero\n");
    printf("4. Salir\n");
}

int main(void) {
    User users[3] = {
        {"steven", "1234", 1500.00},
        {"ana", "2026",  800.00},
        {"juan", "qwerty", 300.00}
    };

    char username[20];
    char password[20];
    int acceso = 0;
    int intentos = 0;
    int opcion;

    while (intentos < MAX_ATTEMPTS && !acceso) {
        printf("Usuario: ");
        scanf("%19s", username);

        printf("Contrasena: ");
        scanf("%19s", password);

        for (int i = 0; i < 3; i++) {
            if (strcmp(username, users[i].username) == 0 &&
                strcmp(password, users[i].password) == 0) {
                acceso = 1;
            }
        }

        if (!acceso) {
            intentos++;
            printf("Credenciales incorrectas. Intento %d de %d.\n", intentos, MAX_ATTEMPTS);
        }
    }

    if (!acceso) {
        printf("Demasiados intentos fallidos.\n");
        return 0;
    }

    do {
        mostrarMenu();
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

    } while (opcion != 4);

    return 0;
}