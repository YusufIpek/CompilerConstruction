#include "mCc/ast.h"
#include "mCc/parser.h"
#include "mCc_test/mCc_test_utils.h"
#include "gtest/gtest.h"


TEST(Parser, BinaryOp_1)
{
	const char input[] = "192 + 3.14";
	auto result = mCc_parser_parse_string(input);

	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);

	auto expr = result.expression;

	// root
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_BINARY_OP, expr->type);
	ASSERT_EQ(MCC_AST_BINARY_OP_ADD, expr->op);

	// root -> lhs
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_LITERAL, expr->lhs->type);

	// root -> lhs -> literal
	ASSERT_EQ(MCC_AST_DATA_TYPE_INT, expr->lhs->literal->type);
	ASSERT_EQ(192, expr->lhs->literal->i_value);

	// root -> rhs
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_LITERAL, expr->rhs->type);

	// root -> rhs -> literal
	ASSERT_EQ(MCC_AST_DATA_TYPE_FLOAT, expr->rhs->literal->type);
	ASSERT_EQ(3.14, expr->rhs->literal->f_value);

	mCc_ast_delete_expression(expr);
}


TEST(Parser, BinaryOp_2){
	const char input[] = "192 > 3.14";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);

	auto expr = result.expression;

	// root
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_BINARY_OP, expr->type);
	ASSERT_EQ(MCC_AST_BINARY_OP_GREATER_THAN, expr->op);

	mCc_ast_delete_expression(expr);

}


TEST(Parser, BinaryOp_3){
	const char input[] = "192 < 3.14";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);

	auto expr = result.expression;

	// root
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_BINARY_OP, expr->type);
	ASSERT_EQ(MCC_AST_BINARY_OP_LESS_THAN, expr->op);

	mCc_ast_delete_expression(expr);

}

TEST(Parser, BinaryOp_4){
	const char input[] = "192 >= 3.14";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);

	auto expr = result.expression;

	// root
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_BINARY_OP, expr->type);
	ASSERT_EQ(MCC_AST_BINARY_OP_GREATER_OR_EQUALS_THAN, expr->op);

	mCc_ast_delete_expression(expr);

}

TEST(Parser, BinaryOp_5){
	const char input[] = "192 <= 3.14";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);

	auto expr = result.expression;

	// root
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_BINARY_OP, expr->type);
	ASSERT_EQ(MCC_AST_BINARY_OP_LESS_OR_EQUALS_THAN, expr->op);

	mCc_ast_delete_expression(expr);
}

TEST(Parser, BinaryOp_6){
	const char input[] = "192 && 3.14";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);

	auto expr = result.expression;

	// root
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_BINARY_OP, expr->type);
	ASSERT_EQ(MCC_AST_BINARY_OP_AND, expr->op);

	mCc_ast_delete_expression(expr);
}


TEST(Parser, BinaryOp_7){
	const char input[] = "192 || 3.14";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);

	auto expr = result.expression;

	// root
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_BINARY_OP, expr->type);
	ASSERT_EQ(MCC_AST_BINARY_OP_OR, expr->op);

	mCc_ast_delete_expression(expr);
}

TEST(Parser, BinaryOp_8){
	const char input[] = "192 == 3.14";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);

	auto expr = result.expression;

	// root
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_BINARY_OP, expr->type);
	ASSERT_EQ(MCC_AST_BINARY_OP_EQUALS, expr->op);

	mCc_ast_delete_expression(expr);
}


TEST(Parser, BinaryOp_9){
	const char input[] = "192 != 3.14";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);

	auto expr = result.expression;

	// root
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_BINARY_OP, expr->type);
	ASSERT_EQ(MCC_AST_BINARY_OP_NOT_EQUALS, expr->op);

	mCc_ast_delete_expression(expr);
}

TEST(Parser, BinaryOp_10){
	const char input[] = "192 - 3.14";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);

	auto expr = result.expression;

	// root
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_BINARY_OP, expr->type);
	ASSERT_EQ(MCC_AST_BINARY_OP_SUB, expr->op);

	mCc_ast_delete_expression(expr);
}

TEST(Parser, BinaryOp_11){
	const char input[] = "192 * 3.14";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);

	auto expr = result.expression;

	// root
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_BINARY_OP, expr->type);
	ASSERT_EQ(MCC_AST_BINARY_OP_MUL, expr->op);

	mCc_ast_delete_expression(expr);
}

