//Win32->API->Windows and Messages-> WinMain function (winbase.h)

#include <Windows.h>
//#include <windef.h>
#include "renderer.h"
#include "utilities.h"
#include "typenames.h"

static struct Render_State
{
	int height, width;
	void* memory;
	BITMAPINFO bitmap_info;

} render_state;

static bool gameIsRunning = true;

/*
The BITMAPINFOHEADER structure contains information
about the dimensions and color format
of a device-independent bitmap (DIB).
*/
//BITMAPINFO render_state.bitmap_info;

LRESULT window_callback(
	HWND hwnd,
	//A handle to the window.
	//This parameter is typically named hWnd.
	UINT uMsg,
	/*
	The message. This parameter is typically named uMsg.
	For lists of the system-provided messages, see System-defined messages.
	*/
	WPARAM wParam,
	/*
	Additional message information. This parameter is typically named wParam.
	The contents of the wParam parameter depend on the value of the uMsg parameter.
	*/
	LPARAM lParam
	/*
	Additional message information. This parameter is typically named lParam.
	The contents of the lParam parameter depend on the value of the uMsg parameter.
	*/
)
{
	LRESULT result = 0;
	switch (uMsg) {
		case WM_CLOSE:
		case WM_DESTROY:
		{
			gameIsRunning = false;
		} break;
		case WM_SIZE:
		{
			RECT rect;

			GetClientRect(
				/*[in]  HWND   hWnd*/		hwnd,			//A handle to the window whose client coordinates are to be retrieved.
				/*[out] LPRECT lpRect*/		&rect			//A pointer to a RECT structure that receives the client coordinates.
				//The left and top members are zero.
				//The right and bottom members contain the width and height of the window.
			);

			render_state.width = rect.right - rect.left;									//Calculate width
			render_state.height = rect.bottom - rect.top;									//Calculate height
			int size = render_state.width * render_state.height * sizeof(u32);

			/*
			return type LPVOID 
			Reserves, commits, or changes the state of a region of pages in the
			virtual address space of the calling process. Memory allocated
			by this function is automatically initialized to zero.
			*/
			if (render_state.memory)
				//Releases, decommits, or releases and decommits a region of pages within the virtual address space of the calling process.
				//return type VirtualFree() - bool
				VirtualFree(
					/*[in] LPVOID lpAddress*/		render_state.memory,			//A pointer to the base address of the region of pages to be freed.
					/*[in] SIZE_T dwSize*/			0,								//The size of the region of memory to be freed, in bytes.
					/*[in] DWORD  dwFreeType*/		MEM_RELEASE);					//The type of free operation.

			//void* pointer
			//return type VirtualAlloc() - LPVOID
			render_state.memory = VirtualAlloc(
				/*[in, optional] LPVOID lpAddress*/				0,								//The starting address of the region to allocate.
				/*[in]           SIZE_T dwSize*/				size,							//The size of the region, in bytes.
				/*[in]           DWORD  flAllocationType*/		MEM_COMMIT | MEM_RESERVE,		//The type of memory allocation.
				/*[in]           DWORD  flProtect*/				PAGE_READWRITE					//The memory protection for the region of pages to be allocated. 
			);

			render_state.bitmap_info.bmiHeader.biSize = sizeof(render_state.bitmap_info.bmiHeader);			//Specifies the number of bytes required by the structure.
			render_state.bitmap_info.bmiHeader.biWidth = render_state.width;
			render_state.bitmap_info.bmiHeader.biHeight = render_state.height;
			render_state.bitmap_info.bmiHeader.biPlanes = 1;												//Must be one for some reason
			render_state.bitmap_info.bmiHeader.biBitCount = 32;												//Specifies the number of bits per pixel (bpp).
			render_state.bitmap_info.bmiHeader.biCompression = BI_RGB;										//For compressed video and YUV formats,
																											//this member is a FOURCC code, specified as a DWORD
																											//in little-endian order. For example,
																											//YUYV video has the FOURCC 'VYUY' or 0x56595559.

		} break;
		default:
		{
			result = DefWindowProc(hwnd, uMsg, wParam, lParam);
		}

	}
	return result;
}

