#include "start.h"
#include <QApplication>

// Función principal de la aplicación
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);  // Inicializa la aplicación Qt

    Start Start;  // Crea la ventana de inicio
    Start.show();  // Muestra la ventana de inicio

    return a.exec();  // Entra en el bucle principal de eventos de Qt
}

//probando repositorio... xd
