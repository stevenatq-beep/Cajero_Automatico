#include <stdio.h>
#include <string.h>

typedef struct {
    char username[20];
    char password[20];
    double balance;
} User;

int main(void) {
    User users[3] = {
        {"steven", "1234", 1500.00},
        {"ana", "2026",  800.00},
        {"juan", "qwerty", 300.00}
    };

    char username[20];
    char password[20];
    int acceso = 0;

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

    if (acceso) {
        printf("Acceso permitido.\n");
    } else {
        printf("Acceso denegado.\n");
    }

    return 0;
}