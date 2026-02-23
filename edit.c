#include <stdio.h>
#include<string.h>
#include<ctype.h>
#include"ret_types.h"
#include "prototypes.h"
#include <stdlib.h>

/*function definitions for edit function*/

//to open files
Status open_files(char *argv[], Editmp3 *editInfo){
    //first open a original mp3 file in read mode
    editInfo->fptr_org_mp3 = fopen(argv[4],"r");
    //do error handling
    if (editInfo->fptr_org_mp3 == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", "Sunny.mp3");

    	return e_failure;
    }

    //now open duplicate mp3 file in write mode
    editInfo->fptr_dup_mp3 = fopen("duplicate.mp3","w");
    //do error handling
    if (editInfo->fptr_dup_mp3 == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", argv[4]);

    	return e_failure;
    }
}

//mp3_edit() function definition
Status mp3_edit(char *argv[], Editmp3 *editInfo, char stropt[]){
    
    //first open the files
    if(open_files(argv, editInfo)==e_failure){
        return e_failure;
    }

    //copy header of 10 bytes from org.mp3 to sample.mp3
    char header[10];
    //read 10 bytes from org file
    if(fread(header , 10, 1 , editInfo->fptr_org_mp3)!=1)
        return e_failure;
    
    //write 10 bytes as is is into sample file
    if(fwrite(header ,10, 1 , editInfo->fptr_dup_mp3)!=1)
        return e_failure;
    
    
    //now call function to edit the info
    if(do_editting(argv, editInfo, stropt)==e_success){
        printf("INFO:\tEditted successfully!!\n");
    }
    else{
        printf("INFO:\tNothing editted\n");
        return e_failure;
    }
    return e_success;
}

//function definition to perform actual editting
Status do_editting(char *argv[], Editmp3 *editInfo, char stropt[]){
    //read the tag and compare with stropt

    for(int i=0;i<6;i++){
    //read the 4 bytes of Frame header ID
        char tags[5];
        fread(tags,4,1,editInfo->fptr_org_mp3);
        //store \0 at end to make it a string
        tags[4]='\0';

        if(strcmp(tags, stropt)==0){
            //write tag to the duplicate.mp3 as it is
            fwrite(tags,4,1,editInfo->fptr_dup_mp3);
            //read size only
            char size_bytes[4];
            fread(size_bytes,4,1,editInfo->fptr_org_mp3);
            // so now convert size to little endian by swapping bytes
            int size = (size_bytes[0] << 24) | (size_bytes[1] << 16) | (size_bytes[2] << 8)  | (size_bytes[3]);

            //now get the new size of new content and write in a dupliacte.mp3
            int new_size = strlen(argv[3])+1;
            //convert to big endian
            unsigned char buf[4];
            buf[0] = (new_size >> 24) & 0xFF;
            buf[1] = (new_size >> 16) & 0xFF;
            buf[2] = (new_size >> 8) & 0xFF;
            buf[3] = new_size & 0xFF;
            //write in duplicate.mp3
            fwrite(buf, 4, 1, editInfo->fptr_dup_mp3);

            //read and write the flag of 2 bytes
            char flag_null[2];
            fread(flag_null,2,1,editInfo->fptr_org_mp3);
            fwrite(flag_null,2,1,editInfo->fptr_dup_mp3);

            //read and write 1 encode byte i.e '\0'
            char encode;
            fread(&encode,1,1,editInfo->fptr_org_mp3);
            fwrite(&encode,1,1,editInfo->fptr_dup_mp3);

            //overwrite the previous content with new content
            fwrite(argv[3], 1, new_size-1, editInfo->fptr_dup_mp3);

            //move the file offset to the next tag
            fseek(editInfo->fptr_org_mp3, size-1 , SEEK_CUR);

            
        }
        else{
            //write tag to the duplicate.mp3
            fwrite(tags,4,1,editInfo->fptr_dup_mp3);

            //read and write the size
            char size_bytes[4];
            fread(size_bytes,4,1,editInfo->fptr_org_mp3);
            fwrite(size_bytes,4,1,editInfo->fptr_dup_mp3);

            //read and write the flag of 2 bytes
            char flag_null[2];
            fread(flag_null,2,1,editInfo->fptr_org_mp3);
            fwrite(flag_null,2,1,editInfo->fptr_dup_mp3);

            //read and write 1 encode byte i.e '\0'
            char encode;
            fread(&encode,1,1,editInfo->fptr_org_mp3);
            fwrite(&encode,1,1,editInfo->fptr_dup_mp3);

            // so now convert size to little endian by swapping bytes to access the content properly
            int size = (size_bytes[0] << 24) | (size_bytes[1] << 16) | (size_bytes[2] << 8)  | (size_bytes[3]);

            //based on size read content and write it one by one
            char content[size];
            char ch;
            for(int i=0;i<size-1;i++){
                fread(&ch,1,1,editInfo->fptr_org_mp3);
                fwrite(&ch,1,1,editInfo->fptr_dup_mp3);
            }
        }
    }

        //read and write remaining contents from org.mp3 to duplicate.mp3
        char cont;
        while(fread(&cont,1,1,editInfo->fptr_org_mp3)==1){
            fwrite(&cont,1,1,editInfo->fptr_dup_mp3);
        }

        fclose(editInfo->fptr_org_mp3);
        fclose(editInfo->fptr_dup_mp3);

        remove(argv[4]);
        rename("duplicate.mp3", "song.mp3");
        return e_success;

}