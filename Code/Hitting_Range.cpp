#include <Windows.h>
#include <tchar.h>
#include <math.h>
#include "Source.h"
#include "Hitting_Range.h"

Hitting_Range::~Hitting_Range() {}

const int& Hitting_Range::Get_Owner() const {
	return owner;
}

const int& Hitting_Range::Get_Delay() const {
	return delay;
}

const double& Hitting_Range::Get_Attack_Multiple() const {
	return attack_multiple;
}

const bool& Hitting_Range::Is_Move() const {
	return move;
}

const int& Hitting_Range::Get_Direction() const {
	return direction;
}

const bool& Hitting_Range::Is_Guide() const {
	return guide;
}

const POINT& Hitting_Range::Get_Speed() const {
	return speed;
}

const BITMAP& Hitting_Range::Get_Range_Bitmap_Size() const {
	return range_bitmap_size;
}

const HBITMAP& Hitting_Range::Get_Range_Bitmap(const int& direction) const {
	return range_bitmap[direction];
}

void Hitting_Range::Set_Owner(const int& owner) {
	this->owner = owner;
}

void Hitting_Range::Set_Delay(const int& delay) {
	this->delay = delay;
}

void Hitting_Range::Set_Attack_Multiple(const double& attack_multiple) {
	this->attack_multiple = attack_multiple;
}

void Hitting_Range::Set_Move(const bool& move) {
	this->move = move;
}

void Hitting_Range::Set_Direction(const int& direction) {
	this->direction = direction;
}

void Hitting_Range::Set_Guide(const bool& guide) {
	this->guide = guide;
}

void Hitting_Range::Set_Speed(const POINT& speed) {
	this->speed = speed;
}

void Hitting_Range::Set_Range_Bitmap(const int& owner, const int& type, const int& attack_type) {
	TCHAR str[80];
	if (owner == Hit_Owner::HO_Player) {

	}
	else {
		switch (type)
		{
		case Enemy_Type::Zadrom:
			if (attack_type == Attack_Type::A_Attack) {
				for (int direction = Object_Direction::Right; direction <= Object_Direction::DownRight; direction++) 
						range_bitmap[direction] = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Monster\\M2\\Attack\\Zadrom_Effect1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			}
			break;
		case Enemy_Type::Tolpi:
			if (attack_type == Attack_Type::A_SkillQ) {
				for (int direction = Object_Direction::Right; direction <= Object_Direction::DownRight; direction++)
						range_bitmap[direction] = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Monster\\M3\\Skill1\\Tolpi_SkillQ_Effect.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			}	
			break;
		case Enemy_Type::Dark_Flower:
			if (attack_type == Attack_Type::A_SkillQ || attack_type == Attack_Type::A_SkillW) {
				for (int direction = Object_Direction::Right; direction <= Object_Direction::DownRight; direction++)
					range_bitmap[direction] = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Monster\\Boss1\\SkillW\\Effect1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			}
			break;
		case Enemy_Type::Huba:
			if (attack_type == Attack_Type::A_Attack) {
				for (int direction = Object_Direction::Right; direction <= Object_Direction::DownRight; direction++) {
					wsprintf(str, _T(".\\BitMap\\Monster\\M6\\Attack\\Huba_Attack_Effect%d.bmp"), direction + 1);
					range_bitmap[direction] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
				}
			}
			break;
		case Enemy_Type::Huba2:
			if (attack_type == Attack_Type::A_Attack) {
				for (int direction = Object_Direction::Right; direction <= Object_Direction::DownRight; direction++) {
					wsprintf(str, _T(".\\BitMap\\Monster\\M7\\Attack\\Huba_Attack_Effect%d.bmp"), direction + 1);
					range_bitmap[direction] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
				}
			}
			break;
		case Enemy_Type::Mobre:
			if (attack_type == Attack_Type::A_Attack) {
				for (int direction = Object_Direction::Right; direction <= Object_Direction::DownRight; direction++)
					range_bitmap[direction] = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Monster\\M10\\Attack\\Mobre_Attack_Effect1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			}
			break;
		default:
			break;
		}
	}
	GetObject(range_bitmap[0], sizeof(BITMAP), &range_bitmap_size);
}

