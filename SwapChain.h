#pragma once
#include <dxgi1_6.h>
#include "RenderTargetView.h"
#include "RTVDescriptorHeap.h"
#pragma comment(lib,"dxgi.lib")


class SwapChain
{
private:
    DXGI_SWAP_CHAIN_DESC1 mSwapChainDesc = {};
    RenderTargetView* mpRTV = nullptr;
    RTVDescriptorHeap* mpRTVDescriptorHeap = nullptr;//レンダーターゲットビュー用のDescriptorHeap
    IDXGISwapChain4* mpSwapChain = nullptr;

    void PrepareBackBuffer();
    void InitDescriptor(ID3D12Device* pDevice);
public:
    SwapChain();
    ~SwapChain();
    DXGI_SWAP_CHAIN_DESC1* GetSwapChainDesc() { return &mSwapChainDesc; }
    IDXGISwapChain4** GetDXGISwapChain() { return &mpSwapChain; }
    D3D12_CPU_DESCRIPTOR_HANDLE PassRenderTargetFirstAddress(ID3D12Device* pDevice);
    void Init(LONG WindowWidth,LONG WindowHeight,ID3D12Device* pDevice);
    void LinkingBufferToView(ID3D12Device* pDevice);
};

