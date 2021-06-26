#include <windows.h>
#include <iostream>

using std::cout;
using std::endl;

/* 
USEFULL INFO
ExW means Extend to Wide character format (Unicode), A - ANCI format
str (char string) - "Hello world!" - ASCII characters
wcs (wide char string) - L"Hello world!" - 16-bit UNICODE characters (L means Long foramt)
*/

/* 
Window processing function processes the window messages
hwnd is a handle to the window.
uMsg is the message code; for example, the WM_SIZE message indicates the window was resized.
wParam and lParam contain additional data that pertains to the message. The exact meaning depends on the message code.
*/
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_DESTROY:
            // The PostQuitMessage function posts a WM_QUIT message to the message queue
            PostQuitMessage(0);
        break;
        case WM_KEYDOWN:
            cout << "Key Down: " << wParam << endl;
        break;
        case WM_LBUTTONDOWN:
            cout << "Left Button Down." << endl;
        break;
        case WM_MOUSEMOVE:
            // The LOWORD() and HIWORD() macros get the 16-bit width and height values from lParam
            cout << "Mouse Move: [" << LOWORD(lParam) << ", " << HIWORD(lParam) << "]" << endl;
        break;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int main()
{
    // Handle to the application instance
    HINSTANCE hInstance = GetModuleHandle(nullptr);

    // Register the window class, WNDCLASS - window class
    // LPCWSTR - Long Pointer to Const Wide String (const wchar_t*)
    WNDCLASS wc = {};
    const wchar_t CLASS_NAME[] = L"WindowClass";

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    /*
    Create the window, HWND - handle to the window
    Windows are not C++ classes. A program references to window by using a value called a handle. 
    It is just a number that OS uses to identify an object.
    */
    HWND hwnd = CreateWindow(
        CLASS_NAME,                  // Window class
        L"Learn to Program Windows", // Window text
        WS_OVERLAPPEDWINDOW,         // Window style
        CW_USEDEFAULT,               // X
        CW_USEDEFAULT,               // Y
        640,                         // Width
        480,                         // Height
        nullptr,                     // Parent window    
        nullptr,                     // Menu
        hInstance,                   // Instance handle
        nullptr                      // Additional application data
    );  
    
    // Show the window
    ShowWindow(hwnd, SW_SHOWNORMAL);

    /*
    Hide and show the console
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    ShowWindow(GetConsoleWindow(), SW_SHOWNORMAL);
    */

    // Window message, MSG - message
    MSG msg = {};

    // Main loop
    while (GetKeyState(VK_ESCAPE) >= 0)
    {
        // Processing window messages
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            /*
            GetMessage is a blocking function
            It waits until a message is received from the queue. During this time program is standing
            For that case use PeekMessage function instead. It checks if the message in the queue and runs further
            PeekMessage uses the same parameters + one for removing messages
            */

            DispatchMessage(&msg);
            if (msg.message == WM_QUIT) break;
        }

        /*  
        For example, user presses the left mouse button. This causes a chain of events:
        1. The operating system puts a WM_LBUTTONDOWN message on the message queue.
        2. Your program calls the GetMessage function.
        3. GetMessage pulls the WM_LBUTTONDOWN message from the queueand fills in the MSG structure.
        4. Your program calls the TranslateMessageand DispatchMessage functions.
        5. Inside DispatchMessage, the operating system calls your window procedure.
        6. Your window procedure can either respond to the message or ignore it.
        */
    }

    return 0;
}