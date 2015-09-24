#include <iostream>
#include <stdio.h>
#include <fstream> 
#include <string.h> 
#include <string>
#include <vector>
#include <stdlib.h>
#include <iomanip>
#include <algorithm>
#include <cmath>

using namespace std;

struct IndiceClientes{
	char llave[13];
	int rrn; 
	bool operator<( const IndiceClientes& indice ) const { 
    	int compare = strcmp(llave, indice.llave);
    	if (compare < 0){
    		return true;
    	} else {
    		return false;
    	}
    }
    bool operator>( const IndiceClientes& indice ) const { 
    	int compare = strcmp(llave, indice.llave);
    	if (compare > 0){
    		return true;
    	} else {
    		return false;
    	}
    }
};

struct IndiceLineas{
	int llave;
	int rrn; 
	bool operator<( const IndiceLineas& indice ) const { 
    	return llave < indice.llave;
    }
};

struct NodoClientes{
	int parent;
	int order;
	int num;
	vector<IndiceClientes> keys;
	vector<int> hijos;
	NodoClientes(){
		parent = -1;
	}
	NodoClientes(int orden, int numero){
		order = orden;
		num = numero;
		parent = -1;
	}
	NodoClientes(int orden, int numero, int padre){
		order = orden;
		num = numero;
		parent = padre;
	}
	bool isFull(){
		if (keys.size() == order-1){
			return true;
		} else {
			return false;
		}
	}
	bool isLeaf(){
		if (hijos.size()==0){
			return true;
		} else {
			return false;
		}
	}
	string toString(){
		string s ="";
		s+="Orden: ";
		s+=to_string(order);
		s+="\nNumero: ";
		s+=to_string(num);
		s+="\nKeys: |";
		for (int i = 0; i < keys.size(); ++i){
			s+=keys[i].llave;
			s+="-";
			s+=to_string(keys[i].rrn);
			s+="|";
		}
		s+="\nHijos: |";
		for (int i = 0; i < hijos.size(); ++i){
			s+=to_string(hijos[i]);
			s+="|";
		}
		return s;
	}
};

struct BTreeClientes{
	int order;
	int nodecount;
	bool hasRoot;
	NodoClientes root;
	vector<NodoClientes> nodos;
	BTreeClientes() : order(3), nodecount(0), hasRoot(false), root() {
	}
};

struct NodoLineas{
	int parent;
	int order;
	int num;
	vector<IndiceLineas> keys;
	vector<int> hijos;
	NodoLineas(){
		parent = -1;
	}
	NodoLineas(int orden, int numero){
		order = orden;
		num = numero;
		parent = -1;
	}
	NodoLineas(int orden, int numero, int padre){
		order = orden;
		num = numero;
		parent = padre;
	}
	bool isFull(){
		if (keys.size() == order-1){
			return true;
		} else {
			return false;
		}
	}
	bool isLeaf(){
		if (hijos.size()==0){
			return true;
		} else {
			return false;
		}
	}
	string toString(){
		string s ="";
		s+="Orden: ";
		s+=to_string(order);
		s+="\nNumero: ";
		s+=to_string(num);
		s+="\nKeys: |";
		for (int i = 0; i < keys.size(); ++i){
			s+=keys[i].llave;
			s+="-";
			s+=to_string(keys[i].rrn);
			s+="|";
		}
		s+="\nHijos: |";
		for (int i = 0; i < hijos.size(); ++i){
			s+=to_string(hijos[i]);
			s+="|";
		}
		return s;
	}
};

struct BTreeLineas{
	int order;
	int nodecount;
	bool hasRoot;
	NodoLineas root;
	vector<NodoLineas> nodos;
	BTreeLineas() : order(3), nodecount(0), hasRoot(false), root() {
	}
};

struct Ciudades{
	int idCiudad;
	char* nombreCiudad;
};

struct Clientes{
	char* idCliente;
	char* nombreCliente;
	char genero;
	int idCiudad;
};

struct Lineas{
	int numero;
	char* id;
};

struct Llamadas{
	int numero;
	long inicio;
	long final;
	int destino;
};

struct Factura {
	char* id;
	char* emisor;
	float subtotal;
	float isv;
	float total;
};

istream& operator>>(istream& input1, Ciudades& ciudades){
	input1 >> ciudades.idCiudad >> ciudades.nombreCiudad;
	return input1;
}

ostream& operator<<(ostream& output1, const Ciudades& ciudades){
	output1 << ciudades.idCiudad << "\t" << ciudades.nombreCiudad;
	return output1;  
}

istream& operator>>(istream& input2, Clientes& clientes){
	input2 >> clientes.idCliente >> clientes.nombreCliente >> clientes.genero >> clientes.idCiudad;
	return input2;
}

ostream& operator<<(ostream& output2, const Clientes& clientes){
	output2 << clientes.idCliente << setw(25) << clientes.nombreCliente << setw(20) << clientes.genero << setw(13) << clientes.idCiudad;
	return output2;  
}

istream& operator>>(istream& input3, Lineas& lineas){
	input3 >> lineas.numero >> lineas.id;
	return input3;
}

ostream& operator<<(ostream& output3, const Lineas& lineas){
	output3 << lineas.numero << setw(20) << lineas.id;
	return output3;  
}

istream& operator>>(istream& input4, Llamadas& llamadas){
	input4 >> llamadas.numero >> llamadas.inicio >> llamadas.final >> llamadas.destino;
	return input4;
}

ostream& operator<<(ostream& output4, const Llamadas& llamadas){
	output4 << llamadas.numero << setw(15) << llamadas.inicio << setw(15) << llamadas.final << setw(10) << llamadas.destino;
	return output4;  
}

BTreeClientes arbolClientes;
BTreeLineas arbolLineas;
vector<IndiceClientes> indicesClientes;
vector<IndiceLineas> indicesLineas;

