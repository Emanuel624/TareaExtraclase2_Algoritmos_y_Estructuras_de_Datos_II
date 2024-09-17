#include <QApplication>
#include <QWidget>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);  // Crear la aplicación

    QWidget window;  // Crear una ventana
    window.resize(400, 350);  // Definir el tamaño de la ventana
    window.setWindowTitle("Ventana básica en Qt");  // Título de la ventana
    window.show();  // Mostrar la ventana

    return app.exec();  // Ejecutar el ciclo de eventos de Qt
}
