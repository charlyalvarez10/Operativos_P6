#include "SEM.h"

void msgwait(int msgid, message_container *msgp); //Funcion para espera de mensaje.
void msgsignal(int msgid, message_container *msgp); //Funcion para entregar señal de mensaje.
int msginit(message_container *msgp); //Funcion para inicializar el mensaje
void msgclear(int msgid); //Funcion para borrar mensajes.