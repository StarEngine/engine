#pragma once

#include "../defines.h"
#include <algorithm>
#include <string>
#include <functional>
#include "../Logger.h"
#include "../Graphics/Color.h"

/// <summary>
/// This fill collects every function in the engine that has
/// a general purpose and doesn't belong to a specific class.
/// </summary>
namespace star
{
	/// <summary>
	/// Generate a hash based on a tstring.
	/// </summary>
	/// <param name="str">string to be hashed</param>
	/// <returns>generated hash</returns>
	const uint32 GenerateHash(const tstring & str);

	/// <summary>
	/// Opens a webpage in the user's default browser.
	/// </summary>
	/// <param name="page">the URL of the webpage to be opened</param>
	void LaunchWebpage(const tstring & page);
	
	/// <summary>
	/// Cast from type 'TReturnValue' to type 'TValue', where one of the 2 types is a string type.
	/// </summary>
	/// <param name="value">the value to be casted to type 'TReturnValue'</param>
	/// <returns>a copy of the casted value</returns>
	template < typename TReturnValue, typename TValue>
	TReturnValue string_cast(const TValue & value);
	
	/// <summary>
	/// Returns a copy of value. This overload should never be used.
	/// </summary>
	/// <param name="value">the value to be copied</param>
	/// <returns>a copy value</returns>
	template <>
	sstring_16 string_cast<sstring_16, sstring_16>
		(const sstring_16 & value);

	/// <summary>
	/// Returns a copy of value, casted into a 'sstring_16'.
	/// </summary>
	/// <param name="value">the value to be casted</param>
	/// <returns>a sstring_16 object, casted from value</returns>
	template <>
	sstring_16 string_cast<sstring_16, swstring>
		(const swstring & value);

	/// <summary>
	/// Returns a copy of value, casted into a 'sstring_16'.
	/// </summary>
	/// <param name="value">the value to be casted</param>
	/// <returns>a sstring_16 object, casted from value</returns>
	template <>
	sstring_16 string_cast<sstring_16, sstring>
		(const sstring & value);
	
	/// <summary>
	/// Returns a copy of value, casted into a 'swstring'.
	/// </summary>
	/// <param name="value">the value to be casted</param>
	/// <returns>a swstring object, casted from value</returns>
	template <>
	swstring string_cast<swstring, sstring_16>
		(const sstring_16 & value);
	
	/// <summary>
	/// Returns a copy of value, casted into a 'sstring'.
	/// </summary>
	/// <param name="value">the value to be casted</param>
	/// <returns>a sstring object, casted from value</returns>
	template <>
	sstring string_cast<sstring, sstring_16>
		(const sstring_16 & value);
	
	/// <summary>
	/// Returns a copy of value. This overload should never be used.
	/// </summary>
	/// <param name="value">the value to be copied</param>
	/// <returns>a copy value</returns>
	template <>
	swstring string_cast<swstring, swstring>
		(const swstring & value);

	/// <summary>
	/// Returns a copy of value. This overload should never be used.
	/// </summary>
	/// <param name="value">the value to be copied</param>
	/// <returns>a copy value</returns>
	template <>
	sstring string_cast<sstring, sstring>
		(const sstring & value);

	/// <summary>
	/// Returns a copy of value, casted into a 'sstring'.
	/// </summary>
	/// <param name="value">the value to be casted</param>
	/// <returns>a sstring object, casted from value</returns>
	template <>
	sstring string_cast<sstring, swstring>
		(const swstring & value);

	/// <summary>
	/// Returns a copy of value, casted into a 'swstring'.
	/// </summary>
	/// <param name="value">the value to be casted</param>
	/// <returns>a swstring object, casted from value</returns>
	template <>
	swstring string_cast<swstring, sstring>
		(const sstring & value);
	
	/// <summary>
	/// Returns a copy of c-string value, casted into a 'TReturnValue' object.
	/// </summary>
	/// <param name="value">the value to be casted</param>
	/// <returns>a 'TReturnValue' object, casted from value</returns>
	template < typename TReturnValue, typename TValue>
	TReturnValue string_cast(const TValue * value);

	/// <summary>
	/// Returns a copy of c-string value, casted into a 'sstring_16' object.
	/// </summary>
	/// <param name="value">the value to be casted</param>
	/// <returns>a 'sstring_16' object, casted from value</returns>
	template <>
	sstring_16 string_cast<sstring_16, schar_16>
		(const schar_16 * value);

	/// <summary>
	/// Returns a copy of c-string value, casted into a 'sstring_16' object.
	/// </summary>
	/// <param name="value">the value to be casted</param>
	/// <returns>a 'sstring_16' object, casted from value</returns>
	template <>
	sstring_16 string_cast<sstring_16, swchar>
		(const swchar * value);

	/// <summary>
	/// Returns a copy of c-string value, casted into a 'sstring_16' object.
	/// </summary>
	/// <param name="value">the value to be casted</param>
	/// <returns>a 'sstring_16' object, casted from value</returns>
	template <>
	sstring_16 string_cast<sstring_16, schar>
		(const schar * value);

