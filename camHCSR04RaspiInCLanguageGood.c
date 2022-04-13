/*

Pour compiler et exececuter le programme 
g++ -Wall -o nameFile nameFile.c  -lwiringPi
./nameFile

*/


#include <wiringPi.h>  
#include <stdio.h>  
#include <stdlib.h>
#include <sys/time.h>  
#include <assert.h>
#include <unistd.h>


#define  Trig    4  
#define  Echo    5  
 
void ultraInit(void)  
{  
        pinMode(Echo, INPUT);  
        pinMode(Trig, OUTPUT);  
}  

float disMeasure(void)  
{  
        struct timeval tv1;  
        struct timeval tv2;  
        long start, stop;  
        float dis;  
        digitalWrite(Trig, LOW);  
        delayMicroseconds(2);   

        digitalWrite(Trig, HIGH);  //produce a pluse
        delayMicroseconds(10); 
        digitalWrite(Trig, LOW);  

        while(!(digitalRead(Echo) == 1));  
        gettimeofday(&tv1, NULL);           //current time 
 
        while(!(digitalRead(Echo) == 0));  
        gettimeofday(&tv2, NULL);                         //current time  

                start = tv1.tv_sec * 1000000 + tv1.tv_usec; 
        stop  = tv2.tv_sec * 1000000 + tv2.tv_usec;  
 
        dis = (float)(stop - start) / 1000000 * 34000 / 2;  //count the distance
        return dis;  
}
                                      
void send_mail()
{
  FILE *pip;
char command[250] = "mpack -s 'Warning' -d 'test.txt' /home/pi/mypicture.jpg bemuss88@gmail.com";

  char sortie[100] ;
  char * content;
  FILE *fp ;
  FILE *body = fopen("test.txt","w");

  assert(fp = popen(command,"w"));
  fprintf(fp,"Distance");
  pclose(fp);
  printf("sending ...\n");
  assert(pip = popen("sendmail bemuss88@gmail.com < mypicture.jpg", "w"));

  fprintf(pip, "Subject: foobar\n");

  fprintf(pip, "foo\n");
  fprintf(pip, "bar\n");
  fprintf(pip, "distance %0.2f\n",disMeasure());
  fwrite(content,sizeof(char),1,body);
  fprintf(pip, ".\n");
  fclose(body);
  pclose(pip);
  printf("... sent\n");

  exit(0);
}  

int main(void)  
{  
       // float dis;  
        if(wiringPiSetup() == -1){ //when initialize wiring failed,print message to screem
                printf("setup wiringPi failed !\n");  
                return -1;   
        }  
        ultraInit();   
                while(1){  
                //dis = disMeasure();  
                //printf("Distance = %0.2f cm\n",dis);  
                //delay(1000);
                  if(disMeasure()<20){
                  printf("Distance = %0.2f cm\n", disMeasure());

                  //take_picture();
                  //sleep(15);
                  send_mail();
        }  
 }
        return 0;  
}



