/*

INTEGRANTES GRUPO 11:

Carbajal Reyes, Alan Alberto
Gonzales Guzmán, Brayham Carlos
Espinoza Ramirez Carlos
Laveriano Porroa, Melani Yulli
Huere Sánchez, Miguel Ángel

*/

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <thread>
#include <chrono>
#include <unistd.h>
#include <random>
#include <atomic>
#include <mutex>
#include <shared_mutex>
#include <sstream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

std::atomic<bool> finJuego(false);
std::atomic<bool> finEnemigos(false);
std::mutex mtx;
std::recursive_mutex vidasMutex;
std::shared_timed_mutex SMutex;
std::condition_variable cv; 
int puntaje = 0;
int number_ofLives = 1;
auto start = std::chrono::high_resolution_clock::now();

/*

/* declaración de la función de ayuda merge */





void merge(std::vector<double>& array, unsigned int izquierda, unsigned int medio, unsigned int derecha);

void merge_sort_secuencial(std::vector<double>& array, unsigned int izquierda, unsigned int derecha) {
    if (izquierda < derecha) {
        unsigned int medio = (izquierda + derecha) / 2;
        merge_sort_secuencial(array, izquierda, medio);
        merge_sort_secuencial(array, medio + 1, derecha);
        merge(array, izquierda, medio, derecha);
    }
}

void merge_sort_paralelo(std::vector<double>& array, unsigned int izquierda, unsigned int derecha, unsigned int profundidad = 0) {
    if (profundidad >= 5) {
        merge_sort_secuencial(array, izquierda, derecha);
    } else {
        unsigned int medio = (izquierda + derecha) / 2;
        std::thread hilo_izquierdo = std::thread(merge_sort_paralelo, std::ref(array), izquierda, medio, profundidad + 1);
        merge_sort_paralelo(array, medio + 1, derecha, profundidad + 1);
        hilo_izquierdo.join();
        merge(array, izquierda, medio, derecha);
    }
}

void merge(std::vector<double>& array, unsigned int izquierda, unsigned int medio, unsigned int derecha) {
    unsigned int num_izquierda = medio - izquierda + 1;
    unsigned int num_derecha = derecha - medio;

    std::vector<double> subarray_izquierdo(num_izquierda);
    std::vector<double> subarray_derecho(num_derecha);

    std::copy(array.begin() + izquierda, array.begin() + medio + 1, subarray_izquierdo.begin());
    std::copy(array.begin() + medio + 1, array.begin() + derecha + 1, subarray_derecho.begin());

    unsigned int indice_izquierdo = 0;
    unsigned int indice_derecho = 0;
    unsigned int indice_insertar = izquierda;

    while (indice_izquierdo < num_izquierda || indice_derecho < num_derecha) {
        if (indice_izquierdo < num_izquierda && indice_derecho < num_derecha) {
            if (subarray_izquierdo[indice_izquierdo] <= subarray_derecho[indice_derecho]) {
                array[indice_insertar] = subarray_izquierdo[indice_izquierdo];
                indice_izquierdo++;
            } else {
                array[indice_insertar] = subarray_derecho[indice_derecho];
                indice_derecho++;
            }
        } else if (indice_izquierdo < num_izquierda) {
            array[indice_insertar] = subarray_izquierdo[indice_izquierdo];
            indice_izquierdo++;
        } else if (indice_derecho < num_derecha) {
            array[indice_insertar] = subarray_derecho[indice_derecho];
            indice_derecho++;
        }
        indice_insertar++;
    }
}





