# Sol-Injector

# [NOT BEING WORKED ON] 

## This project was a learning milestone to explore the Windows API and low-level programming the code remains messy despite refactoring, but it is shared as guide for other learners—use it however you like, but expect bugs. the core injection logic is functional but the error handling could be improved and the whole project could be made alot more modular and less redundant

Sol-Injector is a lightweight Windows command-line tool with a basic UI designed for listing active system processes and performing DLL injection.

## Getting Started

You can get Sol-Injector running on your machine by either downloading the latest pre-compiled binary or by building the source code yourself.

To use Sol-Injector, choose an option from the main menu to select a target process: 
Then select the injection option and choose ur target dll

* **1**: Find target process via PID.
* **2**: List all running process names and PIDs.
* **3**: Copy the community Discord link to the clipboard.

## Prerequisites

* **OS**: Windows 10/11
* **Permissions**: Administrator privileges (required for process access and injection).
* **Build Tools**: [Visual Studio 2022](https://visualstudio.microsoft.com/) (if compiling from source) with the "Desktop development with C++" workload.
* **Git**: [Git](https://git-scm.com/) is required if you are cloning the source files.

## Installation

### Option 1: Download Pre-compiled Binary
1. Go to the [Releases Page](https://github.com/Not-0Joe/Sol-Injector-Clt/releases).
2. Download the latest `.exe` file.
3. **Run as Administrator** to ensure the tool has permission to interact with other processes.

### Option 2: Build from Source
1. Create a folder where you would like to store the project.
2. Open a terminal in that location and run:
3. ```bash
   git clone [https://github.com/Not-0Joe/Sol-Injector-Clt.git](https://github.com/Not-0Joe/Sol-Injector-Clt.git)```
5. open the sln file in visual studio code
6. set build to release
7. Set the architecture to x64.
8. build the solution
9. built binary will be found in /"repo"/x64/Release 

