%define api.prefix {mCc_parser_}

%define api.pure full
%lex-param   {void *scanner}
%parse-param {void *scanner} {struct mCc_ast_expression** result}{struct mCc_ast_program** result_p}

%define parse.trace
%define parse.error verbose

%code requires {
#include "mCc/parser.h"
}

%{
#include <string.h>

int mCc_parser_lex();
void mCc_parser_error();

//#define loc(ast_node, ast_sloc) \
//	(ast_node)->node.sloc.start_col = (ast_sloc).first_column;
%}

%define api.value.type union
%define api.token.prefix {TK_}



%token END 0 "EOF"

%token <struct mCc_ast_identifier* > 		IDENTIFIER "IDENTIFIER"
%token <long>   			INT_LITERAL   "integer literal"
%token <double> 			FLOAT_LITERAL "float literal"
%token <const char*>        STRING_LITERAL "string literal"
%token <bool>               BOOL_LITERAL "bool literal"

%token INT_TYPE "integer type"
%token FLOAT_TYPE "float type"
%token STRING_TYPE "string type"
%token BOOL_TYPE "bool type"
%token VOID_TYPE "void type"

%token IF_KEYWORD    "if"
%token ELSE_KEYWORD  "else"
%token WHILE_KEYWORD "while"
%token RETURN_KEYWORD "return"

%token LPARENTH "("
%token RPARENTH ")"

%token LBRACE "{"
%token RBRACE "}"

%token LBRACKET "["
%token RBRACKET "]"

%token PLUS  "+"
%token MINUS "-"
%token ASTER "*"
%token SLASH "/"

%token NEGATION "!"

%token SEMICOLON ";"
%token COMMA ","

%token ASSIGNMENT "="
%token LESSEQ "<="
%token LESS "<"
%token GREATEREQ ">="
%token GREATER ">"
%token OR "||"
%token AND "&&"
%token EQUALS "=="
%token NOTEQUALS "!="

%type <enum mCc_ast_binary_op> binary_op
%type <enum mCc_ast_unary_op> unary_op
%type <enum mCc_ast_literal_type> type
%type <enum mCc_ast_function_return_type> function_def_return_type

%type <struct mCc_ast_expression *> expression single_expr arguments
%type <struct mCc_ast_literal *> literal
%type <struct mCc_ast_assignment *> assignment
%type <struct mCc_ast_declaration *> declaration parameters
%type <struct mCc_ast_function_def *> function_def function_list
%type <struct mCc_ast_statement *> statement if_stmt while_stmt ret_stmt compound_stmt statement_list
%type <struct mCc_ast_function_call *> call_expr
%type <struct mCc_ast_program *> program

%start toplevel

%%

toplevel : expression { *result = $1; printf("expression\n");}
		 | program {printf("program\n"); *result_p = $1; }
         ;

declaration : type IDENTIFIER									{ $$ = mCc_ast_new_primitive_declaration($1, $2); }
		    | type LBRACKET INT_LITERAL RBRACKET IDENTIFIER		{ $$ = mCc_ast_new_array_declaration($1, $5, $3); }
			;

assignment : IDENTIFIER ASSIGNMENT expression								{ $$ = mCc_ast_new_primitive_assignment($1, $3); }
		   | IDENTIFIER LBRACKET expression RBRACKET ASSIGNMENT expression	{ $$ = mCc_ast_new_array_assignment($1, $3, $6); }
		   ;

unary_op	: 	MINUS		{ $$ = MCC_AST_UNARY_OP_MINUS; }
			|	NEGATION	{ $$ = MCC_AST_UNARY_OP_NEGATION; }
			;
			
