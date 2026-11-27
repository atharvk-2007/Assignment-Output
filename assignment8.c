#include <stdio.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main()
{
    int motor1, motor2;
    int *p1, *p2;

    printf("Enter speed of motor 1 (RPM): ");
    scanf("%d", &motor1);

    printf("Enter speed of motor 2 (RPM): ");
    scanf("%d", &motor2);

    p1 = &motor1;
    p2 = &motor2;

    printf("\nBefore Swapping:\n");
    printf("Motor 1 speed : %d RPM\n", motor1);
    printf("Motor 2 speed : %d RPM\n", motor2);

    swap(p1, p2);

    printf("\nAfter Swapping (Control Switched):\n");
    printf("Motor 1 Speed: %d RPM\n", motor1);
    printf("Motor 2 Speed: %d RPM\n", motor2);

    return 0;
}