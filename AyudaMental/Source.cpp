#include <Windows.h>
#include <psapi.h>
#include <tlhelp32.h>
#include <iostream>
#include <vector>
#include <string>

void closeLoL(const int&);

std::vector<std::string> const processLOL = {
	"RiotClientServices.exe",
	"RiotClientCrashHandler.exe",
    "LeagueClient.exe",
    "LeagueCrashHandler.exe",
	"LeagueClientUx.exe",
    "LeagueClientUxRender.exe",
	"LeagueClientUxRender.exe",
};

//: detectar si el lol se ha iniciado para empezar la cuenta regresiva 
//: solo falta poner el programa en los registros dearranqe de windows
//: despues de eliminar el proceso se esconde el programa de windows 


int main() {
	//FreeConsole();
	while (true){ closeLoL(60); }
	std::cin.get();
}

// Se lo instale a un amigo que queria jugar solo una partida lol nada mas
void closeLoL(const int &contSe) {
	// campturamos todos los procesos
	HANDLE createProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS | TH32CS_SNAPMODULE, 0);
	int cont = 0;
	bool oned = true;
	if (createProcess != NULL) {
		// describimos una entrada a la lista procesos 
		PROCESSENTRY32 process = { sizeof(PROCESSENTRY32) };
		Process32First(createProcess, &process);

		do {
			HANDLE new_hProcess = OpenProcess(PROCESS_ALL_ACCESS, TRUE, process.th32ProcessID);
			if (new_hProcess != NULL) {
				
				for (auto it : processLOL) {
					if (process.szExeFile == it) {
						if (oned) {
							cont = contSe;
							while (cont != 0) {
								Sleep(1000);
								cont--;
							}
							oned = false;
						}

						DWORD info_salida = 0;
						BOOL salida = GetExitCodeProcess(new_hProcess, &info_salida);
						TerminateProcess(new_hProcess, salida);
					}
				}
				CloseHandle(new_hProcess);
			}
		} while (Process32Next(createProcess, &process));
		CloseHandle(createProcess);
	}
	else {
		//std::cerr << "No se enconro el proceso league og legends" << std::endl;
	}
}




