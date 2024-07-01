#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <utility>
#include <conio.h> 

using namespace std;

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

void agregarEmpleado() {
    Empleado nuevoEmpleado;
    cout << "*********************************************" << endl;
    cout << "* NOMBRE DEL EMPLEADO *    ";
    cin.ignore();
    getline(cin, nuevoEmpleado.nombre);
    cout << "*********************************************" << endl;
    empleados.push_back(nuevoEmpleado);
}

void mostrarEmpleados() {
    cout << "*********************************************" << endl;
    cout << "*       LISTA DE EMPLEADOS REGISTRADOS      *" << endl;
    cout << "*********************************************" << endl;
    for (size_t i = 0; i < empleados.size(); ++i) {
        cout << "* " << i + 1 << ". " << empleados[i].nombre << " *" << endl;
    }
    cout << "*********************************************" << endl;
}

void registrarAsistencia() {
    mostrarEmpleados();
    cout << "Seleccione el numero del empleado: ";
    int indice;
    cin >> indice;
    if (indice < 1 || indice > empleados.size()) {
        cout << "Empleado no encontrado." << endl;
        return;
    }

    Empleado& empleado = empleados[indice - 1];
    const double Pago_Por_Hora = 45;
    int entradaHora, salidaHora;
    string fecha;

    cout << "*********************************************" << endl;
    cout << "*        FECHA (DD/MM/AAAA) *     ";
    cin >> fecha;
    cout << "*********************************************" << endl;
    cout << "*   HORA DE ENTRADA   *           ";
    cin >> entradaHora;
    cout << "*********************************************" << endl;
    cout << "*   HORA DE SALIDA    *           ";
    cin >> salidaHora;
    cout << "*********************************************" << endl;

    double horasTrabajadas = calcularHorasTrabajadas(entradaHora, salidaHora);
    double pagoDiario = horasTrabajadas * Pago_Por_Hora;

    empleado.asistencia.push_back(make_pair(fecha, make_pair(entradaHora, salidaHora)));

    cout << "*  HORAS DE TRABAJO   *     " << fixed << setprecision(2) << horasTrabajadas << " HORAS     *" << endl;
    cout << "*********************************************" << endl;
    cout << "* PAGO CORRESPONDIENTE*       " << fixed << setprecision(2) << pagoDiario << " PESOS  *" << endl;
    cout << "*********************************************" << endl;
}

void mostrarAsistencia() {
    mostrarEmpleados();
    cout << "Seleccione el numero del empleado: ";
    int indice;
    cin >> indice;
    if (indice < 1 || indice > empleados.size()) {
        cout << "Empleado no encontrado. " << endl;
        return;
    }

    Empleado& empleado = empleados[indice - 1];
    cout << "*********************************************" << endl;
    cout << "*  REGISTRO DE ASISTENCIA DE " << empleado.nombre << "  *" << endl;
    cout << "*********************************************" << endl;

    double totalPagoMensual = 0.0;
    const double PAGO_POR_HORA = 45;

    for (const auto& registro : empleado.asistencia) {
        string fecha = registro.first;
        int entradaHora = registro.second.first;
        int salidaHora = registro.second.second;

        double horasTrabajadas = calcularHorasTrabajadas(entradaHora, salidaHora);
        double pagoDiario = horasTrabajadas * PAGO_POR_HORA;

        cout << "* Fecha: " << fecha << " * Entrada: " << entradaHora << " * Salida: " << salidaHora << " *" << endl;
        cout << "* Horas Trabajadas: " << fixed << setprecision(2) << horasTrabajadas << " * Pago: " << fixed << setprecision(2) << pagoDiario << " *" << endl;
        cout << "*********************************************" << endl;

        totalPagoMensual += pagoDiario;
    }

    cout << "* PAGO MENSUAL TOTAL: " << fixed << setprecision(2) << totalPagoMensual << " PESOS *" << endl;
    cout << "*********************************************" << endl;
}

void actualizarEmpleado() {
    mostrarEmpleados();
    cout << "Seleccione el numero del empleado a actualizar: ";
    int indice;
    cin >> indice;
    if (indice < 1 || indice > empleados.size()) {
        cout << "Empleado no encontrado." << endl;
        return;
    }

    Empleado& empleado = empleados[indice - 1];
    cout << "Nuevo nombre del empleado: ";
    cin.ignore();
    getline(cin, empleado.nombre);
    cout << "Empleado actualizado correctamente. " << endl;
}

void eliminarEmpleado() {
    mostrarEmpleados();
    cout << "Seleccione el numero del empleado a eliminar: ";
    int indice;
    cin >> indice;
    if (indice < 1 || indice > empleados.size()) {
        cout << "Empleado no encontrado." << endl;
        return;
    }

    empleados.erase(empleados.begin() + indice - 1);
    cout << "Empleado eliminado exitosamente." << endl;
}

void registrarInasistencia() {
    mostrarEmpleados();
    cout << "Seleccione el numero del empleado: ";
    int indice;
    cin >> indice;
    if (indice < 1 || indice > empleados.size()) {
        cout << "Empleado no encontrado." << endl;
        return;
    }

    Empleado& empleado = empleados[indice - 1];
    string fecha, motivo;

    cout << "*********************************************" << endl;
    cout << "*        FECHA (DD/MM/AAAA) *     ";
    cin.ignore();
    getline(cin, fecha);
    cout << "*********************************************" << endl;
    cout << "*   MOTIVO DE INASISTENCIA   *     ";
    getline(cin, motivo);
    cout << "*********************************************" << endl;

    empleado.inasistencias.push_back(make_pair(fecha, motivo));

    cout << "Inasistencia registrada correctamente." << endl;
}

void reporteInasistencias() {
    cout << "*********************************************" << endl;
    cout << "*          REPORTE DE INASISTENCIAS         *" << endl;
    cout << "*********************************************" << endl;

    for (const auto& empleado : empleados) {
        if (empleado.inasistencias.empty()) {
            continue;
        }

        cout << "* Empleado: " << empleado.nombre << " *" << endl;

        for (const auto& inasistencia : empleado.inasistencias) {
            string fecha = inasistencia.first;
            string motivo = inasistencia.second;

            cout << "* Fecha: " << fecha << " * Motivo: " << motivo << " *" << endl;
            cout << "*********************************************" << endl;
        }
    }
}

void menu() {
    vector<string> opciones = {
        "1. Agregar Empleado",
        "2. Registrar Asistencia",
        "3. Mostrar Asistencia",
        "4. Actualizar Empleado",
        "5. Eliminar Empleado",
        "6. Registrar Inasistencia",
        "7. Reporte de Inasistencias",
        "8. Salir"
    };

    int opcion = 0;

    while (true) {
        system("cls"); 
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
                    cout << "Saliendo del sistema..." << endl;
                    return;
                default:
                    cout << "Opcion invalida, intente nuevamente." << endl;
            }
            cout << "Presione cualquier tecla para continuar...";
            _getch(); 
        }
    }
}

int main() {
    menu();
    return 0;
}

