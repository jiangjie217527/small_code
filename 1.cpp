#include <iostream>
using namespace std;

int main()
{    
	char *s=new char[105];
	cin.getline(s,105);
	char *sq=new char[20];
	cin>>sq;
	char **token = new char*[20];//token[20] token[0] = char *
	for(int i=0;i<20;i++)token[i]=NULL;
	token[0] = new char[20];
	int token_num=0,token_len=0;
	for(int i=0;s[i]!='\0';i++){
		if(s[i]==' '){
			token[token_num][token_len]='\0';
			token_num++;
			token_len=0;
			token[token_num] = new char[20];
			continue;
		}
		token[token_num][token_len]=s[i];
		token_len++;
	}
	token[token_num][token_len]='\0';
	cout<<token_num+1<<endl;
	for(int i=0;sq[i]!='\0';i++){
		cout<<token[sq[i]-'0']<<" ";
	}
    return 0;
}
