// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once
#define _CRT_SECURE_NO_WARNINGS 1

//windows SDK
#include "targetver.h"
#include <Windows.h>

//windows common lib API
#include <Psapi.h>
#pragma comment(lib, "Psapi.lib")
#include <TlHelp32.h>

//d3d9 - related
#include <d3d9.h>
#include <d3dx9.h>
#include <Dwmapi.h> 

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"Dwmapi.lib")


#include <stdio.h>
#include <tchar.h>
// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
#include <atlconv.h> //A2W W2A
