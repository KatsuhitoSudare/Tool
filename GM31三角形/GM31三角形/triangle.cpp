#include	<DirectXMath.h>
#include	"CDirectxGraphics.h"
#include	"dx11helper.h"
#include "triangle.h"

using namespace DirectX;

// 頂点構造体
struct Vertex {
	XMFLOAT3	Pos;
};

// 定数バッファ構造体
struct ConstantBuffer_Color {
	XMFLOAT4	Color;							// カラー値
};

ID3D11Buffer*			g_VertexBuffer = nullptr;	// 頂点バッファ
ID3D11VertexShader*		g_VertexShader = nullptr;	// 頂点シェーダー
ID3D11PixelShader*		g_PixelShader = nullptr;	// ピクセルシェーダー
ID3D11InputLayout*		g_VertexLayout = nullptr;	// 頂点レイアウト

ID3D11Buffer*			g_ConstantBuffer = nullptr;	// 定数バッファ

int                     g_vertexnum = 6;

// 初期処理
bool InitTrinagle() {

	ID3D11Device*		 device;

	// デバイスを取得する
	device = CDirectXGraphics::GetInstance()->GetDXDevice();

	// 頂点データの定義
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	// エレメント数
	unsigned int numElements = ARRAYSIZE(layout);

	// 頂点シェーダーオブジェクトを生成、同時に頂点レイアウトも生成
	bool sts = CreateVertexShader(			
		device,								// デバイスオブジェクト						
		"vstriangle.hlsl",					// 頂点シェーダーソースファイル					
		"main",								// エントリ関数
		"vs_5_0",							// 頂点シェーダーモデル５．０
		layout,								// 頂点データレイアウト
		numElements,						// 頂点データのエレメント数
		&g_VertexShader,					// 頂点シェーダーオブジェクト
		&g_VertexLayout);					// 頂点データレイアウトオブジェクト
	if (!sts) {
		MessageBox(nullptr, "CreateVertexShader error", "error", MB_OK);
		return false;
	}

	// ピクセルシェーダーを生成
	sts = CreatePixelShader(			// ピクセルシェーダーオブジェクトを生成
			device,						// デバイスオブジェクト
			"pstriangle.hlsl",			// ピクセルシェーダーソースファイル
			"main",						// エントリ関数
			"ps_5_0",					// ピクセルシェーダーモデル５．０
			&g_PixelShader);			// ピクセルシェーダーオブジェクト
	if (!sts) {
		MessageBox(nullptr, "CreatePixelShader error", "error", MB_OK);
		return false;
	}

	// 頂点座標
	/*Vertex	v[3] = {
		XMFLOAT3(0.0f*2.0f, 0.25f*2.0f, 0.5f),
		XMFLOAT3(0.25f*2.0f, -0.25f*2.0f, 0.5f),
		XMFLOAT3(-0.25f*2.0f, -0.25f*2.0f, 0.5f)
	};*/

	 //頂点座標四角形バージョン
	Vertex	v[6] = {
		XMFLOAT3(-0.5f, 0.5f, 0.5f),
		XMFLOAT3(0.5,   0.5f, 0.5f),
		XMFLOAT3(-0.5, -0.5f, 0.5f),
		XMFLOAT3(0.5f,  0.5f, 0.5f),
		XMFLOAT3(0.5,  -0.5f, 0.5f),
		XMFLOAT3(-0.5, -0.5f, 0.5f),
	};

	

	// 頂点バッファを生成
	sts = CreateVertexBuffer(
		device,						// デバイスオブジェクト
		sizeof(Vertex),				// １頂点当たりバイト数
		g_vertexnum,				    // 頂点数
		v,							// 頂点データ格納メモリ先頭アドレス
		&g_VertexBuffer				// 頂点バッファ
	);



	if (!sts) {
		MessageBox(nullptr, "CreateVertexBuffer error", "error", MB_OK);
		return false;
	}

	// 定数バッファ作成(ここをコーディング)
	D3D11_BUFFER_DESC cbDesc{};

	cbDesc.ByteWidth = sizeof(ConstantBuffer_Color);
	cbDesc.Usage = D3D11_USAGE_DEFAULT;
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.CPUAccessFlags = 0;
	cbDesc.MiscFlags = 0;
	cbDesc.StructureByteStride = 0;

	device->CreateBuffer(&cbDesc, NULL, &g_ConstantBuffer);

	return true;
}

