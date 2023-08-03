#pragma once

namespace mystl {
struct __true_type {};
struct __false_type {};

template <class type>
struct __type_traits {
	typedef __false_type has_trivial_default_constructor;
	typedef __false_type has_trivial_copy_constructor;
	typedef __false_type has_trivial_assignment_operator;
	typedef __false_type has_trivial_destructor;
	typedef __false_type is_POD_type;
};
} // namespace mystl
