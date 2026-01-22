# KeyHunter
A lightweight C utility that recursively scans directories and subdirectories (including hidden folders) to locate specific alphanumeric strings or keys.

# 🔍 KeyHunter (Recursive String Searcher)

A lightweight, robust C command-line tool designed to recursively traverse directory trees and locate specific alphanumeric strings or keys.

## 🚀 Features

* **Deep Recursion:** Automatically traverses through all subdirectories from a given path.
* **Hidden File Support:** explicitly scans hidden files and directories (those starting with `.`), ensuring no config file or secret is missed.
* **Line-Level Precision:** Outputs the specific line number and content where the match was found.
* **Error Handling:** Gracefully skips directories with denied permissions without crashing.
* **Standard Library:** Built using POSIX standard libraries (`dirent.h`), requiring no external dependencies on Linux/macOS.

## 🛠️ Prerequisites

* **OS:** Linux, macOS, or Windows (via WSL or MinGW).
* **Compiler:** GCC (GNU Compiler Collection) or Clang.

## 📥 Installation

1.  **Clone the repository:**
    ```bash
    git clone [https://github.com/sidshinde510/recursive-key-finder.git](https://github.com/sidshinde510/recursive-key-finder.git)
    cd recursive-key-finder
    ```

2.  **Compile the source code:**
    ```bash
    gcc main.c -o keyfinder
    ```

## 💻 Usage

Run the executable from your terminal:

```bash
./keyfinder
