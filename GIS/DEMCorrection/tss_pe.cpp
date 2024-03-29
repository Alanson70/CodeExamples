// $Id: tss_pe.cpp 49324 2008-10-13 20:30:13Z anthonyw $
// (C) Copyright Aaron W. LaFramboise, Roland Schwarz, Michael Glassford 2004.
// (C) Copyright 2007 Roland Schwarz
// (C) Copyright 2007 Anthony Williams
// (C) Copyright 2007 David Deakins
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "StdAfx.h"

#define BOOST_ALL_NO_LIB
#define BOOST_THREAD_BUILD_LIB

#include <boost/thread/detail/config.hpp>

#if defined(BOOST_HAS_WINTHREADS) && defined(BOOST_THREAD_BUILD_LIB) 

#if defined(__MINGW32__) && !defined(_WIN64)

#include <boost/thread/detail/tss_hooks.hpp>

#include <windows.h>

#include <cstdlib>

extern "C" void tss_cleanup_implemented(void) {}

namespace {
    void NTAPI on_tls_callback(void* h, DWORD dwReason, PVOID pv)
    {
        switch (dwReason)
        {
        case DLL_THREAD_DETACH:
        {
            on_thread_exit();
            break;
        }
        }
    }

    void on_after_ctors(void)
    {
        on_process_enter();
    }
    
    void on_before_dtors(void)
    {
        on_thread_exit();
    }
    
    void on_after_dtors(void)
    {
        on_process_exit();        
    }
}

extern "C" {

    void (* after_ctors )(void) __attribute__((section(".ctors")))     = on_after_ctors;
    void (* before_dtors)(void) __attribute__((section(".dtors")))     = on_before_dtors;
    void (* after_dtors )(void) __attribute__((section(".dtors.zzz"))) = on_after_dtors;

    ULONG __tls_index__ = 0;
    char __tls_end__ __attribute__((section(".tls$zzz"))) = 0;
    char __tls_start__ __attribute__((section(".tls"))) = 0;


    PIMAGE_TLS_CALLBACK __crt_xl_start__ __attribute__ ((section(".CRT$XLA"))) = 0;
    PIMAGE_TLS_CALLBACK __crt_xl_tls_callback__ __attribute__ ((section(".CRT$XLB"))) = on_tls_callback;
    PIMAGE_TLS_CALLBACK __crt_xl_end__ __attribute__ ((section(".CRT$XLZ"))) = 0;
}

extern "C" const IMAGE_TLS_DIRECTORY32 _tls_used __attribute__ ((section(".rdata$T"))) =
{
        (DWORD) &__tls_start__,
        (DWORD) &__tls_end__,
        (DWORD) &__tls_index__,
        (DWORD) (&__crt_xl_start__+1),
        (DWORD) 0,
        (DWORD) 0
};


