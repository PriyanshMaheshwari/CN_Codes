#include<stdio.h>
#include<rpc/rpc.h>
#include "add.h"
int main()
{
	CLIENT *c1;
	add_in in;
	add_out *outp;
	c1=clnt_create("127.0.0.1",ADD_PROG,ADD_VERS,"tcp");
	printf("Enter the first number\n");
	scanf("%ld",&in.arg1);
  printf("Enter the second number\n");
  scanf("%ld",&in.arg2);
	outp=addproc_1(&in,c1);
	if(outp!=NULL)
		printf("The sum of two numbers is %d\n",outp->res);
	exit(0);
	return 0;
}
