	template<class T>
	struct precision_trait {
		enum { precisionRank = 0,
			knowPrecisionRank = 0 };
	};
#define DECLARE_PRECISION(T,rank) \
	template<> \
	struct precision_trait< T > { \
	enum { precisionRank = rank, \
	knowPrecisionRank = 1 }; \
	};
	DECLARE_PRECISION(int,100)
	DECLARE_PRECISION(unsigned int,200)
	DECLARE_PRECISION(long,300)
	DECLARE_PRECISION(unsigned long,400)
	DECLARE_PRECISION(float,500)
	DECLARE_PRECISION(double,600)
	DECLARE_PRECISION(long double,700)

	template<class T>
	struct autopromote_trait {
		typedef T T_numtype;
	};
#define DECLARE_AUTOPROMOTE(T1,T2) \
	template<> \
	struct autopromote_trait<T1> { \
	typedef T2 T_numtype; \
	};
	// These are the odd cases where small integer types
	// are automatically promoted to int or unsigned int for
	// arithmetic.
	DECLARE_AUTOPROMOTE(bool, int)
	DECLARE_AUTOPROMOTE(char, int)
	DECLARE_AUTOPROMOTE(unsigned char, int)
	DECLARE_AUTOPROMOTE(short int, int)
	DECLARE_AUTOPROMOTE(short unsigned int, unsigned int)
	template<class T1, class T2, int promoteToT1>
	struct promote2 {
		typedef T1 T_promote;
	};
	template<class T1, class T2>
	struct promote2<T1,T2,0> {
		typedef T2 T_promote;
	};
	template<class T1_orig, class T2_orig>
	struct promote_trait {
		// Handle promotion of small integers to int/unsigned int
		typedef typename autopromote_trait<T1_orig>::T_numtype T1;
		typedef typename autopromote_trait<T2_orig>::T_numtype T2;
		// True if T1 is higher ranked
		enum {
			T1IsBetter =
			precision_trait<T1>::precisionRank >
			precision_trait<T2>::precisionRank,
			// True if we know ranks for both T1 and T2
			knowBothRanks =
			precision_trait<T1>::knowPrecisionRank
			&& precision_trait<T2>::knowPrecisionRank,

			// True if we know T1 but not T2
			knowT1butNotT2 = precision_trait<T1>::knowPrecisionRank
			&& !(precision_trait<T2>::knowPrecisionRank),
			// True if we know T2 but not T1
			knowT2butNotT1 = precision_trait<T2>::knowPrecisionRank
			&& !(precision_trait<T1>::knowPrecisionRank),
			// True if T1 is bigger than T2
			T1IsLarger = sizeof(T1) >= sizeof(T2),
			// We know T1 but not T2: true
			// We know T2 but not T1: false
			// Otherwise, if T1 is bigger than T2: true
			defaultPromotion = knowT1butNotT2 ? _bz_false :
			(knowT2butNotT1 ? _bz_true : T1IsLarger)
		};
		// If we have both ranks, then use them.
		// If we have only one rank, then use the unknown type.
		// If we have neither rank, then promote to the larger type.
		enum {
			promoteToT1 = (knowBothRanks ? T1IsBetter : defaultPromotion)
			? 1 : 0
		};
		typedef typename promote2<T1,T2,promoteToT1>::T_promote T_promote;
	};

