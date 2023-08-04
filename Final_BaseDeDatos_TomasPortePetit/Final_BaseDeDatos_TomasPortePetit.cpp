#include <mysql.h>
#include <iostream>
#include <string>

MYSQL* connection;
MYSQL_ROW row;
MYSQL_RES* res;


using namespace std;

bool CheckServerConection();
void CheckData();
void InsertData();
void UpdateBalance();
void DeleteUser();

int totalUsers = 0;

int main()
{

	if (CheckServerConection())
	{
		bool isRunning = true;
		int input = 0;

		do
		{
			system("cls");
			switch (input)
			{
			case 0:
			{
				cout << "|----------------------------------|" << endl;
				cout << "|               SUBE               |" << endl;
				cout << "|----------------------------------|" << endl;
				cout << "|                                  |" << endl;
				cout << "|         1. Leer Datos            |" << endl;
				cout << "|         2. Agregar Datos         |" << endl;
				cout << "|         3. Actualizar Datos      |" << endl;
				cout << "|         4. Eliminar Usuarios     |" << endl;
				cout << "|         5. Salir                 |" << endl;
				cout << "|                                  |" << endl;
				cout << "|----------------------------------|" << endl;
				cin >> input;
				break;
			}

			case 1:
			{
				CheckData();
				input = 0;
				break;
			}

			case 2:
			{
				InsertData();
				input = 0;
				break;
			}

			case 3:
			{
				UpdateBalance();
				input = 0;
				break;
			}

			case 4:
			{
				DeleteUser();
				input = 0;
				break;
			}

			case 5:
			{
				isRunning = false;
			}
			default:
				break;
			}

		} while (isRunning);
	}
	else
	{
		return 0;
	}

}

bool CheckServerConection()
{
	connection = mysql_init(0);
	connection = mysql_real_connect(connection, "localhost", "root", "SakuraChan115", "Sube", 3306, NULL, 0);

	if (!connection)
	{
		std::cout << "Not working server..." << std::endl;
		return false;
	}
	else
	{
		std::cout << "working server..." << std::endl;
		return true;
	}


}

void CheckData()
{
#pragma region var
	string users = "SELECT * FROM USERS";
	string actualDestiny = "SELECT * FROM actualDestiny";
	string lastTransportUsed = "SELECT * FROM lastTransportUsed";

	const char* query1 = users.c_str();
	const char* query2 = actualDestiny.c_str();
	const char* query3 = lastTransportUsed.c_str();
#pragma endregion var


	int state = 0;

	state = mysql_query(connection, query1);

	cout << "|----------------------------------|" << endl;
	cout << "|               User               |" << endl;
	cout << "|----------------------------------|" << endl;

	if (!state)
	{
		res = mysql_store_result(connection);
		

		while (row = mysql_fetch_row(res))
		{
			cout << "| ID:"<< row[0]<< " DNI: " << row[1]<< " NAME:" << row[2]<< " BALANCE:" << row[3] << endl;
		}
	}

	state = mysql_query(connection, query2);

	cout << "|----------------------------------|" << endl;
	cout << "|             Destino              |" << endl;
	cout << "| 1. 9 de julio    2. Constitucion |" << endl;
	cout << "| 3. Plaza Italia  4. Plaza de Mayo|" << endl;
	cout << "|----------------------------------|" << endl;

	if (!state)
	{
		res = mysql_store_result(connection);


		while (row = mysql_fetch_row(res))
		{
			cout << "| Usuario: " << row[0] << " Destino: " << row[1] << endl;
		}
	}

	state = mysql_query(connection, query3);

	cout << "|----------------------------------|" << endl;
	cout << "|    Ultimo transporte utilizado   |" << endl;
	cout << "|  1. Tren  2. Colectivo  3. Subte |" << endl;
	cout << "|----------------------------------|" << endl;

	if (!state)
	{
		res = mysql_store_result(connection);


		while (row = mysql_fetch_row(res))
		{
			cout << "| Usuario: " << row[0] << " Transporte: " << row[1] << endl;
		}
	}


	system("pause > null");


}

