#pragma once

#include <complex>
#include <typeinfo>

#include <ismrmrd/ismrmrd.h>

namespace sirf {

	class aNumRef {
	public:
		virtual complex_double_t complex_double() const = 0;
		virtual complex_float_t complex_float() const = 0;
		virtual operator float() const = 0;
		virtual void assign(const aNumRef& ref) = 0;
		aNumRef& operator=(const aNumRef& ref)
		{
			assign(ref);
			return *this;
		}
		virtual void set_ptr(void* ptr) = 0;
		virtual void copy(const aNumRef& ref) = 0;
	};

	class FloatRef : public aNumRef {
	public:
		FloatRef(float* ptr = 0, int dummy = 0) : ptr_(ptr)
		{}
		virtual complex_double_t complex_double() const
		{
			return complex_double_t(*ptr_);
		}
		virtual complex_float_t complex_float() const
		{
			return complex_float_t(*ptr_);
		}
		virtual operator float() const
		{
			return *ptr_;
		}
		template<typename T>
		FloatRef& operator=(T v)
		{
			*ptr_ = v;
			return *this;
		}
		virtual void assign(const aNumRef& a_ref)
		{
			const FloatRef& ref = (const FloatRef&)a_ref;
			*ptr_ = float(ref);
		}
		aNumRef& operator=(const aNumRef& ref)
		{
			assign(ref);
			return *this;
		}
		void set_ptr(void* ptr)
		{
			ptr_ = (float*)ptr;
		}
		void copy(const aNumRef& a_ref)
		{
			const FloatRef& ref = (const FloatRef&)a_ref;
			ptr_ = ref.ptr_;
		}
	private:
		float* ptr_;
	};

	template <typename Type>
	ISMRMRD::ISMRMRD_DataTypes TypeID(Type t)
	{
		if (typeid(Type) == typeid(complex_double_t))
			return ISMRMRD::ISMRMRD_CXDOUBLE;
		else if (typeid(Type) == typeid(complex_float_t))
			return ISMRMRD::ISMRMRD_CXFLOAT;
		else if (typeid(Type) == typeid(double))
			return ISMRMRD::ISMRMRD_DOUBLE;
		else if (typeid(Type) == typeid(float))
			return ISMRMRD::ISMRMRD_FLOAT;
		else if (typeid(Type) == typeid(int))
			return ISMRMRD::ISMRMRD_INT;
		else if (typeid(Type) == typeid(unsigned int))
			return ISMRMRD::ISMRMRD_UINT;
		else if (typeid(Type) == typeid(short))
			return ISMRMRD::ISMRMRD_SHORT;
		else if (typeid(Type) == typeid(unsigned short))
			return ISMRMRD::ISMRMRD_USHORT;
		else
			throw std::invalid_argument
			(std::string("unsupported numeric type ") + typeid(Type).name());
	}

