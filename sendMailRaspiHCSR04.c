/*
Materiaux utilisés:
Raspberry PI 3 b+
Camera V2
Capteur de distance HC-SR04

Fonction: 

  Ce script avec 3 fonctions, une pour recuperer le distance 
  envoyée par le capteur, une pour prendre une photo avec V2
  et une autre pour envoyer une alerte sur le mail mentionné  
*/



#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <assert.h>
#include <unistd.h>


#define TRIG 24
#define ECHO 8

// Fonction de configuration du trigger et de l'echo
void setup() {
        wiringPiSetupGpio();
        pinMode(TRIG, OUTPUT);
        pinMode(ECHO, INPUT);

        //TRIG pin must start LOW
        digitalWrite(TRIG, LOW);
        delay(30);
}

//Fonction de calcul des distances 
double getCM() {

        //Send trig pulse
        digitalWrite(TRIG, HIGH);
        delayMicroseconds(20);
        digitalWrite(TRIG, LOW);

        //Wait for echo start
        while(digitalRead(ECHO) == LOW);

        //Wait for echo end
        long startTime = micros();
        while(digitalRead(ECHO) == HIGH);
        long travelTime = micros() - startTime;

        //Get distance in cm
        double distance = travelTime / 58;

        return distance;
}

//Fonction capture d'image
void take_picture()
{
    char command[24] = "raspistill -o image.jpg";
    char sortie[100];
    FILE *fp;
    fp=popen(command, "w");

    while(fgets(sortie, 100,fp) != NULL)
        printf("%s",sortie);
}

//Fonction envoi d'email
void send_mail()
{
  FILE *pip;

  char command[250] = "mpack -s 'Alerte intrusion' -d 'test.txt' /home/pi/Desktop/image.jpg mailDestinataire@yahoo.fr " ;
  char sortie[100] ;
  char * content;
  FILE *fp ;
  FILE *body = fopen("test.txt","w");

  assert(fp = popen(command,"w"));
  fprintf(fp,"Distance");
  pclose(fp);
  printf("sending ...\n");
  assert(pip = popen("sendmail mailDestinataire@yahoo.fr < image.jpg", "w"));

  fprintf(pip, "Subject: foobar\n");

  fprintf(pip, "foo\n");
  fprintf(pip, "bar\n");
  fprintf(pip, "distance %f\n",getCM());
  fwrite(content,sizeof(char),1,body);
  fprintf(pip, ".\n");
  fclose(body);
  pclose(pip);
  printf("... sent\n");

  exit(0);
}

//Fonction principale
int main(void) {
    setup();
    int val = 1;
    while (val==1) {

        if(getCM()<20){
        printf("distance: %f cm\n",getCM());

        take_picture();
        sleep(15);
        send_mail();
        val=2 ;

        }

    }
        //return 0;
}