void indexar(vector<Clientes>, vector<Lineas>);
void leerTodos();
string datosCliente();
void eliminarCliente(int);
void agregarCliente();
void appendCliente (string);
void modificarCliente(int);
int buscarCliente(char[]);
void datosLinea(char[]);
void agregarLinea(string);
void appendLinea(string);
void modificarLinea(int, string); 
void eliminarLinea(int);
void datosLinea(int);
int buscarLinea(int);
void buscarLinea(char*);
void buscarLineas(char*);
void buscarLlamadas (vector<string>, char*);
void agregarBTreeClientes(IndiceClientes indice);
void agregarBTreeLineas(IndiceLineas indice);
void splitRootClientes(IndiceClientes indice);
void splitNodeClientes(IndiceClientes indice, int nodenum, int promotenum, int parent);
int findpos(vector<IndiceClientes> keys, IndiceClientes indice);
bool leftright(vector<IndiceClientes> keys, IndiceClientes indice);
int findNodeNum(vector<NodoClientes> vec, int n);
void facturacion (vector<string>, vector<string>, char*);
void exportFacturasJson(vector<Factura> vf);

int main(int argc, char const *argv[]){
	//leerTodos();
	int op1, op2, op3, RRN;
	char id [14];
	bool flagId;

	do {
		cout << "1. Clientes \n2. Lineas\n3. Salir" << endl;
		cin >> op1;
		if (op1 == 1) {
			do {
				cout << "Opciones Clientes\n1. Agregar\n2. Modificar\n3. Eliminar\n4. Buscar\n5. Transacciones\n6. Salir" << endl;
				cin >> op2;
				if (op2 == 1){
					agregarCliente();
				}else if (op2 == 2) {
					cout << "Seleccione el registro a modificar: ";
					cin >> RRN;
					modificarCliente(RRN-1);
				} else if (op2 == 3) {
					cout << "Seleccione el registro a eliminar: ";
					cin >> RRN;
					eliminarCliente(RRN-1);
				} else if (op2 == 4) {
					getchar();
					do {
						flagId = true; 
						cout << "Numero de Identidad: ";
						cin.getline(id,14);

						if ((unsigned)strlen(id) < 13) {
							flagId = false;
							cerr << "Valor no valido" << endl;
						}
					} while(!flagId);
					int found = buscarCliente(id);
					if (found != 0) {
						cout << "RRN usuario: " << found << endl;
					} else {
						cout << "Usuario no encontrado." << endl;
					}
				} else if (op2 == 5) {
					getchar();
					do {
						flagId = true; 
						cout << "Numero de Identidad: ";
						cin.getline(id,14);

						if ((unsigned)strlen(id) < 13) {
							flagId = false;
							cerr << "Valor no valido" << endl;
						}
					} while(!flagId);
					buscarLineas(id);

				}
			}while (op2 <= 5);


		} else if (op1 == 2) {
			do {
				cout << "Opciones Lineas\n1. Agregar\n2. Modificar\n3. Eliminar\n4. Buscar\n5. Salir" << endl;
				cin >> op3;
				
				if (op3 == 1){
					getchar();
					char id [14];
					bool flagId;
					do {
						flagId = true; 
						cout << "Numero de Identidad: ";
						cin.getline(id,14);

						if ((unsigned)strlen(id) < 13) {
							flagId = false;
							cerr << "Valor no valido" << endl;
						}
					} while(!flagId);
					datosLinea(id);
				}else if (op3 == 2) {
					cout << "Seleccione el registro a modificar: ";
					cin >> RRN;
					datosLinea(RRN-1);
				} else if (op3 == 3) {
					cout << "Seleccione el registro a eliminar: ";
					cin >> RRN;
					eliminarLinea(RRN-1);
				} else if (op3 == 4) {
					int numCliente;
					cout << "Ingrese el numero del cliente: ";
					cin >> numCliente;
					int found = buscarLinea(numCliente);
					if (found != 0) {
						cout << "RRN usuario: " << found << endl;
					} else {
						cout << "Usuario no encontrado." << endl;
					}


				}
			}while (op3 <= 4);

		}


	} while (op1 <= 2);
	return 0;
}

