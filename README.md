# 📜 get_next_line

**get_next_line** is a project that implements a function to read a single line from a file descriptor, regardless of its length. It’s designed to handle edge cases like very large files, varying buffer sizes, and simultaneous reads from multiple file descriptors.

---

## 🛠️ Features

### **Mandatory Part**
- The function `get_next_line` reads and returns one line at a time from a given file descriptor.
- Handles:
  - Files of any size.
  - Customizable buffer size (defined at compile time with `BUFFER_SIZE`).
  - Multiple calls to `get_next_line` to read subsequent lines until EOF.

### **Bonus Part**
- Supports simultaneous reading from multiple file descriptors.
- Efficient memory usage to handle overlapping and large reads.
- Works seamlessly with different buffer sizes and file types.

---

## 🎯 Objectives

- Implement a function capable of reading a single line from a file descriptor.
- Efficiently manage memory using dynamic allocation.
- Handle edge cases such as empty files, varying buffer sizes, and multi-FD reading.
- Gain a deeper understanding of file I/O in C and how to manage state across function calls.

---
