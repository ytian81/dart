/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.10
 * 
 * This file is not intended to be easily readable and contains a number of 
 * coding conventions designed to improve portability and efficiency. Do not make
 * changes to this file unless you know what you are doing--modify the SWIG 
 * interface file instead. 
 * ----------------------------------------------------------------------------- */

#define SWIGCSHARP


#ifdef __cplusplus
/* SwigValueWrapper is described in swig.swg */
template<typename T> class SwigValueWrapper {
  struct SwigMovePointer {
    T *ptr;
    SwigMovePointer(T *p) : ptr(p) { }
    ~SwigMovePointer() { delete ptr; }
    SwigMovePointer& operator=(SwigMovePointer& rhs) { T* oldptr = ptr; ptr = 0; delete oldptr; ptr = rhs.ptr; rhs.ptr = 0; return *this; }
  } pointer;
  SwigValueWrapper& operator=(const SwigValueWrapper<T>& rhs);
  SwigValueWrapper(const SwigValueWrapper<T>& rhs);
public:
  SwigValueWrapper() : pointer(0) { }
  SwigValueWrapper& operator=(const T& t) { SwigMovePointer tmp(new T(t)); pointer = tmp; return *this; }
  operator T&() const { return *pointer.ptr; }
  T *operator&() { return pointer.ptr; }
};

template <typename T> T SwigValueInit() {
  return T();
}
#endif

/* -----------------------------------------------------------------------------
 *  This section contains generic SWIG labels for method/variable
 *  declarations/attributes, and other compiler dependent labels.
 * ----------------------------------------------------------------------------- */

/* template workaround for compilers that cannot correctly implement the C++ standard */
#ifndef SWIGTEMPLATEDISAMBIGUATOR
# if defined(__SUNPRO_CC) && (__SUNPRO_CC <= 0x560)
#  define SWIGTEMPLATEDISAMBIGUATOR template
# elif defined(__HP_aCC)
/* Needed even with `aCC -AA' when `aCC -V' reports HP ANSI C++ B3910B A.03.55 */
/* If we find a maximum version that requires this, the test would be __HP_aCC <= 35500 for A.03.55 */
#  define SWIGTEMPLATEDISAMBIGUATOR template
# else
#  define SWIGTEMPLATEDISAMBIGUATOR
# endif
#endif

/* inline attribute */
#ifndef SWIGINLINE
# if defined(__cplusplus) || (defined(__GNUC__) && !defined(__STRICT_ANSI__))
#   define SWIGINLINE inline
# else
#   define SWIGINLINE
# endif
#endif

/* attribute recognised by some compilers to avoid 'unused' warnings */
#ifndef SWIGUNUSED
# if defined(__GNUC__)
#   if !(defined(__cplusplus)) || (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
#     define SWIGUNUSED __attribute__ ((__unused__)) 
#   else
#     define SWIGUNUSED
#   endif
# elif defined(__ICC)
#   define SWIGUNUSED __attribute__ ((__unused__)) 
# else
#   define SWIGUNUSED 
# endif
#endif

#ifndef SWIG_MSC_UNSUPPRESS_4505
# if defined(_MSC_VER)
#   pragma warning(disable : 4505) /* unreferenced local function has been removed */
# endif 
#endif

#ifndef SWIGUNUSEDPARM
# ifdef __cplusplus
#   define SWIGUNUSEDPARM(p)
# else
#   define SWIGUNUSEDPARM(p) p SWIGUNUSED 
# endif
#endif

/* internal SWIG method */
#ifndef SWIGINTERN
# define SWIGINTERN static SWIGUNUSED
#endif

/* internal inline SWIG method */
#ifndef SWIGINTERNINLINE
# define SWIGINTERNINLINE SWIGINTERN SWIGINLINE
#endif

/* exporting methods */
#if (__GNUC__ >= 4) || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4)
#  ifndef GCC_HASCLASSVISIBILITY
#    define GCC_HASCLASSVISIBILITY
#  endif
#endif

