### **Shared Libraries in C**
Shared libraries are dynamically linked libraries that are loaded into memory and shared among multiple programs at runtime. This reduces memory usage and disk space compared to static libraries.

---

### **1. Key Characteristics**
- **Dynamic Loading**: The library is loaded at runtime rather than at compile time.
- **Shared Memory**: Multiple programs can use the same library loaded into memory, saving system resources.
- **File Extension**: Shared libraries typically have the `.so` (Shared Object) extension on Linux/Unix and `.dll` (Dynamic Link Library) on Windows.

---

### **2. Creating and Using Shared Libraries**

#### **Step 1: Compile Source Files**
Compile the source files into position-independent code (PIC), which is required for shared libraries:

```bash
cc -Wall -fPIC -c ctest1.c ctest2.c
```

- **`-fPIC`**: Generates position-independent code, allowing the library to be loaded at any memory address.

This produces:
- `ctest1.o`
- `ctest2.o`

---

#### **Step 2: Create the Shared Library**
Use the `-shared` flag to create the shared library from the object files:

```bash
cc -shared -o libctest.so ctest1.o ctest2.o
```

- **`-shared`**: Indicates that a shared library should be created.
- This produces `libctest.so`.

---

#### **Step 3: Compile and Link the Main Program**
Compile and link the main program (`prog.c`) with the shared library:

```bash
cc -o prog prog.c ./libctest.so
```

- If the library is not in the current directory, specify its path with `-L` and `-l` flags:
  ```bash
  cc -o prog prog.c -L/path/to/library-directory -lctest
  ```

---

#### **Step 4: Run the Program**
If the shared library is in the default system paths (e.g., `/usr/lib`, `/usr/local/lib`), you can run the program directly:

```bash
./prog
```

If the shared library is in a custom directory, you must tell the runtime linker where to find it.

- **Option 1: Use `LD_LIBRARY_PATH`**
  ```bash
  export LD_LIBRARY_PATH=/path/to/library-directory:$LD_LIBRARY_PATH
  ./prog
  ```

- **Option 2: Embed the Library Path**
  Use the `-Wl,-rpath` flag during linking to embed the library's path into the executable:
  ```bash
  cc -o prog prog.c -L/path/to/library-directory -lctest -Wl,-rpath,/path/to/library-directory
  ```

---

### **3. Checking Shared Library Dependencies**
Use the `ldd` command to verify which shared libraries the program depends on:

```bash
ldd prog
```

Output:
```plaintext
libctest.so => /path/to/library/libctest.so (0x...)
libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x...)
```

---

### **4. Advantages of Shared Libraries**
1. **Memory Efficiency**: A shared library is loaded once into memory and shared among all programs that use it.
2. **Reduced File Size**: Programs are smaller because they don't include the library code; they reference it dynamically.
3. **Easy Updates**: Updating a shared library updates all programs that use it without recompiling them.

---

### **5. Cleaning Up**
To remove temporary files and reset the environment:

```bash
rm -f *.o libctest.so prog
```

---

### Summary of Commands for Shared Libraries

| **Command**       | **Purpose**                                    |
|--------------------|------------------------------------------------|
| `-fPIC`           | Generate position-independent code.            |
| `-shared`         | Create a shared library.                       |
| `-L`              | Specify the directory containing the library.  |
| `-l`              | Link with a shared library.                    |
| `LD_LIBRARY_PATH` | Specify runtime search paths for libraries.    |
| `ldd`             | Display shared library dependencies.           |

Shared libraries offer a powerful way to manage code reuse and memory efficiency in C programs.