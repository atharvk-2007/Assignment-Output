#include <stdio.h>
#include <string.h>

#define DEPTH_LIMIT 300.0
#define PRESSURE_LIMIT 30.0
#define TEMP_LIMIT 35.0
#define BATTERY_LIMIT 20

typedef struct {
    int id;
    float depth, pressure, temperature;
    int battery;
    char defect[30];
} RobotRecord;

void addRecord() {
    FILE *fp = fopen("underwater_log.txt", "a");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    RobotRecord r;
    printf("Enter ID: ");
    scanf("%d", &r.id);
    printf("Enter Depth (m): ");
    scanf("%f", &r.depth);
    printf("Enter Pressure (MPa): ");
    scanf("%f", &r.pressure);
    printf("Enter Temperature (C): ");
    scanf("%f", &r.temperature);
    printf("Enter Battery (%%): ");
    scanf("%d", &r.battery);
    printf("Enter Defect (None/Crack/Corrosion): ");
    scanf("%s", r.defect);

    fprintf(fp, "%d %.1f %.1f %.1f %d %s\n",
            r.id, r.depth, r.pressure, r.temperature, r.battery, r.defect);
    fclose(fp);
    printf("Record added successfully!\n");
}

void generateReport() {
    FILE *fp = fopen("underwater_log.txt", "r");
    FILE *rep = fopen("underwater_report.txt", "w");
    if (fp == NULL || rep == NULL) {
        printf("Error opening files!\n");
        return;
    }

    RobotRecord r;
    int total = 0, unsafe = 0;

    printf("\n=== Underwater Robot Monitoring ===\n");
    printf("ID\tStatus\tReason(s)\n");

    fprintf(rep, "===== Underwater Inspection Report =====\n");
    fprintf(rep, "Date: 16-Nov-2026\n\n");
    fprintf(rep, "-- Unsafe Records Details --\n");
    fprintf(rep, "ID\tDepth\tPressure\tTemp\tBattery\tDefect\n");

    while (fscanf(fp, "%d %f %f %f %d %s",
                  &r.id, &r.depth, &r.pressure, &r.temperature, &r.battery, r.defect) != EOF) {
        total++;
        int isUnsafe = 0;
        char reason[150] = "";

        if (r.depth > DEPTH_LIMIT) {
            isUnsafe = 1;
            strcat(reason, "Depth>300m, ");
        }
        if (r.pressure > PRESSURE_LIMIT) {
            isUnsafe = 1;
            strcat(reason, "Pressure>30MPa, ");
        }
        if (r.temperature > TEMP_LIMIT) {
            isUnsafe = 1;
            strcat(reason, "Temp>35C, ");
        }
        if (r.battery < BATTERY_LIMIT) {
            isUnsafe = 1;
            strcat(reason, "Battery<20%, ");
        }
        if (strcmp(r.defect, "None") != 0) {
            isUnsafe = 1;
            strcat(reason, "Defect: ");
            strcat(reason, r.defect);
            strcat(reason, ", ");
        }

        if (isUnsafe) {
            unsafe++;
            // Remove trailing comma and space
            int len = strlen(reason);
            if (len >= 2) {
                reason[len - 2] = '\0';
            }

            printf("%d\tUNSAFE\t%s\n", r.id, reason);
            fprintf(rep, "%d\t%.1f\t%.1f\t\t%.1f\t%d%%\t%s\n",
                    r.id, r.depth, r.pressure, r.temperature, r.battery, r.defect);
        }
    }

    printf("\nTotal Records : %d\n", total);
    printf("Unsafe Records: %d\n", unsafe);
    printf("Safe Records  : %d\n", total - unsafe);

    fprintf(rep, "\nSummary:\n");
    fprintf(rep, "Total Records     : %d\n", total);
    fprintf(rep, "Safe Operations   : %d\n", total - unsafe);
    fprintf(rep, "Unsafe Operations : %d\n", unsafe);

    fprintf(rep, "\nRecommendations:\n");
    fprintf(rep, "- Avoid depths beyond 300 m.\n");
    fprintf(rep, "- Maintain pressure <= 30 MPa.\n");
    fprintf(rep, "- Maintain temperature <= 35 C.\n");
    fprintf(rep, "- Recharge battery (>= 20%%) before next mission.\n");

    fclose(fp);
    fclose(rep);
    printf("Report generated: underwater_report.txt\n");
}

int main() {
    int choice;
    while (1) {
        printf("\n1. Add Record\n2. Generate Report\n3. Exit\nEnter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            addRecord();
        } else if (choice == 2) {
            generateReport();
        } else if (choice == 3) {
            break;
        } else {
            printf("Invalid choice!\n");
        }
    }
    return 0;
}