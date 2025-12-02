#include <stdio.h>
#include <string.h>
#include <math.h>

//constant values
const char* colour_names[]= {"Black","Brown","Red","Orange","Yellow","Green","Blue","Violet","Gray","White"};
const char* tolerance_colours[]= {"Brown","Red","Green","Blue","Blue","Violet","Gray","Gold","Sliver","None"};
double tolerance_values[]= {1,2,0.5,0.25,0.1,0.05,5,10,20};

//Function prototype
void Resistor_colour_code_decoder(void)
static void show_colour_choice()
static int get_colour_choice(const char* prompt,int max_choice)
static double calculate_resistance(int band1, int band2, int multiplier);
static void print_resistance_with_units(double resistance, int multiplier);
static const char* get_tolerance_color(int tolerance_choice);

//Function
static void show_color_choice(void) {
        printf("Color Code Chart\n");
        printf("0: Black\n1: Brown\n2: Red\n3: Orange\n4: Yellow\n5: Green\n6: Blue\n7: Violet\n8: Gray\n9: White\n");
    }


static int get_color_choice(const char* prompt, int max_choice) {
        int choice;
        while (1) {
            printf("%s", prompt);
            if (scanf("%d", &choice) == 1) {
                if (choice >= 0 && choice <= max_choice) {
                    break;
                }
            }
            printf("Invalid choice! Please enter a number between 0 and %d\n", max_choice);
            while (getchar() != '\n');
        }
        return choice;
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


static void print_resistance_with_units(double resistance, int multiplier) {
    const char* units[] = {"Ω", "kΩ", "MΩ", "GΩ"};
    int unit = 0;
    double value = resistance;
        
    while (value >= 1000.0 && unit < 3) {
            value /= 1000.0;
            unit++;
    }  
    printf("Resistance: %.2f %s", value, units[unit]);
        
    if (multiplier >= 0) {
        printf(" (%.0f * 10^%d Ω)", resistance / pow(10, multiplier), multiplier);
    } 
    else {
            printf(" (%.3f Ω)", resistance);
        }
    }


void Resistor_colour_code_decoder(void) {
    printf("Enter the color codes for each band:\n");
    show_color_chart();
        
    int band1 = get_color_choice("First band: ", 9);
    int band2 = get_color_choice("Second band: ", 9);
    int multiplier = get_color_choice("Third band: ", 9);
        
    printf("\nTolerance Colors\n");
    printf("0: Brown (±1%%)\n1: Red (±2%%)\n2: Green (±0.5%%)\n3: Blue (±0.25%%)\n4: Violet (±0.1%%)\n
        5: Gray (±0.05%%)\n6: Gold (±5%%)\n7: Silver (±10%%)\n8: None (±20%%)\n");
    

    int tolerance = get_color_choice("Fourth band (tolerance): ", 8);
    double resistance = calculate_resistance(band1, band2, multiplier);
    const char* tolerance1 = get_tolerance_color(tolerance);
        
    printf("\nDecoding Results\n");
    printf("Color Code: %s - %s - %s - %s\n", color_names[band1], color_names[band2], 
            color_names[multiplier], tolerance1);
        
    print_resistance_with_units(resistance, multiplier);
    printf("\nTolerance: %s\n", tolerance1);
}