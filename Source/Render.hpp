#pragma once

#undef CreateFont

typedef uint32_t Color;

class Direct3D9Font;
class Graphics;

enum VertexType
{
	
};

class Vertex
{
public:
	Vertex ( ) :
		mPosition ( ), mRHW ( 1.f ), mColor ( 0x00000000 )
	{
		mUV [ 0 ] = 0.f;
		mUV [ 1 ] = 0.f;
	}
	explicit Vertex ( const Vector& vec, uint32_t color, float ( &uv ) [ 2 ] ) : 
		mPosition(vec), mRHW ( 1.f )
	{
		mUV [ 0 ] = uv [ 0 ];
		mUV [ 1 ] = uv [ 1 ];
	}
	explicit Vertex ( const Vector& vec, uint32_t color ) : mRHW ( 1.f )
	{
		mUV [ 0 ] = mUV [ 1 ] = 0.f;
	}
	~Vertex()
	{
	}

	void Set( const Vector& vec, uint32_t color, float u = 0.f, float v = 0.f)
	{
		mPosition = vec;
		mRHW = 1.f;
		mColor = color;
		mUV [ 0 ] = u;
		mUV [ 1 ] = v;
	}

private:
	Vector mPosition;
	float mRHW;
	uint32_t mColor;
	float mUV [ 2 ];
};

class VertexStroage
{
public:
	VertexStroage ( )
	{
		
	}
	~VertexStroage ( )
	{
		
	}

	attr_alwaysinline Vertex* GetStart ( )
	{
		return &mVertices [ 0 ];
	}

	attr_alwaysinline size_t GetSize() const
	{
		return mVertices.size ( );
	}

	attr_alwaysinline size_t GetTotalSize() const
	{
		return mVertices.size ( ) * sizeof ( Vertex );
	}

	void AddVertex ( const Vertex& vertex )
	{
		mVertices.push_back ( vertex );
	}

private:
	std::vector<Vertex> mVertices;
};

class Direct3D9Render
{
public:
	Direct3D9Render ( );
	~Direct3D9Render ( );

	void Initialize ( IDirect3DDevice9* device );

	Direct3D9Font& CreateFont ( const std::string& font_name, int height, int width, bool italic, int weight );

	void AddStroage ( );

	void Flush ( );

private:
	std::list< Direct3D9Font > mFonts;
	std::vector<VertexStroage> mVertexStroages;
};

class Direct3D9Font
{
public:
	void Delete ( );
	void Measure ( const std::string& text, float& wide, float& high );
	void PrintF ( const std::string& text, float x, float y, uint32_t flags, float width = 0.f, float height = 0.f ); 

private:
	friend Direct3D9Font & Direct3D9Render::CreateFont ( const std::string & font_name, int height, int width, bool italic, int weight );

	Direct3D9Font ( Direct3D9Render& render, const std::string& font_name, int height, int width, bool italic, int weight );
	~Direct3D9Font ( );

	struct GlyphInfo
	{
		
	};
	std::map<char, GlyphInfo> mGlyphs;

	Direct3D9Render mOwner;
};

class Graphics
{
public:
	explicit Graphics ( Direct3D9Render& render ) :
		mOwner ( render )
	{
	}
	~Graphics ( )
	{
		
	}

	void DrawRectangle ( Color color, float x, float y, float width, float height );
	void FillRectangle ( Color color, float x, float y, float width, float height );
	void DrawLine ( Color color, float x0, float y0, float x1, float y1 );

private:
	friend void Direct3D9Render::TakeVertices ( Graphics& g );

	VertexStroage mDummyStroage;
	Vertex mDummyVertex;
	Direct3D9Render& mOwner;
};

attr_alwaysinline Direct3D9Render& GetRender ( );
