#ifndef _BIN_FILE_CAR_H_
#define _BIN_FILE_CAR_H_

#include "struct_car.h"

#include <stdio.h>

int get_car_by_pos(FILE *f, long pos, Car_t *car);
int put_car_by_pos(FILE *f, long pos, Car_t car);
int bin_file_swap_cars(FILE *f, int pos_1, int pos_2);
long bin_file_cars_cnt(FILE *f);
int bin_file_sort_by_car_type(FILE *f, char rule);
int bin_file_del_car_by_litrage(FILE *f, long min_litrage);
int bin_file_insert_car(FILE *f, long pos, Car_t car);
int insert_best_car_after_porshe(FILE *f, Car_t car);
void bin_file_del_car_by_pos(FILE *f, long pos, long *len);
void f_printf(FILE *f);
void f_writef(FILE *f, Car_t car);

#endif // _BIN_FILE_CAR_H_