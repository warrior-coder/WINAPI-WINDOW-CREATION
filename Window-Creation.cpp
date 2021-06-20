#include <iostream>
#include <windows.h>

using std::cout;
using std::endl;

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
            /*
            The PostQuitMessage function posts a WM_QUIT message to the message queue
            */
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

    return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}

int main()
{
    // Handle to the application instance
    HINSTANCE hInstance = GetModuleHandleW(nullptr);
    
    // Register the window class, WNDCLASS - window class
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"MyWindow";
    RegisterClassW(&wc);

    // Create the window, HWND - handle to the window
    HWND hwnd = CreateWindowExW(
        0,                   // Optional window styles
        L"MyWindow",         // Window class
        L"My Window",        // Window title
        WS_OVERLAPPEDWINDOW, // Window style
        CW_USEDEFAULT,       // X
        CW_USEDEFAULT,       // Y
        600,                 // Width
        400,                 // Height
        NULL,                // Parent window    
        NULL,                // Menu
        hInstance,           // Instance handle
        NULL                 // Additional application data
    );  

    // Show the window
    ShowWindow(hwnd, SW_SHOWNORMAL);

    /* Hides and show the console
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    ShowWindow(GetConsoleWindow(), SW_SHOWNORMAL);
    */

    // Window message, MSG - message
    MSG msg = {};

    // Main loop
    while (GetKeyState(VK_ESCAPE) >= 0)
    {
        // Processing window messages
        if (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            /*
            GetMessage is a blocking function
            It waits until a message is received from the queue. During this time program is standing
            For that case use PeekMessage function instead. It checks if the message in the queue and runs further
            PeekMessage uses the same parameters + one for removing messages
            */

            DispatchMessageW(&msg);
            if (msg.message == WM_QUIT) break;
        }

        /*  For example, user presses the left mouse button. This causes a chain of events:
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