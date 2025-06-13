/*
ShaderGlass: shader effect overlay
Copyright (C) 2021-2025 mausimus (mausimus.net)
https://github.com/mausimus/ShaderGlass
GNU General Public License v3.0
*/

#pragma once

#define MAX_LOADSTRING 100
#define MENU_FADE_DELAY 1000
#define CUSTOM_PARAM_SCALE 1000

#include "Options.h"
#include "CaptureManager.h"
#include "InputDialog.h"
#include "CropDialog.h"
#include "Helpers.h"

class ShaderWindow
{
public:
    ShaderWindow(CaptureManager& manager);

    bool Create(_In_ HINSTANCE hInstance, _In_ int nCmdShow);
    void Start(_In_ LPWSTR lpCmdLine, HWND paramsWindow, HWND browserWindow, HWND compileWindow);
    void CompileThreadFunc();
    HWND m_mainWindow {nullptr};

private:
    WCHAR                        m_title[MAX_LOADSTRING];
    WCHAR                        m_windowClass[MAX_LOADSTRING];
    HINSTANCE                    m_instance {nullptr};
    HWND                         m_paramsWindow {nullptr};
    HWND                         m_browserWindow {nullptr};
    HWND                         m_compileWindow {nullptr};
    UINT                         m_dpi {USER_DEFAULT_SCREEN_DPI};
    HMENU                        m_mainMenu {nullptr};
    HMENU                        m_programMenu {nullptr};
    HMENU                        m_gpuMenu {nullptr};
    HMENU                        m_shaderMenu {nullptr};
    HMENU                        m_pixelSizeMenu {nullptr};
    HMENU                        m_aspectRatioMenu {nullptr};
    HMENU                        m_outputScaleMenu {nullptr};
    HMENU                        m_frameSkipMenu {nullptr};
    HMENU                        m_flipMenu {nullptr};
    HMENU                        m_windowMenu {nullptr};
    HMENU                        m_modeMenu {nullptr};
    HMENU                        m_displayMenu {nullptr};
    HMENU                        m_outputWindowMenu {nullptr};
    HMENU                        m_inputMenu {nullptr};
    HMENU                        m_recentMenu {nullptr};
    HMENU                        m_importsMenu {nullptr};
    HMENU                        m_advancedMenu {nullptr};
    HMENU                        m_helpMenu {nullptr};
    HMENU                        m_orientationMenu {nullptr};
    std::vector<CaptureWindow>   m_captureWindows;
    std::vector<CaptureDisplay>  m_captureDisplays;
    CaptureManager&              m_captureManager;
    CaptureOptions&              m_captureOptions;
    unsigned                     m_numPresets {0};
    unsigned                     m_selectedPixelSize {0};
    unsigned                     m_selectedOutputScale {0};
    unsigned                     m_selectedAspectRatio {0};
    unsigned                     m_selectedFrameSkip {0};
    bool                         m_isTransparent {false};
    bool                         m_isBorderless {false};
    bool                         m_paramsPositioned {false};
    bool                         m_browserPositioned {false};
    HANDLE                       m_compileThread {nullptr};
    HANDLE                       m_compileEvent {nullptr};
    float                        m_dpiScale {1.0f};
    RECT                         m_lastPosition;
    std::unique_ptr<InputDialog> m_inputDialog;
    std::unique_ptr<CropDialog>  m_cropDialog;
    bool                         m_toggledNone;
    unsigned                     m_toggledPresetNo;
    std::vector<std::wstring>    m_recentProfiles;
    std::vector<std::wstring>    m_recentImports;
    std::filesystem::path        m_importPath;

    bool LoadProfile(const std::wstring& fileName);
    void LoadProfile();
    void SaveProfile(const std::wstring& fileName);
    void SaveProfile();
    void ImportShader();
    bool ImportShader(const std::wstring& fileName);
    void ScanWindows();
    void ScanDisplays();
    void CropWindow();
    void BuildProgramMenu();
    void BuildInputMenu();
    void BuildOutputMenu();
    void BuildShaderMenu();
    void SetTransparent(bool transparent);
    void AdjustWindowSize(HWND hWnd);
    void UpdateWindowState();
    void ToggleBorderless(HWND hWnd);
    bool Start();
    void Stop();
    void TryUpdateInput();
    void Screenshot();
    void LoadImage();
    void UpdateTitle();
    void SetFreeScale();
    void RegisterHotkeys();
    void UnregisterHotkeys();
    void SaveHotkeyState(bool state);
    bool GetHotkeyState();
    void SaveFlipModeState(bool state);
    bool GetFlipModeState();
    void SaveTearingState(bool state);
    bool GetTearingState();
    void SaveMaxCaptureRateState(bool state);
    bool GetMaxCaptureRateState();
    void SaveRememberFPS(int fps);
    bool RememberFPS();
    int  GetRememberFPS();
    bool GetRegistryOption(const wchar_t* name, bool default);
    void SaveRegistryOption(const wchar_t* name, bool value);
    int  GetRegistryInt(const wchar_t* name, int default);
    void SaveRegistryInt(const wchar_t* name, int value);
    void GetStartingPosition(int& x, int& y, int& w, int& h);
    void SaveStartingPosition();
    void ForgetStartingPosition();
    bool GetStartingPositionState();
    void SaveStartingPositionState(bool state);
    void SaveRecentProfiles();
    void LoadRecentProfiles();
    void AddRecentProfile(const std::wstring& path);
    void RemoveRecentProfile(const std::wstring& path);
    void SaveRecentImports();
    void LoadRecentImports();
    void AddRecentImport(const std::wstring& path);
    void RemoveRecentImport(const std::wstring& path);
    void UpdateGPUName();
    std::wstring GetDefaultPath() const;
    void SaveDefault();
    void RemoveDefault();
    bool LoadDefault();
    bool ScaleLocked() const;

    static BOOL CALLBACK    EnumWindowsProcProxy(_In_ HWND hwnd, _In_ LPARAM lParam);
    static BOOL CALLBACK    EnumDisplayMonitorsProcProxy(_In_ HMONITOR hMonitor, _In_ HDC hDC, _In_ LPRECT lpRect, _In_ LPARAM lParam);
    static LRESULT CALLBACK WndProcProxy(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    ATOM                    MyRegisterClass(HINSTANCE hInstance);
    BOOL                    InitInstance(HINSTANCE hInstance, int nCmdShow);
    BOOL CALLBACK           EnumWindowsProc(_In_ HWND hwnd, _In_ LPARAM lParam);
    BOOL CALLBACK           EnumDisplayMonitorsProc(_In_ HMONITOR hMonitor, _In_ HDC hDC, _In_ LPRECT lpRect, _In_ LPARAM lParam);
    LRESULT CALLBACK        WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};