# g--
Garbage collection compiler for C++

#### How to use
1. Clone this repository to your computer and add `compiler/Windows` to your PATH.
2. Enter `g-- <file_name>` to compile your file, with `<file_name>` being the path to your file. The compiler will change your file "directly" so that you can easily use the normal compiler right after (like `g++` or `cl`) :)

You can also add optional parameters after the filename when running `g--`:
- `--compress`: Compresses everything added by the compiler; that is `delete` (or `delete[]`) will be placed right after the `;` instead of on the next line.
- `--debug`: Prints out debugging information to the console while compiling.

**NOTE: Currently only works on Windows, if you want to run it on another OS you'll have to compile the `g--.cpp` file with a compiler working on your OS before using it.**
