#include <stdio.h>
#include <stdlib.h>
#include "photoOPS.h"
int main()
{
    int selection, id, size;
    char namePhoto[50], albumName[50];
    do{
        printf("Create album (1)\n");
        printf("Delete album (2)\n");
        printf("Add photo to album (3)\n");
        printf("Show photos in album (4)\n");
        printf("Rename album (5)\n");
        printf("Rename photo (6)\n");
        printf("Display album names (7)\n");
        printf("Exit (8)\n");
        printf("Enter your selection : ");
        scanf("%d",&selection);
        switch(selection){
          case 1:
            printf("Enter new album name :");
            scanf("%s",&albumName);
            createAlbum(albumName);
            break;
          case 2:
            printf("Enter album name to delete:");
            scanf("%s",&albumName);
            deleteAlbum(albumName);
            break;
          case 3:
            printf("Enter album name :");
            scanf("%s",&albumName);
            printf("Enter new photo id :");
            scanf("%d",&id);
            printf("Enter new photo size :");
            scanf("%d",&size);
            printf("Enter new photo name :");
            scanf("%s",&namePhoto);
            photo p;
            p.id = id;
            p.size = size;
            strcpy(p.name,namePhoto);
            addNewPhoto(p,albumName);
            break;
          case 4:
            printf("Enter album name to show photos:");
            scanf("%s",&albumName);
            showPhotos(albumName);
            break;
          case 5:
            printf("Enter album name to rename:");
            scanf("%s",&albumName);
            renameAlbum(albumName);
            break;
          case 6:
            printf("Enter album name :");
            scanf("%s",&albumName);
            printf("Enter photo id to update :");
            scanf("%d",&id);
            printf("Enter new photo name :");
            scanf("%s",&namePhoto);
            renamePhotoName(albumName,id,namePhoto);
            break;
          case 7:
                displayAlbums();
            break;
        }
    }while(selection !=8);
    return 0;
}
