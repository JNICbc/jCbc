Introduction

jCbc is a Java Native Interface for COIN OR Mixed Integer Linear Programming Solver Cbc and Linear Programming Solver CLP. jCbc  uses open source Simplified Wrapper and Interface Generator SWIG, which is a software development tool that connects libraries written in C and C++ with a variety of high-level programming languages. jCbc solves Mixed Integer Programming Problems of the form 

![equation](http://www.sciweavers.org/tex2img.php?eq=%5Cbegin%7Beqnarray%2A%7D%0A%09%5Cbegin%7Barray%7D%7Blllrr%7D%0A%09%09%5Cmbox%7Bmin%7D%20%26%20c%5ETx%20%5C%5C%0A%09%09%5Cmbox%7Bs.t.%7D%26%20Ax%5Clesseqqgtr%20b%26%26%28MILP%29%5C%5C%0A%09%09%26%20l%5Cleq%20x%20%5Cleq%20u%20%5C%5C%0A%09%09%26%20x_i%20%5Cin%20%5Cmathbb%7BZ%7D%5C%20%20%5Cforall%20i%5Cin%20I%2C%5C%5C%0A%09%5Cend%7Barray%7D%0A%5Cend%7Beqnarray%2A%7D%0A&bc=White&fc=Black&im=png&fs=12&ff=arev&edit=0)

The MILP can be either constructed using the relavant functions in jCbc, or it can be loaded from an LP or MPS file. In either case, jCbc uses branch and cut algorithm to find an optimal solution or declares that the problem has no solution. 

![equation](http://www.sciweavers.org/tex2img.php?eq=1%2Bsin%28mc%5E2%29&bc=White&fc=Black&im=jpg&fs=12&ff=arev&edit=)


*********************************************************************************
License 

jCbc is distributed under GPL-v3 licese. Everyone is permitted to copy and distribute verbatim copies of this license document, but changing it is not allowed.



