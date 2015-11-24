#ifndef _EventBuffer_hh
#define _EventBuffer_hh
#include "stdlib.h"
#include "TString.h"
template <class TEvent>
struct EventCapsule
{
  TEvent                 event;
  EventCapsule<TEvent> * previous;
  EventCapsule<TEvent> * next;
};

template <class TEvent>
class EventBuffer 
{
  EventCapsule<TEvent>        * buffer;
  unsigned long                 consumed;
  unsigned long                 capacity;
public:
  class iterator
  {
    EventCapsule<TEvent> *to;

  public:
    iterator operator ++(); 
  };
  EventCapsule<TEvent> * beginning;
  EventCapsule<TEvent> * theend;
  iterator begin();
  iterator end();
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
struct EventCapsule<TEvent*>
{
  TEvent                * event    ;
  EventCapsule<TEvent*> * previous ;
  EventCapsule<TEvent*> * next     ;
  EventCapsule<TEvent*>();
};


template <class TEvent>
class EventBuffer<TEvent *> 
{
  EventCapsule<TEvent*>    * buffer;
  unsigned long              consumed;
  unsigned long              capacity;
  bool                       IsIndependent;
public:
  class iterator
  {
    friend class EventBuffer<TEvent*>;
    EventCapsule<TEvent*> *to ;
  public:
    EventCapsule<TEvent*> *&next();
    EventCapsule<TEvent*> *&previous();
  public:
    
    iterator  operator ++(); 
    iterator  operator ++(int); 

    TEvent   *operator -> ();
    bool      operator != (const iterator &);
    bool      operator == (const iterator &);
    iterator();
    iterator(EventCapsule<TEvent*>  *other);
    iterator &operator =  (EventCapsule<TEvent*>  *);
    TEvent  & operator * ();
  };
  EventCapsule<TEvent*> * beginning;
  EventCapsule<TEvent*> * theend;
  static EventCapsule<TEvent*> * END_OUTOFBOUNDS;
  iterator begin();
  iterator end();
  iterator erase(iterator & it);
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
#include "TauAnalysis/interface/templates/EventBuffer.cpp"
#include "TauAnalysis/interface/templates/EventBuffer_ptr.cpp"

#include "TauAnalysis/interface/templates/EventBuffer_iterator.cpp"

#endif
