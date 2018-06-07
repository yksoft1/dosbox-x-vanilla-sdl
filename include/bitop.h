
#include <limits.h>
#include <stdint.h>

#include <utility>

#if __cplusplus < 201103L
#if !defined(constexpr)
#define constexpr
#define static_assert(a,...) assert(a)
#endif
#endif

namespace bitop {

/* Return the number of bits of the data type.
 *
 * @return Number of bits in data type T
 */
template <typename T> static inline constexpr unsigned int type_bits(void) {
    return (unsigned int)sizeof(T) * (unsigned int)CHAR_BIT;
}

/* Return data type T with all bits 0
 *
 * @return Type T with zero bits
 */
template <typename T> static inline constexpr T allzero(void) {
    return (T)0;
}

/* Return data type T with all bits 1
 *
 * @return Type T with set bits
 */
template <typename T> static inline constexpr T allones(void) {
    return (T)( ~((T)0) );
}


/* Return data type T with value negated
 *
 * This is to avoid typecast messes when masking by the inverse of a constant
 *
 * @return Type T with value negated
 */
template <typename T> static inline constexpr T negate(const T v) {
	return (T)( ~v );
}

/* private */
template <typename T> static inline constexpr unsigned int _bitlength_recursion(const T v,const unsigned int bits) {
	return (v != allzero<T>()) ? _bitlength_recursion(v >> (T)1u,bits + 1u) : bits;
}

/* Return minimum number of bits required to represent value 'v' in data type 'T'
 *
 *  @return Number of bits needed
 */
template <typename T, const T v> static inline constexpr unsigned int bitlength(void) {
	return _bitlength_recursion<T>(v,0);
}

template <const unsigned int v> static inline constexpr unsigned int bitlength(void) {
	return bitlength<unsigned int,v>();
}

template <typename T> static inline unsigned int bitlength(T v) {
	unsigned int c = 0;
	while ((v & 0xFFUL) == 0xFFUL) {
		v >>= (T)8UL;
		c += (T)8;
	}
	while (v != allzero<T>()) {
		v >>= (T)1UL;
		c++;
	}
	return c;
}

/* Return number of sequential 1 bits counting from LSB in value 'v' of type 'T'
*
* @return Number of bits
*/
template <typename T> static inline constexpr unsigned int _bitseqlength_recursionlsb(const T v,const unsigned int bits) {
	return (v & 1u) ? _bitseqlength_recursionlsb<T>(v >> (T)1u,bits + 1u) : bits;
}

template <typename T,const T v> static inline constexpr unsigned int bitseqlengthlsb(void) {
	return _bitseqlength_recursionlsb<T>(v,0);
}

template <const unsigned int v> static inline constexpr unsigned int bitseqlengthlsb(void) {
	return bitseqlengthlsb<unsigned int,v>();
}

template <typename T> static inline void _bitseqlengthlsb_1(unsigned int &c,T &v) {
	while ((v & 0xFFUL) == 0xFFUL) {
		v >>= (T)8UL;
		c += (T)8;
	}
	while (v & 1u) {
		v >>= (T)1UL;
		c++;
	}
}

template <typename T> static inline unsigned int bitseqlengthlsb(T v) {
	unsigned int c = 0;
	_bitseqlengthlsb_1(/*&*/c,/*&*/v);
	return c;
}


/* Return binary mask of bit 'a'
 *
 * @return Bitmask
 */
template <unsigned int a,typename T> static inline constexpr T bit2mask(void) {
    static_assert(a < type_bits<T>(), "bit2mask constexpr bit count too large for data type");
    return (T)1U << (T)a;
}

template <typename T> static inline constexpr T bit2mask(unsigned int a) {
    return (T)1U << (T)a;
}

/* Return binary mask of MSB in type 'T'
 *
 * @return Bitmask
 */
template <typename T> static inline constexpr T type_msb_mask(void) {
    return bit2mask<T>(type_bits<T>() - 1u);
}

#if __cplusplus >= 201103L //There seemed to be no way to implement this without constexpr
/* Return binary mask of 'a' LSB bits starting at bit offset 'offset' in type 'T'
 *
 * @return Bitmask
 */
template <const unsigned int a,const unsigned int offset,typename T=unsigned int> static inline constexpr T bitcount2masklsb(void) {
	/* NTS: special case for a == type_bits because shifting the size of a register OR LARGER is undefined.
	 * On Intel x86 processors, with 32-bit integers, x >> 32 == x >> 0 because only the low 5 bits are used
	 * a % type_bits<T>() is there to keep a < type_bits<T> in case your C++11 compiler likes to trigger
	 * all static_assert<> clauses even if the ternary would not choose that path. */
	static_assert(a <= type_bits<T>(), "bitcount2masklsb constexpr bit count too large for data type");
	static_assert(offset < type_bits<T>(), "bitcount2masklsb constexpr offset count too large for data type");
	static_assert((a+offset) <= type_bits<T>(), "bitcount2masklsb constexpr bit count + offset count too large for data type");
	return ((a < type_bits<T>()) ? (bit2mask<a % type_bits<T>(),T>() - (T)1u) : allones<T>()) << (T)offset;
}


template <const unsigned int a,typename T> static inline constexpr T bitcount2masklsb(void) {
    return bitcount2masklsb<a,0u,T>();
}


#endif

template <typename T> static inline constexpr T bitcount2masklsb(const unsigned int a,const unsigned int offset=0) {
    /* NTS: special case for a == type_bits because shifting the size of a register OR LARGER is undefined.
     *      On Intel x86 processors, with 32-bit integers, x >> 32 == x >> 0 because only the low 5 bits are used */
	
	 return ((a < type_bits<T>()) ? (bit2mask<T>(a) - (T)1u) : allones<T>()) << (T)offset;
}

/* Return binary mask of 'a' MSB bits starting at bit offset 'offset' in type 'T'
 *
 * @return Bitmask
 */
template <const unsigned int a,const unsigned int offset,typename T> static inline constexpr T bitcount2maskmsb(void) {
	/* NTS: special case for a == type_bits because shifting the size of a register OR LARGER is undefined.
	 * On Intel x86 processors, with 32-bit integers, x >> 32 == x >> 0 because only the low 5 bits are used
	 * a % type_bits<T>() is there to keep a < type_bits<T> in case your C++11 compiler likes to trigger
	 * all static_assert<> clauses even if the ternary would not choose that path. */
	static_assert(a <= type_bits<T>(), "bitcount2maskmsb constexpr bit count too large for data type");
	static_assert(offset < type_bits<T>(), "bitcount2maskmsb constexpr offset count too large for data type");
	static_assert((a+offset) <= type_bits<T>(), "bitcount2maskmsb constexpr bit count + offset count too large for data type");
	return ((a != (T)0) ? ((T)(allones<T>() << (T)(type_bits<T>() - a)) >> (T)offset) : allzero<T>());
}

template <const unsigned int a,typename T> static inline constexpr T bitcount2maskmsb(void) {
	return bitcount2maskmsb<a,0u,T>();
}

template <typename T> static inline constexpr T bitcount2maskmsb(const unsigned int a,const unsigned int offset=0) {
	/* NTS: special case for a == type_bits because shifting the size of a register OR LARGER is undefined.
	 * On Intel x86 processors, with 32-bit integers, x >> 32 == x >> 0 because only the low 5 bits are used */
	return ((a != (T)0) ? ((T)(allones<T>() << (T)(type_bits<T>() - a)) >> (T)offset) : allzero<T>());
}

/* Indicate whether 'a' is a power of 2.
 *
 * This code will NOT work correctly if a == 0, the result is to be considered undefined.
 *
 * @return Boolean true if 'a' is a power of 2 */
template <typename T> static inline constexpr T ispowerof2(const unsigned int a) {
	return (a & (a-(T)1u)) == 0;
}


/* Return log2(v), or the bit position of the highest '1' bit of value 'v'
 *
 * A value of '0' will return allones<unsigned int>() to indicate an invalid value.
 *
 * The constexpr templated version will trigger a static_assert if v == 0.
 *
 * log2(2^31) == 31
 * log2(2^30) == 30
 * log2(2^16) == 16 2^16 == 65536
 * log2(2^4) == 4 2^4 == 16
 * log2(2^1) == 1 2^1 == 2
 * log2(2^0) == 0 2^0 == 1
 * log2(0) == ~0u (UINT_MAX or allones())
 *
 * @return Bitmask
 */

/* private recursion function */
template <typename T> static inline constexpr unsigned int _log2_recursion(const T v,const unsigned int bits) {
	/* NTS: The additional check against v == allzero() is needed to avoid an infinite recursion loop */
	return (v != allzero<T>()) ?
			(((v & type_msb_mask<T>()) == allzero<T>()) ? _log2_recursion(v << (T)1u,bits - 1u) : bits) :
			(~0u);
}

template <typename T,const T v> static inline constexpr unsigned int log2(void) {
	return _log2_recursion<T>(v,type_bits<T>() - 1u);
}

template <const unsigned int v> static inline constexpr unsigned int log2(void) {
	return log2<unsigned int,v>();
}

/* non-constant version for runtime use */
template <typename T> static inline unsigned int log2(T v) {
	if (v != allzero<T>()) {
		unsigned int c = type_bits<T>() - 1u;

		while (!(v & type_msb_mask<T>())) {
			v <<= (T)1UL;
			c--;
		}

		return c;
	}

	return ~0u;
}

/* return type, pair */
class bitseqlengthandpos_ret_t {
	public:
		bitseqlengthandpos_ret_t(const unsigned int _start,const unsigned int _length) : start(_start), length(_length) { }
	public:
		bool operator==(const bitseqlengthandpos_ret_t &n) const {
			return (n.start == start) &&
			(n.length == length);
		}
		bool empty(void) const {
			return (start == 0u && length == 0u);
		}
	public:
		unsigned int start, length;
};

/* return a pair struct representing start and length of a series of 1 bits */
template <typename T> static inline bitseqlengthandpos_ret_t bitseqlengthandpos(T v) {
	if (v != bitop::allzero<T>()) {
		unsigned int start=0,length=0;

		/* count zeros */
		while ((v & (T)0xFFUL) == (T)0x00UL) {
			start += (T)8;
			v >>= (T)8UL;
		}
		while (!(v & (T)1u)) {
			start++;
			v >>= (T)1UL;
		}

		/* count ones */
		while ((v & (T)0xFFUL) == (T)0xFFUL) {
			length += (T)8;
			v >>= (T)8UL;
		}
		while (v & (T)1u) {
			length++;
			v >>= (T)1UL;
		}

		return bitseqlengthandpos_ret_t(start,length);
	}

	return bitseqlengthandpos_ret_t(0u,0u);
}

void self_test();

}
