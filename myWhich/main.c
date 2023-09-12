#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char** argv) { // also known as: char* argv[]

//FOURTH BULLET pt1
int file_exists(const char *path)
{
    // Check if the file exists and is executable
    if (access(path, X_OK) == 0)
        return 1;
    else
        return 0;
}

// SECOND BULLET 
// Checking to see if there is at least one argument, and if not, returning argv[0]
    if (argc < 2)
    {
        printf("Only argument entered: %s\n", argv[0]);
        return 1;
    }

    // Checking if the first argument is the -a flag, and if not, continuing without it
    int a_check = 0;
    if (strcmp(argv[1], "-a") == 0)
    {
        a_check = 1;
        // Shifting the argument list which skips the -a flag
        argv++;
        argc--;
        // Checking if there is at least one more argument after the shift is done
        if (argc < 2)
        {
            printf("Usage: %s [-a] executable_name\n", argv[0]);
            return 1;
        }
    }


    // FIRST BULLET pt1
	// Get the PATH
    char *pPath = getenv("PATH");
    if (pPath == NULL)
    {
        printf("PATH environment variable not found.\n");
        return 1;
    }
    
    // FIRST BULLET pt2
    // Split the PATH into individual directories
    // Most of the code below was modelled after what was given in lecture
    char *token;
    char *path_copy = strdup(pPath); // Make a copy since strtok modifies the original string
    /*
    I had some troubles using strcpy, so I look on cplusplus.com and found strdup which essentially works the same
    but allocates memory
    */
    token = strtok(path_copy, ":");

    // THIRD BULLET
    int found[argc - 1];             // I added this array to be able to keep track of how many arguments were put in,
                                     // because I got really stuck at one point when doing multiple arguments without using a flag
    memset(found, 0, sizeof(found)); // Setting the array to 0
                                     // This line is taken from stack overflow. https://stackoverflow.com/questions/20161179/usage-of-memset-in-c
    int all_found = 1;         // Declaring a variable to see if all the arguments were read in
    while (token != NULL)
    {
        // Looping through each command-line argument and checking if it exists in the current directory
        for (int i = 0; i < argc - 1; i++)
        {
            if (found[i])
                continue; // I implemented this conditional to work when the loop goes through after
                    // originally finding the first location of the executable
}

// BULLET 4 pt2
    char executable_path[1024]; 
        snprintf(executable_path, sizeof(executable_path), "%s/%s", token, argv[i + 1]);
        // had some troubles for a while figuring out why I was getting an error with printf
        // had to use snprintf to avoid something with a buffer
            if (file_exists(executable_path))
            {
                printf("%s\n", executable_path);
                found[i] = 1;
            }
        }

        token = strtok(NULL, ":"); // consulted stack overflow to see why strtok had to be     stated again, was very difficult figuring out how this function works
    }

    // Check if all arguments are found
    for (int i = 0; i < argc - 1; i++)
    {
        if (!found[i])
        {
            all_found = 0;
            break;
        }
    }

    if (!all_found)
    {
        printf("Some arguments were not found in the PATH or are not executable.\n");
    }

    free(path_copy); // Free the memory allocated for the copied PATH

    return 0;
