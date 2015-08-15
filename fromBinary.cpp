#include <iostream>
#include <stdio.h>
#include <fstream> 
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

int main(int argc, char const *argv[]){

	Ciudades ciudades;
	Clientes clientes;
	Lineas lineas;
	Llamadas llamadas;
	ifstream fileCiudades("BinaryFiles/dataCiudades.bin", ifstream::binary);
	cout << "CIUDADES" << endl << "ID" << "\t" << "Nombre" << endl;
	while(fileCiudades.read(reinterpret_cast<char*>(&ciudades), sizeof(ciudades))){
		cout << ciudades << endl;
	}
	fileCiudades.close();

	ifstream fileClientes("BinaryFiles/dataClientes.bin", ifstream::binary);
	cout << "CLIENTES" << endl << "ID" << setw(30) << "Nombre" <<  setw(30)  << "Genero" << setw(13) << "Ciudad" << endl;
	while(fileClientes.read(reinterpret_cast<char*>(&clientes), sizeof(clientes))){
		cout << clientes << endl;
	}
	fileClientes.close();

	ifstream fileLineas("BinaryFiles/dataLineas.bin", ifstream::binary);
	cout << "LINEAS" << endl << "Numero" << "\t" << "ID Cliente" << endl;
	while(fileLineas.read(reinterpret_cast<char*>(&lineas), sizeof(lineas))){
		cout << lineas << endl;
	}
	fileLineas.close();

	ifstream fileLlamadas("BinaryFiles/dataLlamadas.bin", ifstream::binary);
	cout << "LLAMADAS" << endl << "Numero" << "\t" << "Inicio" << "\t" << "Final" << "\t" << "Destino" << endl;
	while(fileLlamadas.read(reinterpret_cast<char*>(&llamadas), sizeof(llamadas))){
		cout << llamadas << endl;
	}
	fileLlamadas.close();
	return 0;
}