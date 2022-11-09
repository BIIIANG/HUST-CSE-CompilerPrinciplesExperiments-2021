int read(){
	int a=0;
	int b;
    b=getchar();
	while(b!=10)
	{
		a=a*10+b-48;
		b=getchar();
	}
	return a;
}
int write(int a){
	int b=1;
	int c;
	while(b<=a){
		b=b*10;
	}
	b=b/10;
	while(a>=10){
		c=a/b;
		a=a-c*b;
		b=b/10;
		c=c+48;
		putchar(c);
	}
	putchar(a+48);
	putchar(10);
	return a;
}
int fibo(int a){
	if(a==1||a==2){
		return 1;
	}
	return fibo(a-1)+fibo(a-2);
}
int main(){
	int m,n;
	int i=1;
	m=read();
	while(i<=m){
		n=fibo(i);
		write(n);
		i=i+1;
	}
	return 0;
}