	/// <summary>
	/// Returns an array of schar_16 characters, casted from a sstring_16 object.
	/// </summary>
	/// <param name="value">the value to be casted</param>
	/// <returns>an array of schar_16 characters casted from a sstring_16 object</returns>
	template <>
	schar_16 * string_cast<schar_16*, sstring_16>
		(const sstring_16 & value);
	
	/// <summary>
	/// Returns an array of swchar characters, casted from a sstring_16 object.
	/// </summary>
	/// <param name="value">the value to be casted</param>
	/// <returns>an array of swchar characters casted from a sstring_16 object</returns>
	template <>
	swchar * string_cast<swchar*, sstring_16>
		(const sstring_16 & value);
	
	/// <summary>
	/// Returns an array of schar characters, casted from a sstring_16 object.
	/// </summary>
	/// <param name="value">the value to be casted</param>
	/// <returns>an array of schar characters casted from a sstring_16 object</returns>
	template <>
	schar * string_cast<schar*, sstring_16>
		(const sstring_16 & value);

	/// <summary>
	/// Returns a copy of c-string value, casted into a 'sstring' object.
	/// </summary>
	/// <param name="value">the value to be casted</param>
	/// <returns>a 'sstring' object, casted from value</returns>
	template <>
	sstring string_cast<sstring, schar_16>
		(const schar_16 * value);

	/// <summary>
	/// Returns a copy of c-string value, casted into a 'swstring' object.
	/// </summary>
	/// <param name="value">the value to be casted</param>
	/// <returns>a 'swstring' object, casted from value</returns>
	template <>
	swstring string_cast<swstring, schar_16>
		(const schar_16 * value);
	
	/// <summary>
	/// Returns an array of schar_16 characters, casted from a sstring object.
	/// </summary>
	/// <param name="value">the value to be casted</param>
	/// <returns>an array of schar_16 characters casted from a sstring object</returns>
	template <>
	schar_16* string_cast<schar_16*, sstring>
		(const sstring & value);

	/// <summary>
	/// Returns an array of schar_16 characters, casted from a swstring object.
	/// </summary>
	/// <param name="value">the value to be casted</param>
	/// <returns>an array of schar_16 characters casted from a swstring object</returns>
	template <>
	schar_16* string_cast<schar_16*, swstring>
		(const swstring & value);
	
	/// <summary>
	/// Returns a copy of c-string value, casted into a 'swstring' object.
	/// </summary>
	/// <param name="value">the value to be casted</param>
	/// <returns>a 'swstring' object, casted from value</returns>
	template <>
	swstring string_cast<swstring, swchar>
		(const swchar * value);
	
	/// <summary>
	/// Returns a copy of c-string value, casted into a 'sstring' object.
	/// </summary>
	/// <param name="value">the value to be casted</param>
	/// <returns>a 'sstring' object, casted from value</returns>
	template <>
	sstring string_cast<sstring, schar>
		(const schar * value);
	
	/// <summary>
	/// Returns a copy of c-string value, casted into a 'sstring' object.
	/// </summary>
	/// <param name="value">the value to be casted</param>
	/// <returns>a 'sstring' object, casted from value</returns>
	template <>
	sstring string_cast<sstring, swchar>
		(const swchar * value);
	
	/// <summary>
	/// Returns a copy of c-string value, casted into a 'swstring' object.
	/// </summary>
	/// <param name="value">the value to be casted</param>
	/// <returns>a 'swstring' object, casted from value</returns>
	template <>
	swstring string_cast<swstring, schar>
		(const schar * value);
	
	/// <summary>
	/// Returns an array of schar characters, casted from a swstring object.
	/// </summary>
	/// <param name="value">the value to be casted</param>
	/// <returns>an array of schar characters casted from a swstring object</returns>
	template <>
	schar* string_cast<schar*, swstring>
		(const swstring & value);
	
	/// <summary>
	/// Returns an array of schar characters, casted from a sstring object.
	/// </summary>
	/// <param name="value">the value to be casted</param>
	/// <returns>an array of schar characters casted from a sstring object</returns>
	template <>
	schar* string_cast<schar*, sstring>
		(const sstring & value);
	
	/// <summary>
	/// Returns an array of swchar characters, casted from a swstring object.
	/// </summary>
	/// <param name="value">the value to be casted</param>
	/// <returns>an array of swchar characters casted from a swstring object</returns>
	template <>
	swchar* string_cast<swchar*, swstring>
		(const swstring & value);

	/// <summary>
	/// Returns an array of swchar characters, casted from a sstring object.
	/// </summary>
	/// <param name="value">the value to be casted</param>
	/// <returns>an array of swchar characters casted from a sstring object</returns>
	template <>
	swchar* string_cast<swchar*, sstring>
		(const sstring & value);
	
