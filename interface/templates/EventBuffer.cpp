#include <stdlib.h>
template <class TEvent>
EventBuffer<TEvent>::EventBuffer(const unsigned long capacity): capacity(capacity)
{
  //buffer = (TEvent*) malloc(sizeof(TEvent)*capacity);
  //buffer = static_cast<TEvent*> (::operator new(sizeof(TEvent[capacity])));
  /*for (unsigned int ind = 0; ind < capacity; ind ++){
      new (buffer + ind) TEvent();
      *(buffer + ind) = TEvent();
  }*/
  
  buffer = new TEvent[capacity];
  consumed = 0;
} 

template <class TEvent>
TEvent & EventBuffer<TEvent>::GetWriteSlot() const
{
  return buffer[consumed];
}

template <class TEvent>
void EventBuffer<TEvent>::PushWriteSlot()
{
  consumed ++;
}

template <class TEvent>
bool EventBuffer<TEvent>::IsFull() const
{
  return consumed >= capacity;
}

template <class TEvent>
bool EventBuffer<TEvent*>::IsFull() const
{
  return consumed >= capacity;
}

template <class TEvent>
bool EventBuffer<TEvent>::IsEmpty() const
{
  return consumed == 0;
}

template <class TEvent>
unsigned long EventBuffer<TEvent>::size() const
{
  return consumed;
}


template <class TEvent>
unsigned long EventBuffer<TEvent>::GetCapacity() const
{
  return capacity;
}

template <class TEvent>
TEvent & EventBuffer<TEvent>::operator[] (const unsigned long index) const
{
  return buffer[index];
}



template <class TEvent>
EventBuffer<TEvent>::~EventBuffer()
{
  for (unsigned ind = 0; ind < this -> size(); ind ++)
    {
      buffer[ind] . Close();
    }	
  //free((TEvent*)buffer);
  delete [] buffer;
}

template <class TEvent>
EventBuffer<TEvent*>::EventBuffer(const unsigned long capacity, const char * option): capacity(capacity)
{
  //buffer = (TEvent**) malloc(sizeof(TEvent)*capacity);
  buffer = new TEvent*[capacity];
  IsIndependent = (TString(option) == "independent");
  for (uint ind = 0; ind < capacity; ind ++)
    {
      buffer[ind] = (IsIndependent) ? new TEvent() : NULL;
    }
  consumed = 0;
  //printf("constructed pointer buffer\n");
} 

template <class TEvent>
void EventBuffer<TEvent*>::DeepCopy(const EventBuffer<TEvent*>* const other_buffer)
{
  IsIndependent = true;
  new (this) EventBuffer<TEvent*>(other_buffer -> GetCapacity());
  
  for (uint ind = 0; ind < other_buffer -> size(); ind ++){
    buffer[ind] = new TEvent(); 
    other_buffer -> operator[](ind) -> ls("all");
    *buffer[ind] = *other_buffer -> operator[](ind); 
    buffer[ind] -> ls("all");
    printf("-----------\n");
    getchar();
  }       
}

template <class TEvent>
EventBuffer<TEvent*>::EventBuffer(const EventBuffer<TEvent*>* const other_buffer)
{
  IsIndependent = true;
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
    }      
}

template <class TEvent>
TEvent *& EventBuffer<TEvent*>::GetWriteSlot() const{
  return buffer[consumed];
}

template <class TEvent>
void EventBuffer<TEvent*>::PushWriteSlot(){
  consumed ++;
}

template <class TEvent>
bool EventBuffer<TEvent*>::IsEmpty() const{
  return consumed == 0;
}

template <class TEvent>
unsigned long EventBuffer<TEvent*>::size() const{
  return consumed;
}

template <class TEvent>
unsigned long EventBuffer<TEvent*>::GetCapacity() const{
  return capacity;
}

template <class TEvent>
TEvent *& EventBuffer<TEvent*>::operator[] (const unsigned long index) const{
       return buffer[index];
}

template <class TEvent>
EventBuffer<TEvent*>::~EventBuffer()
{
  //printf("%s\n", IsIndependent ? "true": "false");	
  if (IsIndependent) 
    {
      for (ushort ind = 0; ind < consumed; ind ++)
	{
	  buffer[ind] -> Close();
	  delete buffer[ind];
	}
    }
  //free((TEvent**)buffer);
  delete [] buffer;
 //printf("destructed pointer buffer\n");
}

