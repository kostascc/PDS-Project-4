# PDS-Project-4
Sparse Compressed (CSC) Boolean Matrix-Matrix Multiplication Algorithms - Parallel &amp; Distributed Systems


Note: Measured times in the report were flawed, as the timing was done by mistake with the `-O0` flag for g++. Actual times are in many cases a tenth of the recorded time.


Test this by executing:
```
make
./debug --v1 --opt-csr-a --opt-csr-f -a ./resources/1138_bus.mtx -b ./resources/1138_bus.mtx -f ./resources/1138_bus.mtx -t 6
```

Warning! Matrices are automatically padded based on the algorithm. The Height and Width of an imported Matrix may be different than what is stated in the `.mtx` file.


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


For debugging information and sanity checks, uncomment the `#define DEBUGGING_CHECKS` in `include/AUXParameters.hpp` and:
```
make clean
make
```


To change the length of Blocks in a Noodle, and thus the required memory for V3 and V4, edit `#define V3_BLOCKS_PER_NOODLE_BLOCK 1` in `include/AUXParameters.hpp` to a positive integer of your choice. Acceptable values are 1 through H, where H is the height of the Padded matrix.

The required Memory for V3 is `4* H^2 / (8 * V3_BLOCKS_PER_NOODLE_BLOCK)` bytes, where H is the Height of the input Matrix.
The required Memory for V4 is the above calculation multiplied by the number of nodes.
