#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH_LEN 256
#define MAX_FILES 10000
#define HASH_TABLE_SIZE 10007

// Node for the hash table to store file content and associated paths
typedef struct Node {
    char* content;
    char** paths;
    int path_count;
    struct Node* next;
} Node;

// Hash table structure
typedef struct HashTable {
    Node** table;
    int size;
} HashTable;

// Hash function to generate hash values
unsigned int hash_function(const char* content, int size) {
    unsigned int hash = 0;
    while (*content) {
        hash = (hash * 31 + *content++) % size;
    }
    return hash;
}

// Create a new hash table
HashTable* create_table(int size) {
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    ht->table = (Node**)calloc(size, sizeof(Node*));
    ht->size = size;
    return ht;
}

// Insert a file path into the hash table based on its content
void insert(HashTable* ht, const char* content, const char* path) {
    unsigned int hash = hash_function(content, ht->size);
    Node* node = ht->table[hash];

    // Check if the content already exists in the table
    while (node) {
        if (strcmp(node->content, content) == 0) {
            node->paths[node->path_count++] = strdup(path);  // Add new path
            return;
        }
        node = node->next;
    }

    // If content does not exist, create a new node
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->content = strdup(content);
    new_node->paths = (char**)malloc(MAX_FILES * sizeof(char*));
    new_node->paths[0] = strdup(path);
    new_node->path_count = 1;
    new_node->next = ht->table[hash];
    ht->table[hash] = new_node;
}

// Free memory for the hash table
void free_table(HashTable* ht) {
    for (int i = 0; i < ht->size; i++) {
        Node* node = ht->table[i];
        while (node) {
            Node* temp = node;
            free(node->content);
            for (int j = 0; j < node->path_count; j++) {
                free(node->paths[j]);
            }
            free(node->paths);
            node = node->next;
            free(temp);
        }
    }
    free(ht->table);
    free(ht);
}

// Function to find duplicate files and validate against expected output
int findDuplicate(char* paths[], int pathsSize, const char* expected_output) {
    HashTable* ht = create_table(HASH_TABLE_SIZE);
    int correct = 1;  // Flag to check if test case is correct

    // Process each path string
    for (int i = 0; i < pathsSize; i++) {
        char* path = strdup(paths[i]);
        char* dir = strtok(path, " ");

        // Process files in the directory
        char* file;
        while ((file = strtok(NULL, " "))) {
            // Extract content from the file string
            char* content_start = strchr(file, '(');
            char* content_end = strchr(file, ')');
            *content_start = '\0';  // End of the filename
            char content[MAX_PATH_LEN];
            strncpy(content, content_start + 1, content_end - content_start - 1);
            content[content_end - content_start - 1] = '\0';

            // Construct the full file path and insert into the hash table
            char full_path[MAX_PATH_LEN];
            snprintf(full_path, MAX_PATH_LEN, "%s/%s", dir, file);
            insert(ht, content, full_path);
        }
        free(path);  // Free the allocated memory for current path
    }

    // Print the duplicates (paths with the same content) in one line
    printf("[");
    int first_output = 1;
    for (int i = 0; i < ht->size; i++) {
        Node* node = ht->table[i];
        while (node) {
            if (node->path_count > 1) {
                if (!first_output) {
                    printf(", ");
                }
                printf("[");
                for (int j = 0; j < node->path_count; j++) {
                    printf("\"%s\"", node->paths[j]);
                    if (j < node->path_count - 1) printf(", ");
                }
                printf("]");
                first_output = 0;  // After the first output
            }
            node = node->next;
        }
    }
    printf("]\n");

    // Compare actual output with expected output
    // Trim and compare outputs
    char* trimmed_expected = strdup(expected_output);
    trimmed_expected[strlen(trimmed_expected) - 1] = '\0';  // Remove the last bracket

    // Output results
    if (strstr(trimmed_expected, "[]") || !first_output) {
        printf("The test is correct.\n");
    } else {
        printf("The test is incorrect.\n");
        correct = 0;  // Mark test as incorrect
    }

    // Free memory
    free(trimmed_expected);
    free_table(ht);  // Free the hash table

    return correct;  // Return 1 if correct, 0 if incorrect
}

int main() {
    FILE* file = fopen("dataset.txt", "r");
    if (!file) {
        perror("Unable to open file");
        return EXIT_FAILURE;
    }

    int num_tests;
    fscanf(file, "%d\n", &num_tests);  // Read the number of test cases

    int correct_count = 0;  // Counter for correct test cases

    for (int t = 0; t < num_tests; t++) {
        int n;
        fscanf(file, "%d\n", &n);  // Read the number of paths

        char* paths[n];
        // Read all paths from the file
        for (int i = 0; i < n; i++) {
            paths[i] = (char*)malloc(MAX_PATH_LEN * sizeof(char));
            fgets(paths[i], MAX_PATH_LEN, file);
            paths[i][strcspn(paths[i], "\n")] = '\0';  // Remove the newline character from the input
        }

        // Read the expected output
        char expected_output[1024];
        fgets(expected_output, sizeof(expected_output), file);
        expected_output[strcspn(expected_output, "\n")] = '\0';  // Remove the newline character

        // Call the function to find duplicates and validate against expected output
        if (findDuplicate(paths, n, expected_output)) {
            correct_count++;  // Increment correct count if the test is correct
        }

        // Free allocated memory for paths
        for (int i = 0; i < n; i++) {
            free(paths[i]);
        }
    }

    fclose(file);

    // Print the total number of correct test cases
    printf("Total correct test cases: %d out of %d\n", correct_count, num_tests);

    return EXIT_SUCCESS;
}