void leerTodos(){
	string lineaCiudades;
	string lineaClientes;
	string lineaLineas;
	string lineaLlamadas;

	vector<string>sv1;
	vector<string>sv2;
	vector<string>sv3;
	vector<string>sv4;
	
	ifstream fileCiudades("Files/ciudades.txt", ifstream::in);
	ifstream fileClientes("Files/dataClientes.txt", ifstream::in);
	ifstream fileLineas("Files/lineasClientes.txt", ifstream::in);
	ifstream fileLlamadas("Files/llamadas.txt", ifstream::in);

	int num = 1;
	if (fileCiudades.is_open()){
		fileCiudades.seekg(40, fileCiudades.beg);
		int length = 4;
		lineaCiudades = "";
		while (fileCiudades.good()){
			char* caracteres = new char[length];
			fileCiudades.read(caracteres, length);
			if (num%2 == 0){
				lineaCiudades += caracteres;
				sv1.push_back(lineaCiudades);
				delete[] caracteres;
				lineaCiudades = "";
				length = 4;
			} else {
				lineaCiudades += caracteres;
				delete[] caracteres;
				length = 17;
			}
			num++;
			if (num == 61){
				break;
			}
		}
		fileCiudades.close();
	}

	num = 1;
	bool alternado = false;
	if (fileClientes.is_open()){
		fileClientes.seekg(87, fileClientes.beg);
		int length = 13;
		lineaClientes = "";
		char* caracteres2;
		while (fileClientes.good()){
			caracteres2 = new char[length];
			fileClientes.read(caracteres2, length);
			if (num%2 == 0){
				if (alternado){
					for (int i = 0; i < 40; ++i){
						lineaClientes += caracteres2[i];
					}
					delete[] caracteres2;
					length = 1;
					alternado = true;
				} else {
					lineaClientes += caracteres2;
					sv2.push_back(lineaClientes);
					delete[] caracteres2;
					lineaClientes = "";
					length = 13;
					alternado = false;
				}
			} else {
				if (alternado){
					lineaClientes += caracteres2;
					delete[] caracteres2;
					length = 4;
					alternado = false;
				} else {
					lineaClientes += caracteres2;
					delete[] caracteres2;
					length = 40;
					alternado = true;
				}
			}
			num++;
			if (num == 2001){
				break;
			}
		}
		fileClientes.close();
	}

	num = 1;
	alternado = false;
	if (fileLineas.is_open()){
		fileLineas.seekg(39, fileLineas.beg);
		int length = 8;
		lineaLineas = "";
		while (fileLineas.good()){
			char* caracteres3 = new char[length];
			fileLineas.read(caracteres3, length);
			if (num%2 == 0){
				lineaLineas += caracteres3;
				sv3.push_back(lineaLineas);
				delete[] caracteres3;
				lineaLineas = "";
				length = 8;
			} else {
				for (int i = 0; i < 8; ++i){
					lineaLineas += caracteres3[i];
				}
				delete[] caracteres3;
				length = 13;
			}
			num++;
			if (num == 1501){
				break;
			}
			
		}
		fileLineas.close();
	}

	num = 1;
	alternado = false;
	if (fileLlamadas.is_open()){
		fileLlamadas.seekg(54, fileLlamadas.beg);
		int length = 8;
		char* caracteres4;
		lineaLlamadas = "";
		while (fileLlamadas.good()){
			caracteres4 = new char[length];
			fileLlamadas.read(caracteres4, length);
			if (num%2 == 0){
				if (alternado){
					for (int i = 0; i < 14; ++i){
						lineaLlamadas += caracteres4[i];
					}
					delete[] caracteres4;
					length = 14;
					alternado = true;
				} else {
					for (int i = 0; i < 8; ++i){
						lineaLlamadas += caracteres4[i];
					}
					sv4.push_back(lineaLlamadas);
					delete[] caracteres4;
					lineaLlamadas = "";
					length = 8;
					alternado = false;
				}
			} else {
				if (alternado){
					for (int i = 0; i < 14; ++i){
						lineaLlamadas += caracteres4[i];
					}
					delete[] caracteres4;
					length = 8;
					alternado = false;
				} else {
					for (int i = 0; i < 8; ++i){
						lineaLlamadas += caracteres4[i];
					}
					delete[] caracteres4;
					length = 14;
					alternado = true;
				}
			}
			num++;
			if (num == 200001){
				break;
			}
		}
		fileLlamadas.close();
	}

	char* st1; 
	char* st2;
	char* st3;
	char* st4;

	vector<Ciudades> vectorCiudades;
	vector<Clientes> vectorClientes;
	vector<Lineas> vectorLineas;
	vector<Llamadas> vectorLlamadas;

	Ciudades ciudades;
	Clientes clientes;
	Lineas lineas;
	Llamadas llamadas;

	for (int i = 0; i < sv1.size(); ++i) {
		st1 = new char[strlen(sv1[i].c_str())];
		strcat(st1, sv1[i].c_str());
		char* id = new char[2];
		for (int i = 0; i < 2; i++){
			id[i] = st1[i];
		}
		ciudades.idCiudad = atoi(id);
		delete[] id;
		char* nombre = new char[17];
		for (int i = 2; i < 19; i++){
			nombre[i-2] = st1[i];
		}
		ciudades.nombreCiudad = new char[17];
		strncat(ciudades.nombreCiudad, nombre, 17);
		vectorCiudades.push_back(ciudades);
	}

	for (int i = 0; i < sv2.size(); ++i) {
		st2 = new char[strlen(sv2[i].c_str())];
		strcat(st2, sv2[i].c_str());
		char* tempid = new char[13];
		for (int i = 0; i < 13; i++){
			tempid[i] = st2[i];
		}
		char* id = new char[13];
		strncat(id, tempid, 13);
		char* nombre = new char[41];
		int cont = 0;
		for (int i = 13; i < 52; i++){
			nombre[cont] = st2[i];
			cont++;
		}
		nombre[41] = '\0';
		clientes.genero = st2[54];
		char tempidCiudad[4];
		cont = 0;
		for (int i = 55; i < 59; i++){
			tempidCiudad[cont] = st2[i];
			cont++;
		}
		char* idCiudad = new char[4];
		strncat(idCiudad, tempidCiudad, 4);
		clientes.idCiudad = atoi(idCiudad);
		clientes.idCliente = new char[13];
		strncat(clientes.idCliente, id, 13);
		clientes.nombreCliente = new char[40];
		strncat(clientes.nombreCliente, nombre, 39);
		strcat(clientes.nombreCliente, " ");
		vectorClientes.push_back(clientes);
	}

	for (int i = 0; i < sv3.size(); ++i) {
		st3 = new char[strlen(sv3[i].c_str())];
		strcat(st3, sv3[i].c_str());
		char* numero = new char[8];
		for (int i = 0; i < 8; i++){
			numero[i] = st3[i];
		}
		numero[8] = '\0';
		lineas.numero = atoi(numero);
		char* id = new char[13];
		int cont = 0;
		for (int i = 8; i < 21; i++){
			id[cont] = st3[i];
			cont++;
		}
		lineas.id = new char[13];
		strncat(lineas.id, id, 13);
		delete[] numero;
		delete[] id;
		vectorLineas.push_back(lineas);
	}

	for (int i = 0; i < sv4.size(); ++i) {
		st4 = new char[strlen(sv4[i].c_str())];
		strcat(st4, sv4[i].c_str());
		char* numero = new char[8];
		for (int i = 0; i < 8; i++){
			numero[i] = st4[i];
		}
		llamadas.numero = atoi(numero);
		char* inicio = new char[13];
		int cont = 0;
		for (int i = 8; i < 22; i++){
			inicio[cont] = st4[i];
			cont++;
		}
		llamadas.inicio = atol(inicio);
		char* fin = new char[13];
		cont = 0;
		for (int i =22; i < 36; i++){
			fin[cont] = st4[i];
			cont++;
		}
		llamadas.final = atol(fin);
		char* destino = new char[8];
		cont = 0;
		for (int i = 36; i < 44; i++){
			destino[cont] = st4[i];
			cont++;
		}
		llamadas.destino = atoi(destino);
		vectorLlamadas.push_back(llamadas);
	}

	delete[] st1;
	delete[] st2;
	delete[] st3;
	delete[] st4;

	//indexar(vectorClientes ,vectorLineas);
}

