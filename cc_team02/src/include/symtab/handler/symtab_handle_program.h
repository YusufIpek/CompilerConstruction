#ifndef MCC_SYMTAB_HANDLE_PROGRAM_H
#define MCC_SYMTAB_HANDLE_PROGRAM_H

#include "ast_program.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_symtab_handle_program_post_order(struct mCc_ast_program *program,
                                          void *data);

void mCc_symtab_handle_program_pre_order(struct mCc_ast_program *program,
                                          void *data);

#ifdef __cplusplus
}
#endif

#endif
