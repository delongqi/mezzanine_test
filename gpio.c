#include <stdio.h>
#include <stdlib.h>

#include "libsoc_gpio.h"
#include "libsoc_debug.h"

#define GPIO_CS 13

int main()
{
    int i = 0;
    gpio *gpio_cs;  
    libsoc_set_debug(0);
    gpio_cs = libsoc_gpio_request(GPIO_CS,LS_SHARED);
    if(gpio_cs == NULL)
    {
	goto fail;
    }
    libsoc_gpio_set_direction(gpio_cs,OUTPUT);
    if(libsoc_gpio_get_direction(gpio_cs) != OUTPUT)
    {
	printf("Failed to set direction to OUTPUT\n");
	goto fail;
    }
   for(i = 0;i < 5;i++ )
   {
	libsoc_gpio_set_level(gpio_cs,HIGH);
 	usleep(1000000);
	libsoc_gpio_set_level(gpio_cs,LOW);
	usleep(1000000);
   }
   fail:
   if(gpio_cs)
   {
	libsoc_gpio_free(gpio_cs);
   }
   return EXIT_SUCCESS;
}

