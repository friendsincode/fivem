/*
 * This file is part of the CitizenFX project - http://citizen.re/
 *
 * See LICENSE and MENTIONS in the root of the source tree for information
 * regarding licensing.
 */

#include <stdint.h>

#include <pgBase.h>
#include <pgContainers.h>
//#include <grcTexture.h>

#define RAGE_FORMATS_FILE rmcDrawable
#include <formats-header.h>

#ifdef RAGE_FORMATS_OK
#if defined(RAGE_FORMATS_GAME_NY)
#define RAGE_FORMATS_ny_rmcDrawable 1
#endif

class grcTexture : public pgBase
{
private:
	uint8_t m_objectType;
	uint8_t m_depth;
	uint16_t m_usageCount;
	uint32_t m_pad;
	uint32_t m_pad2;
	pgPtr<char> m_name;
	void* m_nativeHandle;
	uint16_t m_width;
	uint16_t m_height;
	uint32_t m_pixelFormat;
	uint16_t m_stride;
	uint8_t m_textureType;
	uint8_t m_levels;

public:
	inline grcTexture()
		: pgBase()
	{
		m_objectType = 2;
		m_depth = 0;
		m_usageCount = 1;
		m_pad = 0;
		m_pad2 = 0;
		m_nativeHandle = nullptr;
		m_width = 0;
		m_height = 0;
		m_pixelFormat = 0;
		m_stride = 0;
		m_textureType = 0;
		m_levels = 0;
	}

	inline void SetName(const char* name)
	{
		m_name = pgStreamManager::StringDup(name);
	}

	inline void Resolve(BlockMap* blockMap = nullptr)
	{
		m_name.Resolve(blockMap);
	}
};

class grcTexturePC : public grcTexture
{
private:
	float m_28[3];
	float m_34[3];
	void* m_next;
	void* m_prev;
	pgPtr<void> m_pixelData;
	uint8_t pad[4];

public:
	inline grcTexturePC()
		: grcTexture()
	{
		memset(m_28, 0, sizeof(m_28));
		memset(m_34, 0, sizeof(m_34));
		m_next = nullptr;
		m_prev = nullptr;
		memset(pad, 0, sizeof(pad));
	}

	inline void Resolve(BlockMap* blockMap = nullptr)
	{
		grcTexture::Resolve(blockMap);
	}
};

class crSkeletonData
{
public:
	inline void Resolve(BlockMap* blockMap = nullptr)
	{

	}
};

enum class grmShaderEffectParamType : uint8_t
{
	Texture = 0,
	Vector4 = 1,
	Matrix = 4,
	Vector4x6 = 8,
	Vector4x14 = 14,
	Vector4x15 = 15,
	Vector4x16 = 16
};

class grmShaderEffect
{
private:
	pgPtr<pgPtr<void>> m_parameters;
	pgPtr<int> m_pNull;
	uint32_t m_parameterCount;
	uint32_t m_parameterDataSize;
	pgPtr<grmShaderEffectParamType> m_parameterTypes;
	uint32_t m_shaderHash;
	uint32_t _f2C;
	uint32_t _f30;
	pgPtr<uint32_t> m_parameterNameHashes;
	uint32_t _f38;
	uint32_t _f3C;
	uint32_t _f40;

public:
	inline grmShaderEffect()
	{
		m_parameterCount = 0;
		m_parameterDataSize = 0;
		m_shaderHash = 0;
		_f2C = 0;
		_f30 = 0;
		_f38 = 0;
		_f3C = 0;
		_f40 = 0;
	}

	inline uint32_t GetParameterDataSize()
	{
		return SwapLongRead(m_parameterDataSize);
	}

	inline void SetParameterDataSize(uint32_t dataSize)
	{
		m_parameterDataSize = SwapLongWrite(dataSize);
	}

	inline uint32_t GetShaderHash()
	{
		return SwapLongRead(m_shaderHash);
	}

	inline void SetShaderHash(uint32_t shaderHash)
	{
		m_shaderHash = SwapLongWrite(shaderHash);
	}

	inline uint32_t GetParameterCount()
	{
		return SwapLongRead(m_parameterCount);
	}

	inline uint32_t GetParameterNameHash(int idx)
	{
		return SwapLongRead((*m_parameterNameHashes)[idx]);
	}

