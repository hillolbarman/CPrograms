#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void strev(char *str1, char *str2)
{
        int i = 0, len = 0, r = 0;
        while(*(str1+len)!='\0')
                len++;
        for(i=len-1; i>=0; i--)
        {
                *(str2+r) = *(str1+i);
                r++;
        }
        *(str2+r) = '\0';
}

char* funnyString(char* s)
{
   int i=0,len=strlen(s);
    char *s2;
    strev(s,s2);
	for(i=1;i<len;i++)
		if((int)*(s+i)-(int)*(s+i-1)!=(int)*(s2+i)-(int)*(s2+i-1))
        	    return "Not Funny";
    return "Funny";
}
int main(int argc, char const *argv[]) {
    char* str;
    str=strdup((char*)malloc(50*sizeof(char)));
    scanf("%s",str);
    puts(funnyString(str));
    return 0;
}
