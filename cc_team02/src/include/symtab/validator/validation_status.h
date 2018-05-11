#ifndef MCC_VALIDATION_STATUS_TYPE_H
#define MCC_VALIDATION_STATUS_TYPE_H

#ifdef __cplusplus
extern "C" {
#endif

enum mCc_validation_status_type {
	MCC_VALIDATION_STATUS_VALID,
	MCC_VALIDATION_STATUS_INVALID_TYPE,
	//TODO: needed
	MCC_VALIDATION_STATUS_INVALID_TYPE_ARRAY,
	MCC_VALIDATION_STATUS_INVALID_IF_CONDITION,
	MCC_VALIDATION_STATUS_INVALID_LOOP_CONDITION,
	MCC_VALIDATION_STATUS_INVALID_PARAMETER,
	MCC_VALIDATION_STATUS_INVALID_RETURN,
	//====
	MCC_VALIDATION_STATUS_NO_DEF,
	MCC_VALIDATION_STATUS_NOT_UNIQUE,
	MCC_VALIDATION_STATUS_INVALID_SIGNATURE,
	MCC_VALIDATION_STATUS_NO_MAIN,
	MCC_VALIDATION_STATUS_NO_RETURN,
	MCC_VALIDATION_STATUS_RETURN_ON_VOID,
	MCC_VALIDATION_STATUS_ERROR_REPORTED_LATER,

	MCC_VALIDATION_STATUS_MISSING_RETURN_PATH
};

#ifdef __cplusplus
}
#endif

#endif
