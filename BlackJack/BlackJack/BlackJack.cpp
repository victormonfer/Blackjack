#include <iostream>
using namespace std;
#include<windows.h>

//Variables Jugador 1
string JugadorName;
int puntosJugador;
bool JugadorSigueJugando = true;


//Variables Casino
string croupiereName = "Senyor Monroy";
int casinoPoints;
bool croupiereSigueJugando = true;

//baraja
int baraja[4][13];
int valorCarta[4][13];

void iniciBaraja(int(&arrayBaraja)[4][13], int(&arrayCarta)[4][13]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++) {
			arrayBaraja[i][j] = 1;

			if (j > 0 && j < 10) {
				arrayCarta[i][j] = j + 1;
			}
			else if (j >= 10 && j < 14) {
				arrayCarta[i][j] = 10;
			}

		}
	}
}

void startGame() {

	cout << "Bienvendido a la sala de BlackJack, \n";
	cout << "yo soy el Croupiere " << croupiereName << " , tu quien eres? (introduce tu nombre): \n";
	cin >> JugadorName;
	cout << "\n";
	Sleep(100);
}

void repartoCartas(int& totalPoints, int(&arrayBaraja)[4][13], int(&arrayCarta)[4][13], int numJugadas, string nomJugador, bool& SigueJugando) {
	int palos = 0;
	int num = 0;
	int valor = 0;
	string palo;

	for (int cartasRepartidas = 0; cartasRepartidas < numJugadas; cartasRepartidas++) {


		palos = rand() % 4;
		num = rand() % 13;

		if (palos == 0) {
			palo = "picas";
		}
		else if (palos == 1) {
			palo = "corazones";
		}
		else if (palos == 2) {
			palo = "treboles";
		}
		else if (palos == 3) {
			palo = "diamantes";
		}
		if (nomJugador._Equal(JugadorName)) {

			if (arrayBaraja[palos][num] == 1) {
				if (num == 0) {
					cout << "Te ha salido un As\n";
					cout << "Que valor quieres que tenga el As?, 1 o 11 \n";
					int opcion;
					do {
						cin >> opcion;

						switch (opcion) {
						case 1:
							arrayCarta[palos][num] = 1;
							break;
						case 11:
							arrayCarta[palos][num] = 11;
							break;


						default:
							cout << "Eso no es un valor que pueda tener el As, dame otro\n";
						}
					} while (opcion != 1 && opcion != 11);

				}
				if (totalPoints >= 21) {

					SigueJugando = false;
				}
			}
		}
		else if (nomJugador._Equal(croupiereName)) {
			if (arrayBaraja[palos][num] == 1) {
				if (num == 0) {
					cout << "Le ha salido un As a la casa \n";
					if (totalPoints + 11 <= 21) {
						arrayCarta[palos][num] = 11;
					}

					else if (totalPoints + 11 > 21) {
						arrayCarta[palos][num] = 1;
					}
				}
				if (totalPoints >= 21 || (SigueJugando == false && totalPoints >= puntosJugador)) {
					SigueJugando = false;
				}
			}
		}
		else if (arrayBaraja[palos][num] == 0) {
			cartasRepartidas--;
		}

		valor = arrayCarta[palos][num];
		totalPoints = totalPoints + valor;
		arrayBaraja[palos][num] = 0;
		cout << "A " << nomJugador << " le ha salido un " << valor << " de " << palo << "\n";
		cout << "y tiene un total de " << totalPoints << " puntos \n";

	}
}

void seguirJugando(bool& SigueJugando) {
	cout << JugadorName << ", quieres seguir jugando?\n";
	int opcion;
	do {

		cout << "[1] Si\n";
		cout << "[2] No\n";
		cin >> opcion;
		switch (opcion) {

		case 1:
			repartoCartas(puntosJugador, baraja, valorCarta, 1, JugadorName, SigueJugando);
			Sleep(100);
			cout << "\n";
			break;
		case 2:

			SigueJugando = false;
			break;


		default:
			cout << "Eso no es opcion\n";
		}
	} while (opcion != 1 && opcion != 2);
}

void revisarGanador(string nomJugador) {

	if ((puntosJugador == 21 && (casinoPoints > 21 || casinoPoints < 21)) || (puntosJugador < 21 && casinoPoints > 21)) {
		cout << nomJugador << " ha ganado al casino, " << "\n";
		cout << "FELICIDADES!!" << "\n";
	}

	else if (casinoPoints == 21 && puntosJugador == 21) {
		cout << nomJugador << " has empatado al casino, " << "\n";
		
	}

	else if (puntosJugador > 21 || (puntosJugador < 21 && (puntosJugador < casinoPoints))) {
		cout << nomJugador << " has perdido contra el casino, " << "\n";
		
	}
	else { cout << "Eso no es un resltado posible\n"; }
}
int main() {
	srand(time(NULL));
	startGame();
	iniciBaraja(baraja, valorCarta);
	repartoCartas(puntosJugador, baraja, valorCarta, 2, JugadorName, JugadorSigueJugando);
	Sleep(100);
	cout << "\n";

	while ((JugadorSigueJugando == true || croupiereSigueJugando == true) && puntosJugador < 21) {
		if (croupiereSigueJugando == true) {
			repartoCartas(casinoPoints, baraja, valorCarta, 1, croupiereName, croupiereSigueJugando);
			Sleep(100);
			cout << "\n";
		}
		if (JugadorSigueJugando == true) {
			seguirJugando(JugadorSigueJugando);
			Sleep(100);
			cout << "\n";
		}
	}

	revisarGanador(JugadorName);
}

