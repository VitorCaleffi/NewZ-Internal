#pragma once

template <typename return_t, typename... forward_args_t>
class Event
{
public:

	using Function = return_t ( __stdcall * )( forward_args_t... args );

	Event()
	{
	}

	~Event()
	{
	}

	void operator ()( forward_args_t... args ) const
	{
		for ( auto& fn : mFunctions )
			fn ( args );
	}

	Event& operator += ( Function fn )
	{
		mFunctions += fn;
	}

private:
	std::list < std::function < Function > > mFunctions;
};

