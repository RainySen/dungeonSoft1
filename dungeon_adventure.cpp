#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

class Direction {
    private:
    char directionKey;
    string direction_name;

    public:
    Direction(char dir) {
        directionKey = dir;
        switch (directionKey) {
            case 'w':
                direction_name = "North";
                break;
            case 's':
                direction_name = "South";
                break;
            case 'a':
                direction_name = "East";
                break;
            case 'd':
                direction_name = "West";
                break;
            default:
                direction_name = "Unknown";
        }
    }

    char getDirectionKey() {return directionKey;}
    string getDirectionName() {return direction_name;}
    bool isValid(){return direction_name != "Unknown";}
};

class Player {
    private:
    string player_name;
    int player_health;
    bool player_has_lockPick;
    bool player_has_compass;
    int player_score;

    public: Player (string name) {
        player_name = name;
        player_health = 80;
        player_has_lockPick = false;
        player_has_compass = false;
        player_score = 0;
    };

    string getPlayerName() {return player_name;}
    int getPlayerHealth() {return player_health;}
    bool hasPlayerHasLockPick() {return player_has_lockPick;}
    bool hasPlayerHasCompass() {return player_has_compass;}
    int getPlayerScore() {return player_score;}

    void setPlayerHealth(int health) {player_health = health;}
    void healPlayer(int healAmount) {player_health += healAmount;}
    void damagetaken(int damageAmount) {player_health -= damageAmount;}
    void addPlayerScore(int scoreAmount) {player_score += scoreAmount;}

    void pickUpLockPick() {player_has_lockPick = true; player_score ++;}
    void pickUpCompass() {player_has_compass = true;}

    void displayPlayerStats() {
        cout << "\n--- " << player_name << " ---" << endl;
        cout << "Health: " << player_health << endl;
        cout << "Score: " << player_score << endl;
        cout << "Inventory: " << endl;
        if (player_has_lockPick) {
            cout << "- [Lock Pick]" << endl;
        }
        if (player_has_compass) {
            cout << "- [Compass]" << endl;
        }
        if (!player_has_lockPick && !player_has_compass) {
            cout << "- [Empty]" << endl;
        }
    }
    
};

class Room {
    private:
    string room_name;
    string room_description;

    public:
    Room(string name, string description) {
        room_name = name;
        room_description = description;
    }

    string getRoomName() {return room_name;}
    string getRoomDescription() {return room_description;}
};

int main(){
    setlocale(LC_ALL, "spanish");
    
    Player player("Adventurer");
    Room entrance("sala de entrada", "hay una habitacion con dos pasajes");
    Room corridor("corredor oscuro", "un pasillo angosto, se escuchan gotas de fondo");

    cout << "\n========================================" << endl;
    cout << "  UNA PROFESORA DE GEOGRAFIA PERDIDA EN LAS MAZMORRAS" << endl;
    cout << "========================================" << endl;
    cout << "\nLa Profesora Maya Carter despierta en una mazmorra oscura..." << endl;
    cout << "\n--- RETROSPECTIVA ---" << endl;
    cout << "Maya Carter, de 42 anios, es profesora de geografia en la" << endl;
    cout << "Secundaria Riverside. La semana pasada, llevo a sus alumnos" << endl;
    cout << "a una excursion para estudiar formaciones de cuevas." << endl;
    cout << "Durante la expedicion, resbalo y cayo en un pasaje oculto." << endl;
    cout << "Desperto aqui, herida y sola, sin memoria de cuanto tiempo" << endl;
    cout << "ha estado inconsciente." << endl;
    cout << "\nSus heridas:" << endl;
    cout << "  - Esguince del tobillo izquierdo" << endl;
    cout << "  - Cortaduras y moretones en los brazos" << endl;
    cout << "  - Un golpe en la cabeza" << endl;
    cout << "\nDebe encontrar la salida antes de que sus alumnos" << endl;
    cout << "y colegas dejen de buscarla." << endl;
    cout << "========================================" << endl;


    cout << "\n--- " << entrance.getRoomName() << " ---" << endl;
    cout << entrance.getRoomDescription() << endl;
    cout << "[w] Arriba: Corredor oscuro, [s] Abajo: Muro bloqueado" << endl;

    while (true) {
        char entranceChoice;
        cout << "\n¿Hacia donde vas? (w/s): ";
        cin >> entranceChoice;

        Direction entranceDir(entranceChoice);
        if(entranceDir.isValid() && (entranceDir.getDirectionKey() == 'w' || entranceDir.getDirectionKey() == 'W')) {
            cout << "Entras en el corredor oscuro..." << endl;
            cout << "\n--- " << corridor.getRoomName() << " ---" << endl;
            cout << "Ves cuatro esquinas, a que direccion quieres ir?: ";
            char corridorChoice;
            cin >> corridorChoice;

            Direction dir(corridorChoice);

            if(dir.isValid()) {
                cout << "\nTe diriges hacia " << dir.getDirectionName() << "..." << endl;

                switch (dir.getDirectionKey()){
                    case 'w':
                    case 'W':
                        cout << "Encuentras una brújula" << endl;
                        player.pickUpCompass();
                        break;

                    case 's':
                    case 'S':
                        cout << "Sientes un frio penetrate" << endl;
                        cout << "Sin lugar seguro para descansar" << endl;
                        player.damagetaken(5);
                        cout << "-5 de daño por frio " << endl;
                        break;
                    
                    case 'a':
                    case 'A':
                        cout << "Encuentras una ganzua oxidada" << endl;
                        player.pickUpLockPick();
                        player.addPlayerScore(1);
                        break;

                    case 'd':
                    case 'D':
                        cout << "Has encontrado una puerta con llave" << endl;
                        cout << "Necesitas algo para abrirla" << endl;
                        break;
                }
            } else {
                cout << "Direccion invalida." << endl;
            }

            player.displayPlayerStats();

            cout << "\n--- a la espera de mas aventura  ---" << endl;
            break;

        }
        else if(entranceDir.isValid() && (entranceDir.getDirectionKey() == 's' || entranceDir.getDirectionKey() == 'S')) {
            cout << "Camino bloqueado - Guarda tu salud" << endl;
            player.damagetaken(3);
            player.displayPlayerStats();
        }
        else {
            cout << "Direccion invalida." << endl;
        }
    }

    cout << "\n--- Fin de la aventura ---" << endl;
    player.displayPlayerStats();


}