	/// <summary>
	/// Returns an array of swchar characters, casted from an array of schar characters.
	/// </summary>
	/// <param name="value">the value to be casted</param>
	/// <returns>an array of swchar characters casted from an array of schar characters</returns>
	template <>
	swchar* string_cast<swchar*, schar>
		(const schar * value);

	/// <summary>
	/// Returns a copy of an array of swchar characters. This function should never be used.
	/// </summary>
	/// <param name="value">the value to be casted</param>
	/// <returns>a copy of an array of swchar aharacters</returns>
	template <>
	swchar* string_cast<swchar*, swchar>
		(const swchar * value);
	
	/// <summary>
	/// Returns an array of schar characters, casted from an array of swchar characters.
	/// </summary>
	/// <param name="value">the value to be casted</param>
	/// <returns>an array of schar characters casted from an array of swchar characters</returns>
	template <>
	schar* string_cast<schar*, swchar>
		(const swchar * value);

	/// <summary>
	/// Returns a copy of an array of schar characters. This function should never be used.
	/// </summary>
	/// <param name="value">the value to be casted</param>
	/// <returns>a copy of an array of schar aharacters</returns>
	template <>
	schar* string_cast<schar*, schar>
		(const schar * value);
	
	/// <summary>
	/// Returns an array of schar_16 characters, casted from an array of schar characters.
	/// </summary>
	/// <param name="value">the value to be casted</param>
	/// <returns>an array of schar_16 characters casted from an array of schar characters</returns>
	template <>
	schar_16* string_cast<schar_16*, schar>
		(const schar * value);
	
	/// <summary>
	/// Returns an array of schar_16 characters, casted from an array of swchar characters.
	/// </summary>
	/// <param name="value">the value to be casted</param>
	/// <returns>an array of schar_16 characters casted from an array of swchar characters</returns>
	template <>
	schar_16* string_cast<schar_16*, swchar>
		(const swchar * value);

	/// <summary>
	/// Returns an array of schar characters, casted from an array of schar_16 characters.
	/// </summary>
	/// <param name="value">the value to be casted</param>
	/// <returns>an array of schar characters casted from an array of schar_16 characters</returns>
	template <>
	schar* string_cast<schar*, schar_16>
		(const schar_16 * value);

	/// <summary>
	/// Returns an array of swchar characters, casted from an array of schar_16 characters.
	/// </summary>
	/// <param name="value">the value to be casted</param>
	/// <returns>an array of swchar characters casted from an array of schar_16 characters</returns>
	template <>
	swchar* string_cast<swchar*, schar_16>
		(const schar_16 * value);
	
	/// <summary>
	/// Returns a tstring, generated from a floating vector2.
	/// </summary>
	/// <param name="value">the value to be casted</param>
	/// <returns>a tstring in the format 'x;y'</returns>
	template <>
	tstring string_cast<tstring, fvec2>
		(const fvec2 & value);
	
	/// <summary>
	/// Returns a tstring, generated from a pos.
	/// </summary>
	/// <param name="value">the value to be casted</param>
	/// <returns>a tstring in the format 'x;y;l'</returns>
	/// <seealso cref="pos"></seealso>
	template <>
	tstring string_cast<tstring, pos>
		(const pos & value);
	
	/// <summary>
	/// Returns a tstring, generated from a floating vector3.
	/// </summary>
	/// <param name="value">the value to be casted</param>
	/// <returns>a tstring in the format 'x;y;z'</returns>
	template <>
	tstring string_cast<tstring, fvec3>
		(const fvec3 & value);
	
	/// <summary>
	/// Returns a tstring, generated from a floating vector4.
	/// </summary>
	/// <param name="value">the value to be casted</param>
	/// <returns>a tstring in the format 'x;y;z;w'</returns>
	template <>
	tstring string_cast<tstring, fvec4>
		(const fvec4 & value);
	
	/// <summary>
	/// Returns a tstring, generated from a floating quaternion.
	/// </summary>
	/// <param name="value">the value to be casted</param>
	/// <returns>a tstring in the format 'x;y;z;w'</returns>
	template <>
	tstring string_cast<tstring, fquat>
		(const fquat & value);

	/// <summary>
	/// Returns a tstring, generated from a double presision floating vector2.
	/// </summary>
	/// <param name="value">the value to be casted</param>
	/// <returns>a tstring in the format 'x;y'</returns>
	template <>
	tstring string_cast<tstring, dvec2>
		(const dvec2 & value);
	
	/// <summary>
	/// Returns a tstring, generated from a double presision floating vector3.
	/// </summary>
	/// <param name="value">the value to be casted</param>
	/// <returns>a tstring in the format 'x;y;z'</returns>
	template <>
	tstring string_cast<tstring, dvec3>
		(const dvec3 & value);
	
	/// <summary>
	/// Returns a tstring, generated from a double presision floating vector4.
	/// </summary>
	/// <param name="value">the value to be casted</param>
	/// <returns>a tstring in the format 'x;y;z;w'</returns>
	template <>
	tstring string_cast<tstring, dvec4>
		(const dvec4 & value);
	
