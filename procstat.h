#ifndef _PROCSTAT_H_
#define _PROCSTAT_H_

#include <sys/types.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif

/* this roughly matches the structure of the Ubuntu linux /proc/<pid>/stat data */
struct ProcStatData{
   int      pid;
   char     executable[100];
   char     state;
   int      parent_pid;
   int      group_id;
   int      session_id;
   int      tty_nr; /* controlling terminal */
   int      foreground_id; /* id of foreground process group of controlling terminal process */
   unsigned int   flags;
   long unsigned int   minor_faults;
   long unsigned int   child_minor_faults;
   long unsigned int   major_faults;
   long unsigned int   child_major_faults;
   long unsigned int   uptime;
   long unsigned int   scheduled_time; /* in clock ticks, divide by sysconf(__SC_CLK_TCK) */
   long int   child_uptime;
   long int   child_scheduled_time;
   long int   priority;
   long int   nice;
   long int   number_threads;
   long int   itrealvalue; /* not used */
   long long unsigned int start_time; /* in jiffies */
   long unsigned int virtual_mem_size_bytes; 
   long int resident_mem_size;
   long unsigned int resident_mem_soft_limit;
   long unsigned int startcode; /* address above which program text can run */
   long unsigned int endcode; /* address below which program text can run */
   long unsigned int startstack; /* bottom of stack */
   long unsigned int curr_esp; /* current value of stack pointer */
   long unsigned int curr_eip; /* current instruction pointer */
   long unsigned int signal_unused;
   long unsigned int signal_ignore_unused;
   long unsigned int signal_caught_unused;
   long unsigned int channel;
   long unsigned int pages_swapped;
   long unsigned int cumulative_child_swapped_pages;
   int   exit_signal;
   int   processor_last_executed_on;
   unsigned int rt_schedule; /* 0-99 for RT process, otherwise 0 */
   unsigned int policy; /* defined in linux/sched.h */
   long long unsigned int delayed_io_ticks; /* clock ticks process was delayed for io */
   long unsigned int guest_time; /* time spent running a virtual cpu for guest OS */
   long int child_guest_time;
};


struct ProcStatusData{
   int voluntary_context_swaps;
   int non_voluntary_context_swaps;
};

struct ProcStatusData* get_context_swaps_for_process(pid_t *pid);

struct ProcStatData* get_proc_stat_data_for_process(pid_t *pid);

#ifdef __cplusplus
}
#endif
#endif /* END _PROCSTAT_H_ */
