#include "ast_declaration.h"

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

#include "validator.h"

struct mCc_ast_declaration *
mCc_ast_new_primitive_declaration(enum mCc_ast_data_type data_type,
                                  struct mCc_ast_identifier *identifier)
{
	struct mCc_ast_declaration *declaration = malloc(sizeof(*declaration));
	if (!declaration) {
		return NULL;
	}

	declaration->declaration_type = MCC_AST_DECLARATION_PRIMITIVE;
	declaration->data_type = data_type;
	declaration->identifier = identifier;
	// set explicitly to null
	declaration->next_declaration = NULL;
	declaration->semantic_error = NULL;

	return declaration;
}

struct mCc_ast_declaration *
mCc_ast_new_array_declaration(enum mCc_ast_data_type data_type,
                              struct mCc_ast_identifier *identifier,
                              size_t size)
{
	struct mCc_ast_declaration *declaration = malloc(sizeof(*declaration));
	if (!declaration) {
		return NULL;
	}

	declaration->declaration_type = MCC_AST_DECLARATION_ARRAY;
	declaration->data_type = data_type;
	declaration->array_identifier = identifier;
	declaration->size = size;
	// set explicitly to null
	declaration->next_declaration = NULL;
	declaration->semantic_error = NULL;

	return declaration;
}

struct mCc_ast_identifier *
mCc_ast_get_declaration_identifier(struct mCc_ast_declaration *decl)
{
	return decl->declaration_type == MCC_AST_DECLARATION_PRIMITIVE
	           ? decl->identifier
	           : decl->array_identifier;
}

void mCc_ast_delete_declaration(struct mCc_ast_declaration *declaration)
{
	assert(declaration);

	mCc_validator_delete_validation_result(declaration->semantic_error);

	if (declaration->declaration_type == MCC_AST_DECLARATION_PRIMITIVE) {
		mCc_ast_delete_identifier(declaration->identifier);
	} else if (declaration->declaration_type == MCC_AST_DECLARATION_ARRAY) {
		mCc_ast_delete_identifier(declaration->array_identifier);
	}

	if (declaration->next_declaration) {
		mCc_ast_delete_declaration(declaration->next_declaration);
	}

	free(declaration);
}
