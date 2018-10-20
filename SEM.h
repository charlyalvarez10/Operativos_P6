#define CICLOS 10
#define MSGSZ 1024

typedef struct msgcontainer { //Se crea una estructura como contenedor de los mensajes del proceso.
         long    mtype; //Variable que contiene el tipo de mensaje.
         char    mtext[MSGSZ]; // Variable que contiene el texto del mensaje.
} message_container; //Nombre con el que se define la estructura.
