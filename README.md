# Employee Management System (C)

A menu-driven console program written in C for practicing structures, file handling, searching, sorting, and basic employee record management.

## Current functionality

The source code includes operations for adding employee records, searching by employee ID, listing employees by department, displaying records, updating/deleting records, and using salary/rating data in calculations.

The program uses an `Employee` structure and references a local data file named `Employee.txt` for persistence. Review the source code for the exact menu and current implementation details.

## Build and run

You need a C compiler such as GCC.

**Windows (MinGW-w64 installed)**
```powershell
gcc code.c -o employee-management.exe
.\employee-management.exe
```

**macOS/Linux**
```bash
gcc code.c -o employee-management
./employee-management
```

Run the executable in a writable directory so the program can create or update its local employee data file.

## Concepts practiced

- C structures and arrays
- Functions and pointers
- File I/O
- Searching and sorting
- Basic algorithmic problem solving

## Limitations

This is a learning project. Validate user input and back up any local data file before using it; it is not intended for real employee or payroll data.
