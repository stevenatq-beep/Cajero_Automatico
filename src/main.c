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

    printf("Sistema listo con usuarios registrados.\n");
    return 0;
}