CC   = clang
CXX  = clang++

procstatlib:
	$(MAKE) procstat.o
	$(AR) rcs libprocstat.a procstat.o

cleanprocstatlib:
	rm -rf procstat.o libprocstat.a