	/// <summary>
	/// Returns a tstring, generated from a double presision floating quaternion.
	/// </summary>
	/// <param name="value">the value to be casted</param>
	/// <returns>a tstring in the format 'x;y;z;w'</returns>
	template <>
	tstring string_cast<tstring, dquat>
		(const dquat & value);
	
	/// <summary>
	/// Returns a tstring, generated from an integer vector2.
	/// </summary>
	/// <param name="value">the value to be casted</param>
	/// <returns>a tstring in the format 'x;y'</returns>
	template <>
	tstring string_cast<tstring, ivec2>
		(const ivec2 & value);
	
	/// <summary>
	/// Returns a tstring, generated from an integer vector3.
	/// </summary>
	/// <param name="value">the value to be casted</param>
	/// <returns>a tstring in the format 'x;y;z'</returns>
	template <>
	tstring string_cast<tstring, ivec3>
		(const ivec3 & value);
	
	/// <summary>
	/// Returns a tstring, generated from an integer vector4.
	/// </summary>
	/// <param name="value">the value to be casted</param>
	/// <returns>a tstring in the format 'x;y;z;w'</returns>
	template <>
	tstring string_cast<tstring, ivec4>
		(const ivec4 & value);
	
	/// <summary>
	/// Returns a tstring, generated from an integer unsigned integer vector2.
	/// </summary>
	/// <param name="value">the value to be casted</param>
	/// <returns>a tstring in the format 'x;y'</returns>
	template <>
	tstring string_cast<tstring, uvec2>
		(const uvec2 & value);
	
	/// <summary>
	/// Returns a tstring, generated from an integer unsigned integer vector3.
	/// </summary>
	/// <param name="value">the value to be casted</param>
	/// <returns>a tstring in the format 'x;y;z'</returns>
	template <>
	tstring string_cast<tstring, uvec3>
		(const uvec3 & value);
	
	/// <summary>
	/// Returns a tstring, generated from an integer unsigned integer vector4.
	/// </summary>
	/// <param name="value">the value to be casted</param>
	/// <returns>a tstring in the format 'x;y;z;w'</returns>
	template <>
	tstring string_cast<tstring, uvec4>
		(const uvec4 & value);
	
	/// <summary>
	/// Returns a tstring, generated from a color value.
	/// </summary>
	/// <param name="value">the color value to be casted</param>
	/// <returns>a tstring in the format 'r;g;b;a'</returns>
	/// <seealso cref="Color"></seealso>
	template <>
	tstring string_cast<tstring, Color>
		(const Color & value);
	
	/// <summary>
	/// Returns a boolean value, generated from a tstring.
	/// </summary>
	/// <param name="value">the value to be casted</param>
	/// <returns>returns a boolean value, converted from the tstring</returns>
	template <>
	bool string_cast<bool, tstring>
		(const tstring & value);
	
	/// <summary>
	/// Returns an integer value, generated from a tstring.
	/// </summary>
	/// <param name="value">the value to be casted</param>
	/// <returns>returns an integer value, converted from the tstring</returns>
	template <>
	int32 string_cast<int32, tstring>
		(const tstring & value);
	
	/// <summary>
	/// Returns an unsigned integer value, generated from a tstring.
	/// </summary>
	/// <param name="value">the value to be casted</param>
	/// <returns>returns an unsigned integer value, converted from the tstring</returns>
	template <>
	uint32 string_cast<uint32, tstring>
		(const tstring & value);

	/// <summary>
	/// Returns an integer value, generated from a tstring.
	/// </summary>
	/// <param name="value">the value to be casted</param>
	/// <returns>returns an integer value, converted from the tstring</returns>
	template <>
	long string_cast<long, tstring>
		(const tstring & value);
	
	/// <summary>
	/// Returns a floating value, generated from a tstring.
	/// </summary>
	/// <param name="value">the value to be casted</param>
	/// <returns>returns a floating value, converted from the tstring</returns>
	template <>
	float32 string_cast<float32, tstring>
		(const tstring & value);
	
	/// <summary>
	/// Returns a double presision floating value, generated from a tstring.
	/// </summary>
	/// <param name="value">the value to be casted</param>
	/// <returns>returns a double presision floating value, converted from the tstring</returns>
	template <>
	float64 string_cast<float64, tstring>
		(const tstring & value);
	
	/// <summary>
	/// Returns a floating vector2 object, generated from a tstring.
	/// </summary>
	/// <param name="value">a string with the structure 'x;y'</param>
	/// <returns>returns a floating vector2 object, converted from the tstring</returns>
	template <>
	fvec2 string_cast<fvec2, tstring>
		(const tstring & value);

	/// <summary>
	/// Returns a pos object, generated from a tstring.
	/// </summary>
	/// <param name="value">a string with the structure 'x;y;l'</param>
	/// <returns>returns a pos object, converted from the tstring</returns>
	/// <seealso cref="pos"></seealso>
	template <>
	pos string_cast<pos, tstring>
		(const tstring & value);

