#include <stdio.h>
#include <string.h>
int main(int argc, char** argv)
{
    FILE *fp;
    fp=fopen("yx.txt","w+");
    if(strcmp(argv[1],"-w")==0){
        fputs("-w\n", fp);
    }else if(strcmp(argv[1],"-c")==0){
        fputs("-c\n", fp);
    }
    fclose(fp);
    return 0;
}