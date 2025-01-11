#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QString>
#include <sstream>
#include <vector>

#include <algorithm>
#include <iostream>

// Método de la Esquina Noroeste
void esquinaNoroeste(const std::vector<std::string>& tiendas,
                     const std::vector<int>& oferta,
                     const std::vector<int>& demanda,
                     std::vector<std::vector<int>>& sol) {
    int n = tiendas.size();
    int m = demanda.size();
    std::vector<int> ofertaRestante = oferta;
    std::vector<int> demandaRestante = demanda;

    sol.assign(n, std::vector<int>(m, 0));

    int i = 0, j = 0;
    while (i < n && j < m) {
        int asignar = std::min(ofertaRestante[i], demandaRestante[j]);
        sol[i][j] = asignar;

        ofertaRestante[i] -= asignar;
        demandaRestante[j] -= asignar;

        if (ofertaRestante[i] == 0) i++;
        if (demandaRestante[j] == 0) j++;
    }
}






// Método de Mínimo Costo
void costoMinimo(const std::vector<std::string>& tiendas,
                 const std::vector<int>& oferta,
                 const std::vector<int>& demanda,
                 const std::vector<std::vector<double>>& costos,
                 std::vector<std::vector<int>>& sol) {
    int n = tiendas.size();
    int m = demanda.size();
    std::vector<int> ofertaRestante = oferta;
    std::vector<int> demandaRestante = demanda;

    sol.assign(n, std::vector<int>(m, 0));

    while (true) {
        double minCost = std::numeric_limits<double>::max();
        int row = -1, col = -1;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (ofertaRestante[i] > 0 && demandaRestante[j] > 0 && costos[i][j] < minCost) {
                    minCost = costos[i][j];
                    row = i;
                    col = j;
                }
            }
        }

        if (row == -1 || col == -1) break;

        int asignar = std::min(ofertaRestante[row], demandaRestante[col]);
        sol[row][col] = asignar;
        ofertaRestante[row] -= asignar;
        demandaRestante[col] -= asignar;
    }
}







// Método de Aproximación de Vogel
void aproximacionVogel(const std::vector<std::string>& tiendas,
                       const std::vector<int>& oferta,
                       const std::vector<int>& demanda,
                       const std::vector<std::vector<double>>& costos,
                       std::vector<std::vector<int>>& sol) {
    int n = tiendas.size();
    int m = demanda.size();
    std::vector<int> ofertaRestante = oferta;
    std::vector<int> demandaRestante = demanda;

    sol.assign(n, std::vector<int>(m, 0)); // Inicializamos la solución con ceros.

    while (true) {
        // Calcular penalidades para filas y columnas.
        std::vector<int> rowPenalty(n, 0);
        std::vector<int> colPenalty(m, 0);

        // Penalidades para filas.
        for (int i = 0; i < n; ++i) {
            if (ofertaRestante[i] > 0) {
                double min1 = std::numeric_limits<double>::max();
                double min2 = std::numeric_limits<double>::max();
                for (int j = 0; j < m; ++j) {
                    if (demandaRestante[j] > 0) {
                        if (costos[i][j] < min1) {
                            min2 = min1;
                            min1 = costos[i][j];
                        } else if (costos[i][j] < min2) {
                            min2 = costos[i][j];
                        }
                    }
                }
                rowPenalty[i] = (min2 == std::numeric_limits<double>::max()) ? min1 : min2 - min1;
            }
        }

        // Penalidades para columnas.
        for (int j = 0; j < m; ++j) {
            if (demandaRestante[j] > 0) {
                double min1 = std::numeric_limits<double>::max();
                double min2 = std::numeric_limits<double>::max();
                for (int i = 0; i < n; ++i) {
                    if (ofertaRestante[i] > 0) {
                        if (costos[i][j] < min1) {
                            min2 = min1;
                            min1 = costos[i][j];
                        } else if (costos[i][j] < min2) {
                            min2 = costos[i][j];
                        }
                    }
                }
                colPenalty[j] = (min2 == std::numeric_limits<double>::max()) ? min1 : min2 - min1;
            }
        }

        // Encontrar la penalidad máxima.
        int maxRow = -1, maxCol = -1;
        int maxPenalty = -1;

        for (int i = 0; i < n; ++i) {
            if (ofertaRestante[i] > 0 && rowPenalty[i] > maxPenalty) {
                maxPenalty = rowPenalty[i];
                maxRow = i;
                maxCol = -1;
            }
        }

        for (int j = 0; j < m; ++j) {
            if (demandaRestante[j] > 0 && colPenalty[j] > maxPenalty) {
                maxPenalty = colPenalty[j];
                maxCol = j;
                maxRow = -1;
            }
        }

        // Si no hay penalidades válidas, hemos terminado.
        if (maxRow == -1 && maxCol == -1) {
            break;
        }

        // Determinar la celda a asignar.
        int selectedRow = -1, selectedCol = -1;

        if (maxRow != -1) {
            selectedRow = maxRow;
            double minCost = std::numeric_limits<double>::max();
            for (int j = 0; j < m; ++j) {
                if (demandaRestante[j] > 0 && costos[maxRow][j] < minCost) {
                    minCost = costos[maxRow][j];
                    selectedCol = j;
                }
            }
        } else if (maxCol != -1) {
            selectedCol = maxCol;
            double minCost = std::numeric_limits<double>::max();
            for (int i = 0; i < n; ++i) {
                if (ofertaRestante[i] > 0 && costos[i][maxCol] < minCost) {
                    minCost = costos[i][maxCol];
                    selectedRow = i;
                }
            }
        }

        // Asignar la cantidad mínima entre oferta y demanda restante.
        int asignar = std::min(ofertaRestante[selectedRow], demandaRestante[selectedCol]);
        sol[selectedRow][selectedCol] = asignar;
        ofertaRestante[selectedRow] -= asignar;
        demandaRestante[selectedCol] -= asignar;
    }
}






