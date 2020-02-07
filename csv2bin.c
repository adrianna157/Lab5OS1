#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <xlocale.h>
#include <stdlib.h>
#include <sys/types.h>
#include "file_struct.h"
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#define BUFFER_SIZE 1000
#define MAX_LINE 80

int main(int argc, char *argv[])
{

  char *filename = NULL;
  FILE *iFile = stdin;
  int c;
  char *outname;
  int outfile = STDOUT_FILENO;

  while ((c = getopt(argc, argv, "i:o:hv")) != -1)
  {
    switch (c)
    {
    case 'i':
      filename = optarg;
      iFile = fopen(optarg, "r");
      if (iFile == NULL)
      {
        fprintf(stderr, "Error: the file %s\n", optarg);
      }
      exit(2);
      break;
    case 'o':
      outname = optarg;
    
      outfile = open(outname, O_RDONLY | O_RDWR | O_CREAT, S_IWUSR | S_IRUSR);

        break;
      case 'h':
        //cvalue = optarg;

        {
          printf("h: help \n");
          printf("i: input file name \n");
          printf("o: name of output file \n");
          printf("v: verbose mode \n");
        }
        break;

      case 'v':
        printf("v flag enabled \n");
        break;
      case '?':
        fprintf(stderr,
                "Unknown option character `\\x%x'.\n",
                optopt);
        return 1;
      default:
        exit(2);
      }
    }
      {
        char buff[BUFFER_SIZE] = {0};
        char *token = NULL;
        file_struct_t s;
        char delims[] = ",\n";
        
        fgets(buff, BUFFER_SIZE, iFile);
        while (fgets(buff, BUFFER_SIZE, iFile) != NULL)
        {
          memset(&s, 0, sizeof(s));

          token = strtok(buff, delims);
          strcpy(s.id, token);

          token = strtok(NULL, delims);
          strcpy(s.fname, token);

          token = strtok(NULL, delims);
          strcpy(s.mname, token);

          token = strtok(NULL, delims);
          strcpy(s.lname, token);

          token = strtok(NULL, delims);
          strcpy(s.street, token);

          token = strtok(NULL, delims);
          strcpy(s.city, token);

          token = strtok(NULL, delims);
          strcpy(s.zip, token);

          token = strtok(NULL, delims);
          strcpy(s.country_code, token);

          token = strtok(NULL, delims);
          strcpy(s.email, token);

          token = strtok(NULL, delims);
          strcpy(s.phone, token);

          write(outfile, &s, sizeof(s));
        }
      }
      if (filename == NULL)
      {
        iFile = stdin;
      }
      else
      {
        iFile = fopen(filename, "r");
        if (iFile == NULL)
        {
          fprintf(stderr, "File not opened. Input valid filename!");
          exit(2);
        }
      }

  return 0;
    
  }
