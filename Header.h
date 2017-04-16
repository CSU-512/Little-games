#ifndef CHK
#define CHK
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#endif
using namespace std;
void newelement(int arr[][4]);
int getoperation(int arr[][4]);
void printgrid(int arr[4][4]);
void gridinit(int arr[4][4]);
void gridmanip(int arr[][4], int operation);
void moveright(int arr[][4]);
void moveleft(int arr[][4]);
void moveup(int arr[][4]);
void movedown(int arr[][4]);
void isupmovable(int arr[][4]);
void isdownmovable(int arr[][4]);
void isleftmovable(int arr[][4]);
void isrightmovable(int arr[][4]);
//void test();