#include <stdio.h>
#include <stdlib.h>
int getPrice()
{
    int n;
    scanf("%d",&n);
    if(n<=0)
    {
        printf("Invalid price. Enter again: ");
        getPrice();
    }
    return n;
}
int main(int argc, char const *argv[]) {
    printf("Enter the no. of Items: ");
    int n,i,total=0;;
    scanf("%d",&n);
    int* prices=(int*)malloc(n*sizeof(int));
    if(n<=0)
    {    printf("Invalid input."); return 0;    }
    printf("Enter the price for the items: \n");
    for(i=0;i<n;i++)
    {
        prices[i]=getPrice();
        total=total+prices[i];
    }
    double vat=total*5/100,dis=0;
    if(total>=2000&&total<5000)
        dis=total*5/100;
    else if(total>=2000&&total<5000)
        dis=total*10/100;
    printf("Please Pay Rs %.2f\n",(total-dis+vat));
    return 0;
}
