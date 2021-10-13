# PDS-Project-4
Sparse Compressed (CSC) Boolean Matrix-Matrix Multiplication Algorithms - Parallel &amp; Distributed Systems

Test this by executing:
```
make
./debug --v1 --opt-csr-a --opt-csr-f -a ./resources/1138_bus.mtx -b ./resources/1138_bus.mtx -f ./resources/1138_bus.mtx -t 6
```

Acceptable input arguments:
```
 -t <int>           Threads
 -a <uri>           Matrix A file
 --a-transpose      Transpose Matrix A
 --a-twocolumncoo   MM file of Matrix A doesn't contain values
 -b <uri>           Matrix B file
 --b-transpose      Transpose Matrix B
 --b-twocolumncoo   MM file of Matrix B doesn't contain values
 -f <uri>           Matrix F file
 --f-transpose      Transpose Matrix F
 --f-twocolumncoo   MM file of Matrix F doesn't contain values
 --opt-csr-a        Optimization: Uses CSR storage for Matrix A
 --opt-csr-b        Optimization: Uses CSR storage for Matrix B
 --opt-csr-f        Optimization: Uses CSR storage for Matrix F
 --v1               V1: O(n^3) algorithm
 --v2               V2: 3x3 Block BMM
 --v3               V3: Four-Russians (8x8 Block)
 --v4               V4: V3 with OpenMPI nodes
```

Test the OpenMPI execution with:
```
mpirun -np 3 ./debug --v4 --opt-csr-b -a ./resources/1138_bus.mtx -b ./resources/1138_bus.mtx -f ./resources/1138_bus.mtx -t 2
```
