#include <iostream>
#include <stdio.h>
#include <fstream> 
#include <string.h> 
#include <string>
#include <vector>
#include <stdlib.h>
#include <iomanip>

using namespace std;

struct Ciudades{
	int idCiudad;
	char nombreCiudad[40];
};

struct Clientes{
	char idCliente[17];
	char nombreCliente[40];
	char genero;
	int idCiudad;
};

struct Lineas{
	int numero;
	char id[17];
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

int main(int argc, char const *argv[]){
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

	/*Lee el contenido de ambos archivos de texto y los ingresa en un vector de tipo string*/

	if (fileCiudades.is_open()){
		while (fileCiudades.good()){
			getline(fileCiudades,lineaCiudades);
			if (!lineaCiudades.empty())
				sv1.push_back(lineaCiudades);
			}
		fileCiudades.close();
	}
	

	if (fileClientes.is_open()){
		while (fileClientes.good()){
			getline(fileClientes,lineaClientes);
			if (!lineaClientes.empty())
				sv2.push_back(lineaClientes);
		}
		fileClientes.close();
	}

	if (fileLineas.is_open()){
		while (fileLineas.good()){
			getline(fileLineas,lineaLineas);
			if (!lineaLineas.empty())
				sv3.push_back(lineaLineas);
		}
		fileLineas.close();
	}

	if (fileLlamadas.is_open()){
		while (fileLlamadas.good()){
			getline(fileLlamadas,lineaLlamadas);
			if (!lineaLlamadas.empty())
				sv4.push_back(lineaLlamadas);
		}
		fileLlamadas.close();
	}

	char * st1; 
	char * st2;
	char * st3;
	char * st4;
	vector<string> temp1;
	vector<string> temp2;
	vector<string> temp3;
	vector<string> temp4;

	/*
		Separa en tokes cada registro y los ingresa en un vector de tipo string
		char * st1 = string tokenizer ciudades
		char * st2 = string tokenizer clientes
		char * st3 = string tokenizer lineas
		char * st4 = string tokenizer llamadas
		Vector temp1 = tokens registros ciudades
		Vector temp2 = tokens registros clientes 
		Vector temp3 = tokens registros lineas 
		Vector temp4 = tokens registros llamadas 
	*/

	for (int i = 0; i < sv1.size(); ++i) {
		char* c1 = const_cast<char*>(sv1[i].c_str());
		st1 = strtok(c1,",.");
		
		while (st1 != NULL) {
			temp1.push_back(st1);
			st1 = strtok (NULL, ",.");
		}	
	}

	for (int i = 0; i < sv2.size(); ++i) {
		char* c2 = const_cast<char*>(sv2[i].c_str());
		st2 = strtok(c2,",.");
		
		while (st2 != NULL) {
			temp2.push_back(st2);
			st2 = strtok (NULL, ",.");
		}
	}
	
	for (int i = 0; i < sv3.size(); ++i) {
		char* c3 = const_cast<char*>(sv3[i].c_str());
		st3 = strtok(c3,",.");
		
		while (st3 != NULL) {
			temp3.push_back(st3);
			st3 = strtok (NULL, ",.");
		}
	}

	for (int i = 0; i < sv4.size(); ++i) {
		char* c4 = const_cast<char*>(sv4[i].c_str());
		st4 = strtok(c4,",.");
		
		while (st4 != NULL) {
			temp4.push_back(st4);
			st4 = strtok (NULL, ",.");
		}
	}

	vector<Ciudades> vectorCiudades;
	vector<Clientes> vectorClientes;
	vector<Lineas> vectorLineas;
	vector<Llamadas> vectorLlamadas;
	Ciudades ciudades;
	Clientes clientes;
	Lineas lineas;
	Llamadas llamadas;

	/*
		A partir de los vectores temp1, temp2, temp3 y temp4 se llenan los vectores de tipo ciudades, clientes, lineas y llamadas
		Se castean las strings en temp1, temp2, temp3 y temp4 a los respectivos tipos de variables del Struct para
		ciudades, clientes, lineas y llamadas.
		**memset libera la memoria de char[]
	*/

	for (int i = 0; i < temp1.size(); i+=2){
		int tempId; 
		tempId = atoi(temp1[i].c_str());
		ciudades.idCiudad = tempId;
		memcpy(ciudades.nombreCiudad,temp1[i+1].c_str(),temp1[i+1].size());
		vectorCiudades.push_back(ciudades);
		memset(ciudades.nombreCiudad, 0, 40);
	}

	for (int i = 0; i < temp2.size(); i+=4){
		memcpy(clientes.idCliente,temp2[i].c_str(),temp2[i].size());
		memcpy(clientes.nombreCliente,temp2[i+1].c_str(),temp2[i+1].size());
		char tempGenero = temp2[i+2].at(0);
		clientes.genero = tempGenero;
		int tempId; 
		tempId = atoi(temp2[i+3].c_str());
		clientes.idCiudad = tempId;
		vectorClientes.push_back(clientes);
		memset(clientes.idCliente, 0, 17);
		memset(clientes.nombreCliente, 0, 40);
	}

	for (int i = 0; i < temp3.size(); i+=2){
		int tempNum; 
		tempNum = atoi(temp3[i].c_str());
		lineas.numero = tempNum;
		memcpy(lineas.id,temp3[i+1].c_str(),temp3[i+1].size());
		vectorLineas.push_back(lineas);
		memset(lineas.id, 0, 17);
	}

	for (int i = 0; i < temp4.size(); i+=4){
		int tempNumero, tempDestino; 
		long tempInicio, tempFinal;
		tempNumero = atoi(temp4[i].c_str());
		tempInicio = atol(temp4[i+1].c_str());
		tempFinal = atol(temp4[i+2].c_str());
		tempDestino = atoi(temp4[i+3].c_str());
		llamadas.numero = tempNumero;
		llamadas.inicio = tempInicio;
		llamadas.final = tempFinal;
		llamadas.destino = tempDestino;
		vectorLlamadas.push_back(llamadas);
	}

	indexar(vectorClientes ,vectorLineas);
	return 0;
}

void indexar(vector<Clientes> vectorClientes, vector<Lineas> vectorLineas){
	vector<IndiceClientes> indices1;
	vector<IndiceLineas> indices2;

	for (int i = 0; i < vectorClientes.size(); ++i){
		IndiceClientes indice;
		strcpy(indice.llave, vectorClientes[i].idCliente);
		indice.rrn = i+1;
		indices1.push_back(indice);
	}
	

	for (int i = 0; i < vectorLineas.size(); ++i){
		IndiceLineas indice;
		indice.llave = vectorLineas[i].numero;
		indice.rrn = i+1;
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
			outputClientes << index << "\n";
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
			outputLineas << index << "\n";
		}
    } else {
       	cerr << "No se pueden escribir los datos" << endl;
    }
    outputLineas.close();
}