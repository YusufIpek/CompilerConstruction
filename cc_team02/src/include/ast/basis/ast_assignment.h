#ifndef MCC_AST_ASSIGNMENT_H
#define MCC_AST_ASSIGNMENT_H

#include "ast_expression.h"
#include "ast_identifier.h"
#include "ast_node.h"

#ifdef __cplusplus
extern "C" {
#endif

enum mCc_ast_assignment_type {
	MCC_AST_ASSIGNMENT_PRIMITIVE,
	MCC_AST_ASSIGNMENT_ARRAY
};

struct mCc_ast_assignment {
	struct mCc_ast_node node;
	/* MCC_AST_IDENTIFIER */
	struct mCc_ast_identifier *identifier;
	enum mCc_ast_assignment_type assignment_type;

	// for semantic checks
	struct mCc_validation_status_result *semantic_error;

	union {
		/* MCC_AST_EXPRESSION */
		struct mCc_ast_expression *assigned_expression;

		struct {
			/* MCC_AST_EXPRESSION */
			struct mCc_ast_expression *array_index_expression;
			/* MCC_AST_EXPRESSION */
			struct mCc_ast_expression *array_assigned_expression;
		};
	};
};

struct mCc_ast_assignment *mCc_ast_new_primitive_assignment(
    struct mCc_ast_identifier *identifier,
    struct mCc_ast_expression *assigned_expresion_value);

struct mCc_ast_assignment *
mCc_ast_new_array_assignment(struct mCc_ast_identifier *identifier,
                             struct mCc_ast_expression *index,
                             struct mCc_ast_expression *value);

void mCc_ast_delete_assignment(struct mCc_ast_assignment *name);

struct mCc_ast_expression *
mCc_ast_get_expression(struct mCc_ast_assignment *assignment);

#ifdef __cplusplus
}
#endif

#endif