	inline void* GetParameterValue(int idx)
	{
		return *((*m_parameters)[idx]);
	}

	inline void SetParameters(uint32_t count, uint32_t* names, void** values, grmShaderEffectParamType* types)
	{
		pgPtr<void>* valuesInt = new(false) pgPtr<void>[count];

		for (int i = 0; i < count; i++)
		{
			valuesInt[i] = values[i];
		}

		m_parameterNameHashes = (uint32_t*)pgStreamManager::Allocate(sizeof(uint32_t) * count, false, nullptr);

		for (int i = 0; i < count; i++)
		{
			(*m_parameterNameHashes)[i] = names[i];
		}

		m_parameterTypes = (grmShaderEffectParamType*)pgStreamManager::Allocate(sizeof(grmShaderEffectParamType) * count, false, nullptr);

		for (int i = 0; i < count; i++)
		{
			(*m_parameterTypes)[i] = types[i];
		}

		m_parameters = valuesInt;

		m_parameterCount = SwapLongWrite(count);
	}

	inline void Resolve(BlockMap* blockMap = nullptr)
	{
		m_parameters.Resolve(blockMap);
		m_parameterNameHashes.Resolve(blockMap);
		m_parameterTypes.Resolve(blockMap);

		auto count = GetParameterCount();

		for (int i = 0; i < count; i++)
		{
			(*m_parameters)[i].Resolve(blockMap);
		}
	}
};

#ifdef RAGE_FORMATS_GAME_FIVE
class grmShaderParameter
{
private:
	uint8_t m_pad;
	uint8_t m_type;
	uint16_t m_pad2;
	pgPtr<void> m_value;

public:
	inline void Resolve(BlockMap* blockMap = nullptr)
	{
		m_value.Resolve(blockMap);
	}
};
#endif

class grmShader : public pgBase
{
private:
#ifdef RAGE_FORMATS_GAME_NY
	uint8_t m_version;
	uint8_t m_drawBucket;
	uint8_t m_usageCount;
	uint8_t m_pad;
	uint16_t _fC;
	uint16_t m_shaderIndex;
	uint32_t _f10;
	grmShaderEffect m_effect;
#endif

#ifdef RAGE_FORMATS_GAME_FIVE
	pgPtr<grmShaderParameter> m_parameters;
	uint32_t m_shaderHash;
	uint8_t m_parameterCount;
	uint8_t m_drawBucket;
	uint16_t m_pad;
	uint16_t m_parameterSize;
	uint16_t m_parameterDataSize;
	uint32_t m_spsHash;
	uint32_t m_pad2[3];
#endif

public:
#ifdef RAGE_FORMATS_GAME_NY
	inline grmShader()
	{
		m_version = 0;
		m_drawBucket = 0;
		m_usageCount = 1;
		_fC = 0;
		m_shaderIndex = 0;
		_f10 = 0;
	}

	inline uint8_t GetVersion() { return m_version; }
	inline uint16_t GetShaderIndex() { return SwapShortRead(m_shaderIndex); }
	inline uint8_t GetUsageCount() { return m_usageCount; }

	inline void SetIndex(uint16_t shaderIndex)
	{
		m_shaderIndex = shaderIndex;
	}

	inline void SetVersion(uint8_t version) { m_version = version; }
	inline void SetUsageCount(uint8_t usageCount) { m_usageCount = SwapShortWrite(usageCount); }

	inline grmShaderEffect& GetEffect() { return m_effect; }

	inline void Resolve(BlockMap* blockMap = nullptr)
	{
		m_effect.Resolve(blockMap);
	}
#endif

	inline uint8_t GetDrawBucket() { return m_drawBucket; }

	inline void SetDrawBucket(uint8_t drawBucket) { m_drawBucket = drawBucket; }

#ifdef RAGE_FORMATS_GAME_FIVE
	inline void Resolve(BlockMap* blockMap = nullptr)
	{
		m_parameters.Resolve(blockMap);

		for (int i = 0; i < m_parameterCount; i++)
		{
			(*m_parameters)[i].Resolve(blockMap);
		}
	}
#endif
};

