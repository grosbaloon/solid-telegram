#include <stdio.h>
#include <stdlib.h>
#include "dmessage.pb-c.h"

int main (int argc, const char * argv[]) 
{
  DMessage msg    = DMESSAGE__INIT;
  ReqGetSlotInfo sub1 = REQ_GET_SLOT_INFO__INIT;
  ReqGetSlotList sub2 = REQ_GET_SLOT_LIST__INIT;
  void *buf;
  unsigned len;
  
  sub1.slotid = 12;

  msg.getslotinfo = &sub1;
  msg.code = 5;
  
  
  len = dmessage__get_packed_size (&msg); // This is the calculated packing length
  buf = malloc (len);                     // Allocate memory
  dmessage__pack (&msg, buf);             // Pack msg, including submessages

  fprintf(stderr,"Writing %d serialized bytes\n",len); // See the length of message

  fwrite (&len, sizeof(len), 1, stdout);           // Write to stdout to allow direct command line piping
  fwrite (buf, len, 1, stdout);           // Write to stdout to allow direct command line piping
  
  free(buf); // Free the allocated serialized buffer


  dmessage__init(&msg);
  sub2.tokenpresent = 1;
  sub2.ulcount = 10;
  msg.getslotlist = &sub2;
  msg.code = 4;
  

  len = dmessage__get_packed_size (&msg); // This is the calculated packing length
  buf = malloc (len);                     // Allocate memory
  dmessage__pack (&msg, buf);             // Pack msg, including submessages

  fprintf(stderr,"Writing %d serialized bytes\n",len); // See the length of message
  fwrite (&len, sizeof(len), 1, stdout);
  fwrite (buf, len, 1, stdout);           // Write to stdout to allow direct command line piping
  
  free(buf); // Free the allocated serialized buffer


  return 0;
}
