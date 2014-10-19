//实验三 预测分析法

#include <stdio.h>

char ch[20];			//存储输入串
char sign[20];			//符号栈
int digit[20];			//数字栈
int topsign;			//符号栈顶指针
int topdigit;			//数字栈顶指针
int	table[7][7]={{1,1,-1,-1,-1,-1,1},		//二维算符优先关系表
				 {1,1,-1,-1,-1,-1,1},
			     {1,1,1,1,-1,-1,1},
				 {1,1,1,1,-1,-1,1},
				 {-1,-1,-1,-1,-1,-1,2}, 
				 {1,1,1,1,2,1,1},
				 {-1,-1,-1,-1,-1,-1,0}};

void error(){
	printf("error!\n");
}

void output(){
	printf("ans=%d\n",digit[topdigit]);
}

int change(char ch){				//将符号变成算符优先关系表里的下标
	switch(ch){
		case '+':return 0;
			break;
		case '-':return 1;
			break;
		case '*':return 2;
			break;
		case '/':return 3;
			break;
		case '(':return 4; 
			break;
		case ')':return 5;
			break;
		case'#':return 6;
			break;
		default:error();
			break;
	}
}

void operate(char c){				//归约并计算的函数
	int temp;
	switch(c){
	case '+':temp=digit[topdigit-1]+digit[topdigit];
		topdigit--;
		digit[topdigit]=temp;
		topsign--;
		break;
	case '-':digit[topdigit-1]=digit[topdigit-1]-digit[topdigit];
		topdigit--;
		topsign--;
		break;
	case '*':digit[topdigit-1]=digit[topdigit-1]*digit[topdigit];
		topdigit--;
		topsign--;
		break;
	case '/':digit[topdigit-1]=digit[topdigit-1]/digit[topdigit];
		topdigit--;
		topsign--;
		break;
	case ')':topsign--;
		temp=sign[topsign];
		switch(temp){
			case '+':digit[topdigit-1]=digit[topdigit-1]+digit[topdigit];
				topdigit--;
				topsign--;
				break;
			case '-':digit[topdigit-1]=digit[topdigit-1]-digit[topdigit];
				topdigit--;
				topsign--;
				break;
			case '*':digit[topdigit-1]=digit[topdigit-1]*digit[topdigit];
				topdigit--;
				topsign--;
				break;
			case '/':digit[topdigit-1]=digit[topdigit-1]/digit[topdigit];
				topdigit--;
				topsign--;
				break;
			}

	}
}

void main(){
	char a,b,c;
	int i=0,m,n;
	
	printf("本程序仅能完成单位数输入的简单四则运算！\n");
	printf("本程序利用算符优先分析法归约过程进行计算！\n");
	printf("算符优先分析表如下：\n");
	printf("\t+\t-\t*\t/\t(\t)\t#\n");
	printf("+\t>\t>\t<\t<\t<\t<\t>\n");
	printf("-\t>\t>\t<\t<\t<\t<\t>\n");
	printf("*\t>\t>\t>\t>\t<\t<\t>\n");
	printf("/\t>\t>\t>\t>\t<\t<\t>\n");
	printf("(\t<\t<\t<\t<\t<\t<\t\n");
	printf(")\t>\t>\t>\t>\t\t>\t>\n");
	printf("#\t<\t<\t<\t<\t<\t<\t=\n");
	printf("请输入符号串（以‘#’符结束）：\n");
	
	while((c=getchar())!='#'){
		ch[i]=c;
		i++;
	}
	ch[i]='#';
	i=0;
	sign[0]='#';
	digit[0]='#';
	topsign=0;
	topdigit=0;

	b=ch[i++];

	while(b!='#'){
		if((b!='+')&&(b!='-')&&(b!='*')&&(b!='/')&&(b!='(')&&(b!=')')){		//数字直接入数字栈
			topdigit=topdigit+1;
			digit[topdigit]=b-'0';
			b=ch[i++];
		}
		else{
			a=sign[topsign];						//当前符号栈栈顶符号

			m=change(a);		//转换为下标
			n=change(b);

			if(table[m][n]==-1){				//当前符号栈栈顶符号不优先于待入栈符号，则符号入栈
				topsign=topsign+1;
				sign[topsign]=b;
				b=ch[i++];
			}
			else if(table[m][n]==0||1){			//否则进行归约并进行计算
				operate(sign[topsign]);
				topsign++;
				sign[topsign]=b;
				b=ch[i++]; 

			}
		}
	}
	operate(sign[topsign]);
	output();

}
