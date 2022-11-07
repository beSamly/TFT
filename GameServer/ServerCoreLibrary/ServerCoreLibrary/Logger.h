#pragma once
#include <iostream>

enum class Color
{
	BLACK,
	WHITE,
	RED,
	GREEN,
	BLUE,
	YELLOW,
};

class Logger
{
	enum { BUFFER_SIZE = 4096 };

public:
	Logger();
	~Logger();

private:
	HANDLE		stdOut;
	HANDLE		stdErr;

public:
	void		Error(const string str, ...);
	void		Debug(const string str, ...);
	void		Warn(const string str, ...);
	void		Info(const string str, ...);
	template<typename... Args>
	void		InfoP(const char* f, Args... args);

protected:
	void		SetColor(Color color, bool isStdOut);

private:
	void		Log(Color color, bool isStdOut, const string str, string prefix);
};
