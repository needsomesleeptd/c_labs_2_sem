#include "bin_file_car.h"
#include "file_return_codes.h"
#include "struct_car.h"

#include <sys/types.h>
#include <unistd.h>
#include <string.h>

void f_printf(FILE *f)
{
	long cars = bin_file_cars_cnt(f);
	for (long i = 0; i < cars; i++)
	{
		Car_t car;
		get_car_by_pos(f, i, &car);
		print_car(car);
	}
		
}

void f_writef(FILE *f, Car_t car)
{
	long cars = bin_file_cars_cnt(f);
	put_car_by_pos(f, cars, car);
		
}

int get_car_by_pos(FILE *f, long pos, Car_t *car)
{
    pos *= sizeof(Car_t);
	if (fseek(f, pos, SEEK_SET))
		return FILE_MOV_ERROR;
	if (fread(car, sizeof(Car_t), 1, f) != 1)
		return FILE_READ_ERROR;
	return OK;
}

int  put_car_by_pos(FILE *f, long pos, Car_t car)
{
    pos *= sizeof(Car_t);
	if (fseek(f, pos, SEEK_SET))
		return FILE_MOV_ERROR;
	if ((fwrite(&car, sizeof(Car_t), 1, f)) != 1)
		return FILE_WRITE_ERROR;
	return OK;
}

int bin_file_swap_cars(FILE *f, int pos_1, int pos_2)
{

	Car_t car_1;
	int error_code = 0;
	if ((error_code = get_car_by_pos(f, pos_1, &car_1)))
		return error_code;
	Car_t car_2;
	if ((error_code = get_car_by_pos(f, pos_2, &car_2)))
		return error_code;
	
	if ((error_code = put_car_by_pos(f, pos_1, car_2)))
		return error_code;
	
	if ((error_code = put_car_by_pos(f, pos_2, car_1)))
		return error_code;

	return OK;
}

long bin_file_cars_cnt(FILE *f)
{	
	long saved_pos = ftell(f);
	if (saved_pos < 0)
		return FILE_TELL_ERROR;
	if (fseek(f, 0, SEEK_END))
		return FILE_MOV_ERROR;
	long f_size;
	if ( (f_size = ftell(f)) < 0)
		return FILE_TELL_ERROR;
	if (f_size % sizeof(Car_t) != 0)
		return FILE_DESCR_NOT_VALID;
	long cars_cnt = f_size / sizeof(Car_t);
	if (fseek(f, saved_pos, SEEK_SET))
		return FILE_MOV_ERROR;
	return cars_cnt;
}

int bin_file_sort_by_car_type(FILE *f, char rule)
{	
    
	long cars_cnt =  bin_file_cars_cnt(f);
	if (cars_cnt < 0)
		return cars_cnt;
	int error_code;
	for (long  i = 0; i < cars_cnt - 1; i++)
		for (long j = i + 1; j < cars_cnt; j++)
		{
			Car_t car_1;
			Car_t car_2;
			if ((error_code = get_car_by_pos(f, i, &car_1)))
				return error_code;
			if ((error_code = get_car_by_pos(f, j, &car_2)))
				return error_code;
			if (strcmp(car_1.Car_type, car_2.Car_type) > 0)
			{
				if ((error_code = bin_file_swap_cars(f, i, j)))
					return error_code;
			}
			
		}

	return cars_cnt;
}


int bin_file_del_car_by_litrage(FILE *f, long min_litrage)
{
	long len = bin_file_cars_cnt(f);
	for (long i = 0; i < len; i++)
	{
		Car_t car;
		get_car_by_pos(f, i, &car);
		if (min_litrage > car.litrage)
		{
			bin_file_del_car_by_pos(f, i, &len);
			i--;
		}
	}
	ftruncate(fileno(f), len * sizeof(Car_t));
	return len;
}

void bin_file_del_car_by_pos(FILE *f, long pos, long *len)
{
	for (long i = pos; i < *len - 1; i++)
		bin_file_swap_cars(f, pos, pos + 1);
	*len -= 1;
}

int bin_file_insert_car(FILE *f, long pos, Car_t car)
{
    if (!fseek(f, 0, SEEK_END))
        return FILE_MOV_ERROR;
    if (fwrite(&car, sizeof(Car_t), 1, f) != 1)
        return FILE_WRITE_ERROR;
    long cars_cnt;
    if ((cars_cnt = bin_file_cars_cnt(f)) < 0)
        return cars_cnt;
    put_car_by_pos(f, cars_cnt, car);
    for (long i = cars_cnt; i > pos; i++)
        bin_file_swap_cars(f, i, i - 1);
    return cars_cnt;
}

int insert_best_car_after_porshe(FILE *f, Car_t car)
{
    long cars_cnt;
    Car_t lada;
    strcpy(lada.Car_type, "lada");
    strcpy(lada.Number, "228 никого не просим");
    lada.litrage = 20;
    lada.mass = 30;
    if ((cars_cnt = bin_file_cars_cnt(f)) < 0)
        return cars_cnt;
    for (long i = 0; i < cars_cnt; i++)
    {
        Car_t car;
        get_car_by_pos(f, i, &car);
		if (!strcmp(car.Car_type, "Porsche"))
        	bin_file_insert_car(f, i + 1, lada);
    }

    return OK;
}




