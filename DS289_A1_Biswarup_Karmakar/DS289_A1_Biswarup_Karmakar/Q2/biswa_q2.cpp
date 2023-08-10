// including header files
#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<fstream>
#include<math.h>
#include<stdlib.h>

using namespace std;

typedef double real;

//dynamic memory allocation
void allocate1D(real *&x, int n)
{
    x=new real[n];
    //vector<real>x(n);
}
//reading file 
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

// taking intilising inputs
 
void input(int* iMethod, vector<real>&step_array){
    //double *inputs = new real[100];
    real *inputs;
	allocate1D(inputs, 100);
    readfile(inputs);
    *iMethod = inputs[0];
    //*dt = inputs[1];
    for(int i=1;i<=5;i++)
    {
 		step_array[i-1]=inputs[i];
 		}
}

 // explicit euler method
vector<real>  expliciteuler(vector<real> y, real &dt,real &t, int &nsteps)
{
	for(int i=0; i<nsteps; i++)
		{
        	y[i+1]=y[i] + dt*(y[i]*t*t -1.1*y[i]);
        	cout<<y[i+1]<<endl;
        	t=t+dt;
    	}
    return y;
  
}

// adam bash method 
vector<real> adam_bash(vector<real> y, real &dt,real &t, int &nsteps, vector<real> t1)
{
	y[1]=y[0] + dt*(y[0]*t1[0]*t1[0] -1.1*y[0]);
	t1[1]=t1[0]+dt;
    for(int i=1; i<nsteps; i++)
    {   
		y[i+1] = y[i] + dt*(3*y[i]*(t1[i]*t1[i]-1.1) -y[i-1]*(t1[i-1]*t1[i-1]-1.1))/2;
    	cout<<y[i+1]<<endl;
    	t1[i+1]=t1[i]+dt; 
	}
	return y;
}

// rk method
vector<real> rk(vector<real> y, real &dt,real &t, int &nsteps)
{
	real k1, k2, k3, k4;
    for(int i=0; i<nsteps; i++)
    {  
        k1 = dt*y[i]*(t*t - 1.1);
        k2 = dt*(y[i]+k1/2)*((t+dt/2)*(t+dt/2) - 1.1);
        k3 = dt*(y[i]+k2/2)*((t+dt/2)*(t+dt/2) - 1.1);
        k4 = dt*(y[i]+k3)*((t+dt)*(t+dt) - 1.1);
        y[i+1]=y[i] +(k1+2*k2+2*k3+k4)/6;
        cout<<y[i+1]<<endl;
        t=t+dt;
    }
	return y;
}

// main 

int main()
{
	int imethod, nsteps;    // imethod 1 for euler, 2 for adam bash , 3 for rk
	real tend =2.0,dt;
	
	// creating array for step size
	vector<real>step_array(5);
	input(&imethod,step_array);
	cout<<imethod<<endl;
	
	string name;
	
	//loop for step sizes 
	for(int k=0;k<5;k++)
	{
	
		dt=step_array[k];
		cout<<endl<<dt<<endl;
		nsteps = (int)(tend/dt);
		//vector<real> t(nsteps+1);
		vector<real> y(nsteps+1);
	    vector<real> y_ana(nsteps+1);
	    vector<real> T(nsteps+1);
		vector<real> t1(nsteps+1);
		y[0]=y_ana[0]=1.0;
		real t=0.0;
		t1[0]=0;
		
		if(imethod==1)
		{
			y = expliciteuler(y,dt,t,nsteps);     // calling function and returning y
			name="euler_";
		}
	   
		if(imethod==2)
		{
			y= adam_bash(y,dt,t,nsteps,t1);   // calling function for adam bash
			name="adam_bash_";
		}

		if(imethod==3)
		{
			y= rk(y,dt,t,nsteps);
			name="rk_";
		}
	
     
	y_ana[0]=1;
	T[0]=0;
	real t2=0.0;   //intial time
		for(int i=1;i<=nsteps;i++)
		{
		t2=t2+dt;
		y_ana[i]=exp( pow(t2,3)/3 - (1.1*t2));
		T[i]=T[i-1]+dt;
		}
		
		
		
// writing in file 
		
		string name2 = name + to_string(dt);

		ofstream f1;
		ofstream f2;
		
		f2.open(name2+"_error"+".txt");
		f1.open(name2+".txt");
		f1 << "t" << '\t' << "y" << endl;
		f2 << "t" << '\t' << "error" << endl;
		for (int i=0;i<=nsteps;i++)
		{
		    f1 << T[i] <<'\t' << y[i] << "\n";
		    f2 << T[i] <<'\t' << fabs(y_ana[i]-y[i]) << "\n";
		    
			
		}
		f1.close();
		f2.close();
		
	}
		
		
	return 0;
}





