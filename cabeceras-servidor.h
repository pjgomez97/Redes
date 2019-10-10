#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define MAX_CLIENTS 30
#define MAX_MATCHES 10
#define MAX_QUEUE 10

volatile sig_atomic_t stop;

struct cliente {
  char usuario[20];
  char password[20];
  int socket;
  int estado;
  struct partida * partida;
  struct ficha * fichas[21];
};

struct partida {
  struct cliente * jugador1;
  struct cliente * jugador2;
  struct fichas * monton[14];
  char tablero[200];
};

struct ficha {
  int num1;
  int num2;
};

void compruebaEntrada(char * buffer, struct cliente arrayClientes[], int * numClientes, struct partida arrayPartidas[], int * numPartidas, struct cliente cola[],int * nCola, int socket, fd_set * readfds);
void Usuario(struct cliente * cliente, struct cliente arrayClientes[], char aux[], int numClientes);
void Password(struct cliente * cliente, struct cliente arrayClientes[], char aux[], int numClientes);
void Registro(struct cliente * cliente, struct cliente arrayClientes[], int numClientes, char buffer[]);
void iniciaPartida(struct cliente * cliente, struct cliente arrayClientes[], int numClientes, struct partida arrayPartidas[], int * numPartidas, struct cliente cola[], int * nCola);
void Fichas(struct cliente * jugador1, struct cliente * jugador2);
void colocarFicha(struct cliente * cliente, char buffer[]);
void Salir(struct cliente * cliente, struct cliente arrayClientes[], int * numClientes,fd_set * auxfds);
bool compruebaUsuario(char usuario[], struct cliente arrayClientes[], int numClientes);
bool compruebaPass(char password[], struct cliente cliente, int numClientes);
bool registraUsuario(char usuario[], char password[], struct cliente arrayClientes[], int numClientes);
struct cliente * popCola(struct cliente cola[],int * nCola);
void pushCola(struct cliente * cliente,struct cliente * cola[],int * nCola);
void desconectaClientes(struct cliente arrayClientes[], int * numClientes, fd_set * readfds);
void manejadorSenal(int sig);
