#include <stdio.h>
#include <stdlib.h>
#include <math.h>


// Function declaration
void Basic_circuit_analyser();
static void analyse_series_circuit(void);
static void analyse_parallel_circuit(void);
static void analyse_mixed_circuit(void);
static void calculate_current(double resistance);
static void print_resistance_with_units(double resistance);
static double calculate_series_resistance(double* resistors, int number);
static double calculate_parallel_resistance(double* resistors, int number);


//Function
void Basic_circuit_analyser() {
    int choice;

    do {
        printf("\nBasic Circuit Analyser\n");
        printf("1. Analyse Series Circuit\n");
        printf("2. Analyse Parallel Circuit\n");
        printf("3. Analyse Mixed Circuit\n");
        printf("4. Exit\n"); 
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                analyse_series_circuit();
                break;
            case 2:
                analyse_parallel_circuit();
                break;
            case 3:
                analyse_mixed_circuit();
                break;
            case 4: 
                printf("Exit.\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 4); 
}

static void calculate_current(double resistance) {
    if (resistance <= 0) {
        printf("Error: Resistance is zero or negative.\n");
        return;
    }
    
    double voltage;
    printf("\n--- Current Calculation ---\n");
    printf("Enter Voltage source (Volts): ");
    scanf("%lf", &voltage);
    double current = voltage / resistance;

    printf("Total Current: ");
    if (current < 0.001) {
        printf("%.3f µA\n", current * 1000000.0);
    } 
    else if (current < 1.0) {
        printf("%.3f mA\n", current * 1000.0);
    } 
    else {
        printf("%.3f A\n", current);
    }
}

static double calculate_series_resistance(double* resistors, int number) {
    double total = 0;
    for (int i = 0; i < number; i++) {
        total += resistors[i];
    }
    return total;
}

static double calculate_parallel_resistance(double* resistors, int number) {
    double total_inverse = 0;
    for (int i = 0; i < number; i++) {
        if (resistors[i] <= 0) {
            printf("Error: Resistor %d has invalid value (must be > 0)\n", i+1);
            return 0;
        }
        total_inverse += 1.0 / resistors[i];
    }
    return 1.0 / total_inverse;
}

static void print_resistance_with_units(double resistance) {
    if (resistance >= 1000000000) {
        printf("Resistance: %.3f GΩ\n", resistance / 1000000000.0);
    } 
    else if (resistance >= 1000000) {
        printf("Resistance: %.3f MΩ\n", resistance / 1000000.0);
    } 
    else if (resistance >= 1000) {
        printf("Resistance: %.3f KΩ\n", resistance / 1000.0);
    } 
    else {
        printf("Resistance: %.3f Ω\n", resistance);
    }
}

static void analyse_series_circuit(void) {
    int series_resistors;
    
    printf("\nSeries Circuit Analysis\n");
    printf("Enter number of resistors in series: ");
    scanf("%d", &series_resistors);
        
    if (series_resistors <= 0) {
        printf("Please enter a valid value.\n");
        return;
    }
        
    double* resistors = (double*)malloc(series_resistors * sizeof(double));
        
    printf("Enter resistor values (in ohms):\n");
    for (int i = 0; i < series_resistors; i++) {
        printf("R%d: ", i+1);
        scanf("%lf", &resistors[i]);
    }
        
    double total_resistance = calculate_series_resistance(resistors, series_resistors);
        
    printf("\nTotal resistance: ");
    print_resistance_with_units(total_resistance);
    calculate_current(total_resistance); 
      
    free(resistors);
}

static void analyse_parallel_circuit(void) {
    int parallel_resistors;
    printf("\nParallel Circuit Analysis\n");
    printf("Enter number of resistors in parallel: ");
    scanf("%d", &parallel_resistors);
        
    if (parallel_resistors <= 0) {
        printf("Please enter a valid value.\n");
        return;
    }
        
    double* resistors = (double*)malloc(parallel_resistors * sizeof(double));
        
    printf("Enter resistor values (in ohms):\n");
    for (int i = 0; i < parallel_resistors; i++) {
        printf("R%d: ", i+1);
        scanf("%lf", &resistors[i]);
    }
        
    double total_resistance = calculate_parallel_resistance(resistors, parallel_resistors);
        
    printf("\nTotal resistance: ");
    print_resistance_with_units(total_resistance);
    calculate_current(total_resistance);
    
    free(resistors);
}

static void analyse_mixed_circuit(void) {
    printf("\nAnalyse_mixed_circuit\n");
    printf("Start with 2 resistors, then add more one by one\n");
      
    double current_resistor;
    double R1, R2;
    int connection;
        
    printf("Enter first two resistors\n");
    printf("Resistor 1 (ohms): ");
    scanf("%lf", &R1);
    printf("Resistor 2 (ohms): ");
    scanf("%lf", &R2);
        
    if (R1 <= 0 || R2 <= 0) {
        printf("Error: Resistor values must be positive\n");
        return;
    }
        
    printf("\nHow are these resistors connected?\n1. Series\n2. Parallel\n");
    printf("Choice (1-2): ");
    scanf("%d", &connection);
    
    double temp_resistors[2];
    temp_resistors[0] = R1;
    temp_resistors[1] = R2;

    if (connection == 1) {
        current_resistor = calculate_series_resistance(temp_resistors, 2);
    } 
    else if (connection == 2) {
        current_resistor = calculate_parallel_resistance(temp_resistors, 2);
    } 
    else {
        printf("Invalid choice.\n");
        return;
    }

    printf("Current equivalent resistance: ");
    print_resistance_with_units(current_resistor);

    int choice = 0;
    do {
        printf("\nDo you want to add another resistor to this equivalent circuit?\n");
        printf("1. Yes\n2. No (Finish calculation)\n");
        printf("Choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            double next_R;
            int next_conn;

            printf("Enter next resistor value (ohms): ");
            scanf("%lf", &next_R);

            if (next_R <= 0) {
                printf("Error: Resistor must be positive.\n");
                return;
            }

            printf("How is this resistor connected to the previous equivalent circuit (%f Ohms)?\n", current_resistor);
            printf("1. Series\n2. Parallel\n");
            printf("Choice: ");
            scanf("%d", &next_conn);

            temp_resistors[0] = current_resistor;
            temp_resistors[1] = next_R;

            if (next_conn == 1) {
                current_resistor = calculate_series_resistance(temp_resistors, 2);
            } 
            else if (next_conn == 2) {
                current_resistor = calculate_parallel_resistance(temp_resistors, 2);
            } 
            else {
                printf("Invalid choice. \n");
            }

            printf("New equivalent resistance: ");
            print_resistance_with_units(current_resistor);
        }

    } while (choice != 2);

    printf("\nFinal Result:\n");
    print_resistance_with_units(current_resistor); 
    calculate_current(current_resistor);
}




