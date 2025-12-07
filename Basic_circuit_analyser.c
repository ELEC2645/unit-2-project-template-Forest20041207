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
static double safe_double();
static double safe_positive_double();
static int safe_int_range(int min, int max);



//Function
void Basic_circuit_analyser() {
    int choice;

    do {
        printf("\n----------- Basic Circuit Analyser -----------\n");
        printf("1. Series Circuit Analysis\n");
        printf("2. Parallel Circuit Analysis\n");
        printf("3. Mixed Circuit Analysis\n");
        printf("4. Return to Main Menu\n");
        printf("----------------------------------------------\n");
        printf("Select an option: ");
        choice = safe_int_range(1, 4);

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
                printf("Thank you for using the Basic circuit analyser\nReturn to Main Menu...\n");
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
    printf("\n------ Current Calculation ------\n");
    printf("Enter Voltage source (Volts): ");
    voltage = safe_double();
    if (voltage < 0) {
        printf("Voltage cannot be negative. Enter again:\n");
        voltage = safe_double();
        return;
    }

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
    
    printf("\n------ Series Circuit Analysis ------\n");
    printf("Enter number of resistors in series: ");
    series_resistors = safe_int_range(1, 100);
        
    double* resistors = (double*)malloc(series_resistors * sizeof(double));
    if (resistors == NULL) {
        printf("Error: not enough memory.\n");
        return; 
    }
        
    printf("Enter resistor values (in ohms):\n");
    for (int i = 0; i < series_resistors; i++) {
        printf("R%d: ", i+1);
        resistors[i] = safe_positive_double();

    }
        
    double total_resistance = calculate_series_resistance(resistors, series_resistors);
        
    printf("\n----------- Calculation Result -----------\n");
    printf("Total Resistance : ");
    print_resistance_with_units(total_resistance);
    printf("-----------------------------------------\n");

    calculate_current(total_resistance);

      
    free(resistors);
}


static void analyse_parallel_circuit(void) {
    int parallel_resistors;
    printf("\n------ Parallel Circuit Analysis ------\n");
    printf("Enter number of resistors in parallel: ");
    parallel_resistors = safe_int_range(1, 100);
        
    double* resistors = (double*)malloc(parallel_resistors * sizeof(double));
    if (resistors == NULL) {
        printf("Error: not enough memory.\n");
        return; 
    }
        
    printf("Enter resistor values (in ohms):\n");
    for (int i = 0; i < parallel_resistors; i++) {
        printf("R%d: ", i+1);
        resistors[i] = safe_positive_double();
    }
        
    double total_resistance = calculate_parallel_resistance(resistors, parallel_resistors);
        
    printf("\n----------- Calculation Result -----------\n");
    printf("Total Resistance : ");
    print_resistance_with_units(total_resistance);
    printf("-----------------------------------------\n");

    calculate_current(total_resistance);

    
    free(resistors);
}


static void analyse_mixed_circuit(void) {
    printf("\n------ Analyse_mixed_circuit ------\n");
    printf("Start with 2 resistors, then add more one by one\n");
      
    double current_resistor;
    double R1, R2;
    int connection;
        
    printf("Enter first two resistors\n");
    printf("Resistor 1 (ohms): ");
    R1 = safe_positive_double();
    printf("Resistor 2 (ohms): ");
    R2 = safe_positive_double();
        
        
    printf("\nHow are these resistors connected?\n1. Series\n2. Parallel\n");
    printf("Choice (1-2): ");
    connection = safe_int_range(1, 2);

    
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
        choice = safe_int_range(1, 2);

        if (choice == 1) {
            double next_R;
            int next_conn;

            printf("Enter next resistor value (ohms): ");
            next_R = safe_positive_double();


            printf("How is this resistor connected to the previous equivalent circuit (%f Ohms)?\n", current_resistor);
            printf("1. Series\n2. Parallel\n");
            printf("Choice: ");
            next_conn = safe_int_range(1, 2);

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

    printf("\n----------- Calculation Result -----------\n");
    printf("Final Resistance : ");
    print_resistance_with_units(current_resistor);
    printf("-----------------------------------------\n");

    calculate_current(current_resistor);

}


//Protection
static double safe_double() {
    double value;
    char c;

    while (scanf("%lf", &value) != 1) {
        printf("Invalid input! Enter a number: ");
        while ((c = getchar()) != '\n' && c != EOF);
    }

    while ((c = getchar()) != '\n' && c != EOF);
    return value;
}

static double safe_positive_double() {
    double value;
    do {
        value = safe_double();
        if (value <= 0) printf("Value must be > 0. Enter again: ");
    } while (value <= 0);

    return value;
}

static int safe_int_range(int min, int max) {
    double temp;
    char c;

    while (scanf("%lf", &temp) != 1 || temp != (int)temp || (int)temp < min || (int)temp > max)
    {
        printf("Enter an integer between %d and %d: ", min, max);
        while ((c = getchar()) != '\n' && c != EOF);
    }

    while ((c = getchar()) != '\n' && c != EOF);
    return (int)temp;
}



