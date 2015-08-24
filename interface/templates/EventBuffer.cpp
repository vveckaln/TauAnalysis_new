template <class TEvent>
EventBuffer<TEvent>::EventBuffer(const unsigned long capacity): capacity(capacity)
{
  //buffer = (TEvent*) malloc(sizeof(TEvent)*capacity);
  //buffer = static_cast<TEvent*> (::operator new(sizeof(TEvent[capacity])));
  /*for (unsigned int ind = 0; ind < capacity; ind ++){
      new (buffer + ind) TEvent();
      *(buffer + ind) = TEvent();
  }*/
  
  buffer      = new EventCapsule<TEvent>[capacity];
  beginning   = buffer;
  theend      = buffer + capacity;
  consumed    = 0;
} 

template <class TEvent>
TEvent & EventBuffer<TEvent>::GetWriteSlot() const
{
  return buffer[consumed].event;
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
  return buffer[index].event;
}



template <class TEvent>
EventBuffer<TEvent>::~EventBuffer()
{
  /*for (unsigned ind = 0; ind < this -> size(); ind ++)
    {
      buffer[ind] .event.Close();
      }*/	
  //free((TEvent*)buffer);
  delete [] buffer;
}
