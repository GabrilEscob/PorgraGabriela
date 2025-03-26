#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>   // Para manejo de archivos
#include <iomanip>   // Para formateo de salida

using namespace std;

// Función para mostrar y guardar resultados
void mostrarYGuardarResultados(const vector<vector<int>>& votos, const vector<string>& candidatos) {
    int numCandidatos = candidatos.size();
    int numRondas = votos[0].size();
    vector<int> totalVotos(numCandidatos, 0);

    // Abrir archivo para guardar resultados
    ofstream archivo("resultados_votacion.txt");
    if (!archivo) {
        cerr << "Error al abrir el archivo para guardar resultados.\n";
        return;
    }

    cout << "\nResultados de la votación:\n";
    cout << "---------------------------------------------------\n";
    cout << "Candidato\tR1\tR2\tR3\tR4\tR5\tTotal\n";
    cout << "---------------------------------------------------\n";
    archivo << "Resultados de la votación:\n";
    archivo << "---------------------------------------------------\n";
    archivo << "Candidato\tR1\tR2\tR3\tR4\tR5\tTotal\n";
    archivo << "---------------------------------------------------\n";

    for (int i = 0; i < numCandidatos; i++) {
        cout << left << setw(10) << candidatos[i] << "\t";
        archivo << left << setw(10) << candidatos[i] << "\t";
        for (int j = 0; j < numRondas; j++) {
            cout << votos[i][j] << "\t";
            archivo << votos[i][j] << "\t";
            totalVotos[i] += votos[i][j];
        }
        cout << totalVotos[i] << endl;
        archivo << totalVotos[i] << endl;
    }

    // Determinar ganador y perdedor
    int maxVotos = totalVotos[0], minVotos = totalVotos[0];
    string ganador = candidatos[0], perdedor = candidatos[0];

    for (int i = 1; i < numCandidatos; i++) {
        if (totalVotos[i] > maxVotos) {
            maxVotos = totalVotos[i];
            ganador = candidatos[i];
        }
        if (totalVotos[i] < minVotos) {
            minVotos = totalVotos[i];
            perdedor = candidatos[i];
        }
    }

    cout << "\nEl candidato ganador es: " << ganador << " con " << maxVotos << " votos.\n";
    cout << "El candidato con menos votos es: " << perdedor << " con " << minVotos << " votos.\n";

    archivo << "\nEl candidato ganador es: " << ganador << " con " << maxVotos << " votos.\n";
    archivo << "El candidato con menos votos es: " << perdedor << " con " << minVotos << " votos.\n";

    archivo.close();
    cout << "\nResultados guardados en 'resultados_votacion.txt'\n";
}

// Función para validar la entrada de números enteros
int obtenerEntero(string mensaje) {
    int valor;
    while (true) {
        cout << mensaje;
        cin >> valor;
        if (cin.fail() || valor <= 0) {
            cin.clear(); // Limpiar error
            cin.ignore(1000, '\n'); // Descartar entrada inválida
            cout << "Entrada inválida. Intente de nuevo.\n";
        } else {
            return valor;
        }
    }
}

int main() {
    srand(time(0));
    int numCandidatos = obtenerEntero("Ingrese el número de candidatos: ");

    vector<string> candidatos(numCandidatos);
    for (int i = 0; i < numCandidatos; i++) {
        cout << "Nombre del candidato " << i + 1 << ": ";
        cin >> candidatos[i];
    }

    const int numVotantes = 50;
    const int numRondas = 5;
    vector<vector<int>> votos(numCandidatos, vector<int>(numRondas));

    // Generar votos aleatorios
    for (int i = 0; i < numCandidatos; i++) {
        for (int j = 0; j < numRondas; j++) {
            votos[i][j] = rand() % (numVotantes + 1);
        }
    }

    mostrarYGuardarResultados(votos, candidatos);

    char repetir;
    cout << "\n¿Desea realizar otra votación? (s/n): ";
    cin >> repetir;

    if (repetir == 's' || repetir == 'S') {
        main(); // Reiniciar la votación
    }

    return 0;
}
