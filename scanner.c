//实验一 词法分析器

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char *Key[8]={"begin","integer","function","if","then","else","read","write"};     //定义保留字（关键字）
char ch;     //新读入字符
char token[20];     //已读入字符                           



int letter(char c){                 //判断字母的函数
    if(((c>='a')&&(c<='z'))||((c>='A')&&(c<='Z')))
    	return 1;
    else
    	return 0;

}

int digit(char c){                 //判断数字的函数
	if (c>='0'&&c<='9')
		return 1;
	else
		return 0;
}

int reserve(char *token){               //处理关键字（保留字）的函数
    int i;
    for(i=0;i<8;i++){
        if((strcmp(token,Key[i]))==0)
			return i;
        }
    return -1;
}

void LexAnalyze(FILE *fp){

	char token[20]={'\0'};
    char ch;              
    int i,c;
	ch=fgetc(fp);             //开始获取字符

    if(letter(ch)){            //判断该字符是否是字母
    	token[0]=ch;
    	ch=fgetc(fp);
    	i=1;

        while(letter(ch)||digit(ch)){     //判断该字符是否是字母或者数字
    		token[i]=ch;
    		i++;
    		ch=fgetc(fp);
    	}

    	token[i]='\0';                  
		fseek(fp,-1,1);
        c=reserve(token);             //判断是否保留字（关键字）

    	if(c==-1)
    	    printf("%s\t\t普通标识符\t$SYMBOL\n\n",token);
		else if(c==0)
    	    printf("%s\t\t关键字\t\t$BEGIN\n\n",token);
		else if(c==1)
    	    printf("%s\t\t关键字\t\t$INT\n\n",token);
		else if(c==2)
    	    printf("%s\t关键字\t\t$FUN\n\n",token);
		else if(c==3)
    	    printf("%s\t\t关键字\t\t$IF\n\n",token);
		else if(c==4)
    	    printf("%s\t\t关键字\t\t$THEN\n\n",token);
		else if(c==5)
    	    printf("%s\t\t关键字\t\t$ELSE\n\n",token);
		else if(c==6)
    	    printf("%s\t\t关键字\t\t$READ\n\n",token);
		else if(c==7)
    	    printf("%s\t\t关键字\t\t$WRITE\n\n",token);

    }
	else if(digit(ch)){                      //判断是否为数字
		    token[0]=ch;
			ch=fgetc(fp);
			i=1;
			while(digit(ch)){
			    token[i]=ch;
				i++;
				ch=fgetc(fp);
			}
			token[i]='\0';
			fseek(fp,-1,1);
			printf("%s\t\t常数\t\t$CONSTANT\n\n",token);
		}
	else{
	    token[0]=ch;
		switch(ch){
			case '(':
				printf("%s\t\t界符\t\t$LPAR\n\n",token);
				break;
			case ')':
				printf("%s\t\t界符\t\t$RPAR\n\n",token);
				break;
			case ',':
				printf("%s\t\t界符\t\t$COM\n\n",token);
				break;
			case ';':
				printf("%s\t\t界符\t\t$SEM\n\n",token);
				break;
			case '+':
				printf("%s\t\t算数运算符\t$ADD\n\n",token);
				break;
			case '-':
				printf("%s\t\t算数运算符\t$SUB\n\n",token);
				break;
			case '*':
				printf("%s\t\t算数运算符\t$MUL\n\n",token);
				break;
			case '/':
				printf("%s\t\t算数运算符\t$DIV\n\n",token);
				break;
			case ':':
				ch=fgetc(fp);
				token[1]=ch;
				if(ch=='='){
				    printf("%s\t\t算数表达式\t$ASSIGN\n\n",token);
				}
				else{
				    fseek(fp,-1,1);
					printf("%s\t\t界符\t\t$COL\n\n",token);
				}
				break;
			case '<':
				ch=fgetc(fp);
				token[1]=ch;
				if(ch=='='){
				     printf("%s\t\t关系运算符\t$LE\n\n",token);
				}
				else{
				    fseek(fp,-1,1);
					printf("%s\t\t关系运算符\n\n",token);
				}
				break;
			case '>':
				ch=fgetc(fp);
				token[1]=ch;
				if(ch=='='){
				     printf("%s\t\t关系运算符\t\t$GE\n\n",token);
				}
				else{
				    fseek(fp,-1,1);
					printf("%s\t\t关系运算符\n\n",token);
				}
				break;
			default:
				printf("ERROR（未定义或无法识别）！\n\n");
				break;
		}
	}
}

int main (void){
	char in_fn[30];
	FILE *fp;	
	printf("请输入文件路径和名字：");

	while(true){
	    gets(in_fn);
		if((fp=fopen(in_fn,"r"))!=NULL)
			break;
		else 
			printf("文件路径错误！");
	}
	
	printf("词法分析如下：\n\n");
	printf("单词符号\t类别\t\t助记符\n\n");
	
	while((ch=fgetc(fp))!=EOF){                                          
		if(ch==' '||ch=='\t'||ch=='\n'){}           //跳过空格、制表符、换行符
		
		else{
		    fseek(fp,-1,1);
			LexAnalyze(fp);

		}
	};
	getchar();

	return 0;
}
