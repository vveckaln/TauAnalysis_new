#ifndef _EventBuffer_hh
#define _EventBuffer_hh
#include "stdlib.h"
#include "TString.h"
template <class TEvent>
class EventBuffer 
{
  TEvent        * buffer;
  unsigned long   consumed;
  unsigned long   capacity;
public:
  EventBuffer(const unsigned long capacity);
  TEvent &GetWriteSlot() const; 
  void PushWriteSlot();
  bool IsFull() const;
  bool IsEmpty() const;
  unsigned long size() const;
  unsigned long GetCapacity() const;
  ~EventBuffer();
  TEvent & operator[] (const unsigned long index) const;

};

template <class TEvent>
class EventBuffer<TEvent *> 
{
  TEvent        **buffer;
  unsigned long   consumed;
  unsigned long   capacity;
  bool IsIndependent;
public:
  EventBuffer(const unsigned long capacity, const char* = "");
  EventBuffer(const EventBuffer<TEvent*>* const other_buffer);
  void DeepCopy(const EventBuffer<TEvent*>* const);
  TEvent *& GetWriteSlot() const; 
  void PushWriteSlot();
  bool IsFull() const;
  bool IsEmpty() const;
  unsigned long size() const;
  unsigned long GetCapacity() const;
  ~EventBuffer();
  TEvent *& operator[] (const unsigned long index) const;

};
#include "LIP/TauAnalysis/interface/templates/EventBuffer.cpp"
#endif