#ifndef SWIGEXPORT
# if defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
#   if defined(STATIC_LINKED)
#     define SWIGEXPORT
#   else
#     define SWIGEXPORT __declspec(dllexport)
#   endif
# else
#   if defined(__GNUC__) && defined(GCC_HASCLASSVISIBILITY)
#     define SWIGEXPORT __attribute__ ((visibility("default")))
#   else
#     define SWIGEXPORT
#   endif
# endif
#endif

/* calling conventions for Windows */
#ifndef SWIGSTDCALL
# if defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
#   define SWIGSTDCALL __stdcall
# else
#   define SWIGSTDCALL
# endif 
#endif

/* Deal with Microsoft's attempt at deprecating C standard runtime functions */
#if !defined(SWIG_NO_CRT_SECURE_NO_DEPRECATE) && defined(_MSC_VER) && !defined(_CRT_SECURE_NO_DEPRECATE)
# define _CRT_SECURE_NO_DEPRECATE
#endif

/* Deal with Microsoft's attempt at deprecating methods in the standard C++ library */
#if !defined(SWIG_NO_SCL_SECURE_NO_DEPRECATE) && defined(_MSC_VER) && !defined(_SCL_SECURE_NO_DEPRECATE)
# define _SCL_SECURE_NO_DEPRECATE
#endif



#include <stdlib.h>
#include <string.h>
#include <stdio.h>


/* Support for throwing C# exceptions from C/C++. There are two types: 
 * Exceptions that take a message and ArgumentExceptions that take a message and a parameter name. */
typedef enum {
  SWIG_CSharpApplicationException,
  SWIG_CSharpArithmeticException,
  SWIG_CSharpDivideByZeroException,
  SWIG_CSharpIndexOutOfRangeException,
  SWIG_CSharpInvalidCastException,
  SWIG_CSharpInvalidOperationException,
  SWIG_CSharpIOException,
  SWIG_CSharpNullReferenceException,
  SWIG_CSharpOutOfMemoryException,
  SWIG_CSharpOverflowException,
  SWIG_CSharpSystemException
} SWIG_CSharpExceptionCodes;

typedef enum {
  SWIG_CSharpArgumentException,
  SWIG_CSharpArgumentNullException,
  SWIG_CSharpArgumentOutOfRangeException
} SWIG_CSharpExceptionArgumentCodes;

typedef void (SWIGSTDCALL* SWIG_CSharpExceptionCallback_t)(const char *);
typedef void (SWIGSTDCALL* SWIG_CSharpExceptionArgumentCallback_t)(const char *, const char *);

typedef struct {
  SWIG_CSharpExceptionCodes code;
  SWIG_CSharpExceptionCallback_t callback;
} SWIG_CSharpException_t;

typedef struct {
  SWIG_CSharpExceptionArgumentCodes code;
  SWIG_CSharpExceptionArgumentCallback_t callback;
} SWIG_CSharpExceptionArgument_t;

static SWIG_CSharpException_t SWIG_csharp_exceptions[] = {
  { SWIG_CSharpApplicationException, NULL },
  { SWIG_CSharpArithmeticException, NULL },
  { SWIG_CSharpDivideByZeroException, NULL },
  { SWIG_CSharpIndexOutOfRangeException, NULL },
  { SWIG_CSharpInvalidCastException, NULL },
  { SWIG_CSharpInvalidOperationException, NULL },
  { SWIG_CSharpIOException, NULL },
  { SWIG_CSharpNullReferenceException, NULL },
  { SWIG_CSharpOutOfMemoryException, NULL },
  { SWIG_CSharpOverflowException, NULL },
  { SWIG_CSharpSystemException, NULL }
};

