%{
	#include<bits/stdc++.h>
	using namespace std;
	int yylex();	
	void yyerror(string e);
	string s;
	stack <int> stck;
	string flag;
%}

%token <str>  IF ELSE FOR OP CL OP1 CL1 TEXT SC UNR DO WHILE CONTINUE

%union{
	char *str;
}

%type <str> s stmt for dwhile continue if else

%%
ss: 	s {cout<<s<<endl;}
s:		for s | stmt s | dwhile s| if s| {};
continue:	CONTINUE SC {s=s + "goto LABEL;\n" ; flag="LABEL:" ;}| {flag = "";};

if:		IF OP TEXT CL OP1 {s = s + $1 + $2 + $3 + $4 + $5 + "\n";} s CL1 {s = s + $8;} else	;

else:	ELSE OP1 {s = s + "\n" +  $1 + $2 + "\n" ;} s CL1 {s = s + $5 + "\n";} s | { s=s+"\n" ;} ;

for:	FOR OP TEXT SC TEXT SC TEXT CL OP1 
			{   s=s + $3 + ";\nwhile("+$5+"){\n";   } s continue s CL1 {   s=s+flag+$7+";\n}\n";   }
			|
		FOR OP SC TEXT SC TEXT CL OP1 
			{   s=s + "\nwhile("+$4+"){\n";   } s continue s CL1 {   s=s+flag+$6+";\n}\n";   }
			|
		FOR OP TEXT SC TEXT SC CL OP1 
			{   s=s + $3 + ";\nwhile("+$5+"){\n";   } s continue s CL1 {   s=s+flag+"\n}\n";   }
			|
		FOR OP SC TEXT SC CL OP1 
			{   s=s + "\nwhile("+$4+"){\n";   } s continue s CL1 {   s=s+flag+"\n}\n";   }
		;

stmt:	TEXT SC {s=s+$1+$2+"\n";};
dwhile: DO OP1 
			{
				stck.push(s.length());
				s=s+"\nwhile(";
				stck.push(s.length());
			} 
			s CL1 WHILE OP TEXT CL SC 
			{
				int startIndexOfCondition = stck.top();
				stck.pop();	
				int startIndexOfBlock = stck.top();
				stck.pop();

				int len = s.length();
				string block = "";
				for(int i=startIndexOfCondition;i<len;i++)
				{
					block += s[i];
				}

				s.insert(startIndexOfCondition,strcat( $8 , "){\n" ));
				s=s+"\n}";

				s.insert(startIndexOfBlock,block);
			};
%%

void yyerror(string e)
{
	cout << e << endl;
}
int yywrap()
{
	return 1;
}
int main(void)
{
	yyparse();
}