#include "directx9.h"
#include <d3d9.h>
#include <imgui/imgui_impl_dx9.h>
#include "utinni.h"
#include "swg/ui/imgui_impl.h"
#include "swg/ui/cui_manager.h"

namespace directX
{
LPDIRECT3DDEVICE9 pDevice = nullptr;
DWORD* vtbl = nullptr;
DWORD dllBaseAddress = 0;

static bool blockPresentCall = false;
static bool isPresenting = false;

using pBeginScene = HRESULT(__stdcall*)(LPDIRECT3DDEVICE9 pDevice);
using pEndScene = HRESULT(__stdcall*)(LPDIRECT3DDEVICE9 pDevice);
using pPresent = HRESULT(__stdcall*)(LPDIRECT3DDEVICE9 pDevice, const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion);
using pReset = HRESULT(__stdcall*)(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);
using pDrawIndexedPrimitive = HRESULT(__stdcall*)(LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE type, int baseVertexIndex, unsigned int minIndex, unsigned int numVertices, unsigned int startIndex, unsigned int primitiveCount);
using pSetRenderTarget = HRESULT(__stdcall*)(LPDIRECT3DDEVICE9 pDevice, DWORD index, IDirect3DSurface9* surface);
using pSetDepthStencil = HRESULT(__stdcall*)(LPDIRECT3DDEVICE9 pDevice, IDirect3DSurface9* surface);
using pSetRenderState = HRESULT(__stdcall*) (LPDIRECT3DDEVICE9 pDevice, D3DRENDERSTATETYPE State, DWORD Value);

pBeginScene beginScene;
pEndScene endScene;
pPresent present;
pReset reset;
pDrawIndexedPrimitive drawIndexedPrimitive;
pSetRenderTarget setRenderTarget;
pSetDepthStencil setDepthStencil;
pSetRenderState setRenderState;

enum D3DInformation
{
	 d3di_Queryinterface_Index = 0,
	 d3di_AddRef_Index = 1,
	 d3di_Release_Index = 2,
	 d3di_TestCooperativeLevel_Index = 3,
	 d3di_GetAvailableTextureMem_Index = 4,
	 d3di_EvictManagedResources_Index = 5,
	 d3di_GetDirect3D_Index = 6,
	 d3di_GetDeviceCaps_Index = 7,
	 d3di_GetDisplayMode_Index = 8,
	 d3di_GetCreationParameters_Index = 9,
	 d3di_SetCursorProperties_Index = 10,
	 d3di_SetCursorPosition_Index = 11,
	 d3di_ShowCursor_Index = 12,
	 d3di_CreateAdditionalSwapChain_Index = 13,
	 d3di_GetSwapChain_Index = 14,
	 d3di_GetNumberOfSwapChains_Index = 15,
	 d3di_Reset_Index = 16,
	 d3di_Present_Index = 17,
	 d3di_GetBackBuffer_Index = 18,
	 d3di_GetRasterStatus_Index = 19,
	 d3di_SetDialogBoxMode_Index = 20,
	 d3di_SetGammaRamp_Index = 21,
	 d3di_GetGammaRamp_Index = 22,
	 d3di_CreateTexture_Index = 23,
	 d3di_CreateVolumeTexture_Index = 24,
	 d3di_CreateCubeTexture_Index = 25,
	 d3di_CreateVertexBuffer_Index = 26,
	 d3di_CreateIndexBuffer_Index = 27,
	 d3di_CreateRenderTarget_Index = 28,
	 d3di_CreateDepthStencilSurface_Index = 29,
	 d3di_UpdateSurface_Index = 30,
	 d3di_UpdateTexture_Index = 31,
	 d3di_GetRenderTargetData_Index = 32,
	 d3di_GetFrontBufferData_Index = 33,
	 d3di_StretchRect_Index = 34,
	 d3di_ColorFill_Index = 35,
	 d3di_CreateOffscreenPlainSurface_Index = 36,
	 d3di_SetRenderTarget_Index = 37,
	 d3di_GetRenderTarget_Index = 38,
	 d3di_SetDepthStencilSurface_Index = 39,
	 d3di_GetDepthStencilSurface_Index = 40,
	 d3di_BeginScene_Index = 41,
	 d3di_EndScene_Index = 42,
	 d3di_Clear_Index = 43,
	 d3di_SetTransform_Index = 44,
	 d3di_GetTransform_Index = 45,
	 d3di_MultiplyTransform_Index = 46,
	 d3di_SetViewport_Index = 47,
	 d3di_GetViewport_Index = 48,
	 d3di_SetMaterial_Index = 49,
	 d3di_GetMaterial_Index = 50,
	 d3di_SetLight_Index = 51,
	 d3di_GetLight_Index = 52,
	 d3di_LightEnable_Index = 53,
	 d3di_GetLightEnable_Index = 54,
	 d3di_SetClipPlane_Index = 55,
	 d3di_GetClipPlane_Index = 56,
	 d3di_SetRenderState_Index = 57,
	 d3di_GetRenderState_Index = 58,
	 d3di_CreateStateBlock_Index = 59,
	 d3di_BeginStateBlock_Index = 60,
	 d3di_EndStateBlock_Index = 61,
	 d3di_SetClipStatus_Index = 62,
	 d3di_GetClipStatus_Index = 63,
	 d3di_GetTexture_Index = 64,
	 d3di_SetTexture_Index = 65,
	 d3di_GetTextureStageState_Index = 66,
	 d3di_SetTextureStageState_Index = 67,
	 d3di_GetSamplerState_Index = 68,
	 d3di_SetSamplerState_Index = 69,
	 d3di_ValidateDevice_Index = 70,
	 d3di_SetPaletteEntries_Index = 71,
	 d3di_GetPaletteEntries_Index = 72,
	 d3di_SetCurrentTexturePalette_Index = 73,
	 d3di_GetCurrentTexturePalette_Index = 74,
	 d3di_SetScissorRect_Index = 75,
	 d3di_GetScissorRect_Index = 76,
	 d3di_SetSoftwareVertexProcessing_Index = 77,
	 d3di_GetSoftwareVertexProcessing_Index = 78,
	 d3di_SetNPatchMode_Index = 79,
	 d3di_GetNPatchMode_Index = 80,
	 d3di_DrawPrimitive_Index = 81,
	 d3di_DrawIndexedPrimitive_Index = 82,
	 d3di_DrawPrimitiveUP_Index = 83,
	 d3di_DrawIndexedPrimitiveUP_Index = 84,
	 d3di_ProcessVertices_Index = 85,
	 d3di_CreateVertexDeclaration_Index = 86,
	 d3di_SetVertexDeclaration_Index = 87,
	 d3di_GetVertexDeclaration_Index = 88,
	 d3di_SetFVF_Index = 89,
	 d3di_GetFVF_Index = 90,
	 d3di_CreateVertexShader_Index = 91,
	 d3di_SetVertexShader_Index = 92,
	 d3di_GetVertexShader_Index = 93,
	 d3di_SetVertexShaderConstantF_Index = 94,
	 d3di_GetVertexShaderConstantF_Index = 95,
	 d3di_SetVertexShaderConstantI_Index = 96,
	 d3di_GetVertexShaderConstantI_Index = 97,
	 d3di_SetVertexShaderConstantB_Index = 98,
	 d3di_GetVertexShaderConstantB_Index = 99,
	 d3di_SetStreamSource_Index = 100,
	 d3di_GetStreamSource_Index = 101,
	 d3di_SetStreamSourceFreq_Index = 102,
	 d3di_GetStreamSourceFreq_Index = 103,
	 d3di_SetIndices_Index = 104,
	 d3di_GetIndices_Index = 105,
	 d3di_CreatePixelShader_Index = 106,
	 d3di_SetPixelShader_Index = 107,
	 d3di_GetPixelShader_Index = 108,
	 d3di_SetPixelShaderConstantF_Index = 109,
	 d3di_GetPixelShaderConstantF_Index = 110,
	 d3di_SetPixelShaderConstantI_Index = 111,
	 d3di_GetPixelShaderConstantI_Index = 112,
	 d3di_SetPixelShaderConstantB_Index = 113,
	 d3di_GetPixelShaderConstantB_Index = 114,
	 d3di_DrawRectPatch_Index = 115,
	 d3di_DrawTriPatch_Index = 116,
	 d3di_DeletePatch_Index = 117,
	 d3di_CreateQuery_Index = 118,
	 d3di_NumberOfFunctions = 118
};

void setDevice()
{
    pDevice = (LPDIRECT3DDEVICE9)memory::findPattern((swgptr)GetModuleHandle("d3d9.dll"), 0x128000, "\xC7\x06\x00\x00\x00\x00\x89\x86\x00\x00\x00\x00\x89\x86", "xx????xx????xx");
    memcpy(&vtbl, (void*)(((DWORD)pDevice) + 2), 4);
}

HRESULT __stdcall hkBeginScene(LPDIRECT3DDEVICE9 pDevice)
{
    HRESULT result = beginScene(pDevice);
    return result;
}

HRESULT __stdcall hkEndScene(LPDIRECT3DDEVICE9 pDevice)
{
    HRESULT result = endScene(pDevice);
    return result;
}

HRESULT __stdcall hkPresent(LPDIRECT3DDEVICE9 pDevice, const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion)
{
	 imgui_impl::render();
	 HRESULT result = 0;

	 // Workaround for WinForms crashes on maximize and minimize/restore, something breaks inside of Present when either occur.
    // ToDo: Find better solution in the future
	 if (!blockPresentCall)
	 {
		  isPresenting = true;
		  result = present(pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
	 }
	 else
	 {
		  isPresenting = false;
	 }

	 imgui_impl::setup(pDevice);
    return result;
}

HRESULT __stdcall hkReset(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	 ImGui_ImplDX9_InvalidateDeviceObjects();
    HRESULT result = reset(pDevice, pPresentationParameters);
	 ImGui_ImplDX9_CreateDeviceObjects();
    return result;
}

bool enableWireframe = false;
HRESULT __stdcall hkDrawIndexedPrimitive(LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE type, int baseVertexIndex, unsigned int minVertexIndex, unsigned int numVertices, unsigned int startIndex, unsigned int primitiveCount)
{
    if (pDevice != nullptr && ((enableWireframe && utinni::CuiManager::isRenderingUi()) || !enableWireframe))
    {
        pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
    }
    else if (pDevice != nullptr && enableWireframe && !utinni::CuiManager::isRenderingUi())
    {
        pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
    }

    HRESULT result = drawIndexedPrimitive(pDevice, type, baseVertexIndex, minVertexIndex, numVertices, startIndex, primitiveCount);
    return result;
}

HRESULT _stdcall hkSetRenderTarget(LPDIRECT3DDEVICE9 pDevice, DWORD index, IDirect3DSurface9* surface)
{
    pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID); // Sets the FillMode to Solid before post processing for Wireframe to work
    HRESULT result = setRenderTarget(pDevice, index, surface);
    return result;
}

HRESULT __stdcall hkSetDepthStencil(LPDIRECT3DDEVICE9 pDevice, IDirect3DSurface9* surface)
{
    HRESULT result = setDepthStencil(pDevice, surface);
    return result;
}

HRESULT __stdcall hkSetRenderState(LPDIRECT3DDEVICE9 pDevice, D3DRENDERSTATETYPE State, DWORD Value)
{
    return setRenderState(pDevice, State, Value);
}

void detour()
{
    setDevice();

    DWORD BeginSceneAddress = Detour::CheckPointer(vtbl[d3di_BeginScene_Index]);
    beginScene = (pBeginScene)Detour::Create((LPVOID)BeginSceneAddress, hkBeginScene, DETOUR_TYPE_PUSH_RET);

    DWORD EndSceneAddress = Detour::CheckPointer(vtbl[d3di_EndScene_Index]);
    endScene = (pBeginScene)Detour::Create((LPVOID)EndSceneAddress, hkEndScene, DETOUR_TYPE_PUSH_RET);

    DWORD PresentAddress = Detour::CheckPointer(vtbl[d3di_Present_Index]);
    present = (pPresent)Detour::Create((LPVOID)PresentAddress, hkPresent, DETOUR_TYPE_PUSH_RET);

    DWORD ResetAddress = Detour::CheckPointer(vtbl[d3di_Reset_Index]);
    reset = (pReset)Detour::Create((LPVOID)ResetAddress, hkReset, DETOUR_TYPE_PUSH_RET);

    DWORD DrawIndexedPrimitiveAddress = Detour::CheckPointer(vtbl[d3di_DrawIndexedPrimitive_Index]);
    drawIndexedPrimitive = (pDrawIndexedPrimitive)Detour::Create((LPVOID)DrawIndexedPrimitiveAddress, hkDrawIndexedPrimitive, DETOUR_TYPE_PUSH_RET);

    DWORD SetRenderTargetAddress = Detour::CheckPointer(vtbl[d3di_SetRenderTarget_Index]);
    setRenderTarget = (pSetRenderTarget)Detour::Create((LPVOID)SetRenderTargetAddress, hkSetRenderTarget, DETOUR_TYPE_PUSH_RET);

    DWORD SetDepthStencilAddress = Detour::CheckPointer(vtbl[d3di_SetDepthStencilSurface_Index]);
    setDepthStencil = (pSetDepthStencil)Detour::Create((LPVOID)SetDepthStencilAddress, hkSetDepthStencil, DETOUR_TYPE_PUSH_RET);
}

void toggleWireframe()
{
    enableWireframe = !enableWireframe;
}

void blockPresent(bool value)
{
	 blockPresentCall = value;
}

bool isPresentBlocked()
{
	 return !isPresenting;
}

}


