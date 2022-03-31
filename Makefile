# -*- Makefile -*-
pi_e: GreatBin.o GB_math.o pi_e.o
	g++ -o pi_e pi_e.o GreatBin.o GB_math.o
pi_e.o: pi_e.cpp
	g++ pi_e.cpp -c
GreatBin.o: GreatBin.cpp
	g++ GreatBin.cpp -c
GB_math.o: GB_math.cpp
	g++ GB_math.cpp -c