static SWIG_CSharpExceptionArgument_t SWIG_csharp_exceptions_argument[] = {
  { SWIG_CSharpArgumentException, NULL },
  { SWIG_CSharpArgumentNullException, NULL },
  { SWIG_CSharpArgumentOutOfRangeException, NULL }
};

static void SWIGUNUSED SWIG_CSharpSetPendingException(SWIG_CSharpExceptionCodes code, const char *msg) {
  SWIG_CSharpExceptionCallback_t callback = SWIG_csharp_exceptions[SWIG_CSharpApplicationException].callback;
  if ((size_t)code < sizeof(SWIG_csharp_exceptions)/sizeof(SWIG_CSharpException_t)) {
    callback = SWIG_csharp_exceptions[code].callback;
  }
  callback(msg);
}

static void SWIGUNUSED SWIG_CSharpSetPendingExceptionArgument(SWIG_CSharpExceptionArgumentCodes code, const char *msg, const char *param_name) {
  SWIG_CSharpExceptionArgumentCallback_t callback = SWIG_csharp_exceptions_argument[SWIG_CSharpArgumentException].callback;
  if ((size_t)code < sizeof(SWIG_csharp_exceptions_argument)/sizeof(SWIG_CSharpExceptionArgument_t)) {
    callback = SWIG_csharp_exceptions_argument[code].callback;
  }
  callback(msg, param_name);
}


#ifdef __cplusplus
extern "C" 
#endif
SWIGEXPORT void SWIGSTDCALL SWIGRegisterExceptionCallbacks_UnityOptimizationPlugin(
                                                SWIG_CSharpExceptionCallback_t applicationCallback,
                                                SWIG_CSharpExceptionCallback_t arithmeticCallback,
                                                SWIG_CSharpExceptionCallback_t divideByZeroCallback, 
                                                SWIG_CSharpExceptionCallback_t indexOutOfRangeCallback, 
                                                SWIG_CSharpExceptionCallback_t invalidCastCallback,
                                                SWIG_CSharpExceptionCallback_t invalidOperationCallback,
                                                SWIG_CSharpExceptionCallback_t ioCallback,
                                                SWIG_CSharpExceptionCallback_t nullReferenceCallback,
                                                SWIG_CSharpExceptionCallback_t outOfMemoryCallback, 
                                                SWIG_CSharpExceptionCallback_t overflowCallback, 
                                                SWIG_CSharpExceptionCallback_t systemCallback) {
  SWIG_csharp_exceptions[SWIG_CSharpApplicationException].callback = applicationCallback;
  SWIG_csharp_exceptions[SWIG_CSharpArithmeticException].callback = arithmeticCallback;
  SWIG_csharp_exceptions[SWIG_CSharpDivideByZeroException].callback = divideByZeroCallback;
  SWIG_csharp_exceptions[SWIG_CSharpIndexOutOfRangeException].callback = indexOutOfRangeCallback;
  SWIG_csharp_exceptions[SWIG_CSharpInvalidCastException].callback = invalidCastCallback;
  SWIG_csharp_exceptions[SWIG_CSharpInvalidOperationException].callback = invalidOperationCallback;
  SWIG_csharp_exceptions[SWIG_CSharpIOException].callback = ioCallback;
  SWIG_csharp_exceptions[SWIG_CSharpNullReferenceException].callback = nullReferenceCallback;
  SWIG_csharp_exceptions[SWIG_CSharpOutOfMemoryException].callback = outOfMemoryCallback;
  SWIG_csharp_exceptions[SWIG_CSharpOverflowException].callback = overflowCallback;
  SWIG_csharp_exceptions[SWIG_CSharpSystemException].callback = systemCallback;
}

