#include "stdafx.h"

#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include <iostream>
#include <thread>

typedef void(WINAPI *DLL_LIB_FUNC)(); // ѕеред тем, как использовать функции библиотеки, необходимо получить их
                               // адрес. ƒл€ этого сначала следует воспользоватьс€ директивой typedef дл€
                               // определени€ типа указател€ на функцию
                               // тип DLL_LIB_FUNC будет объ€вл€ть указатель на функцию типа void  
                               // без параметров 

HINSTANCE dll_library;  // это дескриптор модул€ dll, который уникален в пределах процесса       

//-----------------------объ€вление функций-------------------------------
void read(); 
void write(); 
//-----------------------конец объ€влени€ функций-------------------------

int main(int args, char* argv[]) {

	dll_library = LoadLibrary("fileio.dll"); // загружаем библиотеку 

	if (dll_library == nullptr) { // если не удалось загрузить, ф-и€ возвращает nullptr
		std::cout << "Cannot load dll library!" << std::endl; // выводим сообщение о том, что библиотека не загружена
		_getch(); // ожидаем нажати€ на любую клавишу
		exit(0); // и выходим из программы
	} else {
		std::cout << "Dll library has been loaded." << std::endl; // иначе выводим сообщение, что быблиотека была загружена
	}

	std::cout << "Performing reading and writing..." << std::endl;


	std::thread reader(read); // создаем поток, который будет исполн€ть функцию read
	std::thread writer(write); // создаем поток, который будет исполн€ть функцию write 

	reader.join(); // ожидаем завершени€ потока reader
	writer.join(); // ожидаем завершени€ потока writer

	std::cout << "Reader and writer finished their tasks." << std::endl; // выводим сообщение о том, что потоки отработали

	FreeLibrary(dll_library); // выгружаем dll
	_getch(); // ожидаем нажати€ на любую клавишу
	return 0; // завершаем работу
}

void read() {
	// загружаем из dll функцию с именем read
	DLL_LIB_FUNC dll_read = (DLL_LIB_FUNC)GetProcAddress(dll_library, "read");
	dll_read(); // вызываем данную ф-ию
	ExitThread(0); // заканчиваем работу потока с кодом 0
}

void write() {
	// загружаем из dll функцию с именем write
	DLL_LIB_FUNC dll_write = (DLL_LIB_FUNC)GetProcAddress(dll_library, "write");
	dll_write(); // вызываем данную ф-ию
	ExitThread(0); // заканчиваем работу потока с кодом 0
}