class grmShaderFx : public grmShader
{
private:
	pgPtr<char> m_shaderName;
	pgPtr<char> m_spsName;
	uint32_t _f4C;
	uint32_t _f50;
	uint32_t m_preset;
	uint32_t _f58;

public:
	inline grmShaderFx()
		: grmShader()
	{
		_f4C = 0;
		_f50 = 0;
		m_preset = 0;
		_f58 = 0;
	}

	inline const char* GetShaderName() { return *(m_shaderName); }

	inline const char* GetSpsName() { return *(m_shaderName); }

	inline void SetShaderName(char* value) { m_shaderName = pgStreamManager::StringDup(value); }

	inline void SetSpsName(char* value) { m_spsName = pgStreamManager::StringDup(value); }

	inline uint32_t GetPreset() { return SwapLongRead(m_preset); }

	inline void SetPreset(uint32_t value) { m_preset = SwapLongWrite(value); }

	inline void Resolve(BlockMap* blockMap = nullptr)
	{
		m_shaderName.Resolve(blockMap);
		m_spsName.Resolve(blockMap);

		grmShader::Resolve(blockMap);
	}
};

class grmShaderGroup : public datBase
{
private:
	pgPtr<pgDictionary<grcTexturePC>> m_textures;
	pgObjectArray<grmShaderFx> m_shaders;
	pgObjectArray<int> _f10;
	pgObjectArray<int> _f18;
	pgObjectArray<int> _f20;
	pgArray<int> _f28;
	pgArray<int> _f30;
	pgObjectArray<int> _f38;
	pgArray<uint32_t> m_vertexFormats;
	pgArray<uint32_t> m_shaderIndices;

public:
	inline pgDictionary<grcTexturePC>& GetTextures() { return **m_textures; }

	inline grmShaderFx* GetShader(uint16_t offset) { return m_shaders.Get(offset); }

	inline void SetShaders(uint16_t count, pgPtr<grmShaderFx>* shaders)
	{
		m_shaders.SetFrom(shaders, count);
	}

	inline uint32_t GetVertexFormat(uint16_t offset) { return SwapLongRead(m_vertexFormats.Get(offset)); }

	inline void SetVertexFormats(uint16_t count, uint32_t* formats)
	{
		for (int i = 0; i < count; i++)
		{
			formats[i] = SwapLongWrite(formats[i]);
		}

		m_vertexFormats.SetFrom(formats, count);
	}

	inline uint32_t GetShaderIndex(uint16_t offset)
	{
		return SwapLongRead(m_shaderIndices.Get(offset));
	}

	inline void SetShaderIndices(uint16_t count, uint32_t* formats)
	{
		for (int i = 0; i < count; i++)
		{
			formats[i] = SwapLongWrite(formats[i]);
		}

		m_shaderIndices.SetFrom(formats, count);
	}

	inline void Resolve(BlockMap* blockMap = nullptr)
	{
		m_textures.Resolve(blockMap);
		m_textures->Resolve(blockMap);

		m_shaders.Resolve(blockMap);

#ifdef RAGE_FORMATS_GAME_NY
		m_vertexFormats.Resolve(blockMap);
		m_shaderIndices.Resolve(blockMap);
#endif
	}
};

class rmcDrawableBase : public pgBase
{
private:
	pgPtr<grmShaderGroup> m_shaderGroup;

public:
	inline grmShaderGroup* GetShaderGroup() { return *m_shaderGroup; }

	inline void SetShaderGroup(grmShaderGroup* shaderGroup) { m_shaderGroup = shaderGroup; }

	inline void Resolve(BlockMap* blockMap = nullptr)
	{
		m_shaderGroup.Resolve(blockMap);
		m_shaderGroup->Resolve(blockMap);
	}
};

class grcIndexBuffer : public datBase
{
private:
	uint32_t m_indexCount;
	pgPtr<uint16_t, true> m_indexData;

public:
	grcIndexBuffer(uint32_t indexCount, uint16_t* indexData)
	{
		m_indexCount = indexCount;
		
		if (pgStreamManager::IsInBlockMap(indexData, nullptr, true))
		{
			m_indexData = indexData;
		}
		else
		{
			m_indexData = (uint16_t*)pgStreamManager::Allocate(indexCount * sizeof(uint16_t), true, nullptr);
			memcpy(*m_indexData, indexData, indexCount * sizeof(uint16_t));
		}
	}

