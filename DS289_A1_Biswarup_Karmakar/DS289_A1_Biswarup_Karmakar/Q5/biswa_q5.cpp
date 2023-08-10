#include<iostream>
#include<vector>
#include<string.h>
#include<sstream>
#include<fstream>
#include<math.h>
#include<stdlib.h>
#include <cstdlib>

#define size 1024

using namespace std ;

typedef double real;

void temp_ode_solver(int s, real *R,real *T, real &temperature){
    int i, j;
    real **temp_mat, b[size];
    real r_in=0, r_out=1;
    real r;
    real dr = (r_out-r_in)/(size-1);
    
    temp_mat = new real*[size];
    for(i=0 ; i<size ; i++ )
        temp_mat[i] = new real[size];
    
    //initialize matrix with 0
    for(j=0; j<size; j++)
    	for(i=0; i<size; i++)
            temp_mat[i][j] = 0;
            
    // given r at end r=1 T=1 so adding in matrix 
    
    T[size-1] = 1;  //  T[1023] = 1
    b[size-1] = 1;
    temp_mat[size-1][size-1] = 1;
    
    
    // at r= 0 dt/dr =0 is given so initialising this
    temp_mat[0][0] = -1;   //  T(dr)-T(0) = 0
    temp_mat[0][1] = 1;
    b[0] = 0;   //  dT/dr(0) = 0

    //for left values of b we have calculated the rhs it is -2s*r^2 * dr^2
    R[0]=r_in;
    r = r_in+dr;
    R[1]=r;
    i=1;
    while(i<size-1){
        b[i] = -s*r*dr*dr;
        r += dr;
        R[i+1] =r;
        i++;
    }
    b[size-1]=1;
    //initialize A    
      //  1*Tn = 1
    

    r = r_in+dr;
    i=1;
    while(i<size-1){
        temp_mat[i][i-1] = r;
        temp_mat[i][i]   = -2*r-dr;
        temp_mat[i][i+1] = r+dr;
        r += dr;
        i++;
    }
    
	// upper traingular matrix operation
	for(i=1 ; i<size-1 ; i++ ){
        real u = temp_mat[i][i-1] / temp_mat[i-1][i-1];
        temp_mat[i][i-1] -= u*temp_mat[i-1][i-1];
        temp_mat[i][i]   -= u*temp_mat[i-1][i];
        temp_mat[i][i+1] -= u*temp_mat[i-1][i+1];

        b[i] -= u*b[i-1];
    }

	// back substitution
    for(i=size-2 ; i>=0 ; i--){
        T[i] = ( b[i] - temp_mat[i][i+1]*T[i+1] ) / temp_mat[i][i];
    }
    
}


int main()
{  
    int S[4] = {100, 500, 1000, 1500 };
    real temperature;

    real *T = new real[size];
    real *R = new real[size];
    int p= 0;
    while(p<4)
         {
         temp_ode_solver(S[p],R , T,temperature);
         
     //for(int i=0; i<size; i++)
       //{ cout<<T[i]<<" "; }
       string name = "radius_temp_"+ to_string(S[p]);

		ofstream f1;
		f1.open(name+".txt");
        f1  <<"Radius" << '\t'<< "Temperature" << endl;
        int i=0;
		while(i<size)
		{
		    f1 << R[i] << '\t' << T[i] << "\n";
		    i++;
		}
		f1.close();
		    
     p++;
    }
}
