#include <stdio.h>
#include <string.h>

#define MAX_USERS 3
#define MAX_ATTEMPTS 3

// Estructura que representa un usuario
typedef struct {
    char username[20];
    char password[20];
    double balance;
} User;

// Prototipos de funciones
int login(User users[], int *index);
void menu(User *user);
void consultarSaldo(User *user);
void depositar(User *user);
void retirar(User *user);

int main() {

    // Usuarios de prueba
    User users[MAX_USERS] = {
        {"steven", "1234", 1500},
        {"ana", "2026", 800},
        {"juan", "qwerty", 300}
    };

    int index;

    printf("=== CAJERO AUTOMATICO ===\n");

    // Validar login
    if (!login(users, &index)) {
        printf("Acceso denegado.\n");
        return 0;
    }

    // Mostrar menu del usuario autenticado
    menu(&users[index]);

    return 0;
}

// Funcion para autenticar usuario
int login(User users[], int *index) {
    char user[20], pass[20];

    for (int intento = 0; intento < MAX_ATTEMPTS; intento++) {

        printf("Usuario: ");
        scanf("%s", user);

        printf("Contrasena: ");
        scanf("%s", pass);

        // Buscar usuario
        for (int i = 0; i < MAX_USERS; i++) {
            if (strcmp(user, users[i].username) == 0 &&
                strcmp(pass, users[i].password) == 0) {

                *index = i;
                printf("Bienvenido %s\n", users[i].username);
                return 1;
            }
        }

        printf("Datos incorrectos (%d/%d)\n", intento + 1, MAX_ATTEMPTS);
    }

    return 0;
}

// Menu principal
void menu(User *user) {
    int op;

    do {
        printf("\n1. Consultar saldo\n");
        printf("2. Depositar\n");
        printf("3. Retirar\n");
        printf("4. Salir\n");
        printf("Opcion: ");
        scanf("%d", &op);

        switch (op) {
            case 1:
                consultarSaldo(user);
                break;
            case 2:
                depositar(user);
                break;
            case 3:
                retirar(user);
                break;
            case 4:
                printf("Hasta luego %s\n", user->username);
                break;
            default:
                printf("Opcion invalida\n");
        }

    } while (op != 4);
}

// Mostrar saldo
void consultarSaldo(User *user) {
    printf("Saldo: %.2f\n", user->balance);
}

// Depositar dinero
void depositar(User *user) {
    double monto;

    printf("Monto a depositar: ");
    scanf("%lf", &monto);

    if (monto <= 0) {
        printf("Monto invalido\n");
        return;
    }

    user->balance += monto;
    printf("Deposito exitoso. Nuevo saldo: %.2f\n", user->balance);
}

// Retirar dinero
void retirar(User *user) {
    double monto;

    printf("Monto a retirar: ");
    scanf("%lf", &monto);

    if (monto <= 0) {
        printf("Monto invalido\n");
        return;
    }

    if (monto > user->balance) {
        printf("Fondos insuficientes\n");
        return;
    }

    user->balance -= monto;
    printf("Retiro exitoso. Nuevo saldo: %.2f\n", user->balance);
}