	inline uint32_t GetIndexCount()
	{
		return m_indexCount;
	}

	inline void Resolve(BlockMap* blockMap = nullptr)
	{
		m_indexData.Resolve(blockMap);
	}
};

class grcIndexBufferD3D : public grcIndexBuffer
{
private:
	void* m_pIIndexBuffer;
	uint32_t m_unk[8];

public:
	grcIndexBufferD3D(uint32_t indexCount, uint16_t* indexData)
		: grcIndexBuffer(indexCount, indexData)
	{
		m_pIIndexBuffer = nullptr;
		memset(m_unk, 0, sizeof(m_unk));
	}

	inline void Resolve(BlockMap* blockMap = nullptr)
	{
		grcIndexBuffer::Resolve(blockMap);
	}
};

class grcVertexFormat : public pgStreamableBase
{
private:
#ifdef RAGE_FORMATS_GAME_NY
	uint16_t m_mask;
	uint16_t _pad;
	uint16_t m_vertexSize;
	uint8_t _f6;
	uint8_t m_vertexFieldCount;
	uint64_t m_vertexFields;
#endif

#ifdef RAGE_FORMATS_GAME_FIVE
	uint32_t m_mask;
	uint16_t m_vertexSize;
	uint16_t m_vertexFieldCount; // maybe still 2 uint8s?
	uint64_t m_vertexFields;
#endif

public:
	grcVertexFormat(uint16_t mask, uint16_t vertexSize, uint8_t fieldCount, uint64_t fvf)
	{
		_pad = 0;
		_f6 = 0;

		m_mask = mask;
		m_vertexSize = vertexSize;
		m_vertexFieldCount = fieldCount;
		m_vertexFields = fvf;
	}

	inline void Resolve(BlockMap* blockMap = nullptr)
	{

	}
};

class grcVertexBuffer : public datBase
{
private:
#ifdef RAGE_FORMATS_GAME_NY
	uint16_t m_vertexCount;
	uint8_t m_locked;
	uint8_t m_pad;
	pgPtr<void> m_lockedData;
	uint32_t m_vertexSize;
	pgPtr<grcVertexFormat> m_vertexFormat;
	uint32_t m_lockThreadId;
	pgPtr<void, true> m_vertexData;
#endif

#ifdef RAGE_FORMATS_GAME_FIVE
	uint16_t m_vertexSize;
	uint8_t m_locked;
	pgPtr<void> m_vertexData;
	uint32_t m_vertexCount;
	uint32_t m_pad[2];
	pgPtr<grcVertexFormat> m_vertexFormat;
	pgPtr<void> m_unkData;
#endif

public:
	grcVertexBuffer()
	{
		m_locked = 0;
		m_pad = 0;
		m_lockThreadId = 0;
	}

	inline void SetVertexFormat(grcVertexFormat* vertexFormat)
	{
		m_vertexFormat = vertexFormat;
	}

	inline void SetVertices(uint32_t vertexCount, uint32_t vertexStride, void* vertexData)
	{
		m_vertexCount = vertexCount;
		m_vertexSize = vertexStride;

		if (pgStreamManager::IsInBlockMap(vertexData, nullptr, true))
		{
			m_vertexData = vertexData;
		}
		else
		{
			m_vertexData = pgStreamManager::Allocate(vertexCount * vertexStride, true, nullptr);
			memcpy(*m_vertexData, vertexData, vertexCount * vertexStride);
		}
	}

	inline uint32_t GetStride()
	{
		return m_vertexSize;
	}

	inline uint32_t GetCount()
	{
		return m_vertexCount;
	}

	inline void Resolve(BlockMap* blockMap = nullptr)
	{
#ifdef RAGE_FORMATS_GAME_NY
		m_lockedData.Resolve(blockMap);
#endif
		m_vertexData.Resolve(blockMap);

		m_vertexFormat.Resolve(blockMap);

		if (!m_vertexFormat.IsNull())
		{
			m_vertexFormat->Resolve(blockMap);
		}
	}
};

class grcVertexBufferD3D : public grcVertexBuffer
{
private:
	void* m_pIVertexBuffer;
	uint32_t m_unk[8];

public:
	inline grcVertexBufferD3D()
	{
		memset(m_unk, 0, sizeof(m_unk));

		m_pIVertexBuffer = nullptr;
	}

