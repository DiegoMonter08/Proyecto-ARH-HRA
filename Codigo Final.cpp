#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <utility>

using namespace std;

struct Empleado {
    string nombre;
    vector<pair<string, pair<int, int>>> asistencia;
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
  empleados.push_back (nuevoEmpleado);
}

void mostrarEmpleados() {
  cout << "*********************************************" << endl;
  cout << "*       LISTA DE EMPLEADOS REGISTRADOS      *" << endl;
  cout << "*********************************************" << endl;
  for (size_t i = 0; i < empleados.size(); ++i){
    cout << "* " << i+1 << ". " << empleados[i].nombre << " *" << endl;
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
cin. ignore();
getline (cin, empleado.nombre);
cout << "Empleado actualizado correctamente. " <<endl;
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

  int main() {
      int opcion;
      do {
          cout << "*********************************************" << endl;
          cout << "* 1. Agregar Empleado                       *" << endl;
          cout << "* 2. Registrar Asistencia                   *" << endl;
          cout << "* 3. Mostrar Asistencia                     *" << endl;
          cout << "* 4. Actualizar Empleado                    *" << endl;
          cout << "* 5. Eliminar Empleado                      *" << endl;
          cout << "* 6. Salir                                  *" << endl;
          cout << "*********************************************" << endl;
          cout << "Seleccione una opcion: ";
          cin >> opcion;

            switch (opcion) {
                case 1:
                    agregarEmpleado();
                    break;
                case 2:
                    registrarAsistencia();
                    break;
                case 3:
                    mostrarAsistencia();
                    break;
                case 4:
                    actualizarEmpleado();
                    break;
                case 5:
                    eliminarEmpleado();
                    break;
                case 6:
                    cout << "Saliendo del sistema..." << endl;
                    break;
                default:
                    cout << "Opcion invalida, intente nuevamente." << endl;
            }
        } while (opcion != 6);

        return 0;

}

