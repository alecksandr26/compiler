#ifndef TAG_INCLUDED
#define TAG_INCLUDED

#include <string>

namespace pyc {
	class TagType {
	public:
		enum TagTypeEnum {
			// Names and literals 
			ID = 0,	// variables
			INTEGER,
			REAL,
			STRL,	// strings lieterals
			INDEX,
			TRUE,
			FALSE,
			
			// Arithmetic Operations
			INIT,	// =
			ADD,	// +
			SUB,	// -
			MUL,	// *
			DIV,	// /
			MOD,	// %
			POW,	// **


			// Basic Logical Operations
			GT,	// >
			GE,	// >=
			LT,	// <
			LE,	// <=
			EQ,	// ==
			NEQ, 	// !=

			// Boolean Operations
			AND,
			OR,
			NOT,

			// Structural Paradigm
			IF,
			ELSE,
			ELIF,
			WHILE,
			FOR,
			BREAK,
			CONTINUE,
			DEF,	// functions
			IDENT,	// Python identation ":"
			
			// -------------------------------
			UNKNOWN,
			TAG_COUNT  // Total number of tags
		};
		
		static const std::string tag_types_str[TAG_COUNT];
	};
}

#endif





