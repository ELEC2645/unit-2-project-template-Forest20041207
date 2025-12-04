#include <stdio.h>
#include <math.h>

//Definition
#define Square_root_3 1.732050808
#define PI 3.141592654 


//Functions
static double calculate_power_factor(double angle_degrees) {
    double angle_radians = angle_degrees * (PI / 180.0);
    return cos(angle_radians);
}


static void print_power_with_units(double value, const char* unit) {
    double absolute_value = fabs(value); 
    
    if (absolute_value >= 1000000000.0) {
        printf("%.3f G%s\n", absolute_value / 1000000000.0, unit);
    } 
    else if (absolute_value >= 1000000.0) {
        printf("%.3f M%s\n", absolute_value / 1000000.0, unit);
    } 
    else if (absolute_value >= 1000.0) {
        printf("%.3f k%s\n", absolute_value / 1000.0, unit);
    } 
    else {
        printf("%.3f %s\n", absolute_value, unit);
    }
}


static void calculate_three_phase_power(void) {
    int connection_choice;
    double line_voltage, line_current, phase_angle;

    printf("Select Connection Type:\n");
    printf("1. Star Connection (Y)\n");
    printf("2. Delta Connection (Δ)\n");
    printf("Enter choice: ");
    
    if (scanf("%d", &connection_choice) != 1 || (connection_choice != 1 && connection_choice != 2)) {
        printf("Invalid input.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    printf("Enter Line Voltage (V): ");
    if (scanf("%lf", &line_voltage) != 1 || line_voltage <= 0) {
        printf("Line voltage must be a positive value.\n");
        while (getchar() != '\n');
        return;
    }
    
    printf("Enter Line Current (A): ");
    if (scanf("%lf", &line_current) != 1 || line_current <= 0) {
        printf("Line current must be a positive value.\n");
        while (getchar() != '\n');
        return;
    }

    printf("Enter Phase Angle φ (degrees, positive for Inductive, negative for Capacitive): ");
    if (scanf("%lf", &phase_angle) != 1) {
        printf("Invalid phase angle input.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    double power_factor = calculate_power_factor(phase_angle);
    double cos_phi = power_factor;
    double sin_phi = sin(phase_angle * (PI / 180.0));
    
    double apparent_power_S = Square_root_3 * line_voltage * line_current;
    
    double active_power_P = apparent_power_S * cos_phi;
    
    double reactive_power_Q = apparent_power_S * sin_phi;
    
    printf("\nThree-Phase Power Calculation Results\n");
    printf("Connection Type: ");
    if (connection_choice == 1) {
        printf("Star (Y)\n");
    } else {
        printf("Delta (Δ)\n");
    }
    
    printf("Power Factor (PF): %.4f ", fabs(cos_phi)); 
    if (phase_angle > 0.001) {
        printf("(Lagging/Inductive)\n");
    } 
    else if (phase_angle < -0.001) {
        printf("(Leading/Capacitive)\n");
    } 
    else {
        printf("(Resistive)\n");
    }
    
    printf("1. Total Apparent Power (S): \n");
    print_power_with_units(apparent_power_S, "VA");
    
    printf("2. Total Active Power (P): \n");
    print_power_with_units(active_power_P, "W");
    
    printf("3. Total Reactive Power (Q): \n");
    print_power_with_units(reactive_power_Q, "VAR"); // prints absolute value internally
    
    
    if (connection_choice == 1) { 
        printf("Phase Voltage: %.3f V\n", line_voltage / Square_root_3);
        printf("Phase Current: %.3f A\n", line_current);
    } 
    else { 
        printf("Phase Voltage: %.3f V\n", line_voltage);
        printf("Phase Current: %.3f A\n", line_current / Square_root_3);
    }
}


void Three_phase_power_calculator(void) {
    int choice = 0;
    
    do {
        printf("\nThree-Phase Power Calculator\n");
        printf("1. Start Calculation\n");
        printf("2. Back to Main Menu (Exit)\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please re-enter.\n");
            while (getchar() != '\n');
            choice = 0;
            continue;
        }
        while (getchar() != '\n'); 

        switch (choice) {
            case 1:
                calculate_three_phase_power();
                break;
            case 2:
                printf("Exiting Three-Phase Power Calculator.\n");
                break;
            default:
                printf("Invalid option.\n");
        }
    } while (choice != 2);
}

