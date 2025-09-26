#pragma once

struct Position	// 좌표 계산 구조체
{
	int x;
	int y;

	Position() : x(0), y(0) {}
	Position(int InX, int InY) : x(InX), y(InY) {}

	Position operator+(const Position& Other) const
	{
		return Position(x + Other.x, y + Other.y);
	}
	Position operator-(const Position& Other) const
	{
		return Position(x - Other.x, y - Other.y);
	}
	bool operator==(const Position& Other) const
	{
		return x == Other.x && y == Other.y;
	}
	bool operator!=(const Position& Other) const
	{
		return !(*this == Other);
	}
};