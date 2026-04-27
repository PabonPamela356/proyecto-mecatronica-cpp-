#include <iostream>
#include <string>
#include <mysql.h>

using namespace std;

int main() {
    MYSQL* conexion;
    conexion = mysql_init(NULL);

    conexion = mysql_real_connect(conexion, "localhost", "root", "yato_777@", "nexus_academy", 3306, NULL, 0);

    if (!conexion) {
        cout << "Error de conexion: " << mysql_error(conexion) << endl;
        return 1;
    }

    int opcion;
    bool salir = false;

    while (!salir) {
        cout << "\n===== Sistema alumnos xd =====" << endl;
        cout << "1. Registrar alumno" << endl;
        cout << "2. Mostrar lista" << endl;
        cout << "3. Eliminar alumno" << endl;
        cout << "4. Cambiar nota" << endl;
        cout << "5. Top 5 notas" << endl;
        cout << "6. Alumnos con baja nota" << endl;
        cout << "7. Buscar por ID" << endl;
        cout << "8. Salir" << endl;
        cout << "Elige opcion: ";
        cin >> opcion;

        switch (opcion) {

        case 1: {
            int id;
            string nombre, apellido, celular;
            double nota;

            cout << "Ingrese el ID del alumno: ";
            cin >> id;
            cout << "Nombre: ";
            cin >> nombre;
            cout << "Apellido: ";
            cin >> apellido;
            cout << "Celular: ";
            cin >> celular;
            cout << "Nota final: ";
            cin >> nota;

            string consulta = "INSERT INTO alumnos VALUES(" +
                to_string(id) + ", '" + nombre + "', '" + apellido + "', '" +
                celular + "', " + to_string(nota) + ")";

            if (mysql_query(conexion, consulta.c_str()))
                cout << "No se pudo guardar\n";
            else
                cout << "Alumno guardado correctamente\n";

            break;
        }

          
        case 2: {
            string consulta = "SELECT * FROM alumnos";

            if (!mysql_query(conexion, consulta.c_str())) {
                MYSQL_RES* res = mysql_store_result(conexion);
                MYSQL_ROW fila;

                cout << "\n--- Lista de alumnos ---\n";

                while ((fila = mysql_fetch_row(res))) {
                    cout << "ID: " << fila[0] << " | "
                         << fila[1] << " " << fila[2] << " | Nota: "
                         << fila[4] << endl;
                }

                mysql_free_result(res);
            }
            break;
        }

        case 3: {
            int id;
            cout << "Ingrese ID a eliminar: ";
            cin >> id;

            string consulta = "DELETE FROM alumnos WHERE id=" + to_string(id);

            if (mysql_query(conexion, consulta.c_str()))
                cout << "Error al eliminar\n";
            else
                cout << "Alumno eliminado\n";

            break;
        }

        case 4: {
            int id;
            double nota;

            cout << "ID del alumno: ";
            cin >> id;
            cout << "Nueva nota: ";
            cin >> nota;

            string consulta = "UPDATE alumnos SET nota_final=" + to_string(nota) +
                              " WHERE id=" + to_string(id);

            if (mysql_query(conexion, consulta.c_str()))
                cout << "No se pudo actualizar...\n";
            else
                cout << "Nota cambiada\n";

            break;
        }

        case 5: {
            string consulta = "SELECT nombre, nota_final FROM alumnos ORDER BY nota_final DESC LIMIT 5";

            if (!mysql_query(conexion, consulta.c_str())) {
                MYSQL_RES* res = mysql_store_result(conexion);
                MYSQL_ROW fila;

                cout << "\nTop 5:\n";

                while ((fila = mysql_fetch_row(res))) {
                    cout << fila[0] << " -> " << fila[1] << endl;
                }

                mysql_free_result(res);
            }
            break;
        }

        case 6: {
            string consulta = "SELECT nombre, nota_final FROM alumnos WHERE nota_final < 4";

            if (!mysql_query(conexion, consulta.c_str())) {
                MYSQL_RES* res = mysql_store_result(conexion);
                MYSQL_ROW fila;

                cout << "\nEn riesgo:\n";

                while ((fila = mysql_fetch_row(res))) {
                    cout << fila[0] << " tiene " << fila[1] << endl;
                }

                mysql_free_result(res);
            }
            break;
        }

        case 7: {
            int id;
            cout << "Buscar alumno por su ID: ";
            cin >> id;

            string consulta = "SELECT * FROM alumnos WHERE id=" + to_string(id);

            if (!mysql_query(conexion, consulta.c_str())) {
                MYSQL_RES* res = mysql_store_result(conexion);
                MYSQL_ROW fila = mysql_fetch_row(res);

                if (fila) {
                    cout << "Encontrado: " << fila[1] << " " << fila[2]
                         << " con nota " << fila[4] << endl;
                } else {
                    cout << "No existe ese alumno\n";
                }

                mysql_free_result(res);
            }
            break;
        }

        case 8:
            cout << "Saliendo...\n";
            salir = true;
            break;

        default:
            cout << "La opcion no es valida\n";
        }
    }

    mysql_close(conexion);
    return 0;
}