float PuntajeFinal(int puntaje,int  vidas, double tiempo ){
	
	float puntajeFinal=puntaje+vidas*(5000000/tiempo);
	
	return puntajeFinal;
	
}
/*
//Funciones Divide y Venceras
void merge(std::vector<double>& arr, int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;
    
    // Crear subarrays temporales
    std::vector<double> L(n1), R(n2);
    // Copiar datos a los subarrays temporales L[] y R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[middle + 1 + j];
    // Fusionar los subarrays temporales en arr[left..right]
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    // Copiar los elementos restantes de L[], si los hay
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    // Copiar los elementos restantes de R[], si los hay
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Función para realizar la ordenación de merge sort en un rango específico
void mergeSort(std::vector<double>& arr, int left, int right) {
    if (left < right) {
        // Calcular el punto medio
        int middle = left + (right - left) / 2;

       //Si el subvector tiene un tamaño menor que la mitad del tamaño original del vector
       // Entonces se limita el uso de hilos para evitar una sobrecarga
        if (right - left < 5000) {
            mergeSort(arr, left, middle);
            mergeSort(arr, middle + 1, right);
        } else {
            // Crear hilos para ordenar las dos mitades
            std::thread t1(mergeSort, std::ref(arr), left, middle);
            std::thread t2(mergeSort, std::ref(arr), middle + 1, right);

            // Esperar a que los hilos terminen
            t1.join();
            t2.join();
        }

        // Fusionar las dos mitades ordenadas
        merge(arr, left, middle, right);
    }
}



*/

// Función para guardar un vector en un archivo de texto
void saveArrayToFile(const std::vector<double>& arr, const std::string& filename) {
    std::ofstream outputFile(filename);
    if (outputFile.is_open()) {
        for (double num : arr) {
            outputFile << num << "\n"; // Se utiliza "\n" para separar por saltos de línea
        }
        outputFile.close();
        std::cout << "  Puntaje registrado en " << filename << std::endl;
    } else {
        std::cerr << "Error: No se pudo abrir el archivo " << filename << std::endl;
    }
}

// Función para leer números desde un archivo de texto y almacenarlos en un vector
std::vector<double> readNumbersFromFile(const std::string& filename) {
    std::vector<double> numbers;
    std::ifstream inputFile(filename);
    if (inputFile.is_open()) {
        std::string line;
        while (std::getline(inputFile, line)) {
            std::istringstream iss(line);
            double num;
            while (iss >> num) {
                numbers.push_back(num);
            }
        }
        inputFile.close();
    } else {
        std::cerr << "Error: No se pudo abrir el archivo " << filename << std::endl;
    }
    return numbers;
}




int findRanking(const std::vector<double>& arr, double num) {
    // Realizar una búsqueda binaria para encontrar el ranking del número
    int low = 0;
    int high = arr.size() - 1;
    int ranking = -1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == num) {
            ranking = mid + 1; // El ranking se cuenta desde 1
            break;
        } else if (arr[mid] < num) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return ranking;
}


//------------------------------------------------------------------------------------------------------------------------------------------

void DibujarPuntaje() {	
	if(mtx.try_lock()){
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),{2,1});
	    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // Blanco	    
	    cout << "Puntaje: " << puntaje;	    
		mtx.unlock();
		}		
}

void DibujarVidas(){
	if(mtx.try_lock()){
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),{15,1});
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // Blanco	    
		cout << "Vidas: " << number_ofLives+1;
		mtx.unlock();
	}
}
	
void ActualizarPuntaje() {
    std::unique_lock<std::shared_timed_mutex> lock(SMutex); // Bloquea el mutex exclusivo
    puntaje++;
 
}

void verPuntaje(){
	//son 265 puntos
	std::shared_lock<std::shared_timed_mutex> lock(SMutex);
	if(puntaje == 265){
		finJuego = true;
		Beep(600,300);

	}
}

int MAPA[20][40]{	
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
	{1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1},
	{1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1},
	{1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1},
	{1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1},
	{1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1},
	{1,1,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,1,1},
	{1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1},
	{1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1},
	{1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1},
	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
	{1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1},
	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},	
};

