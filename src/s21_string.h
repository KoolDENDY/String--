#ifndef S21_STRING_H
#define S21_STRING_H

#include <math.h>
#include <stdarg.h>

#define S21_NULL ((void *)0)

typedef unsigned long s21_size_t;

typedef struct {
  int minus;      
  int plus;       
  int space;      
  int hash;       
  int zero;       
  int width;      
  int precision;  
  char length;    
} s21_spec_t;

int s21_sprintf(char *str, const char *format, ...);

#endif 
