#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <vector>
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void processInput(); // Procesar entradas del usuario

private:
    Ui::MainWindow *ui;

    std::vector<std::string> tiendas;               // Nombres de las tiendas
    std::vector<std::string> ciudades;             // Nombres de las ciudades
    std::vector<int> ofertaTiendas;                // Oferta disponible en cada tienda
    std::vector<std::vector<double>> costos;       // Matriz de costos de transporte
    void setupData(); // Inicializar datos
    void handleLogic(const QString& input); // Lógica principal
    void mostrarResultados(const std::vector<std::vector<int>>& sol,
                           const std::vector<std::vector<double>>& costos);

    // Nueva función para generar resultados como texto
    QString obtenerResultadosComoTexto(const std::vector<std::vector<int>>& sol,
                                       const std::vector<std::vector<double>>& costos);

};
#endif // MAINWINDOW_H