	inline void Resolve(BlockMap* blockMap = nullptr)
	{
		grcVertexBuffer::Resolve(blockMap);
	}
};

class grmGeometryQB : public datBase
{
private:
	void* m_vertexDeclaration; // actually IDirect3DVertexDeclaration9* at runtime
	uint32_t _f8;
	pgPtr<grcVertexBufferD3D> m_vertexBuffers[4];
	pgPtr<grcIndexBufferD3D> m_indexBuffers[4];
	uint32_t m_dwIndexCount;
	uint32_t m_dwFaceCount;
	uint16_t m_wVertexCount;
	uint16_t m_wIndicesPerFace;

	// undefined for non-NY
	pgPtr<uint16_t> m_boneMapping;
	uint16_t m_vertexStride;
	uint16_t m_boneCount;
	pgPtr<void> m_vertexDeclarationInstance;
	pgPtr<void> m_vertexBufferInstance;
	uint32_t m_useGlobalStreamIndex;

public:
	inline grmGeometryQB()
	{
		m_vertexDeclaration = nullptr;
		_f8 = 0;
		m_dwIndexCount = 0;
		m_dwFaceCount = 0;
		m_wVertexCount = 0;
		m_wIndicesPerFace = 3;
		m_boneCount = 0;
		m_useGlobalStreamIndex = 0;
	}

	inline void SetVertexBuffer(grcVertexBufferD3D* vertexBuffer)
	{
		m_vertexBuffers[0] = vertexBuffer;
		m_vertexStride = vertexBuffer->GetStride();
		m_wVertexCount = vertexBuffer->GetCount();
	}

	inline void SetIndexBuffer(grcIndexBufferD3D* indexBuffer)
	{
		m_indexBuffers[0] = indexBuffer;
		m_dwIndexCount = indexBuffer->GetIndexCount();
		m_dwFaceCount = indexBuffer->GetIndexCount() / m_wIndicesPerFace;
	}

	inline void Resolve(BlockMap* blockMap = nullptr)
	{
		for (int i = 0; i < 4; i++)
		{
			m_vertexBuffers[i].Resolve(blockMap);

			if (!m_vertexBuffers[i].IsNull())
			{
				m_vertexBuffers[i]->Resolve(blockMap);
			}

			m_indexBuffers[i].Resolve(blockMap);

			if (!m_indexBuffers[i].IsNull())
			{
				m_indexBuffers[i]->Resolve(blockMap);
			}
		}

#ifdef RAGE_FORMATS_GAME_NY
		m_boneMapping.Resolve(blockMap);
#endif
	}
};

#if defined(RAGE_FORMATS_GAME_FIVE)
struct GeometryBound
{
	Vector4 aabbMin;
	Vector4 aabbMax;
};
#endif

class grmModel : public datBase
{
private:
	pgObjectArray<grmGeometryQB> m_geometries;

#if defined(RAGE_FORMATS_GAME_NY)
	pgPtr<Vector4> m_geometryBounds;
#elif defined(RAGE_FORMATS_GAME_FIVE)
	pgPtr<GeometryBound> m_geometryBounds;
#endif
	pgPtr<uint16_t> m_shaderMappings;

	// undefined for non-NY so far
	uint8_t m_boneCount;
	uint8_t m_skinned;
	uint8_t m_pad;
	uint8_t m_zero;
	uint8_t m_zero2;
	uint8_t m_hasBoneMapping;
	uint16_t m_shaderMappingCount; // may be geometry count by proxy?

public:
	inline grmModel()
	{
		m_boneCount = 0;
		m_skinned = 0;
		m_zero = 0;
		m_zero2 = 0;
		m_hasBoneMapping = 0;
		m_shaderMappingCount = 0;
	}

	inline void SetGeometries(int count, grmGeometryQB** geometries)
	{
		static pgPtr<grmGeometryQB> geometriesInd[64];

		for (int i = 0; i < count; i++)
		{
			geometriesInd[i] = geometries[i];
		}

		m_geometries.SetFrom(geometriesInd, count);
	}

