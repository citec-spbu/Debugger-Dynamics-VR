#pragma once
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <thread>
#include <chrono>
#include <conio.h>
#include <sstream>
#include <iomanip>
#include <map>

#define sleep(x) std::this_thread::sleep_for(std::chrono::milliseconds(x))
#define _CRT_SECURE_NO_WARNINGS
