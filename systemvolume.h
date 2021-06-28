#ifndef SYSTEMVOLUME_H
#define SYSTEMVOLUME_H

#include <windows.h>
//The Windows Multimeidia Device API
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <Audioclient.h>

//__declspec是Microsoft c++中专用的关键字，它配合着一些属性可以对标准c++进行扩充。
//dll提供者和使用者使用同一个头文件
#ifndef SYSTEM_DLLEXPORT
//在提供者处方法被声明为dllexport
#define SYSTEM_DLLEXPORTAPI __declspec(dllexport)
#else
//在使用者处方法被声明为dllimport
#define SYSTEM_DLLEXPORTAPI __declspec(dllimport)
#endif // !SYSTEM_DLLEXPORT

#define _SYSTEMVOLUME_H_

namespace SystemConf
{

class SystemVolume
{
public:
    explicit SystemVolume();
    virtual ~SystemVolume();

private:
    HRESULT hr;
    IMMDeviceEnumerator* pDeviceEnumerator = 0;
    IMMDevice* pDevice = 0;
    IAudioEndpointVolume* pAudioEndpointVolume = 0;
    IAudioClient* pAudioClient = 0;

public:
    /*初始化服务*/
    void Init();
    /*关闭服务 释放资源*/
    void Close();
    /*设置音量*/
    void SetVolume(int volume);
    /*获取系统音量*/
    int GetVolume();
    /*静音*/
    void Mute();
    /*解除静音*/
    void UnMute();
};

SYSTEM_DLLEXPORTAPI void SetVolumn(int volumn);
SYSTEM_DLLEXPORTAPI int GetVolumn();

}// namesoace SystemConf



#endif // SYSTEMVOLUME_H
