#include "symtab_check.h"

#include <assert.h>
#include <stddef.h>
#include <string.h>

#include "ast_print_visitors.h"
#include "log.h"
#include "mCc/ast_visit.h"
#include "symbol_table.h"
#include "symtab_handler.h"
#include "validator.h"

//"global" visitor needed
static struct mCc_ast_visitor
symtab_visitor(struct mCc_symtab_and_validation_holder *symtab_info_holder)
{
	assert(symtab_info_holder);

	return (struct mCc_ast_visitor){

		.traversal = MCC_AST_VISIT_DEPTH_FIRST,
		.order = MCC_AST_VISIT_BOTH_ORDER,
		.userdata = symtab_info_holder,
		// TODO: declaration-handler -> in function AND in statement
		// (declaration-handler not needed anymore)
		//===============================
		// needed for symtab-construction:
		.function_def_enter_scope = mCc_symtab_enter_scope,
		.function_def_leave_scope = mCc_symtab_leave_scope,
		.statement_if_enter_scope = mCc_symtab_enter_scope,
		.statement_if_leave_scope = mCc_symtab_leave_scope,
		.statement_while_enter_scope = mCc_symtab_enter_scope,
		.statement_while_leave_scope = mCc_symtab_leave_scope,

		.statement_if_post_order = mCc_symtab_handle_if_statement_post_order,
		.statement_while_post_order =
		    mCc_symtab_handle_while_statement_post_order,

		// needed
		.identifier = mCc_symtab_handle_identifier,
		// identifier => get from symtab an link information
		//.function
		.function_def = mCc_symtab_handle_function_def_pre_order,
		.function_call = mCc_symtab_handle_function_call_pre_order,
		.function_def_post_order = mCc_symtab_handle_function_def_post_order,
		.function_call_post_order = mCc_symtab_handle_function_call_post_order,

		//.declaration => add declarations to current symtab
		.declaration_primitive =
		    mCc_symtab_handle_declaration_primitive_pre_order,
		.declaration_array = mCc_symtab_handle_declaration_array_pre_order,

		// expression
		.expression_binary_op_post_order =
		    mCc_handle_expression_binary_op_post_order,
		.expression_parenth_post_order =
		    mCc_handle_expression_parenth_post_order,
		.expression_function_call_post_order =
		    mCc_handle_expression_function_call_post_order,
		.expression_identifier_post_order =
		    mCc_handle_expression_identifier_post_order,
		.expression_array_identifier_post_order =
		    mCc_handle_expression_identifier_array_post_order,
		.expression_unary_op_post_order =
		    mCc_handle_expression_unary_op_post_order,
		.expression_literal_post_order =
		    mCc_handle_expression_literal_post_order,

		//.assignment
		.assignment_primitive_post_order =
		    mCc_symtab_handle_primitive_assignment_post_order,
		.assignment_array_post_order =
		    mCc_symtab_handle_array_assignment_post_order,

		.program_post_order = mCc_symtab_handle_program_post_order,
		.program = mCc_symtab_handle_program_pre_order,

		//=================================

		// assignment preorder
		.assignment_primitive = NULL,
		.assignment_array = NULL,

		// declaration postorder
		.declaration_primitive_post_order = NULL,
		.declaration_array_post_order = NULL,

		// maybe not needed inside symtab-construction
		//.expression
		.expression_literal = NULL,
		.expression_binary_op = NULL,
		.expression_parenth = NULL,
		.expression_function_call = NULL,
		.expression_identifier = NULL,
		.expression_array_identifier = NULL,
		.expression_unary_op = NULL,

		//.literal
		.literal_int = NULL,
		.literal_float = NULL,
		.literal_bool = NULL,
		.literal_string = NULL,

		.literal_int_post_order = NULL,
		.literal_float_post_order = NULL,
		.literal_bool_post_order = NULL,
		.literal_string_post_order = NULL,

		// statement
		.statement_if = NULL,
		.statement_while = NULL,
		.statement_return = NULL,
		.statement_assignment = NULL,
		.statement_expression = NULL,
		.statement_declaration = NULL,
		.statement_return_post_order = NULL,
		.statement_assignment_post_order = NULL,
		.statement_expression_post_order = NULL,
		.statement_declaration_post_order = NULL,
	};
}

// TODO: return status
int mCc_symtab_perform_semantic_checks(struct mCc_ast_program *program)
{
	assert(program);

	struct mCc_symbol_table *symbol_table =
	    mCc_symtab_new_symbol_table(NULL, 0);
	if (!symbol_table) {
		log_error("Malloc failed: Could not init top-level symbol-table");
		return -1;
	}
	log_debug("Top-level symbol-table with scope %d created",
	          symbol_table->scope_level);

	struct mCc_symtab_and_validation_holder info_holder;

	info_holder.symbol_table = symbol_table;
	info_holder.scope_level = 0;
	info_holder.error_count = 0;

	// TODO: add build-ins
	struct mCc_ast_visitor visitor = symtab_visitor(&info_holder);

	mCc_ast_visit_program(program, &visitor);

	log_debug("Leaving symbol-table with scope %d", symbol_table->scope_level);
	// free symtab
	mCc_symtab_delete_symbol_table(symbol_table);

	return info_holder.error_count;
}