int PUNTOS[20][40]{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},

	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
	{1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1},
	{1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1},
	{1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1},
	{1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1},
	{1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1},
	{1,1,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,1,1},
	{1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1},
	{1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1},
	{1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1},
	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
	{1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1},
	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};

void DibujarMapa() {   
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 40; j++) {
            COORD coord;
            coord.X = j;
            coord.Y = i;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
            if (MAPA[i][j] == 0){
			 	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);  // Negro
			 	
        	}
            else if (MAPA[i][j] == 1){
			 	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);  // Azul
            	
        	}
        	cout << (char)219;
        }
    }	
}  

void DibujarPuntos(){
	for (int i = 0; i < 20; i++) {
	    for (int j = 0; j < 40; j++) {
	        COORD coord;
	        coord.X = j;
	        coord.Y = i;
	        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	        if (PUNTOS[i][j] == 0){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);  // Negro
				cout << (char)250;
	        }
	    }
   	}
}

struct Jugador {
	
	COORD coord;
	COORD cordenada_anterior;
    int x = 19;
    int y = 14;
    char c = 219;  
	int dir = 1;
	bool flag = true;
	
	void ActualizarPuntos(){
		if(PUNTOS[y][x]==0){
			PUNTOS[y][x] = 1;
			
			ActualizarPuntaje();
			
			mtx.lock();
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {2,1});
	    	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // Blanco	    
	    	cout << "Puntaje: " << puntaje;
	    	mtx.unlock();
	    	
		}
	}
	
	void actualizarVida(){
		number_ofLives = number_ofLives - 1;
	}
	
	void ActualizarCordenada(){
		COORD coord;
		x = 19;
    	y = 14;
    	coord.X = x;
    	coord.Y = y;
    	dir = 1;
    	bool flag = true;
	}
	
	void MovimientoAutomatico(){
		
		cordenada_anterior.X = x;
		cordenada_anterior.Y = y;
		
		if(dir == 1 && MAPA[y][x+1] == 0){
			x++;	
			flag = true;	
		}else if(dir == 3 && MAPA[y][x-1] == 0){
			x--;
			flag = true;
		}else if(dir == 2 && MAPA[y+1][x] == 0){
			y++;
			flag = true;
		}else if(dir == 4 && MAPA[y-1][x] == 0){
			y--;
			flag = true;
		}else{
			flag = false;
		}					
	}

    void Mover(char tecla) {
    	
    	cordenada_anterior.X = x;
		cordenada_anterior.Y = y;
		
        if (tecla == 72 && MAPA[y-1][x] == 0 ){
			dir = 4;  
			flag = true;
		}
        else if (tecla == 80 && MAPA[y+1][x] == 0 ){
			dir = 2;   
			flag = true; 
		}
        else if (tecla == 75 && MAPA[y][x-1] == 0 ){
			dir = 3;
			flag = true;  
		}
        else if (tecla == 77 && MAPA[y][x+1] == 0){
			dir = 1;  
			flag = true; 
		}else{
			flag = false;
		}
    }

    void Mostrar() {
		
		//DibujarMapa();
   
        coord.X = x;
        coord.Y = y;
        
      
      	if(flag == true){
	      	mtx.lock();
		    
		    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),2);  //Color de jugador  
			 	    
	        cout << c;
	       
		    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cordenada_anterior);
		    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0);  
		     
	        cout << c;
	        
	        mtx.unlock();	 
			       
		  }else{
		  	
		  	mtx.lock();
		  	
		  	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),2);  //Color de jugador  
			 	    
	        cout << c;
	        
	        mtx.unlock();
		  }
      
      	
    }
};

struct Enemigo {

	COORD coord;
	COORD cor2;
	int x = 14;
	int y = 10;
	char c = 219;
	int direccion = 1;
		
