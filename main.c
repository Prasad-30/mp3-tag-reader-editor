/* Name : Prasad Kumbhar
 * Project Name : MP3 Tag Reader & Editor
 * Description  :
 * This project reads and edits ID3 tags of MP3 files using C.
 * It allows users to view and modify song details such as title,
 * artist, album, year, content, and comments through command-line
 * arguments, helping understand file handling and binary data processing.
 */

#include<stdio.h>
#include "prototypes.h"
#include <string.h>
int main(int argc, char *argv[]){
    //print the usage message if argc is only one
    if(argc<2){
        printf("Provide sufficient arguments!\n");
        printf("To view please pass like: %s -v Mp3filename\n"
               "To edit please pass like: %s -e -t/-a/-A/-m/-y/-c changing_text mp3filename\n"
               "To get help pass like:    %s --help\n",argv[0],argv[0],argv[0]);
        return 0;
    }
    //now check the operation type i.e help,view or edit
    if(check_operation_type(argv)==e_help){
        if(argc>2){
            printf("Provide valid arguments!\nTo get help pass like:    %s --help\n",argv[0]);
            return 0;
        }
        //if operation is help, then simply print the following prompt message
        printf("1. -v -> to view mp3 file contents\n"
               "2. -e -> to edit mp3 file contents\n"
               "        2.1. -t  -> to edit song title\n"
               "        2.2. -a  -> to edit artist name\n"
               "        2.3. -A  -> to edit album name\n"
               "        2.4. -y  -> to edit year\n"
               "        2.5. -m  -> to edit content\n"
               "        2.6. -c  -> to edit comment\n"
            );
    }
    //if the operation is view then
    else if(check_operation_type(argv) == e_view){
        //create viewInfo structure variable to store info
        Viewmp3 viewInfo;
        //first validate the argument is there or not
        if(read_and_validate_view_args(argv, &viewInfo)==e_success){
            //now call mp3_view() function to print the data about file
            if(mp3_view(argv,&viewInfo)==e_success){
                //e_success means view is successfull, so close the file
                fclose(viewInfo.fptr_src_mp3);
            }
            else{
                return 0;
            }
        }
        else{
            return 0;
        }
    }
    
    //if the operation is edit
    else if(check_operation_type(argv) == e_edit){
        //validate the number of arguments for edit operation
        if(argc<5 || argc>5){
            printf("Provide valid arguments\n");
            printf("To edit please pass like: %s -e -t/-a/-A/-m/-y/-c changing_text mp3filename\n",argv[0]);
            return 0;
        }
        //create editInfo structure to store info
        Editmp3 editInfo;
        //to change a title of a song
        if(strcmp(argv[2], "-t")==0){
            if(mp3_edit(argv, &editInfo, "TIT2")==e_success){
                printf("INFO:\tTitle changed successfully!\n");
            }
            else{
                return 0;
            }
        }
        //to change the artist name
        else if(strcmp(argv[2], "-a")==0){
            if(mp3_edit(argv, &editInfo, "TPE1")==e_success){
                printf("INFO:\tArtist name changed successfully!\n");
            }
            else{
                return 0;
            }
        }
        //to change the album name
        else if(strcmp(argv[2], "-A")==0){
            if(mp3_edit(argv, &editInfo, "TALB")==e_success){
                printf("INFO:\tAlbum changed successfully!\n");
            }
            else{
                return 0;
            }
        }
        //to change the year of song released
        else if(strcmp(argv[2], "-y")==0){
            if(mp3_edit(argv, &editInfo, "TYER")==e_success){
                printf("INFO:\tYear changed successfully!\n");
            }
            else{
                return 0;
            }
        }
        //to change the content
        else if(strcmp(argv[2], "-m")==0){
            if(mp3_edit(argv, &editInfo, "TCON")==e_success){
                printf("INFO:\tContent changed successfully!\n");
            }
            else{
                return 0;
            }
        }
        //to change the comment of a song
        else if(strcmp(argv[2], "-c")==0){
            if(mp3_edit(argv, &editInfo, "COMM")==e_success){
                printf("INFO:\tComment changed successfully!\n");
            }
            else{
                return 0;
            }
        }
        //otherwise prompt the usage message
        else{
            printf("ERROR:\tWrong operation type\n");
            printf("To edit please pass like: %s -e -t/-a/-A/-m/-y/-c changing_text mp3filename\n",argv[0]);
            return 0;
        }
    }
    
    //if the operation is unsupported
    else{
        printf("ERROR: Wrong operation type\nUSAGE:\n");
        printf("To view please pass like: %s -v Mp3filename\n"
               "To edit please pass like: %s -e -t/-a/-A/-m/-y/-c changing_text mp3filename\n"
               "To get help pass like:    %s --help\n",argv[0],argv[0],argv[0]);
        return 0;
    }

    return 0;
}