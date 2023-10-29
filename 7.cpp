char * oddstr(char * s){
    char * ans = new char[200];
    int k=0;
    for (int i =0 ;s[i]!='\0';i++){
        if (i%2==1){
            ans[k]=s[i];
            k++;
        }
    }
    ans[k]='\0';
    return ans;
}
