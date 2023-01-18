%{
    #include <stdio.h>
    #include <stdlib.h>

    #define YYDEBUG 1

int yylex();
int yyerror();
%}

%token FUN;
%token VOID;
%token INT_TYPE;
%token STRING_TYPE;
%token BOOL_TYPE;
%token READ;
%token WRITE;
%token DEF;
%token FINAL;
%token UNLESS;
%token ELSE;
%token UNTIL;
%token FORENUM;
%token FOREACH;
%token IN;
%token MAIN;

%token CONST;
%token ID;

%token PLUS_ASSIGN;
%token MINUS_ASSIGN;
%token MULTI_ASSIGN;
%token DIV_ASSIGN;
%token MOD_ASSIGN;
%token ASSIGN;

%token PLUS;
%token MINUS;
%token MULTI;
%token DIV;
%token MOD;

%token GEQ;
%token GT;
%token LEQ;
%token LT;
%token EQ;
%token NEQ;

%token AND;
%token OR;

%token OPEN_BRACKET;
%token CLOSE_BRACKET;
%token OPEN_BRACE;
%token CLOSE_BRACE;
%token COLON;
%token COMMA;
%token SEMICOLON;
%token OPEN_RIGHT_BRACKET;
%token CLOSE_RIGHT_BRACKET;

%start Program

%%

Program : FUN MAIN OPEN_BRACKET CLOSE_BRACKET COLON VOID OPEN_BRACE StmtList CLOSE_BRACE {
    printf("Program -> fun main(): void { StmtList })");
}

Type: BOOL_TYPE { printf("Type -> bool\n"); } |
      INT_TYPE { printf("Type -> int\n"); } |
      STRING_TYPE { printf("Type -> string\n"); }
ArrayType: Type OPEN_RIGHT_BRACKET Expression CLOSE_RIGHT_BRACKET {
    printf("ArrayType -> Type[Expression]\n");
}
CompleteType: Type { printf("CompleteType -> Type\n"); } |
              ArrayType { printf("CompleteType -> ArrayType\n"); }

StmtList: Stmt { printf("StmtList -> Stmt\n"); } |
          Stmt StmtList { printf("StmtList -> Stmt StmtList\n"); }
Stmt: SimplStmt { printf("Stmt -> SimplStmt\n"); } |
      StructStmt { printf("Stmt -> StructStmt\n"); }
SimplStmt: DeclStmt { printf("SimplStmt -> DeclStmt\n"); } |
           AssignStmt { printf("SimplStmt -> AssignStmt\n"); } |
           IoStmt { printf("SimplStmt -> IoStmt\n"); }

VarDeclWord: DEF { printf("VarDeclWord -> def\n"); } |
             FINAL { printf("VarDeclWord -> final\n"); }
DeclStmt: VarDeclWord ID COLON CompleteType SEMICOLON { printf("VarDeclStmt -> VarDeclWord ID: CompleteType;\n"); } |
          VarDeclWord ID COLON CompleteType ASSIGN Expression SEMICOLON { printf("VarDeclStmt -> VarDeclWord ID: CompleteType = Expression;\n"); }

AssignStmt: ID AssignOperator Expression SEMICOLON { printf("AssignStmt -> ID AssignOperator Expression;\n"); }
AssignOperator: ASSIGN { printf("AssignOperator -> =\n"); } |
                PLUS_ASSIGN { printf("AssignOperator -> +=\n"); } |
                MINUS_ASSIGN { printf("AssignOperator -> -=\n"); } |
                MULTI_ASSIGN { printf("AssignOperator -> *=\n"); } |
                DIV_ASSIGN { printf("AssignOperator -> /=\n"); } |
                MOD_ASSIGN { printf("AssignOperator -> %%= \n"); }
        
Expression: Expression SimpleSign Term { printf("Expression -> Expression SimpleSign Term\n"); } |
            Term { printf("Expression -> Term\n"); }

SimpleSign: PLUS { printf("SimpleSign -> +\n"); } |
            MINUS { printf("SimpleSign -> -\n"); } |
            AND { printf("SimpleSign -> &&\n"); } |
            OR { printf("SimpleSign -> ||\n"); } |

