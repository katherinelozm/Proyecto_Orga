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
	//output2 << clientes.idCliente << "\t" << clientes.nombreCliente << "\t\t  " << clientes.genero << "\t" << clientes.idCiudad;
	output2 << clientes.idCliente << setw(25) << clientes.nombreCliente << setw(20) << clientes.genero << setw(13) << clientes.idCiudad;
	return output2;  
}

int main(int argc, char const *argv[]){

	Ciudades ciudades;
	Clientes clientes;
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

	return 0;
}