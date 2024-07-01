#include <iostream>
#include <iomanip>
#include <conio.h>
#include <windows.h>
#include <string>
#include <vector>
#include <utility>
using namespace std;

#define COLOR_TEXTO     12

struct Empleado {
    string nombre;
    vector<pair<string, pair<int, int>>> asistencia;
    vector<pair<string, string>> inasistencias;
};

vector<Empleado> empleados;

double calcularHorasTrabajadas(int entradaHora, int salidaHora) {
    double horasTrabajadas = salidaHora - entradaHora;
    return horasTrabajadas;
}

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void limpiarPantalla() {
    system("cls");
}

void centrarTexto(const string& texto) {
    int anchoConsola = 80; // Ancho de la consola
    int espacioIzquierda = (anchoConsola - texto.length()) / 2;
    cout << string(espacioIzquierda, ' ') << texto << endl;
}

void mostrarAnimacionCarga(int segundos) {
    limpiarPantalla();
    setColor(COLOR_TEXTO);
    const string animacion = "|/-\\";

    int contador = 0;
    clock_t inicio = clock();
    clock_t fin = inicio + segundos * CLOCKS_PER_SEC;

    cout << " \n\n" << endl;
    centrarTexto("Cargando...");

    while (clock() < fin) {
        cout << "\r" << setw(20) << animacion[contador % animacion.size()];
        fflush(stdout);
        contador++;
        Sleep(100);
    }

    cout << "\rCarga completada!     " << endl;
}

void mostrarMensaje(const string& mensaje, const string& titulo) {
    MessageBox(NULL, mensaje.c_str(), titulo.c_str(), MB_ICONERROR | MB_OK);
}

void agregarEmpleado() {
    Empleado nuevoEmpleado;
    cout << "\033[1;32m*********************************************\033[0m" << endl;
    cout << "\033[1;32m* NOMBRE DEL EMPLEADO *    \033[0m";
    cin.ignore();
    getline(cin, nuevoEmpleado.nombre);
    cout << "\033[1;32m*********************************************\033[0m" << endl;
    empleados.push_back(nuevoEmpleado);
}

void mostrarEmpleados() {
    cout << "\033[1;33m*********************************************\033[0m" << endl;
    cout << "\033[1;33m*       LISTA DE EMPLEADOS REGISTRADOS      *\033[0m" << endl;
    cout << "\033[1;33m*********************************************\033[0m" << endl;
    for (size_t i = 0; i < empleados.size(); ++i) {
        cout << "\033[1;33m* " << i + 1 << ". " << empleados[i].nombre << " *\033[0m" << endl;
    }
    cout << "\033[1;33m*********************************************\033[0m" << endl;
}

void registrarAsistencia() {
    mostrarEmpleados();
    cout << "\033[1;34mSeleccione el numero del empleado: \033[0m";
    int indice;
    cin >> indice;
    if (indice < 1 || indice > empleados.size()) {
        mostrarMensaje("Empleado no encontrado.", "Error");
        return;
    }

    Empleado& empleado = empleados[indice - 1];
    const double Pago_Por_Hora = 45;
    int entradaHora, salidaHora;
    string fecha;

    cout << "\033[1;33m*********************************************\033[0m" << endl;
    cout << "\033[1;33m*        FECHA (DD/MM/AAAA) *     \033[0m";
    cin >> fecha;
    cout << "\033[1;33m*********************************************\033[0m" << endl;
    cout << "\033[1;33m*   HORA DE ENTRADA   *           \033[0m";
    cin >> entradaHora;
    cout << "\033[1;33m*********************************************\033[0m" << endl;
    cout << "\033[1;33m*   HORA DE SALIDA    *           \033[0m";
    cin >> salidaHora;
    cout << "\033[1;33m*********************************************\033[0m" << endl;

    double horasTrabajadas = calcularHorasTrabajadas(entradaHora, salidaHora);
    double pagoDiario = horasTrabajadas * Pago_Por_Hora;

    empleado.asistencia.push_back(make_pair(fecha, make_pair(entradaHora, salidaHora)));

    cout << "\033[1;33m*  HORAS DE TRABAJO   *     " << fixed << setprecision(2) << horasTrabajadas << " HORAS     *\033[0m" << endl;
    cout << "\033[1;33m*********************************************\033[0m" << endl;
    cout << "\033[1;33m* PAGO CORRESPONDIENTE*       " << fixed << setprecision(2) << pagoDiario << " PESOS  *\033[0m" << endl;
    cout << "\033[1;33m*********************************************\033[0m" << endl;
}

void mostrarAsistencia() {
    mostrarEmpleados();
    cout << "\033[1;34mSeleccione el numero del empleado: \033[0m";

    int indice;
    cin >> indice;
    if (indice < 1 || indice > empleados.size()) {
        mostrarMensaje("Empleado no encontrado.", "Error");
        return;
    }

    Empleado& empleado = empleados[indice - 1];
    cout << "\033[1;34m*********************************************\033[0m" << endl;
    cout << "\033[1;34m*  REGISTRO DE ASISTENCIA DE " << empleado.nombre << "  *\033[0m" << endl;
    cout << "\033[1;34m*********************************************\033[0m" << endl;

    double totalPagoMensual = 0.0;
    const double PAGO_POR_HORA = 45;

    for (const auto& registro : empleado.asistencia) {
        string fecha = registro.first;
        int entradaHora = registro.second.first;
        int salidaHora = registro.second.second;

        double horasTrabajadas = calcularHorasTrabajadas(entradaHora, salidaHora);
        double pagoDiario = horasTrabajadas * PAGO_POR_HORA;

        cout << "\033[1;34m* Fecha: " << fecha << " * Entrada: " << entradaHora << " * Salida: " << salidaHora << " *\033[0m" << endl;
        cout << "\033[1;34m* Horas Trabajadas: " << fixed << setprecision(2) << horasTrabajadas << " * Pago: " << fixed << setprecision(2) << pagoDiario << " *\033[0m" << endl;
        cout << "\033[1;34m*********************************************\033[0m" << endl;

        totalPagoMensual += pagoDiario;
    }

    cout << "\033[1;34m* PAGO MENSUAL TOTAL: " << fixed << setprecision(2) << totalPagoMensual << " PESOS *\033[0m" << endl;
    cout << "\033[1;34m*********************************************\033[0m" << endl;
}

