#include <stdio.h>
#include <string.h>
#define maxsize 100
typedef struct lifo{
    char st[maxsize];
    int top;
}stack;//stack used during infix to postfix conversion
typedef struct operands{
    int st[maxsize];
    int top;
}operands;//stack used during evaluation of postfix expression
void create(stack *);
void createint(operands *);//for creating operands stack 
void push(stack *,char);
void pushint(operands *,int);
void eval(char []);
char pop(stack *);
int isp(char);
int icp(char);
int popint(operands *);
int main(){//Infix to Postfix conversion
    stack operator;
    int i,j,r;
    char inf[50],a;//inf is used to store infix string
    char post[50];//to store postfix string
    create(&operator);
    j=0;
    printf("Enter expression:");
    scanf("%s",inf);
    for (i=0;i<=strlen(inf);i++){
        if (inf[i]>='A' && inf[i]<='Z'){//A-Z
            printf("%c",inf[i]);
            post[j]=inf[i];
            j++;
        }
        else if (inf[i]=='\0'){//end of infix expression
            while (operator.top!=-1){
                if ((operator.st[operator.top])=='('){//ignore opening parenthesis while popping operator
                    operator.top--;
                    continue;
                }
                else{//pop out operators from stack
                    a=pop(&operator);
                    printf("%c",a);
                    post[j]=a;
                    j++;
                }
            }
        }
        else if (operator.top==-1){
            push(&operator,inf[i]);
        }
        else if(inf[i]==')'){//pop till closing parenthesis
            while (operator.st[operator.top]!='('){
                a=pop(&operator);
                printf("%c",a);
                post[j]=a;
                j++;
            }
        }
        else {
            while((isp(operator.st[operator.top])>=icp(inf[i]))){
                a=pop(&operator);
                printf("%c",a);
                post[j]=a;
                j++;
            }
            push(&operator,inf[i]);
        }
    }
    eval(post);
    return 0;
}
void create(stack *s){
    s->top=-1;
    return;
}
void createint(operands *op){
    op->top=-1;
    return;
}
int isp(char op){//in stack priority
    switch (op){
        case '+':
        case '-':
            return 2;
        case '*':
        case '/':
            return 4;
        case '^':
            return 5;
        case '(':
            return 0;
    }
}
int icp(char op){//in coming priority
    switch (op){
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 3;
        case '^':
            return 6;
        case '(':
            return 9;
    }
}
int popint(operands *op){
    op->top--;
    return (op->st[op->top+1]);
}
void pushint(operands *s, int op){
    s->top++;
    s->st[s->top]=op;
    return;
}
void push(stack *s,char op){
    s->top++;
    s->st[s->top]=op;
    return;
}
char pop(stack *s){
    s->top--;
    return(s->st[s->top+1]);
}
void eval(char e[]){//function to evaluate postfix expression
    operands result;
    int i,x,y,r,final,n,ind;
    createint(&result);
    int arr[26]={0};
    for (i=0;i<=strlen(e);i++){
        if (e[i]>='A' && e[i]<='Z'){
            ind=e[i]-'A';
            if (arr[ind]==0){
                printf("\nEnter value of %c:",e[i]);
                scanf("%d",&arr[ind]);
            }
            pushint(&result,arr[ind]);
        }
        else{
            x=popint(&result);
            y=popint(&result);
            switch(e[i]){
                case '+':
                    r=x+y;
                    break;
                case '-':
                    r=y-x;
                    break;
                case '*':
                    r=y*x;
                    break;
                case '/':
                    r=y/x;
                    break;
                case '^':
                    r=y^x;
                    break;
                
            }
            pushint(&result,r);

        }
    }
    final=popint(&result);
    printf("\nResult:%d",final);
}