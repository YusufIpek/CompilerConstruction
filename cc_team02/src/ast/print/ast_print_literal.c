#include "ast_print_literal.h"

#include <assert.h>
#include <stdlib.h>

#include "ast_basic_printing.h"

void mCc_print_dot_literal_int(struct mCc_ast_literal *literal, void *data)
{
	assert(literal);
	assert(data);

	char label[LABEL_SIZE] = { 0 };
	snprintf(label, sizeof(label), "%ld", literal->i_value);

	FILE *out = data;
	mCc_ast_print_dot_node(out, literal, label);
}

void mCc_print_dot_literal_float(struct mCc_ast_literal *literal, void *data)
{
	assert(literal);
	assert(data);

	char label[LABEL_SIZE] = { 0 };
	snprintf(label, sizeof(label), "%f", literal->f_value);

	FILE *out = data;
	mCc_ast_print_dot_node(out, literal, label);
}

void mCc_print_dot_literal_bool(struct mCc_ast_literal *literal, void *data)
{
	assert(literal);
	assert(data);

	char label[LABEL_SIZE] = { 0 };
	snprintf(label, sizeof(label), "%s",
	         literal->b_value == true ? "true" : "false");

	FILE *out = data;
	mCc_ast_print_dot_node(out, literal, label);
}

void mCc_print_dot_literal_string(struct mCc_ast_literal *literal, void *data)
{
	assert(literal);
	assert(data);

	char label[LABEL_SIZE] = { 0 };
	snprintf(label, sizeof(label), "%s", literal->s_value);

	FILE *out = data;
	mCc_ast_print_dot_node(out, literal, label);
}
