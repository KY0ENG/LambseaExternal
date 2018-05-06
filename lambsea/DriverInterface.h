#pragma once
#include "stdafx.h"
#include "Driver-resrvlib-Interface.h"
#include <iostream>

//ʹ�� �궨�� �Լ� namespace ��ʵ�������л���ͬ��driver interface
#pragma region ģ��

//��������/ɾ������
BOOL WINAPI LoadDriver();
BOOL WINAPI UnLoadDriver();

//�ڴ��д���

//1.��ȡ���̻�ַ, Tslgame.exe baseaddress
BOOL WINAPI DriverGetModulebase();

//2.�������ڴ�
BOOL WINAPI DriverReadMemory(_In_  ULONGLONG lpBaseAddress, _Out_ LPVOID  lpBuffer, _In_  SIZE_T  nSize);

//3.����д�ڴ�
BOOL WINAPI DriverWriteMemory(_In_  ULONGLONG  lpBaseAddress, _In_  LPVOID lpBuffer, _In_  SIZE_T  nSize);

//4.����Alloc ��Ϸ�ڴ�
BOOL WINAPI DriverAllocMemory();

//5.����free  ��Ϸ�ڴ�
BOOL WINAPI DriverFreeMemory();

#pragma endregion


//Helper ����
template<typename T>
T GetDriverFunctions(HMODULE hModule, wchar_t* funcName) {
	return reinterpret_cast<T>(GetProcAddress(hModule, funcName));
};
uint32_t GetProcessID();

//ʹ��namespace��
namespace resrvlib {

	void WINAPI Init(LPCSTR modulename, LPCWSTR processname);

	//��������/ɾ������
	BOOL WINAPI LoadDriver();
	BOOL WINAPI UnLoadDriver();

	//�ڴ��д���

	//1.��ȡ���̻�ַ, Tslgame.exe baseaddress
	DWORD_PTR WINAPI DriverGetModulebase(OPTIONAL ULONG size);

	//2.�������ڴ�
	BOOL WINAPI DriverReadMemory(_In_  ULONGLONG lpBaseAddress, _Out_ LPVOID  lpBuffer, _In_  SIZE_T  nSize );

	//3.����д�ڴ�
	BOOL WINAPI DriverWriteMemory(_In_  ULONGLONG  lpBaseAddress, _In_  LPVOID lpBuffer, _In_  SIZE_T  nSize);

	//4.����Alloc ��Ϸ�ڴ�
	BOOL WINAPI DriverAllocMemory();

	//5.����free  ��Ϸ�ڴ�
	BOOL WINAPI DriverFreeMemory();

	extern reserve_init ResInit;
	extern reserve_module ResModule;
	extern reserve_read ResRead;
	extern reserve_write ResWrite;


	extern LPCSTR szModuleName;
	extern LPCWSTR wszProcName;
	extern unsigned int ProcID;

}










// Request to retrieve initialize from kernel space
#define IO_Init_REQUEST CTL_CODE(FILE_DEVICE_UNKNOWN, 0x05240 /* Our Custom Code */, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)

// Request to retrieve the base address of process in csgo.exe from kernel space
#define IO_GET_MODULE_REQUEST CTL_CODE(FILE_DEVICE_UNKNOWN, 0x05241 /* Our Custom Code */, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)

// Request to read virtual user memory (memory of a program) from kernel space
#define IO_READ_REQUEST CTL_CODE(FILE_DEVICE_UNKNOWN, 0x05242 /* Our Custom Code */, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)

// Request to write virtual user memory (memory of a program) from kernel space
#define IO_WRITE_REQUEST CTL_CODE(FILE_DEVICE_UNKNOWN, 0x05243 /* Our Custom Code */, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)

#define IO_PROTECT_REQUEST CTL_CODE(FILE_DEVICE_UNKNOWN, 0x05244 /* Our Custom Code */, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)

#define RegPath L"\\\\.\\JYAV"

// datatype for read request
typedef struct _KERNEL_READ_REQUEST
{
	DWORD_PTR TargetAddress;
	DWORD_PTR ResponseAddress;
	ULONG Size;
} KERNEL_READ_REQUEST, *PKERNEL_READ_REQUEST;

// datatype for write request
typedef struct _KERNEL_WRITE_REQUEST
{
	DWORD_PTR TargetAddress;
	DWORD_PTR CopiedFromAddress;
	ULONG Size;
} KERNEL_WRITE_REQUEST, *PKERNEL_WRITE_REQUEST;

namespace LambseaDriver {

	void WINAPI Init(LPCSTR modulename, LPCWSTR processname);

	//��������/ɾ������
	BOOL WINAPI LoadDriver();
	BOOL WINAPI UnLoadDriver();

	//�ڴ��д���

	//1.��ȡ���̻�ַ, Tslgame.exe baseaddress
	DWORD_PTR WINAPI DriverGetModulebase(OPTIONAL ULONG size);

	//2.�������ڴ�
	BOOL WINAPI DriverReadMemory(_In_  ULONGLONG lpBaseAddress, _Out_ LPVOID  lpBuffer, _In_  SIZE_T  nSize);

	//3.����д�ڴ�
	BOOL WINAPI DriverWriteMemory(_In_  ULONGLONG  lpBaseAddress, _In_  LPVOID lpBuffer, _In_  SIZE_T  nSize);

	extern HANDLE hDriver;
	extern ULONG ProcID;

}

inline BOOL LambseaDriver::DriverReadMemory(ULONGLONG lpBaseAddress, LPVOID lpBuffer, SIZE_T nSize)
{
	if (hDriver == INVALID_HANDLE_VALUE)
		return FALSE;

	DWORD Bytes;
	KERNEL_READ_REQUEST ReadRequest;
	ReadRequest.TargetAddress = lpBaseAddress;
	ReadRequest.ResponseAddress = (DWORD_PTR)lpBuffer;
	ReadRequest.Size = nSize;

	// send code to our driver with the arguments
	if (DeviceIoControl(hDriver, IO_READ_REQUEST, &ReadRequest, sizeof(ReadRequest), &ReadRequest, sizeof(ReadRequest), &Bytes, NULL))
		return TRUE;
	else
		return FALSE;

}