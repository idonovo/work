#include <stdio.h>

int Fact(int n){
	
	if(n ==0){
		return 1;
	}
	
	
	return (Fact(n-1) * n);
	
}

int Fib(int n){
	
	if(n < 3){
		return 1;
	}
	
	return Fib(n-1) + Fib(n-2); 
}

int main(){
	
	int num = 50;
		
	printf("%d\n", Fact(num));
	printf("%d\n", Fib(num));	

}
