#include "Commanders.h"

void Commanders::CreateCommanders(ID3D12Device* pDevice)
{
    auto result = pDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&mpCmdAllocator));
    result = pDevice->CreateCommandList(
        0, D3D12_COMMAND_LIST_TYPE_DIRECT,
        mpCmdAllocator, nullptr,
        IID_PPV_ARGS(&mpCmdList));
    D3D12_COMMAND_QUEUE_DESC cmdQueueDesc = {};

    //タイムアウトなし
    cmdQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;

    //アダプターを一つしか使わないときは0でよい
    cmdQueueDesc.NodeMask = 0;

    //プライオリティは特に指定なし
    cmdQueueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;

    //コマンドリストと合わせる
    cmdQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

    //キュー生成
    result = pDevice->CreateCommandQueue(&cmdQueueDesc, IID_PPV_ARGS(&mpCmdQueue));

}

Commanders::Commanders()
{
}

Commanders::~Commanders()
{
}
/// <summary>
/// リストの実行
/// </summary>
/// <param name="CommandNum">実行するコマンドリスト数</param>
void Commanders::Run(int CommandNum)
{
    //コマンドリストの実行
    ID3D12CommandList* cmdlists[] = { mpCmdList };
                                  
    mpCmdQueue->ExecuteCommandLists(CommandNum, cmdlists);
}

/// <summary>
/// 命令をため込むようにできる
/// </summary>
void Commanders::Close()
{
    //命令のクローズ
    mpCmdList->Close();
}
/// <summary>
/// 命令が全部終えたらリセット
/// </summary>
void Commanders::Reset()
{
    mpCmdAllocator->Reset();//キューをクリア
    mpCmdList->Reset(mpCmdAllocator, nullptr);//再びコマンドリストを貯める準備
}

void Commanders::Clear(D3D12_CPU_DESCRIPTOR_HANDLE rtvH)
{
    auto result = mpCmdAllocator->Reset();
    mpCmdList->OMSetRenderTargets(1, &rtvH, true, nullptr);
}

void Commanders::Clear(D3D12_CPU_DESCRIPTOR_HANDLE rtvH, float color[])
{
    auto result = mpCmdAllocator->Reset();
    mpCmdList->OMSetRenderTargets(1, &rtvH, true, nullptr);

    mpCmdList->ClearRenderTargetView(rtvH, color, 0, nullptr);
}
