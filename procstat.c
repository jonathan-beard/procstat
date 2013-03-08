#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include "procstat.h"

struct ProcStatusData* get_context_swaps_for_process(pid_t *id){
   pid_t the_id = 0;
   if(id == NULL) 
      the_id = getpid();
   else
      the_id = *id;
   struct ProcStatusData *data = malloc(sizeof(struct ProcStatusData));
   if(data == NULL){
      perror("Failed to initialize ProcStatusData struct!!");
      exit( EXIT_FAILURE );
   }
   memset(data, 0, sizeof(struct ProcStatusData));
   const size_t path_buffer_size = 500;
   char path_buffer[ path_buffer_size ];
   memset(path_buffer, '\0', path_buffer_size * sizeof( char ) );
   snprintf(path_buffer, path_buffer_size, "/proc/%d/status", the_id);
   FILE *fp = fopen(path_buffer, "r");
   if(fp == NULL){
      perror(path_buffer);
      exit(EXIT_FAILURE);
   }
   const size_t token_buffer_size = 100;
   char token_buffer[ token_buffer_size ];
   memset(token_buffer, '\0', token_buffer_size );
   int num_read = fscanf(fp, "%s\n",token_buffer);
   enum STATE {
                  VOL = 0, 
                  NON, 
                  DONE,
                  N
              };
   const char *tokens[N] = 
            {
               [VOL] = "voluntary_ctxt_switches:",
               [NON] = "nonvoluntary_ctxt_switches:",
               [DONE] = NULL
            };
   enum STATE s = VOL;
   while(EOF != num_read ){
      if(strcmp(token_buffer, tokens[s]) == 0){
         num_read = fscanf(fp, "%s\n",token_buffer);   
         if(s == VOL) data->voluntary_context_swaps = 
                                    strtol(token_buffer, NULL, 10);
         if(s == NON) data->non_voluntary_context_swaps = 
                                    strtol(token_buffer, NULL, 10);
         if(++s == DONE) break;  
      }
      num_read = fscanf(fp, "%s\n",token_buffer);   
   }
   fclose(fp);
   return(data);
};

struct ProcStatData* get_proc_stat_data_for_process(pid_t *pid){
   pid_t the_id  = 0;
   if(pid == NULL)
      the_id = getpid();
   else
      the_id = *pid;
   struct ProcStatData *data = malloc(sizeof(struct ProcStatData));
   if(data == NULL){
      perror("Failed to initialize ProcStatData struct!!");
      exit(EXIT_FAILURE);
   }
   memset(data, 0, sizeof(struct ProcStatData));
   const size_t path_buffer_size = 500;
   char path_buffer[ path_buffer_size ];
   memset( path_buffer, '\0', path_buffer_size * sizeof( char ) );
   snprintf(path_buffer, path_buffer_size, "/proc/%d/stat", the_id );
   FILE *fp = fopen(path_buffer, "r");
   if(fp == NULL){
      perror(path_buffer);
      exit(EXIT_FAILURE);
   }
   const size_t token_buffer_size = 100;
   char token_buffer[ token_buffer_size ];
   memset( token_buffer, '\0', token_buffer_size * sizeof( char ) );

   /* should probably also check errno and re-add the null term for
    * strings if this is to be used in production code */

   //int      pid;
   fscanf(fp, "%s",token_buffer);
   data->pid = strtol(token_buffer,NULL,10);

   //char     executable[100];
   fscanf(fp, "%s",token_buffer);
   {
      const size_t length = strlen(token_buffer);
      strncpy(data->executable,token_buffer, length);
   }
   //char     state;
   fscanf(fp, "%s",token_buffer);
   data->state = token_buffer[0];

   //int      parent_pid;
   fscanf(fp, "%s",token_buffer);
   data->parent_pid = strtol(token_buffer,NULL,10);
   
   //int      group_id;
   fscanf(fp, "%s",token_buffer);
   data->group_id = strtol(token_buffer,NULL,10);

   //int      session_id;
   fscanf(fp, "%s",token_buffer);
   data->session_id = strtol(token_buffer, NULL, 10);

   //int      tty_nr; /* controlling terminal */
   fscanf(fp, "%s",token_buffer);
   data->tty_nr = strtol(token_buffer, NULL, 10);

   //int      foreground_id; /* id of foreground process group of controlling terminal process */
   fscanf(fp, "%s",token_buffer);
   data->foreground_id = strtol(token_buffer, NULL, 10);

   //unsigned int   flags;
   fscanf(fp, "%s",token_buffer);
   data->flags = strtoul(token_buffer, NULL, 10);
   
   //long unsigned int   minor_faults;
   fscanf(fp, "%s",token_buffer);
   data->minor_faults = strtoul(token_buffer, NULL, 10);

   //long unsigned int   child_minor_faults;
   fscanf(fp, "%s",token_buffer);
   data->child_minor_faults = strtoul(token_buffer, NULL, 10);

   //long unsigned int   major_faults;
   fscanf(fp, "%s",token_buffer);
   data->major_faults = strtoul(token_buffer, NULL, 10);

   //long unsigned int   child_major_faults;
   fscanf(fp, "%s",token_buffer);
   data->child_major_faults = strtoul(token_buffer, NULL, 10);