void indexar(vector<Clientes> vectorClientes, vector<Lineas> vectorLineas){
	vector<IndiceClientes> indices1;
	vector<IndiceLineas> indices2;

	for (int i = 0; i < vectorClientes.size(); ++i){
		IndiceClientes indice;
		strcpy(indice.llave, vectorClientes[i].idCliente);
		indice.rrn = i;
		indices1.push_back(indice);
	}
	

	for (int i = 0; i < vectorLineas.size(); ++i){
		IndiceLineas indice;
		indice.llave = vectorLineas[i].numero;
		indice.rrn = i;
		indices2.push_back(indice);
	}

	sort(indices1.begin(), indices1.end());
	sort(indices2.begin(), indices2.end());

	ofstream outputClientes;
	outputClientes.open("Files/indicesClientes.txt");
	if (outputClientes.is_open()) {
		for (int i = 0; i < indices1.size(); ++i){
			char index[22];
			strcpy(index, indices1[i].llave);
			string s = to_string(indices1[i].rrn);
			char RRN[4];
			strcpy(RRN, s.c_str());
			int len = strlen(RRN);
			if (len == 1){
				char temp[4];
				strcpy(temp, RRN);
				strcpy(RRN, "000");
				strcat(RRN, temp);
			} else if (len == 2){
				char temp[4];
				strcpy(temp, RRN);
				strcpy(RRN, "00");
				strcat(RRN, temp);
			} else if (len == 3){
				char temp[4];
				strcpy(temp, RRN);
				strcpy(RRN, "0");
				strcat(RRN, temp);
			}
			strcat(index, RRN);
			outputClientes << index;
		}
	} else {
		cerr << "No se pueden escribir los datos" << endl;
	}
	outputClientes.close();
	ofstream outputLineas;
	outputLineas.open("Files/indicesLineas.txt");
	if (outputLineas.is_open()) {
		for (int i = 0; i < indices2.size(); ++i){
			char index[22];
			string numero = to_string(indices2[i].llave);
			char num[8];
			strcpy(num, numero.c_str());
			strcpy(index, num);
			string s = to_string(indices2[i].rrn);
			char RRN[4];
			strcpy(RRN, s.c_str());
			int len = strlen(RRN);
			if (len == 1){
				char temp[4];
				strcpy(temp, RRN);
				strcpy(RRN, "000");
				strcat(RRN, temp);
			} else if (len == 2){
				char temp[4];
				strcpy(temp, RRN);
				strcpy(RRN, "00");
				strcat(RRN, temp);
			} else if (len == 3){
				char temp[4];
				strcpy(temp, RRN);
				strcpy(RRN, "0");
				strcat(RRN, temp);
			}
			strcat(index, RRN);
			outputLineas << index;
		}
	} else {
		cerr << "No se pueden escribir los datos" << endl;
	}
	outputLineas.close();
}

string datosCliente(){
	
	string temp = "", nomCliente;
	char tempIdCiudad[5];
	char name[40];
	char id[14];
	char genero;
	int idCiudad;
	bool flagId, flagName, flagGenero, flagCiudad;
	
	getchar();
	cin.clear();
	fflush(stdin);
	
	do {
		flagId = true; 
		cout << "Numero de Identidad: ";
		cin.getline(id,14);

		if ((unsigned)strlen(id) < 13) {
			flagId = false;
			cerr << "Valor no valido" << endl;
		}
	} while(!flagId);

	do {
		flagName = true; 
		cout << "Nombre: ";
		cin.getline(name, 40);

		if ((unsigned)strlen(name) == 0) {
			flagName = false;
			cerr << "Valor no valido" << endl;
		}

	} while(!flagName);

	do {
		flagCiudad = true;
		cout << "Id Ciudad [1-30]: ";
		cin >> idCiudad;
		if (idCiudad > 30)
			flagCiudad = false;
		if (idCiudad < 1)
			flagCiudad = false;
		if (!flagCiudad)
			cerr << "Valor no valido" << endl;

	} while (!flagCiudad);

	do {
		flagGenero = false;
		cout << "Genero [F/M]: ";
		cin >> genero;
		genero = toupper(genero);
		
		if (genero == 'F') 
			flagGenero = true;
		else if (genero == 'M') 
			flagGenero = true;
		else
			cerr << "Valor no valido" << endl;

	} while (!flagGenero);

	
	for(int i = (unsigned)strlen(name); i < 40; i++){
		strcat (name," ");
	}
	
	
	string s = to_string(idCiudad);
	char const *schar = s.c_str();

	*tempIdCiudad = 0;
	
	if (idCiudad < 10) {
		strcat (tempIdCiudad,"000");
		strcat (tempIdCiudad, schar);	
	} else {
		strcat (tempIdCiudad,"00");
		strcat (tempIdCiudad, schar);
	}

	temp += id;
	temp += name;
	temp += genero;
	temp += tempIdCiudad;
	datosLinea(id);
	return temp;
}

