#pragma once

enum States
{
	SPLASH = 0,
	MENU,
	OPTIONS,
	LOADING,
	INGAME,
	PAUSE,
	STATE_COUNT
};

enum Prompt
{
	REGISTER = 0,
	PUSH,
	POP,
	QUIT
};

struct Request
{
	Prompt	pr;
	States	st;
};