void Reset_Hitting_Range(Hitting_Range& hit_range, const int& owner, const bool& move, const int& direction, const bool& guide, const POINT& speed, const int& type, const int& attack_type) {
	hit_range.Set_Owner(owner);
	hit_range.Set_Move(move);
	hit_range.Set_Direction(direction);
	hit_range.Set_Guide(guide);
	hit_range.Set_Speed(speed);
	hit_range.Set_Range_Bitmap(owner, type, attack_type);
}

const POINT Create_Speed(const int& direction, const int& speed) {
	switch (direction)
	{
	case Object_Direction::Right:
		return { speed,0 };
	case Object_Direction::UpRight:
		return { static_cast<LONG>(speed / sqrt(2) + 0.5),-static_cast<LONG>(speed / sqrt(2) + 0.5) };
	case Object_Direction::Up:
		return { 0,-speed };
	case Object_Direction::UpLeft:
		return { -static_cast<LONG>(speed / sqrt(2) + 0.5),-static_cast<LONG>(speed / sqrt(2) + 0.5) };
	case Object_Direction::Left:
		return { -speed,0 };
	case Object_Direction::DownLeft:
		return { -static_cast<LONG>(speed / sqrt(2) + 0.5), static_cast<LONG>(speed / sqrt(2) + 0.5) };
	case Object_Direction::Down:
		return { 0,speed };
	case Object_Direction::DownRight:
		return { static_cast<LONG>(speed / sqrt(2) + 0.5), static_cast<LONG>(speed / sqrt(2) + 0.5) };
	default:
		break;
	}
}

Hitting_Range_Polygon::~Hitting_Range_Polygon() {}

const POINT Hitting_Range_Polygon::Get_Pos(const int& index) const {
	return pos[index];
}

void Hitting_Range_Polygon::Set_Pos(const POINT p[4]) {
	for (int index = 0; index < 4; index++)
		pos[index] = p[index];
}

void Hitting_Range_Polygon::Set_Pos_One(const POINT& pos, const int& index) {
	this->pos[index] = pos;
}

void Reset_Hitting_Range_Polygon(Hitting_Range_Polygon& hit_range_p, const int& onwer, const bool& move, const int& direction, const bool& guide, const POINT& speed, const int& type, const int& attack_type, const POINT pos[4], const int& delay, const double& attack_multiple) {
	hit_range_p.Set_Pos(pos);
	hit_range_p.Set_Delay(delay);
	hit_range_p.Set_Attack_Multiple(attack_multiple);
	Reset_Hitting_Range(hit_range_p, onwer, move, direction, guide, speed, type, attack_type);
}

void Move_Hitting_Range_Polygon(Hitting_Range_Polygon& hit_range_p) {
	if (hit_range_p.Is_Move() || hit_range_p.Is_Guide()) {
		for (int index = 0; index < 4; index++) {
			hit_range_p.Set_Pos_One({ hit_range_p.Get_Pos(index).x + hit_range_p.Get_Speed().x ,hit_range_p.Get_Pos(index).y + hit_range_p.Get_Speed().y }, index);
		}
	}
}

void Paint_Hitting_Range(HDC hdc, HDC bitdc, const Hitting_Range_Polygon& hit_range_p) {
	if (hit_range_p.Get_Range_Bitmap(hit_range_p.Get_Direction()) != NULL) {
		SelectObject(bitdc, hit_range_p.Get_Range_Bitmap(hit_range_p.Get_Direction()));
		POINT pos;
		pos = { (hit_range_p.Get_Pos(0).x + hit_range_p.Get_Pos(2).x) / 2, (hit_range_p.Get_Pos(0).y + hit_range_p.Get_Pos(2).y) / 2 };
		TransparentBlt(hdc, pos.x - hit_range_p.Get_Range_Bitmap_Size().bmWidth / 2, pos.y - hit_range_p.Get_Range_Bitmap_Size().bmHeight / 2, hit_range_p.Get_Range_Bitmap_Size().bmWidth, hit_range_p.Get_Range_Bitmap_Size().bmHeight,
			bitdc, 0, 0, hit_range_p.Get_Range_Bitmap_Size().bmWidth, hit_range_p.Get_Range_Bitmap_Size().bmHeight, RGB(150, 150, 150));
	}
}