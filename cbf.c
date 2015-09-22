//Edit by XieTao, 2015-06-14
//命令格式：cbf </path/to/file>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 300000
typedef unsigned char Uint8;

Uint8 bf[MAXLEN];
int bf_p=0;
FILE *Fp;

char fgetc_inverce(FILE *p)//倒着读文件
{
    char ch;
    ch=fgetc(p);
    fseek(p,-2L,SEEK_CUR);
    return ch;
}

void loop_to_n(void)
{
    if(bf[bf_p]!=0)return;//不为零什么也不做
    int left=0,right=0;
    char ch;
    int flag_suc=0;
    //long start=ftell(Fp);
    //long end;

    for(;;)
    {
        ch=fgetc(Fp);
        if(ch==EOF)break;
        if(ch=='[') left++;
        if(ch==']') right++;
        if(right-left==1)
        {
            flag_suc=1;
           // end=ftell(Fp);
            break;
        }
    }
    if(flag_suc==0)printf("\nerror:can not match '[' and ']',at %ld\n",ftell(Fp));
}

void loop_to_p(void)
{
    if(bf[bf_p]==0)return;//为零什么也不做
    int left=0,right=0;
    char ch;
    int flag_suc=0;
    //long start=ftell(Fp);
    //long end;
    fseek(Fp,-1L,SEEK_CUR);
    for(;;)
    {
        ch=fgetc_inverce(Fp);
        if(ch=='[') left++;
        if(ch==']') right++;
        if(right-left==0)
        {
            flag_suc=1;
           // end=ftell(Fp);
           fseek(Fp,2L,SEEK_CUR);
            break;
        }
    }
    if(flag_suc==0)printf("\nerror:can not match '[' and ']',at %ld\n",ftell(Fp));
}

void todo(Uint8 ch)
{
    char tmp;
    //printf("\n do : %c\n",ch);
    switch(ch)
    {
    case '.':
        putchar(bf[bf_p]);
    break;
    case ',':
            tmp=getchar();
		    if (tmp == EOF) bf[bf_p]=0;
		    else bf[bf_p]=tmp;
        /*
        tmp=getchar();
        for(;tmp=='\r'||tmp=='\n';)
        {
            tmp=getchar();
        }
        bf[bf_p]=tmp;
        */
    break;
    case '>':
        bf_p++;
        if(bf_p==MAXLEN){puts("\n---error:Pointer OverFlow---");bf_p=0;}
    break;
    case '<':
        bf_p--;
        if(bf_p<0){puts("\n---error:Pointer OverFlow---");bf_p=MAXLEN-1;}
    break;
    case '[':
        loop_to_n();
    break;
    case ']':
        loop_to_p();
    break;
    case '+':
        bf[bf_p]++;
    break;
    case '-':
        bf[bf_p]--;
    break;
    }
}

void cbf(char *s)
{
    Fp=fopen(s,"rb");
    if(Fp==NULL)printf("can not open file : %s",s);
    else
    {
        char ch;
        for(;;)
        {
            ch=fgetc(Fp);
            if(ch==EOF)break;
            todo(ch);
        }
    }
    fclose(Fp);
}

void warning(void)
{
        puts("you can use by :");
        puts("cbf </path/to/file>");
}

int main(int argc, char* argv[])
{
    if(argc!=2)
    {
        warning();
    }
    else if(argc==2)
    {
        cbf(argv[1]);
    }
    return 0;
}
