struct add_in
{
	long arg1;
  long arg2;
};
struct add_out
{
	long res;
};
program ADD_PROG
{
	version ADD_VERS
	{
		add_out ADDPROC(add_in)=1;
	} =1;
}= 0x3123000;
