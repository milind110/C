/* this file has implementations of the commonly used functions  */


#include <time.h>
#include <sys/time.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

#include "msm_common.h"


void gettimestring(char *s)
{
  int retval = 0; 
  time_t t; 
  char *ret = NULL;
  struct timeval tval;

  //get the seconds and make a string into timestring
  t = time(NULL);
  ret = ctime_r(&t, s);
  assert(NULL != ret);

  //get the micro seconds 
  retval = gettimeofday(&tval, NULL); 
  assert(0 == retval);

  //get a single string. Ugly code!! 
  snprintf(s+strnlen(s, MAX_TIME_STR_LEN)-1, MAX_TIME_STR_LEN, ": %ld", tval.tv_usec);
  s[strnlen(s, MAX_TIME_STR_LEN)] = '\0';
  
  return;
}