TEST(Parser, BinaryOp_12){
	const char input[] = "192 / 3.14";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);

	auto expr = result.expression;

	// root
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_BINARY_OP, expr->type);
	ASSERT_EQ(MCC_AST_BINARY_OP_DIV, expr->op);

	mCc_ast_delete_expression(expr);
}

TEST(Parser, NestedExpression_1)
{
	const char input[] = "42 * (-192 + 3.14)";
	auto result = mCc_parser_parse_string(input);	
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);

	auto expr = result.expression;

	// root
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_BINARY_OP, expr->type);
	ASSERT_EQ(MCC_AST_BINARY_OP_MUL, expr->op);

	// root -> lhs
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_LITERAL, expr->lhs->type);

	// root -> lhs -> literal
	ASSERT_EQ(MCC_AST_DATA_TYPE_INT, expr->lhs->literal->type);
	ASSERT_EQ(42, expr->lhs->literal->i_value);

	// root -> rhs
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_PARENTH, expr->rhs->type);

	auto subexpr = expr->rhs->expression;

	// subexpr
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_BINARY_OP, subexpr->type);
	ASSERT_EQ(MCC_AST_BINARY_OP_ADD, subexpr->op);

	// subexpr -> lhs
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_UNARY_OP, subexpr->lhs->type);

	// subexpr -> lhs -> literal

	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_LITERAL, subexpr->lhs->unary_rhs->type);
	ASSERT_EQ(MCC_AST_UNARY_OP_MINUS, subexpr->lhs->unary_op);
	


	ASSERT_EQ(MCC_AST_DATA_TYPE_INT, subexpr->lhs->unary_rhs->literal->type);
	ASSERT_EQ(192, subexpr->lhs->unary_rhs->literal->i_value);
	
	// subexpr -> rhs
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_LITERAL, subexpr->rhs->type);

	// subexpr -> rhs -> literal
	ASSERT_EQ(MCC_AST_DATA_TYPE_FLOAT, subexpr->rhs->literal->type);
	ASSERT_EQ(3.14, subexpr->rhs->literal->f_value);

	mCc_ast_delete_expression(expr);
}


TEST(Parser, UnaryExpression_1){
	const char input[] = "-5";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);

	auto expression = result.expression;

	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_UNARY_OP, expression->type);
	ASSERT_EQ(MCC_AST_UNARY_OP_MINUS, expression->unary_op);
	ASSERT_EQ(5, expression->unary_rhs->literal->i_value);
	mCc_ast_delete_expression(expression);
}


TEST(Parser, UnaryExpression_2){
	const char input[] = "-5 + 6";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);

	auto expression = result.expression;

	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_BINARY_OP, expression->type);
	mCc_ast_delete_expression(expression);
}




TEST(Parser, UnaryExpression_3){

	const char input[] = "!true";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);

	auto expression = result.expression;
	

	ASSERT_EQ(MCC_AST_UNARY_OP_NEGATION, expression->unary_op);
	mCc_ast_delete_expression(expression);
}


TEST(Parser, MissingClosingParenthesis_1)
{
	const char input[] = "(42";
	auto result = mCc_parser_parse_string(input);
	ASSERT_NE(MCC_PARSER_STATUS_OK, result.status);
	
}


TEST(Parser, Assignment_1)
{
	const char input[] = "a = 4";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);

	auto assignment = result.assignment;

	ASSERT_EQ(4, assignment->assigned_expression->literal->i_value);
	ASSERT_STREQ("a", assignment->identifier->identifier_name);
	ASSERT_EQ(MCC_AST_ASSIGNMENT_PRIMITIVE, assignment->assignment_type);
	mCc_ast_delete_assignment(assignment);
}


TEST(Parser, Assignment_2)
{
	const char input[] = "a = \"london\"";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);
	auto assignment = result.assignment;

	ASSERT_EQ(MCC_AST_ASSIGNMENT_PRIMITIVE, assignment->assignment_type);
	ASSERT_STREQ("a", assignment->identifier->identifier_name);
	ASSERT_STREQ("\"london\"", assignment->assigned_expression->literal->s_value);
	
	
	mCc_ast_delete_assignment(assignment);
}


TEST(Parser, Assignment_3)
{
	const char input[] = "a[3] = 4";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);
	auto assignment = result.assignment;

	ASSERT_EQ(MCC_AST_ASSIGNMENT_ARRAY, assignment->assignment_type);
	ASSERT_EQ(3, assignment->array_index_expression->literal->i_value);
	ASSERT_EQ(4, assignment->array_assigned_expression->literal->i_value);
	ASSERT_STREQ("a", assignment->identifier->identifier_name);
	
	mCc_ast_delete_assignment(assignment);
}

