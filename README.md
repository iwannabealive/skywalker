# skywalker

A tiny, self-contained C++17 galgame-style engine skeleton. It uses only the C++ standard library and prints actions to the console so it can compile on Visual Studio without extra dependencies.

## Building
```
cmake -S . -B build
cmake --build build
```

## Running
From the repo root:
```
./build/gal_engine_demo
```
Use **Enter** (or type `c` then Enter) to advance dialogue, and `q` then Enter to quit. The sample script is located at `scripts/main.txt`.
