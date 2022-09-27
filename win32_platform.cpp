//Win32->API->Windows and Messages-> WinMain function (winbase.h)

#include <windows.h>

bool gameIsRunning = true;

LRESULT window_callback(
	HWND hwnd,
	//A handle to the window. This parameter is typically named hWnd.
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
		default:
		{
			result = DefWindowProc(hwnd, uMsg, wParam, lParam);
		}

	}
	return result;
}

int WINAPI WinMain(
	HINSTANCE hInstance,
	//A handle to the current instance of the application.
	HINSTANCE hPrevInstance,
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
	LPSTR     lpCmdLine,
	/*
	The command line for the application, excluding the program name.
	To retrieve the entire command line, use the GetCommandLine function.
	*/
	int       nShowCmd
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
	window_class.lpfnWndProc = window_callback;

	//#2. Register a window class
	RegisterClass(&window_class);

	//#3. Create a window
	HWND window = CreateWindowA(
		/*lpClassName*/		window_class.lpszClassName,			//A null-terminated string or a class atom created by a previous call to the RegisterClass or RegisterClassEx function.
		/*lpWindowName*/	"My first Game!",					//The window name.
		/*dwStyle*/			WS_OVERLAPPEDWINDOW | WS_VISIBLE,	//The style of the window being created.
		/*x*/				CW_USEDEFAULT,						//The initial horizontal position of the window. 
		/*y*/				CW_USEDEFAULT,						//The initial vertical position of the window.
		/*nWidth*/			1280,								//The width, in device units, of the window. 
		/*nHeight*/			720,								//The height, in device units, of the window. 
		/*hWndParent*/		0,									//A handle to the parent or owner window of the window being created.
		/*hMenu*/			0,									//A handle to a menu, or specifies a child-window identifier depending on the window style. 
		/*hInstance*/		hInstance,							//A handle to the instance of the module to be associated with the window.
		/*lpParam*/			0,									//A pointer to a value to be passed to the window through the CREATESTRUCT structure
																//(lpCreateParams member) pointed to by the lParam param of the WM_CREATE message. 
	);

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
			DispatchMessageA(
			/*const MSG * lpMsg*/		&message					//A pointer to a structure that contains the message.
			);
		}
		//Simulate
		//Render
	}

	//return MessageBox(NULL, (LPCWSTR)"hello, world", (LPCWSTR)"caption", 0);
	//return MessageBox(NULL, "hello, world", "caption", 0);
	return 0;
}
