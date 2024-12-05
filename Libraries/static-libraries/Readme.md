# Creating and Using a Static Library in C

This guide demonstrates how to create a static library using `ctest1.c` and `ctest2.c` and how to compile and run `prog.c` using this library.

---

## **1. Files Included**
- **`prog.c`**: The main program that uses the library functions.
- **`ctest1.c`**: Contains the definition of `func1()`.
- **`ctest2.c`**: Contains the definition of `func2()`.

---

## **2. Steps to Create and Use a Static Library**

### **Step 1: Compile the Source Files**
Compile `ctest1.c` and `ctest2.c` into object files (`.o` files):

```bash
cc -Wall -c ctest1.c ctest2.c
```

This will generate:
- `ctest1.o`
- `ctest2.o`

### **Step 2: Create the Static Library**
Use the `ar` command to archive the object files into a static library:

```bash
ar -cvq libctest.a ctest1.o ctest2.o
```

- `libctest.a` is the static library file.
- Use `ar -t libctest.a` to verify the contents of the library.

### **Step 3: Link the Library with the Main Program**
Compile and link `prog.c` with the static library:

```bash
cc -o prog prog.c libctest.a
```

This creates the executable `prog`.

---

## **3. Running the Program**

To execute the program, simply run the generated executable:

```bash
./prog
```

### **Expected Output**
If everything is set up correctly, the output should be:

```plaintext
Program started.
Function 1 from library.
Function 2 from library.
Program finished.
```

---

## **4. Cleaning Up**
To remove temporary files and reset the environment, use:

```bash
rm -f *.o libctest.a prog
```

---

## **5. Directory Structure**

```
project/
├── prog.c       # Main program
├── ctest1.c     # Library source file 1
├── ctest2.c     # Library source file 2
├── libctest.a   # Static library (generated)
└── README.md    # This documentation
```

---

## **6. Additional Notes**
- The `-Wall` flag is used to enable compiler warnings, helping identify potential issues in the code.
- To ensure compatibility, always check that the architecture of the object files matches the target system.

---

Here’s an explanation of the commands and flags used for creating and using a static library:

---

### **1. `cc`** (The C Compiler)
Used to compile C source files.

#### **Options:**
- **`-Wall`**: Enables most common compiler warnings to help catch potential errors in the code.
- **`-c`**: Compiles the source code into object files (`.o`) without linking.
  - Example: `cc -Wall -c ctest1.c` produces `ctest1.o`.

---

### **2. `ar`** (Archiver)
Used to create, modify, and extract contents of archive files (like static libraries).

#### **Options:**
- **`-c`**: Creates a new archive file.
- **`-v`**: Verbose mode, shows details of the operation performed (e.g., files being added).
- **`-q`**: Quickly appends files to the archive without extensive checking.
  - Example: `ar -cvq libctest.a ctest1.o ctest2.o` creates `libctest.a` from the object files.

#### Additional Commands:
- **`ar -t libctest.a`**: Lists the contents of the static library.

---

### **3. `-L` and `-l` Flags**
Used to specify libraries during linking.

#### **Options:**
- **`-L`**: Specifies the path to the directory containing the library.
  - Example: `-L/path/to/library-directory`
- **`-l`**: Specifies the library name (without the `lib` prefix or `.a` extension).
  - Example: `-lctest` links to `libctest.a`.

---

### **4. Linking with the Library**
- **Direct Linking**: If the library is in the current directory, include it directly in the command:
  ```bash
  cc -o prog prog.c libctest.a
  ```
- **Using `-L` and `-l`**: When the library is in a different directory:
  ```bash
  cc -o prog prog.c -L/path/to/library-directory -lctest
  ```

---

### **5. `./prog`**
- Executes the program (`prog`) generated after linking.

---

### **6. Cleaning Up**
- **`rm -f`**: Removes files without prompting for confirmation.
  - Example: `rm -f *.o libctest.a prog` cleans up all temporary files and the executable.

---

### Summary of Key Flags:
| **Command** | **Flag**   | **Purpose**                         |
|-------------|------------|-------------------------------------|
| `cc`        | `-Wall`    | Enable warnings for better debugging. |
| `cc`        | `-c`       | Compile to object files only (no linking). |
| `ar`        | `-cvq`     | Create and append files to a static library. |
| `ar`        | `-t`       | List contents of a library.         |
| `cc`        | `-L`       | Specify library directory.          |
| `cc`        | `-l`       | Link with a specific library.       |
| `rm`        | `-f`       | Force delete files without prompts. |

--- 

These commands are essential for creating, managing, and linking static libraries in C.