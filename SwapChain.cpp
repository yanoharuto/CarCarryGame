#include "SwapChain.h"

void SwapChain::PrepareBackBuffer()
{
    mpRTV = new RenderTargetView(mSwapChainDesc.BufferCount);
}

void SwapChain::InitDescriptor(ID3D12Device* pDevice)
{
    mpRTVDescriptorHeap = new RTVDescriptorHeap();
    mpRTVDescriptorHeap->InitHeapDesc();
    pDevice->CreateDescriptorHeap(
        mpRTVDescriptorHeap->GetHeapDesc(),
        IID_PPV_ARGS(mpRTVDescriptorHeap->GetDescriptorHeap())
    );
}

SwapChain::SwapChain()
{
}

SwapChain::~SwapChain()
{
    delete mpRTVDescriptorHeap;
    mpRTVDescriptorHeap = nullptr;
    delete mpRTV;
    mpRTV = nullptr;
}
void SwapChain::Flip()
{                      //フリップまでの待ちフレーム数(待つべき垂直同期の数)
    mpSwapChain->Present(1, 0);
}
//レンダーターゲットの先頭アドレスを渡す
D3D12_CPU_DESCRIPTOR_HANDLE SwapChain::PassRenderTargetFirstAddress(ID3D12Device* pDevice)
{
    auto bbIdx = mpSwapChain->GetCurrentBackBufferIndex();//描画し終えた方のバックバッファーの番号が返ってくる
 
    auto rtvHandle = mpRTVDescriptorHeap->PassDescriptorHeapFirstAddressToHandle();
    //必要なパディングを含む、RTVのDescriptorヒープのハンドル増分のサイズを返します
    rtvHandle.ptr += bbIdx * pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

    return rtvHandle;
}

void SwapChain::Init(LONG WindowWidth, LONG WindowHeight,ID3D12Device* pDevice)
{
    mSwapChainDesc.Width = WindowWidth;
    mSwapChainDesc.Height = WindowHeight;
    mSwapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    mSwapChainDesc.Stereo = false;
    mSwapChainDesc.SampleDesc.Count = 1;
    mSwapChainDesc.SampleDesc.Quality = 0;
    mSwapChainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER;
    mSwapChainDesc.BufferCount = 2;
    //バックバッファーは伸び縮み可能
    mSwapChainDesc.Scaling = DXGI_SCALING_STRETCH;

    //フリップ後は速やかに破棄
    mSwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

    //特に指定なし
    mSwapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;

    //ウィンドウ⇔フルスクリーン切り替え可能
    mSwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    PrepareBackBuffer();
    InitDescriptor(pDevice);
}
/// <summary>
/// BackBufferとViewの紐づけ
/// </summary>
void SwapChain::LinkingBufferToView(ID3D12Device* pDevice)
{   
    mpRTVDescriptorHeap->PassDescriptorHeapFirstAddressToHandle();
    //BackBufferの数だけ
    for (int idx = 0; idx < mSwapChainDesc.BufferCount; ++idx)
    {
        auto result = mpSwapChain->GetBuffer(idx, IID_PPV_ARGS(mpRTV->GetBackBuffer(idx)));
        //DescriptorHeapのアドレスを指しているHandleのメンバ変数を移動させる
        mpRTVDescriptorHeap->SetHandlePtr( idx * pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
        pDevice->CreateRenderTargetView(*mpRTV->GetBackBuffer(idx),nullptr,mpRTVDescriptorHeap->GetHandle());
    }   
}
