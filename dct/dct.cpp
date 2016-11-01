#include <iostream>
#include <math.h>
#define M_PI 3.1415926535897
using namespace std;
void dct_ii_8(const float x[8], float X[8]);


void dct_ii_8(const float x[8], float X[8]) {
  for (int k = 0; k < 8; ++k) {
    float sum = 0.;
    float s = (k == 0) ? sqrt(.5) : 1.;
    for (int n = 0; n < 8; ++n) {
      sum += s * x[n] * cos(M_PI * (n + .5) * k / 8);
    }
    X[k] = sum * sqrt(2. / 8);
  }
}
int main()
{
    int i;
    float aMatrix[8] = {255,255,255,255,255,255,255,255};
    float bMatrix[8];

    dct_ii_8(aMatrix,bMatrix);
    for (i=0;i<8;i++)
    {
        cout << round(bMatrix[i]) <<endl;
    }

    return 0;
}
