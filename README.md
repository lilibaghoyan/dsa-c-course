# dsa-c-course

This is the **starter project for the Data Structures & Algorithms in C course**.  
It is a **pure C project** built with **CMake**, with a simple library and tests.  
A ready-to-use **Docker Compose environment** is included — no need to install a compiler or CMake locally.

---

## Requirements
- [Docker](https://docs.docker.com/get-docker/)  
- [Docker Compose](https://docs.docker.com/compose/)

---

## Quick Start

### 1. Clone the repository
```bash
git clone <repo_url> dsa-c-course
cd dsa-c-course
```

### 2. Build the Docker environment
```bash
docker compose build
```

### 3. Start developing
```bash
docker compose run --rm dev
```

Inside the container, build and test your project:
```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

---

## Development Workflow

### Build the project
```bash
docker compose run --rm dev cmake -S . -B build
docker compose run --rm dev cmake --build build
```

### Run tests
```bash
docker compose run --rm dev ctest --test-dir build --output-on-failure
```

### Format code
```bash
docker compose run --rm dev clang-format -i src/*.c include/*.h tests/*.c
```

### Interactive development shell
For longer coding sessions, open an interactive shell:
```bash
docker compose run dev
```

### Working Inside the Container

Once inside the container, you can build and run tests as follows:

#### Using CMake's recommended workflow
```bash
# Configure and build the project
cmake -S . -B build
cmake --build build

# Run all tests with output on failure
ctest --test-dir build --output-on-failure

# Format source code
clang-format -i src/*.c include/*.h tests/*.c
````

#### Using a manual build directory

```bash
# Create and enter a build directory
mkdir -p build
cd build

# Configure and build
cmake ..
make -j$(nproc)   # Use all available cores

# Run all tests with verbose output
ctest --verbose

# Or run a specific test by name
ctest -R test_name --verbose
```

This approach keeps your build clean, ensures tests are reproducible, and helps maintain consistent code formatting.


### Clean Build

To remove any previous build artifacts and build the project from scratch:

```bash
# Clean build: remove old build directory and rebuild
rm -rf build
mkdir build
cd build
cmake ..
make -j$(nproc)

# Run all tests
ctest --verbose

# Format source code
clang-format -i src/*.c include/*.h tests/*.c
````

You can think of this as a one-step “cleanbuild” process—use it whenever you want a completely fresh build.

---

Type `exit` when done. Your changes are automatically saved on your host machine.

---

## Included Tools

The Docker environment includes everything you need:

- **CMake** (3.16+) - Build system generator
- **Clang** - Modern C compiler
- **clang-format** - Automatic code formatting
- **GDB** - Debugger for troubleshooting
- **Valgrind** - Memory leak detection
- **Git** - Version control

---

## Common Tasks

### Check for memory leaks
```bash
docker compose run --rm dev valgrind --leak-check=full ./build/tests/test_executable
```

### Debug with GDB
```bash
docker compose run --rm dev gdb ./build/tests/test_executable
```

### Clean build
```bash
docker compose run --rm dev rm -rf build
```

---

## Notes

* The project uses `assert()` for tests (simple and lightweight).  
* You can add a real C testing framework later (e.g., Check, Unity, Criterion).  
* `.clang-format` ensures consistent code style across all code.
* All your code changes are saved on your host machine, even after exiting the container.
* The container uses **Clang** as the default C compiler.

---

## Troubleshooting

**Container won't start?**
- Ensure Docker is running
- Try: `docker compose down` then rebuild with `docker compose build`

**Can't find compiled files?**
- Make sure you created the `build` directory first: `cmake -S . -B build`

**Permission issues on Linux?**
- You may need to run Docker commands with `sudo`, or add your user to the `docker` group

**Changes not persisting?**
- The current directory is mounted as a volume, so all changes should persist automatically
- Verify you're in the correct directory before running `docker compose run`

---

## Tips for Developers

1. Always use the Docker environment to ensure consistent builds across different machines
2. Run `clang-format` before committing code to maintain consistent style
3. Use `ctest --output-on-failure` to see detailed test output
4. Run tests frequently as you develop
5. Use `valgrind` to catch memory leaks early
6. Keep the interactive shell open during active development, then `exit` when done
