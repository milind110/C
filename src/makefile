#THIS IS ALSO MY SAMPLE MAKEFILE 
#$@ refers to the target for which we are writing the rule, useful for naming the executable. 

#the general format is : 
#target: dependency1 dependency2 dependency3
#	rule

CC:= gcc
COMPILE_OPTIONS:= -g -Wall -c 
LINK_OPTIONS:= -lpthread  

INC_FILES:= ../inc/msm_common.h ../inc/threads.h
INC_PATHS:=../inc

threads: threads.o msm_common.o
	$(CC) $(LINK_OPTIONS) -o $@ threads.o msm_common.o 

threads.o: $(INC_FILES) threads.c
	$(CC) $(COMPILE_OPTIONS) -I$(INC_PATHS) threads.c

msm_common.o: $(INC_FILES) msm_common.c
	$(CC) $(COMPILE_OPTIONS) -I$(INC_PATHS) msm_common.c


#.PHONY is needed to tell make that clean does not have anything do depend on. so it's a "phony" target.
.PHONY clean: 
clean:
	rm -fv *.o 
