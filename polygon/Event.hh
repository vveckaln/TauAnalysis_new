#ifndef _Event_hh
#define _Event_hh

class Event
{
public:
  Event();
  virtual ~Event();
  virtual void Open() = 0;
  virtual void Close() = 0;
};
#endif
