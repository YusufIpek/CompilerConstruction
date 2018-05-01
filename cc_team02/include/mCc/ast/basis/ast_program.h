#ifndef MCC_AST_PROGRAM_H
#define MCC_AST_PROGRAM_H

#include <stddef.h>
#include <stdbool.h>

#include "mCc/ast/basis/ast_function.h"
#include "mCc/ast/basis/ast_node.h"

#ifdef __cplusplus
extern "C" {
#endif

struct mCc_ast_program {
	struct mCc_ast_node node;

	struct mCc_ast_function_def *first_function_def;

	bool is_library;
};

struct mCc_ast_program *
mCc_ast_new_program(struct mCc_ast_function_def *first_function_def);

void mCc_ast_delete_program(struct mCc_ast_program *program);

#ifdef __cplusplus
}
#endif

#endif
