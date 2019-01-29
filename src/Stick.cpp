#include "../include/Stick.h"
#include "../include/Drawable.h"

Stick::Stick(const std::string texturepath) {
	texture = Drawable::LoadTexture(texturepath);

	srcRect.w = 390;
	srcRect.h = 12;
	srcRect.x = 0;
	srcRect.y = 0;

	point = { -30, 0 };
	angle = 180;

	destRect.w = srcRect.w;
	destRect.h = srcRect.h;
	destRect.x = whiteBall_destRect.x - point.x
		+ whiteBall_destRect.w / 2 + 1;
	if (angle > 90) {
		destRect.x += destRect.h * (180 - angle) / 180;
		std::cout << "2" << std::endl;
	}
	else if (abs(angle) <= 90) {
		destRect.x += destRect.h * angle / 180;
		std::cout << "1" << std::endl;
	}
	else if (angle <= -90) {
		destRect.x -= destRect.h * (180 + angle) / 180;
		std::cout << "3" << std::endl;
	}
	destRect.y = whiteBall_destRect.y - point.y
		+ whiteBall_destRect.h / 2 + 1
		- destRect.h / 2
		+ abs(destRect.h * angle / 180);
}

void Stick::setWhiteBall_destRect(SDL_Rect whiteBall_destRect) {
	this->whiteBall_destRect = whiteBall_destRect;
}

double Stick::Angle(int x1, int y1, int x2, int y2) {
	return atan2(y2 - y1, x2 - x1) * (180 / M_PI);
}

/*double Stick::AngleRad(int x1, int y1, int x2, int y2) {
	return atan2(y2 - y1, x2 - x1);
}*/

void Stick::Update(int mouse_x, int mouse_y) {
	angle = Angle(destRect.x, destRect.y, mouse_x, mouse_y);

	destRect.x = whiteBall_destRect.x - point.x
		+ whiteBall_destRect.w / 2 + 1;
	if (angle > 90) {
		destRect.x += destRect.h * (180 - angle) / 180;
	}
	else if (abs(angle) <= 90) {
		destRect.x += destRect.h * angle / 180;
	}
	else if (angle <= -90) {
		destRect.x -= destRect.h * (180 + angle) / 180;
	}
	destRect.y = whiteBall_destRect.y - point.y
		+ whiteBall_destRect.h / 2 + 1
		- destRect.h / 2
		+ abs(destRect.h * angle / 180);
}

void Stick::RenderEx() {
	SDL_RenderCopyEx(Game::renderer, texture, &srcRect, &destRect, 
		angle, &point, SDL_FLIP_NONE);
}

void Stick::Render() {
	SDL_RenderCopy(Game::renderer, texture, &srcRect, &destRect);
}

SDL_Rect Stick::get() {
	return destRect;
}