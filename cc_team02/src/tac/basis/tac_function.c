#include "tac_function.h"

#include <assert.h>
#include <stdlib.h>

#include "basic_tac.h"
#include "tac_declaration.h"
#include "tac_expression.h"
#include "tac_statement.h"

enum mCc_tac_operation tac_helper_get_tac_oparation_for_parameter_type(
    enum mCc_tac_operation operation)
{
	switch (operation) {
	case MCC_TAC_OPARATION_DECLARE_PRIMITIVE_INT:
		return MCC_TAC_OPARATION_PARAM_INT_PRIMITIVE;
		break;
	case MCC_TAC_OPARATION_DECLARE_PRIMITIVE_FLOAT:
		return MCC_TAC_OPARATION_PARAM_FLOAT_PRIMITIVE;
		break;
	case MCC_TAC_OPARATION_DECLARE_PRIMITIVE_BOOL:
		return MCC_TAC_OPARATION_PARAM_BOOL_PRIMITIVE;
		break;
	case MCC_TAC_OPARATION_DECLARE_PRIMITIVE_STRING:
		return MCC_TAC_OPARATION_PARAM_STRING_PRIMITIVE;
		break;
	case MCC_TAC_OPARATION_DECLARE_ARRAY_INT:
		return MCC_TAC_OPARATION_PARAM_INT_ARRAY;
		break;
	case MCC_TAC_OPARATION_DECLARE_ARRAY_FLOAT:
		return MCC_TAC_OPARATION_PARAM_FLOAT_ARRAY;
		break;
	case MCC_TAC_OPARATION_DECLARE_ARRAY_BOOL:
		return MCC_TAC_OPARATION_PARAM_BOOL_ARRAY;
		break;
	case MCC_TAC_OPARATION_DECLARE_ARRAY_STRING:
		return MCC_TAC_OPARATION_PARAM_STRING_ARRAY;
		break;
	default: return MCC_TAC_OPARATION_EMPTY; break;
	}
}

struct mCc_tac_element *
mCc_tac_function_def(struct mCc_ast_function_def *def,
                     struct mCc_tac_element *previous_tac)
{
	assert(def);
	assert(previous_tac);

	// adds label for the start of the function
	// next function as first argument in tac element
	struct tac_new_identifier *next_function_def;
	if (def->next_function_def != NULL) {
		next_function_def = tac_new_identifier(
		    def->next_function_def->identifier->identifier_name);
	} else {
		next_function_def = NULL;
	}
	struct mCc_tac_element *tac_function_label = tac_new_element(
	    MCC_TAC_OPARATION_LABEL_FUNCTION, next_function_def, NULL,
	    tac_new_identifier(def->identifier->identifier_name),
	    MCC_TAC_TYPE_NO_TYPE, 0);
	mCc_tac_connect_tac_entry(previous_tac, tac_function_label);
	previous_tac = tac_function_label;

	// stores parameter into tac table
	struct mCc_ast_declaration *parameter = def->first_parameter;
	while (parameter != NULL) {
		struct mCc_tac_element *parameter_tac;
		if (parameter->declaration_type == MCC_AST_DECLARATION_PRIMITIVE) {
			parameter_tac =
			    mCc_tac_declaration_primitive(parameter, previous_tac);
		} else if (parameter->declaration_type == MCC_AST_DECLARATION_ARRAY) {
			parameter_tac = mCc_tac_declaration_array(parameter, previous_tac);
		}

		struct mCc_tac_element *tac = tac_new_element(
		    tac_helper_get_tac_oparation_for_parameter_type(
		        parameter_tac->tac_operation),
		    mCc_tac_create_from_tac_identifier(parameter_tac->tac_result), NULL,
		    tac_new_identifier(def->identifier->identifier_name),
		    MCC_TAC_TYPE_NO_TYPE, 0);
		mCc_tac_connect_tac_entry(parameter_tac, tac);
		previous_tac = tac;
		parameter = parameter->next_declaration;
	}

	// started function def:
	struct mCc_tac_element *tac_function_def_start =
	    tac_new_element(MCC_TAC_OPARATION_START_FUNCTION_DEF, NULL, NULL,
	                    tac_new_identifier(def->identifier->identifier_name),
	                    MCC_TAC_TYPE_NO_TYPE, 0);
	mCc_tac_connect_tac_entry(previous_tac, tac_function_def_start);
	previous_tac = tac_function_def_start;

	// tac table creation for statements:
	struct mCc_ast_statement *statement = def->first_statement;
	while (statement != NULL) {
		struct mCc_tac_element *statement_tac =
		    helper_get_tac_of_statement(statement, previous_tac);
		// Has a statement to be in the tac table?
		/*struct mCc_tac_element *tac = tac_new_element(
		    MCC_TAC_OPARATION_LABLE,
		    mCc_tac_create_from_tac_identifier(statement_tac->tac_result), NULL,
		    tac_new_identifier(def->identifier->identifier_name),
		    MCC_TAC_TYPE_NO_TYPE, 0);
		mCc_tac_connect_tac_entry(statement_tac, tac);
		previous_tac = tac;*/
		previous_tac = statement_tac;
		statement = statement->next_statement;
	}

	struct mCc_tac_element *tac_function_def_end =
	    tac_new_element(MCC_TAC_OPARATION_END_FUNCTION_DEF, NULL, NULL,
	                    tac_new_identifier(def->identifier->identifier_name),
	                    MCC_TAC_TYPE_NO_TYPE, 0);
	mCc_tac_connect_tac_entry(previous_tac, tac_function_def_end);

	return tac_function_def_end;
}

struct mCc_tac_element *
mCc_tac_function_call(struct mCc_ast_function_call *call,
                      struct mCc_tac_element *previous_tac)
{
	assert(call);
	assert(previous_tac);

	// introduces arguments of a function:
	struct mCc_tac_element *tac_starting_arguments =
	    tac_new_element(MCC_TAC_OPARATION_LABEL_ARGUMENT, NULL, NULL,
	                    tac_new_identifier(call->identifier->identifier_name),
	                    MCC_TAC_TYPE_NO_TYPE, 0);
	mCc_tac_connect_tac_entry(previous_tac, tac_starting_arguments);
	previous_tac = tac_starting_arguments;

	// call->first_argument
	// stores arguments into tac table
	struct mCc_ast_expression *argument = call->first_argument;
	while (argument != NULL) {
		struct mCc_tac_element *tac_argument =
		    helper_get_tac_of_expression(argument, previous_tac);

		struct mCc_tac_element *tac = tac_new_element(
		    tac_helper_get_tac_oparation_for_parameter_type(
		        tac_argument->tac_operation),
		    mCc_tac_create_from_tac_identifier(tac_argument->tac_result), NULL,
		    tac_new_identifier(call->identifier->identifier_name),
		    MCC_TAC_TYPE_NO_TYPE, 0);
		mCc_tac_connect_tac_entry(tac_argument, tac);
		previous_tac = tac;
		argument = argument->next_expr;
	}

	// call->identifier->identifier_name
	// stores call into tac table
	struct mCc_tac_element *tac_function_call =
	    tac_new_element(MCC_TAC_OPARATION_FUNCTION_CALL, NULL, NULL,
	                    tac_new_identifier(call->identifier->identifier_name),
	                    MCC_TAC_TYPE_NO_TYPE, 0);
	mCc_tac_connect_tac_entry(previous_tac, tac_function_call);
	return tac_function_call;
}