void eliminarCliente(int RRN){
	char idCliente [14];
	fstream is("Files/dataClientes.txt");
	if(is.is_open()){
		char availList[5] = "";
		

		is.read(availList, sizeof(availList)-1);
		
		int offset = 87 + RRN * 58;
		is.seekg(offset);
		is.seekp(offset);
		is.read(idCliente, 13);
		idCliente[13] = '\0';
		is.seekg(offset);
		is.seekp(offset);
		is.write("*",1);
		
		is.write(availList, 4);
		
		RRN = RRN + 1;
		string newAvailList = to_string(RRN);
		for (int i = newAvailList.size(); i < 5; ++i){
			newAvailList += " ";
		}
		
		is.seekp(0);
		is.write(newAvailList.c_str(), newAvailList.size());

		is.close();
	}else {
		cerr << "No se puede abrir el archivo." << endl ;
	}
	
}

void agregarCliente() {
	
	string temp = datosCliente();
	
	const char* buffer = new char[temp.size()];
	buffer = temp.c_str();
	fstream fileClientes ("Files/dataClientes.txt");
	if (fileClientes.is_open()) {
		char availList[5] = "";
		fileClientes.read(availList, sizeof(availList)-1);

		int RRN = stoi(availList);

		if(RRN != -1) {
			int offset = 87 + (RRN - 1) * 58;

			fileClientes.seekg(offset);

			char * tempAvailList = new char [58];

			fileClientes.read (tempAvailList,58);

   		//Splitting into tokens
			char * pch;
			pch = strtok (tempAvailList," ");
			char * finalAvailList;
			finalAvailList = strtok (pch, "*");

			fileClientes.seekp(offset);
			fileClientes.write(buffer,temp.size());
			fstream fileClientes ("Files/dataClientes.txt");
		}
	}
	if (fileClientes.is_open()) {
		char availList[5] = "";
		fileClientes.read(availList, sizeof(availList)-1);

		int RRN = stoi(availList);

		if(RRN != -1) {
			int offset = 87 + (RRN - 1) * 58;

			fileClientes.seekg(offset);

			char * tempAvailList = new char [58];

			fileClientes.read (tempAvailList,58);

   		//Splitting into tokens
			char * pch;
			pch = strtok (tempAvailList," ");
			char * finalAvailList;
			finalAvailList = strtok (pch, "*");

			fileClientes.seekp(offset);
			fileClientes.write(buffer,temp.size());
			string strTemp;
			strcat (finalAvailList," ");
			strTemp = finalAvailList;
			fileClientes.seekp(0);
			fileClientes.write(finalAvailList, strTemp.size());
			fileClientes.close();

		} else {
			appendCliente(temp);
		}
	}else{
		cerr << "No se puede abrir el archivo." << endl;
	}

}

void appendCliente (string temp) {
	ofstream fileClientes ("Files/dataClientes.txt", ios::app);
	if(fileClientes.is_open()) {
		const char* buffer = new char[temp.size()];
		buffer = temp.c_str();

		fileClientes.write(buffer, temp.size());
		fileClientes.close();
	} else {
		cerr << "No se puede abrir el archivo." << endl;
	}
}

void modificarCliente(int RRN){
	string temp = datosCliente();

	const char* buffer = new char[temp.size()];
	buffer = temp.c_str();
	
	fstream is("Files/dataClientes.txt");
	if(is.is_open()){

		int offset = 87 + RRN * 58;
		is.seekg(offset);
		is.seekp(offset);
		is.write(buffer,temp.size());
		
		is.close();
	}else{
		cerr << "Could not open file" << endl ;
	}
}

int buscarCliente(char* idCliente) {
	fstream is("Files/dataClientes.txt");
	int RRN = 0, offset;
	char idClienteTemp [14];
	if(is.is_open()) {
		while(!is.eof()) {
			offset = 87 + RRN * 58;
			is.seekg(offset);
			is.seekp(offset);
			is.read(idClienteTemp, 13);
			idClienteTemp[13] = '\0';
			
			if((strcmp (idCliente, idClienteTemp) == 0)){
				return RRN + 1;
				is.close();
				break;
			}
			RRN++;
		}

		is.close();
	} else {
		cerr << "No se puede abrir el archivo." << endl;
	}
	return 0;
}

void datosLinea(char* idCliente) {
	char op;
	int numero;
	
	do {
		cout << "Numero de linea: ";
		cin >> numero;
		
		string temp = "";	
		temp += to_string(numero);
		temp += idCliente;
		
		agregarLinea(temp);

		cout << "Desea agregar otra linea? [S/N]: ";
		cin >> op;
		op = toupper(op); 
	}while(op == 'S');
}

void datosLinea(int RRN) {
	int numero;
	bool flagId;
	string id;
	do {
		flagId = true; 
		cout << "Numero de Identidad: ";
		//cin.getline(id,14);
		cin >> id;
		if (id.size() < 13) {
			flagId = false;
			cerr << "Valor no valido" << endl;
		} else if (id.size() > 13) {
			flagId = false;
			cerr << "Valor no valido" << endl;
		}
	} while(!flagId);
	
	cout << "Numero de linea: ";
	cin >> numero;

	string temp = "";
	temp += to_string(numero);
	temp += id;

	modificarLinea(RRN, temp);

}

