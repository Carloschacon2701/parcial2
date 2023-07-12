#include <iostream>

using namespace std;

struct Nodo
{
    int codigo;
    Nodo *siguiente;
};

struct Cola
{
    Nodo *frente;
    Nodo *final;
};

struct Pila
{
    Nodo *cima;
};

Cola crearCola()
{
    Cola cola;
    cola.frente = nullptr;
    cola.final = nullptr;
    return cola;
}

void encolar(Cola &cola, int codigo)
{
    Nodo *nuevoNodo = new Nodo;
    nuevoNodo->codigo = codigo;
    nuevoNodo->siguiente = nullptr;

    if (cola.final == nullptr)
    {
        cola.frente = nuevoNodo;
        cola.final = nuevoNodo;
    }
    else
    {
        cola.final->siguiente = nuevoNodo;
        cola.final = nuevoNodo;
    }
}

void desencolar(Cola &cola)
{
    if (cola.frente != nullptr)
    {
        Nodo *nodoEliminar = cola.frente;
        cola.frente = cola.frente->siguiente;

        if (cola.frente == nullptr)
        {
            cola.final = nullptr;
        }

        delete nodoEliminar;
    }
}

bool estaVacia(const Cola &cola)
{
    return cola.frente == nullptr;
}

void mostrarCola(const Cola &cola)
{
    Nodo *nodoActual = cola.frente;
    while (nodoActual != nullptr)
    {
        cout << nodoActual->codigo << " ";
        nodoActual = nodoActual->siguiente;
    }
    cout << endl;
}

Pila crearPila()
{
    Pila pila;
    pila.cima = nullptr;
    return pila;
}

void apilar(Pila &pila, int codigo)
{
    Nodo *nuevoNodo = new Nodo;
    nuevoNodo->codigo = codigo;
    nuevoNodo->siguiente = pila.cima;
    pila.cima = nuevoNodo;
}

void desapilar(Pila &pila)
{
    if (pila.cima != nullptr)
    {
        Nodo *nodoEliminar = pila.cima;
        pila.cima = pila.cima->siguiente;
        delete nodoEliminar;
    }
}

bool estaVacia(const Pila &pila)
{
    return pila.cima == nullptr;
}

void mostrarPila(const Pila &pila)
{
    Nodo *nodoActual = pila.cima;
    while (nodoActual != nullptr)
    {
        cout << nodoActual->codigo << " ";
        nodoActual = nodoActual->siguiente;
    }
    cout << endl;
}

int invertirCedula(int cedula)
{
    int remainder, reversed_number = 0;

    while (cedula != 0)
    {
        remainder = cedula % 10;
        reversed_number = reversed_number * 10 + remainder;
        cedula /= 10;
    }

    return reversed_number;
};

int generarCodigo(int cedula, Cola &cola, Pila &pila)
{
    int codigo = cedula % 1000;
    Nodo *nodoActual = cola.frente;

    while (nodoActual != nullptr)
    {
        if (nodoActual->codigo == codigo)
        {

            int penultimosTres = codigo % 1000000; // Obtiene los tres penúltimos dígitos
            int antePenultimos = codigo % 1000000000;

            if (penultimosTres != codigo)
            {
                codigo = penultimosTres;
            }
            else if (antePenultimos != codigo)
            {
                codigo = antePenultimos;
            }
            else
            {
                codigo = invertirCedula(cedula);

                int ultimosTres = codigo % 1000;
                int penUltimos = (codigo % 1000000) / 1000; // Obtiene los tres penúltimos dígitos
                int antePenultimos = (codigo % 1000000000) / 1000000;

                if (ultimosTres != codigo)
                {
                    codigo = ultimosTres;
                }
                else if (penUltimos != codigo)
                {
                    codigo = penUltimos;
                }
                else if (antePenultimos != codigo)
                {
                    codigo = antePenultimos;
                }
            }

            nodoActual = cola.frente;
        }
        else
        {
            nodoActual = nodoActual->siguiente;
        }
    }

    return codigo;
}

int main()
{
    Cola cola = crearCola();
    Pila pila = crearPila();
    char opcion;
    int cedula;

    do
    {
        cout << "Seleccione una opcion:\n";
        cout << "A: Ingresar cédula, generar código y agregar a la cola.\n";
        cout << "1: Llamar al siguiente de la cola en taquilla 1.\n";
        cout << "2: Llamar al siguiente de la cola en taquilla 2.\n";
        cout << "3: Llamar al siguiente de la cola en taquilla 3.\n";
        cout << "F: Finalizar la ejecucion del programa.\n";
        cin >> opcion;

        switch (opcion)
        {
        case 'A':
        case 'a':
        {
            cout << "Ingrese la cedula del cliente: ";
            cin >> cedula;

            int codigo = generarCodigo(cedula, cola, pila);
            encolar(cola, codigo);

            cout << "Codigo generado: " << codigo << endl;
        }
        break;

        case '1':
        {
            if (!estaVacia(cola))
            {
                cout << "Atendiendo al cliente con codigo: " << cola.frente->codigo << " en taquilla 1." << endl;
                desencolar(cola);
            }
            else
            {
                cout << "No hay clientes en espera en taquilla 1." << endl;
            }
        }
        break;

        case '2':
        {
            if (!estaVacia(cola))
            {
                cout << "Atendiendo al cliente con codigo: " << cola.frente->codigo << " en taquilla 2." << endl;
                desencolar(cola);
            }
            else
            {
                cout << "No hay clientes en espera en taquilla 2." << endl;
            }
        }
        break;

        case '3':
        {
            if (!estaVacia(cola))
            {
                cout << "Atendiendo al cliente con codigo: " << cola.frente->codigo << " en taquilla 3." << endl;
                desencolar(cola);
            }
            else
            {
                cout << "No hay clientes en espera en taquilla 3." << endl;
            }
        }
        break;

        case 'F':
        case 'f':
        {
            cout << "Finalizando el programa." << endl;
        }
        break;

        default:
        {
            cout << "Opcion invalida. Intente nuevamente." << endl;
        }
        }

        cout << "Cola de numeros actualizada: ";
        mostrarCola(cola);

    } while (opcion != 'F' && opcion != 'f');

    return 0;
}
