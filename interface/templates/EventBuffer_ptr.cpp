#include <stdlib.h>


template<class TEvent>
EventCapsule<TEvent*>::EventCapsule()
{
  event = NULL;
  next = NULL;
  previous = NULL;
}


template <class TEvent>
void EventBuffer<TEvent*>::DeepCopy(const EventBuffer<TEvent*>* const other_buffer)
{
  /*IsIndependent = true;
  new (this) EventBuffer<TEvent*>(other_buffer -> GetCapacity());
  
  for (uint ind = 0; ind < other_buffer -> size(); ind ++){
    buffer[ind] = new TEvent(); 
    other_buffer -> operator[](ind) -> ls("all");
    *buffer[ind] = *other_buffer -> operator[](ind); 
    buffer[ind] -> ls("all");
    printf("-----------\n");
    getchar();
    } */      
}

template <class TEvent>
EventBuffer<TEvent*>::EventBuffer(const EventBuffer<TEvent*>* const other_buffer)
{
  /*IsIndependent = true;
  consumed = other_buffer -> size();
  capacity = other_buffer -> GetCapacity();
  typedef TEvent * tp;
  //buffer = (TEvent**) malloc(sizeof(TEvent)*capacity);
  buffer = new tp[capacity];
  for (uint ind = 0; ind < other_buffer -> GetCapacity(); ind ++)
    {
      buffer[ind] = new TEvent(); 
    }
  for (uint ind = 0; ind < other_buffer -> size(); ind ++)
    {
      *buffer[ind] = *other_buffer -> operator[](ind); 
      }   */   
}

template <class TEvent>
EventCapsule<TEvent*> * EventBuffer<TEvent*>::END_OUTOFBOUNDS = new EventCapsule<TEvent*>();

template<class TEvent>
typename EventBuffer<TEvent*>::iterator EventBuffer<TEvent*>::begin()
{
  iterator tmp = beginning;
  return tmp;
}
template<class TEvent>
typename EventBuffer<TEvent*>::iterator EventBuffer<TEvent*>::end()
{
  iterator tmp = theend;
  return tmp;
}
template<class TEvent>
typename EventBuffer<TEvent*>::iterator EventBuffer<TEvent*>::erase(iterator & it)
{
  iterator tmp;
  tmp = it.next();
  if (not it .next())
    theend = it .previous();
  if (not it .previous())
    beginning = it . next();

  if(it .previous())
    {
      it.previous() -> next = it.next();
    }
  if(it .next())
    it. next ()-> previous = it .previous();
  it = tmp;
  return tmp;
}

template <class TEvent>
TEvent *& EventBuffer<TEvent*>::GetWriteSlot() const
{
 
  return buffer[consumed].event;
}

template <class TEvent>
void EventBuffer<TEvent*>::PushWriteSlot()
{
  if(consumed > 0)
    buffer[consumed].previous = &buffer[consumed - 1];
  else
    buffer[consumed].previous = NULL;
  if (consumed < capacity -1)
    theend = &buffer[consumed];
  if (consumed == capacity - 1)
    {
      theend = END_OUTOFBOUNDS;
      buffer[consumed].next = END_OUTOFBOUNDS;
    }
  if (consumed > 0)
    buffer[consumed -1 ].next = &buffer[consumed];
  consumed ++;
}

template <class TEvent>
bool EventBuffer<TEvent*>::IsEmpty() const
{
  return consumed == 0;
}

template <class TEvent>
bool EventBuffer<TEvent*>::IsFull() const
{
  return consumed >= capacity;
}

template <class TEvent>
unsigned long EventBuffer<TEvent*>::size() const
{
  return consumed;
}

template <class TEvent>
unsigned long EventBuffer<TEvent*>::GetCapacity() const
{
  return capacity;
}

template <class TEvent>
TEvent *& EventBuffer<TEvent*>::operator[] (const unsigned long index) const
{
       return buffer[index].event;
}

template <class TEvent>
EventBuffer<TEvent*>::EventBuffer(const unsigned long capacity, const char * option): capacity(capacity)
{
  //buffer = (TEvent**) malloc(sizeof(TEvent)*capacity);
  printf("capacity %lu\n", capacity);
  buffer = new EventCapsule<TEvent*>[capacity];
  IsIndependent = true;// (TString(option) == "independent");
  if (IsIndependent)
    {
      TEvent * events = new TEvent[capacity];
      printf("created events at %p\n", events);
      for (uint ind = 0; ind < capacity; ind ++)
	{
	  buffer[ind].event    = events + ind;
	  
	}
    }
  beginning = buffer;
  theend = buffer;
  consumed = 0;
  //printf("constructed pointer buffer\n");
} 


template <class TEvent>
EventBuffer<TEvent*>::~EventBuffer()
{
  //printf("%s\n", IsIndependent ? "true": "false");	
  if (IsIndependent) 
    {
      for (ushort ind = 0; ind < consumed; ind ++)
	{
	  operator[](ind) -> Close();
	  
	}
      printf("deleting events %p\n", buffer[0].event);
      delete [] buffer[0].event;
    }
  //free((TEvent**)buffer);
  printf("deleteing buffer %p\n", buffer);
  delete [] buffer;
  printf("deleted buffer\n");
 //printf("destructed pointer buffer\n");
 }