	inline void SetGeometryBounds(const Vector4& vector)
	{
		m_geometryBounds = (Vector4*)pgStreamManager::Allocate(sizeof(Vector4), false, nullptr);
		(*m_geometryBounds)[0] = vector;
	}

	inline void SetBoneCount(uint8_t count)
	{
		m_boneCount = count;
	}

	inline void SetShaderMappings(uint16_t count, const uint16_t* shaderMappings)
	{
		m_shaderMappings = (uint16_t*)pgStreamManager::Allocate(sizeof(uint16_t) * count, false, nullptr);

		for (int i = 0; i < count; i++)
		{
			(*m_shaderMappings)[i] = shaderMappings[i];
		}

		m_shaderMappingCount = count;
	}

	inline void Resolve(BlockMap* blockMap = nullptr)
	{
		m_geometries.Resolve(blockMap);
		m_geometryBounds.Resolve(blockMap);
		m_shaderMappings.Resolve(blockMap);
	}
};

class grmLodGroup
{
private:
	Vector3 m_center;
	Vector3 m_boundsMin;
	Vector3 m_boundsMax;
	pgPtr<pgObjectArray<grmModel>> m_models[4];

#ifdef RAGE_FORMATS_GAME_NY
	float m_9999[4];
#endif
#ifdef RAGE_FORMATS_GAME_FIVE
	Vector4 m_maxPoint;
#endif

	int m_drawBucketMask[4]; // does this apply to five?
	float m_radius;
	float m_zeroes[3];

public:
	inline grmLodGroup()
	{
#ifdef RAGE_FORMATS_GAME_NY
		m_9999[0] = 9999.f;
		m_9999[1] = 9999.f;
		m_9999[2] = 9999.f;
		m_9999[3] = 9999.f;
#endif

		m_drawBucketMask[0] = -1;
		m_drawBucketMask[1] = -1;
		m_drawBucketMask[2] = -1;
		m_drawBucketMask[3] = -1;

		m_zeroes[0] = 0;
		m_zeroes[1] = 0;
		m_zeroes[2] = 0;

		m_radius = 0.0f;
	}

	inline Vector3 GetBoundsMin()
	{
		return m_boundsMin;
	}

	inline Vector3 GetBoundsMax()
	{
		return m_boundsMax;
	}

	inline Vector3 GetCenter()
	{
		return m_center;
	}

	inline float GetRadius()
	{
		return m_radius;
	}

	inline void SetBounds(const Vector3& min, const Vector3& max, const Vector3& center, float radius)
	{
		m_boundsMin = min;
		m_boundsMax = max;
		m_center = center;
		m_radius = radius;
	}

	inline grmModel* GetModel(int idx)
	{
		if (idx < 0 || idx >= _countof(m_models))
		{
			FatalError("");
		}

		return m_models[idx]->Get(0);
	}

	inline void SetModel(int idx, grmModel* model)
	{
		if (idx < 0 || idx >= _countof(m_models))
		{
			FatalError("");
		}

		pgPtr<grmModel> models[1];
		models[0] = model;

		m_models[idx] = new(false) pgObjectArray<grmModel>(models, 1);
	}

	inline void SetDrawBucketMask(int idx, int mask)
	{
		if (idx < 0 || idx >= _countof(m_models))
		{
			FatalError("");
		}

		m_drawBucketMask[idx] = mask;
	}

	inline void Resolve(BlockMap* blockMap = nullptr)
	{
		for (int i = 0; i < 4; i++)
		{
			m_models[i].Resolve(blockMap);

			if (!m_models[i].IsNull())
			{
				m_models->Resolve(blockMap);
			}
		}
	}
};

class rmcDrawable : public rmcDrawableBase
{
private:
	pgPtr<crSkeletonData> m_skeletonData;

	grmLodGroup m_lodGroup;

public:
	inline grmLodGroup& GetLodGroup()
	{
		return m_lodGroup;
	}

	inline void Resolve(BlockMap* blockMap = nullptr)
	{
		rmcDrawableBase::Resolve(blockMap);

		m_skeletonData.Resolve(blockMap);

		if (!m_skeletonData.IsNull())
		{
			m_skeletonData->Resolve(blockMap);
		}

		m_lodGroup.Resolve(blockMap);
	}
};
#endif

#include <formats-footer.h>