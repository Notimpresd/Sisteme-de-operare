#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[]) {
// Verificam numarul de argumente
if (argc != 2) {
printf("Usage: %s <fisier_intrare>\n", argv[0]);
return 1;
}
// Deschidem fisierul BMP pentru citire
int fd_bmp = open(argv[1], O_RDONLY);
if (fd_bmp == -1) {
perror("Eroare la deschiderea fisierului");
return 1;
}
// Citim header-ul BMP
unsigned char header[54];
int nr_cititi = read(fd_bmp, header, 54);
if (nr_cititi != 54) {
perror("Eroare la citirea header-ului");
close(fd_bmp);
return 1;
}
// Extragem inaltimea si lungimea din header
int inaltime = (int)&header[18];
int lungime = (int)&header[22];
// Deschidem fisierul de iesire
int fd_statistici = open("statistica.txt", O_CREAT | O_WRONLY, 0644);
if (fd_statistici == -1) {
perror("Eroare la deschiderea fisierului de iesire");
close(fd_bmp);
return 1;
}
// Structura pentru stat
struct stat file_stat;
// Apelam stat pentru a obtine informatii despre fisierul BMP
if (fstat(fd_bmp, &file_stat) == -1) {
perror("Eroare la apelul fstat");
close(fd_bmp);
close(fd_statistici);
return 1;
}
// Formam siruri cu informatiile
char nume_fisier[100];
strcpy(nume_fisier, argv[1]);
char dimensiune[100];
sprintf(dimensiune, "%ld", (long int)file_stat.st_size);
char user_id[100];
sprintf(user_id, "%d", (int)file_stat.st_uid);
char data_modificare[100];
strftime(data_modificare, 100, "%d.%m.%Y", localtime(&file_stat.st_mtime));
// Scriem informatiile in fisierul de iesire
char buffer[BUF_SIZE];
sprintf(buffer, "nume fisier: %s\n", nume_fisier);
write(fd_statistici, buffer, strlen(buffer));
sprintf(buffer, "inaltime: %d\n", inaltime);
write(fd_statistici, buffer, strlen(buffer));
sprintf(buffer, "lungime: %d\n", lungime);
write(fd_statistici, buffer, strlen(buffer));
sprintf(buffer, "dimensiune: %s\n", dimensiune);
write(fd_statistici, buffer, strlen(buffer));
sprintf(buffer, "identificatorul utilizatorului: %s\n", user_id);
write(fd_statistici, buffer, strlen(buffer));
sprintf(buffer, "timpul ultimei modificari: %s\n", data_modificare);
write(fd_statistici, buffer, strlen(buffer));
// Formam sirul cu permisiunile
char permisiuni[100];
sprintf(permisiuni, "drepturi de acces user: %c%c%c\n",
(file_stat.st_mode & S_IRUSR)?'R':'-',
(file_stat.st_mode & S_IWUSR)?'W':'-',
(file_stat.st_mode & S_IXUSR)?'X':'-');
sprintf(buffer, "contorul de legaturi: %d\n", file_stat.st_nlink);
write(fd_statistici, buffer, strlen(buffer));
sprintf(buffer, "%s", permisiuni);
write(fd_statistici, buffer, strlen(buffer));
// Formam sirurile pentru permisiunile grup si altii
char permisiuni_grup[100];
sprintf(permisiuni_grup, "drepturi de acces grup: %c%c%c\n",
(file_stat.st_mode & S_IRGRP)?'R':'-',
(file_stat.st_mode & S_IWGRP)?'W':'-',
(file_stat.st_mode & S_IXGRP)?'X':'-');
char permisiuni_altii[100];
sprintf(permisiuni_altii, "drepturi de acces altii: %c%c%c\n",
(file_stat.st_mode & S_IROTH)?'R':'-',
(file_stat.st_mode & S_IWOTH)?'W':'-',
(file_stat.st_mode & S_IXOTH)?'X':'-');
sprintf(buffer, "%s", permisiuni_grup);
write(fd_statistici, buffer, strlen(buffer));
sprintf(buffer, "%s", permisiuni_altii);
write(fd_statistici, buffer, strlen(buffer));
// Inchidem fisierele
close(fd_bmp);
close(fd_statistici);
return 0;
}
