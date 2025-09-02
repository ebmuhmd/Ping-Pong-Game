#include<iostream>
#include<raylib.h>
using namespace std;

int PlayerScore = 0;
int CpuScore = 0;

//Colors
Color Green = Color{ 38,185,154,255 };
Color Dark_Green = Color{ 20,160,133,255 };
Color Light_Green = Color{ 129,204,184,255 };
Color Yellow = Color{ 243,213,91,255 };


class Ball
{
public:
	float x, y;
	int speed_x,speed_y;
	int radius;
	void Draw()
	{
		DrawCircle(x, y, radius,Yellow);
	}

	void RsetBall()
	{
		x = GetScreenWidth() / 2;
		y = GetScreenHeight() / 2;

		int SpeedChoices[2] = { -1,1 };
		speed_x *= SpeedChoices[GetRandomValue(1, 0)];
		speed_y *= SpeedChoices[GetRandomValue(1, 0)];
	}

	void update()
	{
		x += speed_x;
		y += speed_y;



		if (x + radius >= GetScreenWidth())
		{
			CpuScore++;
			RsetBall();

		}
		if(x-radius<=0)
		{
				PlayerScore++;
				RsetBall();
		}

		if (y + radius >= GetScreenHeight() || y - radius <= 0)
		{
			speed_y *= -1;
		}
	}

};

class Player
{
protected:
	void Movement_Limits()
	{
		if (y+height >=GetScreenHeight())
		{
			y = GetScreenHeight()-height;
		}

		if (y <= 0)
		{
			y = 0;
		}
	}

	public:
	float x, y, width, height;
	int speed;

	void draw()
	{
		DrawRectangleRounded(Rectangle{ x,y,width,height }, 0.7, 0, WHITE);
		
	}

	void Update()
	{
		if (IsKeyDown(KEY_UP))
		{
			y -= speed;
		}
		if (IsKeyDown(KEY_DOWN))
		{
			y += speed;
		}

		Movement_Limits();
	}

};

class CPU  : public Player
{
public:
	void Update(int ball_y) {
		if (y+height/2 < ball_y)
		{
			y =	y+speed;
		}
		if (y + height / 2 > ball_y)
		{
			y -= speed;
		}

	}

};




Ball ball;
Player player;
CPU cpu;

int main()
{
	cout << "Starting the Game ...";
	const int Screen_width = 1280;
	const int Screen_height = 720;
	InitWindow(Screen_width,Screen_height,"Ping Pong Game!");
	SetTargetFPS(60);

	//Ball Info
	ball.x = Screen_width / 2;
	ball.y = Screen_height / 2;
	ball.radius = 20;
	ball.speed_x = 7;
	ball.speed_y = 7;


	//Player Info
	player.height = 120;
	player.width = 25;
	player.x = Screen_width - 35;
	player.y = Screen_height / 2 - 60;
	player.speed = 10;

	//Cpu Info
	cpu.height = 120;
	cpu.width = 25;
	cpu.x = 10;
	cpu.y = Screen_height / 2 - 60;
	cpu.speed = 7;



	while (WindowShouldClose() == false)
	{
		BeginDrawing();


		//Colors
		ClearBackground(Green);
		DrawRectangle(Screen_width / 2, 0, Screen_width / 2, Screen_height, Dark_Green);
		DrawCircle(Screen_width / 2, Screen_height / 2, 150, Light_Green);


		//Collisions
		if (CheckCollisionCircleRec(Vector2{ ball.x,ball.y }, ball.radius, Rectangle{ player.x,player.y,player.width,player.height }))
		{
			ball.speed_x *= -1;
		}
		if (CheckCollisionCircleRec(Vector2{ ball.x,ball.y }, ball.radius, Rectangle{ cpu.x,cpu.y,cpu.width,cpu.height }))
		{
			ball.speed_x *= -1;
		}

		//Updates
		ball.update();
		player.Update();
		cpu.Update(ball.y);

		//Draw
		DrawLine(Screen_width / 2, 0, Screen_width / 2, Screen_height, WHITE);
		ball.Draw();
		player.draw();
		cpu.draw();

		//Scores
		DrawText(TextFormat("%i", CpuScore), Screen_width / 4, 40, 80, WHITE);
		DrawText(TextFormat("%i", PlayerScore), 3 * Screen_width / 4, 40, 80, WHITE);

		

		EndDrawing();
	}


	CloseWindow();
	return 0;
}