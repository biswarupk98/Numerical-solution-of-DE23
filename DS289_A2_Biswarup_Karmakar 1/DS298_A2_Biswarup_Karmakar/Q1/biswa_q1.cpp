#include <iostream>
#include <fstream>

using namespace std;

typedef double real;

extern "C" void dgesv_(int* n, int* nrhs, double* a, int* lda, int* ipiv, double* b, int* ldb, int* info);

int main()
{
    int NX=64, NY=128;
    int TNX, TNY, PNX1, PNX2, PNY1, PNY2;
    int NST = 1;// Stride for ghost points
    int NGPX = 0, NGPY = 2; //Number of ghost points
    int i,j; //Loop variables
    int temp; //Temporary variable

    real lx=2.0, ux=3.0, ly=4.0, uy=6.0, dx, dy; // Domain limit and spacing
// calculating spacing along x,y direction respectively
    dx = (ux-lx) / (NX-1);
    dy = (uy-ly) / (NY-1);
//Calculate total points along x,y direction respectively
    TNX = NX + NGPX * NST;
    TNY = NY + NGPY * NST;
// Index of first,last interior point along x ,y direction respectively
    PNX1 = NGPX * NST;      
    PNX2 = TNX - NGPX * NST - 1;
    PNY1 = NST*NGPY-1;
    PNY2 = TNY - NST*NGPY;

    cout<<"dx="<<dx<<" dy="<<dy<<"\n";
    cout<<"TNX: "<<TNX<<" TNY: "<<TNY<<" PNX1: "<<PNX1<<" PNX2: "<<PNX2<<" PNY1: "<<PNY1<<" PNY2 "<<PNY2 << " NST: "<<NST<<endl;
    int A_dim = TNX*TNY;

    real* A = new real[A_dim*A_dim];       //1-D array so that it can also be used for LAPACK and save memory.
    real *b = new real[A_dim];

    if (b && A) {
        cout << "Memory is allocated Successfully";
    }
    else {
        cout << "Memory  allocation fails";
    }

    //Initialize A with zero
    for(i=0 ; i<A_dim*A_dim; i++)
        A[i] = 0;

    //                                      Boundary Conditions
    //Left Boundary
    for(i = 0; i<TNY; i++)
    {
        A[TNX*i + TNX*i*A_dim] = 1.0;
        b[TNX*i]=30.0;
    }

    //Right Boundary
    for(i = 0; i<TNY; i++)
    {    
        temp = TNX*(i+1)-1;
        A[temp + temp*A_dim] = 1.0;
        b[temp] = 60.0;
    }

    // Bottom boundary
    for(i=0;i<TNX;i++)
    {
        A[i + i*A_dim]=1;
        A[i + (i+2*TNX)*A_dim]=-1;
        b[i]=0;
    }
    
    // Top Boundary 
    for(i=0;i<TNX;i++)
    {
        temp = (TNY-1)*TNX+i;
        A[temp + (temp-TNX)*A_dim]=2*dy;
        A[temp + (temp-2*TNX)*A_dim]=1;
        A[temp + temp*A_dim]=-1;

        b[temp] = 120*dy;
    }

    //Interior points
    real r = (dx*dx) / (dy*dy);
    for(i=PNY1;i<=PNY2;i++)
    {
        for(int k=PNX1 + 1; k<PNX2; k++)
        {   
            temp = i*TNX+k;
            A[temp + temp*A_dim] = (-2*r-2);
            A[temp + (temp+1)*A_dim] = 1;
            A[temp + (temp-1)*A_dim] = 1;
            A[temp + (temp+TNX)*A_dim] = r;
            A[temp + (temp-TNX)*A_dim] = r;
    
            b[temp] = 0;
        }
    }


    cout<<"Boundary conditions applied\n";
    
    //LAPACK
    int *ipiv = new int[A_dim];

    int x = A_dim;

    
    int nrhs = 1;
    int info;
    int LDA = A_dim;
	int LDB = A_dim;
    cout<<"Calling LAPACK\n";

    dgesv_(&x, &nrhs, A, &LDA, ipiv, b, &LDB, &info);

    for(i=0; i<A_dim;i++)
        cout<<b[i]<<" ";

    cout<<"Solution done";

    ofstream file ("temperature_values.txt");
    if (file.is_open())
    {   file<<dx<<" "<<lx<<" "<<ux<<endl;
        file<<dy<<" "<<ly<<" "<<uy<<endl;
        for(i =PNY2;i>=PNY1;i--)
        {
            for(j=PNX1; j<=PNX2 ; j++)
                file<<b[j + i*TNX]<<" ";
            file<<endl;
        }
        file.close();
    }
}