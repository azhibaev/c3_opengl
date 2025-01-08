#define VAR(t,s) t s;
#define VAR_POINTER(t,s) VAR(t,*s)
#define VAR_POINTER_CREATE(t,s) VAR_POINTER(t,s)
#define VAR_POINTER_INIT(t,s) VAR_POINTER(t,s)
#define VAR_POINTER_FREE(t,s) VAR_POINTER(t,s)
#define VAR_POINTER_NATIVE_CREATE(t,s) VAR_POINTER(t,s)
#define VAR_POINTER_NATIVE_INIT(t,s) VAR_POINTER(t,s)
#define VAR_POINTER_NATIVE_FREE(t,s) VAR_POINTER(t,s)
#define VAR_STRUCT(t,s) VAR(struct t,s)
#define VAR_STRUCT_POINTER(t,s) VAR_STRUCT(t,*s)
#define VAR_STRUCT_POINTER_CREATE(t,s) VAR_STRUCT_POINTER(t,s)
#define VAR_STRUCT_POINTER_INIT(t,s) VAR_STRUCT_POINTER(t,s)
#define VAR_STRUCT_POINTER_FREE(t,s) VAR_STRUCT_POINTER(t,s)
#define VAR_STRUCT_POINTER_NATIVE_CREATE(t,s) VAR_STRUCT_POINTER(t,s)
#define VAR_STRUCT_POINTER_NATIVE_INIT(t,s) VAR_STRUCT_POINTER(t,s)
#define VAR_STRUCT_POINTER_NATIVE_FREE(t,s) VAR_STRUCT_POINTER(t,s)
#include MODULE_STRUCT_H
#undef VAR_STRUCT_POINTER_NATIVE_FREE
#undef VAR_STRUCT_POINTER_NATIVE_INIT
#undef VAR_STRUCT_POINTER_NATIVE_CREATE
#undef VAR_STRUCT_POINTER_FREE
#undef VAR_STRUCT_POINTER_INIT
#undef VAR_STRUCT_POINTER_CREATE
#undef VAR_STRUCT_POINTER
#undef VAR_STRUCT
#undef VAR_POINTER_NATIVE_FREE
#undef VAR_POINTER_NATIVE_INIT
#undef VAR_POINTER_NATIVE_CREATE
#undef VAR_POINTER_FREE
#undef VAR_POINTER_INIT
#undef VAR_POINTER_CREATE
#undef VAR_POINTER
#undef VAR
