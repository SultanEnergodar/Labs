#include <windows.h>
#include <math.h>

class Vector2D {
public:
    double x, y;

    Vector2D(double x = 0, double y = 0) : x(x), y(y) {}

    Vector2D operator+(const Vector2D& v) const {
        return Vector2D(x + v.x, y + v.y);
    }

    Vector2D operator-(const Vector2D& v) const {
        return Vector2D(x - v.x, y - v.y);
    }

    Vector2D operator*(double s) const {
        return Vector2D(x * s, y * s);
    }

    Vector2D operator/(double s) const {
        return Vector2D(x / s, y / s);
    }


    double Length() const {
        return sqrt(x * x + y * y);
    }

    double LengthSquared() const {
        return x * x + y * y;
    }

    void Normalize() {
        double len = Length();
        if (len == 0) {
            x = 0;
            y = 0;
        }
        else {
            x /= len;
            y /= len;
        }
    }
};

void Ellipse(HDC hdc, const Vector2D& center, const Vector2D& radius) {
    Ellipse(hdc, int(center.x - radius.x), int(center.y - radius.y),
        int(center.x + radius.x), int(center.y + radius.y));
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        Vector2D center(50, 50);
        Vector2D radius(20, 20);
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                Ellipse(hdc, center, radius);
                center = center + Vector2D(100, 0);
            }
            center = center + Vector2D(-200, 100);
        }

        EndPaint(hWnd, &ps);
        break;
    }
    case WM_DESTROY: {
        PostQuitMessage(0);
        break;
    }
    default: {
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    }

    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"MyWindowClass";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    RegisterClass(&wc);

    HWND hWnd = CreateWindow(L"MyWindowClass", L"My Window", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL, hInstance, NULL);

    ShowWindow(hWnd, nCmdShow);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
