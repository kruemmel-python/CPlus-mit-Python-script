#include <Python.h>
#include <boost/python.hpp>
#include <iostream>

using namespace boost::python;

// Funktion in C++ zur Durchführung einer Berechnung
int berechnung(int a, int b) {
    return a * b;  // Einfache Multiplikation in C++
}

int main() {
    // Python-Interpreter initialisieren
    Py_Initialize();  // Standard-Initialisierung ohne PyConfig

    try {
        // Berechnung in C++ durchführen
        int ergebnis = berechnung(5, 10);  // Beispielwerte

        // Python-Skript laden und Ergebnis übergeben
        object main_module = import("__main__");
        object main_namespace = main_module.attr("__dict__");

        // Erstelle eine Python-Variable mit dem berechneten Ergebnis aus C++
        main_namespace["ergebnis"] = ergebnis;

        // Führe Python-Code aus, der das Ergebnis weiterverarbeitet
        exec(R"(
def weiterverarbeiten(zahl):
    print(f'Das Ergebnis aus C++ ist: {zahl}')
    # Beispiel für weitere Python-Berechnungen
    verarbeiteter_wert = zahl + 100
    print(f'Nach Weiterverarbeitung in Python: {verarbeiteter_wert}')
weiterverarbeiten(ergebnis)
        )", main_namespace);

    }
    catch (error_already_set) {
        PyErr_Print();
    }

    // Python-Interpreter beenden
    Py_Finalize();

    return 0;
}
