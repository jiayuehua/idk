// =============================================================================
//
// ztd.idk
// Copyright © 2022-2023 JeanHeyd "ThePhD" Meneide and Shepherd's Oasis, LLC
// Contact: opensource@soasis.org
//
// Commercial License Usage
// Licensees holding valid commercial ztd.idk licenses may use this file in
// accordance with the commercial license agreement provided with the
// Software or, alternatively, in accordance with the terms contained in
// a written agreement between you and Shepherd's Oasis, LLC.
// For licensing terms and conditions see your agreement. For
// further information contact opensource@soasis.org.
//
// Apache License Version 2 Usage
// Alternatively, this file may be used under the terms of Apache License
// Version 2.0 (the "License") for non-commercial use; you may not use this
// file except in compliance with the License. You may obtain a copy of the
// License at
//
// https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// ============================================================================ //

#pragma once

#ifndef ZTD_IDK_SIZE_H
#define ZTD_IDK_SIZE_H

#include <ztd/idk/charN_t.h>

#if ZTD_IS_ON(ZTD_CXX)
#include <climits>
#include <cstddef>
#include <ztd/idk/type_traits.hpp>
#else
#include <limits.h>
#include <stddef.h>
#endif

#define ztdc_c_array_size(...) (sizeof((__VA_ARGS__)) / sizeof(*(__VA_ARGS__)))
#define ztdc_c_string_array_size(...) (ztdc_c_array_size(__VA_ARGS__) - 1)

#define ztdc_c_array_byte_size(...) (ztdc_c_array_size(__VA_ARGS__) * sizeof(*(__VA_ARGS__)))
#define ztdc_c_string_array_byte_size(...) (ztdc_c_string_array_size(__VA_ARGS__) * sizeof(*(__VA_ARGS__)))

#define ztdc_c_array_bit_size(...) (ztdc_c_array_byte_size(__VA_ARGS__) * CHAR_BIT)
#define ztdc_c_string_array_bit_size(...) (ztdc_c_string_array_byte_size(__VA_ARGS__) * CHAR_BIT)

inline ZTD_CONSTEXPR_IF_CXX_I_ size_t ztdc_c_string_ptr_size_c(const char* __ptr) {
	size_t __ptr_size = 0;
	if (__ptr) {
		for (; *__ptr; ++__ptr) {
			__ptr_size += 1;
		}
	}
	return __ptr_size;
}

inline ZTD_CONSTEXPR_IF_CXX_I_ size_t ztdc_c_string_ptr_size_uc(const unsigned char* __ptr) ZTD_NOEXCEPT_IF_CXX_I_ {
	size_t __ptr_size = 0;
	if (__ptr) {
		for (; *__ptr; ++__ptr) {
			__ptr_size += 1;
		}
	}
	return __ptr_size;
}

inline ZTD_CONSTEXPR_IF_CXX_I_ size_t ztdc_c_string_ptr_size_w(const ztd_wchar_t* __ptr) ZTD_NOEXCEPT_IF_CXX_I_ {
	size_t __ptr_size = 0;
	if (__ptr) {
		for (; *__ptr; ++__ptr) {
			__ptr_size += 1;
		}
	}
	return __ptr_size;
}

inline ZTD_CONSTEXPR_IF_CXX_I_ size_t ztdc_c_string_ptr_size_c8(const ztd_char8_t* __ptr) ZTD_NOEXCEPT_IF_CXX_I_ {
	size_t __ptr_size = 0;
	if (__ptr) {
		for (; *__ptr; ++__ptr) {
			__ptr_size += 1;
		}
	}
	return __ptr_size;
}

inline ZTD_CONSTEXPR_IF_CXX_I_ size_t ztdc_c_string_ptr_size_c16(const ztd_char16_t* __ptr) ZTD_NOEXCEPT_IF_CXX_I_ {
	size_t __ptr_size = 0;
	if (__ptr) {
		for (; *__ptr; ++__ptr) {
			__ptr_size += 1;
		}
	}
	return __ptr_size;
}

