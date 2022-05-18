#include "RTVDescriptorHeap.h"

void RTVDescriptorHeap::InitHeapDesc()
{
    mHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;//レンダーターゲットビュー
    mHeapDesc.NodeMask = 0;//一つだけなので0
    mHeapDesc.NumDescriptors = 2;//表裏の二つ
    mHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;//特に指定なし
    
}
