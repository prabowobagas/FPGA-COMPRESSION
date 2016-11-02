#include "dct.h"


static const float c0 =  0.353553391 ;  //1. / sqrt(2.) * sqrt(2. / 8.);
static const float c1 =  0.49039264  ;  //cos(M_PI * 1. / 16.) * sqrt(2. / 8.);
static const float c2 =  0.461939766 ;  //cos(M_PI * 2. / 16.) * sqrt(2. / 8.);
static const float c3 =  0.415734806 ;  //cos(M_PI * 3. / 16.) * sqrt(2. / 8.);
static const float c4 =  0.353553391 ;  //cos(M_PI * 4. / 16.) * sqrt(2. / 8.);
static const float c5 =  0.277785117 ;  //cos(M_PI * 5. / 16.) * sqrt(2. / 8.);
static const float c6 =  0.191341716 ;  //cos(M_PI * 6. / 16.) * sqrt(2. / 8.);
static const float c7 =  0.097545161 ;  //cos(M_PI * 7. / 16.) * sqrt(2. / 8.);

//c++ rounds down, so if it is not working add +0.5

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

void matrix_transpose(float inMatrix[8][8],float transposed_matrix[8][8])
{
    int i,j;
    float buffer_matrix[8][8]={0};
    for (i=0;i<8;i++)
    {
        for(j=0;j<8;j++)
        {
            buffer_matrix[i][j]=inMatrix[j][i];
        }
    }
    for (i=0;i<8;i++)
    {
        for(j=0;j<8;j++)
        {
            transposed_matrix[i][j]=buffer_matrix[i][j];
        }
    }
}


void quantitized(float inMatrix[8][8],int doneMatrix[8][8])
{
	int i,j;
	float q_50[8][8]=
	{
			{16,11,10,16,24,40,51,61},
			{12,12,14,19,26,58,60,55},
			{14,13,16,24,40,57,69,56},
			{14,17,22,29,51,87,80,62},
			{18,22,37,56,68,109,103,77},
			{24,35,55,64,81,104,113,92},
			{49,64,78,87,103,121,120,101},
			{72,92,95,68,112,100,103,99}
	};
	for (i=0;i<8;i++)
	{
		for (j=0;j<9;j++)
		{
			doneMatrix[i][j]= round(inMatrix[i][j]/q_50[i][j]);
		}
	}
}

void dct_2d(const float inMatrix[8][8],int doneMatrix[8][8])
{
    float bMatrix[8][8]={0},cMatrix[8][8]={0};
    int i,j;

    for (i=0;i<8;i++)
    {
        dct_ii_8a(inMatrix[i],bMatrix[i]);
    }

    matrix_transpose(bMatrix,bMatrix);

    for (i=0;i<8;i++)
    {
        dct_ii_8a(bMatrix[i],cMatrix[i]);
    }
    matrix_transpose(cMatrix,cMatrix);
    quantitized(cMatrix,doneMatrix);
}
