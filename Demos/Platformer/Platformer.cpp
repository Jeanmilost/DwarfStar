/****************************************************************************
 * ==> Platformer Demo -----------------------------------------------------*
 ****************************************************************************
 * Description : Very minimalist platformer demo                            *
 * Developer   : Jean-Milost Reymond                                        *
 ****************************************************************************
 * MIT License - DwarfStar Game Engine                                      *
 *                                                                          *
 * Permission is hereby granted, free of charge, to any person obtaining a  *
 * copy of this software and associated documentation files (the            *
 * "Software"), to deal in the Software without restriction, including      *
 * without limitation the rights to use, copy, modify, merge, publish,      *
 * distribute, sub-license, and/or sell copies of the Software, and to      *
 * permit persons to whom the Software is furnished to do so, subject to    *
 * the following conditions:                                                *
 *                                                                          *
 * The above copyright notice and this permission notice shall be included  *
 * in all copies or substantial portions of the Software.                   *
 *                                                                          *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS  *
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF               *
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.   *
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY     *
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,     *
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE        *
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                   *
 ****************************************************************************/

// std
#include <memory>

// classes
#include "Main.h"

#include "DWF_Logger.h"
#include "DWF_SceneTimer.h"
#include "DWF_OpenAL.h"

// libraries
#include <windows.h>
#include <windowsx.h>

#ifdef _DEBUG
    #define _CRTDBG_MAP_ALLOC
    #include <stdlib.h>
    #include <crtdbg.h>
#endif

//------------------------------------------------------------------------------
int APIENTRY wWinMain(_In_     HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_     LPWSTR    lpCmdLine,
    _In_     int       nCmdShow)
{
    // initialize memory leaks detection structures
    /*
    #ifdef _DEBUG
        _CrtMemState sOld;
        _CrtMemState sNew;
        _CrtMemState sDiff;

        // take a memory snapshot before execution begins
        ::_CrtMemCheckpoint(&sOld);
    #endif
    */

    // for debug purposes
    /*
    DWF_Logger::Logger::GetInstance()->Open(L"bin\\x64\\Debug\\__Log.txt");
    (*DWF_Logger::Logger::GetInstance()) << L"This is a demo message - here is a number - " << 123.456f << L"\n";
    */

    // create and run the main form
    std::unique_ptr<Main> pMain = std::make_unique<Main>();
    const int             result = pMain->Run(hInstance, nCmdShow);

    // for the debugging, force the objects to be deleted in order to better highlight memory leaks
    /*
    #ifdef _DEBUG
        pMain.reset();
        DWF_Logger::Logger::ReleaseInstance();
        DWF_Scene::Timer::ReleaseInstance();
        DWF_Audio::OpenAL::ReleaseInstance();
    #endif
    */

    // detect memory leaks, log them if found
    /*
    #ifdef _DEBUG
        // take a memory snapshot after execution ends
        ::_CrtMemCheckpoint(&sNew);

        // found a difference between memories?
        if (_CrtMemDifference(&sDiff, &sOld, &sNew))
        {
            ::OutputDebugString(L"-----------_CrtMemDumpStatistics ---------\n");
            ::_CrtMemDumpStatistics(&sDiff);
            ::OutputDebugString(L"-----------_CrtMemDumpAllObjectsSince ---------\n");
            ::_CrtMemDumpAllObjectsSince(&sOld);
            ::OutputDebugString(L"-----------_CrtDumpMemoryLeaks ---------\n");
            ::_CrtDumpMemoryLeaks();
        }
    #endif
    */

    return result;
}
//------------------------------------------------------------------------------
