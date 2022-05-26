#include "bin_file_car.h"
#include "file_return_codes.h"

#include <string.h>
#include <stdlib.h>


#define NOT_ENOUGH_PARAMS -10
#define UNKNOWN_PARAMS -11
#define INVALID_PARAMS 53

int main(int argc, char **argv)
{
    if (argc == 1)
        return INVALID_PARAMS;
    char *command = argv[1];
    if (!strcmp(command, "sb"))
    {
        FILE *f = fopen(argv[2], "r+");
        bin_file_sort_by_car_type(f, '1');
        fclose(f);
    }
    else if (!strcmp(command, "ab"))
    {
        FILE *f = fopen(argv[2], "r+");
        long pos = atoi(argv[3]);
        Car_t car;
        scanf("%s %s %ld %ld", car.Car_type, car.Number, &car.mass, &car.litrage);
        bin_file_insert_car(f, pos, car);
        fclose(f);
    }
    else if (!strcmp(command, "db"))
    {
        FILE *f = fopen(argv[2], "r+");
        bin_file_del_car_by_litrage(f, 10);
        fclose(f);
    }
    else if (!strcmp(command, "aap"))
    {
        FILE *f = fopen(argv[2], "r+");
        Car_t car;
        insert_best_car_after_porshe(f, car);
        fclose(f);
    }
    else if (!strcmp(command, "p"))
    {
        FILE *f = fopen(argv[2], "rb");
        f_printf(f);
        fclose(f);
    }
    else if (!strcmp(command, "w"))
    {
        FILE *f = fopen(argv[2], "wb");
        Car_t car;
        f_writef(f, car);
        fclose(f);
    }
    
}
