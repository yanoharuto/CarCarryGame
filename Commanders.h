#pragma once

#include <d3d12.h>
#pragma comment (lib,"d3d12.lib")
class Commanders
{
private:
    
    ID3D12CommandAllocator* mpCmdAllocator = nullptr;
    ID3D12GraphicsCommandList* mpCmdList = nullptr;
    ID3D12CommandQueue* mpCmdQueue = nullptr;
public:
    Commanders();
    ~Commanders();
    
    void CreateCommanders(ID3D12Device* pDevice);
    void Run(int CommandNum);
    void Close();
    void Reset();
    void Clear(D3D12_CPU_DESCRIPTOR_HANDLE rtvH);
    void Clear(D3D12_CPU_DESCRIPTOR_HANDLE rtvH,float color[]);

    ID3D12CommandQueue* GetQueue() { return mpCmdQueue; };
};