TEST(Parser, IfStatement_1)
{

	const char input[] = " if(5){}";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);
	auto if_statement = result.statement;

	ASSERT_EQ(MCC_AST_STATEMENT_IF, if_statement->statement_type);
	ASSERT_EQ(MCC_AST_DATA_TYPE_INT, if_statement->condition_expression->literal->type);
	mCc_ast_delete_statement(if_statement);
}

TEST(Parser, IfStatement_2)
{
	const char input[] = " if(5){int a;}else{int s;}";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);
	auto statement = result.statement;

	ASSERT_STREQ("s", statement->else_statement->declaration->identifier->identifier_name);
	mCc_ast_delete_statement(statement);
}

TEST(Parser, IfStatement_3)
{
	const char input[] = " if(5){if(true){}else{float a;}}";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);
	auto statement = result.statement;

	ASSERT_EQ(MCC_AST_DATA_TYPE_FLOAT, statement->if_statement->else_statement->declaration->data_type);
	mCc_ast_delete_statement(statement);
}

TEST(Parser, WhileStatement_1){
	const char input[] = "while(5){}";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);
	auto statement = result.statement;
	ASSERT_EQ(MCC_AST_STATEMENT_WHILE, statement->statement_type);
	mCc_ast_delete_statement(statement);
}

TEST(Parser, ReturnStatement_1){
	const char input[] = "return;";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);
	auto statement = result.statement;

	ASSERT_EQ(MCC_AST_STATEMENT_RETURN, statement->statement_type);
	mCc_ast_delete_statement(statement);
}

TEST(Parser, ReturnStatement_2){
	const char input[] = "return 5;";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);
	auto statement = result.statement;

	ASSERT_EQ(MCC_AST_STATEMENT_RETURN, statement->statement_type);
	ASSERT_EQ(5, statement->return_expression->literal->i_value);
	mCc_ast_delete_statement(statement);
}

TEST(Parser, NestedStatement_1){
	const char input[] = "while(5){if(5){return 5;}}";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);
	auto statement = result.statement;

	ASSERT_EQ(MCC_AST_STATEMENT_RETURN, statement->while_statement->if_statement->statement_type);
	ASSERT_EQ(5, statement->while_statement->if_statement->return_expression->literal->i_value);
	
	mCc_ast_delete_statement(statement);
}


TEST(Parser, Declaration_1){
	const char input[] = "int a";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);
	auto declaration = result.declaration;

	ASSERT_EQ(MCC_AST_DECLARATION_PRIMITIVE, declaration->declaration_type);
	ASSERT_EQ(MCC_AST_DATA_TYPE_INT, declaration->data_type);
	ASSERT_STREQ("a", declaration->identifier->identifier_name);
	mCc_ast_delete_declaration(declaration);
}

TEST(Parser, Declaration_2){
	const char input[] = "bool a";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);
	auto declaration = result.declaration;

	ASSERT_EQ(MCC_AST_DECLARATION_PRIMITIVE, declaration->declaration_type);
	ASSERT_EQ(MCC_AST_DATA_TYPE_BOOL, declaration->data_type);
	ASSERT_STREQ("a", declaration->identifier->identifier_name);
	mCc_ast_delete_declaration(declaration);
}

TEST(Parser, Declaration_3){
	const char input[] = "string a";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);
	auto declaration = result.declaration;

	ASSERT_EQ(MCC_AST_DECLARATION_PRIMITIVE, declaration->declaration_type);
	ASSERT_EQ(MCC_AST_DATA_TYPE_STRING, declaration->data_type);
	ASSERT_STREQ("a", declaration->identifier->identifier_name);
	mCc_ast_delete_declaration(declaration);
}

TEST(Parser, Declaration_4){
	const char input[] = "float a";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);
	auto declaration = result.declaration;

	ASSERT_EQ(MCC_AST_DECLARATION_PRIMITIVE, declaration->declaration_type);
	ASSERT_EQ(MCC_AST_DATA_TYPE_FLOAT, declaration->data_type);
	ASSERT_STREQ("a", declaration->identifier->identifier_name);
	mCc_ast_delete_declaration(declaration);
}

TEST(Parser, Literal_1){
	const char input[] = "a = 3.4";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);
	auto assignment = result.assignment;

	ASSERT_EQ(MCC_AST_DATA_TYPE_FLOAT, assignment->assigned_expression->literal->type);
	mCc_ast_delete_assignment(assignment);
}

