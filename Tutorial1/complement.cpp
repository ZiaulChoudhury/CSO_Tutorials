#include <iostream> 
#include <bitset>        

//#define BITS 8

struct bit
{	
	int carry;
	int sum;
};

struct bit  full_adder(int A, int B, int C)
{
	struct bit s;
	s.sum = A ^ B ^ C;
	s.carry = (A&B) | (B&C) | (C&A);
	return s;
}

int get_value(std::bitset<BITS> Z)
{
	bool sign = Z[BITS-1] == 1 ? 1 : 0;
	if (sign == 1)
		return 0 - (int)(Z.flip().to_ulong() + 1);
	else
		return (int)(Z.flip().to_ulong() + 1);	
}
int ripple_adder(std::bitset<BITS> X, std::bitset<BITS> Y)
{
	std::bitset<BITS> Z;
	int C_In = 0;
	printf("\n X Y S C ");
	for(int i=0;i<BITS;i++){
		struct bit s = full_adder(X[i], Y[i], C_In);
		printf(" \n %d %d %d %d ", X[i]==1, Y[i]==1, s.sum, s.carry);
		C_In = s.carry;
		Z[i] = s.sum;
	}
	std::cout << " \n result " << Z.to_string()<<"\n ";
	if(Z[BITS-1] == 1)
		return get_value(Z);
	else
		return (int)Z.to_ulong();
}

bool detect_error(std::bitset<BITS> X, std::bitset<BITS> Y)
{
	bool flag = false;
        std::bitset<BITS> Z;
        int C_In = 0;
        for(int i=0;i<BITS;i++){
                struct bit s = full_adder(X[i], Y[i], C_In);
		if(i == BITS - 1)
			flag = C_In ^ s.carry;
                C_In = s.carry;
                Z[i] = s.sum;
        }
	return flag;
}


int main (int argc, char *argv[])
{
  int x = atoi(argv[1]);
  int y = atoi(argv[2]);
  std::bitset<BITS> X(x);
  std::bitset<BITS> Y(y);
  std::cout << X.to_string() <<"\n";
  printf("\nX = %d Y = %d bits = %d ", x,y, BITS);
  int z = ripple_adder(X,Y);
  std::cout << " \n " << z << "\n";
  if(detect_error(X,Y))
	  printf(" \n Error - Oveflow Detected \n ");
  return 0;
}
