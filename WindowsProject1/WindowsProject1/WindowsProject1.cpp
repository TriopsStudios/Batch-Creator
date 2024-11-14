// WindowsProject1.cpp : Define el punto de entrada de la aplicación.
//

#include "framework.h"
#include "WindowsProject1.h"
#include <string>
#include <vector>

#define DINAMIC std::wstring
#define WH 420
#define HH 150
#define tBWH WH/4
#define tBHH 25

// Variables globales:
HINSTANCE hInst;                                // instancia actual
DINAMIC szTitle = L"BatchCode";                  // Texto de la barra de título
DINAMIC szWindowClass =L"Window";           // nombre de clase de la ventana principal
DINAMIC* textObtained1 = nullptr;
DINAMIC* textObtained2 = nullptr;
DINAMIC* textObtained3 = nullptr;
DINAMIC* textObtained4 = nullptr;
DINAMIC* loteFinal = nullptr;

wchar_t buffer[100];
HWND hTextBoxFecha, hTextBoxProducto, Boton, hTextBoxDia, hTextBoxMes, textoResultado;

// Declaraciones de funciones adelantadas incluidas en este módulo de código:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

//Declaracion funciones propias
void CrearElementos(HWND hWnd, HINSTANCE instance);
int Conversion(HWND hWnd);
bool esBisiesto(int year);
int diaDelAno(int dia, int mes, int year);

void CrearElementos(HWND hWnd, HINSTANCE instance) {
    hTextBoxFecha = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"Year",
        WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_LEFT,
        0, 0, tBWH, tBHH, hWnd, (HMENU)1, instance, nullptr);
    hTextBoxDia = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"Day",
        WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_LEFT,
        100, 0, tBWH, tBHH, hWnd, (HMENU)2, instance, nullptr);
    hTextBoxMes = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"Month",
        WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER,
        200, 0, tBWH, tBHH, hWnd, (HMENU)3, instance, nullptr);
   hTextBoxProducto = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"Product",
        WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER,
        300, 0, tBWH, tBHH, hWnd, (HMENU)4, instance, nullptr);
   Boton = CreateWindowEx(0, L"BUTTON", L"Create",
       WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER,
       WH/2 -40, 40, tBWH, tBHH, hWnd, (HMENU)5, instance, nullptr);
   textoResultado = CreateWindowEx(WS_EX_TRANSPARENT, L"EDIT", L"Result",
       WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_LEFT,
       WH/2 - 40, 70, tBWH, tBHH, hWnd, (HMENU)6, instance, nullptr);

}



int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Colocar código aquí.

    // Inicializar cadenas globales
    //LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
   // LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Realizar la inicialización de la aplicación:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

    MSG msg;

    // Bucle principal de mensajes:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCIÓN: MyRegisterClass()
//
//  PROPÓSITO: Registra la clase de ventana.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wcex.lpszClassName  = szWindowClass.c_str();
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCIÓN: InitInstance(HINSTANCE, int)
//
//   PROPÓSITO: Guarda el identificador de instancia y crea la ventana principal
//
//   COMENTARIOS:
//
//        En esta función, se guarda el identificador de instancia en una variable común y
//        se crea y muestra la ventana principal del programa.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Almacenar identificador de instancia en una variable global

   HWND hWnd = CreateWindowW(szWindowClass.c_str(), szTitle.c_str(), WS_BORDER,
      CW_USEDEFAULT, 0, WH, HH, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   CrearElementos(hWnd, hInstance);
   textObtained1 = new DINAMIC();
   textObtained2 = new DINAMIC();
   textObtained3 = new DINAMIC();
   textObtained4 = new DINAMIC();
   loteFinal = new DINAMIC();
   

   return TRUE;
}


