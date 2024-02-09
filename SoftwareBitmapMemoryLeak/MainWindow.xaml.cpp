#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif
#include <Shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Graphics.Imaging.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::SoftwareBitmapMemoryLeak::implementation
{

    winrt::fire_and_forget MainWindow::myButton_Click(IInspectable const&, RoutedEventArgs const&)
    {
        DescriptionText().Text(L"Decode test is running...");

        WCHAR exePath[MAX_PATH];
        GetModuleFileNameW(NULL, exePath, MAX_PATH);
        PathRemoveFileSpecW(exePath);
        auto sampleRawFilePath = std::wstring{ exePath } + L"\\SampleRawFiles";

        auto folder = co_await Windows::Storage::StorageFolder::GetFolderFromPathAsync(sampleRawFilePath);
        auto files = co_await folder.GetFilesAsync();

        for (auto file : files)
        {
            Windows::Graphics::Imaging::SoftwareBitmap bitmap = nullptr;
            Windows::Storage::Streams::IRandomAccessStream fileStream = nullptr;

            try
            {
                fileStream = co_await file.OpenAsync(Windows::Storage::FileAccessMode::Read);
                auto decoder = co_await Windows::Graphics::Imaging::BitmapDecoder::CreateAsync(fileStream);
                if (decoder != nullptr)
                {
                    bitmap = co_await decoder.GetSoftwareBitmapAsync();
                    bitmap.Close();
                }
                fileStream.Close();
            }
            catch (...)
            {
                if (bitmap != nullptr)
                {
                    bitmap.Close();
                }

                if (fileStream != nullptr)
                {
                    fileStream.Close();
                }
            }
        }

        DescriptionText().Text(L"Decode test is finished. The process memory should settle after a few seconds. \nClick the button again and you should see the process memory permanently increase with each subsequent run.");
    }
}
