# -*- Makefile -*-
pi_e: GreatBin.o GB_math.o pi_e.o GreatBinExp.o
	g++ -o pi_e pi_e.o GreatBin.o GB_math.o GreatBinExp.o
pi_e.o: pi_e.cpp
	g++ pi_e.cpp -c
GreatBin.o: GreatBin.cpp
	g++ GreatBin.cpp -c
GreatBinExp.o: GreatBinExp.cpp
	g++ GreatBinExp.cpp -c
GB_math.o: GB_math.cpp
	g++ GB_math.cpp -c
# profile: GreatBin.o GB_math.o pi_e.o GreatBinExp.o
# 	g++ -pg -o pi_e pi_e.o GreatBin.o GB_math.o GreatBinExp.o
# pi_e.o: pi_e.cpp
# 	g++ pi_e.cpp -c -pg
# GreatBin.o: GreatBin.cpp
# 	g++ GreatBin.cpp -c -pg
# GreatBinExp.o: GreatBinExp.cpp
# 	g++ GreatBinExp.cpp -c -pg
# GB_math.o: GB_math.cpp
# 	g++ GB_math.cpp -c -pg
