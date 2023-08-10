// include header files

#include<iostream>
#include<fstream>
#include<vector>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include<sstream>


using namespace std ;
// typedef double to real

typedef double real;

// allocating input dynamically

void allocate1D(real *&x, int n)
{
    x=new real[n];
    //vector<real>x(n);
}

// reading file 

void readfile(real *inputs)
{
	ifstream fin;
	fin.open("input");
	string str;
	real temp;
	int count =0;

	for(int i=0;i<50; i++)
	{  
	   fin>>str;;
	       
	   if(stringstream(str)>>temp)
	   {
 	       inputs[count] = temp;
	       count++;	
	   }
	}
	fin.close();
}

//initializing inputs from file
void input(int* c, real *dt)
{
    //double *inputs = new real[100];
    real *inputs;
	allocate1D(inputs, 100);
    readfile(inputs);
    *c = inputs[0];
    *dt= inputs[1];
}

// main code
int main(int argv, char *argc[])
{
    int c , k, m, i;                          //declaration of variable
    real dv, dx,dv_dt,dx_dt,dt,v_new,x_new ;

    k = 20;                                      //spring constant in N/m 
    m = 20;    
    real tend=15.0;      
    input(&c,&dt);      
    cout<<c;
    cout<<endl<<dt;     
    int nsteps = (int)(tend/dt);                   //mass in kg 
 
    // dv_dt = (-c * v - k * x )/m;                 //detivative of w.r.t time
    // dx_dt = v ;
    real k1, k2, k3, k4;
    real l1, l2, l3, l4;
    vector<real> v(nsteps+1);
    vector<real> x(nsteps+1);
    vector<real> t(nsteps+1);
    vector<real> x_ana(nsteps+1);
    v[0]=0;
    x[0]=1;
    t[0]=0;
    for(int i=0;i<nsteps;i++)
    {
            k1 = dt * v[i] ;
            l1 = dt * (-c * v[i] - k * x[i] )/m;

            k2 = dt * (v[i]+ l1/2);
            l2 = dt * (-c * (v[i]+(l1/2)) - k * (x[i]+k1/2) )/m;

            k3 = dt * (v[i]+ l2/2);
            l3 = dt * (-c * (v[i]+(l2/2)) - k * (x[i]+k2/2) )/m;

            k4 = dt * (v[i]+ l3);
            l4 = dt * (-c * (v[i]+ l3) - k * (x[i]+k3) )/m;
            
            dx = (k1 + 2*k2 + 2*k3 + k4)/6;
            x[i+1] = x[i] + dx;
           
            dv = (l1 + l2*2 + 2*l3 + l4)/6;
            v[i+1] = v[i] + dv ;
            
            t[i+1]= t[i]+ dt;
    }
    

for (int i=0;i<=nsteps;i++)
		{
		    cout<<endl<<x[i];
	
		}
// Analytical solution        
x_ana[0]=1;
real t2=0.0;   //intial time
		for(int i=1;i<=nsteps;i++)
		{
		t2=t2+dt;
		x_ana[i]=(exp(-t2/8))*(cos(3*sqrt(7)*t2/8)+(1 / (3 * sqrt(7)))*sin(3*sqrt(7)*t2/8));
		}
		       
  // writing in file
    	string name= "time_displacement_"+ to_string(c);
		ofstream f2;
		f2.open(name+"_"+ to_string(dt) +".txt");
		f2 << "t" << '\t' << "x" << '\t' <<"error" << endl;
		for (int i=0;i<=nsteps;i++)
		{
		    
		    f2 << t[i] << '\t'<< x[i] << '\t' <<fabs(x_ana[i]-x[i]) << endl;
		}
		
		f2.close();
    return 0;
}
