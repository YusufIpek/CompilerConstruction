#ifndef MCC_ASSEMBLY_GENERAL_H
#define MCC_ASSEMBLY_GENERAL_H

#include <stdbool.h>
#include <stdio.h>

#include "assembly_data.h"

#ifdef __cplusplus
extern "C" {
#endif

/*=========================================================== stack ops*/
/*
 * All literals are treated as variables (get their own tmp-label)
 */
void mCc_assembly_load_int(FILE *out, int calculated_offset, const char *dest);
// pops actual float-val from stack to dest
void mCc_assembly_load_float(FILE *out, int calculated_offset);
// stack_offset needs to be negative?
void mCc_assembly_push_int(FILE *out, int calculated_offset,
                           const char *ret_to_push);
// pushes float on floating-point-stack
void mCc_assembly_push_float(FILE *out, int calculated_offset);
/*============================================================= allocation */
void mCc_assembly_allocate_int_on_stack(FILE *out,
                                        struct mCc_assembly_data *data,
                                        int nr_of);
void mCc_assembly_allocate_float_on_stack(FILE *out,
                                          struct mCc_assembly_data *data,
                                          int nr_of);
void mCc_assembly_allocate_bool_on_stack(FILE *out,
                                         struct mCc_assembly_data *data,
                                         int nr_of);

void mCc_assembly_allocate_string_on_stack(FILE *out,
                                           struct mCc_assembly_data *data,
                                           const char *str);
/*============================================================= return */

void mCc_assembly_prepare_return(FILE *out, int calculated_offset);
/*============================================================= arithmetics */

void mCc_assembly_add_int(FILE *out, int calculated_offset);

void mCc_assembly_add_float(FILE *out, int calculated_offset);

void mCc_assembly_sub_int(FILE *out, int calculated_offset);

void mCc_assembly_sub_float(FILE *out, int calculated_offset);

void mCc_assembly_mul_int(FILE *out, int calculated_offset);

void mCc_assembly_mul_float(FILE *out, int calculated_offset);

void mCc_assembly_div_int(FILE *out, int calculated_offset);

void mCc_assembly_div_float(FILE *out, int calculated_offset);
/*============================================================= assignment */

void mCc_assembly_assign_int(FILE *out, int int_val, int calculated_offset);

// TODO: really required?
void mCc_assembly_assign_float(FILE *out, float float_val);

void mCc_assembly_assign_bool(FILE *out, bool bool_val, int calculated_offset);

// TODO: really required?
void mCc_assembly_assign_string(FILE *out, const char *string_val);
// TODO: what about arrays?

/*=============================================================
 * logical-binary-ops */
/*
 * TODO:
 * - values are already loaded to the registers which are compared
 * - cmp-result is stored into cmp-reg
 */

void mCc_assembly_compare_int(FILE *out, int calculated_offset_op_1,
                              int calculated_offset_op_2);

// Maybe the same?
void mCc_assembly_compare_float(FILE *out, int calculated_offset_op);

void mCc_assembly_and(FILE *out, int calculated_offset);

void mCc_assembly_or(FILE *out, int calculated_offset);
/*============================================================= unary-ops */

/*TODO:
 * - values are already stored to the registers
 */
void mCc_assembly_unary_minus_int(FILE *out);

void mCc_assembly_unary_minus_float(FILE *out);

void mCc_assembly_unary_negation(FILE *out);

/*============================================================= jumps */
/*
 * TODO: reads the value from the cmp-reg
 */

void mCc_assembly_jump_equals(FILE *out, const char *dest_label);

void mCc_assembly_jump_not_equals(FILE *out, const char *dest_label);

void mCc_assembly_jump_greater(FILE *out, const char *dest_label);

void mCc_assembly_jump_less(FILE *out, const char *dest_label);

void mCc_assembly_jump_greater_equals(FILE *out, const char *dest_label);

void mCc_assembly_jump_less_equals(FILE *out, const char *dest_label);
/*============================================================= params */

void mCc_assembly_add_param_int(FILE *out, int calculated_offset);

void mCc_assembly_add_param_float(FILE *out, int calculated_offset);

void mCc_assembly_add_param_bool(FILE *out, int calculated_offset);

void mCc_assembly_add_param_string(FILE *out, const char *string_label);
/*============================================================= call */

void mCc_assembly_call_function(FILE *out, const char *function_label);

#ifdef __cplusplus
}
#endif

#endif