   //long unsigned int   uptime;
   fscanf(fp, "%s",token_buffer);
   data->uptime = strtoul(token_buffer, NULL, 10);

   //long unsigned int   scheduled_time; /* in clock ticks, divide by sysconf(__SC_CLK_TCK) */
   fscanf(fp, "%s",token_buffer);
   data->scheduled_time = strtoul(token_buffer, NULL, 10);

   //long int   child_uptime;
   fscanf(fp, "%s",token_buffer);
   data->child_uptime = strtol(token_buffer,NULL,10);

   //long int   child_scheduled_time;
   fscanf(fp, "%s",token_buffer);
   data->child_scheduled_time = strtol(token_buffer, NULL, 10);

   //long int   priority;
   fscanf(fp, "%s",token_buffer);
   data->priority = strtol(token_buffer,NULL,10);

   //long int   nice;
   fscanf(fp, "%s",token_buffer);
   data->nice = strtol(token_buffer, NULL, 10);

   //long int   number_threads;
   fscanf(fp, "%s",token_buffer);
   data->number_threads = strtol(token_buffer, NULL, 10);

   //long int   itrealvalue; /* not used */
   fscanf(fp, "%s",token_buffer);
   data->itrealvalue = strtol(token_buffer, NULL, 10);

   //long long unsigned int start_time; /* in jiffies */
   fscanf(fp, "%s",token_buffer);
   data->start_time = strtoull(token_buffer, NULL, 10);

   //long unsigned int virtual_mem_size_bytes; 
   fscanf(fp, "%s",token_buffer);
   data->virtual_mem_size_bytes = strtoul(token_buffer, NULL, 10);

   //long int resident_mem_size;
   fscanf(fp, "%s",token_buffer);
   data->resident_mem_size = strtol(token_buffer, NULL, 10);

   //long unsigned int resident_mem_soft_limit;
   fscanf(fp, "%s",token_buffer);
   data->resident_mem_soft_limit= strtol(token_buffer,NULL, 10);

   //long unsigned int startcode; /* address above which program text can run */
   fscanf(fp, "%s",token_buffer);
   data->startcode = strtoul(token_buffer, NULL, 10);

   //long unsigned int endcode; /* address below which program text can run */
   fscanf(fp, "%s",token_buffer);
   data->endcode = strtoul(token_buffer, NULL, 10);

   //long unsigned int startstack; /* bottom of stack */
   fscanf(fp, "%s",token_buffer);
   data->startstack = strtoul(token_buffer, NULL, 10);

   //long unsigned int curr_esp; /* current value of stack pointer */
   fscanf(fp, "%s",token_buffer);
   data->curr_esp = strtoul(token_buffer, NULL, 10);

   //long unsigned int curr_eip; /* current instruction pointer */
   fscanf(fp, "%s",token_buffer);
   data->curr_eip = strtoul(token_buffer, NULL, 10);

   //long unsigned int signal_unused;
   fscanf(fp, "%s",token_buffer);
   data->signal_unused = strtoul(token_buffer, NULL, 10);

//   long unsigned int signal_ignore_unused;
   fscanf(fp, "%s",token_buffer);
   data->signal_ignore_unused = strtoul(token_buffer, NULL, 10);

//   long unsigned int signal_caught_unused;
   fscanf(fp, "%s",token_buffer);
   data->signal_caught_unused = strtoul(token_buffer, NULL, 10);

   //long unsigned int channel;
   fscanf(fp, "%s",token_buffer);
   data->channel = strtoul(token_buffer, NULL, 10);

   //long unsigned int pages_swapped;
   fscanf(fp, "%s",token_buffer);
   data->pages_swapped = strtoul(token_buffer, NULL, 10);

   //long unsigned int cumulative_child_swapped_pages;
   fscanf(fp, "%s",token_buffer);
   data->cumulative_child_swapped_pages = strtoul(token_buffer, NULL, 10);

   //int   exit_signal;
   fscanf(fp, "%s",token_buffer);
   data->exit_signal = strtol(token_buffer, NULL, 10);

   //int   processor_last_executed_on;
   fscanf(fp, "%s",token_buffer);
   data->processor_last_executed_on = strtol(token_buffer, NULL, 10);
   
   //unsigned int rt_schedule; /* 0-99 for RT process, otherwise 0 */
   fscanf(fp, "%s",token_buffer);
   data->rt_schedule = strtoul(token_buffer, NULL, 10);

   //unsigned int policy; /* defined in linux/sched.h */
   fscanf(fp, "%s",token_buffer);
   data->policy = strtoul(token_buffer, NULL, 10);

   //long long unsigned int delayed_io_ticks; /* clock ticks process was delayed for io */
   fscanf(fp, "%s",token_buffer);
   data->delayed_io_ticks = strtoull(token_buffer, NULL, 10);

   //long unsigned int guest_time; /* time spent running a virtual cpu for guest OS */
   fscanf(fp, "%s",token_buffer);
   data->guest_time = strtoul(token_buffer, NULL, 10);

   //long int child_guest_time;
   fscanf(fp, "%s",token_buffer);
   data->child_guest_time = strtol(token_buffer, NULL, 10);

   fclose(fp);
   return(data);
};