	class NumRef : public aNumRef {
	public:
		NumRef(void* ptr, int type) :
			ptr_(ptr), abs_(true), type_(type)
		{}
		NumRef(const NumRef& ref) :
			ptr_(ref.ptr_), abs_(ref.abs_), type_(ref.type_)
		{}
		void set_complex_to_real_mode(char m)
		{
			abs_ = (m == 'a');
		}
		char type() const
		{
			return type_;
		}
		virtual void set_ptr(void* ptr)
		{
			//std::cout << (size_t)ptr << '\n';
			ptr_ = ptr;
		}
		virtual void copy(const aNumRef& a_ref)
		{
			const NumRef& ref = (const NumRef&)a_ref;
			ptr_ = ref.ptr_;
			abs_ = ref.abs_;
			type_ = ref.type_;
		}
		complex_double_t complex_double() const
		{
			//std::cout << "casting to complex_float_t...\n";
			complex_double_t z;
			switch (type_) {
			case ISMRMRD::ISMRMRD_CXDOUBLE:
				z = *(complex_double_t*)ptr_;
				break;
			case ISMRMRD::ISMRMRD_CXFLOAT:
				z = *(complex_float_t*)ptr_;
				break;
			case ISMRMRD::ISMRMRD_DOUBLE:
				z = float(*(double*)ptr_);
				break;
			case ISMRMRD::ISMRMRD_FLOAT:
				z = *(float*)ptr_;
				break;
			case ISMRMRD::ISMRMRD_INT:
				z = complex_float_t(float(*(int*)ptr_));
				break;
			case ISMRMRD::ISMRMRD_UINT:
				z = complex_float_t(float(*(unsigned int*)ptr_));
				break;
			case ISMRMRD::ISMRMRD_SHORT:
				z = complex_float_t(float(*(short*)ptr_));
				break;
			case ISMRMRD::ISMRMRD_USHORT:
				z = complex_float_t(float(*(unsigned short*)ptr_));
			}
			return z;
		}
		virtual complex_float_t complex_float() const
		{
			//std::cout << "casting to complex_float_t...\n";
			complex_float_t z;
			switch (type_) {
			case ISMRMRD::ISMRMRD_CXDOUBLE:
				z = *(complex_double_t*)ptr_;
				break;
			case ISMRMRD::ISMRMRD_CXFLOAT:
				z = *(complex_float_t*)ptr_;
				break;
			case ISMRMRD::ISMRMRD_DOUBLE:
				z = float(*(double*)ptr_);
				break;
			case ISMRMRD::ISMRMRD_FLOAT:
				z = *(float*)ptr_;
				break;
			case ISMRMRD::ISMRMRD_INT:
				z = complex_float_t(float(*(int*)ptr_));
				break;
			case ISMRMRD::ISMRMRD_UINT:
				z = complex_float_t(float(*(unsigned int*)ptr_));
				break;
			case ISMRMRD::ISMRMRD_SHORT:
				z = complex_float_t(float(*(short*)ptr_));
				break;
			case ISMRMRD::ISMRMRD_USHORT:
				z = complex_float_t(float(*(unsigned short*)ptr_));
			}
			return z;
		}
		virtual operator float() const
		{
			//std::cout << "casting to float...\n";
			float v;
			complex_float_t c;
			complex_double_t z;
			switch (type_) {
			case ISMRMRD::ISMRMRD_CXDOUBLE:
				z = *(complex_double_t*)ptr_;
				v = float(abs_ ? abs(z) : z.real());
				break;
			case ISMRMRD::ISMRMRD_CXFLOAT:
				c = *(complex_float_t*)ptr_;
				v = abs_ ? abs(c) : c.real();
				break;
			case ISMRMRD::ISMRMRD_DOUBLE:
				v = float(*(double*)ptr_);
				break;
			case ISMRMRD::ISMRMRD_FLOAT:
				v = *(float*)ptr_;
				break;
			case ISMRMRD::ISMRMRD_INT:
				v = float(*(int*)ptr_);
				break;
			case ISMRMRD::ISMRMRD_UINT:
				v = float(*(unsigned int*)ptr_);
				break;
			case ISMRMRD::ISMRMRD_SHORT:
				v = float(*(short*)ptr_);
				break;
			case ISMRMRD::ISMRMRD_USHORT:
				v = float(*(unsigned short*)ptr_);
			}
			return v;
		}
		NumRef& operator=(const NumRef& ref)
		{
			assign(ref);
			return *this;
		}
		virtual void assign(const aNumRef& a_ref)
		{
			const NumRef& ref = (const NumRef&)a_ref;
			//std::cout << "assigning ref...\n";
			switch (type_) {
			case ISMRMRD::ISMRMRD_CXDOUBLE:
				*(complex_double_t*)ptr_ = ref.complex_double();
				break;
			case ISMRMRD::ISMRMRD_CXFLOAT:
				*(complex_float_t*)ptr_ = ref.complex_float();
				break;
			case ISMRMRD::ISMRMRD_DOUBLE:
				*(double*)ptr_ = double(ref);
				break;
			case ISMRMRD::ISMRMRD_FLOAT:
				*(float*)ptr_ = float(ref);
				break;
			case ISMRMRD::ISMRMRD_INT:
				*(int*)ptr_ = int(ref);
				break;
			case ISMRMRD::ISMRMRD_UINT:
				*(unsigned int*)ptr_ = (unsigned int)ref;
				break;
			case ISMRMRD::ISMRMRD_SHORT:
				*(short*)ptr_ = short(ref);
				break;
			case ISMRMRD::ISMRMRD_USHORT:
				*(unsigned short*)ptr_ = (unsigned short)ref;
			}
			//return *this;
		}
		template <typename T>
		NumRef& operator=(std::complex<T> v)
		{
			switch (type_) {
			case ISMRMRD::ISMRMRD_CXDOUBLE:
				*(complex_double_t*)ptr_ = complex_double_t(v);
				break;
			case ISMRMRD::ISMRMRD_CXFLOAT:
				*(complex_float_t*)ptr_ = complex_float_t(v);
				break;
			case ISMRMRD::ISMRMRD_DOUBLE:
				*(double*)ptr_ = double(abs_ ? abs(v) : v.real());
				break;
			case ISMRMRD::ISMRMRD_FLOAT:
				*(float*)ptr_ = float(abs_ ? abs(v) : v.real());
				break;
			case ISMRMRD::ISMRMRD_INT:
				*(int*)ptr_ = int(abs_ ? abs(v) : v.real());
				break;
			case ISMRMRD::ISMRMRD_UINT:
				*(unsigned int*)ptr_ = (unsigned int)(abs_ ? abs(v) : v.real());
				break;
			case ISMRMRD::ISMRMRD_SHORT:
				*(short*)ptr_ = short(abs_ ? abs(v) : v.real());
				break;
			case ISMRMRD::ISMRMRD_USHORT:
				*(unsigned short*)ptr_ = (unsigned short)(abs_ ? abs(v) : v.real());
			}
			return *this;
		}
		template <typename T>
		NumRef& operator=(T v)
		{
			//std::cout << "assigning...\n";
			switch (type_) {
			case ISMRMRD::ISMRMRD_CXDOUBLE:
				*(complex_double_t*)ptr_ = complex_double_t(v);
				break;
			case ISMRMRD::ISMRMRD_CXFLOAT:
				*(complex_float_t*)ptr_ = complex_float_t(v);
				break;
			case ISMRMRD::ISMRMRD_DOUBLE:
				*(double*)ptr_ = double(v);
				break;
			case ISMRMRD::ISMRMRD_FLOAT:
				*(float*)ptr_ = float(v);
				break;
			case ISMRMRD::ISMRMRD_INT:
				*(int*)ptr_ = int(v);
				break;
			case ISMRMRD::ISMRMRD_UINT:
				*(unsigned int*)ptr_ = (unsigned int)v;
				break;
			case ISMRMRD::ISMRMRD_SHORT:
				*(short*)ptr_ = short(v);
				break;
			case ISMRMRD::ISMRMRD_USHORT:
				*(unsigned short*)ptr_ = (unsigned short)v;
			}
			return *this;
		}

	private:
		bool abs_;
		int type_;
		void* ptr_;
	};

}