void MainWindow::mostrarResultados(const std::vector<std::vector<int>>& sol, const std::vector<std::vector<double>>& costos) {
    QString resultado;
    double costoTotal = 0;

    resultado += "Resultados del algoritmo:\n\n";
    resultado += "Asignaciones:\n";

    for (size_t i = 0; i < sol.size(); ++i) {
        for (size_t j = 0; j < sol[i].size(); ++j) {
            if (sol[i][j] > 0) { // Mostrar solo las asignaciones no nulas
                resultado += QString::fromStdString(tiendas[i]) + " -> " +
                             QString::fromStdString(ciudades[j]) +
                             ": " + QString::number(sol[i][j]) + " unidades (Costo: $" +
                             QString::number(costos[i][j] * sol[i][j], 'f', 2) + ")\n";
                costoTotal += costos[i][j] * sol[i][j];
            }
        }
    }

    resultado += "\nCosto total: $" + QString::number(costoTotal, 'f', 2) + "\n";

    ui->labelConsole->setText(resultado);
}


QString MainWindow::obtenerResultadosComoTexto(const std::vector<std::vector<int>>& sol,
                                               const std::vector<std::vector<double>>& costos) {
    QString resultado;
    double costoTotal = 0;

    resultado += "Asignaciones:\n";

    for (size_t i = 0; i < sol.size(); ++i) {
        for (size_t j = 0; j < sol[i].size(); ++j) {
            if (sol[i][j] > 0) { // Mostrar solo las asignaciones no nulas
                resultado += QString::fromStdString(tiendas[i]) + " -> " +
                             QString::fromStdString(ciudades[j]) +
                             ": " + QString::number(sol[i][j]) + " unidades (Costo: $" +
                             QString::number(costos[i][j] * sol[i][j], 'f', 2) + ")\n";
                costoTotal += costos[i][j] * sol[i][j];
            }
        }
    }

    resultado += "Costo total: $" + QString::number(costoTotal, 'f', 2) + "\n";
    return resultado;
}






MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Conectar el QLineEdit con la función para procesar la entrada
    connect(ui->inputField, &QLineEdit::returnPressed, this, &MainWindow::processInput);

    setupData(); // Inicializar datos iniciales
    ui->labelConsole->setText("Hola, bienvenidos al servicio de paquetería.\n"
                              "Por favor indique el número de las ciudades a las que quiere repartir el producto:\n");
    for (size_t i = 0; i < ciudades.size(); ++i) {
        ui->labelConsole->setText(ui->labelConsole->text() + QString::number(i + 1) + ". " + QString::fromStdString(ciudades[i]) + "\n");
    }
    ui->labelConsole->setText(ui->labelConsole->text() + "\nIngrese los números de las ciudades separados por espacio (ej: 1 3 5). Presione Enter al finalizar:");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupData()
{
    // Nombres de las tiendas
    tiendas = {"Hualpen", "Lota", "Concepcion"};

    // Nombres de las ciudades
    ciudades = {"Lota", "Hualpen", "Talcahuano", "Concepcion", "Penco", "Hualqui"};

    // Oferta de las tiendas
    ofertaTiendas = {600, 800, 1000};

    // Inicializar la matriz de costos (costo de transporte desde cada tienda a cada ciudad)
    costos = {
        {5137.5, 0, 950, 1162.5, 2300, 3700}, // Costos desde la tienda "Hualpen"
        {0, 5137.5, 6087.5, 4875, 6512.5, 8150}, // Costos desde la tienda "Lota"
        {4875, 1162.5, 1950, 0, 1637.5, 3275}  // Costos desde la tienda "Concepcion"
    };
}

