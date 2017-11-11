#include <stdio.h>
#include "dmessage.pb-c.h"
#define MAX_MSG_SIZE 4096

int main (int argc, const char * argv[]) 
{
  DMessage *msg;
  ReqGetSlotInfo *sub1;
  ReqGetSlotList *sub2;      


  char c; int i=0;       // Data holders
  uint8_t buf[MAX_MSG_SIZE]; // Input data container for bytes

  unsigned len;
  fread (&len, sizeof(len), 1, stdin);
  printf("len %d\n", len);

    
  while (fread(&c,1,1,stdin) != 0)
  {
    if (i >= MAX_MSG_SIZE)
    {
      fprintf(stderr,"message too long for allocated buffer\n");
      return 1;
    }
    buf[i++] = c;
    if ( i == len)
        break;
  }

    
  msg = dmessage__unpack(NULL,i,buf); // Deserialize the serialized input
  if (msg == NULL)
  { // Something failed
    fprintf(stderr,"error unpacking incoming message\n");
    return 1;
  }
  sub1 = msg->getslotinfo;
  sub2 = msg->getslotlist;
  uint64_t code = msg->code;

  printf("Received: code=%lu\n",msg->code);
  if (msg->getslotinfo != NULL) printf("getslotinfo slotID=%d",sub1->slotid);
  printf("\n");
  if (msg->getslotlist != NULL) printf("getslotlist tokenPresent=%d ulCount=%d",sub2->tokenpresent, sub2->ulcount);
  printf("\n");
    
  dmessage__free_unpacked(msg,NULL);










  fread (&len, sizeof(len), 1, stdin);
  printf("len %d\n", len);
   i = 0;
    
  while (fread(&c,1,1,stdin) != 0)
  {
    if (i >= MAX_MSG_SIZE)
    {
      fprintf(stderr,"message too long for allocated buffer\n");
      return 1;
    }
    buf[i++] = c;
    if ( i == len)
        break;
  }

  msg = dmessage__unpack(NULL,i,buf); // Deserialize the serialized input
  if (msg == NULL)
  { // Something failed
    fprintf(stderr,"error unpacking incoming message\n");
    return 1;
  }
  sub1 = msg->getslotinfo;
  sub2 = msg->getslotlist;
  code = msg->code;

  printf("Received: code=%lu\n",msg->code);
  if (msg->getslotinfo != NULL) printf("getslotinfo slotID=%d",sub1->slotid);
  printf("\n");
  if (msg->getslotlist != NULL) printf("getslotlist tokenPresent=%d ulCount=%d",sub2->tokenpresent, sub2->ulcount);
  printf("\n");
    
  dmessage__free_unpacked(msg,NULL);



















    
  return 0;
}
