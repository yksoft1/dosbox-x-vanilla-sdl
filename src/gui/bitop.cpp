
#include <assert.h>

#include "bitop.h"

namespace bitop {

void self_test(void) {
    // DEBUG
#if __cplusplus >= 201103L
    static_assert(bitcount2masklsb<0u>() == 0u);
    static_assert(bitcount2masklsb<1u>() == 1u, "whoops");
    static_assert(bitcount2masklsb<2u>() == 3u, "whoops");
    static_assert(bitcount2masklsb<2u,1u>() == 6u, "whoops");
    static_assert(bitcount2masklsb<2u,uint8_t>() == 3u, "whoops");
    static_assert(bitcount2masklsb<2u,0u,uint8_t>() == 3u, "whoops");
    static_assert(bitcount2masklsb<2u,1u,uint8_t>() == 6u, "whoops");
    static_assert(bitcount2masklsb<type_bits<>()>() == allones(), "whoops");
#endif
    assert(allones<uint32_t>() == (uint32_t)0xFFFFFFFFUL);
    assert(allzero<uint32_t>() == (uint32_t)0);
    assert(allones<uint64_t>() == (uint64_t)0xFFFFFFFFFFFFFFFFULL);
    assert(allzero<uint64_t>() == (uint64_t)0);
    assert((~allones<uint32_t>()) == allzero<uint32_t>());
    assert((~allzero<uint32_t>()) == allones<uint32_t>());
    assert(type_bits<uint64_t>() == 64u);
    assert(type_bits<uint32_t>() == 32u);
    assert(type_bits<uint16_t>() == 16u);
    assert(type_bits<uint8_t>() == 8u);
    assert(bit2mask<unsigned int>(0u) == 1u);
    assert(bit2mask<unsigned int>(8u) == 256u);
    assert((bit2mask<8u,unsigned int>() == 256u));
    assert((bit2mask<9u,unsigned int>() == 512u));
    assert((bit2mask<33u,uint64_t>() == (1ull << 33ull)));
    assert(bitlength(0u) == 0u);
    assert(bitlength(1u) == 1u);
    assert(bitlength(2u) == 2u);
    assert(bitlength(3u) == 2u);
    assert(bitlength(4u) == 3u);
    assert(bitlength(7u) == 3u);
    assert(bitlength(8u) == 4u);
	assert(bitlength(255u) == 8u);
	assert(bitlength(256u) == 9u);
	assert(bitlength(512u) == 10u);
	assert(bitlength(1024u) == 11u);
	assert(bitlength(32767u) == 15u);
	assert(bitlength(32768u) == 16u);
	
    assert(bitlength(~0u) == type_bits<unsigned int>());
    assert(type_msb_mask<uint8_t>() == 0x80u);
    assert(type_msb_mask<uint16_t>() == 0x8000u);
    assert(type_msb_mask<uint32_t>() == 0x80000000UL);
    assert(type_msb_mask<uint64_t>() == 0x8000000000000000ULL);
	
	static_assert((bitseqlengthlsb<unsigned int, 0u>() == 0u), "whoops"); // 0
	static_assert((bitseqlengthlsb<unsigned int, 1u>() == 1u), "whoops"); // 1
	static_assert((bitseqlengthlsb<unsigned int, 2u>() == 0u), "whoops"); // 10
	static_assert((bitseqlengthlsb<unsigned int, 3u>() == 2u), "whoops"); // 11
	static_assert((bitseqlengthlsb<unsigned int, 4u>() == 0u), "whoops"); // 100
	static_assert((bitseqlengthlsb<unsigned int, 5u>() == 1u), "whoops"); // 101
	static_assert((bitseqlengthlsb<unsigned int, 6u>() == 0u), "whoops"); // 110
	static_assert((bitseqlengthlsb<unsigned int, 7u>() == 3u), "whoops"); // 111
	static_assert((bitseqlengthlsb<unsigned int, 8u>() == 0u), "whoops"); // 1000
	static_assert((bitseqlengthlsb<unsigned int, 9u>() == 1u), "whoops"); // 1001
	static_assert((bitseqlengthlsb<unsigned int, 10u>() == 0u), "whoops"); // 1010
	static_assert((bitseqlengthlsb<unsigned int, 11u>() == 2u), "whoops"); // 1011
	static_assert((bitseqlengthlsb<unsigned int, 12u>() == 0u), "whoops"); // 1100
	static_assert((bitseqlengthlsb<unsigned int, 15u>() == 4u), "whoops"); // 1111
	static_assert((bitseqlengthlsb<unsigned int, 23u>() == 3u), "whoops"); // 10111
	static_assert((bitseqlengthlsb<unsigned int, 31u>() == 5u), "whoops"); // 11111
	static_assert((bitseqlengthlsb<unsigned int, ~0u>() == type_bits<unsigned int>()), "whoops");
	
	assert(bitlength(0u) == 0u);
	assert(bitlength(1u) == 1u);
	assert(bitlength(2u) == 2u);
	assert(bitlength(3u) == 2u);
	assert(bitlength(4u) == 3u);
	assert(bitlength(7u) == 3u);
	assert(bitlength(255u) == 8u);
	assert(bitlength(256u) == 9u);
	assert(bitlength(512u) == 10u);
	assert(bitlength(1024u) == 11u);
	assert(bitlength(32767u) == 15u);
	assert(bitlength(32768u) == 16u);
	
	assert(bitseqlengthlsb(0u) == 0u);
	assert(bitseqlengthlsb(1u) == 1u);
	assert(bitseqlengthlsb(2u) == 0u);
	assert(bitseqlengthlsb(3u) == 2u);
	assert(bitseqlengthlsb(4u) == 0u);
	assert(bitseqlengthlsb(5u) == 1u);
	assert(bitseqlengthlsb(6u) == 0u);
	assert(bitseqlengthlsb(7u) == 3u);
	assert(bitseqlengthlsb(255u) == 8u);
	assert(bitseqlengthlsb(256u) == 0u);
	assert(bitseqlengthlsb(512u) == 0u);
	assert(bitseqlengthlsb(1024u) == 0u);
	assert(bitseqlengthlsb(32767u) == 15u);
	assert(bitseqlengthlsb(32768u) == 0u);
	
	static_assert((bitcount2maskmsb<0u,unsigned int>() == 0u), "whoops");
	static_assert((bitcount2maskmsb<1u,unsigned int>() == (1u << (type_bits<unsigned int>() - 1u))), "whoops");
	static_assert((bitcount2maskmsb<2u,unsigned int>() == (3u << (type_bits<unsigned int>() - 2u))), "whoops");
	static_assert((bitcount2maskmsb<2u,1u,unsigned int>() == (3u << (type_bits<unsigned int>() - 3u))), "whoops");
	static_assert((bitcount2maskmsb<2u,uint8_t>() == (3u << 6u)), "whoops");
	static_assert((bitcount2maskmsb<2u,0u,uint8_t>() == (3u << 6u)), "whoops");
	static_assert((bitcount2maskmsb<2u,1u,uint8_t>() == (3u << 5u)), "whoops");
#if __cplusplus >= 201103L
	static_assert(bitcount2maskmsb<type_bits()>() == allones(), "whoops");
#endif	
	
	assert(bitcount2masklsb<unsigned int>(0u) == 0u);
	assert(bitcount2masklsb<unsigned int>(1u) == 1u);
	assert(bitcount2masklsb<unsigned int>(2u) == 3u);
	assert(bitcount2masklsb<unsigned int>(2u,1u) == 6u);
	assert(bitcount2masklsb<uint8_t>(2u) == 3u);
	assert(bitcount2masklsb<uint8_t>(2u,0u) == 3u);
	assert(bitcount2masklsb<uint8_t>(2u,1u) == 6u);
	assert(bitcount2masklsb<unsigned int>(type_bits<unsigned int>()) == allones<unsigned int>());
	
	assert(bitcount2maskmsb<unsigned int>(0u) == 0u);
	assert(bitcount2maskmsb<unsigned int>(1u) == (1u << (type_bits<unsigned int>() - 1u)));
	assert(bitcount2maskmsb<unsigned int>(2u) == (3u << (type_bits<unsigned int>() - 2u)));
	assert(bitcount2maskmsb<unsigned int>(2u,1u) == (3u << (type_bits<unsigned int>() - 3u)));
	assert(bitcount2maskmsb<uint8_t>(2u) == (3u << 6u));
	assert(bitcount2maskmsb<uint8_t>(2u,0u) == (3u << 6u));
	assert(bitcount2maskmsb<uint8_t>(2u,1u) == (3u << 5u));
	assert(bitcount2maskmsb<unsigned int>(type_bits<unsigned int>()) == allones<unsigned int>());	
	
	static_assert(ispowerof2<unsigned int>(1u) == true, "whoops");
	static_assert(ispowerof2<unsigned int>(2u) == true, "whoops");
	static_assert(ispowerof2<unsigned int>(3u) == false, "whoops");
	static_assert(ispowerof2<unsigned int>(4u) == true, "whoops");
	static_assert(ispowerof2<unsigned int>(5u) == false, "whoops");
	static_assert(ispowerof2<unsigned int>(6u) == false, "whoops");
	static_assert(ispowerof2<unsigned int>(7u) == false, "whoops");
	static_assert(ispowerof2<unsigned int>(8u) == true, "whoops");
	static_assert(ispowerof2<unsigned int>(9u) == false, "whoops");
	static_assert(ispowerof2<unsigned int>(10u) == false, "whoops");
	static_assert(ispowerof2<unsigned int>(11u) == false, "whoops");
	static_assert(ispowerof2<unsigned int>(255u) == false, "whoops");
	static_assert(ispowerof2<unsigned int>(256u) == true, "whoops");
	static_assert(ispowerof2<unsigned int>(257u) == false, "whoops");
	static_assert(ispowerof2<unsigned int>(32767u) == false, "whoops");
	static_assert(ispowerof2<unsigned int>(32768u) == true, "whoops");
	static_assert(ispowerof2<unsigned int>(32769u) == false, "whoops");

	assert(ispowerof2<unsigned int>(1u) == true);
	assert(ispowerof2<unsigned int>(2u) == true);
	assert(ispowerof2<unsigned int>(3u) == false);
	assert(ispowerof2<unsigned int>(4u) == true);
	assert(ispowerof2<unsigned int>(5u) == false);
	assert(ispowerof2<unsigned int>(6u) == false);
	assert(ispowerof2<unsigned int>(7u) == false);
	assert(ispowerof2<unsigned int>(8u) == true);
	assert(ispowerof2<unsigned int>(9u) == false);
	assert(ispowerof2<unsigned int>(10u) == false);
	assert(ispowerof2<unsigned int>(11u) == false);
	assert(ispowerof2<unsigned int>(255u) == false);
	assert(ispowerof2<unsigned int>(256u) == true);
	assert(ispowerof2<unsigned int>(257u) == false);
	assert(ispowerof2<unsigned int>(32767u) == false);
	assert(ispowerof2<unsigned int>(32768u) == true);
	assert(ispowerof2<unsigned int>(32769u) == false);
}

}

