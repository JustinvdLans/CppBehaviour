// BehaviourLes.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <time.h>
#include <vector>
#include <vector>
#include <string>
#include "Character.h"
#include "Behaviour.h"
#include "ChaseBehaviour.h"
#include "EvadeBehaviour.h"

double delay = 0.5;
double previousFrameTime = 0.0;
int maxWidth = 100;
std::vector<std::string> scene;
bool running = true;
int main()
{
	//Characters aanmaken
	Character player1(Character::AvailableBehaviours::IDLE, 10, "E");
	Character player2(Character::AvailableBehaviours::IDLE, 11, "F");
	Character enemy1(Character::AvailableBehaviours::CHASE, 40, "B", &player1);
	Character enemy2(Character::AvailableBehaviours::CHASE, 41, "C", &player2);

	//Game mechanics activeren
	player1.SetTarget(&enemy1);
	player1.Setbehaviour(Character::AvailableBehaviours::EVADE);

	player2.SetTarget(&enemy2);
	player2.Setbehaviour(Character::AvailableBehaviours::EVADE);

	//alle spelers in een lijst
	std::vector<Character*> characters{ &player1, &player2, &enemy1, &enemy2 };

	//een scene van 100 breed aanmaken
	scene.resize(50);

	//deze scene vullen met _
	
	previousFrameTime = clock();
	//de game zelf
	while (running) {
		//een eigen timer
		if ((clock() - previousFrameTime) / CLOCKS_PER_SEC >= delay) {
			std::fill(scene.begin(), scene.end(), "x");
			system("cls");
			//std::cout << "[" << clock() << "] updating" << std::endl;
			for (Character* aCharacter : characters) {
				scene.at(aCharacter->Update()) = aCharacter->GetIcon();
			}
			for (std::string s : scene) {
				std::cout << s;
			}


			previousFrameTime = clock();
		}
		if (characters.at(0)->GetPosition() == characters.at(1)->GetPosition()) {
			std::cout << "\nGAME OVER\nPress ENTER to quit" << std::endl;
			running = false;
		}
	}
	std::cin.get();
}


