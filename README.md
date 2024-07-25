# SCT-mem-api

SCT-mem-api is a C library for writing memory to external programs on Windows. It uses CMake for building the project.

## Requirements

- **CMake**: Version 3.5.0 or higher
- **Windows OS**

## Features

- Write to the memory of external processes.
- Designed for Windows.

## Installation

1. **Clone the repository:**

   ```sh
   git clone https://github.com/SeanProgramming/sct-mem-api.git
   ```

2. **Go to the project directory:**

   ```sh
   cd sct-mem-api
   ```

3. **Create a build directory:**

   ```sh
   mkdir build
   cd build
   ```

4. **Run CMake to generate build files:**

   ```sh
   cmake ..
   ```

5. **Build the project:**

   ```sh
   cmake --build .
   ```

## Usage

Include the provided header files in your C project and link against the built library. Check the `example_program` directory for sample usage.

## Contributing

1. Fork the repository.
2. Create a new branch for your changes.
3. Commit your changes.
4. Push the branch to your fork.
5. Open a Pull Request.

## License

MIT License. See the [LICENSE](LICENSE) file for details.

## Contact

For questions, email sean.pilonb@gmail.com
