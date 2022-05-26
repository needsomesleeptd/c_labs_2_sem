#include "struct_car.h"
#include <stdio.h>

void print_car(Car_t car)
{
    printf("Car: %s\n", car.Car_type);
    printf("Number: %s\n", car.Number);
    printf("Car: %ld\n", car.litrage);
    printf("Car: %ld\n", car.mass);
}
