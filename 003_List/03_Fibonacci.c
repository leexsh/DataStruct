#include<stdio.h>
// 递归的方式求斐波那契数列
int f(int n){
	if(n == 1 || n == 2)
		return 1;
	else
		return f(n-1) + f(n-2);
}
// 非递归的方式求斐波那契数列
int f1(int n){
	int a = 1;
	int b = 1;
	int c, i;
	for(i = 3; i <= n; i++){
		c = a + b;
		a = b;
		b = c;
	}
	return c;
}
int main(){
	printf("%d\n", f(6));
	printf("%d\n", f(6));
	return 0;	
}
