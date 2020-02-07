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

  int iflag = 0;
  int oflag = 0;
  int hflag = 0;
  int vflag = 0;
  char *filename = NULL;
  FILE *iFile = NULL;
  int c;
  char *iname;
  char *outname;
  int outfile;

  while ((c = getopt(argc, argv, "i:o:hv")) != -1)
  {
    switch (c)
    {

    case 'i':
      iflag = 1;
      iname = optarg;
      break;
    case 'o':
      //cvalue = optarg;
      oflag = 1;
      outname = optarg;
      printf("%s", outname);
      break;
    case 'h':
      //cvalue = optarg;
      hflag = 1;
      break;
    case 'v':
      filename = optarg;
      vflag = 1;
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

  if (hflag)
  {
    printf("h: help \n");
    printf("i: input file name \n");
    printf("o: name of output file \n");
    printf("v: verbose mode \n");
  }
  if (iflag)
  {
    filename = optarg;
    iFile = fopen(optarg, "r");
    fclose(iFile);
  }

  if (oflag)
  {
    if (outname == NULL)
    {
      outfile = STDOUT_FILENO;
    }
    else
    {
      outfile = open(outname, O_RDONLY | O_RDWR | O_CREAT, S_IWUSR | S_IRUSR);
    }
  }
  if (vflag)
  {
    printf("v flag enabled \n");
  }

  return 0;
}
