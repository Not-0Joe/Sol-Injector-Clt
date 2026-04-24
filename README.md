# Sol-Injector

Sol-Injector is a lightweight Windows command-line tool with a basic UI designed for listing active system processes and performing DLL injection.

## Getting Started

You can get Sol-Injector running on your machine by either downloading the latest pre-compiled binary or by building the source code yourself.

To use Sol-Injector, choose an option from the main menu to select a target process:

* **0**: Find target process via PID.
* **1**: Find target process via Name.
* **2**: List all running process names and PIDs.
* **3**: Copy the community Discord link to the clipboard.

### Main Menu:
<img width="1100" height="578" alt="Screenshot 2026-04-24 101511" src="https://github.com/user-attachments/assets/c77d6d7e-b12b-4a0d-9b63-15b90de5707f" />

Once you have selected a target process, choose one of the available injection methods:

<img width="766" height="278" alt="Injection Methods Screenshot" src="https://github.com/user-attachments/assets/0b77a676-e861-4e7f-b7ce-8f6deb062401" />

After selecting an injection method, provide the path to the Dynamic Link Library (DLL) you wish to use, and it will be injected into the target process.

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

