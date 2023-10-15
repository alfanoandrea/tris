#include <iostream>
#include <random>
#include <string>
#include <thread>
#include <chrono>

class Color {
public:
    static std::string red;
    static std::string cyan;
    static std::string green;
    static std::string yellow;
    static std::string gray;
    static std::string reset;
};


std::string Color::red = "\u001b[31m";
std::string Color::cyan = "\u001b[36m";
std::string Color::green = "\u001b[32m";
std::string Color::yellow = "\u001b[33m";
std::string Color::gray = "\033[90m";
std::string Color::reset = "\u001b[0m";


void cls() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void loadGriglia(std::string griglia[3][3]) {
    int cont = 1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            griglia[i][j] = std::to_string(cont);
            cont++;
        }
    }
}

void intro() {
    std::cout << "   ____  ___   __  ___ \n";
    std::cout << "  (_  _)(  ,) (  )/ __)\n";
    std::cout << "    )(   )  \\  )( \\__ \\\n";
    std::cout << "   (__) (_)\\_)(__)(___/\n\n";
    std::cout << Color::cyan << "      by alfanowski\n" << Color::red;
    std::cout << "  ---------------------\n" << Color::reset;
}

void printGriglia(std::string griglia[3][3]) {
    std::cout.flush();
    cls();
    intro();
    for (int i = 0; i < 3; i++) {
        std::cout << "\n";
        if (i != 0)
            std::cout << "       " << Color::cyan << "---|---|---" << Color::reset << "\n\t";
        else
            std::cout << "\t";
        for (int j = 0; j < 3; j++) {
            if (j != 2) {
                if (griglia[i][j] == "X" or griglia[i][j] == "O")
                    std::cout << griglia[i][j] << Color::cyan << " | " << Color::reset;
                else
                    std::cout << Color::gray << griglia[i][j] << Color::cyan << " | " << Color::reset;
            }
            else {
                if (griglia[i][j] == "X" or griglia[i][j] == "O")
                    std::cout << griglia[i][j];
                else
                    std::cout << Color::gray << griglia[i][j] << Color::reset;
            }
        }
    }
}

void sostituzione(std::string griglia[3][3], char carattere) {
    int selezione;
    std::string sel;
    bool controllo = false;
    do {
        if (carattere == 'X') {
            do {
                printGriglia(griglia);
                std::cout << Color::yellow << "\n\n   place the 'X': " << Color::reset;
                std::cin >> sel;
                try {
                    selezione = std::stoi(sel);
                }
                catch (const std::invalid_argument&) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    selezione = -1;
                }
            } while (selezione < 1 or selezione > 9);
        } else if (carattere == 'O') {
            printGriglia(griglia);
            std::cout << Color::yellow << "\n\n   opponent's turn... " << Color::reset;
            selezione = rand() % 9 + 1;
        }
        int riga = (selezione - 1) / 3;
        int colonna = (selezione - 1) % 3;
        if (griglia[riga][colonna] != "O" and griglia[riga][colonna] != "X") {
            controllo = true;
            griglia[riga][colonna] = carattere;
        }
    } while (!controllo);
}

char turno(int cont) {
    if (cont % 2 == 0)
        return 'X';
    else
        return 'O';
}

bool controlloVittoria(std::string griglia[3][3], char carattere) {
	std::string vittoria;
	if (carattere == 'X')
		vittoria = Color::green;
	else if (carattere == 'O')
		vittoria = Color::red;
    if (griglia[0][0] == griglia[0][1] and griglia[0][1] == griglia[0][2]) {
        griglia[0][0] = vittoria + griglia[0][0] + Color::reset;
        griglia[0][1] = vittoria + griglia[0][1] + Color::reset;
        griglia[0][2] = vittoria + griglia[0][2] + Color::reset;
        return true;
    }
    else if (griglia[1][0] == griglia[1][1] and griglia[1][1] == griglia[1][2]) {
        griglia[1][0] = vittoria + griglia[1][0] + Color::reset;
        griglia[1][1] = vittoria + griglia[1][1] + Color::reset;
        griglia[1][2] = vittoria + griglia[1][2] + Color::reset;
        return true;
    }
    else if (griglia[2][0] == griglia[2][1] and griglia[2][1] == griglia[2][2]) {
        griglia[2][0] = vittoria + griglia[2][0] + Color::reset;
        griglia[2][1] = vittoria + griglia[2][1] + Color::reset;
        griglia[2][2] = vittoria + griglia[0][2] + Color::reset;
        return true;
    }
    else if (griglia[0][0] == griglia[1][0] and griglia[1][0] == griglia[2][0]) {
        griglia[0][0] = vittoria + griglia[0][0] + Color::reset;
        griglia[1][0] = vittoria + griglia[1][0] + Color::reset;
        griglia[2][0] = vittoria + griglia[2][0] + Color::reset;
        return true;
    }
    else if (griglia[0][1] == griglia[1][1] and griglia[1][1] == griglia[2][1]) {
        griglia[0][1] = vittoria + griglia[0][1] + Color::reset;
        griglia[1][1] = vittoria + griglia[1][1] + Color::reset;
        griglia[2][1] = vittoria + griglia[2][1] + Color::reset;
        return true;
    }
    else if (griglia[0][2] == griglia[1][2] and griglia[1][2] == griglia[2][2]) {
        griglia[0][2] = vittoria + griglia[0][2] + Color::reset;
        griglia[1][2] = vittoria + griglia[1][2] + Color::reset;
        griglia[2][2] = vittoria + griglia[2][2] + Color::reset;
        return true;
    }
    else if (griglia[0][0] == griglia[1][1] and griglia[1][1] == griglia[2][2]) {
        griglia[0][0] = vittoria + griglia[0][0] + Color::reset;
        griglia[1][1] = vittoria + griglia[1][1] + Color::reset;
        griglia[2][2] = vittoria + griglia[2][2] + Color::reset;
        return true;
    }
    else if (griglia[0][2] == griglia[1][1] and griglia[1][1] == griglia[2][0]) {
        griglia[0][2] = vittoria + griglia[0][2] + Color::reset;
        griglia[1][1] = vittoria + griglia[2][1] + Color::reset;
        griglia[2][0] = vittoria + griglia[2][0] + Color::reset;
        return true;
    }
    else
        return false;
}


int main() {
    srand(time(NULL));
	std::string griglia[3][3];
    char carattere;
    int cont = rand() % 2;
	loadGriglia(griglia);
    for (int i = 0; i < 8; i++) {
        carattere = turno(cont);
        sostituzione(griglia, carattere);
        std::cout.flush();
        if (carattere == 'O')
            std::this_thread::sleep_for(std::chrono::milliseconds(1500));
        if (controlloVittoria(griglia, carattere))
            break;
        cont++;
    }
    printGriglia(griglia);
    getchar();
    std::cout << "\n\n";
    getchar();
    cls();
}
