# Nexoris

This is the Nexoris game engine project.

## How to Build

This project uses CMake as its build system. Follow these steps to build the project:

1. Open your terminal (e.g., PowerShell or Command Prompt).
2. Navigate to the root directory of the project.
3. Generate the build files:
   ```sh
   cmake -S . -B build
   ```
4. Build the project:
   ```sh
   cmake --build build
   ```

## How to Run

After a successful build, you can run the executable. Depending on your CMake generator (e.g., Visual Studio/MSVC vs. MinGW/Ninja), the executable might be located in a `Debug` or `Release` subfolder, or directly in the `build` folder.

**If using Visual Studio / MSVC:**
```sh
.\build\Debug\Nexoris.exe
```

**If using MinGW or Ninja:**
```sh
.\build\Nexoris.exe
```
