#include <stdio.h>
#include <string.h>

#define MAX_USERS 3
#define MAX_ATTEMPTS 3

typedef struct {
    char username[20];
    char password[20];
    double balance;
} User;

void mostrarMenu(const char username[]);
void consultarSaldo(User *user);
void depositarDinero(User *user);
void retirarDinero(User *user);
int autenticarUsuario(User users[], int totalUsers, int *userIndex);

int main(void) {
    User users[MAX_USERS] = {
        {"steven", "1234", 1500.00},
        {"ana", "2026", 800.00},
        {"juan", "qwerty", 300.00}
    };

    int userIndex = -1;
    int opcion = 0;

    printf("=====================================\n");
    printf("      CAJERO AUTOMATICO DIGITAL      \n");
    printf("=====================================\n");

    if (!autenticarUsuario(users, MAX_USERS, &userIndex)) {
        printf("\nAcceso denegado.\n");
        return 0;
    }

    do {
        mostrarMenu(users[userIndex].username);
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                consultarSaldo(&users[userIndex]);
                break;
            case 2:
                depositarDinero(&users[userIndex]);
                break;
            case 3:
                retirarDinero(&users[userIndex]);
                break;
            case 4:
                printf("\nGracias por usar el cajero, %s.\n", users[userIndex].username);
                break;
            default:
                printf("Opcion invalida.\n");
        }
    } while (opcion != 4);

    return 0;
}

int autenticarUsuario(User users[], int totalUsers, int *userIndex) {
    char username[20];
    char password[20];
    int intentos = 0;

    while (intentos < MAX_ATTEMPTS) {
        printf("\nUsuario: ");
        scanf("%19s", username);

        printf("Contrasena: ");
        scanf("%19s", password);

        for (int i = 0; i < totalUsers; i++) {
            if (strcmp(username, users[i].username) == 0 &&
                strcmp(password, users[i].password) == 0) {
                *userIndex = i;
                printf("\nInicio de sesion exitoso. Bienvenido, %s.\n", users[i].username);
                return 1;
            }
        }

        intentos++;
        printf("Credenciales incorrectas. Intento %d de %d.\n", intentos, MAX_ATTEMPTS);
    }

    return 0;
}

void mostrarMenu(const char username[]) {
    printf("\n=====================================\n");
    printf("Usuario activo: %s\n", username);
    printf("1. Consultar saldo\n");
    printf("2. Depositar dinero\n");
    printf("3. Retirar dinero\n");
    printf("4. Salir\n");
    printf("=====================================\n");
}

void consultarSaldo(User *user) {
    printf("Saldo actual: $%.2f\n", user->balance);
}

void depositarDinero(User *user) {
    double monto;

    printf("Ingrese el monto a depositar: ");
    scanf("%lf", &monto);

    if (monto <= 0) {
        printf("El monto debe ser mayor que cero.\n");
        return;
    }

    user->balance += monto;
    printf("Deposito realizado con exito.\n");
    printf("Nuevo saldo: $%.2f\n", user->balance);
}

void retirarDinero(User *user) {
    double monto;

    printf("Ingrese el monto a retirar: ");
    scanf("%lf", &monto);

    if (monto <= 0) {
        printf("El monto debe ser mayor que cero.\n");
        return;
    }

    if (monto > user->balance) {
        printf("Fondos insuficientes. Saldo disponible: $%.2f\n", user->balance);
        return;
    }

    user->balance -= monto;
    printf("Retiro realizado con exito.\n");
    printf("Nuevo saldo: $%.2f\n", user->balance);
}