#pragma once

#include  "../defines.h"

namespace star
{
	struct Color final
	{
		float32 r, g, b, a;

		static const Color
			AliceBlue,
			AntiqueWhite,
			Aqua,
			Aquamarine,
			Azure,
			Beige,
			Bisque,
			Black,
			BlanchedAlmond,
			Blue,
			BlueViolet,
			Brown,
			BurlyWood,
			CadetBlue,
			Chartreuse,
			Chocolate,
			Colar,
			CornflowerBlue,
			Cornsilk,
			Crimson,
			Cyan,
			DarkBlue,
			DarkCyan,
			DarkGoldenrod,
			DarkGray,
			DarkGreen,
			DarkKhaki,
			DarkMagenta,
			DarkOliveGreen,
			DarkOrange,
			DarkOrchild,
			DarkRed,
			DarkSalmon,
			DarkSeaGreen,
			DarkSlateBlue,
			DarkSlateGray,
			DarkTurquoise,
			DarkViolet,
			DeepPink,
			DeepSkyBlue,
			DimGray,
			DodgetBlue,
			Firebrick,
			FloralWhite,
			ForestGreen,
			Fuchsia,
			Gainsboro,
			GhostWhite,
			Gold,
			Goldenrod,
			Gray,
			Green,
			GreenYellow,
			Honeydew,
			HotPink,
			IndianRed,
			Indigo,
			Ivory,
			Khaki,
			Lavender,
			LavenderBlush,
			LawnGreen,
			LemonChiffon,
			LightBlue,
			LightCoral,
			LightCyan,
			LightGoldenrodYellow,
			LightGray,
			LightGreen,
			LightPink,
			LightSalmon,
			LightSeaGreen,
			LightSkyBlue,
			LightSlateGray,
			LightSteelBlue,
			LightYellow,
			Lime,
			LimeGreen,
			Linen,
			Magenta,
			Maroon,
			MediumAquamarine,
			MediumBlue,
			MediumOrchid,
			MediumPurple,
			MediumSeaGreen,
			MediumSlateBlue,
			MediumSpringGreen,
			MediumTurquoise,
			MediumVioletRed,
			MidnightBlue,
			MintCream,
			MistyRose,
			Moccasin,
			NavajoWhite,
			Navy,
			OldLace,
			Olive,
			OliveDrab,
			Orange,
			OrangeRed,
			Orchid,
			PaleGoldenrod,
			PaleGreen,
			PaleTurquoise,
			PaleVioletRed,
			PapayaWhip,
			PeachPuff,
			Peru,
			Pink,
			Plum,
			PowderBlue,
			Purple,
			Red,
			RosyBrown,
			RoyalBlue,
			SaddleBrown,
			Salmon,
			SandyBrown,
			SeaGreen,
			SeaShell,
			Sienna,
			Silver,
			SkyBlue,
			SlateBlue,
			SlateGray,
			Snow,
			SpringGreen,
			SteelBlue,
			Tan,
			Teal,
			Thistle,
			Tomato,
			Transparant,
			Turqouise,
			Violet,
			Wheat,
			White,
			WhiteSmoke,
			Yellow,
			YellowGreen;

		Color();
		Color(uint16 R, uint16 G, uint16 B, uint16 A = 255);
		Color(uint32 R, uint32 G, uint32 B, uint32 A = 255);
		Color(uint64 R, uint64 G, uint64 B, uint64 A = 255);
		Color(int16 R, int16 G, int16 B, int16 A = 255);
		Color(int32 R, int32 G, int32 B, int32 A = 255);
		Color(int64 R, int64 G, int64 B, int64 A = 255);
		Color(float32 R, float32 G, float32 B, float32 A = 1.0f);
		Color(float64 R, float64 G, float64 B, float64 A = 1.0);
		Color(const Color & yRef);
		Color(Color && yRef);
		Color(const vec3 & yRef);
		Color(const vec4 & yRef);
		Color(const ivec3 & yRef);
		Color(const ivec4 & yRef);

		Color & operator=(const Color & yRef);
		Color & operator=(const vec3 & yRef);
		Color & operator=(const vec4 & yRef);
		Color & operator=(const ivec3 & yRef);
		Color & operator=(const ivec4 & yRef);

		Color & operator+=(const Color & yRef);
		Color & operator+=(const vec3 & yRef);
		Color & operator+=(const vec4 & yRef);
		Color & operator+=(const ivec3 & yRef);
		Color & operator+=(const ivec4 & yRef);

		Color & operator-=(const Color & yRef);
		Color & operator-=(const vec3 & yRef);
		Color & operator-=(const vec4 & yRef);
		Color & operator-=(const ivec3 & yRef);
		Color & operator-=(const ivec4 & yRef);

		template <typename T>
		Color & operator*=(T x);

		template <typename T>
		Color & operator/=(T x);

		template <typename T>
		Color operator*(T x);

		template <typename T>
		Color operator/(T x);
		
		Color operator+(const Color & yRef) const;
		Color operator+(const vec3 & yRef) const;
		Color operator+(const vec4 & yRef) const;
		Color operator+(const ivec3 & yRef) const;
		Color operator+(const ivec4 & yRef) const;

		Color operator-(const Color & yRef) const;
		Color operator-(const vec3 & yRef) const;
		Color operator-(const vec4 & yRef) const;
		Color operator-(const ivec3 & yRef) const;
		Color operator-(const ivec4 & yRef) const;

		bool operator==(const Color & yRef) const;
		bool operator==(const vec3 & yRef) const;
		bool operator==(const vec4 & yRef) const;
		bool operator==(const ivec3 & yRef) const;
		bool operator==(const ivec4 & yRef) const;

		bool operator!=(const Color & yRef) const;
		bool operator!=(const vec3 & yRef) const;
		bool operator!=(const vec4 & yRef) const;
		bool operator!=(const ivec3 & yRef) const;
		bool operator!=(const ivec4 & yRef) const;

		friend Color operator+(const vec3 & yRef, const Color & op2);
		friend Color operator+(const vec4 & yRef, const Color & op2);
		friend Color operator+(const ivec3 & yRef, const Color & op2);
		friend Color operator+(const ivec4 & yRef, const Color & op2);

		friend Color operator-(const vec3 & yRef, const Color & op2);
		friend Color operator-(const vec4 & yRef, const Color & op2);
		friend Color operator-(const ivec3 & yRef, const Color & op2);
		friend Color operator-(const ivec4 & yRef, const Color & op2);

		friend bool operator==(const vec3 & yRef, const Color & op2);
		friend bool operator==(const vec4 & yRef, const Color & op2);
		friend bool operator==(const ivec3 & yRef, const Color & op2);
		friend bool operator==(const ivec4 & yRef, const Color & op2);

		friend bool operator!=(const vec3 & yRef, const Color & op2);
		friend bool operator!=(const vec4 & yRef, const Color & op2);
		friend bool operator!=(const ivec3 & yRef, const Color & op2);
		friend bool operator!=(const ivec4 & yRef, const Color & op2);

		template <typename T>
		friend Color operator*(T x, const Color & op2);

		template <typename T>
		friend Color operator/(T x, const Color & op2);

		template <typename T, typename U>
		T FloatToInteger(U yRef) const;

		template <typename T, typename U>
		T IntegerToFloat(U yRef) const;
	};
}

#include "Color.inl"
