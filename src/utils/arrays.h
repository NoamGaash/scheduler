#pragma once

int * zeroes(int n);
int ** zeroes(int rows, int cols);
int *** zeroes(int depth, int rows, int cols);

void delete_array(int *f);
void delete_array(int **f, int rows);
void delete_array(int ***f, int rows, int cols);

void print_array(int *f, int n);
void print_array(int **f, int rows, int cols);
void print_array(int ***f, int rows, int cols, int depth);
