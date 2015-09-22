// Edit by XieTao,2015-06-14
//命令格式：txt2bf -f </path/to/file>
//或者 txt2bf -s <“String”>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min_to[128][3]={
0 ,0 ,0 ,
0 ,0 ,1 ,
0 ,0 ,2 ,
0 ,0 ,3 ,
2 ,2 ,0 ,
2 ,2 ,1 ,
3 ,2 ,0 ,
3 ,2 ,1 ,
4 ,2 ,0 ,
3 ,3 ,0 ,
5 ,2 ,0 ,
5 ,2 ,1 ,
4 ,3 ,0 ,
4 ,3 ,1 ,
7 ,2 ,0 ,
5 ,3 ,0 ,
4 ,4 ,0 ,
4 ,4 ,1 ,
6 ,3 ,0 ,
6 ,3 ,1 ,
5 ,4 ,0 ,
7 ,3 ,0 ,
7 ,3 ,1 ,
7 ,3 ,2 ,
6 ,4 ,0 ,
5 ,5 ,0 ,
5 ,5 ,1 ,
9 ,3 ,0 ,
7 ,4 ,0 ,
7 ,4 ,1 ,
6 ,5 ,0 ,
6 ,5 ,1 ,
8 ,4 ,0 ,
8 ,4 ,1 ,
8 ,4 ,2 ,
7 ,5 ,0 ,
6 ,6 ,0 ,
6 ,6 ,1 ,
6 ,6 ,2 ,
6 ,6 ,3 ,
8 ,5 ,0 ,
8 ,5 ,1 ,
7 ,6 ,0 ,
7 ,6 ,1 ,
11 ,4 ,0 ,
9 ,5 ,0 ,
9 ,5 ,1 ,
9 ,5 ,2 ,
8 ,6 ,0 ,
7 ,7 ,0 ,
10 ,5 ,0 ,
10 ,5 ,1 ,
13 ,4 ,0 ,
13 ,4 ,1 ,
9 ,6 ,0 ,
11 ,5 ,0 ,
8 ,7 ,0 ,
8 ,7 ,1 ,
8 ,7 ,2 ,
8 ,7 ,3 ,
10 ,6 ,0 ,
10 ,6 ,1 ,
10 ,6 ,2 ,
9 ,7 ,0 ,
8 ,8 ,0 ,
8 ,8 ,1 ,
11 ,6 ,0 ,
11 ,6 ,1 ,
11 ,6 ,2 ,
11 ,6 ,3 ,
10 ,7 ,0 ,
10 ,7 ,1 ,
9 ,8 ,0 ,
9 ,8 ,1 ,
9 ,8 ,2 ,
15 ,5 ,0 ,
15 ,5 ,1 ,
11 ,7 ,0 ,
13 ,6 ,0 ,
13 ,6 ,1 ,
10 ,8 ,0 ,
9 ,9 ,0 ,
9 ,9 ,1 ,
9 ,9 ,2 ,
12 ,7 ,0 ,
12 ,7 ,1 ,
12 ,7 ,2 ,
12 ,7 ,3 ,
11 ,8 ,0 ,
11 ,8 ,1 ,
10 ,9 ,0 ,
13 ,7 ,0 ,
13 ,7 ,1 ,
13 ,7 ,2 ,
13 ,7 ,3 ,
19 ,5 ,0 ,
12 ,8 ,0 ,
12 ,8 ,1 ,
14 ,7 ,0 ,
11 ,9 ,0 ,
10 ,10 ,0 ,
10 ,10 ,1 ,
10 ,10 ,2 ,
10 ,10 ,3 ,
13 ,8 ,0 ,
15 ,7 ,0 ,
15 ,7 ,1 ,
15 ,7 ,2 ,
12 ,9 ,0 ,
12 ,9 ,1 ,
11 ,10 ,0 ,
11 ,10 ,1 ,
14 ,8 ,0 ,
14 ,8 ,1 ,
14 ,8 ,2 ,
14 ,8 ,3 ,
14 ,8 ,4 ,
13 ,9 ,0 ,
13 ,9 ,1 ,
17 ,7 ,0 ,
12 ,10 ,0 ,
11 ,11 ,0 ,
11 ,11 ,1 ,
11 ,11 ,2 ,
11 ,11 ,3 ,
11 ,11 ,4 ,
14 ,9 ,0 ,
14 ,9 ,1 ,
};

/************
把一个字符串转换为brainfuck源码，
比较和上一个字符的差值，来决定增或减一定数值，产生这个字符的ascii码。
小于十的数直接+/- n次即可，大于十的数，个位部分直接+/- n次，高位部分采用循环来加减，
比如120可以用如下方法到达：（12*10）,上面数组保存了a*b+c=x时，使a+b+c最小取值，为了代码更短
>++++++++++++[<++++++++++>-]
自行分析。
************/

void print_to(int zi,char ch)
{
    if(zi==0)
    {
        printf(".");
    }
    else
        {
            int gewei=min_to[zi][2];
            int shiwei_2=min_to[zi][1];
            int shiwei_1=min_to[zi][0];

            if(shiwei_2==0)
            {
            gewei=gewei+shiwei_2;
            for(int j=0; j<shiwei_1; ++j)
            {
                putchar('+');//循环次数
            }
        goto gew;
            }
            putchar('>');//右移一位,循环次数空间
            for(int j=0; j<shiwei_1; ++j)
            {
                putchar('+');//循环次数
            }
            printf("[<");
            for(int j=0; j<shiwei_2; ++j)
            {
                printf("%c",ch);
            }
            printf(">-]");

            printf("<");//左移一位，字符空间
        gew:
            for(int j=0; j<gewei; ++j)putchar(ch);
            printf(".");
        }

}

void tobf_f(char *s)
{
    FILE *p=fopen(s,"rb");
    if(p==NULL)printf("can not open file : %s",s);
    else
    {
        int count=0;
        char toc='A';
        for(;;count++)
        {
            toc=fgetc(p);
            if(toc==EOF)break;
            char ch='+';
            int cha=toc;
            if(count>0)
            {
                fseek(p,-2L,SEEK_CUR);
                char toc_p=fgetc(p);
                fseek(p,1L,SEEK_CUR);

                cha=toc-toc_p;//比较和上个字符的差值
                if(cha>0)ch='+';//决定递减还是递增
                else if(cha<0)ch='-';
            }
            int zi=abs(cha);
            print_to(zi,ch);
        }
    }
    fclose(p);
}
void tobf_s(const char *S)
{
    int len=strlen(S);
    //使用长度读取每个字符
    for(int i=0; i<len; ++i)
    {
        char ch='+';
        int cha=S[i];
        if(i>0)
        {
            cha=S[i]-S[i-1];//比较和上个字符的差值
            if(cha>0)ch='+';//决定递减还是递增
            else if(cha<0)ch='-';
            else printf(".");
        }
        int zi=abs(cha);
        print_to(zi,ch);
    }
}
void warning(void)
{
        puts("you can use by :");
        puts("txt2bf -f </path/to/file>");
        puts("txt2bf -s <string>");
}
int main(int argc, char* argv[])
{
    if(argc<3)
    {
        warning();
    }
    if(argc==3)
    {
        if(strcmp(argv[1],"-s")==0)
        {
            tobf_s(argv[2]);
        }
        else if(strcmp(argv[1],"-f")==0)
        {
            tobf_f(argv[2]);
        }
        else
        {
            warning();
        }
    }
    printf("\n");
    return 0;
}
