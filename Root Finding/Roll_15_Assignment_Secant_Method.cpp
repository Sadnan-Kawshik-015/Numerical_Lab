/*Assignment-1 Implementation of  Secant Method
Author : Sadnan Kibria Kawshik
Roll : AE-15
Date : January 9,2021*/
#include<bits/stdc++.h>
using namespace std;

/*equation f(x)=(e^-x)-x*/
double equation(double x)
{
    return exp(-x)-x;
}
int main()
{
    double a,b,c,fa,fb,fc,e;
    cout << setprecision(6) << fixed; /*6 numbers after decimal point*/

    cout<<"Enter first guess : ";/*xn-1*/
    cin>>a;
    cout << "f(" << a << ") = " << equation(a) << "\n";/*f(xn-1)*/
    cout<<endl;
    cout<<"Enter second guess : ";/*xn*/
    cin>>b;
    cout << "f(" << b << ") = " << equation(b) << "\n";/*f(xn)*/
    cout<<endl;
    cout<<"Enter tolerrable error rate : ";/*epsilon*/
    cin>>e;

    int step=1;/*number of iterations*/

    fa=equation(a);/*f(xn-1)*/
    fb=equation(b);/*f(xn)*/


    cout<<"Iteration table for secant method is given below:\n\n"<<endl;

    cout <<"\n\n"<< "Iteration    "<< "xn-1	" << setw(10) << "f(xn-1)	"  << setw(10) << "xn	"<<setw(10)<<"f(xn)"<<setw(15)<<"xn+1\n"<<endl;

    do
    {
        c=(b*fa-a*fb)/(fa-fb);/*xn+1 calculation*/
        fc=equation(c);/*f(xn+1)*/


        cout <<setw(5) << step <<"	  "<<  setw(10) << a <<"	"<< setw(10) <<  fa <<"	"<< setw(10) << b<<"	";

        cout<< setw(10) << fb  <<"	"<< setw(10) << c <<endl;

        a=b;/*xn-1=xn*/
        fa=fb;/*f(xn-1)=f(xn)*/
        b=c;/*xn=xn+1*/
        fb=fc;/*f(xn)=f(xn+1)*/


        step++;
    }
    while(fabs(fc)>e);

    cout<<"\nroot is : "<<c<<endl;

    return 0;
}
