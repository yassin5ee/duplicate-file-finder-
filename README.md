# duplicate-file-finder-
# Description
The File Duplicate Finder is a C program designed to identify duplicate files within a specified directory and its subdirectories. It uses file content comparison through hashing to detect duplicates efficiently, regardless of file names or locations.
# fonctionality 
Input: The user specifies a root directory to start scanning.
Directory Traversal:
The program recursively explores all files and subdirectories within the given directory.
Hash Calculation:
For each file, the program reads its content and computes a hash value using a secure hash function (e.g., MD5 or SHA-256).
Duplicate Identification:
The program compares the computed hash values of all files.
Files with identical hashes are identified as duplicates.
Output:
Groups of duplicate files are displayed, listing their paths for easy access.
