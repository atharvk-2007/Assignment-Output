#include <stdio.h>

int main()
{
    int n, i;
    int roll, s1, s2, s3, total;
    float percentage;
    char name[50];

    printf("Enter the number of students: ");
    scanf("%d", &n);

    printf("\nEnter the roll number, name and marks of 3 subjects:\n");

    printf("---------------------------------------------------------------\n");
    printf("Roll No   Name      Subject1  Subject2  Subject3  Total  Percentage\n");
    printf("---------------------------------------------------------------\n");

    for (i = 0; i < n; i++)
    {
        scanf("%d %s %d %d %d", &roll, name, &s1, &s2, &s3);

        total = s1 + s2 + s3;
        percentage = total / 3.0;

        printf("%-10d %-10s %-10d %-10d %-10d %-7d %.2f\n",
               roll, name, s1, s2, s3, total, percentage);
    }

    printf("---------------------------------------------------------------\n");

    return 0;
}