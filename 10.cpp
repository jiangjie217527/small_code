#include <iostream>
using namespace std;

int main()
{    
    char str1[20],str2[20];
    cin>>str1>>str2;
    char c,*cp; 
    for (cp = str1;*cp!='\0'&&*(cp+(str2-str1));cp++){
    	c = *cp;
	*cp = *(cp+(str2-str1));
	*(cp+(str2-str1)) = c;
    }
    cout<<str1<<endl<<str2<<endl;
    //不得再增加其它任何变量
    return 0;
}
