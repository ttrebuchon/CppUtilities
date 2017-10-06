#pragma once

namespace QUtils
{
	
	struct Byte
	{
		
		constexpr inline static unsigned char BitIndex(const short index)
		{
			switch (index)
			{
				case 0:
				return 1;
				
				case 1:
				return 2;
				
				case 2:
				return 4;
				
				case 3:
				return 8;
				
				case 4:
				return 16;
				
				case 5:
				return 32;
				
				case 6:
				return 64;
				
				case 7:
				return 128;
			}
		}
		
		char value;
		
		constexpr Byte(const unsigned char c) : value(c) {}
		
		inline constexpr bool operator()(const short index) const
		{
			return (value & BitIndex(index)) > 0;
		}
		
		inline constexpr void operator()(const short index, const bool b)
		{
			if (b)
			{
				value |= BitIndex(index);
			}
			else
			{
				value &= (255 - BitIndex(index));
			}
			
		}
	};
	
	constexpr bool Bit(const unsigned char value, const short index)
	{
		return (Byte::BitIndex(index) & value) > 0;
	}
	
	static_assert(sizeof(Byte) == 1, "Byte struct is not one byte");
	
}