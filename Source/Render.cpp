#include "pch.hpp"

void Graphics::DrawRectangle ( Color color, float x, float y, float width, float height )
{
}

void Graphics::FillRectangle ( Color color, float x, float y, float width, float height )
{
}

void Graphics::DrawLine ( Color color, float x0, float y0, float x1, float y1 )
{
	mDummyVertex.Set ( Vector ( x0, y0, 0.f ), color );
	mDummyStroage.AddVertex ( mDummyVertex );
	mDummyVertex.Set ( Vector ( x1, y1, 0.f ), color );
	mDummyStroage.AddVertex ( mDummyVertex );
	mOwner.TakeVertices ( *this );
}

void Direct3D9Render::TakeVertices ( Graphics & g )
{
	mVertexStroages.push_back ( g.mDummyStroage );
}

Direct3D9Render::Direct3D9Render ( )
{
}

Direct3D9Render::~Direct3D9Render ( )
{
}

void Direct3D9Render::Initialize ( IDirect3DDevice9 * device )
{
}

Direct3D9Font & Direct3D9Render::CreateFont ( const std::string & font_name, int height, int width, bool italic, int weight )
{
	auto fnt = Direct3D9Font ( *this, font_name, height, width, italic, weight );
	mFonts.push_back ( fnt );
}

void Direct3D9Render::AddStroage ( )
{
}

void Direct3D9Render::Flush ( )
{
}
