#include <iostream>
using namespace std;

int * zeroes(int n)
{
    int *f = new int[n];
    for (int i = 0; i < n; i++)
    {
        f[i] = 0;
    }
    return f;
}

int ** zeroes(int rows, int cols)
{
    int **f = new int *[rows];
    for (int i = 0; i < rows; i++)
    {
        f[i] = zeroes(cols);
    }
    return f;
}

int *** zeroes(int depth, int rows, int cols)
{
    int ***f = new int **[depth];
    for (int i = 0; i < depth; i++)
    {
        f[i] = zeroes(rows, cols);
    }
    return f;
}

void delete_array(int *f)
{
    delete[] f;
}

void delete_array(int **f, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        delete_array(f[i]);
    }
    delete[] f;
}

void delete_array(int ***f, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        delete_array(f[i], cols);
    }
    delete[] f;
}

void print_array(int *f, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << f[i] << "\t";
    }
    cout << endl;
}

void print_array(int **f, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        print_array(f[i], cols);
    }
}

void print_array(int ***f, int rows, int cols, int depth)
{
    for (int i = 0; i < depth; i++)
    {
        cout << "Layer " << i << endl;
        print_array(f[i], rows, cols);
    }
}