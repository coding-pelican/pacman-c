/**
 * @file audio_winmm.c
 * @author Gyeongtae Kim(dev-dasae) <codingpelican@gmail.com>
 *
 * @brief This file contains the definition of audio related functions.
 * @details This file contains the definition of audio related functions.
 *
 * @version 0.1
 * @date 2024-06-12
 *
 * @copyright Copyright 2024. Gyeongtae Kim All rights reserved.
 */


#if defined(_WIN32) || defined(_WIN64)

// #region Header_Inclusions
#  include "audio.h"

#  include <wchar.h>

#  if !defined(_WINDOWS_)
#    include <windows.h>
#  endif // !defined(_WINDOWS_)

#  include <mmsystem.h>

#  if defined(_MSC_VER)
#    pragma comment(lib, "winmm.lib")
#  elif defined(__has_include)
#    if __has_include(<windows.h>) && __has_include(<mmsystem.h>)
#      if !defined(PlaySound)
#        error "The 'winmm' library is not linked. Please link it manually. '-lWINMM'"
#      endif // !defined(PlaySound)
#    else // !(__has_include(<windows.h>) && __has_include(<mmsystem.h>))
#      error "The required header files are missing. Please include them and link the 'winmm' library manually. '-lWINMM'"
#    endif // __has_include(<windows.h>) && __has_include(<mmsystem.h>)
#  else // !defined(__has_include)
#    pragma message("Cannot determine if the 'winmm' library is linked. Please ensure it is linked manually. '-lWINMM'")
#  endif // defined(_MSC_VER)

#  include <Digitalv.h>
// #endregion // Header_Inclusions

// #region Private_Data
static MCIDEVICEID s_deviceID                  = 0;
static MCIDEVICEID s_shotDeviceID              = 0;
static wchar_t     s_audioSource[MAX_PATH]     = { 0 };
static wchar_t     s_shotAudioSource[MAX_PATH] = { 0 };
static bool        s_isRepeat                  = false;
// #endregion // Private_Data

// #region Public_Functions
bool Audio_Init() {
    s_deviceID           = 0;
    s_shotDeviceID       = 0;
    s_audioSource[0]     = '\0';
    s_shotAudioSource[0] = '\0';
    s_isRepeat           = false;
    return true;
}

bool Audio_Play(wchar_t const* audioFile) {
    wchar_t fullAudioPath[MAX_PATH] = { 0 };
    GetFullPathNameW(audioFile, MAX_PATH, fullAudioPath, NULL);

    MCI_OPEN_PARMSW openParams  = { 0 };
    openParams.lpstrElementName = fullAudioPath;
    openParams.lpstrDeviceType  = L"mpegvideo";

    MCIERROR err = mciSendCommandW(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD_PTR)&openParams);
    if (err == 0) {
        s_deviceID = openParams.wDeviceID;
        wcsncpy(s_audioSource, fullAudioPath, MAX_PATH);
        MCI_PLAY_PARMS playParams = { 0 };
        playParams.dwCallback     = 0;
        playParams.dwFrom         = 0;
        err                       = mciSendCommand(s_deviceID, MCI_PLAY, MCI_FROM | (s_isRepeat ? MCI_DGV_PLAY_REPEAT : 0), (DWORD_PTR)&playParams);
        return (err == 0);
    }
    return false;
}

bool Audio_Pause() {
    MCIERROR err = mciSendCommand(s_deviceID, MCI_PAUSE, 0, 0);
    return (err == 0);
}

bool Audio_Resume() {
    MCIERROR err = mciSendCommand(s_deviceID, MCI_RESUME, 0, 0);
    return (err == 0);
}

bool Audio_Stop() {
    MCIERROR err = mciSendCommand(s_deviceID, MCI_STOP, 0, 0);
    if (err != 0) {
        // Handle error
        mciSendCommand(s_deviceID, MCI_CLOSE, 0, 0);
        return false;
    }
    err = mciSendCommand(s_deviceID, MCI_CLOSE, 0, 0);
    return (err == 0);
}

wchar_t const* Audio_GetSource() {
    return s_audioSource;
}

bool Audio_IsPlaying() {
    MCI_STATUS_PARMS statusParams = { 0 };
    statusParams.dwItem           = MCI_STATUS_MODE;
    MCIERROR err                  = mciSendCommand(s_deviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD_PTR)&statusParams);
    return (err == 0 && statusParams.dwReturn == MCI_MODE_PLAY);
}

bool Audio_SetRepeat(bool repeat) {
    s_isRepeat = repeat;
    return true;
}

bool Audio_IsRepeat() {
    return s_isRepeat;
}

bool Audio_PlayOneShot(wchar_t const* audioFile) {
    wchar_t fullAudioPath[MAX_PATH] = { 0 };
    GetFullPathNameW(audioFile, MAX_PATH, fullAudioPath, NULL);

    MCI_OPEN_PARMSW openParams  = { 0 };
    openParams.lpstrElementName = fullAudioPath;
    openParams.lpstrDeviceType  = L"mpegvideo";
    MCIERROR err                = mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD_PTR)&openParams);
    if (err == 0) {
        s_shotDeviceID = openParams.wDeviceID;
        wcsncpy(s_shotAudioSource, fullAudioPath, MAX_PATH);
        MCI_PLAY_PARMS playParams = { 0 };
        playParams.dwCallback     = 0;
        playParams.dwFrom         = 0;
        err                       = mciSendCommand(s_shotDeviceID, MCI_PLAY, MCI_FROM, (DWORD_PTR)&playParams);
        return (err == 0);
    }
    return false;
}

bool Audio_PauseOneShot() {
    MCIERROR err = mciSendCommand(s_shotDeviceID, MCI_PAUSE, 0, 0);
    return (err == 0);
}

bool Audio_ResumeOneShot() {
    MCIERROR err = mciSendCommand(s_shotDeviceID, MCI_RESUME, 0, 0);
    return (err == 0);
}

bool Audio_StopOneShot() {
    MCIERROR err = mciSendCommand(s_deviceID, MCI_STOP, 0, 0);
    if (err != 0) {
        // Handle error
        mciSendCommand(s_deviceID, MCI_CLOSE, 0, 0);
        return false;
    }
    err = mciSendCommand(s_deviceID, MCI_CLOSE, 0, 0);
    return (err == 0);
}

wchar_t const* Audio_GetShotting() {
    return s_shotAudioSource;
}

bool Audio_IsShotting() {
    MCI_STATUS_PARMS statusParams = { 0 };
    statusParams.dwItem           = MCI_STATUS_MODE;
    MCIERROR err                  = mciSendCommand(s_shotDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD_PTR)&statusParams);
    return (err == 0 && statusParams.dwReturn == MCI_MODE_PLAY);
}
// #endregion // Public_Functions

#endif // defined(_WIN32) || defined(_WIN64)
