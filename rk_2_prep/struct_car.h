#ifndef _STRUCT_CAR_H_
#define _STRUCT_CAR_H_

#define TYPE_CAR_LEN 21
#define NUMBER_LEN 21

struct Car
{
    char Car_type[TYPE_CAR_LEN];
    char Number[NUMBER_LEN];
    long litrage;
    long mass;
};

typedef struct Car Car_t;

void print_car(Car_t car);

#endif // _STRUCT_CAR_H_