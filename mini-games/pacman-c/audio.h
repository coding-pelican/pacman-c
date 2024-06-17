/**
 * @file audio.h
 * @author Gyeongtae Kim(dev-dasae) <codingpelican@gmail.com>
 *
 * @brief This file contains the declaration of audio related functions.
 * @details This file contains the declaration of audio related functions.
 *
 * @version 0.1
 * @date 2024-06-12
 *
 * @copyright Copyright 2024. Gyeongtae Kim All rights reserved.
 */


#ifndef AUDIO_H
#define AUDIO_H

#if defined(__cplusplus)
extern "C" {
#endif // defined(__cplusplus)

// #region Header_Inclusions
#include <stdbool.h>
#include <stddef.h>
// #endregion // Header_Inclusions

// #region Public_Function_Prototypes
bool           Audio_Init();
bool           Audio_Play(wchar_t const* audioFile);
bool           Audio_Pause();
bool           Audio_Resume();
bool           Audio_Stop();
wchar_t const* Audio_GetSource();
bool           Audio_IsPlaying();
bool           Audio_SetRepeat(bool repeat);
bool           Audio_IsRepeat();
bool           Audio_PlayOneShot(wchar_t const* audioFile);
bool           Audio_PauseOneShot();
bool           Audio_ResumeOneShot();
bool           Audio_StopOneShot();
wchar_t const* Audio_GetShotting();
bool           Audio_IsShotting();
// #endregion // Public_Function_Prototypes

#if defined(__cplusplus)
}
#endif // defined(__cplusplus)

#endif // !AUDIO_H
