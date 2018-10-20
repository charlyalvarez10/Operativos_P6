#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include "MES.h"


char *pais[3]={"Peru","Bolivia","Colombia"};

message_container msgp; //Se crea un nuevo contenedor para mensaje.
int msgid; //Variable del id del mensaje.

void proceso(int i) //Se crea la funcion "Proceso".
{
	int k; //Se crea variable para el ciclo de ejecución.

	for(k=0;k<CICLOS;k++)
	{
		
		msgwait(msgid, &msgp); //Se manda llamar la funcion msgwait implementada para recibir mensajes.

		printf("Entra %s\n",pais[i]); //Entra el país
		//printf("Mensaje en buzon: \"%s\"\n",msgp.mtext);
		fflush(stdout);
		sleep(rand()%3);
		printf("- %s Sale\n",pais[i]); //Sale país

		
		msgsignal(msgid, &msgp); //Se manda a llamar la funcion msgsignal implementada para mandar mensaje.

		sleep(rand()%3); //Se hace un sleep de espera fuera de la sección critica.
	}
	exit(0); // Termina la ejecución del proceso.
}

int main(){

	int pid; //Variable para el pid
	int status; //Variable para el estado
	int args[3]; //Arreglo para los países.
	int i; //Variable i para el ciclo
	int msgflg; //Bandera para mandar en la funcion msgsnd

	srand(getpid()); //Se obtiene el pid
	
	msgid=msginit(&msgp); //A la variable msgid se le asigna el return de la llamada a la funcion msginit.

	msgflg = 1; //Se establece en 1 la bandera
	
	if (msgsnd(msgid, &msgp, MSGSZ, msgflg) == -1) //Se valida si el mensaje padre fue enviado, si no fue enviado se muestra error.
		printf("Error en enviar mensaje PADRE\n");

	for(i=0;i<3;i++)
	{
	
		pid=fork();  // Crea un nuevo proceso hijo que ejecuta la función proceso()

	if(pid==0)
		proceso(i);
	}

	for(i=0;i<3;i++)
		pid = wait(&status);

	msgclear(msgid); //Se borran los mensajes.
	
}

