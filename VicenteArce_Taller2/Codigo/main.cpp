#include <ctime>
#include "Clique.h"
#include "Menu.h"

int main(){
    Menu *menu = new Menu();    // Creamos un objeto de la clase Menu
    menu->menu();        // Llamamos al metodo menu
    menu->~Menu();        
    return 0;
}