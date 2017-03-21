swig -c++ -java -package src -outdir src jCbc.i  



SET Java_Path=C:\Program Files\Java\jdk1.8.0_121
SET CBC_Path=C:\Univ\Cbc-2.9.8

g++ -c -fopenmp jCbc.cpp jCbc_wrap.cxx  -static -Wl,--kill-at -I "%Java_Path%\include" -I "%Java_Path%\include\win32" -I "%CBC_Path%\include\coin" 

g++ -shared -fopenmp jCbc.o jCbc_wrap.o  -o jCbc.dll  -static -Wl,--kill-at -I "%Java_Path%\include" -I "%Java_Path%\include\win32" -I "%CBC_Path%\include\coin"  -L "%CBC_Path%\lib"   -lCbcSolver -lCbc  -lClp -lOsiClp -lOsi -lOsiCbc -lCgl -lCoinUtils -lcoinmumps -lcoinblas -lcoinlapack -lcoinasl -lcoinmetis -lcoinglpk -lgfortran -lz -lquadmath


:END