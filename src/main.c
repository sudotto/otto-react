#include <stdio.h>
#include <stdlib.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3_image/SDL_image.h>

#include "otto-game.h"

int amplitude(){
	FILE *fp = popen("bash test.sh", "r");
	char buf[7];
	int amp;
	if(fgets(buf, 7, fp) != NULL){
		amp = atoi(buf);
	}
	pclose(fp);
	return amp;
}

int main(){
	Game game = new_game("audio reactive character program ARC_P", 900, 600);
	Img open = new_img(game.rend, "assets/open.png", 0);
	Img close = new_img(game.rend, "assets/close.png", 0);
	while(game.running){
		game.frame_start = SDL_GetTicks();
		clear_game(&game, 0, 255, 0);

		while(get_game_events(&game)){
			switch(game.event.type){
				case SDL_EVENT_QUIT:
					game.running = false;
					break;
			}
		}

		if(amplitude() > 10000){
			render_img(game.rend, &open, 600 - (900/2), 0, 600, 600);
		} else {
			render_img(game.rend, &close, 600 - (900/2), 0, 600, 600);
		}

		render_game_cursor(&game, 32, 32);
		update_game(&game);
		cap_game_framerate(&game, 60);
	}
	destroy_game(&game);
}
