#include <iostream>
#include <string>

using namespace std;

// Estructura para representar una venta
struct Venta {
    int cantidad;       // Cantidad de la venta
    Venta* siguiente;  // Puntero a la siguiente venta en la lista

    // Constructor de la estructura Venta
    Venta(int cant) : cantidad(cant), siguiente(nullptr) {}
};

// Estructura para representar un empleado
struct Empleado {
    string nombre;        // Nombre del empleado
    int ventasTotales;    // Total de ventas del empleado
    Empleado* siguiente;   // Puntero al siguiente empleado en la lista del piso
    Venta* listaVentas;   // Puntero a la primera venta del empleado

    // Constructor de la estructura Empleado
    Empleado(string nom) : nombre(nom), ventasTotales(0),
        siguiente(nullptr), listaVentas(nullptr) {}
};

// Estructura para representar un piso
struct Piso {
    int numero;              // Número del piso
    int ventasTotalesPiso;  // Total de ventas del piso
    Piso* anterior;         // Puntero al piso anterior 
    Piso* siguiente;         // Puntero al piso siguiente
    Empleado* listaEmpleados; // Puntero al primer empleado del piso

    // Constructor de la estructura Piso
    Piso(int num) : numero(num), ventasTotalesPiso(0),
        anterior(nullptr), siguiente(nullptr), listaEmpleados(nullptr) {}
};

// Función para insertar un nuevo empleado en un piso, 
// manteniendo el orden alfabético por nombre
void insertarEmpleadoOrdenado(Piso* piso, Empleado* empleadoInsertar) {
    Empleado* actual = piso->listaEmpleados; // Puntero al nodo actual de la lista
    Empleado* anterior = nullptr;            // Puntero al nodo anterior al actual

    // Recorrer la lista hasta encontrar la posición de inserción
    // La condición del bucle es verdadera mientras no se llegue al final de la lista (actual != nullptr)
    // y el nombre del empleado a insertar sea mayor que el nombre del empleado actual
    while (actual != nullptr && actual->nombre < empleadoInsertar->nombre) {
        anterior = actual;          // Actualizar el nodo anterior
        actual = actual->siguiente; // Avanzar al siguiente nodo
    }

    // Insertar el empleado en la posición correcta
    if (anterior == nullptr) {
        // Insertar al inicio de la lista del piso
        empleadoInsertar->siguiente = piso->listaEmpleados;
        piso->listaEmpleados = empleadoInsertar;
    }
    else {
        // Insertar después del nodo 'anterior'
        empleadoInsertar->siguiente = actual;
        anterior->siguiente = empleadoInsertar;
    }

    // Actualizar las ventas totales del piso
    piso->ventasTotalesPiso += empleadoInsertar->ventasTotales;
}

// Función para insertar una nueva venta para un empleado
void insertarVenta(Empleado* empleado, int cantidadVenta) {
    Venta* nuevaVenta = new Venta(cantidadVenta); // Crear una nueva venta

    // Insertar la venta al inicio de la lista de ventas del empleado
    nuevaVenta->siguiente = empleado->listaVentas; // El siguiente de la nueva venta será la venta actual (cabeza de la lista)
    empleado->listaVentas = nuevaVenta;            // La nueva venta se convierte en la cabeza de la lista

    // Actualizar las ventas totales del empleado
    empleado->ventasTotales += cantidadVenta;
}

