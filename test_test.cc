#include <stdio.h>
#include <vector>
//#include "LIP/TauAnalysis/interface/EventBuffer.hh"
#include "EventBuffer_test.hh"
#include "interface/ReadEvent_llvv.hh"
struct test_class
{
  void Close() {};
};
typedef ReadEvent_llvv * event_type;
using namespace std;
int main() 
{
  EventBuffer<event_type>  *output_buffer = new EventBuffer<event_type>(10, "independent");
  for (uint ind = 0; ind < 100000; ind ++)
    {
      event_type ev = output_buffer -> GetWriteSlot();
	ev -> Close();
      output_buffer -> PushWriteSlot();
      if (output_buffer -> IsFull())
	{
	  delete output_buffer;
	  output_buffer = new EventBuffer<event_type>(10, "independent");    
	}
    }

  delete output_buffer;  //delete [] p;
  
}
