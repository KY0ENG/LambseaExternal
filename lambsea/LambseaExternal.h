#pragma once
#include "stdafx.h"
//-------------�����ʼ������-------------//
void WINAPI Initialize();
void WINAPI Release();


//--------����----------------
void WINAPI Switch();
BOOL WINAPI ConsoleHandler(DWORD CtrlType);

////------�Զ���ȡOffset
//BOOL WINAPI SetupOffsets();

//------��ѭ��
void WINAPI MainLoop();

//----���̶߳�ȡcamera
void WINAPI CameraLoop();