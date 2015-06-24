/*
The MIT License (MIT)

Copyright (c) 2015 Adam Simpson

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "split.h"
#include "print_macros.h"
#include "mpi.h"

int main(int argc, char **argv) {
  if (argc < 2)
    EXIT_PRINT("Please provide executalbe!\n");

  char **new_argv = &argv[1];
  int new_argc = argc - 1;

  // Cray MPI_Init seems to be doing something
  // that PMPI_Init doesn't, so we call it directly
  setenv("W_UNWRAP_INIT", "1", 1);
  MPI_Init(&new_argc, &new_argv);
  SplitInit();

  int child_status;
  pid_t child_pid = fork();

  if(child_pid == 0) { // Child process runs serial executable
    int err = execv(argv[1], new_argv);
    if(err)
      EXIT_PRINT("Failed to launch executable: %s!\n", strerror(errno));
  }
  else { // Parent process waits for child to complete
    waitpid(child_pid, &child_status, 0);

    MPI_Finalize();
    return child_status;
  }

}
