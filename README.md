# CPP Containerklassen

Entstanden im Modul "Effizeinte Software Entwicklen mit C++".
Viele Codeteile wurden durch meinen Dozenten Dr. Schirmacher bereitgestellt. -> Hartmut.Schirmacher@bht-berlin.de

# Generisch

Dieses Repository enthält drei C++-Projekte zur Implementierung und
Testung von Vektor-Klassen (`Vec3f` und `Vec<T,N>`), die im Rahmen
von Übungen zu Templates, Operatorenüberladung und STL-Nutzung erstellt wurden.

Die Projekte basieren auf **C++20** und **CMake**.


---

## A11 – Vec3f (3D-Vektor)

### Beschreibung
- Implementierung eines einfachen 3D-Vektors mit `float`-Werten.
- Operatoren: `[]`, `==`, `!=`, `+=`, `+`, unary `-`.
- Skalarprodukt (`dot`) und const-Korrektheit.
- Fokus auf **Testing & Assertions**.

### Features
- Speicheroptimiert (3 `float`s)
- Lesen/Schreiben über `operator[]`
- Vergleichsoperatoren
- Addition und Negation
- Skalarprodukt
- Vollständig getestete Funktionen (`test_Vec3f`)

---

## A12 – Vec<T,N> (Template-Vektor)

### Beschreibung
- Allgemeiner Vektor mit beliebigem **Typ T** und **Größe N**.
- Unterstützt arithmetische Typen (`int`, `float`, `double`, `long`).
- Operatoren: `[]`, `==`, `!=`, `+=`, `+`, unary `-`.
- Skalarprodukt (`dot`) und const-Korrektheit.

### Features
- Compile-Time Typ-Check (arithmetic types)
- Feste Größe N über Template
- Konstruktor mit variadischen Argumenten
- Vollständig getestete Funktionen (`test_vec<T,N>`)

---

## A13 – STL & Vektoroperationen

### Beschreibung
- Verwendung von `Vec<float,3>` (alias `vec3f`) in **STL-Containern**.
- Demonstration von:
  - `std::vector<vec3f>`
  - `std::transform` für Vektor-Addition
  - `std::sort` und `std::stable_partition`
  - Median-Berechnung
  - Kopieren & Löschen von Elementen
- Berechnung der **Vektorlänge** und Ausgabe

### Features
- Integration mit Standardbibliothek (STL)
- Operationen auf mehreren Vektoren
- Sortierung, Partitionierung, Filtern
- Medianberechnung

---

## Technologie & Tools

- C++20
- CMake 3.20+
- Standardbibliothek (STL)
- Assertions für Unit-Tests

---

## Build & Run

### Voraussetzungen
- C++20 kompatibler Compiler (g++, clang++, MSVC)
- CMake 3.20 oder neuer

### Beispiel für Build & Run

```bash
# Projekt A11
cd A11
mkdir build && cd build
cmake ..
cmake --build .
./main    # oder main.exe auf Windows

# Projekt A12
cd ../../A12
mkdir build && cd build
cmake ..
cmake --build .
./main

# Projekt A13
cd ../../A13
mkdir build && cd build
cmake ..
cmake --build .
./main
```

#Dynamisch

Dieses Repository enthält C++-Übungsprojekte zur Implementierung eines **dynamischen Vektor-Containers** 
(`my::vector`) inklusive **Speicherverwaltung, Rule of 5** und **Payload-Testobjekten**.  
Die Projekte stammen aus dem Wintersemester 2022 (WS22) und dienen zur Vertiefung von Templates, 
Operatorenüberladung und Speicherhandling in C++.


### Aufgabe 2.1 – my::vector (einfach)

- Dynamischer Vektor für beliebige Typen (`template <typename ValueT>`)
- Speicher wird bei jedem `push_back` vergrößert
- Operatoren:
  - `operator[]` (Lese-/Schreibzugriff)
  - `at()` (mit Out-of-Range Exception)
- Methoden:
  - `size()`, `empty()`, `push_back()`, `pop_back()`, `clear()`
- **Payload**-Tests:
  - Überprüft Konstruktion, Zerstörung, Copy- und Move-Zählung
- Kein Copy-Konstruktor/Assignment (gelöscht)

---

### Aufgabe 2.2 – my::vector (erweitert)

- Dynamischer Vektor mit **Capacity** und effizienter Speicherverwaltung
- Methoden:
  - `reserve(n)` – Speicher reservieren ohne Elemente zu erzeugen
  - `shrink_to_fit()` – Speicher passend zur Größe reduzieren
  - `push_back()` – nutzt **Placement new**
  - `pop_back()` – ruft Destruktor, Speicher bleibt erhalten
- **Rule of 5**:
  - Copy-Konstruktor → Deep Copy
  - Move-Konstruktor → Pointer-Tausch
  - Copy/Move Assignment via Swap
- Tests überprüfen:
  - Copy vs Move
  - Capacity-Wachstum
  - `shrink_to_fit` & `reserve`
  - pop_back und Destruktoraufrufe
- Vollständig getestetes Verhalten mit `Payload`-Zählungen:
  - `count()`, `copy_count()`, `move_count()`

---

## Technologie & Tools

- C++20
- CMake 3.20+
- Standardbibliothek (STL nur für Test & Output)
- Assertions für Unit-Tests
- Linux / Windows / macOS kompatibel

---

## Build & Run

### Voraussetzungen

- C++20-kompatibler Compiler (g++, clang++, MSVC)
- CMake 3.20 oder neuer

### Kompilieren und Ausführen

```bash
# Projektverzeichnis betreten
cd CPP_A2X

# Build-Ordner erstellen
mkdir build && cd build

# CMake konfigurieren
cmake ..

# Build starten
cmake --build .
