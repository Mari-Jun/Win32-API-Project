#pragma once
class Enemy;
class Player;
class File;
class Map_Dungeon;

void Attack_Enemy_Action(Enemy& enemy, Map_Dungeon& map_d, const Player& player, const int& index, const File& file);