	/// <summary>
	/// Returns a floating vector3 object, generated from a tstring.
	/// </summary>
	/// <param name="value">a string with the structure 'x;y;z'</param>
	/// <returns>returns a floating vector3 object, converted from the tstring</returns>
	template <>
	fvec3 string_cast<fvec3, tstring>
		(const tstring & value);
	
	/// <summary>
	/// Returns a floating vector4 object, generated from a tstring.
	/// </summary>
	/// <param name="value">a string with the structure 'x;y;z;w'</param>
	/// <returns>returns a floating vector4 object, converted from the tstring</returns>
	template <>
	fvec4 string_cast<fvec4, tstring>
		(const tstring & value);
	
	/// <summary>
	/// Returns a floating quaternion object, generated from a tstring.
	/// </summary>
	/// <param name="value">a string with the structure 'x;y;z;w'</param>
	/// <returns>returns a floating quaternion object, converted from the tstring</returns>
	template <>
	fquat string_cast<fquat, tstring>
		(const tstring & value);
	
	/// <summary>
	/// Returns a double presision floating vector2 object, generated from a tstring.
	/// </summary>
	/// <param name="value">a string with the structure 'x;y'</param>
	/// <returns>returns a double presision floating vector2 object, converted from the tstring</returns>
	template <>
	dvec2 string_cast<dvec2, tstring>
		(const tstring & value);
	
	/// <summary>
	/// Returns a double presision floating vector3 object, generated from a tstring.
	/// </summary>
	/// <param name="value">a string with the structure 'x;y;z'</param>
	/// <returns>returns a double presision floating vector3 object, converted from the tstring</returns>
	template <>
	dvec3 string_cast<dvec3, tstring>
		(const tstring & value);
	
	/// <summary>
	/// Returns a double presision floating vector4 object, generated from a tstring.
	/// </summary>
	/// <param name="value">a string with the structure 'x;y;z;w'</param>
	/// <returns>returns a double presision floating vector4 object, converted from the tstring</returns>
	template <>
	dvec4 string_cast<dvec4, tstring>
		(const tstring & value);

	/// <summary>
	/// Returns a double presision floating quaternion object, generated from a tstring.
	/// </summary>
	/// <param name="value">a string with the structure 'x;y;z;w'</param>
	/// <returns>returns a double presision floating quaternion object, converted from the tstring</returns>
	template <>
	dquat string_cast<dquat, tstring>
		(const tstring & value);

	/// <summary>
	/// Returns an integer vector2 object, generated from a tstring.
	/// </summary>
	/// <param name="value">a string with the structure 'x;y'</param>
	/// <returns>returns an integer vector2 object, converted from the tstring</returns>
	template <>
	ivec2 string_cast<ivec2, tstring>
		(const tstring & value);
	
	/// <summary>
	/// Returns an integer vector3 object, generated from a tstring.
	/// </summary>
	/// <param name="value">a string with the structure 'x;y;z'</param>
	/// <returns>returns an integer vector3 object, converted from the tstring</returns>
	template <>
	ivec3 string_cast<ivec3, tstring>
		(const tstring & value);
	
	/// <summary>
	/// Returns an integer vector4 object, generated from a tstring.
	/// </summary>
	/// <param name="value">a string with the structure 'x;y;z;w'</param>
	/// <returns>returns an integer vector4 object, converted from the tstring</returns>
	template <>
	ivec4 string_cast<ivec4, tstring>
		(const tstring & value);
	
	/// <summary>
	/// Returns an unsigned integer vector2 object, generated from a tstring.
	/// </summary>
	/// <param name="value">a string with the structure 'x;y'</param>
	/// <returns>returns an unsigned integer vector2 object, converted from the tstring</returns>
	template <>
	uvec2 string_cast<uvec2, tstring>
		(const tstring & value);
	
	/// <summary>
	/// Returns an unsigned integer vector3 object, generated from a tstring.
	/// </summary>
	/// <param name="value">a string with the structure 'x;y;z'</param>
	/// <returns>returns an unsigned integer vector3 object, converted from the tstring</returns>
	template <>
	uvec3 string_cast<uvec3, tstring>
		(const tstring & value);
	
	/// <summary>
	/// Returns an unsigned integer vector4 object, generated from a tstring.
	/// </summary>
	/// <param name="value">a string with the structure 'x;y;z;w'</param>
	/// <returns>returns an unsigned integer vector4 object, converted from the tstring</returns>
	template <>
	uvec4 string_cast<uvec4, tstring>
		(const tstring & value);
	
	/// <summary>
	/// Returns a color object, generated from a tstring.
	/// </summary>
	/// <param name="value">a string with the structure 'r;g;b;a'</param>
	/// <returns>returns a color object, converted from the tstring</returns>
	/// <seealso cref="Color"></seealso>
	template <>
	Color string_cast<Color, tstring>
		(const tstring & value);
	
