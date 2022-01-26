int read(){
	int b=0;
	b = getchar();
	return b - 48;
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
		n=n+48;
		putchar(n);
		i=i+1;
	}
	return 0;
}
