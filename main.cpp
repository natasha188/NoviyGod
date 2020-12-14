#include <iostream>
#include <stdexcept>
#include <SDL2/SDL.h>
#include "GLDemoWindow.h"

int main (int, char **)
{
	SDL_Init(SDL_INIT_EVERYTHING);//инициализация

	try{
		GLDemoWindow w;

		w.main_loop();
	}catch (const std::exception &e){
		std::cerr <<"Ошибка! "<< std::endl<<e.what()<<std::endl;
		return 1;
	}catch (...){
		std::cerr <<"Произошла неизвестная ошибка!"<< std::endl;
		return 1;
	}

	return 0;
}