binary_op	:	PLUS 		{ $$ = MCC_AST_BINARY_OP_ADD; }
          	|	MINUS		{ $$ = MCC_AST_BINARY_OP_SUB; }
          	|	ASTER		{ $$ = MCC_AST_BINARY_OP_MUL; }
          	|	SLASH		{ $$ = MCC_AST_BINARY_OP_DIV; }
			|	LESSEQ		{ $$ = MCC_AST_BINARY_OP_LESS_OR_EQUALS_THAN; }
			| 	LESS		{ $$ = MCC_AST_BINARY_OP_LESS_THAN; }
			| 	GREATEREQ	{ $$ = MCC_AST_BINARY_OP_GREATER_OR_EQUALS_THAN; }
			|	GREATER		{ $$ = MCC_AST_BINARY_OP_GREATER_THAN; }
			|	OR			{ $$ = MCC_AST_BINARY_OP_OR; }
			|	AND			{ $$ = MCC_AST_BINARY_OP_AND; }
			|	EQUALS		{ $$ = MCC_AST_BINARY_OP_EQUALS; }
			|	NOTEQUALS	{ $$ = MCC_AST_BINARY_OP_NOT_EQUALS; }
          	;

single_expr : literal                      			    { $$ = mCc_ast_new_expression_literal($1); }
			| IDENTIFIER								{ $$ = mCc_ast_new_expression_identifier($1); }
			| IDENTIFIER LBRACKET expression RBRACKET	{ $$ = mCc_ast_new_expression_array_identifier($1, $3); }
			| call_expr									{ $$ = mCc_ast_new_expression_function_call($1);}
			| unary_op expression						{ $$ = mCc_ast_new_expression_unary_op($1, $2); }
            | LPARENTH expression RPARENTH    			{ $$ = mCc_ast_new_expression_parenth($2); }
            ;

expression : single_expr                      { $$ = $1; }
           | single_expr binary_op expression { $$ = mCc_ast_new_expression_binary_op($2, $1, $3); }
           ;

literal : INT_LITERAL  		{ $$ = mCc_ast_new_literal_int($1);   }
        | FLOAT_LITERAL 	{ $$ = mCc_ast_new_literal_float($1); }
		| BOOL_LITERAL		{ $$ = mCc_ast_new_literal_bool($1);  }
		| STRING_LITERAL 	{ $$ = mCc_ast_new_literal_string($1); }
        ;

type	:	INT_TYPE 	{ $$ = MCC_AST_LITERAL_TYPE_INT; }
		|	FLOAT_TYPE	{ $$ = MCC_AST_LITERAL_TYPE_FLOAT; }
		|	BOOL_TYPE	{ $$ = MCC_AST_LITERAL_TYPE_BOOL; }
		|	STRING_TYPE	{ $$ = MCC_AST_LITERAL_TYPE_STRING; }
		;

statement_list	:	statement_list statement	{
													struct mCc_ast_statement* t = $1;
													if(t == NULL){
														$$ = $2;
													}else{
														while(t->next_statement != NULL){
															t = t->next_statement;
														}
														t->next_statement = $2;
														$$ = $1;
														
													}
												}
				|	statement					{ $$ = $1;}
				;

statement   :   if_stmt			{ $$ = $1; }
            |   while_stmt		{ $$ = $1; }
            |   ret_stmt		{ $$ = $1; }
            |   declaration SEMICOLON { $$ = mCc_ast_new_declaration_statement($1); }
            |   assignment SEMICOLON  { $$ = mCc_ast_new_assign_statement($1); }
            |   expression SEMICOLON  { $$ = mCc_ast_new_expression_statement($1); }
            |   compound_stmt	{ $$ = $1; }
            ;



if_stmt :   IF_KEYWORD LPARENTH expression RPARENTH statement							{ $$ = mCc_ast_new_if_statement($3, $5, NULL); } /*else part missing, check if passing NULL is possible*/
        |   IF_KEYWORD LPARENTH expression RPARENTH statement ELSE_KEYWORD statement	{ $$ = mCc_ast_new_if_statement($3, $5, $7); }
        ;

while_stmt  :   WHILE_KEYWORD LPARENTH expression RPARENTH statement			{ $$ = mCc_ast_new_while_statement($3, $5); }
            ;

