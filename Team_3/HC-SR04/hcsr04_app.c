#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv)
{	
    char *app_name1 = argv[0];	
    char *dev_name1 = "/dev/hcsr04_etx_device";
	
    int fd1 = -1;	;
    char c;
    int d;


    if( (fd1 = open(dev_name1, O_RDWR)) < 0 ) 
    {
        fprintf(stderr, "%s: unable to open %s: %s\n", app_name1, dev_name1, strerror(errno));		
        return( 1 );	
    }
	
    c = 1;
    write( fd1, &c, 1 );
    read( fd1, &d, 4 );

    printf( "Distance: %f\n", d/58.0 );

    close( fd1 );

    return 0;
}
