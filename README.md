===========================
Calling Python from C Guide
===========================

Project Overview:
-----------------
This project demonstrates how to use the Python C API to call Python functions from C code. It includes:
- main.c
- py_interaction.c
- py_interaction.h
- c_interaction.py

The C program starts a Python interpreter, passes data, and receives typed responses like integers, floats, strings, booleans, and dates.

===================
Setting Up Python.h
===================

To get the Python.h header and link Python properly, follow these steps:

1. Install Python:
   ----------------
   - Download from: https://www.python.org/
   - During installation, make sure to check:
     [✔] Add Python to PATH

2. Locate Python install path:
   ----------------------------
   Example location: 
   C:\Users\YourName\AppData\Local\Programs\Python\PythonXY  
   (Replace "XY" with your actual version, e.g., Python311 or Python310)

3. How to find the `include` and `libs` directories:
   --------------------------------------------------
   - Navigate to your Python install directory:
     Example: `C:\Users\YourName\AppData\Local\Programs\Python\PythonXY`
   - Inside, look for:
     • `include\` folder → contains `Python.h`  
     • `libs\` folder → contains `pythonXY.lib`

   If you’re unsure where Python is installed:
   - Open Command Prompt and type:
     ```bash
     python -c "import sys; print(sys.executable)"
     ```
   - This will give you the full path to the Python executable.
   - From there, go up one folder level to find `include` and `libs`.

4. Configure Code::Blocks:
   ------------------------
   - Go to: Settings → Compiler
   - Select the "Search directories" tab:
     • Under **Compiler**, add:
       C:\Path\To\PythonXY\include
     • Under **Linker**, add:
       C:\Path\To\PythonXY\libs

   - Then go to: Project → Build options → Linker settings
     • Click "Add" and type:
       pythonXY
     (Example: python311 for Python 3.11, python310 for Python 3.10)

5. If using gcc/MinGW directly:
   -----------------------------
   Compile with:
   gcc main.c py_interaction.c -IC:\Path\To\PythonXY\include -LC:\Path\To\PythonXY\libs -lpythonXY -o my_program.exe

6. Make sure `pythonXY.lib` exists:
   ---------------------------------
   Found in: C:\Path\To\PythonXY\libs

=====================
Running the Program
=====================

1. Place `c_interaction.py` in the same directory as your executable or source files.
2. Compile the project as described above.
3. Run the compiled `.exe` file.
4. The program will:
   - Start the embedded Python interpreter
   - Call Python functions that return generated data
   - Print results interpreted by their data types

=====================
Common Issues
=====================

- ❌ `fatal error: Python.h: No such file or directory`  
  → Check the "include" path is set to your PythonXY/include directory.

- ❌ `undefined reference to _Py...`  
  → Make sure `pythonXY.lib` is in your linker settings and matches your Python version/architecture.

- ❌ `ModuleNotFoundError: No module named 'c_interaction'`  
  → Ensure `c_interaction.py` is in the same directory and named correctly (no double `.py` extensions).

=====================
Tips
=====================

- Use the same architecture (32-bit or 64-bit) for both Python and your compiler.
- Restart Code::Blocks if you change environment variables like PATH.

You're all set. Build, run, and enjoy the power of mixing C with Python 🚀
