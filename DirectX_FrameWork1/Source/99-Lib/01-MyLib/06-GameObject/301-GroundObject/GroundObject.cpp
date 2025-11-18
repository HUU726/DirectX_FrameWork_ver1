#include "GroundObject.h"
#include "../../07-Component/02-Renderer/02-MeshRenderer/MeshRenderer.h"

#include "../../02-Renderer/99-ShapeTable/02-ShapeTable3D/ShapeTable3D.h"
#include "../../999-Shader/99-ShaderTable/ShaderTable.h"
#include "../../04-Texture/stb_image.h"


void GroundObject::Init()
{
	auto renderer = GetComponent<MeshRenderer>();

	sizeX = 30;
	sizeZ = 30;


	std::shared_ptr<hft::Mesh> sp_mesh = std::make_shared<hft::Mesh>();
	sp_mesh->name = "ground";
	sp_mesh->materials.resize(1);

	{
		std::vector<hft::Vertex> vertices;
		vertices.resize(sizeX * sizeZ * 4);
		{
			for ( int z = 0; z < sizeZ; z++ )
			{
				for ( int x = 0; x < sizeZ; x++ )
				{
					int baseIndex = (sizeX * 4 * z) + (x * 4);
					float basePosX = x - float(float(sizeX) / 2.0f);
					float basePosZ = -z + float(float(sizeZ) / 2.0f);
					vertices[baseIndex + 0].position = { basePosX - 0.5f, 0, basePosZ + 0.5f };
					vertices[baseIndex + 1].position = { basePosX + 0.5f, 0, basePosZ + 0.5f };
					vertices[baseIndex + 2].position = { basePosX - 0.5f, 0, basePosZ - 0.5f };
					vertices[baseIndex + 3].position = { basePosX + 0.5f, 0, basePosZ - 0.5f };

					vertices[baseIndex + 0].color = { 1,1,1,1 };
					vertices[baseIndex + 1].color = { 1,1,1,1 };
					vertices[baseIndex + 2].color = { 1,1,1,1 };
					vertices[baseIndex + 3].color = { 1,1,1,1 };

					vertices[baseIndex + 0].uv = { 0,0 };
					vertices[baseIndex + 1].uv = { 1,0 };
					vertices[baseIndex + 2].uv = { 0,1 };
					vertices[baseIndex + 3].uv = { 1,1 };
				}
			}

			//高さを画像から生成
			{
				//読み込む画像ファイルパス
				const char* filePath = "Assets/01-Texture/99-Test/terrain.png";

				//画像データを格納するポインタ
				unsigned char* imgData = nullptr;
				int l_width, l_height, l_channels;

				//グレースケール（１チャンネル）で画像を読み込む
				imgData = stbi_load(filePath, &l_width, &l_height, &l_channels, 1);
				if ( imgData )
				{
					for ( int z = 0; z <= sizeZ; z++ )
					{
						for ( int x = 0; x <= sizeX; x++ )
						{
							//高さを計算
							int pixX = (int)(1 + x * (float)(l_width - 2) / sizeX);		//左右１ピクセルを無視
							int pixY = (int)(1 + z * (float)(l_height - 2) / sizeZ);	//上下１ピクセルを無視

							unsigned char pixelValue = imgData[pixY * l_width + pixX];
							float h = (float)pixelValue / 10.0f;	//Y座標

							//頂点に高さを代入
							int baseIndex = (z * sizeX * 4) + (x * 4);

							//ベース（四角形左上）
							if ( x != sizeX && z != sizeZ )
							{
								vertices[baseIndex].position.y = h;
							}
							//ベースから左側頂点
							if ( x != 0 && z != sizeZ )
							{
								vertices[baseIndex - 3].position.y = h;
							}
							//ベースから右上頂点
							if ( x != sizeX && z != 0 )
							{
								vertices[baseIndex - sizeX * 4 + 2].position.y = h;
							}
							//ベースから左上頂点
							if ( x != 0 && z != 0 )
							{
								vertices[baseIndex - sizeX * 4 - 1].position.y = h;
							}


						}
					}
				}
				stbi_image_free(imgData);	//メモリ開放
			}



			//法線ベクトルを設定
			{
				
				for ( int z = 0; z < sizeZ; z++ )
				{
					for ( int x = 0; x < sizeX; x++ )
					{

						int baseIndex = (z * sizeX * 4) + (x * 4);

						//2つのベクトルを計算
						hft::HFFLOAT3 v1 = vertices[baseIndex + 1].position - vertices[baseIndex + 0].position;
						hft::HFFLOAT3 v2 = vertices[baseIndex + 2].position - vertices[baseIndex + 0].position;
						DirectX::XMVECTOR vec1 = DirectX::XMVectorSet(v1.x, v1.y, v1.z, 0);
						DirectX::XMVECTOR vec2 = DirectX::XMVectorSet(v2.x, v2.y, v2.z, 0);
						DirectX::XMVECTOR cross1 = DirectX::XMVector3Cross(vec1, vec2);
						DirectX::XMVECTOR normal1 = DirectX::XMVector3Normalize(cross1);
						DirectX::XMStoreFloat3(&vertices[baseIndex + 0].normal, normal1);

						//2つのベクトルを計算
						hft::HFFLOAT3 v3 = vertices[baseIndex + 1].position - vertices[baseIndex + 0].position;
						hft::HFFLOAT3 v4 = vertices[baseIndex + 2].position - vertices[baseIndex + 0].position;
						DirectX::XMVECTOR vec3 = DirectX::XMVectorSet(v3.x, v3.y, v3.z, 0);
						DirectX::XMVECTOR vec4 = DirectX::XMVectorSet(v4.x, v4.y, v4.z, 0);
						DirectX::XMVECTOR cross2 = DirectX::XMVector3Cross(vec3, vec4);
						DirectX::XMVECTOR normal2 = DirectX::XMVector3Normalize(cross2);
						DirectX::XMStoreFloat3(&vertices[baseIndex + 3].normal, normal2);

						DirectX::XMVECTOR midVec = DirectX::XMVectorAdd(cross1, cross2);
						midVec = DirectX::XMVector3Normalize(midVec);
						DirectX::XMStoreFloat3(&vertices[baseIndex + 1].normal, midVec);
						DirectX::XMStoreFloat3(&vertices[baseIndex + 2].normal, midVec);
					}
				}

				for ( int z = 0; z < sizeZ; z++ )
				{
					for ( int x = 0; x < sizeX; x++ )
					{
						int baseIndex = (z * sizeX * 4) + (x * 4);
						hft::HFFLOAT3;

						//ベース（四角形左上）
						if ( x != sizeX && z != sizeZ )
						{
							
						}
						//ベースから左側頂点
						if ( x != 0 && z != sizeZ )
						{
							
						}
						//ベースから右上頂点
						if ( x != sizeX && z != 0 )
						{
							
						}
						//ベースから左上頂点
						if ( x != 0 && z != 0 )
						{
							
						}
					}
				}

			}
		}

		std::vector<UINT> indices;
		indices.resize(sizeX * sizeZ * 6);
		{
			for ( int z = 0; z < sizeZ; z++ )
			{
				for ( int x = 0; x < sizeX; x++ )
				{
					int baseIndex = (z * sizeX * 6) + (x * 6);
					int baseVertex = (z * sizeX * 4) + (x * 4);
					indices[baseIndex + 0] = baseVertex;
					indices[baseIndex + 1] = baseVertex + 1;
					indices[baseIndex + 2] = baseVertex + 2;
					indices[baseIndex + 3] = baseVertex + 1;
					indices[baseIndex + 4] = baseVertex + 3;
					indices[baseIndex + 5] = baseVertex + 2;
				}
			}
		}



		sp_mesh->vertices = vertices;
		sp_mesh->indices = indices;

		hft::CreateVertexIndexBuffer(sp_mesh);

		auto sp_vertexShader = hft::VertexShaderTable::GetInstance().GetShader("Source/99-Lib/01-MyLib/999-Shader/02-3D/02-LightMesh3D/VS_LightMesh3D.hlsl");
		sp_mesh->materials[0].shader.SetVertexShader(sp_vertexShader);
		hft::Shader l_shader;
		l_shader.CreatePixelShader("Source/99-Lib/01-MyLib/999-Shader/02-3D/02-LightMesh3D/PS_LightMesh3D.hlsl");
		auto sp_pixelShader = hft::PixelShaderTable::GetInstance().GetShader("Source/99-Lib/01-MyLib/999-Shader/02-3D/02-LightMesh3D/PS_LightMesh3D.hlsl");
		sp_mesh->materials[0].shader.SetPixelShader(sp_pixelShader);
	}

	
	ShapeTable3D::GetInstance().AddShape(sp_mesh);
	renderer->SetShape(sp_mesh);
	if ( renderer->LoadTexture("Assets/01-Texture/99-Test/field.jpg") )
		sp_mesh->materials[0].isTexture = true;
}

void GroundObject::Update()
{}
