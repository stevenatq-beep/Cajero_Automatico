#include <stdio.h>
#include <string.h>

#define MAX_USERS 3
#define MAX_ATTEMPTS 3
#define MAX_TEXT 50

typedef struct {
    char username[20];
    char password[20];
    double balance;
} User;

void mostrarBanner(void);
void mostrarMenu(const char username[]);
void limpiarBufferEntrada(void);
void quitarSaltoLinea(char texto[]);
void pausarPantalla(void);

int autenticarUsuario(User users[], int totalUsers, int *userIndex);
int buscarUsuario(User users[], int totalUsers, const char username[], const char password[]);
int leerOpcionMenu(int *opcion);
int leerMonto(const char *mensaje, double *monto);

void consultarSaldo(const User *user);
void depositarDinero(User *user);
void retirarDinero(User *user);

int main(void) {
    User users[MAX_USERS] = {
        {"steven", "1234", 1500.00},
        {"ana", "2026", 800.00},
        {"juan", "qwerty", 300.00}
    };

    int userIndex = -1;
    int opcion = 0;

    mostrarBanner();

    if (!autenticarUsuario(users, MAX_USERS, &userIndex)) {
        printf("\nAcceso denegado.\n");
        return 0;
    }

    do {
        mostrarMenu(users[userIndex].username);

        if (!leerOpcionMenu(&opcion)) {
            printf("Entrada invalida. Intente de nuevo.\n");
            pausarPantalla();
            continue;
        }

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

        if (opcion != 4) {
            pausarPantalla();
        }

    } while (opcion != 4);

    return 0;
}

void mostrarBanner(void) {
    printf("=====================================\n");
    printf("      CAJERO AUTOMATICO DIGITAL      \n");
    printf("=====================================\n");
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

void limpiarBufferEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* Vaciar buffer */
    }
}

void quitarSaltoLinea(char texto[]) {
    texto[strcspn(texto, "\n")] = '\0';
}

void pausarPantalla(void) {
    printf("\nPresione Enter para continuar...");
    getchar();
}

int buscarUsuario(User users[], int totalUsers, const char username[], const char password[]) {
    for (int i = 0; i < totalUsers; i++) {
        if (strcmp(username, users[i].username) == 0 &&
            strcmp(password, users[i].password) == 0) {
            return i;
        }
    }
    return -1;
}

int autenticarUsuario(User users[], int totalUsers, int *userIndex) {
    char username[MAX_TEXT];
    char password[MAX_TEXT];
    int intentos = 0;

    while (intentos < MAX_ATTEMPTS) {
        printf("\nUsuario: ");
        fgets(username, sizeof(username), stdin);
        quitarSaltoLinea(username);

        printf("Contrasena: ");
        fgets(password, sizeof(password), stdin);
        quitarSaltoLinea(password);

        *userIndex = buscarUsuario(users, totalUsers, username, password);

        if (*userIndex != -1) {
            printf("\nInicio de sesion exitoso. Bienvenido, %s.\n", users[*userIndex].username);
            return 1;
        }

        intentos++;
        printf("Credenciales incorrectas. Intento %d de %d.\n", intentos, MAX_ATTEMPTS);
    }

    return 0;
}

int leerOpcionMenu(int *opcion) {
    int resultado = scanf("%d", opcion);
    limpiarBufferEntrada();
    return resultado == 1;
}

int leerMonto(const char *mensaje, double *monto) {
    int resultado;

    printf("%s", mensaje);
    resultado = scanf("%lf", monto);
    limpiarBufferEntrada();

    if (resultado != 1) {
        return 0;
    }

    if (*monto <= 0) {
        return -1;
    }

    return 1;
}

void consultarSaldo(const User *user) {
    printf("\nSaldo actual de %s: $%.2f\n", user->username, user->balance);
}

void depositarDinero(User *user) {
    double monto;
    int estado = leerMonto("\nIngrese el monto a depositar: ", &monto);

    if (estado == 0) {
        printf("Entrada invalida.\n");
        return;
    }

    if (estado == -1) {
        printf("El monto debe ser mayor que cero.\n");
        return;
    }

    user->balance += monto;
    printf("Deposito realizado con exito.\n");
    printf("Nuevo saldo: $%.2f\n", user->balance);
}

void retirarDinero(User *user) {
    double monto;
    int estado = leerMonto("\nIngrese el monto a retirar: ", &monto);

    if (estado == 0) {
        printf("Entrada invalida.\n");
        return;
    }

    if (estado == -1) {
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