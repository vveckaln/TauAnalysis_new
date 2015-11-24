#include <boost/shared_ptr.hpp>

#include "FWCore/FWLite/interface/AutoLibraryLoader.h"
#include "FWCore/PythonParameterSet/interface/MakeParameterSets.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "CERN_RTU/TauAnalysis/interface/gConfiguration.hh"
class A
{
public:
  ~A()
  {
    printf("Destructing A\n");
  }
  
};
class B
{
public:
  A A_obj;
};

#include <iostream>
#include <vector>
using namespace std;

// Consider an actual class.
class Obj {
  //static int i, j;
public:
  float sceta;
  // void f() const { cout << i++ << endl; }
  // void g() const { cout << j++ << endl; }
};

// Static member definitions:
//int Obj::i = 10;
//int Obj::j = 12;

// Implement a container for the above class
typedef vector<Obj*> ObjCollection;
/*class ObjContainer {
   vector<Obj*> a;
public:
   void add(Obj* obj)
   { 
      a.push_back(obj);  // call vector's standard method.
   }
   friend class SmartPointer;
   };*/

// implement smart pointer to access member of Obj class.
class SmartPointer {
   ObjCollection oc;
   int index;
public:
   SmartPointer(ObjCollection& objc)
   { 
       oc = objc;
       index = 0;
   }
   // Return value indicates end of list:
   /*bool operator++() // Prefix version
   { 
     if((unsigned int)index >= oc.a.size()) return false;
     if(oc.a[++index] == 0) return false;
     return true;
     }*/
   /*bool operator++(int) // Postfix version
   { 
      return operator++();
      }*/
   // overload operator->
   Obj* operator->() const 
   {
     /*if(!oc.a[index])
     {
        cout << "Zero value";
        return (Obj*)0;
	}*/
     return oc[index];
   }
};

int main() {
  //const int sz = 10;
   Obj o;
   o. sceta = 5.3;
   ObjCollection oc;
   oc.push_back(&o);
   
   SmartPointer sp(oc); // Create an iterator
   printf("%f\n", sp->  sceta);
   Obj * t = sp.operator -> ();
   printf("%f\n", t -> sceta);
   return 0;
}