//
//  FUNCIÓN: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PROPÓSITO: Procesa mensajes de la ventana principal.
//
//  WM_COMMAND  - procesar el menú de aplicaciones
//  WM_PAINT    - Pintar la ventana principal
//  WM_DESTROY  - publicar un mensaje de salida y volver
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int retorno;
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Analizar las selecciones de menú:
            switch (wmId)
            {
            case 5:
                if (HIWORD(wParam) == BN_CLICKED) {
                    
                    GetWindowText(hTextBoxFecha, buffer, 99);
                    *textObtained1 = buffer;

                    GetWindowText(hTextBoxDia, buffer, 99);
                    *textObtained2 = buffer;

                    GetWindowText(hTextBoxProducto, buffer, 99);
                    *textObtained3 = buffer;

                    GetWindowText(hTextBoxMes, buffer, 99);
                    *textObtained4 = buffer;
                   
                    retorno = Conversion(hWnd);

                    if (retorno== 0) {
                        SetWindowText(textoResultado, loteFinal->c_str());
                     
                    }
                    else switch (retorno) {
                    case 1:
                        MessageBox(hWnd, L"Wrong product formar", L"Producto incorrecto", MB_ICONERROR);
                        break;
                    case 2:
                        MessageBox(hWnd, L"Wrong date format", L"fecha incorrecta", MB_ICONERROR);
                        break;
                    }
                }
                break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Agregar cualquier código de dibujo que use hDC aquí...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
    delete textObtained1; 
    delete textObtained2;
    delete textObtained3;
    delete textObtained4;
    delete loteFinal;
   
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Controlador de mensajes del cuadro Acerca de.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

int Conversion(HWND hWnd) {

  

    enum producto {
        COWWASHLYO = 8100,
        COWIVMLYO = 8101,
        COWIVMHEPESLYO = 8102,
        NATURARTSCOWIVMHEPESLYO = 8103,
        NATURARTSCOWIVMLYO = 8104,
        COWSUMLYO = 8105,
        COWSPERMWASHLYO = 8106,
        COWIVFLYO = 8107,
        COWIVCLYO = 8108,
        PIGWASHLYO = 9100,
        NATURARTSPIGIVMONELYO = 9101,
        NATURARTSPIGIVMTWOLYO = 9102,
        PIGSUMLYO = 9103,
        PIGIVFLYO = 9104,
        PIGIVCONELYO = 9105,
        PIGIVCTWOLYO = 9106

    };

    int codigoProducto;
    DINAMIC anio;
    int dia = std::stoi(*textObtained2);
    int mes = std::stoi(*textObtained4);
    int anioN = std::stoi(*textObtained1);
    anio = *textObtained1;
    DINAMIC ultimoDigitoAnio = std::wstring(1, anio.back());
    DINAMIC diaT;
    DINAMIC cPT;

    if (mes < 1 || mes>12) return 2;
    if (dia < 1 || dia>31) return 2;
    
    

     
    diaT = std::to_wstring(diaDelAno(dia, mes, anioN));

    if (*textObtained3 == L"COW-IVF-LYO") {
        codigoProducto = COWIVFLYO;
    }
    else if (*textObtained3 == L"COW-IVM-LYO") {
        codigoProducto = COWIVMLYO;
    }
    else if (*textObtained3 == L"COW-IVM-HEPES-LYO") {
        codigoProducto = COWIVMHEPESLYO;
    }
    else if (*textObtained3 == L"NATURARTS-COW-IVM-HEPES-LYO") {
        codigoProducto = NATURARTSCOWIVMHEPESLYO;
    }
    else if (*textObtained3 == L"NATURARTS-COW-IVM-LYO") {
        codigoProducto = NATURARTSCOWIVMLYO;
    }
    else if (*textObtained3 == L"COW-SUM-LYO") {
        codigoProducto = COWSUMLYO;
    }
    else if (*textObtained3 == L"COW-SPERM-WASH-LYO") {
        codigoProducto = COWSPERMWASHLYO;
    }
    else if (*textObtained3 == L"COW-IVF-LYO") {
        codigoProducto = COWIVFLYO;
    }
    else if (*textObtained3 == L"COW-IVC-LYO") {
        codigoProducto = COWIVCLYO;
    }
    else if (*textObtained3 == L"PIG-WASH-LYO") {
        codigoProducto = PIGWASHLYO;
    }
    else if (*textObtained3 == L"NATURARTS-PIG-IVM1-LYO") {
        codigoProducto = NATURARTSPIGIVMONELYO;
    }
    else if (*textObtained3 == L"NATURARTS-PIG-IVM2-LYO") {
        codigoProducto = NATURARTSPIGIVMTWOLYO;
    }
    else if (*textObtained3 == L"PIG-SUM-LYO") {
        codigoProducto = PIGSUMLYO;
    }
    else if (*textObtained3 == L"PIG-IVF-LYO") {
        codigoProducto = PIGIVFLYO;
    }
    else if (*textObtained3 == L"PIG-IVC1-LYO") {
        codigoProducto = PIGIVCONELYO;
    }
    else if (*textObtained3 == L"PIG-IVC2-LYO") {
        codigoProducto = PIGIVCTWOLYO;
    }
    else return 1;
 


    cPT = std::to_wstring(codigoProducto);
    *loteFinal = cPT + ultimoDigitoAnio + diaT;
   

   

    return 0;
}

bool esBisiesto(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int diaDelAno(int dia, int mes, int year) {
    std::vector<int> diasPorMes = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; 
    if (esBisiesto(year)) {
        diasPorMes[1] = 29; // Febrero tiene 29 días en un año bisiesto 
    } 
    int diaDelAno = 0; 
    for (int i = 0; i < mes - 1; ++i) { 
        diaDelAno += diasPorMes[i];
    } 
    diaDelAno += dia; 
    return diaDelAno; 
}