ret_stmt    :  RETURN_KEYWORD SEMICOLON												{ $$ = mCc_ast_new_return_statement(NULL); } /*check if return with no expression is possible*/
            |  RETURN_KEYWORD expression SEMICOLON									{ $$ = mCc_ast_new_return_statement($2); }
            ;

compound_stmt   : LBRACE statement_list RBRACE				{ 
																$$ = $2;
															 }
				| LBRACE  RBRACE								{ $$ = NULL;}
                ;

function_def    :   function_def_return_type IDENTIFIER LPARENTH RPARENTH compound_stmt				{ $$ = mCc_ast_new_non_parameterized_function_def($2, $1, $5); }
                |   function_def_return_type IDENTIFIER LPARENTH parameters RPARENTH compound_stmt  { $$ = mCc_ast_new_parameterized_function_def($2, $1, $4, $6); }
                ;

function_list	:	function_list function_def	{ 
													struct mCc_ast_function_def* t = $1;
													if(t == NULL){
														$$ = $2;
													}else{
														while(t->next_function_def != NULL){
															t = t->next_function_def;
														}
														t->next_function_def = $2;
														$$ = $1;
													}
													
												}
				|	function_def				{ $$ = $1;}
				;

function_def_return_type   	:   VOID_TYPE	{ $$ = MCC_AST_FUNCTION_RETURN_TYPE_VOID;}
							|	INT_TYPE 	{ $$ = MCC_AST_FUNCTION_RETURN_TYPE_INT; }
							|	FLOAT_TYPE	{ $$ = MCC_AST_FUNCTION_RETURN_TYPE_FLOAT; }
							|	BOOL_TYPE	{ $$ = MCC_AST_FUNCTION_RETURN_TYPE_BOOL; }
							|	STRING_TYPE	{ $$ = MCC_AST_FUNCTION_RETURN_TYPE_STRING; }
							;

parameters  :   declaration					{ $$ = $1; }
            |   parameters COMMA declaration	{
												struct mCc_ast_declaration* t = $1;
												if(t == NULL){
													$$ = $3;
												}else{
													while(t->next_declaration != NULL){
														t = t->next_declaration;
													}
													t->next_declaration = $3;
													$$ = $1;
												}
											}
            ;

call_expr	:	IDENTIFIER LPARENTH RPARENTH		    { $$ = 	mCc_ast_new_non_parameterized_function_call($1); }
			|	IDENTIFIER LPARENTH arguments RPARENTH	{ $$ = mCc_ast_new_parameterized_function_call($1, $3);}
			;

arguments	:	expression					{ $$ = $1; }
			| 	arguments COMMA expression 	{
												struct mCc_ast_expression* t = $1;
												if(t == NULL){
													$$ = $3;
												}else{
													while(t->next_expr != NULL){
														t = t->next_expr;
													}
													t->next_expr = $3;
													$$ = $1;
												}

											}
			;


program	:	function_list			{ $$ = mCc_ast_new_program($1); }
		;
%%

#include <assert.h>

#include "scanner.h"

void yyerror(yyscan_t *scanner, const char *msg) {}

struct mCc_parser_result mCc_parser_parse_string(const char *input)
{
	assert(input);

	struct mCc_parser_result result = { 0 };

	FILE *in = fmemopen((void *)input, strlen(input), "r");
	if (!in) {
		result.status = MCC_PARSER_STATUS_UNABLE_TO_OPEN_STREAM;
		return result;
	}

	result = mCc_parser_parse_file(in);

	fclose(in);

	return result;
}

struct mCc_parser_result mCc_parser_parse_file(FILE *input)
{
	assert(input);

	yyscan_t scanner;
	mCc_parser_lex_init(&scanner);
	mCc_parser_set_in(input, scanner);

	struct mCc_parser_result result = {
		.status = MCC_PARSER_STATUS_OK,
	};

	if (yyparse(scanner, &result.expression, &result.program) != 0) {
		result.status = MCC_PARSER_STATUS_UNKNOWN_ERROR;
	}



	mCc_parser_lex_destroy(scanner);

	return result;
}
