procstatlib:
	$(MAKE) procstat.o
	$(AR) rcs procstat.a procstat.o

cleanprocstatlib:
	rm -rf procstat.o procstat.a