void agregarLinea(string temp) {

	const char* buffer = new char[temp.size()];
	buffer = temp.c_str();

	fstream fileLineas ("Files/lineasClientes.txt");
	if (fileLineas.is_open()){	
		char availList[5] = "";
		fileLineas.read(availList, sizeof(availList)-1);
		
		int RRN = stoi(availList);

		if(RRN != -1) {
			int offset = 39 + (RRN - 1) * 21;
			fileLineas.seekg(offset);
			char * tempAvailList = new char [21];
			fileLineas.read (tempAvailList,21);
			
   		//Splitting into tokens
			char * pch;
			pch = strtok (tempAvailList," ");
			char * finalAvailList;
			finalAvailList = strtok (pch, "*");

			fileLineas.seekp(offset);
			fileLineas.write(buffer,temp.size());

			string strTemp;
			strcat (finalAvailList," ");
			strTemp = finalAvailList;
			fileLineas.seekp(0);
			fileLineas.write(finalAvailList, strTemp.size());
			fileLineas.close();

		}else {
		//******Revisar, inserta enter en el primer append.
			appendLinea(temp);
		}
	}else{
		cerr << "No se puede abrir el archivo" << endl;
	}

}

void appendLinea (string temp) {
	ofstream fileLineas ("Files/lineasClientes.txt", ios::app);
	if(fileLineas.is_open()) {
		const char* buffer = new char[temp.size()];
		buffer = temp.c_str();
		fileLineas.write(buffer, temp.size());
		fileLineas.close();
	} else {
		cerr << "No se puede abrir el archivo." << endl;
	}
}

void modificarLinea(int RRN, string temp){
	
	const char* buffer = new char[temp.size()];
	buffer = temp.c_str();
	
	fstream is("Files/lineasClientes.txt");
	if(is.is_open()){

		int offset = 39 + RRN * 21;
		is.seekg(offset);
		is.seekp(offset);
		is.write(buffer,temp.size());
		
		is.close();
	}else{
		cerr << "Could not open file" << endl ;
	}
}

void eliminarLinea(int RRN){
	fstream is("Files/lineasClientes.txt");
	if(is.is_open()){
		char availList[5] = "";

		is.read(availList, sizeof(availList)-1);
		
		int offset = 39 + RRN * 21;
		is.seekg(offset);
		is.seekp(offset);
		is.write("*",1);
		
		is.write(availList, 4);
		
		RRN = RRN + 1;
		string newAvailList = to_string(RRN);
		for (int i = newAvailList.size(); i < 5; ++i){
			newAvailList += " ";
		}
		
		is.seekp(0);
		is.write(newAvailList.c_str(), newAvailList.size());

		is.close();
	}else {
		cerr << "No se puede abrir el archivo." << endl ;
	}
}

int buscarLinea(int numCliente) {
	fstream is("Files/lineasClientes.txt");
	int RRN = 0, offset;
	char numClienteTemp [9];
	string s = to_string(numCliente);
	char const *charNumCliente = s.c_str(); 
	if(is.is_open()) {
		while(!is.eof()) {
			offset = 39 + RRN * 21;
			is.seekg(offset);
			//is.seekp(offset);
			is.read(numClienteTemp, 8);
			numClienteTemp[8] = '\0';
			
			if((strcmp (charNumCliente, numClienteTemp) == 0)){
				return RRN + 1;
				is.close();
				break;
			}
			RRN++;
		}

		is.close();
	} else {
		cerr << "No se puede abrir el archivo." << endl;
	}
	return 0;
}

void buscarLinea(char* idCliente) {
	fstream is("Files/lineasClientes.txt");
	int RRN = 0, offset;
	char idClienteTemp [14];
	
	if(is.is_open()) {
		while(!is.eof()) {
			offset = 39 + (RRN * 21 + 8);
			is.seekg(offset);
			is.read(idClienteTemp, 13);
			idClienteTemp[13] = '\0';
			
			if((strcmp (idCliente, idClienteTemp) == 0)){
				eliminarLinea(RRN);		
			}
			RRN++;
		}

		is.close();

	}else {
		cerr << "No se puede abrir el archivo." << endl;
	}

}

void buscarLineas(char* idCliente) {
	fstream is("Files/lineasClientes.txt");
	int RRN = 0, offset;
	char idClienteTemp [14];
	char numCliente[9];
	vector<string> lineasClientes;
	string numero;
	
	if(is.is_open()) {
		while(!is.eof()) {
			offset = 39 + (RRN * 21 + 8);
			is.seekg(offset);
			is.read(idClienteTemp, 13);
			idClienteTemp[13] = '\0';
			
			if((strcmp (idCliente, idClienteTemp) == 0)){
				is.seekp(offset - 8);
				is.read(numCliente, 8);
				numCliente[8] = '\0';	
				numero.assign(numCliente, 8);
				lineasClientes.push_back(numero);	
			}
			RRN++;
		}

		is.close();

	}else {
		cerr << "No se puede abrir el archivo." << endl;
	}
	
	buscarLlamadas(lineasClientes, idCliente);

}

void buscarLlamadas (vector<string> lineasClientes, char* idCliente) {
	
	int  offset;
	vector<string> llamadas;
	char emisor [9];
	char tempEmisor [9];
	char* call;
	string calls;
	
	
	for (int i = 0; i < lineasClientes.size(); ++i)	{
		strcpy(emisor, lineasClientes[i].c_str());
		emisor[8] = '\0';
		int RRN = 0;
		fstream is("Files/llamadas.txt");
		while(!is.eof()) {
			offset = 54 + RRN * 43;
			is.seekp(offset);
			char* call = new char[44];
			is.read(call, 44);
			calls = "";
			calls.assign(call, 44);
			memcpy (tempEmisor, call, 8);
			tempEmisor[8] = '\0';
			

			
			if(strcmp (emisor, tempEmisor) == 0) {
				llamadas.push_back(calls);
			}
			delete[] call;

			RRN ++;
		}
		if (i == lineasClientes.size()-1) 
			is.close();

	}
	
	facturacion (lineasClientes, llamadas, idCliente);

}

