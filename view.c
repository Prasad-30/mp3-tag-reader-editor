#include <stdio.h>
#include<string.h>
#include<ctype.h>
#include"ret_types.h"
#include"prototypes.h"
#include <stdlib.h>

//Function definitions


//function definition to check operation type
OperationType check_operation_type(char *argv[]){
    //return the enum values according to the selected operation
    if(strcmp(argv[1],"--help")==0){
        return e_help;
    }
    else if(strcmp(argv[1],"-v")==0){
        return e_view;
    }
    else if(strcmp(argv[1],"-e")==0){
        return e_edit;
    }
    else{
        return e_unsupported;
    }
}

//function definition to validate the arguments of view mode
Status read_and_validate_view_args(char *argv[], Viewmp3 *viewInfo){
    
    //if the file name is not given, print the error message
    if(argv[2]==NULL){
        printf("ERROR:\tInvalid Arguments !\nPlease pass the file name\n");
        printf("INFO:\tTo view please pass like: %s -v Mp3filename\n",argv[0]);
        return e_failure;
    }
    //return success if everything is alright
    return e_success;
}

//function definiton of mp3_view() function
Status mp3_view(char *argv[],  Viewmp3 *viewInfo){
    //first open a file
    viewInfo->fptr_src_mp3 = fopen(argv[2],"r");
    //do error handling
    if (viewInfo->fptr_src_mp3 == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", argv[2]);

    	return e_failure;
    }

    //fetch first 3 bytes of header
    char buffer[4];
    fread(buffer,3,1,viewInfo->fptr_src_mp3);
    buffer[4]='\0';
    
    //compare buffer with "ID3" i.e check if it's a mp3 file
    if(strcmp(buffer,"ID3")==0){
        //printf("INFO:\t It's a mp3 file\n");
        printf("-------------------------------VIEW MODE SELECTED--------------------------------\n");
    }
    else{
        printf("ERROR:\t%s is not a mp3 file, please provide .mp3 file only!!\n",argv[2]);
        return e_failure;
    }

    //now skip file pointer by 7 bytes to reach the tag id's
    fseek(viewInfo->fptr_src_mp3,7,SEEK_CUR);
    
    //call function to read the tags
    if(read_tags(viewInfo)==e_failure){
        return e_failure;
    }
    
    return e_success;

}

//function definition to read the tags
Status read_tags(Viewmp3 *viewInfo){
    //we are reading only 6 frame header ID's, so run a loop for 6 times
    for(int i=0;i<6;i++){
        //read the 4 bytes of Frame header ID
        char tags[5];
        fread(tags,4,1,viewInfo->fptr_src_mp3);
        //store \0 at end to make it a string
        tags[4]='\0';
        //print the frame header id
        printf("%d.%s ----> ",i+1,tags);

        //read the content size in 4 bytes, cause it's a integer
        //in mp3 it's stored in a big endian format
        char size_bytes[4];
        fread(size_bytes,4,1,viewInfo->fptr_src_mp3);

        // so now convert size to little endian by swapping bytes
        int size = (size_bytes[0] << 24) | (size_bytes[1] << 16) | (size_bytes[2] << 8)  | (size_bytes[3]);

        //skip 3 bytes of data i.e 2 flags and 1 encoding byte
        fseek(viewInfo->fptr_src_mp3,3,SEEK_CUR);
    
        //read the frame content
        char content[size];
        fread(content, size-1 ,1, viewInfo->fptr_src_mp3);
        content[size-1]='\0';
        //print the frame content
        printf("%s\n",content);
    }
    return e_success;

}