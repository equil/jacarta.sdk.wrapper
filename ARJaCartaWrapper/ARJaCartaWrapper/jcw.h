#ifndef ___JCW_H_INC___
#define ___JCW_H_INC___

#define CK_IMPORT_SPEC
#define CK_EXPORT_SPEC CK_IMPORT_SPEC
#define CK_CALL_SPEC
#define CK_FUNC_SPEC
#define CK_PTR *

#if !defined(MODULE_PREFIX)
#define MODULE_PREFIX(x) x
#endif

#define CK_DEFINE_FUNCTION(returnType, name) \
  returnType CK_EXPORT_SPEC CK_FUNC_SPEC CK_CALL_SPEC MODULE_PREFIX(name)

#define CK_DEFINE_FUNCTION_NOPREFIX(returnType, name) \
  returnType CK_EXPORT_SPEC CK_FUNC_SPEC CK_CALL_SPEC name

#define CK_DECLARE_FUNCTION(returnType, name) \
  returnType CK_EXPORT_SPEC CK_FUNC_SPEC CK_CALL_SPEC MODULE_PREFIX(name)

#define CK_DECLARE_FUNCTION_NOPREFIX(returnType, name) \
  returnType CK_EXPORT_SPEC CK_FUNC_SPEC CK_CALL_SPEC name

#define CK_DECLARE_FUNCTION_POINTER(returnType, name) \
  returnType CK_IMPORT_SPEC CK_FUNC_SPEC (CK_CALL_SPEC CK_PTR name)

#define CK_CALLBACK_FUNCTION(returnType, name) \
  returnType CK_FUNC_SPEC (CK_CALL_SPEC CK_PTR name)

#ifndef NULL_PTR
#define NULL_PTR 0
#endif

#include "pkcs11t.h"

#endif /* ___JCW_H_INC___ */
