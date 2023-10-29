#include <iostream>
#include <algorithm>
using namespace std;

int get_digit(char c){
	if (c=='\0'){
		return 0;
	}
	else {
		return c-'0';
	}
}

void add_float(char* a, char* b, char* res) {
	int pa=-1,pb=-1,lena=0,lenb=0;
	char x[512]={0},y[512]={0},z[512]={0};
    	for(int i=0;a[i]!='\0';i++){
		lena++;
    		if(a[i]=='.'){
			pa=i;
		}

   	}
    	for(int i=0;b[i]!='\0';i++){
		lenb++;
    		if(b[i]=='.'){
			pb=i;
		}
   	}
	if(pa<pb){
		swap(pa,pb);
		swap(a,b);
		swap(lena,lenb);
	}
	int lenx=lena+1,leny=pa-pb+1;
	x[0]='0';//x[0:lenx-1]
	for(int i=0;i<lena;i++){
		x[i+1]=a[i];
	}
	for(int i=0;i<leny;i++){
		y[i]='0';//y[0:leny-1]
	}
	for(int cnt=0;cnt<lenb;cnt++,leny++){
		y[leny]=b[cnt];
	}
	cout<<x<<endl<<y<<endl;;
	int ed = lenx-1;
	int carry=0;
	for(int ed = lenx - 1;ed>=0;ed--){
		if(x[ed]=='.'){
			z[ed] ='.';
			continue;
		}
		z[ed] = (get_digit(x[ed])+get_digit(y[ed])+carry)%10 + '0';
		carry = (get_digit(x[ed])+get_digit(y[ed])+carry)/10;
	}
	cout<<z<<endl;
	int l = 0;
	if(z[0]=='0')l=1;
	int r = lenx-1;
	while(z[r] == '0'){
		r--;
	}
	for(int i=l;i<=r;i++){
		res[i-l]=z[i];
	}
	res[r-l+1]='\0';
}


int main()
{
    char num1[128], num2[128], res[128];
    cin >> num1;
    cin >> num2;
    add_float(num1, num2, res);
    cout << res << endl;
    return 0;
}
