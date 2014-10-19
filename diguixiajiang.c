//实验二 递归下降分析法

#include <stdio.h>
#include <string.h>
	

char sym;						// 表示当前符号（即匹配符号）
char ch[100];					//用来存储输入的字符串
int count=0;					//作为移向下一个字符的下标

void advance();					//函数声明
void error();
void E();
void E1();
void T();
void T1();
void F();

void advance(){					//移向下一个字符
	sym=ch[count++];
}

void error(){					//出错函数，即输入串不符合该文法
	printf("出错！不符合该文法！\n");
}

void E(){						//开始对每个非终结符进行递归
	printf("\nE->TE'\n");
	T();
	E1();
}

void E1(){
	if(sym=='+'){
		printf("E'->+TE'\n");
		advance();
		T();
		E1();
	}

	else{
		printf("E'->ε\n");
	}
}

void T(){
	printf("T->FT'\n");
	F();
	T1();
}

void T1(){
	if(sym=='*'){
		printf("T'->*FT'\n");
		advance();
		F();
		T1();
	}
	else{
		printf("T'->ε\n");
	}
}

void F(){
	if(sym=='i'){
		printf("F->i\n");
		advance();
	}
	else if(sym=='('){
		printf("F->(E)\n");
		advance();
		E();
		if(sym==')'){
			advance();
		}
		else{
			error();
		}
	}
	else{
		error();
	}
}

int main(){
	char c;						//存储当前输入的字符
	int i=0;
	
	printf("文法如下：\n");
	printf("E->TE'\nE'->+TE'|ε\nT->FT'\nT'->*FT'|ε\nF->(E)|i\n\n");
	printf("请输入待判断的符号串（以“#”结束）\n");
	scanf("%c",&c);

	while(c!='#'){
		ch[i++]=c;
		scanf("%c",&c);
	}
	ch[i++]='#';
	ch[i]='\0';
	
	advance();
	E();

	if(sym=='#')
		printf("\n成功分析！输入串符合该文法！\n");
	else
		printf("出错！不符合该文法！\n");
}
