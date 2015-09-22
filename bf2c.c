//Edit by XieTao , 2015-06-14
//bf转化为c语言，用法，bf2c </path/to/file>
//输出到stdout，自行使用重定向保存

#include <stdio.h>
#include <stdlib.h>

FILE *Fp;

void todo(char ch)
{
    char tmp;
    int count;
    switch(ch)
    {
    case '.':
        puts("putchar(bf[bf_p]);");
    break;
    case ',':
            puts("bf[bf_p]=getchar();");
    break;
    case '>':
    count=1;
    for(;;)
    {
        tmp=fgetc(Fp);
        if(tmp=='>') count++;
        else
        {
            fseek(Fp,-1L,SEEK_CUR);
            break;
        }
    }
    printf("bf_p+=%d;",count);

    break;
    case '<':
    count=1;
    for(;;)
    {
        tmp=fgetc(Fp);
        if(tmp=='<') count++;
        else
        {
            fseek(Fp,-1L,SEEK_CUR);
            break;
        }
    }
    printf("bf_p-=%d;",count);
    break;
    case '[':
        puts("\nwhile(bf[bf_p]!=0){");
    break;
    case ']':
        puts("\n}");
    break;
    case '+':
    count=1;
    for(;;)
    {
        tmp=fgetc(Fp);
        if(tmp=='+') count++;
        else
        {
            fseek(Fp,-1L,SEEK_CUR);
            break;
        }
    }
    printf("bf[bf_p]+=%d;",count);
    break;
    case '-':
    count=1;
    for(;;)
    {
        tmp=fgetc(Fp);
        if(tmp=='-') count++;
        else
        {
            fseek(Fp,-1L,SEEK_CUR);
            break;
        }
    }
    printf("bf[bf_p]-=%d;",count);
    break;
    }
}

void bf2c(char *s)
{
    Fp=fopen(s,"rb");
    if(Fp==NULL)printf("can not open file : %s",s);
    else
    {
        puts("#include <stdio.h>\n#include <stdlib.h>");
        puts("#define MAXLEN 300000");
        puts("char bf[MAXLEN];\nint bf_p=0;char tmp;");
        puts("int main(void)\n{");
        char ch;
        for(;;)
        {
            ch=fgetc(Fp);
            if(ch==EOF)break;
            todo(ch);
        }
        puts("}");
    }
    fclose(Fp);
}

void warning(void)
{
        puts("you can use by :");
        puts("bf2c </path/to/file>");
}

int main(int argc, char* argv[])
{
    if(argc!=2)
    {
        warning();
    }
    else if(argc==2)
    {
        bf2c(argv[1]);
    }
    return 0;
}