inline ZTD_CONSTEXPR_IF_CXX_I_ size_t ztdc_c_string_ptr_size_c32(const ztd_char32_t* __ptr) ZTD_NOEXCEPT_IF_CXX_I_ {
	size_t __ptr_size = 0;
	if (__ptr) {
		for (; *__ptr; ++__ptr) {
			__ptr_size += 1;
		}
	}
	return __ptr_size;
}

#if ZTD_IS_ON(ZTD_C)
// NOTE: cascading _Generic implementation prevents issues with multiple types having the same underlying type, because
// unlike C++, all of these types could potentially be aliasing the same primitives.
#define ztdc_c_detail_string_ptr_size_0(_PTR) _Generic(char : ztdc_c_string_ptr_size_c)
#define ztdc_c_detail_string_ptr_size_1(_PTR) \
	_Generic(unsigned char : ztdc_c_string_ptr_size_uc, default : ztdc_c_detail_string_ptr_size_0(_PTR))
#define ztdc_c_detail_string_ptr_size_2(_PTR) \
	_Generic(wchar_t : ztdc_c_string_ptr_size_wc, default : ztdc_c_detail_string_ptr_size_1(_PTR))
#define ztdc_c_detail_string_ptr_size_3(_PTR) \
	_Generic(ztd_char8_t : ztdc_c_string_ptr_size_c8, default : ztdc_c_detail_string_ptr_size_2(_PTR))
#define ztdc_c_detail_string_ptr_size_4(_PTR) \
	_Generic(ztd_char16_t : ztdc_c_string_ptr_size_c16, default : ztdc_c_detail_string_ptr_size_3(_PTR))
#define ztdc_c_detail_string_ptr_size_5(_PTR) \
	_Generic(ztd_char32_t : ztdc_c_string_ptr_size_c32, default : ztdc_c_detail_string_ptr_size_4(_PTR))

#define ztdc_c_string_ptr_size(_PTR) ztdc_c_detail_string_ptr_size_5(_PTR)(_PTR)

#else

template <typename _Ptr>
constexpr ::std::size_t ztdc_c_string_ptr_size(const _Ptr& __ptr) noexcept {
	using _Ty = ::ztd::remove_cvref_t<::std::remove_pointer_t<::ztd::remove_cvref_t<_Ptr>>>;
	if constexpr (::std::is_same_v<::ztd::remove_cvref_t<_Ty>, char>) {
		return ztdc_c_string_ptr_size_c(__ptr);
	}
	else if constexpr (::std::is_same_v<::ztd::remove_cvref_t<_Ty>, unsigned char>) {
		return ztdc_c_string_ptr_size_uc(__ptr);
	}
	else if constexpr (::std::is_same_v<::ztd::remove_cvref_t<_Ty>, wchar_t>) {
		return ztdc_c_string_ptr_size_w(__ptr);
	}
#if ZTD_IS_ON(ZTD_NATIVE_CHAR8_T)
	else if constexpr (::std::is_same_v<::ztd::remove_cvref_t<_Ty>, char8_t>) {
		return ztdc_c_string_ptr_size_c8(__ptr);
	}
#endif
	else if constexpr (::std::is_same_v<::ztd::remove_cvref_t<_Ty>, char16_t>) {
		return ztdc_c_string_ptr_size_c16(__ptr);
	}
	else if constexpr (::std::is_same_v<::ztd::remove_cvref_t<_Ty>, char32_t>) {
		return ztdc_c_string_ptr_size_c32(__ptr);
	}
	else if constexpr (::std::is_same_v<::ztd::remove_cvref_t<_Ty>, ztd_char8_t>) {
		return ztdc_c_string_ptr_size_c8(__ptr);
	}
	else {
		static_assert(::ztd::always_false_v<_Ptr>, "unknown type to ztdc_c_string_ptr_size");
	}
}

#endif

#endif
