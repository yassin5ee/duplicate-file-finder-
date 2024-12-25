This is the readme file that contains a full description of the code giving it's general purpose 
and explaining how each function in the MAIN code works and why we need it in the first 
place while covering it's time and space complexity.

Purpose of the project:
The goal of this project is to detect duplicate files among a multitude of files that 
the user provides; but these files don't actually exist in the user's pc so the content of each file
must be written besides the path of that file; here is a detailed explanation :
first the user enters the path of a file (that we are going to call the main file) in the MAIN code 
exactly at the line 133,meaning that when you launch the code you won't have to enter the name of any
directories or files to search for duplicate files in them as everything is written in the text file 
you provide. Thus the programme shows you directly the results upon launching.
and this file must follow a very strict syntax :
-the first line only includes the number of lines the file contains 
(excluding the first line)
-each other line must follow this terminology :             ( directory_1 file.txt_1 
                                                              directory_2 file.txt_3 file.txt_4 file.txt_5
                                                              directory_3 file.txt_6 file.txt_7
                                                              ... )
however this is an example since each directory may lead to as many text files as the user wants
Notes : -a directory must not lead to other directories in it; it must lead to text files only.
        -each file is written in this manner ( name_of_file ( content_of_file ))
        - each line must have a distinct directory meaning that you can't have this form :
        ( directory_1 file.txt_1 
          directory_2 file.txt_3 
          directory_2 file.txt_4 file.txt_5
          directory_3 file.txt_6 file.txt_7
          ... )



How the code works ?
there is a total of 6 functions used in this project and they are :
-MAIN (which calls :)
   -FIND DUPLICATE (which calls :)
      -CREATE TABLE
      -INSERT (which calls :)
         -HASH FUNCTION
      -FREE TABLE
let's explain each one of them now...
MAIN :
   A) The file that has it's name written in line 133 must be read:
      1) The file that the user provided is opened 
      2) An array whose length is equal to the number of lines the main file contains is created.
      the nth element of paths will contain the entirety of the nth line of the main file,
      however the last element of each line (which is "\n" ) must be removed 
      3) The file is closed
   B) FIND DUPLICATE function is called :
      1) CREATE TABLE function is called to create a hash table
      ---------------------------------------------------------------------------------------------------
      why do we need a hash table in the first place ?
      We know that some files in the main file share the same content; so we must create a data 
      structure that stores all the distinct contents of the main file, and each content will be
      associated with the list of paths of files that share that exact content ; so each distinct 
      content will be identified by it's hash value. However, hash values aren't perfect as 2 or more
      distinct files may share the same hash value. 
      So to make things simple : 
      -the length of the hash table is equal to the number of hash values that can possibly be created.
      -each element of the hash table corresponds to a hash value and for each hash value we have a 
      linked list that's formed of nodes. a node is a structure that includes:
            -A content
            -A list of paths of the files that share that content 
            -The length of that list
            -A pointer that points to the next element of the linked list
      REMINDER : All the contents that are in the same linked list have the same hash value.
      -Then this hash table will be scanned by traversing all hash values
          -for each hash value we will traverse the entire linked list associated with it.
              -each node of a single linked list will be analyzed :
              in one node, if the list of paths has 2 elements or more this means that these files share
              the same content so their paths must be printed out.
      ---------------------------------------------------------------------------------------------------
      As we said; create table function is called to create a hash table whose length is equal to the 
      number of lines in the main file, meaning the number of directories.
      Each element of the hash table corresponds to a multitude of contents that share the same hash 
      value.
      2) a) Now we will try to insert the content and path of each file of the main file to this hash 
      table, and here are the required steps to do that :
      -Traverse the paths array until the last element
            -For each element of the array (which corresponds to a line in the main file) : since the 
            element is written in this fashion : 
            directory_n path_of_file_j (content_of_fie_j) path_of_file_j+1 (content_of_file_j+1)...
            we must split the element into separate strings based on a separator which is spacebar.
            And now in order to insert the path and the content of each file belonging to this directory 
            into the hash table, here are the steps:
            -All these created strings must be traversed (except for the string containing the directory)
                  -For each string we must locate the '(' and ')' characters to distinguish between the
                  path section and the content section of the file
                  -The path section will be concatenated with the directory to construct the full path of
                  the file.
                  2) b) The INSERT function is called to insert the full path and the content of the file 
                  into the hash table :
                  -The HASH FUNCTION function is called to calculate the hash value of that content
                  -In the hash table if there is a linked list that corresponds to that hash value; it 
                  will be traversed to find the node that has the same content :
                        -If we find that node; the path of our file will be added to the list of paths of 
                        that node
                        -If not we simply create a new node in this linked list where we insert the 
                        content and the path and this node will be the head of the linked list.
                  -If there isn't a linked list corresponding to this hash value; a new linked list will
                  be created and the node that we create from the content and path of our file will be 
                  the head and the only element of this linked list.
                  NOTE: during this , in the node where our file will exist the number of paths 
                  associated to our content will be incremented by one.
      3) After inserting every file into the hash table we will print out all the duplicate files and to 
      do that we have to :
      -Traverse our hash table by scanning every hash value
            -For a given hash value we will traverse the entire linked list corresponding to it by 
            scanning each node
                  -For a given node if the number of paths related to it is bigger than 1, all these 
                  paths will be printed out to the screen
      4) FREE TABLE function is called to free up all the space used by the hash table. the steps to do 
      that are :
      -Traverse the hash table with hash values
            -For a given hash value traverse the associated linked list 
                  -For each node:  -free up the content and each element of the paths array
                                   -Free up the paths array itself
      -Free up the hash table itself
   C) Free up each element of the array paths which stores each line of the main file 