	void Mover(){	
		
		cor2.X = x;
		cor2.Y = y;	
		
		std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_int_distribution<int> distribution(1, 3); 
        int aleatorio = distribution(generator);

		if(direccion == 1){
			bool hayOtrasDirecciones = (MAPA[y - 1][x] == 0 || MAPA[y][x + 1] == 0 || MAPA[y + 1][x] == 0);
			if(hayOtrasDirecciones){
				switch(aleatorio){
					case 1:
						if (MAPA[y - 1][x] == 0) {
                    		y--;
                    		direccion = 4;
                		} else if (MAPA[y][x + 1] == 0) {
                       		x++;
                       		direccion = 1;
                    	} else if (MAPA[y + 1][x] == 0) {
                            y++;
                            direccion = 2;
                        }              
                		break; 						
					case 2:
						if (MAPA[y][x + 1] == 0) {
                    		x++;
                       		direccion = 1;
                		} else if (MAPA[y - 1][x] == 0) {
                       		y--;
                       		direccion = 4;
                    	} else if (MAPA[y + 1][x] == 0) {
                            y++;
                            direccion = 2;
                        }
                		break; 	
					case 3:
						if (MAPA[y + 1][x] == 0) {
                    		y++;
                       		direccion = 2;
                		} else if (MAPA[y - 1][x] == 0) {
                       		y--;
                       	    direccion = 4;
                    	} else if (MAPA[y][x + 1] == 0) {
                            x++;
                            direccion = 1;
                        }
                		break; 			
				}
			}else{
				x--;
				direccion = 3;
			}	
		}
		else if(direccion == 2){
			bool hayOtrasDirecciones = (MAPA[y][x + 1] == 0 || MAPA[y + 1][x] == 0 || MAPA[y][x - 1] == 0);
			if(hayOtrasDirecciones){
				switch(aleatorio){
					case 1:
						if (MAPA[y][x + 1] == 0) {
                    		x++;
                    		direccion = 1;
                		} else if (MAPA[y + 1][x] == 0) {
                       		 	y++;
                       		 	direccion = 2;
                    	} else if (MAPA[y][x - 1] == 0) {
                            		x--;
                            		direccion = 3;
                        }                   		                		
                		break; 						
					case 2:
						if (MAPA[y + 1][x] == 0) {
                    		y++;
                       		direccion = 2;
                		} else if (MAPA[y][x + 1] == 0) {
                       		 	x++;
                       		 	direccion = 1;
                    	} else if (MAPA[y][x - 1] == 0) {
                            		x--;
                            		direccion = 3;
                        }
                    		
                		
                		break; 
					case 3:
						if (MAPA[y][x - 1] == 0) {
                    		x--;
                       		direccion = 3;
                		} else if (MAPA[y][x + 1] == 0) {
                       		 	x++;
                       		 	direccion = 1;
                    	} else if (MAPA[y + 1][x] == 0) {
                            		y++;
                            		direccion = 2;
                        }
                    		
                		
                		break; 			
				}
			}else{
				y--;
				direccion = 4;
			}	
			
		}
		
		else if(direccion == 3){
			bool hayOtrasDirecciones = (MAPA[y - 1][x] == 0 || MAPA[y + 1][x] == 0 || MAPA[y][x - 1] == 0);
			if(hayOtrasDirecciones){
				switch(aleatorio){
					case 1:
						if (MAPA[y - 1][x] == 0) {
                    		y--;
                    		direccion = 4;
                		} else if (MAPA[y + 1][x] == 0) {
                       		 	y++;
                       		 	direccion = 2;
                    		} else if (MAPA[y][x - 1] == 0) {
                            		x--;
                            		direccion = 3;
                        		}
                    		
                		
                		break; 
						
					case 2:
						if (MAPA[y + 1][x] == 0) {
                    		y++;
                       		direccion = 2;
                		} else if (MAPA[y - 1][x] == 0) {
                       		 	y--;
                       		 	direccion = 4;
                    		} else if (MAPA[y][x - 1] == 0) {
                            		x--;
                            		direccion = 3;
                        		}
                    		
                		
                		break; 
					case 3:
						if (MAPA[y][x - 1] == 0) {
                    		x--;
                       		direccion = 3;
                		} else if (MAPA[y - 1][x] == 0) {
                       		 	y--;
                       		 	direccion = 4;
                    		} else if (MAPA[y + 1][x] == 0) {
                            		y++;
                            		direccion = 2;
                        		}
                    		
                		
                		break; 			
				}
			}else{
				x++;
				direccion = 1;
			}	
			
		}
		
		else if(direccion == 4){
			bool hayOtrasDirecciones = (MAPA[y - 1][x] == 0 || MAPA[y][x + 1] == 0 || MAPA[y][x - 1] == 0);
			if(hayOtrasDirecciones){
				switch(aleatorio){
					case 1:
						if (MAPA[y - 1][x] == 0) {
                    		y--;
                    		direccion = 4;
                		} else if (MAPA[y][x + 1] == 0) {
                       		 	x++;
                       		 	direccion = 1;
                    		} else if (MAPA[y][x - 1] == 0) {
                            		x--;
                            		direccion = 3;
                        		}
                    		
                		
                		break; 
						
					case 2:
						if (MAPA[y][x + 1] == 0) {
                    		x++;
                       		direccion = 1;
                		} else if (MAPA[y - 1][x] == 0) {
                       		 	y--;
                       		 	direccion = 4;
                    		} else if (MAPA[y][x - 1] == 0) {
                            		x--;
                            		direccion = 3;
                        		}
                    		
                		
                		break; 
					case 3:
						if (MAPA[y][x - 1] == 0) {
                    		x--;
                       		direccion = 3;
                		} else if (MAPA[y - 1][x] == 0) {
                       		 	y--;
                       		 	direccion = 4;
                    		} else if (MAPA[y][x + 1] == 0) {
                            		x++;
                            		direccion = 1;
                        		}
                    		
                		
                		break; 			
				}
			}else{
				y++;
				direccion = 2;
			}	
			
		}
	
 
	}
		
