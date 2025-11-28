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

The engine looks for `scripts/main.txt` in three places, in order:
1. The current working directory (`./scripts/main.txt`).
2. Beside the executable (`<exe_dir>/scripts/main.txt`).
3. The original source tree defined at build time (`PROJECT_SOURCE_DIR/scripts/main.txt`).

If you run the executable from an IDE, set the working directory to the folder that contains the built binary or ensure a `scripts` folder sits next to the executable.
