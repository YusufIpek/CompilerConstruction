#include "basic_tac.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"

int label_count = 0;

//#include "ast_data_type.h"

// add another parameter for defining the next tac element?
// or how to define the next tac element?
// improving the whole tac structure
struct mCc_tac_element *tac_new_element(enum mCc_tac_operation operation,
                                        struct mCc_tac_identifier *argument1,
                                        struct mCc_tac_identifier *argument2,
                                        struct mCc_tac_identifier *result,
                                        enum mCc_tac_type tac_type,
                                        int tac_scope)
{
	// assert(result);

	struct mCc_tac_element *tac_element = malloc(sizeof(*tac_element));
	if (!tac_element) {
		return NULL;
	}
	tac_element->tac_operation = operation;
	tac_element->tac_argument1 = argument1;
	tac_element->tac_argument2 = argument2;
	tac_element->tac_result = result;
	tac_element->tac_type = tac_type;
	tac_element->tac_scope = tac_scope;
	tac_element->tac_next_element = NULL;
	return tac_element;
}

// connect the previous tac element to the current
void mCc_tac_connect_tac_entry(struct mCc_tac_element *previous_tac,
                               struct mCc_tac_element *tac)
{
	assert(previous_tac);
	assert(tac);

	previous_tac->tac_next_element = tac;
}

struct mCc_tac_identifier *tac_new_identifier(char *name)
{
	assert(name);
	/*
	 * NOTE:
	 *
	 * Not sure why, but if using malloc valgrind reports the following at
	 * malloc: "Uninitialised value was created by a heap allocation"
	 *
	 * Workaround: using calloc
	 */
	struct mCc_tac_identifier *tac_identifier =
	    calloc(sizeof(*tac_identifier), 1);
	if (!tac_identifier) {
		return NULL;
	}

	tac_identifier->name = strndup(name, strlen(name) + 1);
	tac_identifier->type = MCC_IDENTIFIER_TAC_TYPE_VAR;
	tac_identifier->is_param = false;
	// tac_identifier->stack_offset;
	return tac_identifier;
}

struct mCc_tac_identifier *tac_new_identifier_string(char *string)
{
	// assert(value);

	struct mCc_tac_identifier *tac_identifier =
	    calloc(sizeof(*tac_identifier), 1);
	if (!tac_identifier) {
		return NULL;
	}
	tac_identifier->s_val = string;
	tac_identifier->name = NULL;
	tac_identifier->type = MCC_IDENTIFIER_TAC_TYPE_STRING;
	tac_identifier->is_param = false;
	// tac_identifier->stack_offset;
	return tac_identifier;
}

struct mCc_tac_identifier *tac_new_identifier_float(double value)
{
	// assert(value);

	struct mCc_tac_identifier *tac_identifier =
	    calloc(sizeof(*tac_identifier), 1);
	if (!tac_identifier) {
		return NULL;
	}
	tac_identifier->f_val = value;
	tac_identifier->name = NULL;
	tac_identifier->type = MCC_IDENTIFIER_TAC_TYPE_FLOAT;
	tac_identifier->is_param = false;
	// tac_identifier->stack_offset;
	return tac_identifier;
}

struct mCc_tac_identifier *tac_new_identifier_int(long value)
{
	// assert(value);

	struct mCc_tac_identifier *tac_identifier =
	    calloc(sizeof(*tac_identifier), 1);
	if (!tac_identifier) {
		return NULL;
	}
	tac_identifier->i_val = value;
	tac_identifier->name = NULL;
	tac_identifier->type = MCC_IDENTIFIER_TAC_TYPE_INTEGER;
	tac_identifier->is_param = false;
	// tac_identifier->stack_offset;
	return tac_identifier;
}

struct mCc_tac_identifier *tac_new_identifier_bool(bool value)
{
	// assert(value);

	struct mCc_tac_identifier *tac_identifier =
	    calloc(sizeof(*tac_identifier), 1);
	if (!tac_identifier) {
		return NULL;
	}
	tac_identifier->b_val = value;
	tac_identifier->name = NULL;
	tac_identifier->type = MCC_IDENTIFIER_TAC_TYPE_BOOL;
	tac_identifier->is_param = false;
	// tac_identifier->stack_offset;
	return tac_identifier;
}

