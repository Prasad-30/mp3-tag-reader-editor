#ifndef VIEW_H
#define VIEW_H

#include "ret_types.h"

//for view function-------->
typedef struct _viewMp3
{
    char *src_mp3_fname;
    FILE *fptr_src_mp3;

} Viewmp3;

/* Check operation type */
OperationType check_operation_type(char *argv[]);

//view mp3 function
Status mp3_view(char *argv[], Viewmp3 *viewInfo);

//read the 6 tags
Status read_tags(Viewmp3 *viewInfo);

/* Read and validate Encode args from argv */
Status read_and_validate_view_args(char *argv[], Viewmp3 *viewInfo);
//----------------------------------end view----------------------


//for edit function---------->
typedef struct _editMp3
{
    FILE *fptr_org_mp3;
    FILE *fptr_dup_mp3;

} Editmp3;

/* to edit the mp3 file*/
Status mp3_edit(char *argv[], Editmp3 *editInfo, char stropt[]);

//to open files
Status open_files(char *argv[], Editmp3 *editInfo);

Status do_editting(char *argv[], Editmp3 *editInfo, char *stropt);
#endif