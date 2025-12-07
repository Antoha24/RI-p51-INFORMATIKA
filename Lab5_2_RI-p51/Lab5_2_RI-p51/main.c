#define _CRT_SECURE_NO_WARNINGS
#define _SRTDC_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


double calculate_function(double x) {
    double temp = x - 100;
    return 0.4 * temp * temp * temp + 0.3 * x * x - 0.2 * x + 200;
}

int main() {
    FILE* input_file, * output_text, * output_binary;
    double start_x, end_x, step;
    int points_count;
    char group_code[50];
    char student_name[100];

    printf("Program started...\n");
    input_file = fopen("input_data.txt", "r");
    if (input_file == NULL) {
        printf("Error: Cannot open input file input_data.txt!\n");
        printf("Please check if file exists in the same directory.\n");
        return 1;
    }

    printf("File opened successfully. Reading data...\n");

    fscanf(input_file, "%lf", &start_x);
    fscanf(input_file, "%lf", &end_x);
    fscanf(input_file, "%d", &points_count);
    fscanf(input_file, "%lf", &step);
    fscanf(input_file, "%s", group_code);
    int c;
    do {
        c = fgetc(input_file);
    } while (c == ' ' || c == '\n' || c == '\r');

    ungetc(c, input_file);

    int i = 0;
    while ((c = fgetc(input_file)) != EOF && c != '\n' && c != '\r' && i < sizeof(student_name) - 1) {
        student_name[i++] = c;
    }
    student_name[i] = '\0';

    fclose(input_file);

    printf("Data read successfully from input file.\n");
    printf("\n=== INPUT DATA ===\n");
    printf("Start x: %.2lf\n", start_x);
    printf("End x: %.2lf\n", end_x);
    printf("Points count: %d\n", points_count);
    printf("Step: %.2lf\n", step);
    printf("Group: %s\n", group_code);
    printf("Student: %s\n", student_name);

    output_text = fopen("output_table.txt", "w");
    if (output_text == NULL) {
        printf("Error: Cannot create output text file!\n");
        return 1;
    }

    fprintf(output_text, "MATHEMATICAL FUNCTION RESULTS\n");
    fprintf(output_text, "Function: f(x) = 0.4*(x-100)^3 + 0.3*x^2 - 0.2*x + 200\n");
    fprintf(output_text, "Start: %.2lf, End: %.2lf, Points: %d, Step: %.2lf\n",
        start_x, end_x, points_count, step);
    fprintf(output_text, "Group: %s, Student: %s\n", group_code, student_name);
    fprintf(output_text, "\nTable of values:\n");
    fprintf(output_text, "Point No. |     x     |   f(x)   \n");
    fprintf(output_text, "----------|-----------|----------\n");
    output_binary = fopen("binary_data.bin", "wb");
    if (output_binary == NULL) {
        printf("Error: Cannot create binary file!\n");
        fclose(output_text);
        return 1;
    }

    int actual_points = 0;
    double x = start_x;
    while (x <= end_x && actual_points < points_count) {
        actual_points++;
        x += step;
    }

    fwrite(&actual_points, sizeof(int), 1, output_binary);

    printf("\n=== CALCULATION RESULTS ===\n");
    printf("Point No. |     x     |   f(x)   \n");
    printf("----------|-----------|----------\n");

    x = start_x;
    for (int i = 0; i < actual_points; i++) {
        double fx = calculate_function(x);

        printf("%9d | %9.2lf | %9.2lf\n", i + 1, x, fx);
        fprintf(output_text, "%9d | %9.2lf | %9.2lf\n", i + 1, x, fx);
        fwrite(&x, sizeof(double), 1, output_binary);
        fwrite(&fx, sizeof(double), 1, output_binary);

        x += step;
    }

    fprintf(output_text, "\nTotal points calculated: %d\n", actual_points);
    fclose(output_text);
    fclose(output_binary);
    printf("\nText file 'output_table.txt' created successfully!\n");
    printf("Binary file 'binary_data.bin' created successfully!\n");

    output_binary = fopen("binary_data.bin", "rb");
    if (output_binary != NULL) {
        fseek(output_binary, 0, SEEK_END);
        long file_size = ftell(output_binary);
        fclose(output_binary);
        printf("Binary file size: %ld bytes\n", file_size);
    }
    printf("\n=== READING FROM BINARY FILE ===\n");
    printf("Point No. |     x     |   f(x)   \n");
    printf("----------|-----------|----------\n");

    output_binary = fopen("binary_data.bin", "rb");
    if (output_binary == NULL) {
        printf("Error: Cannot open binary file for reading!\n");
        return 1;
    }

    int read_points_count;
    fread(&read_points_count, sizeof(int), 1, output_binary);
    printf("Points count in binary file: %d\n", read_points_count);

    double* data_array = (double*)malloc(2 * read_points_count * sizeof(double));
    if (data_array == NULL) {
        printf("Error: Memory allocation failed!\n");
        fclose(output_binary);
        return 1;
    }

    for (int i = 0; i < read_points_count; i++) {
        fread(&data_array[2 * i], sizeof(double), 1, output_binary);
        fread(&data_array[2 * i + 1], sizeof(double), 1, output_binary);
        printf("%9d | %9.2lf | %9.2lf\n", i + 1, data_array[2 * i], data_array[2 * i + 1]);
    }

    fclose(output_binary);
    free(data_array);

    printf("\nProgram completed successfully!\n");
    printf("Press Enter to exit...");
    getchar();

    return 0;
}
