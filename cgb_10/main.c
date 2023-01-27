#include <stdio.h>
#include "graphics.h"

/* A `void` inside a parameter list means the corresponding function has no parameters. */
/* TODO: What does an empty parameter list mean? */
int main(void)
{
    printf("Engine starting...\n");

    int result = startGraphics(1280, 720);

    printf("Engine terminated.\n");

    return result;
}