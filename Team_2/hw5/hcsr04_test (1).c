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
    char *dev_name1 = "/dev/hcsr04_dev";
	
    int fd1 = -1;	;
    char c1,c2;
    int d;


    if( (fd1 = open(dev_name1, O_RDWR)) < 0 ) 
    {
        fprintf(stderr, "%s: unable to open %s: %s\n", app_name1, dev_name1, strerror(errno));		
        return( 1 );	
    }
   /* if( (fd2 = open(dev_name2, O_RDWR)) < 0 ) 
    {
        fprintf(stderr, "%s: unable to open %s: %s\n", app_name2, dev_name2, strerror(errno));		
        return( 1 );	
    }*/
    c1 = 1;
    write( fd1, &c1, 1 );
    read( fd1, &d, 4 );

    printf( "%d: %f\n", d,d/58.0 ); // show distance

   /* if (d < 20)
    {
        c2 = '1';
        write(fd2,&c2,1);
    }
    else
    {
        c2 = '0';
        write(fd2,&c2,);
    }*/

    close( fd1 );

    return 0;
}