Complexity of the code :
Time complexity : Let's suppose that 
-n is the number of directories (number of lines in the main file)
-L is the average length of a line in the main file (called path)
-Lp is the average length of the path of a file (a file has the following structure ): 
name_of_file(content_of_file)
-p is the average number of files in a directory
-N is the number of nodes ( meaning unique contents )
-K is the number of duplicates
And assuming that no collisions happen meaning that two distinct contents can't have the same  hash value
( which is the average scenario ) then the total time complexity is :
O(N + K*Lp + n*p*L)
Space complexity : 
O(n*MAX_FILES*MAX_PATH_LEN) where n is the number of directories (number of lines in the main file)


__________________________________________________________________________________________________________________________________________________________________


#deep explanation of each line of the code
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH_LEN 256
#define MAX_FILES 10000
#define HASH_TABLE_SIZE 10007

// Node for the hash table to store file content and associated paths
typedef struct Node {
    char* content;    //a pointer to a character and it represents the string (content) which refers to the content that all the paths following share
    char** paths;    //a pointer to the string char* and it represents an array of strings and it stores all the paths that share the same content
    int path_count;    //an integer that represents the number of paths that have the same content 
    struct Node* next;    //a pointer to another node which means that a single node can represent a linked list that contains many contents that share the same hash value (known as collisions) ,each one with its corresponding list of paths
} Node;

// Hash table structure
typedef struct HashTable {
    Node** table;    //a pointer to a Node* and it represents an array of pointers, with each one pointing to a Node structure
    int size;    //an integer that represents how many nodes HashTable contains which is equal to the number of different contents given
} HashTable;

