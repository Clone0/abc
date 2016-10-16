%{
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

struct sym_table{
char sym_name[10];
char sym_type[10];
double val;
}Sym[10];

struct quad{
char opr[20];
char op1[20];
char op2[20];
char res[20];
}Quad[20];

struct stack{
char *items[20];
int top;
}Stk;

int sym_cnt=0;
int ind=0;
int temp_var=0;
int yylex();
int yyerror();

int search_sym(char[]);
void add_sym(char[],char[],double);
void disp_sym();

void add_quad(char[],char[],char[],char[]);
void disp_quad();

void push(char *);
char *pop();
%}

%union{
double dval;
char string[10];
}

%token MAIN
%token <dval> NUMBER
%token <string> DATATYPE
%token <string> IDENTIFIER

%type <string> varlist
%type <string> expr

%left '+' '-'
%left '*' '/'

%start program

%%
program:MAIN '('')''{'body'}'
;
body: varstmt stmlist
;
varstmt: vardec varstmt |
;
vardec: DATATYPE varlist ';'
;
varlist: varlist ',' IDENTIFIER { 
					if(search_sym($3)!=-1){
						printf("Multiple Declaration of Variable %s\n",$3);
					}
					else{
						add_sym($3,$<string>0,0);
					}					
					} //IMP

| IDENTIFIER '=' NUMBER {
				if(search_sym($1)!=-1){
					printf("Multiple Declaration of Variable %s\n",$1);
				}
				else{
					add_sym($1,$<string>0,$3);
				}
			}
| IDENTIFIER {
		if(search_sym($1)!=-1)
		{
			printf("Multiple Declaration of Variable%s\n");
		}
		else{
			add_sym($1,$<string>0,0);
		}
	     }

| varlist ',' IDENTIFIER '=' NUMBER  {     //IMP
					if(search_sym($3)!=-1){
						printf("Multiple Declaration of Variable5%s\n",$3);
					}
					else{
						add_sym($3,$<string>0,$5);
					}					
				     }
;
stmlist: stmt stmlist|
;

stmt: IDENTIFIER '=' expr ';' {add_quad("=",pop(),"",$1);}
;
expr: expr '+' expr {char s[5],s2[5]="t"; //IMP s2[5]="t" !!!!!!!!!!!!!!!!!!
			sprintf(s,"%d",temp_var);
			strcat(s2,s);
			temp_var++;
			add_quad("+",pop(),pop(),s2);
			push(s2);}

| expr '-' expr {char s[5],s2[5]="t"; //IMP no expr:
		sprintf(s,"%d",temp_var);		
		strcat(s2,s);
		temp_var++;
		add_quad("-",pop(),pop(),s2);
		push(s2);
		}

| expr '*' expr {char s[5],s2[5]="t";
		sprintf(s,"%d",temp_var);
		strcat(s2,s);
		temp_var++;
		add_quad("*",pop(),pop(),s2);
		push(s2);
		}

| expr '/' expr {char s[5],s2[5]="t";
		sprintf(s,"%d",temp_var);
		strcat(s2,s);
		temp_var++;
		add_quad("/",pop(),pop(),s2);
		push(s2);
		}

| NUMBER {
		char temp[10];
		snprintf(temp,10,"%f",$1);
		push(temp);
	 }

| IDENTIFIER {
		if(search_sym($1)==-1){
			printf("Variable %s is not defined\n",$1);
		}
		else{
			push($1);
		}
	     }
;

%%
extern FILE *yyin;
int main(){
Stk.top=-1;
yyin=fopen("input.txt","r");
yyparse();
disp_sym();
printf("\n\n");
disp_quad();
printf("\n\n");
return 0;
}

int search_sym(char sym[10]){
	int i;
	for(i=0;i<10;i++){
		if(strcmp(Sym[i].sym_name,sym)==0){
			return i;
		}
	}
	return -1;
}

void add_sym(char name[10],char type[10],double val){
	strcpy(Sym[sym_cnt].sym_name,name);
	strcpy(Sym[sym_cnt].sym_type,type);
	Sym[sym_cnt].val=val;
	sym_cnt++;
}

void disp_sym(){
	printf("Symbol Table:-\n");
	printf("Name\t\tType\t\tValue\n");
	for(int i=0;i<sym_cnt;i++){
		printf("%s\t\t%s\t\t%f\n",Sym[i].sym_name,Sym[i].sym_type,Sym[i].val);
	}
}

void add_quad(char opr[],char op1[],char op2[],char res[]){
	strcpy(Quad[ind].op1,op1);
	strcpy(Quad[ind].op2,op2);
	strcpy(Quad[ind].opr,opr);
	strcpy(Quad[ind].res,res);
	ind=ind+1;
}

void disp_quad(){
	int i;
	printf("\nThe INTERMEDIATE CODE Is : \n");
	printf("\nThe Quadruple Table \n");
	printf("\nNo.\tResult\tOperator\tOperand1\tOperand2");
	for(i=0;i<ind;i++)
  	printf("\n%d\t%s\t%s\t\t%s\t\t%s",i,Quad[i].res,Quad[i].opr,Quad[i].op1,Quad[i].op2);
}

int yyerror(char *s){
	printf("%s\n",s);
}

void push(char *str){
	Stk.top++;
	Stk.items[Stk.top]=(char *)malloc(strlen(str)+1);
	strcpy(Stk.items[Stk.top],str);
}

char *pop(){
	if(Stk.top==-1){
		printf("Stack is Empty\n");
		exit(0);
	}
	char *str=(char *)malloc(strlen(Stk.items[Stk.top])+1);
	strcpy(str,Stk.items[Stk.top]);
	Stk.top--;
	return str;
}