// Función para insertar los datos iniciales de la estructura
void insertarDatosIniciales(Piso** inicio) {
    // Crear pisos (se usa doble puntero para modificar el inicio de la lista)
    *inicio = new Piso(1);
    (*inicio)->siguiente = new Piso(2);
    (*inicio)->siguiente->anterior = *inicio;
    (*inicio)->siguiente->siguiente = new Piso(3);
    (*inicio)->siguiente->siguiente->anterior = (*inicio)->siguiente;
    (*inicio)->siguiente->siguiente->siguiente = new Piso(4);
    (*inicio)->siguiente->siguiente->siguiente->anterior = (*inicio)->siguiente->siguiente;

    // Insertar empleados y ventas para el Piso 1
    Empleado* carlos = new Empleado("Carlos");
    insertarEmpleadoOrdenado(*inicio, carlos);
    insertarVenta(carlos, 350);
    insertarVenta(carlos, 200);
    insertarVenta(carlos, 100);
    insertarVenta(carlos, 50);

    Empleado* karla = new Empleado("Karla");
    insertarEmpleadoOrdenado(*inicio, karla);
    insertarVenta(karla, 800);
    insertarVenta(karla, 500);
    insertarVenta(karla, 300);

    // Insertar empleados y ventas para el Piso 2
    Empleado* mario = new Empleado("Mario");
    insertarEmpleadoOrdenado((*inicio)->siguiente, mario);
    insertarVenta(mario, 350);

    // Insertar empleados y ventas para el Piso 3
    Empleado* ana = new Empleado("Ana");
    insertarEmpleadoOrdenado((*inicio)->siguiente->siguiente, ana);
    insertarVenta(ana, 800);
    insertarVenta(ana, 300);

    Empleado* jose = new Empleado("Jose");
    insertarEmpleadoOrdenado((*inicio)->siguiente->siguiente, jose);
    insertarVenta(jose, 500);

    Empleado* sonia = new Empleado("Sonia");
    insertarEmpleadoOrdenado((*inicio)->siguiente->siguiente, sonia);

    // Insertar empleados y ventas para el Piso 4
    Empleado* pedro = new Empleado("Pedro");
    insertarEmpleadoOrdenado((*inicio)->siguiente->siguiente->siguiente, pedro);
    insertarVenta(pedro, 1600);
    insertarVenta(pedro, 1000);
    insertarVenta(pedro, 500);
    insertarVenta(pedro, 100);

    // Calcular las ventas totales de cada piso (esto podría hacerse durante la inserción de ventas para mayor eficiencia)
    Piso* pisoActual = *inicio;
    while (pisoActual != nullptr) {
        Empleado* empleadoActual = pisoActual->listaEmpleados;
        while (empleadoActual != nullptr) {
            pisoActual->ventasTotalesPiso += empleadoActual->ventasTotales;
            empleadoActual = empleadoActual->siguiente;
        }
        pisoActual = pisoActual->siguiente;
    }

}

// Función para mostrar los datos de la estructura
void mostrarDatos(Piso* inicio) {
    Piso* pisoActual = inicio; // Comenzar desde el primer piso
    while (pisoActual != nullptr) { // Iterar mientras haya pisos
        cout << "Piso " << pisoActual->numero << ": (Ventas totales: "
            << pisoActual->ventasTotalesPiso << ")" << endl;

        Empleado* empleadoActual = pisoActual->listaEmpleados; // Recorrer los empleados del piso
        while (empleadoActual != nullptr) {
            cout << "  - " << empleadoActual->nombre
                << " (Ventas: " << empleadoActual->ventasTotales << "): ";

            Venta* ventaActual = empleadoActual->listaVentas; // Recorrer las ventas del empleado
            while (ventaActual != nullptr) {
                cout << ventaActual->cantidad << " ";
                ventaActual = ventaActual->siguiente; // Avanzar a la siguiente venta
            }
            cout << endl;

            empleadoActual = empleadoActual->siguiente; // Avanzar al siguiente empleado
        }

        pisoActual = pisoActual->siguiente; // Avanzar al siguiente piso
    }
}