void InsertData()
{
	int dni = 0;
	string name = "";
	int balance = 0;
	int destiny = 0;
	int transport = 0;

	int state = 0;
	totalUsers++;

#pragma region input
	cout << "|----------------------------------|" << endl;
	cout << "|          Insertar Datos          |" << endl;
	cout << "|----------------------------------|" << endl;
	cout << "Ingrese el DNI: ";
	cin >> dni;
	cout << "Ingrese el Saldo: ";
	cin >> balance;
	cout << "Ingrese el Nombre: ";
	cin >> name;
	cout << "|----------------------------------|" << endl;
	cout << "|             Destino              |" << endl;
	cout << "| 1. 9 de julio    2. Constitucion |" << endl;
	cout << "| 3. Plaza Italia  4. Plaza de Mayo|" << endl;
	cout << "|----------------------------------|" << endl;
	cout << "Ingrese el Destino: ";
	cin >> destiny;
	cout << "|----------------------------------|" << endl;
	cout << "|    Ultimo transporte utilizado   |" << endl;
	cout << "|  1. Tren  2. Colectivo  3. Subte |" << endl;
	cout << "|----------------------------------|" << endl;
	cin >> transport;
#pragma endregion input


	string user = "INSERT INTO USERS(dni, userName, balance) VALUE('" + to_string(dni) + "', '" + name + "', '" + to_string(balance) + "')";
	state = mysql_query(connection, user.c_str());


	string users = "SELECT * FROM USERS";
	state = mysql_query(connection, users.c_str());

	if (!state)
	{
		res = mysql_store_result(connection);

		while (row = mysql_fetch_row(res))
		{
			totalUsers = stoi((string)row[0]);
		}
	}


	string destinyValue = "INSERT INTO actualDestiny(IdUser, IdDestiny) VALUE('" + to_string(totalUsers) + "', '" + to_string(destiny) + "')";
	string transportValue = "INSERT INTO lastTransportUsed(IdUser, IdTransport) VALUE('" + to_string(totalUsers) + "', '" + to_string(transport) + "')";

	state = mysql_query(connection, destinyValue.c_str());
	state = mysql_query(connection, transportValue.c_str());


	if (!state)
	{
		cout << "Guardado con exito!" << endl;
		state = 0;
	}
	else
	{
		cout << "Error al guardar :(" << endl;
	}
	system("pause");
}

void UpdateBalance()
{
	string updateBalance;

	int dni;
	int newBalance;

	cout << "|----------------------------------|" << endl;
	cout << "|         actualizar Saldo         |" << endl;
	cout << "|----------------------------------|" << endl;
	cout << "Ingrese el dni: ";
	cin >> dni;
	cout << "Ingrese el neuvo saldo: ";
	cin >> newBalance;


	updateBalance = "UPDATE USERS SET balance = " + to_string(newBalance) + " WHERE dni = " + to_string(dni);

	const char* query = updateBalance.c_str();

	int state = 0;

	state = mysql_query(connection, query);

	if (!state)
	{
		cout << "Guardado con exito!" << endl;
		state = 0;
	}
	else
	{
		cout << "Error al guardar :(" << endl;
	}
	system("pause");

}

void DeleteUser()
{
	int dni = 0;
	char input;

	int state = 0;

	int id = 0;

	cout << "|----------------------------------|" << endl;
	cout << "|         Eliminar Usuario         |" << endl;
	cout << "|----------------------------------|" << endl;
	cout << "Ingrese el DNI: ";
	cin >> dni;
	cout << "Desea eliminar este usuario? Y|N : ";
	cin >> input;

	if (input != 'y' && input != 'Y')
	{
		return;
	}
	
	string users = "SELECT * FROM USERS";
	state = mysql_query(connection, users.c_str());

	if (!state)
	{
		res = mysql_store_result(connection);

		while (row = mysql_fetch_row(res))
		{
			if (stoi((string)row[1]) == dni)
			{
				id = stoi((string)row[0]);
			}

		}
	}

	string userData = "DELETE FROM USERS WHERE dni = " + to_string(dni);
	string destinyData = "DELETE FROM actualDestiny WHERE IdUser = " + to_string(id);
	string transportData = "DELETE FROM lastTransportUsed WHERE IdUser = " + to_string(id);

	state = mysql_query(connection, userData.c_str());
	state = mysql_query(connection, destinyData.c_str());
	state = mysql_query(connection, transportData.c_str());

	if (!state)
	{
		cout << "Eliminado con exito!" << endl;
		state = 0;
	}
	else
	{
		cout << "Error al eliminar :(" << endl;
	}
	system("pause");
}