#ifndef MCC_AST_VISIT_FUNCTION_H
#define MCC_AST_VISIT_FUNCTION_H

#include "ast_function.h"
#include "mCc/ast_visit.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_ast_visit_optional_function_def(
    struct mCc_ast_function_def *function_def, struct mCc_ast_visitor *visitor);

void mCc_ast_visit_function_def(struct mCc_ast_function_def *function_def,
                                struct mCc_ast_visitor *visitor);

void mCc_ast_visit_function_call(struct mCc_ast_function_call *function_call,
                                 struct mCc_ast_visitor *visitor);

#ifdef __cplusplus
}
#endif

#endif
