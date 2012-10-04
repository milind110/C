/* This file contains  */
/* 1. debug macros that append time, thread name,  file name, function name and line number to debug lines.  */
/* 2. Prototypes of common utility code. */

#ifndef MSM_COMMON
#define MSM_COMMON

#define MAX_TIME_STR_LEN 50 /* 26 letters for ctime() and then some for tv_usec of time val */
#define MAX_THREAD_NAME_LEN 15 /* pthread_setname_np takes only this much, so we also limit it here */



/* common functions prototypes */

/* Returns a null terminated string of maximum length MAX_TIME_STR_LEN into the string allocated by the caller */
void gettimestring(char *s);


/*debug print related macros */

#define ENTRY     {char s[MAX_TIME_STR_LEN] = "" ; \
gettimestring(s);\
printf("%s: in thread: %s\t in func: %s\t at line: %d\t entered\n\r", s, (char *)pthread_getspecific(namekey) , __PRETTY_FUNCTION__, __LINE__);\
}

#define EXIT     {char s[MAX_TIME_STR_LEN] = "" ; \
gettimestring(s);\
printf("%s: in thread: %s\t in func: %s\t at line: %d\t exiting\n\r", s, (char *)pthread_getspecific(namekey) , __PRETTY_FUNCTION__, __LINE__);\
}

#define DEBUG_LOG_0(a)     {char s[MAX_TIME_STR_LEN] = "" ; \
gettimestring(s);\
printf("%s: in thread: %s\t in func: %s\t at line: %d\t " a "\n\r", s, (char *)pthread_getspecific(namekey) , __PRETTY_FUNCTION__, __LINE__);\
}

#define DEBUG_LOG_1(a, b)     {char s[MAX_TIME_STR_LEN] = "" ; \
gettimestring(s);\
printf("%s: in thread: %s\t in func: %s\t at line: %d\t " a "\n\r", s, (char *)pthread_getspecific(namekey), __PRETTY_FUNCTION__, __LINE__, b);\
}

#define DEBUG_LOG_2(a, b ,c)     {char s[MAX_TIME_STR_LEN] = "" ; \
gettimestring(s);\
printf("%s: in thread: %s\t in func: %s\t at line: %d\t " a "\n\r", s, (char *)pthread_getspecific(namekey), __PRETTY_FUNCTION__, __LINE__, b, c);\
}


#endif /* MSM_COMMON */
