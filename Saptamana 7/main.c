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
//
//
// Inchidem fisierele
close(fd_bmp);
close(fd_statistici);
return 0;
}
