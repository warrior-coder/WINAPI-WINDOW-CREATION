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
            When you want to exit the applicationand break out of the message loop, call the PostQuitMessage function.
            PostQuitMessage(0);
            The PostQuitMessage function puts 0 on the message queue.
            It causes GetMessage to return 0, signaling the end of the message loop.
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
    // Register the window class, WNDCLASS - window class
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.lpszClassName = L"MyWindow";
    RegisterClassW(&wc);

    // Create the window, HWND - handle window
    HWND hwnd = CreateWindowExW(
        0,                     // Optional window styles
        L"MyWindow",           // Window class
        L"My Window",          // Window title
        WS_OVERLAPPEDWINDOW,   // Window style
        0,                     // X
        0,                     // Y
        600,                   // Width
        400,                   // Height
        NULL, NULL, NULL, NULL // Optional parametrs
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
        if (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT) break;
            DispatchMessageW(&msg);
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