
#include<stdio.h>
#include<conio.h>
int  main()
{
    float A[20][20]= {0},L[20][20]= {0}, U[20][20];
    float B[20]= {0}, X[20]= {0},Y[20]= {0};
    int i,j,k,n;
    printf("Enter the order of square matrix: ");
    scanf("%d",&n);
    printf("\nEnter matrix element:\n");
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            printf("Enter A[%d][%d] element: ", i,j);
            scanf("%f",&A[i][j]);
        }
    }
    printf("\nEnter the constant terms: \n");
    for(i=0; i<n; i++)
    {
        printf("B[%d]",i);
        scanf("%f",&B[i]);
    }
    for(j=0; j<n; j++)
    {
        for(i=0; i<n; i++)
        {
            if(i<=j)
            {
                U[i][j]=A[i][j];
                for(k=0; k<i-1; k++)
                    U[i][j]-=L[i][k]*U[k][j];
                if(i==j)
                    L[i][j]=1;
                else
                    L[i][j]=0;
            }
            else
            {
                L[i][j]=A[i][j];
                for(k=0; k<=j-1; k++)
                    L[i][j]-=L[i][k]*U[k][j];
                L[i][j]/=U[j][j];
                U[i][j]=0;
            }
        }
    }
    printf("[L]: \n");
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
            printf("%9.3f",L[i][j]);
        printf("\n");
    }
    printf("\n\n[U]: \n");
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
            printf("%9.3f",U[i][j]);
        printf("\n");
    }
    for(i=0; i<n; i++)
    {
        Y[i]=B[i];
        for(j=0; j<i; j++)
        {
            Y[i]-=L[i][j]*Y[j];
        }
    }
    printf("\n\n[Y]: \n");
    for(i=0; i<n; i++)
    {
        printf("%9.3f",Y[i]);
    }
    for(i=n-1; i>=0; i--)
    {
        X[i]= Y[i];
        for(j=i+1; j<n; j++)
        {
            X[i]-=U[i][j]*X[j];
        }
        X[i]/=U[i][i];
    }
    printf("\n\n[X]: \n");
    for(i=0; i<n; i++)
    {
        printf("%9.3f",X[i]);
    }
    getch();
}
