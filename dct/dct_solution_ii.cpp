#include <iostream>
#include <cmath>
#include <math.h>
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif
using namespace std;


static const float c0 =  0.353553391 ;    //1. / sqrt(2.) * sqrt(2. / 8.);
static const float c1 =  0.49039264  ;   //cos(M_PI * 1. / 16.) * sqrt(2. / 8.);
static const float c2 =  0.461939766 ;  //cos(M_PI * 2. / 16.) * sqrt(2. / 8.);
static const float c3 =  0.415734806 ; //cos(M_PI * 3. / 16.) * sqrt(2. / 8.);
static const float c4 =  0.353553391 ;//cos(M_PI * 4. / 16.) * sqrt(2. / 8.);
static const float c5 =  0.277785117 ;   //cos(M_PI * 5. / 16.) * sqrt(2. / 8.);
static const float c6 =  0.191341716 ;  //cos(M_PI * 6. / 16.) * sqrt(2. / 8.);
static const float c7 =  0.097545161 ; //cos(M_PI * 7. / 16.) * sqrt(2. / 8.);

#define a x[0]
#define b x[1]
#define c x[2]
#define d x[3]
#define e x[4]
#define f x[5]
#define g x[6]
#define h x[7]

void dct_ii_8a(const float x[8], float X[8]) {
  X[0] = a*c0 + b*c0 + c*c0 + d*c0 + e*c0 + f*c0 + g*c0 + h*c0;
  X[1] = a*c1 + b*c3 + c*c5 + d*c7 - e*c7 - f*c5 - g*c3 - h*c1;
  X[2] = a*c2 + b*c6 - c*c6 - d*c2 - e*c2 - f*c6 + g*c6 + h*c2;
  X[3] = a*c3 - b*c7 - c*c1 - d*c5 + e*c5 + f*c1 + g*c7 - h*c3;
  X[4] = a*c4 - b*c4 - c*c4 + d*c4 + e*c4 - f*c4 - g*c4 + h*c4;
  X[5] = a*c5 - b*c1 + c*c7 + d*c3 - e*c3 - f*c7 + g*c1 - h*c5;
  X[6] = a*c6 - b*c2 + c*c2 - d*c6 - e*c6 + f*c2 - g*c2 + h*c6;
  X[7] = a*c7 - b*c5 + c*c3 - d*c1 + e*c1 - f*c3 + g*c5 - h*c7;
}

int main()
{
    int i;
    float aMatrix[8] = {66,22,25,32,63,34,12,65};
    float bMatrix[8];

    dct_ii_8a(aMatrix,bMatrix);
    for (i=0;i<8;i++)
    {
        cout << bMatrix[i] <<endl;
    }

    return 0;
}
