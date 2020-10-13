#include <stdio.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int welcome, new_soc, fd, n;
    
    char fname[100];
    struct sockaddr_in addr;

    welcome = socket(PF_INET, SOCK_STREAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(5000);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    printf("\nServer is Online");
    bind(welcome, (struct sockaddr *) &addr, sizeof(addr));
    listen(welcome, 5);
    new_soc = accept(welcome, NULL, NULL);
    recv(new_soc, fname, 50, 0);
    printf("\nRequesting for file: %s\n", fname);
    FILE *fp = fopen(fname,"rb");
        if(fp==NULL)
        {
            printf("File opern error");
            return 1;   
        }
        while (1)
        {
                    
        unsigned char buffer[1024]={0};
        int nread = fread(buffer,1,1024,fp);
        
                if(nread > 0)
                {
                    write(new_soc, buffer, nread);
                }
                if (nread < 1024)
            {
                if (feof(fp))
		{
		    printf("File transfer completed\n");
		}
                if (ferror(fp))
                    printf("Error reading\n");
                break;
            }
        }
    close(fd);

    return 0;
}
