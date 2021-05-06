#ifndef _YLPLAYER_H_
#define _YLPLAYER_H_

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <ctype.h>
#include <errno.h>
#include <sys/select.h>

#include "iniparserapi.h"

#include "cdx_config.h"
#include <cdx_log.h>
#include "xplayer.h"
#include "CdxTypes.h"
#include "memoryAdapter.h"
#include "deinterlace.h"

#define STATUS_STOPPED 0
#define STATUS_PREPARING 1
#define STATUS_PREPARED 2
#define STATUS_PLAYING 3
#define STATUS_PAUSED 4
#define STATUS_SEEKING 5

extern "C"{
    extern SoundCtrl* SoundDeviceCreate();
    extern SubCtrl* SubtitleCreate();
    extern Deinterlace* DeinterlaceCreate();
    extern LayerCtrl* LayerCreate_DE();
}

struct PlayerContext
{
    XPlayer* mAwPlayer;
    int             mPreStatus;
    int             mStatus;
    int             mSeekable;
    int             mError;
    pthread_mutex_t mMutex;
    int             mVideoFrameNum;
};

//typedef struct playerContext PlayerContext;


int set_source_url(PlayerContext* player, char* url);
int player_start(PlayerContext* player);
int player_stop(PlayerContext* player);
PlayerContext* player_init();
void player_uninit(PlayerContext* player);

void player_demo();


#endif