	/// <summary>
	/// Read a text file.
	/// </summary>
	/// <param name="file">filepath of the text file, with the root being defined by the directory parameter</param>
	/// <param name="text">tstring object where the content of the text file will be saved into</param>
	/// <param name="directory">enumeration value to define the directory of the text file</param>
	/// <seealso cref="DirectoryMode"></seealso>
	/// <seealso cref="DEFAULT_DIRECTORY_MODE"></seealso>
	void ReadTextFile(const tstring & file, tstring & text,
			DirectoryMode directory = DEFAULT_DIRECTORY_MODE);
	
	/// <summary>
	/// Read a text file.
	/// </summary>
	/// <param name="file">filepath of the text file, with the root being defined by the directory parameter</param>
	/// <param name="directory">enumeration value to define the directory of the text file</param>
	/// <returns>tstring object where the content of the text file will be saved into</returns>
	/// <seealso cref="DirectoryMode"></seealso>
	/// <seealso cref="DEFAULT_DIRECTORY_MODE"></seealso>
	tstring ReadTextFile(const tstring & file,
			DirectoryMode directory = DEFAULT_DIRECTORY_MODE);

	/// <summary>
	/// Read a text file with a no-crash guarantee.
	/// </summary>
	/// <param name="file">filepath of the text file, with the root being defined by the directory parameter</param>
	/// <param name="text">tstring object where the content of the text file will be saved into</param>
	/// <param name="directory">enumeration value to define the directory of the text file</param>
	/// <param name="logWarning">true to log a warning in case the file can't be found</param>
	/// <returns>true if file exists</returns>
	/// <seealso cref="DirectoryMode"></seealso>
	/// <seealso cref="DEFAULT_DIRECTORY_MODE"></seealso>
	bool ReadTextFileSafe(const tstring & file, tstring & text,
			DirectoryMode directory = DEFAULT_DIRECTORY_MODE,
			bool logWarning = true);
	
	/// <summary>
	/// Write a tstring object to a text file.
	/// </summary>
	/// <param name="file">filepath of the text file, with the root being defined by the directory parameter</param>
	/// <param name="text">tstring that will be written to the text file</param>
	/// <param name="directory">enumeration value to define the directory of the text file</param>
	/// <seealso cref="DirectoryMode"></seealso>
	/// <seealso cref="DEFAULT_DIRECTORY_MODE"></seealso>
	void WriteTextFile(const tstring & file, const tstring & text,
			DirectoryMode directory = DEFAULT_DIRECTORY_MODE);
	
	/// <summary>
	/// Append a tstring object to a text file.
	/// </summary>
	/// <param name="file">filepath of the text file, with the root being defined by the directory parameter</param>
	/// <param name="text">tstring that will be written at the end of the text file</param>
	/// <param name="directory">enumeration value to define the directory of the text file</param>
	/// <seealso cref="DirectoryMode"></seealso>
	/// <seealso cref="DEFAULT_DIRECTORY_MODE"></seealso>
	void AppendTextFile(const tstring & file, const tstring & text,
			DirectoryMode directory = DEFAULT_DIRECTORY_MODE);
	
	/// <summary>
	/// Read from a binary file.
	/// </summary>
	/// <param name="file">filepath of the binary file, with the root being defined by the directory parameter</param>
	/// <param name="size">output parameter that defines the size of the single byte character array</param>
	/// <param name="directory">enumeration value to define the directory of the binary file</param>
	/// <returns>a single byte character array read from the binary file</returns>
	/// <seealso cref="DirectoryMode"></seealso>
	/// <seealso cref="DEFAULT_DIRECTORY_MODE"></seealso>
	schar * ReadBinaryFile(const tstring & file, uint32 & size,
			DirectoryMode directory = DEFAULT_DIRECTORY_MODE);

	/// <summary>
	/// Read from a binary file with a no-crash guarantee.
	/// </summary>
	/// <param name="file">filepath of the binary file, with the root being defined by the directory parameter</param>
	/// <param name="buffer">a single byte character array read from the binary file</param>
	/// <param name="size">output parameter that defines the size of the single byte character array</param>
	/// <param name="directory">enumeration value to define the directory of the binary file</param>
	/// <param name="logWarning">true to log a warning in case it can't find the file</param>
	/// <returns>true if file exists</returns>
	/// <seealso cref="DirectoryMode"></seealso>
	/// <seealso cref="DEFAULT_DIRECTORY_MODE"></seealso>
	bool ReadBinaryFileSafe(const tstring & file, schar *& buffer, uint32 & size,
			DirectoryMode directory = DEFAULT_DIRECTORY_MODE,
			bool logWarning = true);
	
	/// <summary>
	/// Write to a binary file.
	/// </summary>
	/// <param name="file">filepath of the binary file, with the root being defined by the directory parameter</param>
	/// <param name="buffer">a single byte character array to be written to the binary file</param>
	/// <param name="size">size of the single byte character array</param>
	/// <param name="directory">enumeration value to define the directory of the binary file</param>
	/// <seealso cref="DirectoryMode"></seealso>
	/// <seealso cref="DEFAULT_DIRECTORY_MODE"></seealso>
	void WriteBinaryFile(const tstring & file, schar * buffer, uint32 size,
			DirectoryMode directory = DEFAULT_DIRECTORY_MODE);
	
