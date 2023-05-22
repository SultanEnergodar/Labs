#include <windows.h>
#include <vector>

// Структура для хранения информации о фигуре
struct Shape {
    int x, y, radius, width, height;
    COLORREF color;
    Shape(int x, int y, int radius, COLORREF color)
        : x(x), y(y), radius(radius), width(0), height(0), color(color) {}
    Shape(int x, int y, int width, int height, COLORREF color)
        : x(x), y(y), radius(0), width(width), height(height), color(color) {}
};

// Глобальный вектор для хранения фигур
std::vector<Shape> shapes;

// Функция для создания окружности
void CreateCircle(int x, int y, int radius, COLORREF color) {
    Shape circle(x, y, radius, color );
    shapes.push_back(circle);
}

// Функция для создания прямоугольника
void CreateRectangle(int x, int y, int width, int height, COLORREF color) {
    Shape rectangle(x, y, width, height, color);
    shapes.push_back(rectangle);
}

// Функция для рисования окружности
void DrawCircle(HDC hdc, int x, int y, int radius, COLORREF color) {
    HBRUSH brush = CreateSolidBrush(color);
    HGDIOBJ oldBrush = SelectObject(hdc, brush);
    Ellipse(hdc, x - radius, y - radius, x + radius, y + radius);
    SelectObject(hdc, oldBrush);
    DeleteObject(brush);
}

// Функция для рисования прямоугольника
void DrawRectangle(HDC hdc, int x, int y, int width, int height, COLORREF color) {
    HBRUSH brush = CreateSolidBrush(color);
    HGDIOBJ oldBrush = SelectObject(hdc, brush);
    Rectangle(hdc, x, y, x + width, y + height);
    SelectObject(hdc, oldBrush);
    DeleteObject(brush);
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_CREATE: {
        CreateCircle(50, 50, 20, RGB(255, 0, 0));
        CreateRectangle(100, 100, 50, 30, RGB(0, 0, 255));
        return 0;
    }
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        // Рисуем все фигуры из вектора
        for (const Shape& shape : shapes) {
            if (shape.radius > 0) {
                DrawCircle(hdc, shape.x, shape.y, shape.radius, shape.color);
            }
            else {
                DrawRectangle(hdc, shape.x, shape.y, shape.width, shape.height, shape.color);
            }
        }

        EndPaint(hWnd, &ps);
        return 0;
    }
    case WM_DESTROY: {
        PostQuitMessage(0);
        return 0;
    }
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"Class";
    RegisterClass(&wc);

    HWND hWnd = CreateWindowEx(
        0, L"Class", L"Window", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL, hInstance, NULL
    );

    ShowWindow(hWnd, nCmdShow);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