TEST(Parser, Literal_2){
	const char input[] = "a = \"hallo\"";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);
	auto assignment = result.assignment;

	ASSERT_EQ(MCC_AST_DATA_TYPE_STRING, assignment->assigned_expression->literal->type);
	ASSERT_STREQ("\"hallo\"", assignment->assigned_expression->literal->s_value);

	mCc_ast_delete_assignment(assignment);
}

TEST(Parser, Literal_3){
	const char input[] = "a = true";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);
	auto assignment = result.assignment;

	ASSERT_EQ(MCC_AST_DATA_TYPE_BOOL, assignment->assigned_expression->literal->type);
	mCc_ast_delete_assignment(assignment);
}

TEST(Parser, Literal_4){
	const char input[] = "a = 3";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);
	auto assignment = result.assignment;

	ASSERT_EQ(MCC_AST_DATA_TYPE_INT, assignment->assigned_expression->literal->type);
	mCc_ast_delete_assignment(assignment);
}



TEST(Parser, Function_1){
	const char input[] = "int foo(bool a, int b){int bla;}";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);
	auto function = result.function_def;

	//test first parameter
	ASSERT_EQ(MCC_AST_DATA_TYPE_INT, function->return_type);
	ASSERT_EQ(MCC_AST_DATA_TYPE_BOOL, function->first_parameter->data_type);

	//test second parameter
	ASSERT_EQ(MCC_AST_DATA_TYPE_INT, function->first_parameter->next_declaration->data_type);

	//test statement
	ASSERT_EQ(MCC_AST_DATA_TYPE_INT, function->first_statement->declaration->data_type);
	mCc_ast_delete_function_def(function);
}


TEST(Parser, CallExpression_1){
	const char input[] = "foo()";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);
	auto call_expr = result.expression;

	ASSERT_STREQ("foo" , call_expr->function_call->identifier->identifier_name);
	mCc_ast_delete_expression(call_expr);
}

TEST(Parser, CallExpression_2){
	const char input[] = "foo(-5,5+4, a, true)";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);
	auto call_expr = result.expression;

	//test first argument
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_UNARY_OP, call_expr->function_call->first_argument->type);
	ASSERT_EQ(5, call_expr->function_call->first_argument->unary_rhs->literal->i_value);

	//test second argument
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_BINARY_OP, call_expr->function_call->first_argument->next_expr->type);
	ASSERT_EQ(MCC_AST_BINARY_OP_ADD, call_expr->function_call->first_argument->next_expr->op);
	ASSERT_EQ(4, call_expr->function_call->first_argument->next_expr->rhs->literal->i_value);

	//test third argument
	ASSERT_STREQ("a", call_expr->function_call->first_argument->next_expr->next_expr->identifier->identifier_name);

	//test fourth argument
	ASSERT_EQ(MCC_AST_DATA_TYPE_BOOL, call_expr->function_call->first_argument->next_expr->next_expr->next_expr->literal->type);

	mCc_ast_delete_expression(call_expr);
}

TEST(Parser, CallExpression_3){
	const char input[] = "foo(bla())";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);
	auto call_expr = result.expression;

	//test first argument
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_CALL_EXPR, call_expr->function_call->first_argument->type);
	ASSERT_STREQ("bla", call_expr->function_call->first_argument->function_call->identifier->identifier_name);

	mCc_ast_delete_expression(call_expr);
}

TEST(Parser, Program_1){
	const char input[] = "int get_num(){} string get_string(){}";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);
	auto program = result.program;

	ASSERT_EQ(MCC_AST_DATA_TYPE_STRING, program->first_function_def->next_function_def->return_type);
	mCc_ast_delete_program(program);
}

TEST(Parser, SourceLocation_SingleLineColumn)
{
	const char input[] = "(42 + 192)";
	auto result = mCc_parser_parse_string(input);

	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);

	auto expr = result.expression;

	EXPECT_EQ(MCC_AST_EXPRESSION_TYPE_PARENTH, expr->type);
	ASSERT_EQ(1, expr->node.sloc.start_col);

	EXPECT_EQ(MCC_AST_EXPRESSION_TYPE_BINARY_OP, expr->expression->type);
	ASSERT_EQ(2, expr->expression->node.sloc.start_col);

	EXPECT_EQ(MCC_AST_DATA_TYPE_INT, expr->expression->lhs->literal->type);
	ASSERT_EQ(2, expr->expression->lhs->literal->node.sloc.start_col);

	EXPECT_EQ(MCC_AST_DATA_TYPE_INT, expr->expression->rhs->literal->type);
	ASSERT_EQ(7, expr->expression->rhs->literal->node.sloc.start_col);
}