	/// <summary>
	/// Write at the end of a binary file.
	/// </summary>
	/// <param name="file">filepath of the binary file, with the root being defined by the directory parameter</param>
	/// <param name="buffer">a single byte character array to be written at the end of the binary file</param>
	/// <param name="size">size of the single byte character array</param>
	/// <param name="directory">enumeration value to define the directory of the binary file</param>
	/// <seealso cref="DirectoryMode"></seealso>
	/// <seealso cref="DEFAULT_DIRECTORY_MODE"></seealso>
	void AppendBinaryFile(const tstring & file, schar * buffer, uint32 size,
			DirectoryMode directory = DEFAULT_DIRECTORY_MODE);
	
	/// <summary>
	/// Read a encrypted binary file and decrypt it.
	/// </summary>
	/// <param name="file">filepath of the binary file, with the root being defined by the directory parameter</param>
	/// <param name="size">size of the single byte character array</param>
	/// <param name="decrypter">function that contains the logic to decrypt the encrypted content</param>
	/// <param name="directory">enumeration value to define the directory of the text file</param>
	/// <returns>a single byte character array read and decrypted from the binary file</returns>
	/// <seealso cref="DirectoryMode"></seealso>
	/// <seealso cref="DEFAULT_DIRECTORY_MODE"></seealso>
	schar * DecryptBinaryFile(const tstring & file, uint32 & size,
		const std::function<schar*(const schar*, uint32&)> & decrypter, 
		DirectoryMode directory = DEFAULT_DIRECTORY_MODE);

	/// <summary>
	/// Read a encrypted binary file and decrypt it with a no-crash guarantee.
	/// </summary>
	/// <param name="file">filepath of the binary file, with the root being defined by the directory parameter</param>
	/// <param name="buffer">a single byte character array read and decrypted from the binary file</param>
	/// <param name="size">size of the single byte character array</param>
	/// <param name="decrypter">function that contains the logic to decrypt the encrypted content</param>
	/// <param name="directory">enumeration value to define the directory of the text file</param>
	/// <param name="logWarning">true to log a warning if the file can't be found</param>
	/// <returns>true if file exists</returns>
	/// <seealso cref="DirectoryMode"></seealso>
	/// <seealso cref="DEFAULT_DIRECTORY_MODE"></seealso>
	bool DecryptBinaryFileSafe(const tstring & file, schar *& buffer, uint32 & size,
		const std::function<schar*(const schar*, uint32&)> & decrypter, 
		DirectoryMode directory = DEFAULT_DIRECTORY_MODE,
		bool logWarning = true);
	
	/// <summary>
	/// Encrypt a binary data and write it to a file
	/// </summary>
	/// <param name="file">filepath of the binary file, with the root being defined by the directory parameter</param>
	/// <param name="buffer">an array of single byte characters that will be encrypted and written to a binary file</param>
	/// <param name="size">size of the single byte character array</param>
	/// <param name="encrypter">function that contains the logic to encrypt the raw content</param>
	/// <param name="directory">enumeration value to define the directory of the text file</param>
	/// <seealso cref="DirectoryMode"></seealso>
	/// <seealso cref="DEFAULT_DIRECTORY_MODE"></seealso>
	void EncryptBinaryFile(const tstring & file, schar * buffer, uint32 size,
		const std::function<schar*(const schar*, uint32&)> & encrypter, 
		DirectoryMode directory = DEFAULT_DIRECTORY_MODE);

	/// <summary>
	/// Cast an object from one class to another.
	/// There are no safeties build-in this function so make sure the casting is possible.
	/// </summary>
	/// <param name="v">value of type 'To' to be casted to type 'From'</param>
	/// <returns>a casted value of type 'To'</returns>
	template<class To, class From>
	To cast(From v);
	
	/// <summary>
	/// Write a data object (structure) to a binary file.
	/// </summary>
	/// <param name="file">filepath of the binary file, with the root being defined by the directory parameter</param>
	/// <param name="buffer">pointer to the data object to be serialized</param>
	/// <param name="directory">enumeration value to define the directory of the text file</param>
	/// <seealso cref="DirectoryMode"></seealso>
	/// <seealso cref="DEFAULT_DIRECTORY_MODE"></seealso>
	template <typename T>
	void WriteData(const tstring & file, T * buffer,
			DirectoryMode directory = DEFAULT_DIRECTORY_MODE);
	