void facturacion (vector<string> lineasClientes, vector<string> llamadas, char* idCliente) {
	vector<double> costos;
	int cont = 0;

	do{
		double acumLineas = 0;
		char* emisor = new char[9];
		memcpy (emisor, lineasClientes[cont].c_str(), 8);
		emisor[8] = '\0';
		
		
		for (int i = 0; i < llamadas.size(); ++i) {
			char* tempEmisor = new char[9];
			
			memcpy (tempEmisor, llamadas[i].c_str(), 8);
			tempEmisor[8] = '\0';

			if (strcmp (emisor, tempEmisor) == 0) {
				
				string inicio = "", final = "", hora = "";

				for (int j = 16; j <= 29; ++j){
					inicio += llamadas[i].at(j);
					if (j >= 24)
						hora += llamadas[i].at(j);
				}

				for (int k = 30; k <= 43; ++k){
					final += llamadas[i].at(k);
				}


				unsigned long beg = stol(inicio);
				unsigned long end = stol(final);
				unsigned long hrs = stol(hora);

				unsigned int tiempoLlamada = 0;

				tiempoLlamada =  (end - beg);

				if (hrs <= 75959) {
					acumLineas += (tiempoLlamada * 0.01);
				} else if ((hrs >= 80000) && (hrs <= 155959)) {
					acumLineas += (tiempoLlamada * 0.05);
				} else if ((hrs >= 160000) && (hrs <= 235959)) {
					acumLineas += (tiempoLlamada * 0.04);
				}
				
			}

			delete[] tempEmisor;

		}
		costos.push_back(acumLineas);
		++cont;
		delete[] emisor;
	} while (cont < lineasClientes.size());


	double subtotal = 0.0, isv;
	float total;
	bool flag = true;
	cout << "*******************************************" << endl;
	cout << "FACTURA" << endl;
	cout << "Cliente: " << idCliente << endl;
	for (int g = 0; g < lineasClientes.size(); ++g) {

		cout << "Linea No. " << g + 1 << ": " << lineasClientes[g] << endl;
		
		if(llamadas.size() == 0 ) {
			cout << "No hay cargos para esta linea " << endl;
			flag = false;
		}else {
			cout << "Total linea: Lps. " << costos[g] << endl;
			subtotal += costos[g];
		}

	}
	float ruSubtotal, ruISV, ruTotal;

	if(flag) {
		cout << "-------------------------------------------" << endl;
		ruSubtotal = ceilf(subtotal * 100) / 100;
		cout << "Subtotal: Lps. " << ruSubtotal << endl;
		isv = subtotal * 0.15;
		ruISV = ceilf(isv * 100) / 100;
		cout << "ISV: Lps. " << ruISV << endl;
		total = ruSubtotal + ruISV;
		ruTotal = ceilf(total * 100) / 100; 
		cout << "Total: Lps. " << ruTotal << endl;
	}

	cout << "*******************************************" << endl;
	Factura factura;
	vector <Factura> vf;
	for (int z = 0; z < lineasClientes.size(); ++z){
		factura.id = new char[13];
		strncat(factura.id, idCliente, 13);
		factura.emisor = new char[8];
		strncat(factura.emisor, lineasClientes[z].c_str(), 8);
		factura.subtotal = ruSubtotal;
		factura.isv = ruISV;
		factura.total = ruTotal; 
		vf.push_back(factura);
	}
	
	exportFacturasJson(vf);
}

void exportFacturasJson(vector<Factura> vf){
	ofstream output;
	output.open("Files/FacturasJson.txt");
	for (int i = 0; i < vf.size(); ++i){
		string s = "";
		s+="{";
		s+="\n";
		s+="\"id\":";
		s+=vf[i].id;
		s+="\n";
		s+="\"emisor\":";
		s+=vf[i].emisor;
		s+="\n";
		s+="\"subtotal\":";
		s+=to_string(vf[i].subtotal);
		s+="\n";
		s+="\"isv\":";
		s+=to_string(vf[i].isv);
		s+="\n";
		s+="\"total\":";
		s+=to_string(vf[i].total);
		s+="\n";
		s+="}\n";
		output << s;
	}
	output.close();
}

void agregarBTreeClientes(IndiceClientes indice){
	if (arbolClientes.hasRoot){
		if (arbolClientes.nodos.size()==0){
			if (arbolClientes.root.isFull()){
				splitRootClientes(indice);
			} else {
				arbolClientes.root.keys.push_back(indice);
				sort(arbolClientes.root.keys.begin(), arbolClientes.root.keys.end());
			}
		} else {
			int pos = findpos(arbolClientes.root.keys, indice);
			bool izquierda = leftright(arbolClientes.root.keys, indice);
			int child;
			if (izquierda){
				child = arbolClientes.root.hijos[pos];
			} else {
				child = arbolClientes.root.hijos[pos+1];
			}
			int nodenum = findNodeNum(arbolClientes.nodos, child);
			while (!arbolClientes.nodos[nodenum].isLeaf()){
				pos = findpos(arbolClientes.nodos[nodenum].keys, indice);
				izquierda = leftright(arbolClientes.nodos[nodenum].keys, indice);
				if (izquierda){
					child = arbolClientes.nodos[nodenum].hijos[pos];
				} else {
					child = arbolClientes.nodos[nodenum].hijos[pos+1];
				}
				nodenum = findNodeNum(arbolClientes.nodos, child);
			}
			if (arbolClientes.nodos[nodenum].isFull()){
				if (arbolClientes.nodos[nodenum].parent == arbolClientes.root.num){
					if (arbolClientes.root.isFull()){
						splitRootClientes(indice);
					} else {
						arbolClientes.root.keys.push_back(indice);
						sort(arbolClientes.root.keys.begin(), arbolClientes.root.keys.end());
					}
				} else {
					int promotenum = findNodeNum(arbolClientes.nodos, arbolClientes.nodos[nodenum].parent);
					if (arbolClientes.nodos[promotenum].isFull()){
						splitNodeClientes(indice, nodenum, promotenum, arbolClientes.nodos[promotenum].num);
					} else {
						arbolClientes.nodos[promotenum].keys.push_back(indice);
						sort(arbolClientes.nodos[promotenum].keys.begin(), arbolClientes.nodos[promotenum].keys.end());
					}
				}
			} else {
				arbolClientes.nodos[nodenum].keys.push_back(indice);
				sort(arbolClientes.nodos[nodenum].keys.begin(), arbolClientes.nodos[nodenum].keys.end());
			}
		}
	} else {
		NodoClientes root(arbolClientes.order, arbolClientes.nodecount);
		arbolClientes.nodecount++;
		arbolClientes.root = root;
		arbolClientes.root.keys.push_back(indice);
		arbolClientes.hasRoot = true;
	}
}

