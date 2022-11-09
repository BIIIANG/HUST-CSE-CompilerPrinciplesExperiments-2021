int read(){
	int a=0;
	a = getchar();
	return a - 48;
}
int main(){
	int m,n;
	int i=48;
	m = read();
	n = read();
    if(m == n ){
        int i = 1;
        i = i + 48;
        putchar(i);
    }else{
        i = i + 2;
        putchar(i);
    }
    i = i + 1;
    putchar(i);
	return 0;
}
