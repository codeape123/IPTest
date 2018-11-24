#pragma once

typedef unsigned __int64 _uint64;

const DWORD		c_dw1K   = 0x400;		//1024
const DWORD		c_dw1M   = 0x100000;    //1024*1024
const DWORD		c_dw16M  = 0x1000000;	//16*1024*1024
const DWORD		c_dw32M  = 0x2000000;	//32*1024*1024
const DWORD		c_dw64M  = 0x4000000;	//64*1024*1024
const DWORD		c_dw128M = 0x8000000;	//128*1024*1024
const _uint64	c_ui641G = 0x40000000;	//1024*1024*1024

const int c_iVirMemUnit4K = 0x1000;		//4K 分配虚拟内存要4K对齐

static const unsigned int ms_kuiDefaultStackSize = 0x1000000; //128 * 1024; // 128KB


//////////////////////////////////////////////////////////////////////////
// Usefull macro for clean up
#define SAFE_DELETE(ptr)        {if(ptr){delete ptr;ptr = NULL;};}
#define SAFE_DELETE_ARRAY(ptr)  {if(ptr){delete [] ptr;ptr = NULL;};}
#define SAFE_FREE(ptr)          {if(ptr){free(ptr);ptr = NULL;};}
#define SAFE_GLOBAL_FREE(ptr)   {if(ptr){GlobalFree(ptr);ptr = NULL;};}
#define SAFE_COTASKMEMFREE(ptr) {if(ptr){CoTaskMemFree(ptr);ptr = NULL;};}
#define SAFE_RELEASE_PTR(ptr)   {if(ptr){ptr->Release();ptr = NULL;};}
#define SAFE_CLOSE_HANDLE(hdl)  {if(hdl){CloseHandle(hdl);hdl = NULL;};}


