/*Assignment-1 Implementation of Bisection and False position method
Author : Sadnan Kibria Kawshik
Roll : AE-15
Date : January 1,2021*/
#include<bits/stdc++.h>
using namespace std;

/*equation f(x)=3x+sin(x)-e^x*/
double equation(double x)
{
    return 3*x+sin(x)-exp(x);
}
int main()
{
    double a,b,c1,c2,fa,fb,fc1,fc2,e,ans1,ans2,z=0.0,x,error_in_bisection,guess_step,error_in_false_position;
    cout << setprecision(5) << fixed; /*5 numbers after decimal point*/
repeat:
    cout<<"Enter first guess : ";
    cin>>a;
    cout << "f(" << a << ") = " << equation(a) << "\n";
    cout<<endl;
    cout<<"Enter second guess : ";
    cin>>b;
    cout << "f(" << b << ") = " << equation(b) << "\n";
    cout<<endl;
    cout<<"Enter tolerrable error rate : ";
    cin>>e;

    fa=equation(a);/*f(a)*/
    fb=equation(b);/*f(b)*/

    guess_step = (log(b-a) - log(e))/log(2);

    cout<<"Assumed step size in bisection method is : "<<guess_step<<endl;

    if(fa*fb>0.0) /*both f(a) and f(b) in same side*/
    {
        cout<<"Incorrect guess.Try again....\n";
        goto repeat;
    }

    else
    {
        int step=1;
        double temp1=a,temp2=b,temp3=a,temp4=b;

        cout <<"\n\n"<< "Iteration    "<< "c in bisec	" << setw(10) << "f(c) in bisec	" << setw(10) <<  "Error in bisec	" << setw(10) << "c in falseposi	"<<setw(10)<<"f(c) in falseposi "<<"Error in falseposi\n"<<endl;


        do
        {
            c1=(temp1+temp2)/2.0;/*calculating next point*/
            fc1=equation(c1);
            error_in_bisection=(temp2-temp1)/2.0;/*error in bisection*/

            cout <<setw(5) << step <<"	  "<<  setw(10) << c1  <<"	"<< setw(10) << fc1  <<"	"<< setw(10) << error_in_bisection<<"	";

            if(fa*fc1<0.0)/*limit from a to c*/
            {
                temp2=c1;
            }
            else
            {
                temp1=c1;/*limit from c to b*/
            }

            c2=(temp3*equation(temp4)-temp4*equation(temp3))/(equation(temp4)-equation(temp3));
            fc2=equation(c2);
            error_in_false_position=(c2-z);


             cout<< setw(10) << c2  <<"	"<< setw(10) << fc2  <<"	"<< setw(15) << error_in_false_position <<endl;



            if(fa*fc2<0.0)
            {
                temp4=c2;  /*limit from a to c*/
            }
            else
            {
                temp3=c2; /*limit from c to b*/
            }

            z=c2;


            step++;
        }
        while(fabs(fc1)>e);

    }
    return 0;
}