void splitRootClientes(IndiceClientes indice){
	NodoClientes parent(arbolClientes.order, arbolClientes.nodecount);
	arbolClientes.nodecount++;
	NodoClientes node1(arbolClientes.order, arbolClientes.nodecount, parent.num);
	arbolClientes.nodecount++;
	NodoClientes node2(arbolClientes.order, arbolClientes.nodecount, parent.num);
	arbolClientes.nodecount++;
	arbolClientes.root.keys.push_back(indice);
	sort(arbolClientes.root.keys.begin(), arbolClientes.root.keys.end());
	int pos;
	if (arbolClientes.order%2 == 0){
		pos = (arbolClientes.order/2)-1;
	} else {
		pos = (int)(arbolClientes.order/2);
	}
	for (int i = 0; i < pos; ++i){
		node1.keys.push_back(arbolClientes.root.keys[i]);
	}
	for (int i = pos+1; i < arbolClientes.root.keys.size(); ++i){
		node2.keys.push_back(arbolClientes.root.keys[i]);
	}
	parent.keys.push_back(arbolClientes.root.keys[pos]);
	parent.hijos.push_back(node1.num);
	parent.hijos.push_back(node2.num);
	arbolClientes.root = parent;
	arbolClientes.nodos.push_back(node1);
	arbolClientes.nodos.push_back(node2);
}

void splitNodeClientes(IndiceClientes indice, int nodenum, int promotenum, int parent){
	NodoClientes node1(arbolClientes.order, arbolClientes.nodecount, parent);
	arbolClientes.nodecount++;
	NodoClientes node2(arbolClientes.order, arbolClientes.nodecount, parent);
	arbolClientes.nodecount++;
	arbolClientes.nodos[nodenum].keys.push_back(indice);
	sort(arbolClientes.nodos[nodenum].keys.begin(), arbolClientes.nodos[nodenum].keys.end());
	int pos;
	if (arbolClientes.order%2 == 0){
		pos = (arbolClientes.order/2)-1;
	} else {
		pos = (int)(arbolClientes.order/2);
	}
	for (int i = 0; i < pos; ++i){
		node1.keys.push_back(arbolClientes.nodos[nodenum].keys[i]);
	}
	for (int i = pos+1; i < arbolClientes.nodos[nodenum].keys.size(); ++i){
		node2.keys.push_back(arbolClientes.nodos[nodenum].keys[i]);
	}
	IndiceClientes index = arbolClientes.nodos[nodenum].keys[pos];
	arbolClientes.nodos.erase(arbolClientes.nodos.begin()+pos);
	for (int i = 0; i < arbolClientes.nodos[promotenum].hijos.size(); ++i){
		if (arbolClientes.nodos[promotenum].hijos[i]==arbolClientes.nodos[nodenum].num){
			arbolClientes.nodos[promotenum].hijos.erase(arbolClientes.nodos[promotenum].hijos.begin()+i);
		}
	}
	arbolClientes.nodos[promotenum].hijos.push_back(node1.num);
	arbolClientes.nodos[promotenum].hijos.push_back(node2.num);
	arbolClientes.nodos.push_back(node1);
	arbolClientes.nodos.push_back(node2);
	if (arbolClientes.nodos[promotenum].isFull()){
		int num = findNodeNum(arbolClientes.nodos, arbolClientes.nodos[promotenum].parent);
		splitNodeClientes(index, promotenum, num, arbolClientes.nodos[promotenum].parent);
	}
	arbolClientes.nodos[promotenum].keys.push_back(index);
	sort(arbolClientes.nodos[promotenum].keys.begin(), arbolClientes.nodos[promotenum].keys.end());
}

int findpos(vector<IndiceClientes> keys, IndiceClientes indice){
	int pos = -1;
	bool izquierda;
	for (int i = 0; i < keys.size(); ++i){
		if (indice<keys[i]){
			if (i==0){
				pos = i;
				izquierda = true;
				break;
			} else if (indice>keys[i-1]){
				pos = i;
				izquierda = true;
				break;
			}
		}
	}
	if (pos==-1){
		pos =  arbolClientes.root.keys.size()-1;
		izquierda = false;
	}
	return pos;
}
bool leftright(vector<IndiceClientes> keys, IndiceClientes indice){
	int pos = -1;
	bool izquierda;
	for (int i = 0; i < keys.size(); ++i){
		if (indice<keys[i]){
			pos = i;
			izquierda = true;
			break;
		}
	}
	if (pos==-1){
		pos =  arbolClientes.root.keys.size()-1;
		izquierda = false;
	}
	return izquierda;
}

int findNodeNum(vector<NodoClientes> vec, int n){
	int pos;
	for (int i = 0; i < vec.size(); ++i){
		if (vec[i].num==n){
			return i;
		}
	}
	return -1;
}