void MainWindow::processInput()
{
    QString input = ui->inputField->text();
    ui->inputField->clear();

    handleLogic(input);
}

void MainWindow::handleLogic(const QString& input)
{
    static int step = 0;
    static std::vector<int> ciudadesSeleccionadas;
    static std::vector<int> cantidades;

    if (step == 0) {
        std::stringstream ss(input.toStdString());
        int num;
        while (ss >> num) {
            if (num >= 1 && num <= static_cast<int>(ciudades.size())) {
                ciudadesSeleccionadas.push_back(num - 1);
            }
        }
        if (ciudadesSeleccionadas.empty()) {
            ui->labelConsole->setText("Por favor, ingrese números válidos de ciudades.");
            return;
        }
        ui->labelConsole->setText("Ingrese las cantidades de productos para cada ciudad seleccionada separados por espacios:\n");
        for (int i : ciudadesSeleccionadas) {
            ui->labelConsole->setText(ui->labelConsole->text() + QString::fromStdString(ciudades[i]) + ", ");
        }
        step++;
    } else if (step == 1) {
        std::stringstream ss(input.toStdString());
        int cantidad;
        while (ss >> cantidad) {
            cantidades.push_back(cantidad);
        }
        if (cantidades.size() != ciudadesSeleccionadas.size()) {
            ui->labelConsole->setText("Por favor, ingrese cantidades válidas para todas las ciudades seleccionadas.");
            return;
        }
        ui->labelConsole->setText("Seleccione el método para resolver el problema de transporte:\n"
                                  "1. Aproximación de Vogel\n"
                                  "2. Costo Mínimo\n"
                                  "3. Esquina Noroeste\n"
                                  "4. Ejecutar los 3 algoritmos");
        step++;
    } else if (step == 2) {
        int metodo = input.toInt();
        if (metodo < 1 || metodo > 4) {
            ui->labelConsole->setText("Por favor, seleccione un método válido (1-4).");
            return;
        }

        std::vector<std::vector<int>> solucion;

        if (metodo == 1) {
            ui->labelConsole->setText("Ejecutando Aproximación de Vogel...\n");
            aproximacionVogel(tiendas, ofertaTiendas, cantidades, costos, solucion);
            mostrarResultados(solucion, costos);
        } else if (metodo == 2) {
            ui->labelConsole->setText("Ejecutando Método de Costo Mínimo...\n");
            costoMinimo(tiendas, ofertaTiendas, cantidades, costos, solucion);
            mostrarResultados(solucion, costos);
        } else if (metodo == 3) {
            ui->labelConsole->setText("Ejecutando Método de la Esquina Noroeste...\n");
            esquinaNoroeste(tiendas, ofertaTiendas, cantidades, solucion);
            mostrarResultados(solucion, costos);
        } else if (metodo == 4) {
            QString resultados;

            // Ejecución y visualización de Aproximación de Vogel
            ui->labelConsole->setText("Ejecutando los 3 métodos...\n\nAproximación de Vogel:\n");
            solucion.clear();
            aproximacionVogel(tiendas, ofertaTiendas, cantidades, costos, solucion);
            resultados += "Aproximación de Vogel:\n";
            resultados += obtenerResultadosComoTexto(solucion, costos) + "\n";

            // Ejecución y visualización de Costo Mínimo
            solucion.clear();
            resultados += "Método de Costo Mínimo:\n";
            costoMinimo(tiendas, ofertaTiendas, cantidades, costos, solucion);
            resultados += obtenerResultadosComoTexto(solucion, costos) + "\n";

            // Ejecución y visualización de Esquina Noroeste
            solucion.clear();
            resultados += "Método de la Esquina Noroeste:\n";
            esquinaNoroeste(tiendas, ofertaTiendas, cantidades, solucion);
            resultados += obtenerResultadosComoTexto(solucion, costos) + "\n";

            // Mostrar los resultados concatenados
            ui->labelConsole->setText(resultados);
        }
    }
}






