#include "dct.h"
void matrix_transpose(float inMatrix[8][8],float transposed_matrix[8][8]);
void dct_ii_8a(const float x[8], float X[8]);
void dct_2d(const float inMatrix[8][8],float outMatrix[8][8]);

int main()
{
    int i,j;
    float aMatrix[8][8] =
    {
        {255,255,255,255,255,255,255,255},
        {255,255,255,255,255,255,255,255},
        {255,255,255,255,255,255,255,255},
        {255,255,255,255,255,255,255,255},
        {255,255,255,255,255,255,255,255},
        {255,255,255,255,255,255,255,255},
        {255,255,255,255,255,255,255,255},
        {255,255,255,255,255,255,255,255}
    };

    dct_2d(aMatrix,aMatrix);
    for (i = 0; i < 8; ++i)
    {
        for (j = 0; j < 8; ++j)
        {
            cout << aMatrix[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;


    return 0;
}