	void Mostrar(int color){
		
	    coord.X = x;
	    coord.Y = y;
	    
	    
	    mtx.lock();
	    
	    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);  //Color de jugador  
	    
        cout << c;
		  
       if(PUNTOS[cor2.Y][cor2.X] == 0){
       		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cor2);
	    	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6);  
        	cout << (char)250;
	   }else{
		   	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cor2);
		    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0);  
			
	        cout << c;	
	   }
        
       mtx.unlock();
		     	    
	}
		
};

bool Captura(Jugador* jugador, Enemigo* enemigo){
	if((jugador -> x == enemigo ->x && jugador -> y == enemigo -> y) ||
		(jugador -> x+1 == enemigo ->x && jugador -> y == enemigo -> y) ||
		(jugador -> x-1 == enemigo ->x && jugador -> y == enemigo -> y) ||
		(jugador -> x == enemigo ->x && jugador -> y+1 == enemigo -> y) ||
		(jugador -> x == enemigo ->x && jugador -> y-1 == enemigo -> y))
	{     
		return true;
	}	
	else{
		return false;
	}	
	
}

void SetConsoleSize(int columns, int rows) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT rect = {0, 0, static_cast<SHORT>(columns - 1), static_cast<SHORT>(rows - 1)};
    SetConsoleWindowInfo(hConsole, TRUE, &rect);   
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false;  // Ocultar el cursor
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}


void FuncionEnemigo(Enemigo* enemigo,int color) {	
	
    while (!finJuego){
    	enemigo->Mover();
    	enemigo->Mostrar(color);
    	verPuntaje();
        std::this_thread::sleep_for(std::chrono::milliseconds(150));       	 
    } 
    
    while(!finEnemigos){
    	enemigo->Mover();
    	enemigo->Mostrar(color);
        std::this_thread::sleep_for(std::chrono::milliseconds(150)); 
	}
}