// Función para verificar si las sumatorias de ventas son correctas
bool verificarSumatorias(Piso* inicio) {
    bool correcto = true;
    Piso* pisoActual = inicio;

    while (pisoActual != nullptr) { // Recorrer cada piso
        int sumaEmpleados = 0;
        Empleado* empleadoActual = pisoActual->listaEmpleados;

        while (empleadoActual != nullptr) { // Recorrer cada empleado del piso
            sumaEmpleados += empleadoActual->ventasTotales;

            int sumaVentas = 0;
            Venta* ventaActual = empleadoActual->listaVentas;

            while (ventaActual != nullptr) { // Recorrer cada venta del empleado
                sumaVentas += ventaActual->cantidad;
                ventaActual = ventaActual->siguiente;
            }

            // Verificar si la suma de ventas del empleado coincide con su total
            if (sumaVentas != empleadoActual->ventasTotales) {
                correcto = false;
                cout << "Error: Sumatoria de ventas incorrecta para "
                    << empleadoActual->nombre << " en el piso "
                    << pisoActual->numero << endl;
            }

            empleadoActual = empleadoActual->siguiente;
        }

        // Verificar si la suma de ventas de los empleados coincide con el total del piso
        if (sumaEmpleados != pisoActual->ventasTotalesPiso) {
            correcto = false;
            cout << "Error: Sumatoria de empleados incorrecta en el piso "
                << pisoActual->numero << endl;
        }

        pisoActual = pisoActual->siguiente;
    }
    return correcto;
}

// Función para eliminar un empleado de un piso
void eliminarEmpleado(Piso* piso, Empleado* empleadoEliminar) {
    // Caso especial: el empleado a eliminar es el primero de la lista
    if (piso->listaEmpleados == empleadoEliminar) {
        piso->listaEmpleados = empleadoEliminar->siguiente;
    }
    else {
        Empleado* actual = piso->listaEmpleados;
        Empleado* anterior = nullptr;

        // Buscar el empleado a eliminar en la lista
        while (actual != nullptr && actual != empleadoEliminar) {
            anterior = actual;
            actual = actual->siguiente;
        }

        // Si se encuentra el empleado
        if (actual != nullptr) {
            // Conectar el nodo anterior al siguiente del nodo a eliminar
            anterior->siguiente = actual->siguiente;
        }
    }

    // Eliminar la lista de ventas del empleado (liberar memoria)
    Venta* ventaActual = empleadoEliminar->listaVentas;
    while (ventaActual != nullptr) {
        Venta* siguienteVenta = ventaActual->siguiente;
        delete ventaActual;
        ventaActual = siguienteVenta;
    }

    // Eliminar el empleado (liberar memoria)
    delete empleadoEliminar;
}

// Función para eliminar un piso de la estructura y mover sus empleados al piso anterior
void eliminarPiso(Piso** inicio, int numeroPiso) {
    Piso* pisoEliminar = *inicio;
    // Buscar el piso a eliminar
    while (pisoEliminar != nullptr && pisoEliminar->numero != numeroPiso) {
        pisoEliminar = pisoEliminar->siguiente;
    }

    // Si no se encuentra el piso, mostrar un error
    if (pisoEliminar == nullptr) {
        cout << "Error: No se encontro el piso " << numeroPiso << endl;
        return;
    }

    // Conectar el piso anterior y siguiente al piso a eliminar
    if (pisoEliminar->anterior != nullptr) {
        pisoEliminar->anterior->siguiente = pisoEliminar->siguiente;
    }
    else {
        // Si se elimina el primer piso, actualizar el inicio de la lista
        *inicio = pisoEliminar->siguiente;
    }
    if (pisoEliminar->siguiente != nullptr) {
        pisoEliminar->siguiente->anterior = pisoEliminar->anterior;
    }

    // Mover empleados al piso anterior
    Empleado* empleado = pisoEliminar->listaEmpleados;
    while (empleado != nullptr) {
        Empleado* siguienteEmpleado = empleado->siguiente;

        // Insertar el empleado en el piso anterior, manteniendo el orden alfabético
        if (pisoEliminar->anterior != nullptr) {
            insertarEmpleadoOrdenado(pisoEliminar->anterior, empleado);
        }
        else {
            // Si no hay piso anterior, liberar la memoria del empleado 
            delete empleado;
        }

        empleado = siguienteEmpleado;
    }

    // Eliminar el piso (la memoria de los empleados ya se liberó o se movieron)
    delete pisoEliminar;
}

