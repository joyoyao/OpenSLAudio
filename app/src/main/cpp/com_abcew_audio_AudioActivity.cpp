/* DO NOT EDIT THIS FILE - it is machine generated */
#include <SLES/OpenSLES.h>
#include "com_abcew_audio_AudioActivity.h"
// engine interfaces

namespace BAudio {




    static SLObjectItf engineObject2 = NULL;
    static SLEngineItf engineEngine2;

// output mix interfaces
    static SLObjectItf outputMixObject2 = NULL;

// URI player interfaces
    static SLObjectItf uriPlayerObject2 = NULL;
    static SLPlayItf uriPlayerPlay2;
    static SLSeekItf uriPlayerSeek2;
    static SLMuteSoloItf uriPlayerMuteSolo2;
    static SLVolumeItf uriPlayerVolume2;


    JNIEXPORT void JNICALL Java_com_abcew_audio_AudioActivity_createEngine
            (JNIEnv *env, jclass thiz) {
        SLresult result;
        // create engine
        result = slCreateEngine(&engineObject2, 0, NULL, 0, NULL, NULL);
        assert(SL_RESULT_SUCCESS == result);
        (void) result;

        // realize the engine
        result = (*engineObject2)->Realize(engineObject2, SL_BOOLEAN_FALSE);
        assert(SL_RESULT_SUCCESS == result);
        (void) result;

        // get the engine interface, which is needed in order to create other objects
        result = (*engineObject2)->GetInterface(engineObject2, SL_IID_ENGINE, &engineEngine2);
        assert(SL_RESULT_SUCCESS == result);
        (void) result;

        // create output mix
        result = (*engineEngine2)->CreateOutputMix(engineEngine2, &outputMixObject2, 0, 0, 0);
        assert(SL_RESULT_SUCCESS == result);
        (void) result;

        // realize the output mix
        result = (*outputMixObject2)->Realize(outputMixObject2, SL_BOOLEAN_FALSE);
        assert(SL_RESULT_SUCCESS == result);
        (void) result;

    }

/*
 * Class:     com_abcew_audio_AudioActivity
 * Method:    createUriAudioPlayer
 * Signature: (Ljava/lang/String;)Z
 */
    JNIEXPORT jboolean JNICALL Java_com_abcew_audio_AudioActivity_createUriAudioPlayer
            (JNIEnv *env, jclass thiz, jstring uri) {

        SLresult result;
        const char *utf8Uri = env->GetStringUTFChars(uri, NULL);

        if (utf8Uri == NULL) {
            return false;
        }


        SLDataLocator_URI loc_uri = {SL_DATALOCATOR_URI, (SLchar *) utf8Uri};
        SLDataFormat_MIME format_mime = {SL_DATAFORMAT_MIME, NULL,
                                         SL_CONTAINERTYPE_UNSPECIFIED};
        SLDataSource audioSrc = {&loc_uri, &format_mime};

        // configure audio sink
        SLDataLocator_OutputMix loc_outmix = {SL_DATALOCATOR_OUTPUTMIX, outputMixObject2};
        SLDataSink audioSnk = {&loc_outmix, NULL};

        // create audio player
        const SLInterfaceID ids[3] = {SL_IID_SEEK, SL_IID_MUTESOLO, SL_IID_VOLUME};
        const SLboolean req[3] = {SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE};
        result = (*engineEngine2)->CreateAudioPlayer(engineEngine2, &uriPlayerObject2, &audioSrc,
                                                    &audioSnk, 3, ids, req);
        // note that an invalid URI is not detected here, but during prepare/prefetch on Android,
        // or possibly during Realize on other platforms
        assert(SL_RESULT_SUCCESS == result);
        (void) result;

        // realize the player
        result = (*uriPlayerObject2)->Realize(uriPlayerObject2, SL_BOOLEAN_FALSE);
        // this will always succeed on Android, but we check result for portability to other platforms
        if (SL_RESULT_SUCCESS != result) {
            (*uriPlayerObject2)->Destroy(uriPlayerObject2);
            uriPlayerObject2 = NULL;
            return JNI_FALSE;
        }

        // get the play interface
        result = (*uriPlayerObject2)->GetInterface(uriPlayerObject2, SL_IID_PLAY, &uriPlayerPlay2);
        assert(SL_RESULT_SUCCESS == result);
        (void) result;

        // get the seek interface
        result = (*uriPlayerObject2)->GetInterface(uriPlayerObject2, SL_IID_SEEK, &uriPlayerSeek2);

        assert(SL_RESULT_SUCCESS == result);
        (void) result;

        // get the mute/solo interface
        result = (*uriPlayerObject2)->GetInterface(uriPlayerObject2, SL_IID_MUTESOLO,
                                                  &uriPlayerMuteSolo2);
        assert(SL_RESULT_SUCCESS == result);
        (void) result;

        // get the volume interface
        result = (*uriPlayerObject2)->GetInterface(uriPlayerObject2, SL_IID_VOLUME, &uriPlayerVolume2);
        assert(SL_RESULT_SUCCESS == result);
        (void) result;

        env->ReleaseStringUTFChars(uri, utf8Uri);
        return true;

    }

/*
 * Class:     com_abcew_audio_AudioActivity
 * Method:    setPlayingUriAudioPlayer
 * Signature: (Z)V
 */
    JNIEXPORT void JNICALL Java_com_abcew_audio_AudioActivity_setPlayingUriAudioPlayer
            (JNIEnv *env, jclass thiz, jboolean isPlaying) {

        SLresult result;
        // make sure the URI audio player was created
        if (uriPlayerPlay2 != NULL) {
            // set the player's state
            result = (*uriPlayerPlay2)->SetPlayState(uriPlayerPlay2, isPlaying ? SL_PLAYSTATE_PLAYING
                                                                             : SL_PLAYSTATE_PAUSED);
            assert(SL_RESULT_SUCCESS == result);
        }

    }

/*
 * Class:     com_abcew_audio_AudioActivity
 * Method:    setChannelMuteUriAudioPlayer
 * Signature: (IZ)V
 */
    JNIEXPORT void JNICALL Java_com_abcew_audio_AudioActivity_setChannelMuteUriAudioPlayer
            (JNIEnv *env, jclass thiz, jint channel, jboolean mute) {
        SLresult result;
        if (uriPlayerMuteSolo2 != NULL) {
            result = (*uriPlayerMuteSolo2)->SetChannelMute(uriPlayerMuteSolo2, channel, mute);
            assert(SL_RESULT_SUCCESS == result);
        }
    }

/*
 * Class:     com_abcew_audio_AudioActivity
 * Method:    setChannelSoloUriAudioPlayer
 * Signature: (IZ)V
 */
    JNIEXPORT void JNICALL Java_com_abcew_audio_AudioActivity_setChannelSoloUriAudioPlayer
            (JNIEnv *env, jclass thiz, jint channel, jboolean solo) {
        SLresult result;
        if (uriPlayerMuteSolo2 != NULL) {
            result = (*uriPlayerMuteSolo2)->SetChannelSolo(uriPlayerMuteSolo2, channel, solo);
            assert(SL_RESULT_SUCCESS == result);
        }
    }

/*
 * Class:     com_abcew_audio_AudioActivity
 * Method:    getNumChannelsUriAudioPlayer
 * Signature: ()I
 */
    JNIEXPORT jint JNICALL Java_com_abcew_audio_AudioActivity_getNumChannelsUriAudioPlayer
            (JNIEnv *env, jclass thiz) {

        SLresult result;
        if (uriPlayerMuteSolo2 != NULL) {
            SLuint8 chanelNumbes;
            result = (*uriPlayerMuteSolo2)->GetNumChannels(uriPlayerMuteSolo2, &chanelNumbes);
            assert(SL_RESULT_SUCCESS == result);
            if (result == SL_RESULT_SUCCESS) {
                return chanelNumbes;
            }
        }
        return 0;

    }

/*
 * Class:     com_abcew_audio_AudioActivity
 * Method:    setVolumeUriAudioPlayer
 * Signature: (I)V
 */
    JNIEXPORT void JNICALL Java_com_abcew_audio_AudioActivity_setVolumeUriAudioPlayer
            (JNIEnv *env, jclass thiz, jint index) {

        SLresult result;

        if (NULL != uriPlayerVolume2) {
            SLmillibel value;
            result = (*uriPlayerVolume2)->GetMaxVolumeLevel(uriPlayerVolume2, &value);
            if (result == SL_RESULT_SUCCESS) {
            }

            result = (*uriPlayerVolume2)->SetVolumeLevel(uriPlayerVolume2, index);
            assert(SL_RESULT_SUCCESS == result);
        }

    }

/*
 * Class:     com_abcew_audio_AudioActivity
 * Method:    setMuteUriAudioPlayer
 * Signature: (Z)V
 */
    JNIEXPORT void JNICALL Java_com_abcew_audio_AudioActivity_setMuteUriAudioPlayer
            (JNIEnv *env, jclass thiz, jboolean mute) {
        SLresult result;
        if (NULL != uriPlayerVolume2) {
            result = (*uriPlayerVolume2)->SetMute(uriPlayerVolume2, mute);
            assert(SL_RESULT_SUCCESS == result);
        }

    }

/*
 * Class:     com_abcew_audio_AudioActivity
 * Method:    enableStereoPositionUriAudioPlayer
 * Signature: (Z)V
 */
    JNIEXPORT void JNICALL Java_com_abcew_audio_AudioActivity_enableStereoPositionUriAudioPlayer
            (JNIEnv *env, jclass thiz, jboolean jboolean1) {

    }

/*
 * Class:     com_abcew_audio_AudioActivity
 * Method:    setStereoPositionUriAudioPlayer
 * Signature: (I)V
 */
    JNIEXPORT void JNICALL Java_com_abcew_audio_AudioActivity_setStereoPositionUriAudioPlayer
            (JNIEnv *env, jclass thiz, jint jint1) {

    }


/*
 * Class:     com_abcew_audio_AudioActivity
 * Method:    shutdown
 * Signature: ()V
 */
    JNIEXPORT void JNICALL Java_com_abcew_audio_AudioActivity_shutdown
            (JNIEnv *env, jclass thiz) {

        // destroy URI audio player object, and invalidate all associated interfaces
        if (uriPlayerObject2 != NULL) {
            (*uriPlayerObject2)->Destroy(uriPlayerObject2);
            uriPlayerObject2 = NULL;
            uriPlayerPlay2 = NULL;
            uriPlayerSeek2 = NULL;
            uriPlayerMuteSolo2 = NULL;
            uriPlayerVolume2 = NULL;
        }

        // destroy output mix object, and invalidate all associated interfaces
        if (outputMixObject2 != NULL) {
            (*outputMixObject2)->Destroy(outputMixObject2);
            outputMixObject2 = NULL;
        }

        // destroy engine object, and invalidate all associated interfaces
        if (engineObject2 != NULL) {
            (*engineObject2)->Destroy(engineObject2);
            engineObject2 = NULL;
            engineEngine2 = NULL;
        }

    }

}
