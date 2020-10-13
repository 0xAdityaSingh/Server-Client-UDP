#include <stdio.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
int main()
{
    int soc, n;
    int bytesReceived = 0;
    char buffer[1024], fname[100];
    struct sockaddr_in addr;
    soc = socket(PF_INET, SOCK_STREAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(5000);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    while(connect(soc, (struct sockaddr *) &addr, sizeof(addr))) ;
    printf("\nClient is connected to Server");
    printf("\nEnter file name: ");
    scanf("%s", fname);
    send(soc, fname, sizeof(fname), 0);

    printf("\nRecieved response\n");

  FILE *fp;
  fp = fopen(fname, "ab"); 
    	if(NULL == fp)
    	{
       	 printf("File does not exist");
         return 1;
    	}
    long double sz=1;
    while((bytesReceived = read(soc, buffer, 1024)) > 0)
    { 
        sz++;
      fflush(stdout);
      fwrite(buffer, 1,bytesReceived,fp);
        // printf("%s \n", buffer);
    }
        printf("\nFile Recieved Completed\n");
    return 0;
}