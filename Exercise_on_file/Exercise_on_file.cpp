// Exercise_on_file.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.

#pragma once
#include <iostream>
#include "File.h"
#include <windows.h>
#include <locale>
#include <string>



int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    File f("Roman.txt");
    f.browseDictionary();
}

