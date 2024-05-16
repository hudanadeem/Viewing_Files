/*
Huda Nadeem
1143941
CIS*3110

---------COMPILE-------

gcc -std=c11 -Wall A1.c
./a.out

*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <fcntl.h>

#define bytes_line  16 // 16 characters per line 


char *ascii(int fd);
char *hex(char *buf, int n);
char *hex(char *buf, int n) {

    char *tmpStr = (char*)malloc(sizeof(char)*64);
    int count = 0;
    for (int i = 0; i < n; i++) {
        count = count + sprintf(tmpStr + count, "%02x ", buf[i]); //converting char into Hex
        if (i == 7) {
        count = count + sprintf(tmpStr + count, " "); //space every 8 hex 
        } 
    }

    return tmpStr;
}
char *ascii(int fd){

    int len = lseek(fd, 0, SEEK_END);
    char *buffer = (char*)malloc(sizeof(char) * len + 1);
    lseek(fd, 0, SEEK_SET);

    int bytes_read = read(fd, buffer, len);

    //update contents inside buffer
    for(int i = 0; i < bytes_read; i++){
        // 0x0 - 0x9, 0xB - 0x1F with space (ASCII code 0x20)
        if( (buffer[i] >= 0 && buffer[i] <= 9) ||  (buffer[i] >= 11 && buffer[i] <= 31) ){
            buffer[i] = 32;
        }
        // 0x7F and greater with the character ? (ASCII code 0x3F)
        else if(buffer[i] >= 127 || buffer[i] < 0){ 
            buffer[i] = 63;
        }
    }
    return buffer;
}

int main(void) {

    char menuOp;
    char filename[255];
    char updatemenuOp;

   while(1)
   {
        printf("\n\n-----------MENU-------------\n");
        printf(" 'o' to enter a file name\n");
        printf(" 'd' to select display mode\n");
        printf( " 'x' exit\n\n"); 

        scanf("%s", &menuOp);

       if(menuOp != 'x' && menuOp != 'd' && menuOp != 'o'){

            printf("INVALID INPUT! Please enter again\n");
       }

        //FILENAME
        if(menuOp == 'x'){ //"x" to exit
            break;
        } 
        else if(menuOp == 'o'){  //"o" to enter a file name

            printf("Please enter filename\n");
            scanf("%s", filename);

            if( (strcmp(filename, "") == 0) || (strstr(filename, ".txt") == NULL) ){

                printf("INVALID FILENAME! Please enter again.\n");

            }
            else{
                int fd;

                fd = open(filename, O_RDONLY);
                if (fd < 0){
                    fprintf(stderr, "Could not open file %s\n", filename);
                }
                else{
                    printf("File opened sucessfully.\n");
                }
                close(fd);
            }

        }
        //DISPLAY
        else if(menuOp == 'd'){

            if((strstr(filename, ".txt") == NULL)){

                printf("Please choose 'o' and enter a filename before 'd' display.\n");

            }else{

                printf("Please enter 'a' for ASCII or 'h' for HEX...:  ");
                char check[2];
                scanf("%s", check);

                //ASCII
                if(strcmp(check,"a") == 0){
                    printf("\n-------ASCII------\n");

                    int fd = open(filename, O_RDONLY);

                    if (fd < 0){
                        fprintf(stderr, "Could not open file %s\n", filename);
                    }

                    char * buffer = ascii(fd); //ASCII function

                    int len = lseek(fd, 0, SEEK_END);
                    lseek(fd,0,SEEK_SET);

                    write(STDOUT_FILENO, buffer,len);
                    
                    free(buffer);
                    close(fd);

                }
                //HEX
                if(strcmp(check,"h") == 0){
                    printf("\n-------HEX------\n");


                    int fd = open(filename, O_RDONLY);

                    if (fd < 0){
                        fprintf(stderr, "Could not open file %s\n", filename);
                    }

                    int address = 0;
                    char *buf = (char*)malloc(sizeof(char)*bytes_line); //malloc for each line 16 characters
                    int n;

                    while ((n = read(fd, buf, bytes_line)) > 0) {
                        
                        char *line = hex(buf, n);

                        printf("%08x  %s\n", address, line); //%08 address %s is the new string created from hex function
                        address = address + n;//update address each time

                        free(line);
                    }
                    free(buf);
                    close(fd);

                }
                //updated menu
                printf("\n\n'm' to go back to menu\n");
                printf("'x' exit\n\n"); 
                scanf("%s", &updatemenuOp);

                if(updatemenuOp == 'm'){
                    continue;
                }
                else if(updatemenuOp == 'x'){
                    break;
                }
            }
            
        }
    }
    return 0;

}