#ifdef __cplusplus
extern "C" 
#endif
SWIGEXPORT void SWIGSTDCALL SWIGRegisterExceptionArgumentCallbacks_UnityOptimizationPlugin(
                                                SWIG_CSharpExceptionArgumentCallback_t argumentCallback,
                                                SWIG_CSharpExceptionArgumentCallback_t argumentNullCallback,
                                                SWIG_CSharpExceptionArgumentCallback_t argumentOutOfRangeCallback) {
  SWIG_csharp_exceptions_argument[SWIG_CSharpArgumentException].callback = argumentCallback;
  SWIG_csharp_exceptions_argument[SWIG_CSharpArgumentNullException].callback = argumentNullCallback;
  SWIG_csharp_exceptions_argument[SWIG_CSharpArgumentOutOfRangeException].callback = argumentOutOfRangeCallback;
}


/* Callback for returning strings to C# without leaking memory */
typedef char * (SWIGSTDCALL* SWIG_CSharpStringHelperCallback)(const char *);
static SWIG_CSharpStringHelperCallback SWIG_csharp_string_callback = NULL;


#ifdef __cplusplus
extern "C" 
#endif
SWIGEXPORT void SWIGSTDCALL SWIGRegisterStringCallback_UnityOptimizationPlugin(SWIG_CSharpStringHelperCallback callback) {
  SWIG_csharp_string_callback = callback;
}


/* Contract support */

#define SWIG_contract_assert(nullreturn, expr, msg) if (!(expr)) {SWIG_CSharpSetPendingExceptionArgument(SWIG_CSharpArgumentOutOfRangeException, msg, ""); return nullreturn; } else


/* this code will be inserted to the generated UnityOptimizationPlugin_wrap.cpp */
#include "ControlPBP.h"

using namespace AaltoGames;


