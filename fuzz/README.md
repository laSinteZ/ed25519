# To use AFL (Americal Fuzzy Lop)

```bash
mkdir build
cd build
cmake .. -DFUZZING=ON -DCMAKE_CXX_COMPILER=afl-gcc -DCMAKE_CXX_COMPILER=afl-g++
make fuzzer
afl-fuzz -i ../fuzz/testcases/ -o OUTPUT -m none -- bin/fuzzer
```

# To use LLVM's libFuzzer

```bash
mkdir build
cd build
cmake .. -DFUZZING=ON -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang -DSANITIZER=address -DLLVM_ROOT=<path to LLVM>
make fuzzer
bin/fuzzer ../fuzz/testcases
```

