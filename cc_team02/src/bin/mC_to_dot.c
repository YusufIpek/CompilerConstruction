#include <stdio.h>
#include <stdlib.h>

#include "mCc/ast.h"
#include "mCc/ast_print.h"
#include "mCc/parser.h"

int main(void)
{
	// original content of this file

	//	struct mCc_ast_expression *expr = NULL;
	//
	//		/* parsing phase */
	//		{
	//			struct mCc_parser_result result = mCc_parser_parse_file(stdin);
	//			if (result.status != MCC_PARSER_STATUS_OK) {
	//				return EXIT_FAILURE;
	//			}
	//			expr = result.expression;
	//		}
	//
	//		mCc_ast_print_dot_expression(stdout, expr);
	//
	//		mCc_ast_delete_expression(expr);
	//
	//	return EXIT_SUCCESS;

	// just for testing/debugging purposes
	struct mCc_ast_identifier *identifier = mCc_ast_new_identifier("my_func");
	struct mCc_ast_function_call *function_call =
	    mCc_ast_new_non_parameterized_function_call(identifier);


	mCc_ast_print_dot_function_call(stdout, function_call);

	return EXIT_SUCCESS;
}