void FuncionJugador(Jugador* jugador,Enemigo* enemigo1,Enemigo* enemigo2,Enemigo* enemigo3,Enemigo* enemigo4, int lifes) {
	
	DibujarPuntaje();
	DibujarVidas();
	
    do {
   		if(!_kbhit()){ 			
   			jugador -> MovimientoAutomatico();
   			jugador -> ActualizarPuntos();
   			jugador->Mostrar();
   			std::this_thread::sleep_for(std::chrono::milliseconds(150));
   			
		   }
		   
        else if(_kbhit()) {
            jugador->Mover(_getch());
            jugador -> ActualizarPuntos();
            jugador->Mostrar();
			}

		if(Captura(jugador,enemigo1)==true || Captura(jugador,enemigo2)==true || Captura(jugador,enemigo3)==true || Captura(jugador,enemigo4)==true || finJuego == true){
					
			std::lock_guard<std::recursive_mutex> lock(vidasMutex);
			
            if(lifes>0 && finJuego == false){
            	
            	Beep(600,300);
            	DibujarMapa();
            	DibujarPuntos();
            	jugador -> ActualizarCordenada();
            	std::this_thread::sleep_for(std::chrono::seconds(1));
            	jugador->actualizarVida();
            	FuncionJugador(jugador,enemigo1,enemigo2,enemigo3,enemigo4,lifes-1);
            	
            	
            	
			}else if(lifes>0 && finJuego == true){
				auto end = std::chrono::high_resolution_clock::now();
				std::chrono::duration<double, std::milli> elapsed = end - start;
				DibujarMapa();
            	DibujarPuntaje();
            	DibujarPuntos();
            	SetConsoleSize(40, 20);
            	std::this_thread::sleep_for(std::chrono::seconds(4));
            	finEnemigos = true;    
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {3, 7});
    			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);  // Color rojo
    			
    			float PF=PuntajeFinal(puntaje, lifes, elapsed.count());
    			
    			
    			 	
    			cout << "Ha ganado la partida!!! "<<"Vidas restantes: "<<lifes<<", Puntaje: "<<PF<<",Tiempo en el juego: "<<elapsed.count()<<" milisegundos"<< endl;
    			   			
    			std::vector<double> arr = readNumbersFromFile("RankingPuntajes.txt");

    			arr.push_back(PF);
				
				std::vector<double> array1=arr;
				std::vector<double> array2=arr;
				
				
				
			std::chrono::duration<double> tiempo_paralelo(0);
			auto tiempo_inicio = std::chrono::high_resolution_clock::now();
			merge_sort_paralelo(array1, 0, arr.size() - 1,0); // Ordenar el vector completo
			auto tiempo_final = std::chrono::high_resolution_clock::now();
    		    
    		tiempo_paralelo = tiempo_final - tiempo_inicio;
    			
    			
	    			
	    	std::chrono::duration<double> tiempo_secuencial(0);
 			auto tiempo_inicio2 = std::chrono::high_resolution_clock::now();
    		merge_sort_secuencial(array2, 0, arr.size() - 1);  // Ordenar el vector completo
    		auto tiempo_final2=std::chrono::high_resolution_clock::now();
    		    
    		    
    		   	tiempo_secuencial = tiempo_final2 - tiempo_inicio2;
    			
    			saveArrayToFile(array2, "RankingPuntajes.txt");
    			cout<<"Tiempo en Paralelo:  "<<tiempo_paralelo.count()<<endl;
    			cout<<"Tiempo en Secuencial:  "<<tiempo_secuencial.count()<<endl;
    			cout<<"  >>Ranking Registrado: "<<arr.size()-findRanking(arr, PF)+1<<endl;
    			cout << "Aceleración: " << tiempo_secuencial/tiempo_paralelo << endl;
    			cout << "Eficiencia " << 100 * (tiempo_secuencial/tiempo_paralelo) / 4 << "%" << endl;
  				cout << "Número de procesadores: " <<  4 << std::endl;
    			
			}
			else{
				auto end = std::chrono::high_resolution_clock::now();
				std::chrono::duration<double, std::milli> elapsed = end - start;
				
				Beep(600,300);
				finJuego = true;
            	DibujarMapa();
            	DibujarPuntaje();
            	DibujarPuntos();
            	SetConsoleSize(40, 20);
            	std::this_thread::sleep_for(std::chrono::seconds(4));
            	finEnemigos = true;    
				system("cls");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {3, 7});
    			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);  // Color rojo
    			
    			float PF=PuntajeFinal(puntaje, lifes, elapsed.count());
    			   			
    			cout << "Game Over, te quedaste sin vidas , Puntaje: " << PF <<", Tiempo: "<<elapsed.count()<<" milisegundos"<< endl;
    			std::vector<double> arr = readNumbersFromFile("RankingPuntajes.txt");
    		
    			arr.push_back(PF);
    			
    			std::vector<double> array1=arr;
				std::vector<double> array2=arr;
				
				std::chrono::duration<double> tiempo_paralelo(0);
 				auto tiempo_inicio = std::chrono::high_resolution_clock::now();
    			merge_sort_paralelo(array1, 0, arr.size() - 1,0);  // Ordenar el vector completo
    		    auto tiempo_final=std::chrono::high_resolution_clock::now();
    		    
    		    tiempo_paralelo = tiempo_final - tiempo_inicio;
    		    
    		    std::chrono::duration<double> tiempo_secuencial(0);
 				auto tiempo_inicio2 = std::chrono::high_resolution_clock::now();
    			merge_sort_secuencial(array2, 0, arr.size() - 1);  // Ordenar el vector completo
    		    auto tiempo_final2=std::chrono::high_resolution_clock::now();
    		    
    		   	tiempo_secuencial = tiempo_final2 - tiempo_inicio2;
 
    			saveArrayToFile(array2, "RankingPuntajes.txt");
    			cout<<"Tiempo en Paralelo:  "<<tiempo_paralelo.count()<<endl;
    			cout<<"Tiempo en Secuencial:  "<<tiempo_secuencial.count()<<endl;
    			
    			cout<<"  >>Ranking Registrado: "<<arr.size()-findRanking(arr, PF)+1<<endl;
    			
    			
    			
    			cout << "Aceleración: " << tiempo_secuencial/tiempo_paralelo << endl;
    			cout << "Eficiencia " << 100 * (tiempo_secuencial/tiempo_paralelo) / 4 << "%" << endl;
  				cout << "Número de procesadores: " <<  4 << std::endl;
  				
			}
        }
		  		        
    }while(!finJuego);	        

}

int main() {
	auto start = std::chrono::high_resolution_clock::now();
	SetConsoleSize(40, 20);
	
	DibujarMapa();
	DibujarPuntos();
	
    Jugador *jugador = new Jugador;

	Enemigo *enemigo1 = new Enemigo;
	Enemigo *enemigo2 = new Enemigo;
	Enemigo *enemigo3 = new Enemigo;
	Enemigo *enemigo4 = new Enemigo;
	
	std::thread hiloEnemigo1(FuncionEnemigo,enemigo1,4);
    std::thread hiloEnemigo2(FuncionEnemigo,enemigo2,5);
    std::thread hiloEnemigo3(FuncionEnemigo,enemigo3,14);
    std::thread hiloEnemigo4(FuncionEnemigo,enemigo4,7);
	std::thread hiloJugador(FuncionJugador, jugador,enemigo1,enemigo2,enemigo3,enemigo4,number_ofLives);

	
	if(hiloJugador.joinable()){
		hiloJugador.join();
	}
	
	hiloEnemigo1.detach();
    hiloEnemigo2.detach();
	hiloEnemigo3.detach();
	hiloEnemigo4.detach();
   
	return 0;
}