// 更新処理
void UpdateTriangle() {

	static float r = 0.0f;
	static float g = 0.0f;
	static float b = 0.0f;

	if (GetAsyncKeyState(VK_F1) & 0x8000) {
		r += 0.01f;
		if (r >= 1.0f) {
			r = 1.0f;
		}
	}
	if (GetAsyncKeyState(VK_F2) & 0x8000) {
		r -= 0.01f;
		if (r <= 0.0f) {
			r = 0.0f;
		}
	}

	if (GetAsyncKeyState(VK_F3) & 0x8000) {
		g += 0.01f;
		if (g >= 1.0f) {
			g = 1.0f;
		}
	}
	if (GetAsyncKeyState(VK_F4) & 0x8000) {
		g -= 0.01f;
		if (g <= 0.0f) {
			g = 0.0f;
		}
	}

	if (GetAsyncKeyState(VK_F5) & 0x8000) {
		b += 0.01f;
		if (b >= 1.0f) {
			b = 1.0f;
		}
	}
	if (GetAsyncKeyState(VK_F6) & 0x8000) {
		b -= 0.01f;
		if (b <= 0.0f) {
			b = 0.0f;
		}
	}

	// コンスタントバッファ構造体へカラー値をセット
	ConstantBuffer_Color cb;
	cb.Color.x = r;			// r
	cb.Color.y = g;			// g
	cb.Color.z = b;			// b
	cb.Color.w = 1.0f;		// a

	// デバイスコンテキスト取得
	ID3D11DeviceContext*		 devicecontext;		// デバイスコンテキスト															// デバイスコンテキストを取得する
	devicecontext = CDirectXGraphics::GetInstance()->GetImmediateContext();

	// 定数バッファ更新（ここをコーディング）
	devicecontext->UpdateSubresource(g_ConstantBuffer,0,NULL, &cb,0,0);

}

// 描画処理
void DrawTriangle() {

	ID3D11DeviceContext*		 devicecontext;				// デバイスコンテキスト

	// デバイスコンテキストを取得する
	devicecontext = CDirectXGraphics::GetInstance()->GetImmediateContext();

	unsigned int stride = sizeof(Vertex);					// ストライドをセット（１頂点当たりのバイト数）
	unsigned  offset = 0;									// オフセット値をセット

	// 頂点バッファをデバイスコンテキストへセット
	devicecontext->IASetVertexBuffers(			
		0,													// スタートスロット
		1,													// 頂点バッファ個数
		&g_VertexBuffer,									// 頂点バッファの先頭アドレス
		&stride,											// ストライド
		&offset);											// オフセット

	// トポロジーをセット
	devicecontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// 頂点フォーマットをセット
	devicecontext->IASetInputLayout(g_VertexLayout);

	devicecontext->VSSetShader(g_VertexShader, nullptr, 0);		// 頂点シェーダーをセット
	devicecontext->PSSetShader(g_PixelShader, nullptr, 0);		// ピクセルシェーダーをセット

	
	// 定数バッファをGPUへセット（ここをコーディング）
	devicecontext->PSSetConstantBuffers(0, 1, &g_ConstantBuffer);


	// デバイスコンテキストに頂点データを流し込む
	devicecontext->Draw(
		g_vertexnum,				// 頂点数
		0);				            // 開始頂点インデックス
}

void DrawBox()
{
	ID3D11DeviceContext* devicecontext;				// デバイスコンテキスト

	// デバイスコンテキストを取得する
	devicecontext = CDirectXGraphics::GetInstance()->GetImmediateContext();

	unsigned int stride = sizeof(Vertex);					// ストライドをセット（１頂点当たりのバイト数）
	unsigned  offset = 0;									// オフセット値をセット

	// 頂点バッファをデバイスコンテキストへセット
	devicecontext->IASetVertexBuffers(
		0,													// スタートスロット
		1,													// 頂点バッファ個数
		&g_VertexBuffer,									// 頂点バッファの先頭アドレス
		&stride,											// ストライド
		&offset);											// オフセット

	// トポロジーをセット
	devicecontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// 頂点フォーマットをセット
	devicecontext->IASetInputLayout(g_VertexLayout);

	devicecontext->VSSetShader(g_VertexShader, nullptr, 0);		// 頂点シェーダーをセット
	devicecontext->PSSetShader(g_PixelShader, nullptr, 0);		// ピクセルシェーダーをセット


	// 定数バッファをGPUへセット（ここをコーディング）
	devicecontext->PSSetConstantBuffers(0, 1, &g_ConstantBuffer);


	// デバイスコンテキストに頂点データを流し込む
	devicecontext->Draw(
		3,				// 頂点数
		0);				// 開始頂点インデックス
}

// 終了処理
void UninitTriangle() {

	if (g_VertexLayout != nullptr) {
		g_VertexLayout->Release();
		g_VertexLayout = nullptr;
	}

	if (g_VertexShader != nullptr) {
		g_VertexShader->Release();
		g_VertexShader = nullptr;
	}

	if (g_PixelShader != nullptr) {
		g_PixelShader->Release();
		g_PixelShader = nullptr;
	}

	if (g_VertexBuffer != nullptr) {
		g_VertexBuffer->Release();
		g_VertexBuffer = nullptr;
	}

	if (g_ConstantBuffer != nullptr) {
		g_ConstantBuffer->Release();
		g_ConstantBuffer = nullptr;
	}
}