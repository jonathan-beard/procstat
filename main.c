#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

#include "procstat.h"


int main(int argc, char **argv){
   /**
    * this is for example only to show how to use the source within a 
    * program
    */
   struct ProcStatusData *data = get_context_swaps_for_process(NULL);
   fprintf(stdout, "%d  - %d\n", 
           data->voluntary_context_swaps, 
           data->non_voluntary_context_swaps);
   free(data);
   if( argc < 2 ){
      fprintf( stderr, "input format should be ./procstat <process id>");
      exit( EXIT_FAILURE );
   }
   pid_t id = atoi( argv[1] );
   struct ProcStatData *data2 = get_proc_stat_data_for_process(&id);
   fprintf(stdout, 
           "PID - %d, Executable - %s, Exit Signal - %d, Scheduled Time - %lu\n",
           data2->pid, 
           data2->executable, 
           data2->exit_signal, 
           data2->scheduled_time);  
   free(data2);
   return( EXIT_SUCCESS );
};
