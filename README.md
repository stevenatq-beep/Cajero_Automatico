# Cajero Automático Digital

## Descripción
Este proyecto consiste en el desarrollo de un sistema en lenguaje C que simula el funcionamiento básico de un cajero automático.

Permite a usuarios previamente registrados iniciar sesión y realizar operaciones bancarias básicas de manera segura.


## Funcionalidades

- Inicio de sesión con usuario y contraseña
- Límite de intentos de acceso
- Consulta de saldo
- Depósito de dinero
- Retiro de dinero con validación de fondos
- Validación de entradas incorrectas
- Mensajes claros para el usuario



## Usuarios de prueba

| Usuario | Contraseña | Saldo |
|--------|-----------|------|
| steven | 1234      | 1500 |
| ana    | 2026      | 800  |
| juan   | qwerty    | 300  |


## Requisitos

- Compilador de C mingw

## Compilación

```bash
gcc src/main.c -o cajero
