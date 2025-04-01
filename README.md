# 📂 File Viewer in C

A simple interactive file viewer written in C that allows users to open `.txt` files and display their contents in either **ASCII** or **Hexadecimal** format.

---

## 🚀 Features

- Terminal-based interactive menu
- Opens and validates `.txt` files
- Displays file contents in:
  - ASCII format (non-printable characters handled)
  - Hexadecimal format (with memory address-style layout)
- Input validation and error handling
- Loop-back menu for multiple file inspections

---

## 🧠 Technologies

- Language: C (C11 standard)
- Libraries: `<stdio.h>`, `<stdlib.h>`, `<string.h>`, `<unistd.h>`, `<fcntl.h>`

---

## 🛠️ Compilation & Execution

### Compile
```bash
gcc -std=c11 -Wall view_f.c
