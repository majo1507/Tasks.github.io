#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <crow.h>  // Incluir la librería Crow

using namespace std;

// Estructura para representar una tarea
struct Tarea {
    string nombre;
    string prioridad;  // "alta", "media", "baja"
    Tarea(string n, string p) : nombre(n), prioridad(p) {}
};

// Colas para tareas en espera (en espera)
queue<Tarea> tareasEnEspera;

// Pila para tareas desechadas
stack<Tarea> tareasDesechadas;

// Función para agregar una tarea
void agregarTarea(const string& nombre, const string& prioridad) {
    if (prioridad != "alta" && prioridad != "media" && prioridad != "baja") {
        cout << "Prioridad no válida, la tarea no se agregará.\n";
        return;
    }
    Tarea nuevaTarea(nombre, prioridad);
    tareasEnEspera.push(nuevaTarea);
}

// Función para obtener las tareas en espera
string verTareasEnEspera() {
    if (tareasEnEspera.empty()) {
        return "No hay tareas en espera.\n";
    }
    string resultado = "Tareas en espera:\n";
    queue<Tarea> temp = tareasEnEspera;
    while (!temp.empty()) {
        Tarea tarea = temp.front();
        resultado += "Tarea: " + tarea.nombre + " | Prioridad: " + tarea.prioridad + "\n";
        temp.pop();
    }
    return resultado;
}

// Función para desechar una tarea
string desecharTarea(const string& nombre) {
    if (tareasEnEspera.empty()) {
        return "No hay tareas en espera para desechar.\n";
    }

    bool encontrado = false;
    queue<Tarea> temp;
    while (!tareasEnEspera.empty()) {
        Tarea tarea = tareasEnEspera.front();
        tareasEnEspera.pop();

        if (tarea.nombre == nombre) {
            tareasDesechadas.push(tarea);
            encontrado = true;
            break;
        }
        temp.push(tarea);
    }

    while (!temp.empty()) {
        tareasEnEspera.push(temp.front());
        temp.pop();
    }

    if (encontrado) {
        return "Tarea '" + nombre + "' desechada.\n";
    } else {
        return "Tarea no encontrada en espera.\n";
    }
}

// Función para revertir una tarea desechada
string revertirTarea(const string& nombre) {
    if (tareasDesechadas.empty()) {
        return "No hay tareas desechadas para revertir.\n";
    }

    bool encontrado = false;
    stack<Tarea> temp;
    while (!tareasDesechadas.empty()) {
        Tarea tarea = tareasDesechadas.top();
        tareasDesechadas.pop();

        if (tarea.nombre == nombre) {
            tareasEnEspera.push(tarea);
            encontrado = true;
            break;
        }

        temp.push(tarea);
    }

    while (!temp.empty()) {
        tareasDesechadas.push(temp.top());
        temp.pop();
    }

    if (encontrado) {
        return "Tarea '" + nombre + "' revertida a espera.\n";
    } else {
        return "Tarea no encontrada en desechadas.\n";
    }
}

// Definir rutas en el servidor web
int main() {
    crow::SimpleApp app;

    // Ruta para agregar tarea (POST)
    CROW_ROUTE(app, "/agregar_tarea/<string>/<string>").methods("POST"_method)
    ([&](const string& nombre, const string& prioridad){
        agregarTarea(nombre, prioridad);
        return "Tarea agregada a espera.";
    });

    // Ruta para ver tareas en espera (GET)
    CROW_ROUTE(app, "/ver_tareas_en_espera").methods("GET"_method)
    ([&](){
        return verTareasEnEspera();
    });

    // Ruta para desechar tarea (POST)
    CROW_ROUTE(app, "/desechar_tarea/<string>").methods("POST"_method)
    ([&](const string& nombre){
        return desecharTarea(nombre);
    });

    // Ruta para revertir tarea desechada (POST)
    CROW_ROUTE(app, "/revertir_tarea/<string>").methods("POST"_method)
    ([&](const string& nombre){
        return revertirTarea(nombre);
    });

    // Iniciar servidor en el puerto 8080
    app.port(8080).run();

    return 0;
}
