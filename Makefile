#g++-7 -Wall -pedantic -std=c++1z -c -o Matrix.o -O6 Matrix.cpp -lpthread
g++-7 -Wall -pedantic -std=c++1z -o NumberTheory.exe -O6 NumberTheory.cpp -lpthread
#g++-7 -Wall -pedantic -std=c++1z -o crt.exe -O6 crt.cpp -lpthread
#g++-7 -Wall -pedantic -std=c++1z NumberTheory.o -o main.exe -O6 main.cpp -lpthread
rm -f *.o
