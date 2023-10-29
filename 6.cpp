#include<iostream>
using namespace std;

bool cmp(char * a,char * b){ // a > b -> true
	int i = 0;
	while(a[i] != '\0' && b[i] != '\0'){
		if(a[i] > b[i]){
			return true;
		}
		else if (a[i] < b[i]){
			return false;
		}
		i++;
	}
	if (a[i] =='\0'){
		return false;
	}
	if (b[i] =='\0'){
		return true;
	}
	return true;
}

int main(){
	int n;
	char *c[50];
	char ch;
	cin>>n;
	for(int i = 0;i < n ; i++){
		c[i] = new char[30];
		cin>>c[i];
	}
	cin>>ch;
//readin
	for(int i = 0;i < n;i++){
		for(int j = 0;c[i][j] != '\0'; j++){
			while (c[i][j]==ch){
				for(int k = j; c[i][k]!='\0';k++){
					c[i][k] = c[i][k+1];
				}
			}
		}
	}
//process

	int maxi;
	for(int i = 0; i < n-1 ;i++){
		maxi = i;
		for(int j = i+1 ;j < n ;j++){
			if (cmp(c[j] , c[i])){ //c[j] > c[i]
				maxi=j;
			}
		}
		char * tmp = c[maxi];
		c[maxi] = c[i];
		c[i] = tmp;
		for (int i = 0 ;i < n ; i++){
		cout<<c[i]<<endl;
	}
	
	}

//sort
	for (int i = 0 ;i < n ; i++){
		cout<<c[i]<<endl;
	}
	return 0;
}