------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Hash function to generate hash values
unsigned int hash_function(const char* content, int size) {
    //content: A pointer to a null-terminated string to be hashed.
    //size: The range within which the hash value should lie. The computed hash is taken modulo this value.
    unsigned int hash = 0;    //an integer that enables us to calculate the hash of a string (content) and it is initialized to 0
    while (*content) {    //with each iteration the hash value is updated and the pointer content advances to the next character until the pointer reaches the null operator
        hash = (hash * 31 + *content++) % size;    //the formula with wich hash is calculated
    }
    return hash;
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Create a new hash table
HashTable* create_table(int size) {   
    // size:the size of the hash table and it refers to the number of distinct contents detected 
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));    //Dynamically allocates memory for a HashTable structure (ht)
    ht->table = (Node**)calloc(size, sizeof(Node*));    //Allocates memory for (size) buckets, each capable of holding a Node*.
    ht->size = size;    //size parameter is stored in the (ht->size) field of the hash table structure.
    return ht;
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Insert a file path into the hash table based on its content
void insert(HashTable* ht, const char* content, const char* path) {
    // ht :a pointer to the hash table where the data will be stored
    // content :a string representing the content of the path
    // path :a string representing the file path associated with the content
    unsigned int hash = hash_function(content, ht->size);    //calculates the hash value of (content)
    Node* node = ht->table[hash];

    // Check if the content already exists in the table
    while (node) {    //The function checks if there is already a node at the calculated hash index (ht->table[hash]).
    //It starts iterating through the linked list at that index (if the list exists at all, meaning if ht->table[hash]!=NULL) using the while loop.
        if (strcmp(node->content, content) == 0) {    //checks if the current node from the current linked list contains the same content.
            node->paths[node->path_count++] = strdup(path);  //a match is found, the new path is added to the paths array of that node.
            return;
        }
        node = node->next;    //we move on to the next node of the linked list until node==NULL or a node that contains the same content is found
    }

    // If content does not exist, create a new node
    Node* new_node = (Node*)malloc(sizeof(Node));    //A new Node structure is allocated using malloc
    new_node->content = strdup(content);     //Copies the content into the node's content field
    new_node->paths = (char**)malloc(MAX_FILES * sizeof(char*));    //Allocates an array of pointers (char**) to store file paths. The array can hold up to MAX_FILES paths
    new_node->paths[0] = strdup(path);    //Stores the first file path in the paths array
    new_node->path_count = 1;    //the number of paths in the paths array is set to 1
    new_node->next = ht->table[hash];    //Points new_node to the current head of the linked_list at the hash index (index)
    ht->table[hash] = new_node;    //the hash table is updated and new_node is the head of the linked list at the hash index (hash)
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Frees memory for the hash table
void free_table(HashTable* ht) {
    // ht :pointer to the HashTable to be freed
    for (int i = 0; i < ht->size; i++) {    //the loop iterates through all possible buckets in the hashtable(since there are (size) possible hash indexes, there are (size) buckets)
        Node* node = ht->table[i];    //node is initialized as the head of the linked list at hash index[j]
        while (node) {    //For each bucket, it iterates through the linked list of nodes (if it exists at all) at the hash index(j)
            Node* temp = node;    //The temp pointer temporarily stores the current node.
            free(node->content);    //The content field of the node is freed using free
            for (int j = 0; j < node->path_count; j++) {    //The loop iterates over each string in the paths array and frees it.
                free(node->paths[j]);  
            }
            free(node->paths);    //the pointer (paths) which used to store all paths is freed
            node = node->next;    //the pointer (node) is updated to the next node in the linked list at the hash index (i).
            free(temp);   //the currnet node is freed
        }
    }
    free(ht->table);    //the HashTable structure itself is freed.
    free(ht);    //the ht pointer is freed
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Function to find duplicate files
void findDuplicate(char** paths, int pathsSize) {
    //paths :a pointer to a char* and it refernces an array of strings; each string represents a directory and the name of the files in that directory along with their content 
    //pathsSize :the number of paths in the array (paths)
    HashTable* ht = create_table(HASH_TABLE_SIZE);    //a hash table is initialized with a size constant HASH_TABLE_SIZE.

    // Process each path string
    for (int i = 0; i < pathsSize; i++) {    //The function loops through each directory in paths
        char* path = strdup(paths[i]);    //creates a copy of the current directory path
        char* dir = strtok(path, " ");    //splits the path string by spaces to extract the directory name, which will then be stored in (dir)

        // Process files in the directory
        char* file;    //a pointer to a character and it references a string
        while ((file = strtok(NULL, " "))) {    //This loop processes each file within the current directory ;strtok continues tokenizing the string (path) (separating files in the directory).
            // Extract content from the file string
            char* content_start = strchr(file, '(');    //finds the position of the opening parenthesis
            char* content_end = strchr(file, ')');    //finds the position of the closing parenthesis
            *content_start = '\0';    // End of the filename
            char content[MAX_PATH_LEN];    //string of max length : MAX_PATH_LEN
            strncpy(content, content_start + 1, content_end - content_start - 1);    //The content between the parentheses is copied to the string (content)
            content[content_end - content_start - 1] = '\0';    //the end of the string (content) is precised

            // Construct the full file path and insert into the hash table
            char full_path[MAX_PATH_LEN];    //string of max length : MAX_PATH_LENGTH
            snprintf(full_path, MAX_PATH_LEN, "%s/%s", dir, file);    //the full path of the current file is constructed by concatenating (dir) and (file)
            insert(ht, content, full_path);    //the content and its full path are added into the hashtable
        }
        free(path);  // Free the allocated memory for current path
    }
    
    // Print the duplicates (paths with the same content)
    printf("[\n");    
    for (int i = 0; i < ht->size; i++) {    //the function iterates through the hashtable
        Node* node = ht->table[i];    //
        while (node) {    //this loop goes through all the nodes in the linked list of the hash index i
            if (node->path_count > 1) {    //if a node has more than 1 path (meaning that at least 2 files share the content of this node)
                printf("  [");
                for (int j = 0; j < node->path_count; j++) {    // the full paths that are stored in the array (paths) of the current node will be printed
                    printf("\"%s\"", node->paths[j]);
                    if (j < node->path_count - 1) printf(", ");(    //if the last full path that was printed isnt the last in the array (paths): it will be followed by ','
                }
                printf("],\n");    
            }
            node = node->next;    //we move to the next node in the current linked list
        }
    }
    printf("]\n");
    free_table(ht);  // Frees the hash table
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main() {
    FILE* file = fopen("C:/dossier/test.txt", "r");    //The program tries to open the mentioned file in read mode ("r").
    if (!file) {    //if the file cannot be opened, fopen returns NULL
        perror("Unable to open file");    //the program prints an error message using perror
        return EXIT_FAILURE;    //the program exits with EXIT_FAILURE
    }
    int n;
    fscanf(file, "%d\n", &n);  // Reads the number of directories which is the first thing written in the file
    char* paths[n];    //an array of char* and it represents the array in which all the directories along with their files and the content of these files will be stored
    
    // Read all paths from the file
    for (int i = 0; i < n; i++) {    //the program iterates through all the n directories
        paths[i] = (char*)malloc(MAX_PATH_LEN * sizeof(char));    //allocates memory for the pointer paths[i]
        fgets(paths[i], MAX_PATH_LEN, file);    //reads all the directory
        paths[i][strcspn(paths[i], "\n")] = '\0';  // Removes the newline character from the paths[i]
    }
    fclose(file);    //the program closes the file with fclose(file) to free up the resources associated with it.

    // Calls the function to find duplicates
    findDuplicate(paths, n);
                                
    // Frees the allocated memory associated with the array paths
    for (int i = 0; i < n; i++) {
        free(paths[i]);
    }
    return 0;
}