#elif  defined(_MSC_VER) && !defined(UNDER_CE)

    #include <boost/thread/detail/tss_hooks.hpp>

    #include <stdlib.h>

    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>

    //Definitions required by implementation

    #if (_MSC_VER < 1300) // 1300 == VC++ 7.0
        typedef void (__cdecl *_PVFV)(void);
        #define INIRETSUCCESS
        #define PVAPI void
    #else
        typedef int (__cdecl *_PVFV)(void);
        #define INIRETSUCCESS 0
        #define PVAPI int
    #endif

    typedef void (NTAPI* _TLSCB)(HINSTANCE, DWORD, PVOID);

    //Symbols for connection to the runtime environment

    extern "C"
    {
        extern DWORD _tls_used; //the tls directory (located in .rdata segment)
        extern _TLSCB __xl_a[], __xl_z[];    //tls initializers */
    }

    namespace
    {
        //Forward declarations

        static PVAPI on_tls_prepare(void);
        static PVAPI on_process_init(void);
        static PVAPI on_process_term(void);
        static void NTAPI on_tls_callback(HINSTANCE, DWORD, PVOID);

        //The .CRT$Xxx information is taken from Codeguru:
        //http://www.codeguru.com/Cpp/misc/misc/threadsprocesses/article.php/c6945__2/

#if (_MSC_VER >= 1400)
#pragma section(".CRT$XIU",long,read)
#pragma section(".CRT$XCU",long,read)
#pragma section(".CRT$XTU",long,read)
#pragma section(".CRT$XLC",long,read)
        __declspec(allocate(".CRT$XLC")) _TLSCB __xl_ca=on_tls_callback;
        __declspec(allocate(".CRT$XIU"))_PVFV p_tls_prepare = on_tls_prepare;
        __declspec(allocate(".CRT$XCU"))_PVFV p_process_init = on_process_init;
        __declspec(allocate(".CRT$XTU"))_PVFV p_process_term = on_process_term;
#else
        #if (_MSC_VER >= 1300) // 1300 == VC++ 7.0
        #   pragma data_seg(push, old_seg)
        #endif
            //Callback to run tls glue code first.
            //I don't think it is necessary to run it
            //at .CRT$XIB level, since we are only
            //interested in thread detachement. But
            //this could be changed easily if required.

            #pragma data_seg(".CRT$XIU")
            static _PVFV p_tls_prepare = on_tls_prepare;
            #pragma data_seg()

            //Callback after all global ctors.

            #pragma data_seg(".CRT$XCU")
            static _PVFV p_process_init = on_process_init;
            #pragma data_seg()

            //Callback for tls notifications.

            #pragma data_seg(".CRT$XLB")
            _TLSCB p_thread_callback = on_tls_callback;
            #pragma data_seg()
            //Callback for termination.

            #pragma data_seg(".CRT$XTU")
            static _PVFV p_process_term = on_process_term;
            #pragma data_seg()
        #if (_MSC_VER >= 1300) // 1300 == VC++ 7.0
        #   pragma data_seg(pop, old_seg)
        #endif
#endif

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable:4189)
#endif

        PVAPI on_tls_prepare(void)
        {
            //The following line has an important side effect:
            //if the TLS directory is not already there, it will
            //be created by the linker. In other words, it forces a tls
            //directory to be generated by the linker even when static tls
            //(i.e. __declspec(thread)) is not used.
            //The volatile should prevent the optimizer
            //from removing the reference.

            DWORD volatile dw = _tls_used;

            #if (_MSC_VER < 1300) // 1300 == VC++ 7.0
                _TLSCB* pfbegin = __xl_a;
                _TLSCB* pfend = __xl_z;
                _TLSCB* pfdst = pfbegin;
                //pfdst = (_TLSCB*)_tls_used.AddressOfCallBacks;

                //The following loop will merge the address pointers
                //into a contiguous area, since the tlssup code seems
                //to require this (at least on MSVC 6)

                while (pfbegin < pfend)
                {
                    if (*pfbegin != 0)
                    {
                        *pfdst = *pfbegin;
                        ++pfdst;
                    }
                    ++pfbegin;
                }

                *pfdst = 0;
            #endif

            return INIRETSUCCESS;
        }
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

        PVAPI on_process_init(void)
        {
            //Schedule on_thread_exit() to be called for the main
            //thread before destructors of global objects have been
            //called.

            //It will not be run when 'quick' exiting the
            //library; however, this is the standard behaviour
            //for destructors of global objects, so that
            //shouldn't be a problem.

            atexit(on_thread_exit);

            //Call Boost process entry callback here

            on_process_enter();

            return INIRETSUCCESS;
        }

        PVAPI on_process_term(void)
        {
            on_process_exit();
            return INIRETSUCCESS;
        }

        void NTAPI on_tls_callback(HINSTANCE /*h*/, DWORD dwReason, PVOID /*pv*/)
        {
            switch (dwReason)
            {
            case DLL_THREAD_DETACH:
                on_thread_exit();
                break;
            }
        }

        BOOL WINAPI dll_callback(HANDLE, DWORD dwReason, LPVOID)
        {
            switch (dwReason)
            {
            case DLL_THREAD_DETACH:
                on_thread_exit();
                break;
            case DLL_PROCESS_DETACH:
                on_process_exit();
                break;
            }
            return true;
        }
    } //namespace

extern "C"
{
    // extern BOOL (WINAPI * const _pRawDllMain)(HANDLE, DWORD, LPVOID)=&dll_callback;
}

    extern "C" void tss_cleanup_implemented(void)
    {
        /*
        This function's sole purpose is to cause a link error in cases where
        automatic tss cleanup is not implemented by Boost.Threads as a
        reminder that user code is responsible for calling the necessary
        functions at the appropriate times (and for implementing an a
        tss_cleanup_implemented() function to eliminate the linker's
        missing symbol error).

        If Boost.Threads later implements automatic tss cleanup in cases
        where it currently doesn't (which is the plan), the duplicate
        symbol error will warn the user that their custom solution is no
        longer needed and can be removed.
        */
    }
#endif //defined(_MSC_VER) && !defined(UNDER_CE)

#endif //defined(BOOST_HAS_WINTHREADS) && defined(BOOST_THREAD_BUILD_LIB)
