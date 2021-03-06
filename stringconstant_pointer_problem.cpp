// endl.cpp: 定义控制台应用程序的入口点。
//C++ Primer Plus 编程练习8.6

#include "stdafx.h"
#include "iostream"
#include "cstring"
template <typename T>
T maxn(T arr[],int n);
template <>char * maxn(char * arr[], int n);

int main()
{
	using namespace std;
	int a[6] = { 356,6,3,6,55,223};
	double b[4] = { 9.4,4,-9,44};
	char s1[] = "Hello6";
	char s2[] = "12345";
	char s3[] = "1234x6";
	char s4[] = "idon";
	char s5[] = "wtf";
	//此句在vs2017中报错
	//E0144	"const char *" 类型的值不能用于初始化 "char *" 类型的实体	endl
	//char * st[5] = { "Hello6", "12345", "1234x6", "idon", "wtf" };
	char * st[5] = {s1,s2,s3,s4,s5};
	cout << "Max int = " << maxn(a,6)<<endl;
	cout << "Max double = " << maxn(b,4)<<endl;
	cout << "Max string =" << maxn(st, 5)<<endl;
	return 0;
}

template <typename T>
T maxn(T arr[], int n)
{
	T max=arr[0];
	for (int i = 1; i < n; i++)
	{
		max = arr[i] > max ? arr[i] : max;
	}
	return max;
}

template <>char * maxn(char * arr[], int n)
{
	long long len = strlen(arr[0]);
	char* max = arr[0];
	for (int i = 1; i < n; i++)
	{
		long long temp = strlen(arr[i]);
		if (temp > len)
		{
			len = temp;
			max = arr[i];
		}
	}
	return max;
}