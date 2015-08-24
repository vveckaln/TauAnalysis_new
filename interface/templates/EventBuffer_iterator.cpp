


template<class TEvent>
typename EventBuffer<TEvent*>::iterator  EventBuffer<TEvent*>::iterator::operator ++(int)
{
  iterator tmp = *this;
  *this  = to -> next;
  return tmp;
}

template<class TEvent>
typename EventBuffer<TEvent*>::iterator  EventBuffer<TEvent*>::iterator::operator ++()
{
  this = to -> next;
  return *this;
}

template<class TEvent>
bool                           EventBuffer<TEvent*>::iterator::operator != (const iterator & other)
{
  return this -> to != other.to;
}

template<class TEvent>
bool                           EventBuffer<TEvent*>::iterator::operator == (const iterator & other)
{
  return this -> to == other.to;
}

template<class TEvent>
TEvent &                      EventBuffer<TEvent*>::iterator::operator * ()
{
  return *to -> event;
}

template<class TEvent>
TEvent *                      EventBuffer<TEvent*>::iterator::operator -> ()
{
  return to -> event;
}

template<class TEvent>
EventCapsule<TEvent*> *&EventBuffer<TEvent*>::iterator::next()
{
  return to -> next;
}

template<class TEvent>
EventCapsule<TEvent*> *&EventBuffer<TEvent*>::iterator::previous()
{
  return to -> previous;
}

template<class TEvent>
typename EventBuffer<TEvent*>::iterator & EventBuffer<TEvent*>::iterator::operator =(EventCapsule<TEvent*>* other)
{
  to = other;
  return *this;
}

template<class TEvent>
EventBuffer<TEvent*>::iterator::iterator()
{
  to = NULL;
}


template<class TEvent>
EventBuffer<TEvent*>::iterator::iterator(EventCapsule<TEvent*>  * other)
{
  to = other;
}