	/// <summary>
	/// Read a data object (structure) from a binary file.
	/// </summary>
	/// <param name="file">filepath of the binary file, with the root being defined by the directory parameter</param>
	/// <param name="buffer">pointer to the data object to be deserialized</param>
	/// <param name="directory">enumeration value to define the directory of the text file</param>
	/// <seealso cref="DirectoryMode"></seealso>
	/// <seealso cref="DEFAULT_DIRECTORY_MODE"></seealso>
	template <typename T>
	void ReadData(const tstring & file, T * buffer,
			DirectoryMode directory = DEFAULT_DIRECTORY_MODE);
	
	/// <summary>
	/// Write an array of data objects (structure) to a binary file.
	/// </summary>
	/// <param name="file">filepath of the binary file, with the root being defined by the directory parameter</param>
	/// <param name="buffer">pointer to the first data object to be serialized</param>
	/// <param name="size">amount of data objects to be serialized</param>
	/// <param name="directory">enumeration value to define the directory of the text file</param>
	/// <seealso cref="DirectoryMode"></seealso>
	/// <seealso cref="DEFAULT_DIRECTORY_MODE"></seealso>
	template <typename T>
	void WriteDataArray(const tstring & file, T * buffer, uint32 size,
			DirectoryMode directory = DEFAULT_DIRECTORY_MODE);
	
	/// <summary>
	/// Read an array of data objects (structure) from a binary file.
	/// </summary>
	/// <param name="file">filepath of the binary file, with the root being defined by the directory parameter</param>
	/// <param name="size">amount of data objects to be deserialized</param>
	/// <param name="directory">enumeration value to define the directory of the text file</param>
	/// <seealso cref="DirectoryMode"></seealso>
	/// <seealso cref="DEFAULT_DIRECTORY_MODE"></seealso>
	template <typename T>
	T * ReadDataArray(const tstring & file, uint32 size,
			DirectoryMode directory = DEFAULT_DIRECTORY_MODE);
	
	/// <summary>
	/// Write and encrypt a data object (structure) to a binary file.
	/// </summary>
	/// <param name="file">filepath of the binary file, with the root being defined by the directory parameter</param>
	/// <param name="buffer">data object to be ecrypted and serialized</param>
	/// <param name="encrypter">function that contains the encryption logic for the serialized data</param>
	/// <param name="directory">enumeration value to define the directory of the text file</param>
	/// <seealso cref="DirectoryMode"></seealso>
	/// <seealso cref="DEFAULT_DIRECTORY_MODE"></seealso>
	template <typename T>
	void EncryptData(const tstring & file, T * buffer,
		const std::function<schar*(const schar*, uint32&)> & encrypter, 
		DirectoryMode directory = DEFAULT_DIRECTORY_MODE);
	
	/// <summary>
	/// Read and decrypt a data object (structure) to a binary file.
	/// </summary>
	/// <param name="file">filepath of the binary file, with the root being defined by the directory parameter</param>
	/// <param name="buffer">data object to be ecrypted and serialized</param>
	/// <param name="decrypter">function that contains the decryption logic for the deserialized data</param>
	/// <param name="directory">enumeration value to define the directory of the text file</param>
	/// <seealso cref="DirectoryMode"></seealso>
	/// <seealso cref="DEFAULT_DIRECTORY_MODE"></seealso>
	template <typename T>
	void DecryptData(const tstring & file, T * buffer,
		const std::function<schar*(const schar*, uint32&)> & decrypter, 
		DirectoryMode directory = DEFAULT_DIRECTORY_MODE);

	/// <summary>
	/// Write and encrypt an array of data objects (structure) to a binary file.
	/// </summary>
	/// <param name="file">filepath of the binary file, with the root being defined by the directory parameter</param>
	/// <param name="buffer">the first data object to be ecrypted and serialized</param>
	/// <param name="size">size of the binary file.</param>
	/// <param name="encrypter">function that contains the encryption logic for the serialized data</param>
	/// <param name="directory">enumeration value to define the directory of the text file</param>
	/// <seealso cref="DirectoryMode"></seealso>
	/// <seealso cref="DEFAULT_DIRECTORY_MODE"></seealso>
	template <typename T>
	void EncryptDataArray(const tstring & file, T * buffer, uint32 size,
		const std::function<schar*(const schar*, uint32&)> & encrypter,
		DirectoryMode directory = DEFAULT_DIRECTORY_MODE);
	
	/// <summary>
	/// Read and decrypt an array of data objects (structure) to a binary file.
	/// </summary>
	/// <param name="file">filepath of the binary file, with the root being defined by the directory parameter</param>
	/// <param name="size">size of the binary file.</param>
	/// <param name="decrypter">function that contains the decryption logic for the deserialized data</param>
	/// <param name="directory">enumeration value to define the directory of the text file</param>
	/// <seealso cref="DirectoryMode"></seealso>
	/// <seealso cref="DEFAULT_DIRECTORY_MODE"></seealso>
	template <typename T>
	T * DecryptDataArray(const tstring & file, uint32 size,
		const std::function<schar*(const schar*, uint32&)> & decrypter,
		DirectoryMode directory = DEFAULT_DIRECTORY_MODE);
}

#include "Helpers.inl"
