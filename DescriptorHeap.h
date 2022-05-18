#pragma once
#include <d3d12.h>
#pragma comment (lib,"d3d12.lib")
class DescriptorHeap
{
protected:  
    D3D12_CPU_DESCRIPTOR_HANDLE mDescriptorHandle = {};//ptrメンバがDescriptorHeapのViewのアドレスを指す

    D3D12_DESCRIPTOR_HEAP_DESC mHeapDesc = {};
    ID3D12DescriptorHeap* mDescriptorHeaps = nullptr;

public:
    DescriptorHeap();
    ~DescriptorHeap();
    virtual void InitHeapDesc() {};
    D3D12_CPU_DESCRIPTOR_HANDLE PassDescriptorHeapFirstAddressToHandle() {
        mDescriptorHandle = mDescriptorHeaps->GetCPUDescriptorHandleForHeapStart();
        return mDescriptorHandle;
    };//DescriptorHeapの先頭のアドレスをHandleに渡す
  
    void SetHandlePtr(int ptr) { mDescriptorHandle.ptr += ptr; };
    ID3D12DescriptorHeap** GetDescriptorHeap() { return &mDescriptorHeaps; };
    D3D12_DESCRIPTOR_HEAP_DESC* GetHeapDesc() { return &mHeapDesc; };
    D3D12_CPU_DESCRIPTOR_HANDLE GetHandle() { return mDescriptorHandle; };
};