/*Assignment-1 Implementation of Bisection and False position method
Author : Sadnan Kibria Kawshik
Roll : AE-15
Date : January 1,2021*/
#include<bits/stdc++.h>
using namespace std;

/*equation f(x)=x^3-2x^2+x-3*/
double equation(double x)
{
    return x*x*x-2*x*x+x-3;
}

double derivative(double x)
{
    return 3*x*x-4*x+1;
}
int main()
{
    int n = 20,flag = 1,i=0;
    double epsilon,x0,xn,err = 0,root;
    cout<<"Enter initial guess : ";
    cin>>x0;
    cout<<"Enter error tolerance : ";
    cin>>epsilon;
     cout <<"\n\n"<< "Iteration    "<< "x0	in newton" << setw(10) << "      f(x0) in newton	" << setw(10) <<  "     xn	in newton" << setw(10) << "      f(xn) in newton	"<<setw(10)<<"      Relative Error\n"<<endl;

    while(i<20)
    {
        xn = x0 - ((equation(x0))/derivative(x0));
        cout <<setw(5) << i <<"	  "<<  setw(10) << x0  <<"	 "<< setw(10) << equation(x0)  <<"	"<< setw(10) << "	";
         cout<< setw(10) << xn  <<"	"<< setw(10) << equation(xn)  <<"	"<< setw(15) << err <<endl;

        err = (xn-x0)/xn;
        if(fabs(err)<=epsilon)
        {
            root = xn;
            flag = 0;
            break;
        }
        x0 = xn;
        i++;
    }
    if(flag)
    {
        cout<<"\n\n\n\n\n\No root found"<<endl;
    }
    else
    {
        cout<<"\n\n\n\n\n\n\nRoot is : "<<root<<endl;
        cout<<"f(root) = "<<equation(root)<<endl;

    }

    return 0;
}

