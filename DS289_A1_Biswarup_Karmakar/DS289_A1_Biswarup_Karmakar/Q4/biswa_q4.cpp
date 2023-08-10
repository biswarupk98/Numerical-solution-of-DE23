#include<iostream>
#include<vector>
#include<string.h>

#include<sstream>
#include<fstream>
#include<math.h>
#include<stdlib.h>
using namespace std;

typedef double real;


int main()
{
    real dx = 0.1,x=0; 
    double arr =0;
    int nsteps = 2.0/0.1;

    vector<real> y(nsteps+1);
    vector<real> X(nsteps+1);
    y[0] = 0;
    X[0]=0;
    int i=1;
    while(i<=nsteps)    
    {
        x = x+dx;
        X[i]=x;
        y[i] = (y[i-1] + dx * (200000 * exp(-x) - exp(-x)))/(1+200000*dx);
        i++;
    }

    for(int i=0; i<nsteps; i++)
    {
        cout << y[i] << endl;
    }
    ofstream f1;
    f1.open("implicit_euler_x_y.txt");
    f1 << "x" << '\t' << "y" << endl;
    for(int i=0; i<=nsteps; i++){
        f1 << X[i] << '\t' << y[i] << "\n";
    }
    f1.close();
    return 0;
}