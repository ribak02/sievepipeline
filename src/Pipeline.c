/*
 * Pipeline.c
 *
 *  Created on: 26 Mar 2021
 *      Author: jonl
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "Pipeline.h"

Pipeline* new_Pipeline() {
    Pipeline *this = malloc(sizeof(Pipeline));
    this->funcs = malloc(0);
    this->count = 0;
    return this; 
}


bool Pipeline_add(Pipeline* this, Function f) {
    this->funcs = realloc(this->funcs, (this->count + 1) * sizeof(Function));
    this->funcs[this->count] = f;
    //printf("\nCount: %i\n", this->count); --debugging
    this->count++;
    //printf("Funcs: %p ", this->funcs[this->count-1]); --debugging
    return true;
}


void Pipeline_execute(Pipeline* this) {
    pipe(this->fd);
    for (int i=0;i<this->count+1;i++) {
        int child = fork();
        // error
        if (child < 0) {
            printf("Fork error");
            exit(1);
        }
        // child
        if (child == 0) {
            this->funcs[i](this->fd[0], this->fd[1]);
            //printf("fd: %i %i\n", this->fd[0], this->fd[1]); --debugging
            exit(0);
        }
        // parent
        else {
            wait(NULL); // wait for child to exit
        }
    }
}


void Pipeline_free(Pipeline* this) {
    free(this);
    free(this->funcs);
}