// Función para insertar un nuevo piso en la estructura, manteniendo el orden ascendente por número de piso
void insertarPisoOrdenado(Piso** inicio, Piso* nuevoPiso) {
    // Si la lista está vacía o el nuevo piso debe ir al principio
    if (*inicio == nullptr || (*inicio)->numero > nuevoPiso->numero) {
        nuevoPiso->siguiente = *inicio; // El siguiente del nuevo piso es el actual inicio
        if (*inicio != nullptr) {
            (*inicio)->anterior = nuevoPiso; // Si hay un inicio, su anterior ahora es el nuevo piso
        }
        *inicio = nuevoPiso; // El nuevo piso se convierte en el inicio
        return;
    }

    Piso* actual = *inicio;
    // Buscar la posición donde insertar el nuevo piso
    while (actual->siguiente != nullptr && actual->siguiente->numero < nuevoPiso->numero) {
        actual = actual->siguiente;
    }

    // Insertar el nuevo piso después del nodo 'actual'
    nuevoPiso->siguiente = actual->siguiente;
    if (actual->siguiente != nullptr) {
        actual->siguiente->anterior = nuevoPiso;
    }
    actual->siguiente = nuevoPiso;
    nuevoPiso->anterior = actual;
}

int main() {
    Piso* inicio = nullptr; // Puntero al primer piso, inicialmente nulo
    insertarDatosIniciales(&inicio); // Insertar datos de ejemplo

    int opcion;
    do {
        // Mostrar el menú principal
        cout << "\n--- Menu ---" << endl;
        cout << "1. Mostrar datos" << endl;
        cout << "2. Verificar sumatorias" << endl;
        cout << "3. Eliminar piso" << endl;
        cout << "4. Ingresar datos" << endl;
        cout << "0. Salir" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1: // Mostrar datos de la estructura
            mostrarDatos(inicio);
            break;
        case 2: // Verificar sumatorias de ventas
            if (verificarSumatorias(inicio)) {
                cout << "Las sumatorias son correctas." << endl;
            }
            break;
        case 3: { // Eliminar un piso
            int pisoAEliminar;
            cout << "Ingrese el numero de piso a eliminar: ";
            cin >> pisoAEliminar;
            eliminarPiso(&inicio, pisoAEliminar);
            break;
        }
        case 4: { // Submenú para ingresar datos
            cout << "\n--- Ingresar Datos ---" << endl;
            cout << "1. Ingresar Piso" << endl;
            cout << "2. Ingresar Empleado" << endl;
            cout << "3. Ingresar Venta" << endl;
            cout << "4. Volver al menu principal" << endl;
            cout << "Seleccione una opcion: ";

            int opcionIngreso;
            cin >> opcionIngreso;

            switch (opcionIngreso) {
            case 1: { // Ingresar Piso
                int numPiso;
                cout << "Ingrese el numero del nuevo piso: ";
                cin >> numPiso;

                // Verificar si el piso ya existe
                Piso* pisoExistente = inicio;
                while (pisoExistente != nullptr) {
                    if (pisoExistente->numero == numPiso) {
                        cout << "Error: El piso " << numPiso << " ya existe." << endl;
                        break; // Salir del bucle si el piso ya existe
                    }
                    pisoExistente = pisoExistente->siguiente;
                }

                // Si el piso no existe, crearlo e insertarlo en la lista
                if (pisoExistente == nullptr) {
                    Piso* nuevoPiso = new Piso(numPiso);
                    insertarPisoOrdenado(&inicio, nuevoPiso);
                    cout << "Piso " << numPiso << " ingresado correctamente." << endl;
                }
                break;
            }
            case 2: { // Ingresar Empleado
                int numPiso;
                string nombreEmpleado;
                cout << "Ingrese el numero de piso: ";
                cin >> numPiso;
                cout << "Ingrese el nombre del empleado: ";
                cin.ignore(); // Limpiar el buffer
                getline(cin, nombreEmpleado);

                // Buscar el piso donde se insertará el empleado
                Piso* piso = inicio;
                while (piso != nullptr && piso->numero != numPiso) {
                    piso = piso->siguiente;
                }

                // Si se encuentra el piso, crear el empleado e insertarlo
                if (piso != nullptr) {
                    Empleado* nuevoEmpleado = new Empleado(nombreEmpleado);
                    insertarEmpleadoOrdenado(piso, nuevoEmpleado);
                    cout << "Empleado " << nombreEmpleado << " ingresado en el piso "
                        << numPiso << "." << endl;
                }
                else {
                    cout << "Error: El piso " << numPiso << " no existe." << endl;
                }
                break;
            }
            case 3: { // Ingresar Venta
                int numPiso, cantidadVenta;
                string nombreEmpleado;
                cout << "Ingrese el numero de piso: ";
                cin >> numPiso;
                cout << "Ingrese el nombre del empleado: ";
                cin.ignore();
                getline(cin, nombreEmpleado);
                cout << "Ingrese la cantidad de la venta: ";
                cin >> cantidadVenta;

                // Buscar el piso y el empleado al que se le agregará la venta
                Piso* piso = inicio;
                while (piso != nullptr && piso->numero != numPiso) {
                    piso = piso->siguiente;
                }

                // Si se encuentra el piso, buscar el empleado
                if (piso != nullptr) {
                    Empleado* empleado = piso->listaEmpleados;
                    while (empleado != nullptr && empleado->nombre != nombreEmpleado) {
                        empleado = empleado->siguiente;
                    }

                    // Si se encuentra el empleado, agregar la venta
                    if (empleado != nullptr) {
                        insertarVenta(empleado, cantidadVenta);
                        piso->ventasTotalesPiso += cantidadVenta;
                        cout << "Venta de " << cantidadVenta << " agregada a "
                            << nombreEmpleado << " en el piso " << numPiso << "." << endl;
                    }
                    else {
                        cout << "Error: Empleado " << nombreEmpleado << " no encontrado en el piso "
                            << numPiso << "." << endl;
                    }
                }
                else {
                    cout << "Error: El piso " << numPiso << " no existe." << endl;
                }
                break;
            }
            case 4: // Volver al menu principal
                break;
            default: // Opción no válida en el submenú
                cout << "Opcion no valida." << endl;
                break;
            }
            break;
        } // Fin del case 4 (Ingresar datos)
        case 0: // Salir del programa
            cout << "Saliendo del programa." << endl;
            break;
        default: // Opción no válida en el menú principal
            cout << "Opcion no valida." << endl;
            break;
        }
    } while (opcion != 0);

    // Liberar memoria al finalizar programa (Es una buena practica)
    Piso* pisoActual = inicio;
    while (pisoActual != nullptr){
        Empleado* empleadoActual = pisoActual->listaEmpleados;
        while (empleadoActual != nullptr){
            Venta* ventaActual = empleadoActual->listaVentas;
            while (ventaActual != nullptr){
                Venta* siguienteVenta = ventaActual->siguiente;
                delete ventaActual; // Liberar la memoria de cada venta
                ventaActual = siguienteVenta;
            }

            Empleado* siguienteEmpleado = empleadoActual->siguiente;
            delete empleadoActual; // Liberar la memoria de cada empleado
            empleadoActual = siguienteEmpleado;

        }

        Piso* siguientePiso = pisoActual->siguiente;
        delete pisoActual; // Liberar la memoria de cada piso
        pisoActual = siguientePiso;

    }


    return 0;
}