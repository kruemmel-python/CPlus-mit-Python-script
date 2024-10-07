

# Installation von Python3 und Boost.Python in Visual Studio

## 1. Vorbereitungen

Stelle sicher, dass du **vcpkg** installiert hast, um die notwendigen Bibliotheken für Python und Boost.Python zu installieren.

## 2. Python3 und Boost.Python installieren

```bash
C:\vcpkg> vcpkg install python3:x64-windows
C:\vcpkg> vcpkg install boost-python:x64-windows
```

Mit diesen Befehlen werden Python3 und Boost.Python für die x64-Windows-Plattform installiert.

## 3. Visual Studio Projekt erstellen

1. Öffne Visual Studio und lege ein neues Projekt an:
    - Wähle **C++** als Sprache.
    - Lege ein **leeres Projekt** an.
    - Gib dem Projekt einen geeigneten Namen.

2. Erstelle eine neue Datei `main.cpp` im Projektverzeichnis.

3. Kopiere den folgenden Beispielcode in die `main.cpp`:

```cpp
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
```

## 4. Projekteigenschaften in Visual Studio konfigurieren

1. Gehe zu **Konfigurationseigenschaften** → **Debuggen** und setze unter **Umgebung** die folgenden Variablen:

    ```bash
    PYTHONHOME=C:\vcpkg\installed\x64-windows\tools\python3;
    PYTHONPATH=C:\vcpkg\installed\x64-windows\tools\python3\Lib;C:\vcpkg\installed\x64-windows\tools\python3\DLLs;
    PATH=%PATH%;C:\vcpkg\installed\x64-windows\tools\python3
    ```

2. Gehe zu **Konfigurationseigenschaften** → **C/C++** → **Allgemein** und setze unter **Zusätzliche Includeverzeichnisse**:

    ```bash
    C:\vcpkg\installed\x64-windows\include\python3.11;
    C:\vcpkg\installed\x64-windows\tools\python3
    ```

3. Gehe zu **Konfigurationseigenschaften** → **Linker** → **Allgemein** und setze unter **Zusätzliche Bibliotheksverzeichnisse**:

    ```bash
    C:\vcpkg\installed\x64-windows\libs;
    C:\vcpkg\installed\x64-windows\tools\python3
    ```

## 5. Projekteinstellungen auf Release konfigurieren

Stelle sicher, dass dein Projekt auf die **Release-Konfiguration** eingestellt ist und die Plattform auf **x64**.

## 6. Projekt ausführen

Nachdem du die oben genannten Schritte ausgeführt hast, drücke **Strg + F5**, um das Projekt zu kompilieren und auszuführen.

Die Ausgabe sollte Folgendes anzeigen:

```bash
Das Ergebnis aus C++ ist: 50
Nach Weiterverarbeitung in Python: 150
```

## Hinweis

Falls Fehler auftreten, stelle sicher, dass alle Pfade korrekt gesetzt sind und dass **Python3** und **Boost.Python** korrekt über **vcpkg** installiert wurden.


