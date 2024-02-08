#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif
#include <Shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

#include <winrt/Windows.Storage.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::SoftwareBitmapMemoryLeak::implementation
{

    winrt::fire_and_forget MainWindow::myButton_Click(IInspectable const&, RoutedEventArgs const&)
    {
        WCHAR exePath[MAX_PATH];
        GetModuleFileNameW(NULL, exePath, MAX_PATH);
        PathRemoveFileSpecW(exePath);
        auto sampleRawFilePath = std::wstring{ exePath } + L"\\SampleRawFiles";

        auto folder = co_await Windows::Storage::StorageFolder::GetFolderFromPathAsync(sampleRawFilePath);
        auto files = co_await folder.GetFilesAsync();

        for (auto file : files)
        {
            OutputDebugStringW(file.Name().c_str());
        }
    }
}
