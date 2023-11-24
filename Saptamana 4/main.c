    #include <unistd.h>
    #include <fcntl.h>
    #include <stdio.h>
    #include <sys/stat.h>
    #include <stdlib.h>
    #include <string.h>
    int main(int argc, char *argv[])
    {
        char ch = argv[3][0],buffer[1];
        int lowercase=0,uppercase=0, digits=0,ch_count=0,file_size=0;
        int input_fd = open(argv[1], O_RDONLY);
        int output_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
        struct stat file_stat;

        if (argc != 4)
        {
            printf("Argumente gresite!\n");
            exit(1);
        }

        if (input_fd == -1)
        {
            perror("Eroare la deschidere fisier.");
            exit(1);
        }

        if (output_fd == -1)
        {
            perror("Eroare la deschidere fisier.");
            exit(1);
        }

        if (fstat(input_fd, &file_stat) == -1)
        {
            perror("Eroare la obtinere date.");
            exit(1);
        }
        file_size = file_stat.st_size;
        while (read(input_fd, buffer, 1) > 0)
        {
            if (*buffer >= 'a' && *buffer <= 'z')
                lowercase++;
            else if (*buffer >= 'A' && *buffer <= 'Z')
                uppercase++;
            else if (*buffer >= '0' && *buffer <= '9')
                digits++;
            if (*buffer == ch)
                ch_count++;
        }

        char result[100];
        sprintf(result, "numar litere mici: %d\nnumar litere mari: %d\nnumar cifre: %d\nnumar aparitii caracter: %d\ndimensiune fisier: %d\n", lowercase, uppercase, digits, ch_count, file_size);
        write(output_fd, result,strlen(result));
        close(input_fd);
        close(output_fd);

        return 0;
    }
