#include <assert.h>
#include <stdlib.h>

#include "mCc/ast/print/ast_basic_printing.h"
#include "mCc/ast/print/ast_print_assignment.h"
#include "mCc/ast/visit/ast_visit_assignment.h"

void mCc_ast_print_dot_assignment(FILE *out,
                                  struct mCc_ast_assignment *assignment)
{
	/*TODO*/
}

static struct mCc_ast_visitor print_dot_visitor(FILE *out)
{
	assert(out);

	return (struct mCc_ast_visitor){

	};
}
