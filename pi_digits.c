/*
* AUTHOR: ISABELA HUTCHINGS
* CLASS: csc 452 summer 2019
* PROJECT 2
* this program calls /dev/pi_drive to check and see if it runs properly
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
//this s the main program that will open "/dev/pi_driver" and read it
int main(int argc, char *argv[]){
	//this if() checks to see that the command line has 2 parameters it returns an error and extis
	if(argc < 3){
		printf("ERROR: Not enough parameters\n");
		exit(-1);
	}
	//convert the charparameters into their respective numeral value
	int min=atoi(argv[1]);
	int max=atoi(argv[2]);
	//this check to  makes sure min is the samllest num and max is the largest
	if(min > max){
		int temp=min;
		min=max;
		max=temp;
	}
	//set the length of the buff string the max+1
	int len=max+1;
	char pi_str[len];
	//open the file and check if it has been opened properly
	int pfd=open("/dev/pi_driver",O_RDONLY);
	if(pfd==-1){
		printf("Error: dev/pi_driver does not exsist\n");
		exit(-1);
	}
	read(pfd,pi_str,len);
	//check to see hos many digits pi returns
	int return_len=strlen(pi_str);
	//if pi number length is less then the max+1 update the new len
	if(return_len<len )
		len=return_len ;
	//this prints out the chars set by the max and min
	for(int i=min;i<len;i++){
		printf("%c",pi_str[i]);
	}
	printf("\n");
	//close the file and exit
	close(pfd);
	exit(0);
}
