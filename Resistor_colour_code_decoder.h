#ifndef RESISTOR_COLOUR_CODE_DECODER_H
#define RESISTOR_COLOUR_CODE_DECODER_H

// Function declaration
void Resistor_colour_code_decoder(void);
static void show_colour_choice();
static int get_colour_choice(const char* prompt,int max_choice);
static double calculate_resistance(int band1, int band2, int multiplier);
static void print_resistance_with_units(double resistance);
static const char* get_tolerance_color(int tolerance_choice);

#endif