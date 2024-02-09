This is a sample app demonstrating a memory leak when CR2 files are decoded with the Windows::Graphics::Imaging::BitmapDecoder. Note this test app uses Windows App SDK/WinUI3.

Check out MainWindow.xaml.cpp for the code producing the memory leak.

## Repro Instructions

1. Clone the repo and open SoftwareBitmapMemoryLeak.sln.
2. Build solution in x64, release or debug.
3. Launch the test app. You may need to restart Visual Studio for this step to work. I reproduced the issue without a debugger attached.
4. Observe the memory usage SoftwareBitmapMemoryLeak.exe in your process monitor of choice, eg. Task Manager.
5. Click the red button, feel free to spam it a bunch of times. Let the memory usage settle and observe it has permanently increased since step 4.

If I switch the sample folder to use 100MB PNG files, this leak doesn't repro.
