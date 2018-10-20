#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "MES.h"


void msgwait(int msgid, message_container *msgp) //Funcion para recibir mensajes.
{
	if (msgrcv(msgid, msgp, MSGSZ, 1, 0) == -1) //Si el resultado de la funcion msgrcv es -1 se muestra error.
		printf("Error en recibir mensaje\n");

	return;
}
	
void msgsignal(int msgid, message_container *msgp) //Funcion para mandar señal de mensajes enviados.
{	
	if (msgsnd(msgid, msgp, MSGSZ, 1) == -1) //En caso de resultar -1 se muestra error.
		printf("Error en enviar mensaje\n");

	return;
}

int msginit(message_container *msgp) //Funcion para inicializar el mensaje
{
	int msqid; 
	key_t key = 1000; 
	if((msqid = msgget(key, (IPC_CREAT | 0666))) < 0)  //Se crea la cola de mensajes.
		printf("Error en GET\n");

	msgp->mtype = 1; //Se instancia el valor del tipo de mensaje del contenedor en 1.
	strcpy(msgp->mtext, "Estoy dentro del proceso"); //Se instancia el contenido del mensaje.

	return(msqid);
}
 
void msgclear(int msgid) //Funcion para borrar mensajes.
{
	struct msqid_ds mds;

	
	msgctl(msgid, IPC_RMID, &mds);
	return;
}

