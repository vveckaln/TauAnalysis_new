// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME rootdoubleDict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "TauAnalysis/interface/rootdouble.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_rootdouble(void *p = 0);
   static void *newArray_rootdouble(Long_t size, void *p);
   static void delete_rootdouble(void *p);
   static void deleteArray_rootdouble(void *p);
   static void destruct_rootdouble(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::rootdouble*)
   {
      ::rootdouble *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::rootdouble >(0);
      static ::ROOT::TGenericClassInfo 
         instance("rootdouble", ::rootdouble::Class_Version(), "TauAnalysis/interface/rootdouble.h", 5,
                  typeid(::rootdouble), DefineBehavior(ptr, ptr),
                  &::rootdouble::Dictionary, isa_proxy, 4,
                  sizeof(::rootdouble) );
      instance.SetNew(&new_rootdouble);
      instance.SetNewArray(&newArray_rootdouble);
      instance.SetDelete(&delete_rootdouble);
      instance.SetDeleteArray(&deleteArray_rootdouble);
      instance.SetDestructor(&destruct_rootdouble);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::rootdouble*)
   {
      return GenerateInitInstanceLocal((::rootdouble*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::rootdouble*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr rootdouble::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *rootdouble::Class_Name()
{
   return "rootdouble";
}

//______________________________________________________________________________
const char *rootdouble::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::rootdouble*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int rootdouble::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::rootdouble*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *rootdouble::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::rootdouble*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *rootdouble::Class()
{
   if (!fgIsA) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::rootdouble*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void rootdouble::Streamer(TBuffer &R__b)
{
   // Stream an object of class rootdouble.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(rootdouble::Class(),this);
   } else {
      R__b.WriteClassBuffer(rootdouble::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_rootdouble(void *p) {
      return  p ? new(p) ::rootdouble : new ::rootdouble;
   }
   static void *newArray_rootdouble(Long_t nElements, void *p) {
      return p ? new(p) ::rootdouble[nElements] : new ::rootdouble[nElements];
   }
   // Wrapper around operator delete
   static void delete_rootdouble(void *p) {
      delete ((::rootdouble*)p);
   }
   static void deleteArray_rootdouble(void *p) {
      delete [] ((::rootdouble*)p);
   }
   static void destruct_rootdouble(void *p) {
      typedef ::rootdouble current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::rootdouble

namespace {
  void TriggerDictionaryInitialization_rootdoubleDict_Impl() {
    static const char* headers[] = {
"TauAnalysis/interface/rootdouble.h",
0
    };
    static const char* includePaths[] = {
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/lcg/root/6.02.00-odfocd2/include",
"/exper-sw/cmst3/cmssw/users/vveckaln/CMSSW_7_4_2/src/LIP/TauAnalysis/",
0
    };
    static const char* fwdDeclCode = 
R"DICTFWDDCLS(
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$interface/rootdouble.h")))  rootdouble;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "TauAnalysis/interface/rootdouble.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"rootdouble", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("rootdoubleDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_rootdoubleDict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_rootdoubleDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_rootdoubleDict() {
  TriggerDictionaryInitialization_rootdoubleDict_Impl();
}
