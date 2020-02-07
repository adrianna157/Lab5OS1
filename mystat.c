#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <xlocale.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>

struct stat mystat;
void print_mode(mode_t mode);
char *strf_time_converter(char *date, time_t time);

char *strf_time_converter(char *date, time_t time) {
    strftime(date, 101, "%Y-%m-%d %H:%M:%S %z (%Z) %a", localtime(&time));
    return date;
}

void print_mode(mode_t mode){
    printf("  Mode: ");
    printf( (S_ISDIR(mode)) ? "d" : "-");
    printf( (mode & S_IRUSR) ? "r" : "-");
    printf( (mode & S_IWUSR) ? "w" : "-");
    printf( (mode & S_IXUSR) ? "x" : "-");
    printf( (mode & S_IRGRP) ? "r" : "-");
    printf( (mode & S_IWGRP) ? "w" : "-");
    printf( (mode & S_IXGRP) ? "x" : "-");
    printf( (mode & S_IROTH) ? "r" : "-");
    printf( (mode & S_IWOTH) ? "w" : "-");
    printf( (mode & S_IXOTH) ? "x" : "-");


    printf(" %o", (unsigned) (mode & 0777));


    printf("\n");

}


int main(int argc, char* argv[]){
    int i; 
    char date[50];
    
    // struct tm *info;
   

    // time( &rawtime );

    // info = localtime( &rawtime ); 

    // strftime(buffer, 20, "%Y-%m-%d %H:%M:%S %z (%Z) %a", localtime(&time));
    // printf("Formatted date & time : |%s|\n", buffer );



    for(i = 1; i < argc; i++){
        

        struct passwd *username = getpwuid(mystat.st_uid);
        struct group *group_name = getgrgid(mystat.st_gid);
        lstat(argv[i], &mystat);

        printf("File: %s\n", argv[i]);
        printf("  File type:                ");
        

           switch (mystat.st_mode & S_IFMT) {
           case S_IFBLK:  printf("block device\n");            break;
           case S_IFCHR:  printf("character device\n");        break;
           case S_IFDIR:  printf("directory\n");               break;
           case S_IFIFO:  printf("FIFO/pipe\n");               break;
           case S_IFLNK:  printf("symlink\n");                 break;
           case S_IFREG:  printf("regular file\n");            break;
           case S_IFSOCK: printf("socket\n");                  break;
           default:       printf("unknown?\n");                break;
           }
	    printf("  Device ID: %u\n", (unsigned) mystat.st_dev);
	    //printf("regular file\n");
        printf("  I-node number: %u\n",(unsigned) mystat.st_ino);
        print_mode(mystat.st_mode);
        printf("  Link count: %u\n",(unsigned) mystat.st_nlink);
        printf("  Owner ID: %s    %u\n", username->pw_name,(unsigned) mystat.st_uid);
        printf("  Group ID: %s %u\n", group_name->gr_name,(unsigned) mystat.st_gid);
        printf("  File size : %u\n", (unsigned) mystat.st_blksize);
        printf("  Blocks allocated : %u\n", (unsigned) mystat.st_blocks);
        printf("  Last file accessed : %s\n", strf_time_converter(date, mystat.st_atime));
        printf("  Last file modification : %s\n", strf_time_converter(date, mystat.st_mtime));
        printf("  Last status change : %s\n", strf_time_converter(date, mystat.st_ctime));


    }

    return 0;
}

