#include <stdio.h>
#include <stdbool.h>

void assignString(){
	const char *bla="hoikoiakalassssssssssssssssssssssssss";
}

const char* return_string(){
	return "hoikalaalalla";
}

void assignCompare(int a){
	long ab=(1!=4 && a>3);
}

long add(long a, long b)
{
	int c=a+b;
	return c;
}

long div(long a, long b)
{
	int c=a/b;
	return c;
}

long unary_minus(){
	int a=12;
	int b=-a;
}

long unary_minus_float(){
	float a=12.23;
	float b=-a;
}

long unary_negation(){
	bool a=false;
	bool b=!a;
}

void float_compare(){
	float a=21231.12;
	float b=323.122;
	float c=0.0;
	bool d;

	d=a>b;

//	if(a>b){
//		c=232.323;
//	}
}

void compare_bools(){
	bool a=true;
	bool b=false;

	if(a&&b){
		bool c=true;
	}
	if(a||b){
		bool c=true;
	}
}

int addthree( int a, int b, int c )
{
//	printf("hoiladriaho");
        int x;
        int x1=2;
        int x2=3;
        int x3=4;
        int x4=5;
        int x5=6;
        x3=add(x1,x2);
        int x6=7;
        int x7=8;

        x = a+b+c;
        return x+x1+x2+x3+x4+x5+x6+x7;
}

long test(int a, int b){

	int c=0;
	int e=4;
	int f=3;
	int g=2;

	int h=g*f;
	h=e-c;

	return f+e+c+g;
}

float test_float_add(float a, float b){
	float c=a+b;
	int d=3;
	return c;
}

float test_float_sub(float a, float b){
	float c=a-b;
	return c;
}

float test_float_mul(float a, float b){
	float c=a*b;
	return c;
}

float test_float_div(float a, float b){
	float c=a/b;
	return c;
}

void test_if(){
	int a=0;
	int b=32;

	if(a>4 && b==3){
		b=12;
	}else{
		b=3;
	}
	a=10;
}

void test_if_without_else(){
	int a=0;

	if(a==0){
		int b;
		b=3;
	}
}

void test_array(int arr[10], int arr3[10]){
	int arr2[100];
	int b=2;
	int c=b*3;
	arr[b+c+12]=4;
	arr3[b-c+12]=4;
}

void test_arr_simple(){
	int arr[17];
	arr[0]=0;
	arr[1]=0;
	arr[2]=0;
}

int main( int argc, char *argv[] )
{
		int arr[10];
		int arr2[10];

		test_array(arr,arr2);

        return 0;
}
