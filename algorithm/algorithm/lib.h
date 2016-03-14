#ifndef LIB_H
#define LIB_H

namespace autumnlight {
#include <string>
#include "comm_type.h"
	namespace utils {
		bool string2Ints(const string &str, vint &ints, char delim);
	}
}
#endif;