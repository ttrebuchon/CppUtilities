#pragma once
#include <QUtils/Types/TypeSequence.h>
#include <limits>
#include <cstdlib>
#include <algorithm>


namespace QUtils { namespace Network {
namespace SocketProtocol {
	
	namespace Helpers
	{
		class Endianness
		{
			private:
			static constexpr uint32_t uint32_ = 0x01020304;
			static constexpr uint8_t magic_ = (const uint8_t&)uint32_;
			public:
			static constexpr bool little = magic_ == 0x04;
			static constexpr bool middle = magic_ == 0x02;
			static constexpr bool big = magic_ == 0x01;
			static_assert(little || middle || big, "Cannot determine endianness!");
			private:
			Endianness() = delete;
		};
		
		
		constexpr int HostIsBigEndian()
		{
			/*constexpr union
			{
				uint32_t i;
				char c[4];
			} _32b_union = {0x01020304};
			constexpr bool value = _32b_union.c[0] == 1;
			return value;*/
			return Endianness::big;
		}
		
		template <class T>
		constexpr T ToNetEndian(T value) noexcept
		{
			constexpr const bool bigEnd = HostIsBigEndian();
			if (!bigEnd)
			{
				char* ptr = reinterpret_cast<char*>(&value);
				std::reverse(ptr, ptr + sizeof(T));
			}
			return value;
		}
		
		template <class T>
		constexpr T ToHostEndian(T value)
		{
			constexpr const bool bigEnd = HostIsBigEndian();
			if (!bigEnd)
			{
				char* ptr = reinterpret_cast<char*>(&value);
				std::reverse(ptr, ptr + sizeof(T));
			}
			return value;
		}
		
		
		
		static_assert(HostIsBigEndian() || !HostIsBigEndian(), "");
		
		
		constexpr unsigned long long _MaxValue(const size_t s)
		{
			if (s == 1)
			{
				return 256;
			}
			
			return 256*_MaxValue(s-1);
		}
		
		constexpr unsigned long long MaxValue(const size_t s)
		{
			if (s == 1)
			{
				return 255;
			}
			else if (s == 0)
			{
				return 0;
			}
			
			return _MaxValue(s) - 1;
		}
		
		template <bool Value, int Size, class T, class... G>
		struct _SmallestType {};
		
		
		
		template <int Size, class T, class... G>
		struct _SmallestType<true, Size, T, G...>
		{
			typedef T type;
		};
		
		template <int Size, class T, class H, class... G>
		struct _SmallestType<false, Size, T, H, G...>
		{
			typedef typename _SmallestType<MaxValue(Size) <= std::numeric_limits<H>::max(), Size, H, G...>::type type;
		};
		
		template <int Size, class T, class... G>
		struct SmallestType
		{
			typedef typename _SmallestType<MaxValue(Size) <= std::numeric_limits<T>::max(), Size, T, G...>::type type;
			constexpr static size_t size = sizeof(type);
			constexpr static size_t type_size = sizeof(type);
			constexpr static size_t RawSize = Size;
			constexpr static type Max = MaxValue(RawSize);
			
			inline static type Read(const char* data)
			{
				type num = 0;
				if (!HostIsBigEndian())
				{
					std::reverse_copy(data, data+Size, (char*)&num);
				}
				else
				{
					::memcpy(((char*)&num)+(type_size-Size), data, Size*sizeof(char));
				}
				return num;
			}
			
			inline static char* Write(const type num)
			{
				char* num_arr = new char[Size];
				Write(num, num_arr);
				return num_arr;
			}
			
			inline static void Write(const type num, char* num_arr)
			{
				if (!HostIsBigEndian())
				{
					std::reverse_copy((char*)&num, ((char*)&num) + Size, num_arr);
				}
				else
				{
					::memcpy(num_arr, &num+(type_size-Size), Size);
				}
			}
			
		};
		
	}
	
	
	template <int ID_s, int Length_s, int Checksum_s>
	struct HeaderSpec
	{
		const static auto ID_Size = ID_s;
		const static auto Length_Size = Length_s;
		const static auto Checksum_Size = Checksum_s;
		
		constexpr static auto Header_Size = ID_Size + Length_Size + Checksum_Size;
		
		typedef Helpers::SmallestType<
			ID_Size,
			unsigned char,
			unsigned int,
			unsigned long,
			unsigned long long
		> MsgID_Info;
		
		typedef Helpers::SmallestType<
			Length_Size,
			unsigned char,
			unsigned int,
			unsigned long,
			unsigned long long
		> MsgLen_Info;
		
		typedef Helpers::SmallestType<
			Checksum_Size,
			unsigned char,
			unsigned int,
			unsigned long,
			unsigned long long
		> MsgChecksum_Info;
		
		typedef typename MsgID_Info::type MsgID_t;
		typedef typename MsgLen_Info::type MsgLen_t;
		typedef typename MsgChecksum_Info::type MsgChecksum_t;
		
		//Aliases
		typedef MsgLen_Info MsgLength_Info;
		typedef MsgLen_t MsgLength_t;
	};
	
	typedef HeaderSpec<1, 4, 3> DefaultSpec;
	
} } }