procstat
========

Very simple tool to parse info from /proc/stat on ubuntu, can also 
be used to query individual threads.  I built this to check process 
statistics for a scheduler benchmark so the code might not be pretty, 
but it generally will work for Ubuntu's flavor of Linux.

You can easily do this manually but if you're running benchmarks on say
a cluster its nice to have a way that'll work easily with your test 
harness or driver program.

In order to get data from threads you'll have to modify the source to 
look at an individual processes task subfolder in Ubuntu so that it'll 
look within each thread of a process and parse the status.  Eventually
I'll get around to modifying it to do this but I havne't had time yet.

Use at your own risk, otherwise enjoy not re-writing the same code 
although I'm sure if you search enough you'll probably find multiple 
versions out there.