void registrarInasistencia() {
    mostrarEmpleados();
    cout << "\033[1;35mSeleccione el numero del empleado: \033[0m";

    int indice;
    cin >> indice;
    if (indice < 1 || indice > empleados.size()) {
        mostrarMensaje("Empleado no encontrado.", "Error");
        return;
    }

    Empleado& empleado = empleados[indice - 1];
    string fecha, motivo;

    cout << "\033[1;35m*********************************************\033[0m" << endl;
    cout << "\033[1;35m*        FECHA (DD/MM/AAAA) *     \033[0m";

    cin >> fecha;
    cout << "\033[1;35m*********************************************\033[0m" << endl;
    cout << "\033[1;35m*        MOTIVO           *     \033[0m";
    cin.ignore();
    getline(cin, motivo);
    cout << "\033[1;35m*********************************************\033[0m" << endl;

    empleado.inasistencias.push_back(make_pair(fecha, motivo));

    cout << "\033[1;35m* INASISTENCIA REGISTRADA *\033[0m" << endl;
    cout << "\033[1;35m*********************************************\033[0m" << endl;
}

void reporteInasistencias() {
    cout << "\033[1;36m*********************************************\033[0m" << endl;
    cout << "\033[1;36m*       REPORTE DE INASISTENCIAS            *\033[0m" << endl;
    cout << "\033[1;36m*********************************************\033[0m" << endl;

    for (const auto& empleado : empleados) {
        cout << "\033[1;36m* Empleado: " << empleado.nombre << " *\033[0m" << endl;
        for (const auto& inasistencia : empleado.inasistencias) {
            cout << "\033[1;36m* Fecha: " << inasistencia.first << " * Motivo: " << inasistencia.second << " *\033[0m" << endl;
            cout << "\033[1;36m*********************************************\033[0m" << endl;
        }
    }
}

void actualizarEmpleado() {
    mostrarEmpleados();
    cout << "\033[1;37mSeleccione el numero del empleado a actualizar: \033[0m";
    int indice;
    cin >> indice;
    if (indice < 1 || indice > empleados.size()) {
        mostrarMensaje("Empleado no encontrado.", "Error");
        return;
    }

    Empleado& empleado = empleados[indice - 1];
    cout << "\033[1;37mNuevo nombre del empleado: \033[0m";
    cin.ignore();
    getline(cin, empleado.nombre);
    cout << "\033[1;37mEmpleado actualizado correctamente. \033[0m" << endl;
}

void eliminarEmpleado() {
    mostrarEmpleados();
    cout << "\033[1;38mSeleccione el numero del empleado a eliminar: \033[0m";
    int indice;
    cin >> indice;
    if (indice < 1 || indice > empleados.size()) {
        mostrarMensaje("Empleado no encontrado.", "Error");
        return;
    }

    empleados.erase(empleados.begin() + indice - 1);
    cout << "\033[1;38mEmpleado eliminado exitosamente.\033[0m" << endl;
}

void menu() {
    vector<string> opciones = {
        "\033[1;34m1. Agregar Empleado\033[0m",
        "\033[1;32m2. Registrar Asistencia\033[0m",
        "\033[1;32m3. Mostrar Asistencia\033[0m",
        "\033[1;34m4. Actualizar Empleado\033[0m",
        "\033[1;34m5. Eliminar Empleado\033[0m",
        "\033[1;36m6. Registrar Inasistencia\033[0m",
        "\033[1;36m7. Reporte de Inasistencias\033[0m",
        "\033[1;31m8. Salir\033[0m"
    };

    int opcion = 0;

    while (true) {
        limpiarPantalla();
        for (size_t i = 0; i < opciones.size(); ++i) {
            if (i == opcion) {
                cout << "> " << opciones[i] << endl;
            } else {
                cout << "  " << opciones[i] << endl;
            }
        }

        int key = _getch();

        if (key == 224) {
            switch (_getch()) {
                case 72:
                    if (opcion > 0) {
                        opcion--;
                    }
                    break;
                case 80:
                    if (opcion < opciones.size() - 1) {
                        opcion++;
                    }
                    break;
            }
        } else if (key == 13) {
            mostrarAnimacionCarga(1); // Muestra la animación de carga
            switch (opcion) {
                case 0:
                    agregarEmpleado();
                    break;
                case 1:
                    registrarAsistencia();
                    break;
                case 2:
                    mostrarAsistencia();
                    break;
                case 3:
                    actualizarEmpleado();
                    break;
                case 4:
                    eliminarEmpleado();
                    break;
                case 5:
                    registrarInasistencia();
                    break;
                case 6:
                    reporteInasistencias();
                    break;
                case 7:
                    cout << "\033[1;31mSaliendo del programa...\033[0m" << endl;
                    return;
                default:
                    mostrarMensaje("Opción no válida.", "Error");
                    break;
            }

            system("pause");
        }
    }
}

int main() {
    menu();
    return 0;
}