int WINAPI WinMain(
	_In_		HINSTANCE hInstance,
	//A handle to the current instance of the application.
	_In_opt_	HINSTANCE hPrevInstance,
	/*
	A handle to the previous instance of the application.
	This parameter is always NULL.
	If you need to detect whether another instance already exists,
	create a uniquely named mutex using the CreateMutex function.
	CreateMutex will succeed even if the mutex already exists,
	but the function will return ERROR_ALREADY_EXISTS.
	This indicates that another instance of your application exists,
	because it created the mutex first. However, a malicious user can create
	this mutex before you doand prevent your application from starting.
	To prevent this situation, create a randomly named mutexand store
	the name so that it can only be obtained by an authorized user.
	Alternatively, you can use a file for this purpose.
	To limit your application to one instance per user,
	create a locked file in the user's profile directory.
	*/
	_In_		LPSTR     lpCmdLine,
	/*
	The command line for the application, excluding the program name.
	To retrieve the entire command line, use the GetCommandLine function.
	*/
	_In_		int       nShowCmd
	/*
	Controls how the window is to be shown.
	This parameter can be any of the values that can be specified
	in the nCmdShow parameter for the ShowWindow function.
	*/
)
{
	//To draw a window we need:
	//#1. Create a window class
	WNDCLASS window_class = {};
	window_class.style = CS_HREDRAW | CS_VREDRAW;
	window_class.lpszClassName = "Game Window Class";
	window_class.lpfnWndProc = reinterpret_cast<WNDPROC>(window_callback);

	//#2. Register a window class
	RegisterClass(&window_class);

	//#3. Create a window
	HWND window = CreateWindowA(
		/*lpClassName*/		window_class.lpszClassName,			//A null-terminated string or a class atom created by a previous call to the RegisterClass or RegisterClassEx function.
		/*lpWindowName*/	"Game Ping-Pong, produced by Dimmak (c).",					//The window name.
		/*dwStyle*/			WS_OVERLAPPEDWINDOW | WS_VISIBLE,	//The style of the window being created.
		/*x*/				CW_USEDEFAULT,						//The initial horizontal position of the window. 
		/*y*/				CW_USEDEFAULT,						//The initial vertical position of the window.
		/*nWidth*/			1280,								//The width, in device units, of the window. 
		/*nHeight*/			720,								//The height, in device units, of the window. 
		/*hWndParent*/		0,									//A handle to the parent or owner window of the window being created.
		/*hMenu*/			0,									//A handle to a menu, or specifies a child-window identifier depending on the window style. 
		/*hInstance*/		hInstance,							//A handle to the instance of the module to be associated with the window.
		/*lpParam*/			0									//A pointer to a value to be passed to the window through the CREATESTRUCT structure
																//(lpCreateParams member) pointed to by the lParam param of the WM_CREATE message. 
	);

	/*
	Function retrieves a handle to a device context (DC)
	for the client area of a specified window or for the entire screen
	*/
	HDC hdc = GetDC(window);

	while (gameIsRunning)
	{
		//Input
		MSG message;
		while (PeekMessage(
			/*LPMSG lpMsg*/				&message,					//A pointer to an MSG structure that receives message information.
			/*HWND  hWnd*/				window,						//A handle to the window whose messages are to be retrieved.
																	//The window must belong to the current thread.
			/*UINT  wMsgFilterMin*/		0,							//The value of the first message in the range of messages to be examined. 
			/*UINT  wMsgFilterMax*/		0,							//The value of the last message in the range of messages to be examined.
			/*UINT  wRemoveMsg*/		PM_REMOVE					//Specifies how messages are to be handled.
		))
		{
			/*
			Translates virtual - key messages into character messages.
			The character messages are posted to the calling thread's
			message queue, to be read the next time the thread calls
			the GetMessage or PeekMessage function.
			*/
			TranslateMessage(
			/*const MSG * lpMsg*/		&message					//A pointer to an MSG structure that contains message information
																	//retrieved from the calling thread's message queue by using the GetMessage or PeekMessage function.
			);

			/*
			Dispatches a message to a window procedure.
			It is typically used to dispatch a message retrieved
			by the GetMessage function.
			*/
			DispatchMessage(
			/*const MSG * lpMsg*/		&message					//A pointer to a structure that contains the message.
			);
		}
		//Simulate
		u32* pixel = reinterpret_cast<u32*>(render_state.memory);
		//render_background(pixel, render_state.height, render_state.width);
		clear_screen(pixel, render_state.height, render_state.width, 0xff0000);
		draw_rectangle(
			render_state.memory, 
			0, 0, 1, 1, 
			render_state.width, render_state.height, 
			0x0a54d0
		);
		draw_rectangle(
			render_state.memory, 
			5, 12, 5, 5, 
			render_state.width, render_state.height, 
			0xca33d0
		);
		draw_rectangle(
			render_state.memory, 
			-20, -30, 2, 2, 
			render_state.width, render_state.height, 
			0x5235a2
		);

		//Render
		/*
		The StretchDIBits function copies the color data
		for a rectangle of pixels in a DIB, JPEG, or PNG image
		to the specified destination rectangle. 
		*/
		StretchDIBits(
			/*[in] HDC              hdc*/			hdc,						//A handle to the destination device context.
			/*[in] int              xDest*/			0,							//The x-coordinate, in logical units, of the upper-left corner of the destination rectangle.
			/*[in] int              yDest*/			0,							//The y-coordinate, in logical units, of the upper-left corner of the destination rectangle.
			/*[in] int              DestWidth*/		render_state.width,			//The width, in logical units, of the destination rectangle.
			/*[in] int              DestHeight*/	render_state.height,		//The height, in logical units, of the destination rectangle.
			/*[in] int              xSrc*/			0,							//The x-coordinate, in pixels, of the source rectangle in the image.
			/*[in] int              ySrc*/			0,							//The y-coordinate, in pixels, of the source rectangle in the image.
			/*[in] int              SrcWidth*/		render_state.width,			//The width, in pixels, of the source rectangle in the image.
			/*[in] int              SrcHeight*/		render_state.height,		//The height, in pixels, of the source rectangle in the image.
			/*[in] const VOID*		lpBits*/		render_state.memory,		//A pointer to the image bits, which are stored as an array of bytes.
																				//For more information, see the Remarks section.
			/*[in] const BITMAPINFO* lpbmi*/		&render_state.bitmap_info,	//A pointer to a BITMAPINFO structure that contains information about the DIB.
			/*[in] UINT             iUsage*/		DIB_RGB_COLORS,				//Specifies whether the bmiColors member of the BITMAPINFO structure was provided and,
																				//if so, whether bmiColors contains explicit red, green, blue (RGB) values or indexes. 
			/*[in] DWORD            rop*/			SRCCOPY						//A raster-operation code that specifies how the source pixels,
																				//the destination device context's current brush,
																				//and the destination pixels are to be combined to form the new image. 
		);
	}

	//return MessageBox(NULL, (LPCWSTR)"hello, world", (LPCWSTR)"caption", 0);
	//return MessageBox(NULL, "hello, world", "caption", 0);
	return 0;
}
