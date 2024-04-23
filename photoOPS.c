#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdbool.h>
#include "photoOPS.h"
char *fileName = "photos.txt";
char *fileLog = "log.txt";
void writeToLogFile(char text[])
{
	FILE *file = fopen(fileLog,"a+");
	fprintf(file,"%s",text);
	fclose(file);
}
void renamePhotoName(char albumName[], int id, char newPhotoName[])
{
   DIR *dir;
   if( (dir= opendir(albumName)) != NULL)
    {
        strcat(albumName,"//");
        strcat(albumName,fileName);
        FILE *file = fopen(albumName, "rb+");
        photo current;
        fread(&current, sizeof(current),1,file);
        bool isUpdated = false;
        while( !feof(file))
        {
            if(id == current.id)
            {
                strcpy(current.name,newPhotoName);
                fseek(file, -sizeof(current), SEEK_CUR);
                fwrite(&current,sizeof(current),1,file);
                isUpdated = true;
            }
            fread(&current, sizeof(current),1,file);
        }
        fclose(file);
        closedir(dir);
        if(isUpdated == true)
		{
			printf("Photo name is updated...\n");
			char text[200];
			sprintf(text,"Photo with id %d in album %s is renamed as %s\n",id,albumName,newPhotoName);
			writeToLogFile(text);
		}
            
    }
    else
    {
        printf("There is no album with the given name!!!\n");
    }
}
void displayAlbums()
{
    DIR *dir;
    char  cwd[50];
    getcwd(cwd, 50);
    dir = opendir(cwd);
    struct dirent *dirp;
    printf("Albums :\n");
    while( (dirp = readdir(dir)) !=NULL)
    {
        if(strcmp(dirp->d_name,".") != 0 &&strcmp(dirp->d_name,"..") != 0 )
        {
            struct stat info;
            stat(dirp->d_name,&info);
            if(S_ISDIR(info.st_mode))
            {
                  printf("%s\n",dirp->d_name);
            }
        }
    }
    closedir(dir);
}
void renameAlbum(char albumName[])
{
   DIR *dir;
   if( ( dir= opendir(albumName)) != NULL)
    {
        char newName[50];
        printf("Enter new album name :");
        scanf("%s",&newName);
        rename(albumName,newName);
        printf("%s is renamed as %s....\n",albumName, newName);
		char text[200];
		sprintf(text,"Album %s is renamed as %s....\n",albumName, newName);
		writeToLogFile(text);
        closedir(dir);
    }
    else
    {
        printf("There is no album with the given name!!!\n");
    }
}
void showPhotos(char albumName[])
{
   DIR *dir;
   if( ( dir= opendir(albumName)) != NULL)
    {
        strcat(albumName,"//");
        strcat(albumName,fileName);
        FILE *file = fopen(albumName, "rb+");
        photo current;
		printf("Photos : \n");
        fread(&current, sizeof(current),1,file);
        while( !feof(file))
        {
            printf("Photo id : %d\n",current.id);
            printf("Photo size : %d\n",current.size);
            printf("Photo name : %s\n",current.name);
            fread(&current, sizeof(current),1,file);
        }
        fclose(file);
        closedir(dir);
    }
    else
    {
        printf("There is no album with the given name!!!\n");
    }
}
void addNewPhoto(photo newPhoto, char albumName[])
{
   DIR *dir;
   if( ( dir= opendir(albumName)) != NULL)
    {
        strcat(albumName,"//");
        strcat(albumName,fileName);
        FILE *file = fopen(albumName, "ab+");
        fwrite(&newPhoto,sizeof(newPhoto),1,file);
        fclose(file);
        printf("New photo is added successfully....\n");
        closedir(dir);
		char text[200];
		sprintf(text,"New photo with id %d is added to album %s successfully....\n",newPhoto.id,albumName);
		writeToLogFile(text);
    }
    else
    {
        printf("There is no album with the given name!!!\n");
    }
}
void createAlbum(char albumName[])
{
   DIR *dir;
   if( ( dir= opendir(albumName)) == NULL)
    {
        printf("%s is crated successfully....\n",albumName);
        mkdir(albumName, S_IRUSR | S_IWUSR | S_IXUSR);
        strcat(albumName,"//");
        strcat(albumName,fileName);
        FILE *file = fopen(albumName, "ab+");
        fclose(file);
		char text[200];
		sprintf(text,"Album %s is crated successfully....\n",albumName);
		writeToLogFile(text);
    }
    else
    {
        closedir(dir);
        printf("This album already exist!!!\n");
    }

}
void deleteAlbum(char albumName[])
{
   if( ( opendir(albumName)) != NULL)
    {
        char temp[50];
        strcpy(temp,albumName);
        strcat(temp,"//");
        strcat(temp,fileName);
        remove(temp);
        rmdir(albumName);
        printf("%s is deleted successfully....\n",albumName);
		char text[200];
		sprintf(text,"Album %s is deleted successfully....\n",albumName);
		writeToLogFile(text);
    }
    else
    {
        printf("There is no album with the given name!!!\n");
    }
}



