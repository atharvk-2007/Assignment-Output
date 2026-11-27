#include <stdio.h>

int main() {
    char op;
    int num1, num2, result = 0;

    printf("Enter operator (+, -, *, /, m): ");
    scanf(" %c", &op);

    printf("Enter 2 numbers: ");
    scanf("%d %d", &num1, &num2);

    switch (op) {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
            if (num2 != 0) {
                result = num1 / num2;
            } else {
                printf("Error: Division by zero\n");
                return 1;
            }
            break;
        case 'm':
            result = num1 % num2;
            break;
        default:
            printf("Invalid operator\n");
            return 1;
    }

    printf("Result= %d\n", result);

    return 0;
}