#ifdef __cplusplus
extern "C" {
#endif

SWIGEXPORT void * SWIGSTDCALL CSharp_new_ControlPBP() {
  void * jresult ;
  AaltoGames::ControlPBP *result = 0 ;
  
  result = (AaltoGames::ControlPBP *)new AaltoGames::ControlPBP();
  jresult = (void *)result; 
  return jresult;
}


SWIGEXPORT void SWIGSTDCALL CSharp_delete_ControlPBP(void * jarg1) {
  AaltoGames::ControlPBP *arg1 = (AaltoGames::ControlPBP *) 0 ;
  
  arg1 = (AaltoGames::ControlPBP *)jarg1; 
  delete arg1;
}


SWIGEXPORT void SWIGSTDCALL CSharp_ControlPBP_init(void * jarg1, int jarg2, int jarg3, int jarg4, int jarg5, void * jarg6, void * jarg7, void * jarg8, void * jarg9, void * jarg10, void * jarg11, float jarg12, void * jarg13) {
  AaltoGames::ControlPBP *arg1 = (AaltoGames::ControlPBP *) 0 ;
  int arg2 ;
  int arg3 ;
  int arg4 ;
  int arg5 ;
  float *arg6 = (float *) 0 ;
  float *arg7 = (float *) 0 ;
  float *arg8 = (float *) 0 ;
  float *arg9 = (float *) 0 ;
  float *arg10 = (float *) 0 ;
  float *arg11 = (float *) 0 ;
  float arg12 ;
  float *arg13 = (float *) 0 ;
  
  arg1 = (AaltoGames::ControlPBP *)jarg1; 
  arg2 = (int)jarg2; 
  arg3 = (int)jarg3; 
  arg4 = (int)jarg4; 
  arg5 = (int)jarg5; 
  arg6 = (float *)jarg6; 
  arg7 = (float *)jarg7; 
  arg8 = (float *)jarg8; 
  arg9 = (float *)jarg9; 
  arg10 = (float *)jarg10; 
  arg11 = (float *)jarg11; 
  arg12 = (float)jarg12; 
  arg13 = (float *)jarg13; 
  (arg1)->init(arg2,arg3,arg4,arg5,(float const *)arg6,(float const *)arg7,(float const *)arg8,(float const *)arg9,(float const *)arg10,(float const *)arg11,arg12,(float const *)arg13);
}


SWIGEXPORT void SWIGSTDCALL CSharp_ControlPBP_update__SWIG_0(void * jarg1, void * jarg2, void * jarg3, void * jarg4, void * jarg5) {
  AaltoGames::ControlPBP *arg1 = (AaltoGames::ControlPBP *) 0 ;
  float *arg2 = (float *) 0 ;
  AaltoGames::TransitionFunction arg3 = (AaltoGames::TransitionFunction) 0 ;
  AaltoGames::StateCostFunction arg4 = (AaltoGames::StateCostFunction) 0 ;
  AaltoGames::OnStepDone arg5 = (AaltoGames::OnStepDone) 0 ;
  
  arg1 = (AaltoGames::ControlPBP *)jarg1; 
  arg2 = (float *)jarg2; 
  arg3 = (AaltoGames::TransitionFunction)jarg3; 
  arg4 = (AaltoGames::StateCostFunction)jarg4; 
  arg5 = (AaltoGames::OnStepDone)jarg5; 
  (arg1)->update((float const *)arg2,arg3,arg4,arg5);
}


SWIGEXPORT void SWIGSTDCALL CSharp_ControlPBP_update__SWIG_1(void * jarg1, void * jarg2, void * jarg3, void * jarg4) {
  AaltoGames::ControlPBP *arg1 = (AaltoGames::ControlPBP *) 0 ;
  float *arg2 = (float *) 0 ;
  AaltoGames::TransitionFunction arg3 = (AaltoGames::TransitionFunction) 0 ;
  AaltoGames::StateCostFunction arg4 = (AaltoGames::StateCostFunction) 0 ;
  
  arg1 = (AaltoGames::ControlPBP *)jarg1; 
  arg2 = (float *)jarg2; 
  arg3 = (AaltoGames::TransitionFunction)jarg3; 
  arg4 = (AaltoGames::StateCostFunction)jarg4; 
  (arg1)->update((float const *)arg2,arg3,arg4);
}


SWIGEXPORT double SWIGSTDCALL CSharp_ControlPBP_getSquaredCost(void * jarg1) {
  double jresult ;
  AaltoGames::ControlPBP *arg1 = (AaltoGames::ControlPBP *) 0 ;
  double result;
  
  arg1 = (AaltoGames::ControlPBP *)jarg1; 
  result = (double)(arg1)->getSquaredCost();
  jresult = result; 
  return jresult;
}


SWIGEXPORT void SWIGSTDCALL CSharp_ControlPBP_getBestControl(void * jarg1, int jarg2, void * jarg3) {
  AaltoGames::ControlPBP *arg1 = (AaltoGames::ControlPBP *) 0 ;
  int arg2 ;
  float *arg3 = (float *) 0 ;
  
  arg1 = (AaltoGames::ControlPBP *)jarg1; 
  arg2 = (int)jarg2; 
  arg3 = (float *)jarg3; 
  (arg1)->getBestControl(arg2,arg3);
}


SWIGEXPORT void SWIGSTDCALL CSharp_ControlPBP_getBestControlState(void * jarg1, int jarg2, void * jarg3) {
  AaltoGames::ControlPBP *arg1 = (AaltoGames::ControlPBP *) 0 ;
  int arg2 ;
  float *arg3 = (float *) 0 ;
  
  arg1 = (AaltoGames::ControlPBP *)jarg1; 
  arg2 = (int)jarg2; 
  arg3 = (float *)jarg3; 
  (arg1)->getBestControlState(arg2,arg3);
}


SWIGEXPORT double SWIGSTDCALL CSharp_ControlPBP_getBestTrajectoryOriginalStateCost(void * jarg1, int jarg2) {
  double jresult ;
  AaltoGames::ControlPBP *arg1 = (AaltoGames::ControlPBP *) 0 ;
  int arg2 ;
  double result;
  
  arg1 = (AaltoGames::ControlPBP *)jarg1; 
  arg2 = (int)jarg2; 
  result = (double)(arg1)->getBestTrajectoryOriginalStateCost(arg2);
  jresult = result; 
  return jresult;
}


SWIGEXPORT void SWIGSTDCALL CSharp_ControlPBP_setSamplingParams(void * jarg1, void * jarg2, void * jarg3, void * jarg4, float jarg5, void * jarg6) {
  AaltoGames::ControlPBP *arg1 = (AaltoGames::ControlPBP *) 0 ;
  float *arg2 = (float *) 0 ;
  float *arg3 = (float *) 0 ;
  float *arg4 = (float *) 0 ;
  float arg5 ;
  float *arg6 = (float *) 0 ;
  
  arg1 = (AaltoGames::ControlPBP *)jarg1; 
  arg2 = (float *)jarg2; 
  arg3 = (float *)jarg3; 
  arg4 = (float *)jarg4; 
  arg5 = (float)jarg5; 
  arg6 = (float *)jarg6; 
  (arg1)->setSamplingParams((float const *)arg2,(float const *)arg3,(float const *)arg4,arg5,(float const *)arg6);
}


SWIGEXPORT void SWIGSTDCALL CSharp_ControlPBP_startIteration(void * jarg1, unsigned int jarg2, void * jarg3) {
  AaltoGames::ControlPBP *arg1 = (AaltoGames::ControlPBP *) 0 ;
  bool arg2 ;
  float *arg3 = (float *) 0 ;
  
  arg1 = (AaltoGames::ControlPBP *)jarg1; 
  arg2 = jarg2 ? true : false; 
  arg3 = (float *)jarg3; 
  (arg1)->startIteration(arg2,(float const *)arg3);
}


SWIGEXPORT void SWIGSTDCALL CSharp_ControlPBP_startPlanningStep(void * jarg1, int jarg2) {
  AaltoGames::ControlPBP *arg1 = (AaltoGames::ControlPBP *) 0 ;
  int arg2 ;
  
  arg1 = (AaltoGames::ControlPBP *)jarg1; 
  arg2 = (int)jarg2; 
  (arg1)->startPlanningStep(arg2);
}


SWIGEXPORT int SWIGSTDCALL CSharp_ControlPBP_getPreviousSampleIdx(void * jarg1, int jarg2) {
  int jresult ;
  AaltoGames::ControlPBP *arg1 = (AaltoGames::ControlPBP *) 0 ;
  int arg2 ;
  int result;
  
  arg1 = (AaltoGames::ControlPBP *)jarg1; 
  arg2 = (int)jarg2; 
  result = (int)(arg1)->getPreviousSampleIdx(arg2);
  jresult = result; 
  return jresult;
}


SWIGEXPORT void SWIGSTDCALL CSharp_ControlPBP_getControl__SWIG_0(void * jarg1, int jarg2, void * jarg3, void * jarg4, void * jarg5) {
  AaltoGames::ControlPBP *arg1 = (AaltoGames::ControlPBP *) 0 ;
  int arg2 ;
  float *arg3 = (float *) 0 ;
  float *arg4 = (float *) 0 ;
  float *arg5 = (float *) 0 ;
  
  arg1 = (AaltoGames::ControlPBP *)jarg1; 
  arg2 = (int)jarg2; 
  arg3 = (float *)jarg3; 
  arg4 = (float *)jarg4; 
  arg5 = (float *)jarg5; 
  (arg1)->getControl(arg2,arg3,(float const *)arg4,(float const *)arg5);
}


SWIGEXPORT void SWIGSTDCALL CSharp_ControlPBP_getControl__SWIG_1(void * jarg1, int jarg2, void * jarg3, void * jarg4) {
  AaltoGames::ControlPBP *arg1 = (AaltoGames::ControlPBP *) 0 ;
  int arg2 ;
  float *arg3 = (float *) 0 ;
  float *arg4 = (float *) 0 ;
  
  arg1 = (AaltoGames::ControlPBP *)jarg1; 
  arg2 = (int)jarg2; 
  arg3 = (float *)jarg3; 
  arg4 = (float *)jarg4; 
  (arg1)->getControl(arg2,arg3,(float const *)arg4);
}


SWIGEXPORT void SWIGSTDCALL CSharp_ControlPBP_getControl__SWIG_2(void * jarg1, int jarg2, void * jarg3) {
  AaltoGames::ControlPBP *arg1 = (AaltoGames::ControlPBP *) 0 ;
  int arg2 ;
  float *arg3 = (float *) 0 ;
  
  arg1 = (AaltoGames::ControlPBP *)jarg1; 
  arg2 = (int)jarg2; 
  arg3 = (float *)jarg3; 
  (arg1)->getControl(arg2,arg3);
}


SWIGEXPORT void SWIGSTDCALL CSharp_ControlPBP_updateResults__SWIG_0(void * jarg1, int jarg2, void * jarg3, void * jarg4, double jarg5, void * jarg6, void * jarg7) {
  AaltoGames::ControlPBP *arg1 = (AaltoGames::ControlPBP *) 0 ;
  int arg2 ;
  float *arg3 = (float *) 0 ;
  float *arg4 = (float *) 0 ;
  double arg5 ;
  float *arg6 = (float *) 0 ;
  float *arg7 = (float *) 0 ;
  
  arg1 = (AaltoGames::ControlPBP *)jarg1; 
  arg2 = (int)jarg2; 
  arg3 = (float *)jarg3; 
  arg4 = (float *)jarg4; 
  arg5 = (double)jarg5; 
  arg6 = (float *)jarg6; 
  arg7 = (float *)jarg7; 
  (arg1)->updateResults(arg2,(float const *)arg3,(float const *)arg4,arg5,(float const *)arg6,(float const *)arg7);
}


SWIGEXPORT void SWIGSTDCALL CSharp_ControlPBP_updateResults__SWIG_1(void * jarg1, int jarg2, void * jarg3, void * jarg4, double jarg5, void * jarg6) {
  AaltoGames::ControlPBP *arg1 = (AaltoGames::ControlPBP *) 0 ;
  int arg2 ;
  float *arg3 = (float *) 0 ;
  float *arg4 = (float *) 0 ;
  double arg5 ;
  float *arg6 = (float *) 0 ;
  
  arg1 = (AaltoGames::ControlPBP *)jarg1; 
  arg2 = (int)jarg2; 
  arg3 = (float *)jarg3; 
  arg4 = (float *)jarg4; 
  arg5 = (double)jarg5; 
  arg6 = (float *)jarg6; 
  (arg1)->updateResults(arg2,(float const *)arg3,(float const *)arg4,arg5,(float const *)arg6);
}


SWIGEXPORT void SWIGSTDCALL CSharp_ControlPBP_updateResults__SWIG_2(void * jarg1, int jarg2, void * jarg3, void * jarg4, double jarg5) {
  AaltoGames::ControlPBP *arg1 = (AaltoGames::ControlPBP *) 0 ;
  int arg2 ;
  float *arg3 = (float *) 0 ;
  float *arg4 = (float *) 0 ;
  double arg5 ;
  
  arg1 = (AaltoGames::ControlPBP *)jarg1; 
  arg2 = (int)jarg2; 
  arg3 = (float *)jarg3; 
  arg4 = (float *)jarg4; 
  arg5 = (double)jarg5; 
  (arg1)->updateResults(arg2,(float const *)arg3,(float const *)arg4,arg5);
}


SWIGEXPORT void SWIGSTDCALL CSharp_ControlPBP_endPlanningStep(void * jarg1, int jarg2) {
  AaltoGames::ControlPBP *arg1 = (AaltoGames::ControlPBP *) 0 ;
  int arg2 ;
  
  arg1 = (AaltoGames::ControlPBP *)jarg1; 
  arg2 = (int)jarg2; 
  (arg1)->endPlanningStep(arg2);
}


SWIGEXPORT void SWIGSTDCALL CSharp_ControlPBP_endIteration(void * jarg1) {
  AaltoGames::ControlPBP *arg1 = (AaltoGames::ControlPBP *) 0 ;
  
  arg1 = (AaltoGames::ControlPBP *)jarg1; 
  (arg1)->endIteration();
}


SWIGEXPORT void SWIGSTDCALL CSharp_ControlPBP_setParams(void * jarg1, double jarg2, double jarg3, unsigned int jarg4, float jarg5) {
  AaltoGames::ControlPBP *arg1 = (AaltoGames::ControlPBP *) 0 ;
  double arg2 ;
  double arg3 ;
  bool arg4 ;
  float arg5 ;
  
  arg1 = (AaltoGames::ControlPBP *)jarg1; 
  arg2 = (double)jarg2; 
  arg3 = (double)jarg3; 
  arg4 = jarg4 ? true : false; 
  arg5 = (float)jarg5; 
  (arg1)->setParams(arg2,arg3,arg4,arg5);
}


SWIGEXPORT void SWIGSTDCALL CSharp_ControlPBP_gaussianBackPropagation__SWIG_0(void * jarg1, void * jarg2, void * jarg3) {
  AaltoGames::ControlPBP *arg1 = (AaltoGames::ControlPBP *) 0 ;
  AaltoGames::TransitionFunction arg2 = (AaltoGames::TransitionFunction) 0 ;
  AaltoGames::OnStepDone arg3 = (AaltoGames::OnStepDone) 0 ;
  
  arg1 = (AaltoGames::ControlPBP *)jarg1; 
  arg2 = (AaltoGames::TransitionFunction)jarg2; 
  arg3 = (AaltoGames::OnStepDone)jarg3; 
  (arg1)->gaussianBackPropagation(arg2,arg3);
}


SWIGEXPORT void SWIGSTDCALL CSharp_ControlPBP_gaussianBackPropagation__SWIG_1(void * jarg1, void * jarg2) {
  AaltoGames::ControlPBP *arg1 = (AaltoGames::ControlPBP *) 0 ;
  AaltoGames::TransitionFunction arg2 = (AaltoGames::TransitionFunction) 0 ;
  
  arg1 = (AaltoGames::ControlPBP *)jarg1; 
  arg2 = (AaltoGames::TransitionFunction)jarg2; 
  (arg1)->gaussianBackPropagation(arg2);
}


SWIGEXPORT void SWIGSTDCALL CSharp_ControlPBP_gaussianBackPropagation__SWIG_2(void * jarg1) {
  AaltoGames::ControlPBP *arg1 = (AaltoGames::ControlPBP *) 0 ;
  
  arg1 = (AaltoGames::ControlPBP *)jarg1; 
  (arg1)->gaussianBackPropagation();
}


SWIGEXPORT int SWIGSTDCALL CSharp_ControlPBP_getBestSampleLastIdx(void * jarg1) {
  int jresult ;
  AaltoGames::ControlPBP *arg1 = (AaltoGames::ControlPBP *) 0 ;
  int result;
  
  arg1 = (AaltoGames::ControlPBP *)jarg1; 
  result = (int)(arg1)->getBestSampleLastIdx();
  jresult = result; 
  return jresult;
}


SWIGEXPORT float SWIGSTDCALL CSharp_ControlPBP_getGBPRegularization(void * jarg1) {
  float jresult ;
  AaltoGames::ControlPBP *arg1 = (AaltoGames::ControlPBP *) 0 ;
  float result;
  
  arg1 = (AaltoGames::ControlPBP *)jarg1; 
  result = (float)(arg1)->getGBPRegularization();
  jresult = result; 
  return jresult;
}


#ifdef __cplusplus
}
#endif
