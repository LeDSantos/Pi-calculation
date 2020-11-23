#ifndef HEADER_FILE_ENERGY
#define HEADER_FILE_ENERGY

#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <time.h>

#define ENERGIA 1

void rapl_init(void);
void start_rapl_sysfs();
double end_rapl_sysfs();

#endif