#ifndef PHOTOOPS_H_INCLUDED
#define PHOTOOPS_H_INCLUDED
typedef struct photo{
    int id;
    int size;
    char name[50];
}photo;
void createAlbum(char albumName[]);
void deleteAlbum(char albumName[]);
void addNewPhoto(photo newPhoto, char albumName[]);
void showPhotos(char albumName[]);
void renameAlbum(char albumName[]);
void displayAlbums();
void renamePhotoName(char albumName[], int id, char newPhotoName[]);
void writeToLogFile(char text[]);
#endif // PHOTOOPS_H_INCLUDED
