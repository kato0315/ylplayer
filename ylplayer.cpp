#include "ylplayer.h"

#include <unistd.h>


static int callback_for_AwPlayer(void* pUserData, int msg, int ext1, void* param)
{
    PlayerContext* player = (PlayerContext*)pUserData;

    switch (msg)
    {
    case AWPLAYER_MEDIA_INFO:
    {
        switch (ext1)
        {
        case AW_MEDIA_INFO_NOT_SEEKABLE:
        {
            player->mSeekable = 0;
            printf("info: media source is unseekable.\n");
            break;
        }
        case AW_MEDIA_INFO_RENDERING_START:
        {
            printf("info: start to show pictures.\n");
            break;
        }
        }
        break;
    }

    case AWPLAYER_MEDIA_ERROR:
    {
        pthread_mutex_lock(&player->mMutex);
        player->mStatus = STATUS_STOPPED;
        player->mPreStatus = STATUS_STOPPED;
        printf("error: open media source fail.\n");
        pthread_mutex_unlock(&player->mMutex);
        player->mError = 1;

        loge(" error : how to deal with it");
        break;
    }

    case AWPLAYER_MEDIA_PREPARED:
    {
        logd("info : preared");
        player->mPreStatus = player->mStatus;
        player->mStatus = STATUS_PREPARED;
        printf("info: prepare ok.\n");
        break;
    }

    case AWPLAYER_MEDIA_BUFFERING_UPDATE:
    {
        int nTotalPercentage;
        int nBufferPercentage;
        int nLoadingPercentage;

        nTotalPercentage = ((int*)param)[0];   //* read positon to total file size.
        nBufferPercentage = ((int*)param)[1];   //* cache buffer fullness.
        nLoadingPercentage = ((int*)param)[2];   //* loading percentage to start play.

        break;
    }

    case AWPLAYER_MEDIA_PLAYBACK_COMPLETE:
    {
        //* stop the player.
        //* TODO
        break;
    }

    case AWPLAYER_MEDIA_SEEK_COMPLETE:
    {
        pthread_mutex_lock(&player->mMutex);
        player->mStatus = player->mPreStatus;
        printf("info: seek ok.\n");
        pthread_mutex_unlock(&player->mMutex);
        break;
    }
    case AWPLAYER_MEDIA_SET_VIDEO_SIZE:
    {
        int w, h;
        w = ((int*)param)[0];   //* read positon to total file size.
        h = ((int*)param)[1];   //* cache buffer fullness.
        printf("++++ video width: %d, height: %d \n", w, h);
        break;
    }

    default:
    {
        //printf("warning: unknown callback from AwPlayer.\n");
        break;
    }
    }

    return 0;
}

int set_source_url(PlayerContext* player, char* url)
{
    player->mSeekable = 1;

    if (XPlayerSetDataSourceUrl(player->mAwPlayer,
        (const char*)url, NULL, NULL) != 0)
    {
        printf("error:\n");
        printf("    AwPlayer::setDataSource() return fail.\n");
        return -1;
    }

    //* start preparing.
    pthread_mutex_lock(&player->mMutex);
    if (XPlayerPrepareAsync(player->mAwPlayer) != 0)
    {
        printf("error:\n");
        printf("    AwPlayer::prepareAsync() return fail.\n");
        pthread_mutex_unlock(&player->mMutex);
        return -1;
    }


    player->mPreStatus = STATUS_STOPPED;
    player->mStatus = STATUS_PREPARING;
    pthread_mutex_unlock(&player->mMutex);

    return 0;
}

int player_start(PlayerContext* player)
{
    if (XPlayerStart(player->mAwPlayer) != 0)
    {
        printf("error:\n");
        printf("    AwPlayer::start() return fail.\n");
        return -1;
    }
    player->mPreStatus = player->mStatus;
    player->mStatus = STATUS_PLAYING;
 
    return 0;
}

int player_stop(PlayerContext* player)
{
    if (XPlayerReset(player->mAwPlayer) != 0)
    {
        printf("error:\n");
        printf("    AwPlayer::reset() return fail.\n");
        return -1;
    }
    player->mPreStatus = player->mStatus;
    player->mStatus = STATUS_STOPPED;
   
    return 0;
}

PlayerContext* player_init()
{
    //创建播放器
    PlayerContext* player;
    player = (PlayerContext*)malloc(sizeof(PlayerContext));
    
    pthread_mutex_init(&player->mMutex, NULL); //创建互斥锁
    player->mAwPlayer = XPlayerCreate();
    if (player->mAwPlayer == NULL)
    {
        printf("can not create AwPlayer,quit.\n");
        return NULL;
    }

    //设置回调函数
    XPlayerSetNotifyCallback(player->mAwPlayer, callback_for_AwPlayer, (void*)player);

    if (XPlayerInitCheck(player->mAwPlayer) != 0)
    {
        printf("initCheck of the player fail, quit.\n");
        XPlayerDestroy(player->mAwPlayer);
        player->mAwPlayer = NULL;
        return NULL;
    }

    LayerCtrl* layer = LayerCreate_DE();      //页面层
    SoundCtrl* sound = SoundDeviceCreate();   //声音设备
    SubCtrl* sub = SubtitleCreate();          //辅助控制
    Deinterlace* di = DeinterlaceCreate();    //去交错

    XPlayerSetAudioSink(player->mAwPlayer, sound);
    XPlayerSetVideoSurfaceTexture(player->mAwPlayer, layer);
    XPlayerSetSubCtrl(player->mAwPlayer, sub);
    XPlayerSetDeinterlace(player->mAwPlayer, di);

    return player;
}

void player_uninit(PlayerContext* player)
{

    if (player->mAwPlayer != NULL)
    {
        XPlayerDestroy(player->mAwPlayer);
        player->mAwPlayer = NULL;
    }

    pthread_mutex_destroy(&player->mMutex);
    free(player);

}


void player_demo()
{
    PlayerContext* demo_player;
    

    demo_player = player_init();
    set_source_url(demo_player, "/home/admin/video/dmc_test.mp4");
    player_start(demo_player);
    sleep(5);
    player_stop(demo_player);
    player_uninit(demo_player);

}


















