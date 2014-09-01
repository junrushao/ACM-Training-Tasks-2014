#include<iostream>
#include<cstdio>
using namespace std;
int n,b;
unsigned long long p, q, r;

unsigned long long multiply_mod (unsigned long long x, unsigned long long y, unsigned long long mod){
	unsigned long long ret = 0, val = x % mod;
	for (; y > 0; y >>= 1){
		if ((y & 1) == 1){
			if (( ret += val) >= mod)
				ret -= mod;
		}
		if (( val += val) >= mod)
			val -= mod;
	}
	return ret;
}

unsigned long long pow_mod(unsigned long long x, unsigned long long y, unsigned long long mod){
 unsigned long long ret = 1, val = x;
 for (; y > 0 ; y >>= 1){
 	if ((y & 1) == 1)
 		ret = multiply_mod(ret, val , mod);
 	val = multiply_mod(val, val, mod);
 }
 return ret;
}
bool test(unsigned long long  n, int base){
	unsigned long long  m = n - 1, ret = 0;
	int s = 0;
	for (; m % 2 == 0; ++s)
		m >>= 1;
	ret = pow_mod(base, m, n);
	if (ret == 1 || ret == n - 1)
		return true;
		for (-- s; s >= 0; --s){
			ret = multiply_mod(ret, ret, n);
			if (ret == n-1)
				return true;
		}
		return false;
}
	
unsigned long long special[7] = {
	1373653LL,
	25326001LL,
	3215031751LL,
	25000000000LL,
	2152302898747LL,
	3474749660383LL,
	341550071728321LL
}; 

bool is_prime(unsigned long long n){
	if (n < 2)
		return false;
	if (n < 4)
		return true;
	
	if (!test(n,2) || !test(n,3))
		return false;
	if (n < special[0])
		return true;
		
	if (!test(n,5))
		return false;
	if (n < special[1])
		return true;
	
	if (!test(n,7))
		return false;
	if (n == special[2])
		return false;
	if (n < special[3])
		return true;
		
	if (!test(n,11))
		return false;
	if (n < special[4])
		return true;
	
	if (!test(n,13))
		return false;
	if (n < special[5])
		return true;
	
	if (!test(n, 17))
		return false;
	if (n < special[6])
		return true;
	
	return test(n,19) && test(n,23) && test(n,29) && test(n,31) && test(n,37);
}
int main(){
  while (scanf("%d%d", &b, &n) == 2)
  {
  	p = 1;
  	q = 0;
  	for (int i = 1;i < n;i++)
  	{
  		q += p;
  		p *= b;
  	//	cout << p << endl;
  	}
  	q += p;
  //	cout << q << endl; 
  	if (is_prime(q)) printf("YES\n"); else printf("NO\n");
  }
}
