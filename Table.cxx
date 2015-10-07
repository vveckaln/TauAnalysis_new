// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME Table

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
#include "interface/Table.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *Column_speclEfloatgR_Dictionary();
   static void Column_speclEfloatgR_TClassManip(TClass*);
   static void *new_Column_speclEfloatgR(void *p = 0);
   static void *newArray_Column_speclEfloatgR(Long_t size, void *p);
   static void delete_Column_speclEfloatgR(void *p);
   static void deleteArray_Column_speclEfloatgR(void *p);
   static void destruct_Column_speclEfloatgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Column_spec<float>*)
   {
      ::Column_spec<float> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Column_spec<float> >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Column_spec<float>", ::Column_spec<float>::Class_Version(), "interface/Table.h", 28,
                  typeid(::Column_spec<float>), DefineBehavior(ptr, ptr),
                  &Column_speclEfloatgR_Dictionary, isa_proxy, 4,
                  sizeof(::Column_spec<float>) );
      instance.SetNew(&new_Column_speclEfloatgR);
      instance.SetNewArray(&newArray_Column_speclEfloatgR);
      instance.SetDelete(&delete_Column_speclEfloatgR);
      instance.SetDeleteArray(&deleteArray_Column_speclEfloatgR);
      instance.SetDestructor(&destruct_Column_speclEfloatgR);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Column_spec<float>*)
   {
      return GenerateInitInstanceLocal((::Column_spec<float>*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Column_spec<float>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Column_speclEfloatgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Column_spec<float>*)0x0)->GetClass();
      Column_speclEfloatgR_TClassManip(theClass);
   return theClass;
   }

   static void Column_speclEfloatgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *Column_speclEshortgR_Dictionary();
   static void Column_speclEshortgR_TClassManip(TClass*);
   static void *new_Column_speclEshortgR(void *p = 0);
   static void *newArray_Column_speclEshortgR(Long_t size, void *p);
   static void delete_Column_speclEshortgR(void *p);
   static void deleteArray_Column_speclEshortgR(void *p);
   static void destruct_Column_speclEshortgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Column_spec<short>*)
   {
      ::Column_spec<short> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Column_spec<short> >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Column_spec<short>", ::Column_spec<short>::Class_Version(), "interface/Table.h", 28,
                  typeid(::Column_spec<short>), DefineBehavior(ptr, ptr),
                  &Column_speclEshortgR_Dictionary, isa_proxy, 4,
                  sizeof(::Column_spec<short>) );
      instance.SetNew(&new_Column_speclEshortgR);
      instance.SetNewArray(&newArray_Column_speclEshortgR);
      instance.SetDelete(&delete_Column_speclEshortgR);
      instance.SetDeleteArray(&deleteArray_Column_speclEshortgR);
      instance.SetDestructor(&destruct_Column_speclEshortgR);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Column_spec<short>*)
   {
      return GenerateInitInstanceLocal((::Column_spec<short>*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Column_spec<short>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Column_speclEshortgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Column_spec<short>*)0x0)->GetClass();
      Column_speclEshortgR_TClassManip(theClass);
   return theClass;
   }

   static void Column_speclEshortgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *Column_speclEdoublegR_Dictionary();
   static void Column_speclEdoublegR_TClassManip(TClass*);
   static void *new_Column_speclEdoublegR(void *p = 0);
   static void *newArray_Column_speclEdoublegR(Long_t size, void *p);
   static void delete_Column_speclEdoublegR(void *p);
   static void deleteArray_Column_speclEdoublegR(void *p);
   static void destruct_Column_speclEdoublegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Column_spec<double>*)
   {
      ::Column_spec<double> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Column_spec<double> >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Column_spec<double>", ::Column_spec<double>::Class_Version(), "interface/Table.h", 28,
                  typeid(::Column_spec<double>), DefineBehavior(ptr, ptr),
                  &Column_speclEdoublegR_Dictionary, isa_proxy, 4,
                  sizeof(::Column_spec<double>) );
      instance.SetNew(&new_Column_speclEdoublegR);
      instance.SetNewArray(&newArray_Column_speclEdoublegR);
      instance.SetDelete(&delete_Column_speclEdoublegR);
      instance.SetDeleteArray(&deleteArray_Column_speclEdoublegR);
      instance.SetDestructor(&destruct_Column_speclEdoublegR);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Column_spec<double>*)
   {
      return GenerateInitInstanceLocal((::Column_spec<double>*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Column_spec<double>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Column_speclEdoublegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Column_spec<double>*)0x0)->GetClass();
      Column_speclEdoublegR_TClassManip(theClass);
   return theClass;
   }

   static void Column_speclEdoublegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *Column_speclEunsignedsPshortgR_Dictionary();
   static void Column_speclEunsignedsPshortgR_TClassManip(TClass*);
   static void *new_Column_speclEunsignedsPshortgR(void *p = 0);
   static void *newArray_Column_speclEunsignedsPshortgR(Long_t size, void *p);
   static void delete_Column_speclEunsignedsPshortgR(void *p);
   static void deleteArray_Column_speclEunsignedsPshortgR(void *p);
   static void destruct_Column_speclEunsignedsPshortgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Column_spec<unsigned short>*)
   {
      ::Column_spec<unsigned short> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Column_spec<unsigned short> >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Column_spec<unsigned short>", ::Column_spec<unsigned short>::Class_Version(), "interface/Table.h", 28,
                  typeid(::Column_spec<unsigned short>), DefineBehavior(ptr, ptr),
                  &Column_speclEunsignedsPshortgR_Dictionary, isa_proxy, 4,
                  sizeof(::Column_spec<unsigned short>) );
      instance.SetNew(&new_Column_speclEunsignedsPshortgR);
      instance.SetNewArray(&newArray_Column_speclEunsignedsPshortgR);
      instance.SetDelete(&delete_Column_speclEunsignedsPshortgR);
      instance.SetDeleteArray(&deleteArray_Column_speclEunsignedsPshortgR);
      instance.SetDestructor(&destruct_Column_speclEunsignedsPshortgR);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Column_spec<unsigned short>*)
   {
      return GenerateInitInstanceLocal((::Column_spec<unsigned short>*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Column_spec<unsigned short>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Column_speclEunsignedsPshortgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Column_spec<unsigned short>*)0x0)->GetClass();
      Column_speclEunsignedsPshortgR_TClassManip(theClass);
   return theClass;
   }

   static void Column_speclEunsignedsPshortgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *Column_speclEconstsPcharmUgR_Dictionary();
   static void Column_speclEconstsPcharmUgR_TClassManip(TClass*);
   static void *new_Column_speclEconstsPcharmUgR(void *p = 0);
   static void *newArray_Column_speclEconstsPcharmUgR(Long_t size, void *p);
   static void delete_Column_speclEconstsPcharmUgR(void *p);
   static void deleteArray_Column_speclEconstsPcharmUgR(void *p);
   static void destruct_Column_speclEconstsPcharmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Column_spec<const char*>*)
   {
      ::Column_spec<const char*> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Column_spec<const char*> >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Column_spec<const char*>", ::Column_spec<const char*>::Class_Version(), "interface/Table.h", 28,
                  typeid(::Column_spec<const char*>), DefineBehavior(ptr, ptr),
                  &Column_speclEconstsPcharmUgR_Dictionary, isa_proxy, 4,
                  sizeof(::Column_spec<const char*>) );
      instance.SetNew(&new_Column_speclEconstsPcharmUgR);
      instance.SetNewArray(&newArray_Column_speclEconstsPcharmUgR);
      instance.SetDelete(&delete_Column_speclEconstsPcharmUgR);
      instance.SetDeleteArray(&deleteArray_Column_speclEconstsPcharmUgR);
      instance.SetDestructor(&destruct_Column_speclEconstsPcharmUgR);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Column_spec<const char*>*)
   {
      return GenerateInitInstanceLocal((::Column_spec<const char*>*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Column_spec<const char*>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Column_speclEconstsPcharmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Column_spec<const char*>*)0x0)->GetClass();
      Column_speclEconstsPcharmUgR_TClassManip(theClass);
   return theClass;
   }

   static void Column_speclEconstsPcharmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *Column_speclETStringgR_Dictionary();
   static void Column_speclETStringgR_TClassManip(TClass*);
   static void *new_Column_speclETStringgR(void *p = 0);
   static void *newArray_Column_speclETStringgR(Long_t size, void *p);
   static void delete_Column_speclETStringgR(void *p);
   static void deleteArray_Column_speclETStringgR(void *p);
   static void destruct_Column_speclETStringgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Column_spec<TString>*)
   {
      ::Column_spec<TString> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Column_spec<TString> >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Column_spec<TString>", ::Column_spec<TString>::Class_Version(), "interface/Table.h", 28,
                  typeid(::Column_spec<TString>), DefineBehavior(ptr, ptr),
                  &Column_speclETStringgR_Dictionary, isa_proxy, 4,
                  sizeof(::Column_spec<TString>) );
      instance.SetNew(&new_Column_speclETStringgR);
      instance.SetNewArray(&newArray_Column_speclETStringgR);
      instance.SetDelete(&delete_Column_speclETStringgR);
      instance.SetDeleteArray(&deleteArray_Column_speclETStringgR);
      instance.SetDestructor(&destruct_Column_speclETStringgR);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Column_spec<TString>*)
   {
      return GenerateInitInstanceLocal((::Column_spec<TString>*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Column_spec<TString>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Column_speclETStringgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Column_spec<TString>*)0x0)->GetClass();
      Column_speclETStringgR_TClassManip(theClass);
   return theClass;
   }

   static void Column_speclETStringgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static void *new_Column(void *p = 0);
   static void *newArray_Column(Long_t size, void *p);
   static void delete_Column(void *p);
   static void deleteArray_Column(void *p);
   static void destruct_Column(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Column*)
   {
      ::Column *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Column >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Column", ::Column::Class_Version(), "interface/Table.h", 9,
                  typeid(::Column), DefineBehavior(ptr, ptr),
                  &::Column::Dictionary, isa_proxy, 4,
                  sizeof(::Column) );
      instance.SetNew(&new_Column);
      instance.SetNewArray(&newArray_Column);
      instance.SetDelete(&delete_Column);
      instance.SetDeleteArray(&deleteArray_Column);
      instance.SetDestructor(&destruct_Column);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Column*)
   {
      return GenerateInitInstanceLocal((::Column*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Column*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_Table(void *p = 0);
   static void *newArray_Table(Long_t size, void *p);
   static void delete_Table(void *p);
   static void deleteArray_Table(void *p);
   static void destruct_Table(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Table*)
   {
      ::Table *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Table >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Table", ::Table::Class_Version(), "interface/Table.h", 72,
                  typeid(::Table), DefineBehavior(ptr, ptr),
                  &::Table::Dictionary, isa_proxy, 4,
                  sizeof(::Table) );
      instance.SetNew(&new_Table);
      instance.SetNewArray(&newArray_Table);
      instance.SetDelete(&delete_Table);
      instance.SetDeleteArray(&deleteArray_Table);
      instance.SetDestructor(&destruct_Table);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Table*)
   {
      return GenerateInitInstanceLocal((::Table*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Table*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
template <> atomic_TClass_ptr Column_spec<float>::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
template <> const char *Column_spec<float>::Class_Name()
{
   return "Column_spec<float>";
}

//______________________________________________________________________________
template <> const char *Column_spec<float>::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Column_spec<float>*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
template <> int Column_spec<float>::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Column_spec<float>*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
template <> TClass *Column_spec<float>::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Column_spec<float>*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
template <> TClass *Column_spec<float>::Class()
{
   if (!fgIsA) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Column_spec<float>*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
template <> atomic_TClass_ptr Column_spec<short>::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
template <> const char *Column_spec<short>::Class_Name()
{
   return "Column_spec<short>";
}

//______________________________________________________________________________
template <> const char *Column_spec<short>::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Column_spec<short>*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
template <> int Column_spec<short>::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Column_spec<short>*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
template <> TClass *Column_spec<short>::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Column_spec<short>*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
template <> TClass *Column_spec<short>::Class()
{
   if (!fgIsA) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Column_spec<short>*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
template <> atomic_TClass_ptr Column_spec<double>::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
template <> const char *Column_spec<double>::Class_Name()
{
   return "Column_spec<double>";
}

//______________________________________________________________________________
template <> const char *Column_spec<double>::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Column_spec<double>*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
template <> int Column_spec<double>::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Column_spec<double>*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
template <> TClass *Column_spec<double>::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Column_spec<double>*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
template <> TClass *Column_spec<double>::Class()
{
   if (!fgIsA) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Column_spec<double>*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
template <> atomic_TClass_ptr Column_spec<unsigned short>::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
template <> const char *Column_spec<unsigned short>::Class_Name()
{
   return "Column_spec<unsigned short>";
}

//______________________________________________________________________________
template <> const char *Column_spec<unsigned short>::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Column_spec<unsigned short>*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
template <> int Column_spec<unsigned short>::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Column_spec<unsigned short>*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
template <> TClass *Column_spec<unsigned short>::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Column_spec<unsigned short>*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
template <> TClass *Column_spec<unsigned short>::Class()
{
   if (!fgIsA) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Column_spec<unsigned short>*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
template <> atomic_TClass_ptr Column_spec<const char*>::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
template <> const char *Column_spec<const char*>::Class_Name()
{
   return "Column_spec<const char*>";
}

//______________________________________________________________________________
template <> const char *Column_spec<const char*>::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Column_spec<const char*>*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
template <> int Column_spec<const char*>::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Column_spec<const char*>*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
template <> TClass *Column_spec<const char*>::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Column_spec<const char*>*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
template <> TClass *Column_spec<const char*>::Class()
{
   if (!fgIsA) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Column_spec<const char*>*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
template <> atomic_TClass_ptr Column_spec<TString>::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
template <> const char *Column_spec<TString>::Class_Name()
{
   return "Column_spec<TString>";
}

//______________________________________________________________________________
template <> const char *Column_spec<TString>::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Column_spec<TString>*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
template <> int Column_spec<TString>::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Column_spec<TString>*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
template <> TClass *Column_spec<TString>::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Column_spec<TString>*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
template <> TClass *Column_spec<TString>::Class()
{
   if (!fgIsA) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Column_spec<TString>*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Column::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Column::Class_Name()
{
   return "Column";
}

//______________________________________________________________________________
const char *Column::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Column*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Column::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Column*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Column::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Column*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Column::Class()
{
   if (!fgIsA) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Column*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Table::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Table::Class_Name()
{
   return "Table";
}

//______________________________________________________________________________
const char *Table::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Table*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Table::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Table*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Table::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Table*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Table::Class()
{
   if (!fgIsA) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Table*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
template <> void Column_spec<float>::Streamer(TBuffer &R__b)
{
   // Stream an object of class Column_spec<float>.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Column_spec<float>::Class(),this);
   } else {
      R__b.WriteClassBuffer(Column_spec<float>::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Column_speclEfloatgR(void *p) {
      return  p ? new(p) ::Column_spec<float> : new ::Column_spec<float>;
   }
   static void *newArray_Column_speclEfloatgR(Long_t nElements, void *p) {
      return p ? new(p) ::Column_spec<float>[nElements] : new ::Column_spec<float>[nElements];
   }
   // Wrapper around operator delete
   static void delete_Column_speclEfloatgR(void *p) {
      delete ((::Column_spec<float>*)p);
   }
   static void deleteArray_Column_speclEfloatgR(void *p) {
      delete [] ((::Column_spec<float>*)p);
   }
   static void destruct_Column_speclEfloatgR(void *p) {
      typedef ::Column_spec<float> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Column_spec<float>

//______________________________________________________________________________
template <> void Column_spec<short>::Streamer(TBuffer &R__b)
{
   // Stream an object of class Column_spec<short>.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Column_spec<short>::Class(),this);
   } else {
      R__b.WriteClassBuffer(Column_spec<short>::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Column_speclEshortgR(void *p) {
      return  p ? new(p) ::Column_spec<short> : new ::Column_spec<short>;
   }
   static void *newArray_Column_speclEshortgR(Long_t nElements, void *p) {
      return p ? new(p) ::Column_spec<short>[nElements] : new ::Column_spec<short>[nElements];
   }
   // Wrapper around operator delete
   static void delete_Column_speclEshortgR(void *p) {
      delete ((::Column_spec<short>*)p);
   }
   static void deleteArray_Column_speclEshortgR(void *p) {
      delete [] ((::Column_spec<short>*)p);
   }
   static void destruct_Column_speclEshortgR(void *p) {
      typedef ::Column_spec<short> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Column_spec<short>

//______________________________________________________________________________
template <> void Column_spec<double>::Streamer(TBuffer &R__b)
{
   // Stream an object of class Column_spec<double>.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Column_spec<double>::Class(),this);
   } else {
      R__b.WriteClassBuffer(Column_spec<double>::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Column_speclEdoublegR(void *p) {
      return  p ? new(p) ::Column_spec<double> : new ::Column_spec<double>;
   }
   static void *newArray_Column_speclEdoublegR(Long_t nElements, void *p) {
      return p ? new(p) ::Column_spec<double>[nElements] : new ::Column_spec<double>[nElements];
   }
   // Wrapper around operator delete
   static void delete_Column_speclEdoublegR(void *p) {
      delete ((::Column_spec<double>*)p);
   }
   static void deleteArray_Column_speclEdoublegR(void *p) {
      delete [] ((::Column_spec<double>*)p);
   }
   static void destruct_Column_speclEdoublegR(void *p) {
      typedef ::Column_spec<double> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Column_spec<double>

//______________________________________________________________________________
template <> void Column_spec<unsigned short>::Streamer(TBuffer &R__b)
{
   // Stream an object of class Column_spec<unsigned short>.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Column_spec<unsigned short>::Class(),this);
   } else {
      R__b.WriteClassBuffer(Column_spec<unsigned short>::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Column_speclEunsignedsPshortgR(void *p) {
      return  p ? new(p) ::Column_spec<unsigned short> : new ::Column_spec<unsigned short>;
   }
   static void *newArray_Column_speclEunsignedsPshortgR(Long_t nElements, void *p) {
      return p ? new(p) ::Column_spec<unsigned short>[nElements] : new ::Column_spec<unsigned short>[nElements];
   }
   // Wrapper around operator delete
   static void delete_Column_speclEunsignedsPshortgR(void *p) {
      delete ((::Column_spec<unsigned short>*)p);
   }
   static void deleteArray_Column_speclEunsignedsPshortgR(void *p) {
      delete [] ((::Column_spec<unsigned short>*)p);
   }
   static void destruct_Column_speclEunsignedsPshortgR(void *p) {
      typedef ::Column_spec<unsigned short> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Column_spec<unsigned short>

//______________________________________________________________________________
template <> void Column_spec<const char*>::Streamer(TBuffer &R__b)
{
   // Stream an object of class Column_spec<const char*>.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Column_spec<const char*>::Class(),this);
   } else {
      R__b.WriteClassBuffer(Column_spec<const char*>::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Column_speclEconstsPcharmUgR(void *p) {
      return  p ? new(p) ::Column_spec<const char*> : new ::Column_spec<const char*>;
   }
   static void *newArray_Column_speclEconstsPcharmUgR(Long_t nElements, void *p) {
      return p ? new(p) ::Column_spec<const char*>[nElements] : new ::Column_spec<const char*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_Column_speclEconstsPcharmUgR(void *p) {
      delete ((::Column_spec<const char*>*)p);
   }
   static void deleteArray_Column_speclEconstsPcharmUgR(void *p) {
      delete [] ((::Column_spec<const char*>*)p);
   }
   static void destruct_Column_speclEconstsPcharmUgR(void *p) {
      typedef ::Column_spec<const char*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Column_spec<const char*>

//______________________________________________________________________________
template <> void Column_spec<TString>::Streamer(TBuffer &R__b)
{
   // Stream an object of class Column_spec<TString>.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Column_spec<TString>::Class(),this);
   } else {
      R__b.WriteClassBuffer(Column_spec<TString>::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Column_speclETStringgR(void *p) {
      return  p ? new(p) ::Column_spec<TString> : new ::Column_spec<TString>;
   }
   static void *newArray_Column_speclETStringgR(Long_t nElements, void *p) {
      return p ? new(p) ::Column_spec<TString>[nElements] : new ::Column_spec<TString>[nElements];
   }
   // Wrapper around operator delete
   static void delete_Column_speclETStringgR(void *p) {
      delete ((::Column_spec<TString>*)p);
   }
   static void deleteArray_Column_speclETStringgR(void *p) {
      delete [] ((::Column_spec<TString>*)p);
   }
   static void destruct_Column_speclETStringgR(void *p) {
      typedef ::Column_spec<TString> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Column_spec<TString>

//______________________________________________________________________________
void Column::Streamer(TBuffer &R__b)
{
   // Stream an object of class Column.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Column::Class(),this);
   } else {
      R__b.WriteClassBuffer(Column::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Column(void *p) {
      return  p ? new(p) ::Column : new ::Column;
   }
   static void *newArray_Column(Long_t nElements, void *p) {
      return p ? new(p) ::Column[nElements] : new ::Column[nElements];
   }
   // Wrapper around operator delete
   static void delete_Column(void *p) {
      delete ((::Column*)p);
   }
   static void deleteArray_Column(void *p) {
      delete [] ((::Column*)p);
   }
   static void destruct_Column(void *p) {
      typedef ::Column current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Column

//______________________________________________________________________________
void Table::Streamer(TBuffer &R__b)
{
   // Stream an object of class Table.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Table::Class(),this);
   } else {
      R__b.WriteClassBuffer(Table::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Table(void *p) {
      return  p ? new(p) ::Table : new ::Table;
   }
   static void *newArray_Table(Long_t nElements, void *p) {
      return p ? new(p) ::Table[nElements] : new ::Table[nElements];
   }
   // Wrapper around operator delete
   static void delete_Table(void *p) {
      delete ((::Table*)p);
   }
   static void deleteArray_Table(void *p) {
      delete [] ((::Table*)p);
   }
   static void destruct_Table(void *p) {
      typedef ::Table current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Table

namespace ROOT {
   static TClass *vectorlEunsignedsPshortgR_Dictionary();
   static void vectorlEunsignedsPshortgR_TClassManip(TClass*);
   static void *new_vectorlEunsignedsPshortgR(void *p = 0);
   static void *newArray_vectorlEunsignedsPshortgR(Long_t size, void *p);
   static void delete_vectorlEunsignedsPshortgR(void *p);
   static void deleteArray_vectorlEunsignedsPshortgR(void *p);
   static void destruct_vectorlEunsignedsPshortgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<unsigned short>*)
   {
      vector<unsigned short> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<unsigned short>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<unsigned short>", -2, "vector", 214,
                  typeid(vector<unsigned short>), DefineBehavior(ptr, ptr),
                  &vectorlEunsignedsPshortgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<unsigned short>) );
      instance.SetNew(&new_vectorlEunsignedsPshortgR);
      instance.SetNewArray(&newArray_vectorlEunsignedsPshortgR);
      instance.SetDelete(&delete_vectorlEunsignedsPshortgR);
      instance.SetDeleteArray(&deleteArray_vectorlEunsignedsPshortgR);
      instance.SetDestructor(&destruct_vectorlEunsignedsPshortgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<unsigned short> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<unsigned short>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEunsignedsPshortgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<unsigned short>*)0x0)->GetClass();
      vectorlEunsignedsPshortgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEunsignedsPshortgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEunsignedsPshortgR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<unsigned short> : new vector<unsigned short>;
   }
   static void *newArray_vectorlEunsignedsPshortgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<unsigned short>[nElements] : new vector<unsigned short>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEunsignedsPshortgR(void *p) {
      delete ((vector<unsigned short>*)p);
   }
   static void deleteArray_vectorlEunsignedsPshortgR(void *p) {
      delete [] ((vector<unsigned short>*)p);
   }
   static void destruct_vectorlEunsignedsPshortgR(void *p) {
      typedef vector<unsigned short> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<unsigned short>

namespace ROOT {
   static TClass *vectorlEshortgR_Dictionary();
   static void vectorlEshortgR_TClassManip(TClass*);
   static void *new_vectorlEshortgR(void *p = 0);
   static void *newArray_vectorlEshortgR(Long_t size, void *p);
   static void delete_vectorlEshortgR(void *p);
   static void deleteArray_vectorlEshortgR(void *p);
   static void destruct_vectorlEshortgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<short>*)
   {
      vector<short> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<short>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<short>", -2, "vector", 214,
                  typeid(vector<short>), DefineBehavior(ptr, ptr),
                  &vectorlEshortgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<short>) );
      instance.SetNew(&new_vectorlEshortgR);
      instance.SetNewArray(&newArray_vectorlEshortgR);
      instance.SetDelete(&delete_vectorlEshortgR);
      instance.SetDeleteArray(&deleteArray_vectorlEshortgR);
      instance.SetDestructor(&destruct_vectorlEshortgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<short> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<short>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEshortgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<short>*)0x0)->GetClass();
      vectorlEshortgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEshortgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEshortgR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<short> : new vector<short>;
   }
   static void *newArray_vectorlEshortgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<short>[nElements] : new vector<short>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEshortgR(void *p) {
      delete ((vector<short>*)p);
   }
   static void deleteArray_vectorlEshortgR(void *p) {
      delete [] ((vector<short>*)p);
   }
   static void destruct_vectorlEshortgR(void *p) {
      typedef vector<short> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<short>

namespace ROOT {
   static TClass *vectorlEfloatgR_Dictionary();
   static void vectorlEfloatgR_TClassManip(TClass*);
   static void *new_vectorlEfloatgR(void *p = 0);
   static void *newArray_vectorlEfloatgR(Long_t size, void *p);
   static void delete_vectorlEfloatgR(void *p);
   static void deleteArray_vectorlEfloatgR(void *p);
   static void destruct_vectorlEfloatgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<float>*)
   {
      vector<float> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<float>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<float>", -2, "vector", 214,
                  typeid(vector<float>), DefineBehavior(ptr, ptr),
                  &vectorlEfloatgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<float>) );
      instance.SetNew(&new_vectorlEfloatgR);
      instance.SetNewArray(&newArray_vectorlEfloatgR);
      instance.SetDelete(&delete_vectorlEfloatgR);
      instance.SetDeleteArray(&deleteArray_vectorlEfloatgR);
      instance.SetDestructor(&destruct_vectorlEfloatgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<float> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<float>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEfloatgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<float>*)0x0)->GetClass();
      vectorlEfloatgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEfloatgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEfloatgR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<float> : new vector<float>;
   }
   static void *newArray_vectorlEfloatgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<float>[nElements] : new vector<float>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEfloatgR(void *p) {
      delete ((vector<float>*)p);
   }
   static void deleteArray_vectorlEfloatgR(void *p) {
      delete [] ((vector<float>*)p);
   }
   static void destruct_vectorlEfloatgR(void *p) {
      typedef vector<float> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<float>

namespace ROOT {
   static TClass *vectorlEdoublegR_Dictionary();
   static void vectorlEdoublegR_TClassManip(TClass*);
   static void *new_vectorlEdoublegR(void *p = 0);
   static void *newArray_vectorlEdoublegR(Long_t size, void *p);
   static void delete_vectorlEdoublegR(void *p);
   static void deleteArray_vectorlEdoublegR(void *p);
   static void destruct_vectorlEdoublegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<double>*)
   {
      vector<double> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<double>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<double>", -2, "vector", 214,
                  typeid(vector<double>), DefineBehavior(ptr, ptr),
                  &vectorlEdoublegR_Dictionary, isa_proxy, 0,
                  sizeof(vector<double>) );
      instance.SetNew(&new_vectorlEdoublegR);
      instance.SetNewArray(&newArray_vectorlEdoublegR);
      instance.SetDelete(&delete_vectorlEdoublegR);
      instance.SetDeleteArray(&deleteArray_vectorlEdoublegR);
      instance.SetDestructor(&destruct_vectorlEdoublegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<double> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<double>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEdoublegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<double>*)0x0)->GetClass();
      vectorlEdoublegR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEdoublegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEdoublegR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<double> : new vector<double>;
   }
   static void *newArray_vectorlEdoublegR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<double>[nElements] : new vector<double>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEdoublegR(void *p) {
      delete ((vector<double>*)p);
   }
   static void deleteArray_vectorlEdoublegR(void *p) {
      delete [] ((vector<double>*)p);
   }
   static void destruct_vectorlEdoublegR(void *p) {
      typedef vector<double> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<double>

namespace ROOT {
   static TClass *vectorlEconstsPcharmUgR_Dictionary();
   static void vectorlEconstsPcharmUgR_TClassManip(TClass*);
   static void *new_vectorlEconstsPcharmUgR(void *p = 0);
   static void *newArray_vectorlEconstsPcharmUgR(Long_t size, void *p);
   static void delete_vectorlEconstsPcharmUgR(void *p);
   static void deleteArray_vectorlEconstsPcharmUgR(void *p);
   static void destruct_vectorlEconstsPcharmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<const char*>*)
   {
      vector<const char*> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<const char*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<const char*>", -2, "vector", 214,
                  typeid(vector<const char*>), DefineBehavior(ptr, ptr),
                  &vectorlEconstsPcharmUgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<const char*>) );
      instance.SetNew(&new_vectorlEconstsPcharmUgR);
      instance.SetNewArray(&newArray_vectorlEconstsPcharmUgR);
      instance.SetDelete(&delete_vectorlEconstsPcharmUgR);
      instance.SetDeleteArray(&deleteArray_vectorlEconstsPcharmUgR);
      instance.SetDestructor(&destruct_vectorlEconstsPcharmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<const char*> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<const char*>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEconstsPcharmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<const char*>*)0x0)->GetClass();
      vectorlEconstsPcharmUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEconstsPcharmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEconstsPcharmUgR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<const char*> : new vector<const char*>;
   }
   static void *newArray_vectorlEconstsPcharmUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<const char*>[nElements] : new vector<const char*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEconstsPcharmUgR(void *p) {
      delete ((vector<const char*>*)p);
   }
   static void deleteArray_vectorlEconstsPcharmUgR(void *p) {
      delete [] ((vector<const char*>*)p);
   }
   static void destruct_vectorlEconstsPcharmUgR(void *p) {
      typedef vector<const char*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<const char*>

namespace ROOT {
   static TClass *vectorlETStringgR_Dictionary();
   static void vectorlETStringgR_TClassManip(TClass*);
   static void *new_vectorlETStringgR(void *p = 0);
   static void *newArray_vectorlETStringgR(Long_t size, void *p);
   static void delete_vectorlETStringgR(void *p);
   static void deleteArray_vectorlETStringgR(void *p);
   static void destruct_vectorlETStringgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<TString>*)
   {
      vector<TString> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<TString>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<TString>", -2, "vector", 214,
                  typeid(vector<TString>), DefineBehavior(ptr, ptr),
                  &vectorlETStringgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<TString>) );
      instance.SetNew(&new_vectorlETStringgR);
      instance.SetNewArray(&newArray_vectorlETStringgR);
      instance.SetDelete(&delete_vectorlETStringgR);
      instance.SetDeleteArray(&deleteArray_vectorlETStringgR);
      instance.SetDestructor(&destruct_vectorlETStringgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<TString> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<TString>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlETStringgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<TString>*)0x0)->GetClass();
      vectorlETStringgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlETStringgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlETStringgR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<TString> : new vector<TString>;
   }
   static void *newArray_vectorlETStringgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<TString>[nElements] : new vector<TString>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlETStringgR(void *p) {
      delete ((vector<TString>*)p);
   }
   static void deleteArray_vectorlETStringgR(void *p) {
      delete [] ((vector<TString>*)p);
   }
   static void destruct_vectorlETStringgR(void *p) {
      typedef vector<TString> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<TString>

namespace ROOT {
   static TClass *vectorlEColumnmUgR_Dictionary();
   static void vectorlEColumnmUgR_TClassManip(TClass*);
   static void *new_vectorlEColumnmUgR(void *p = 0);
   static void *newArray_vectorlEColumnmUgR(Long_t size, void *p);
   static void delete_vectorlEColumnmUgR(void *p);
   static void deleteArray_vectorlEColumnmUgR(void *p);
   static void destruct_vectorlEColumnmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<Column*>*)
   {
      vector<Column*> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<Column*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<Column*>", -2, "vector", 214,
                  typeid(vector<Column*>), DefineBehavior(ptr, ptr),
                  &vectorlEColumnmUgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<Column*>) );
      instance.SetNew(&new_vectorlEColumnmUgR);
      instance.SetNewArray(&newArray_vectorlEColumnmUgR);
      instance.SetDelete(&delete_vectorlEColumnmUgR);
      instance.SetDeleteArray(&deleteArray_vectorlEColumnmUgR);
      instance.SetDestructor(&destruct_vectorlEColumnmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<Column*> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<Column*>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEColumnmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<Column*>*)0x0)->GetClass();
      vectorlEColumnmUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEColumnmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEColumnmUgR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<Column*> : new vector<Column*>;
   }
   static void *newArray_vectorlEColumnmUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<Column*>[nElements] : new vector<Column*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEColumnmUgR(void *p) {
      delete ((vector<Column*>*)p);
   }
   static void deleteArray_vectorlEColumnmUgR(void *p) {
      delete [] ((vector<Column*>*)p);
   }
   static void destruct_vectorlEColumnmUgR(void *p) {
      typedef vector<Column*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<Column*>

namespace {
  void TriggerDictionaryInitialization_Table_Impl() {
    static const char* headers[] = {
"interface/Table.h",
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
template <typename T> class __attribute__((annotate("$clingAutoload$interface/Table.h")))  Column_spec;

class __attribute__((annotate("$clingAutoload$interface/Table.h")))  TString;
class __attribute__((annotate("$clingAutoload$interface/Table.h")))  Column;
class __attribute__((annotate("$clingAutoload$interface/Table.h")))  Table;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "interface/Table.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"Column", payloadCode, "@",
"Column_spec<TString>", payloadCode, "@",
"Column_spec<const char*>", payloadCode, "@",
"Column_spec<double>", payloadCode, "@",
"Column_spec<float>", payloadCode, "@",
"Column_spec<short>", payloadCode, "@",
"Column_spec<unsigned short>", payloadCode, "@",
"Table", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("Table",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_Table_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_Table_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_Table() {
  TriggerDictionaryInitialization_Table_Impl();
}
