#include <stdio.h>
#include <string.h>
#include <math.h>

//constant values
const char* colour_names[]= {"Black","Brown","Red","Orange","Yellow","Green","Blue","Violet","Gray","White"};
double tolerance_values[]= {0.01, 0.02, 0.005, 0.0025, 0.001, 0.0005, 0.05, 0.10, 0.20};


void Resistor_colour_code_decoder(void);
static void show_colour_choice();
static int get_colour_choice(const char* prompt,int max_choice);
static double calculate_resistance(int band1, int band2, int multiplier);
static void print_resistance_with_units(double resistance);
static const char* get_tolerance_color(int tolerance_choice);
static int safe_int_range(int min, int max);


//Function
static void show_colour_choice(void) {
        printf("Color Code Chart\n");
        printf("0: Black\n1: Brown\n2: Red\n3: Orange\n4: Yellow\n5: Green\n6: Blue\n7: Violet\n8: Gray\n9: White\n");
    }


static int get_colour_choice(const char* prompt, int max_choice) {
        double temp;
        char c;

        printf("%s", prompt);

        while (scanf("%lf", &temp) != 1 || temp != (int)temp || (int)temp < 0 || (int)temp > max_choice)
        {
            printf("Invalid choice! Please enter a number between 0 and %d: ",max_choice);
            while ((c = getchar()) != '\n' && c != EOF);
        }
        while ((c = getchar()) != '\n' && c != EOF);

        return (int)temp;
}


static double calculate_resistance(int band1, int band2, int multiplier) {
        int value = band1 * 10 + band2;
        return value * pow(10, multiplier);
    }


static const char* get_tolerance_color(int tolerance_choice) {
    switch(tolerance_choice) {
        case 0: return "Brown (±1%)";
        case 1: return "Red (±2%)";
        case 2: return "Green (±0.5%)";
        case 3: return "Blue (±0.25%)";
        case 4: return "Violet (±0.1%)";
        case 5: return "Gray (±0.05%)";
        case 6: return "Gold (±5%)";
        case 7: return "Silver (±10%)";
        case 8: return "None (±20%)";
        default: return "Error,please enter a valid value.\n ";
        }
    }


static void print_resistance_with_units(double resistance) {
    if (resistance >= 1000000000) {
        printf("%.3f GΩ", resistance / 1000000000.0);
    } 
    else if (resistance >= 1000000) {
        printf("%.3f MΩ", resistance / 1000000.0);
    } 
    else if (resistance >= 1000) {
        printf("%.3f KΩ", resistance / 1000.0);
    } 
    else {
        printf("%.3f Ω", resistance);
        }
    }


//Protection
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




void Resistor_colour_code_decoder(void) {
    int choice = 0;

    do {
        printf("\n----------- Resistor Colour Code Decoder -----------\n");
        printf("1. Decode a resistor\n");
        printf("2. Return to Main Menu\n");
        printf("Enter your choice: ");
        choice = safe_int_range(1, 2);

        if (choice == 1) {
            printf("Enter the color codes for each band:\n");
            show_colour_choice();
        
            int band1 = get_colour_choice("First band: ", 9);
            int band2 = get_colour_choice("Second band: ", 9);
            int multiplier = get_colour_choice("Third band: ", 9);
        
            printf("\nTolerance Colors\n");
            printf("0: Brown (±1%%)\n""1: Red (±2%%)\n""2: Green (±0.5%%)\n""3: Blue (±0.25%%)\n""4: Violet (±0.1%%)\n");
            printf("5: Gray (±0.05%%)\n""6: Gold (±5%%)\n""7: Silver (±10%%)\n""8: None (±20%%)\n");
    

            int tolerance = get_colour_choice("Fourth band (tolerance): ", 8);
            double resistance = calculate_resistance(band1, band2, multiplier);
            const char* tolerance1 = get_tolerance_color(tolerance);
            double percent = tolerance_values[tolerance];  
            double max_value = resistance * (1 + percent);
            double min_value = resistance * (1 - percent);

        
            printf("\nDecoding Results\n");
            printf("Color Code: %s - %s - %s - %s\n", colour_names[band1], colour_names[band2], 
                    colour_names[multiplier], tolerance1);
            printf("Resistor value:");
            print_resistance_with_units(resistance);
            printf("\nTolerance: %s", tolerance1);
            printf("\nActual resistance range:");
            print_resistance_with_units(min_value);
            printf(" ~ ");
            print_resistance_with_units(max_value);
            printf("\n\n");

        }
    } while (choice != 2);

    printf("Thank you for using the Resistor colour code decoder\nReturn to Main Menu...\n");
}