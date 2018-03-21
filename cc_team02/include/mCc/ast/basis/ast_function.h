#ifndef MCC_AST_FUNCTION_H
#define MCC_AST_FUNCTION_H

#include <stddef.h>

#include "mCc/ast/basis/ast_declaration.h"
#include "mCc/ast/basis/ast_expression.h"
#include "mCc/ast/basis/ast_identifier.h"
#include "mCc/ast/basis/ast_node.h"
#include "mCc/ast/basis/ast_statement.h"

#ifdef __cplusplus
extern "C" {
#endif

// TODO: really required separately or using mcc_type?
enum mCc_ast_function_return_type {
	MCC_AST_FUNCTION_RETURN_TYPE_VOID,
	MCC_AST_FUNCTION_RETURN_TYPE_INT,
	MCC_AST_FUNCTION_RETURN_TYPE_FLOAT,
	MCC_AST_FUNCTION_RETURN_TYPE_BOOL,
	MCC_AST_FUNCTION_RETURN_TYPE_STRING
};

struct mCc_ast_function_def {
	struct mCc_ast_node node;

	/* MCC_AST_IDENTIFIER */
	struct mCc_ast_identifier *identifier;
	enum mCc_ast_function_return_type return_type;
	/* Just a helper */
	struct mCc_ast_statement *first_statement;

	struct mCc_ast_declaration *first_parameter;

	struct mCc_ast_function_def *next_function_def;
};

struct mCc_ast_function_def *mCc_ast_new_non_parameterized_function_def(
    struct mCc_ast_identifier *identifier,
    enum mCc_ast_function_return_type return_type,
    struct mCc_ast_statement *stmts);

struct mCc_ast_function_def *mCc_ast_new_parameterized_function_def(
    struct mCc_ast_identifier *identifier,
    enum mCc_ast_function_return_type return_type,
    struct mCc_ast_declaration *params, struct mCc_ast_statement *stmts);

void mCc_ast_delete_function_def(struct mCc_ast_function_def *function_def);

/* ---------------------------------------------------------------- Function
 * call*/

struct mCc_ast_function_call {
	struct mCc_ast_node node;

	/* MCC_AST_IDENTIFIER */
	struct mCc_ast_identifier identifier;

	/* MCC_AST_EXPRESSION*/
	struct mCc_ast_expression *arguments;
};

struct mCc_ast_function_call *
mCc_ast_new_parameterized_function_call(struct mCc_ast_identifier *identifier,
                                        struct mCc_ast_expression *args);

struct mCc_ast_function_call *mCc_ast_new_non_parameterized_function_call(
    struct mCc_ast_identifier *identifier);

void mCc_ast_delete_function_call(struct mCc_ast_function_call *function_call);

#ifdef __cplusplus
}
#endif

#endif
