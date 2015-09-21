#include <iostream>
#include <stdio.h>
#include <fstream> 
#include <string.h> 
#include <string>
#include <vector>
#include <stdlib.h>
#include <iomanip>
#include <algorithm>

using namespace std;

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
};

struct IndiceLineas{
	int llave;
	int rrn; 
	bool operator<( const IndiceLineas& indice ) const { 
		return llave < indice.llave;
	}
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

int main(int argc, char const *argv[]){
	//leerTodos();
	int op1, op2, op3, RRN;

	do {
		cout << "1. Clientes \n2. Lineas\n3. Salir" << endl;
		cin >> op1;
		if (op1 == 1) {
			do {
				cout << "Opciones Clientes\n1. Agregar\n2. Modificar\n3. Eliminar\n4. Buscar\n5. Salir" << endl;
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
					int found = buscarCliente(id);
					if (found != 0) {
						cout << "RRN usuario: " << found << endl;
					} else {
						cout << "Usuario no encontrado." << endl;
					}

				}
			}while (op2 <= 4);


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
	buscarLinea(idCliente);
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
		return 0;
	}else {
		cerr << "No se puede abrir el archivo." << endl;
	}
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
			is.seekp(offset);
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
		return 0;
	}else {
		cerr << "No se puede abrir el archivo." << endl;
	}

}



void buscarLinea(char* idCliente) {
	fstream is("Files/lineasClientes.txt");
	int RRN = 0, offset;
	char idClienteTemp [9];
	
	if(is.is_open()) {
		while(!is.eof()) {
			offset = 39 + (RRN * 21 + 8);
			is.seekg(offset);
			is.seekp(offset);
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
