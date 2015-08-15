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



int main(int argc, char const *argv[]){
	string lineaCiudades;
	string lineaClientes;
	vector<string>sv1;
	vector<string>sv2;
	
	ifstream fileCiudades("Files/ciudades.txt", ifstream::in);
	ifstream fileClientes("Files/dataClientes.txt", ifstream::in);

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

	char * st1; 
	char * st2;
	vector<string> temp1;
	vector<string> temp2;
	
	/*
		Separa en tokes cada registro y los ingresa en un vector de tipo string
		char * st1 = string tokenizer ciudades
		char * st2 = string tokenizer clientes
		Vector temp1 = tokens registros ciudades
		Vector temp2 = tokens registros clientes 
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
	
	vector<Ciudades> vectorCiudades;
	vector<Clientes> vectorClientes;
	Ciudades ciudades;
	Clientes clientes;

	/*
		A partir de los vectores temp1 y temp2 se llenan los vectores de tipo ciudades y clientes
		Se castean las strings en temp1 y temp2 a los respectivos tipos de variables del Struct para
		ciudades y clientes.
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

	/* Se guardan los archivos binarios */

	ofstream bfCiudades("BinaryFiles/dataCiudades.bin", ofstream::binary);
	ofstream bfClientes("BinaryFiles/dataClientes.bin", ofstream::binary);

	for (int i = 0; i < vectorCiudades.size(); ++i) {
		bfCiudades.write(reinterpret_cast<const char*> (&vectorCiudades[i]), sizeof(ciudades));
	}
	bfCiudades.close();

	for (int i = 0; i < vectorClientes.size(); ++i) {
		bfClientes.write(reinterpret_cast<const char*> (&vectorClientes[i]), sizeof(clientes));
	}
	bfClientes.close();

	return 0;
}