Term: Term CompositeSign Factor { printf("Term -> Term CompositeSign Factor\n"); } |
      Factor { printf("Term -> Factor\n"); }
CompositeSign: MULTI { printf("CompleteType -> *\n"); } |
              DIV { printf("CompleteType -> /\n"); } |
              MOD { printf("CompleteType -> %%\n"); } 
Factor: OPEN_BRACKET Expression CLOSE_BRACKET { printf("Factor -> (Expression)\n"); } |
        ID { printf("Factor -> ID\n"); } |
        CONST { printf("Factor -> CONST\n"); } |
        ID OPEN_RIGHT_BRACKET Expression CLOSE_RIGHT_BRACKET { printf("Factor -> ID[Expression]\n"); }
        
IoStmt: ReadStmt SEMICOLON { printf("IoStmt -> ReadStmt\n"); } |
        WriteStmt SEMICOLON { printf("IoStmt -> WriteStmt\n"); }
ReadStmt: READ OPEN_BRACKET ID CLOSE_BRACKET { printf("ReadStmt -> read(ID)\n"); } |
          READ OPEN_BRACKET ID OPEN_RIGHT_BRACKET Expression CLOSE_RIGHT_BRACKET CLOSE_BRACKET {
            printf("ReadStmt -> read(ID[Expression])\n");
}
WriteStmt: WRITE OPEN_BRACKET Expression CLOSE_BRACKET { printf("WriteStmt -> write(Expression)\n"); }

StructStmt: UnlessStmt { printf("StructStmt -> UnlessStmt\n"); } |
            UntilStmt { printf("StructStmt -> UntilStmt\n"); } |
            ForStmt { printf("StructStmt -> ForStmt\n"); }
UnlessStmt: UNLESS OPEN_BRACKET Condition CLOSE_BRACKET OPEN_BRACE StmtList CLOSE_BRACE {printf("UnlessStmt -> unless (Condition) { StmtList }\n"); } |          
            UNLESS OPEN_BRACKET Condition CLOSE_BRACKET OPEN_BRACE StmtList CLOSE_BRACE ELSE OPEN_BRACE StmtList CLOSE_BRACE { printf("UnlessStmt -> unless (Condition) { StmtList } else { StmtList }\n"); }
UntilStmt: UNTIL OPEN_BRACKET Condition CLOSE_BRACKET OPEN_BRACE StmtList CLOSE_BRACE {
    printf("UntilStmt -> until (Condition) { StmtList }\n");
}
ForStmt: ForBody OPEN_BRACE StmtList CLOSE_BRACE{
    printf("ForStmt -> ForBody { StmtList }\n");
}
ForBody: ForEnumStmt { printf("ForBody -> ForEnumStmt\n"); } |
         ForEachStmt { printf("ForBody -> ForEachStmt\n"); }
ForEnumStmt: FORENUM OPEN_BRACKET ID IN Expression CLOSE_BRACKET {
    printf("ForEnumStmt -> forenum (ID in Expression)\n");
} |          FORENUM OPEN_BRACKET ID IN Expression COMMA Expression CLOSE_BRACKET {
    printf("ForEnumStmt -> forenum (ID in Expression, Expression)\n");
} |          FORENUM OPEN_BRACKET ID IN Expression COMMA Expression COMMA Expression CLOSE_BRACKET {
    printf("ForEnumStmt -> forenum (ID in Expression, Expression, Expression)\n");
}
ForEachStmt: FOREACH OPEN_BRACKET ID IN Expression CLOSE_BRACKET

Condition: Expression { printf("Condition -> Expression\n"); } |
           Expression Relation Expression { printf("Condition -> Expression Relation Expression\n"); }
Relation: LT { printf("Relation -> <\n"); } |
          LEQ { printf("Relation -> <=\n"); } | 
          GT { printf("Relation -> >\n"); } | 
          GEQ { printf("Relation -> >=\n"); } | 
          EQ { printf("Relation -> ==\n"); } |
          NEQ { printf("Relation -> !=\n"); } 

%% 
yyerror(char *s) {
    printf("yyerror: %s\n", s);
}

extern FILE* yyin;

main(int argc, char** argv) {
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
    }
    
    if (!yyparse()) {
        fprintf(stderr, "End\n");
    }
}