// TODO: maybe here the the char has to be freed
// function for concatenate a name of a variable with the scope
struct mCc_tac_identifier *mCc_helper_concat_name_and_scope(char *name,
                                                            int scope)
{
	assert(name);

	// if (scope != NULL) {
	// puts scope level behind the variable name
	char new_name[BASIC_BUFFER_SIZE];
	snprintf(new_name, BASIC_BUFFER_SIZE, "%s%d", name, scope);
	struct mCc_tac_identifier *tac_identifier = tac_new_identifier(new_name);
	// free(new_name);
	return tac_identifier;
	/*} else {
	    return tac_new_identifier(name);
	}*/
}

void mCc_tac_element_delete(struct mCc_tac_element *tac_element)
{
	assert(tac_element);

	if (tac_element->tac_argument1 != NULL) {
		mCc_tac_delete_identifier(tac_element->tac_argument1);
	}
	if (tac_element->tac_argument2 != NULL) {
		mCc_tac_delete_identifier(tac_element->tac_argument2);
	}
	if (tac_element->tac_result != NULL) {
		mCc_tac_delete_identifier(tac_element->tac_result);
	}
	free(tac_element);
}

/*
 * delete the control-flow-graph (cfg) before the tac is deleted!
 */
void mCc_tac_delete(struct mCc_tac_element *tac_element)
{
	assert(tac_element);

	struct mCc_tac_element *next_tac_element;
	while (tac_element != NULL) {
		next_tac_element = tac_element->tac_next_element;
		mCc_tac_element_delete(tac_element);
		tac_element = next_tac_element;
	}
}

void mCc_tac_delete_identifier(struct mCc_tac_identifier *identifier)
{
	assert(identifier);

	if ((identifier->type == MCC_IDENTIFIER_TAC_TYPE_STRING ||
	     identifier->type == MCC_IDENTIFIER_TAC_TYPE_VAR ||
	     identifier->type == MCC_IDENTIFIER_TAC_TYPE_FUNCTION_CALL ||
	     identifier->type == MCC_IDENTIFIER_TAC_TYPE_FUNCTION_DEF) &&
	    identifier->name != NULL) {
		free(identifier->name);
	}
	free(identifier);
}

struct mCc_tac_identifier *
mCc_tac_create_from_tac_identifier(struct mCc_tac_identifier *identifier)
{
	assert(identifier);

	struct mCc_tac_identifier *to_create;

	switch (identifier->type) {
	case MCC_IDENTIFIER_TAC_TYPE_INTEGER:
		to_create = tac_new_identifier_int(identifier->i_val);
		to_create->is_param = identifier->is_param;
		return to_create;
	case MCC_IDENTIFIER_TAC_TYPE_FLOAT:
		to_create = tac_new_identifier_float(identifier->f_val);
		to_create->is_param = identifier->is_param;
		return to_create;
	case MCC_IDENTIFIER_TAC_TYPE_BOOL:
		to_create = tac_new_identifier_bool(identifier->b_val);
		to_create->is_param = identifier->is_param;
		return to_create;
	case MCC_IDENTIFIER_TAC_TYPE_STRING:
	default: break;
	}
	to_create = tac_new_identifier(identifier->name);
	to_create->is_param = identifier->is_param;
	return to_create;
}

// is this function needed?
struct mCc_tac_element *
mCc_tac_create_new_lable_tac_element(enum mCc_tac_operation label_type,
                                     struct mCc_tac_identifier *identifier,
                                     struct mCc_tac_element *previous_tac)
{
	assert(previous_tac);

	struct mCc_tac_identifier *label = mCc_tac_create_new_lable_identifier();

	struct mCc_tac_element *tac;
	if (identifier != NULL) {
		tac = tac_new_element(label_type, identifier, NULL, label,
		                      MCC_TAC_TYPE_NO_TYPE, 0);

	} else {
		tac = tac_new_element(label_type, NULL, NULL, label,
		                      MCC_TAC_TYPE_NO_TYPE, 0);
	}
	mCc_tac_connect_tac_entry(previous_tac, tac);
	return tac;
}

struct mCc_tac_identifier *mCc_tac_create_new_lable_identifier()
{
	/*
	 * currently "l" is used as prefix, but it may be a longer string
	 * (reason for the increased buffer)
	 */
	char label_name[BASIC_BUFFER_SIZE] = "l";
	struct mCc_tac_identifier *label =
	    mCc_helper_concat_name_and_scope(label_name, label_count);
	label_count++;
	return label;
}
