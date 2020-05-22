//vektorius
#include <memory>


template<typename T>
class Vektorius {
	public:
		//deklaracijos
		typedef T* iterator;
		typedef const T* const_iterator;
		typedef T& adress;
		typedef const T& const_adress;
		
		typedef size_t size_type;
		typedef T value_type;
		//konstruktoriai
		Vektorius(){create();} //default
		Vektorius(T* masyvas); //is masyvo
		explicit Vektorius(size_type n, const T& val = T{}); //explicit
		Vektorius(const Vektorius& v) { create(v.begin(), v.end());	} //kopijavimo
		Vektorius(Vektorius<T>::iterator begin, Vektorius<T>::iterator end) { create(begin, end);	}
		~Vektorius(){ destroy();} //destruktorius
		//funkcijos
		size_type size() const {return limit - data;} //limit - data
		size_type realsize() const;
		//operatoriai
		inline T& operator[] (size_type i) const {return data[i];}
		inline T& operator[] (size_type i) {return data[i];}
		//iteratoriai
		inline iterator begin() { return data;	}
		inline const_iterator begin() const { return data; }
		inline iterator end() { return &data[realsize()];} //limit
		inline const_iterator end() const { return &data[realsize()];}
		//funkcijos
		Vektorius<T>& operator=(const Vektorius<T>& v);
		void push_back(const_adress val);
		T at(size_type t);	
	private:
		//deklaracijos
		iterator data;
		iterator limit;
		iterator avail;
		size_type actualsize;
		std::allocator<T> alloc;
		//funkcijos
		void create();
		void create(size_type, const T&);
		void create(const_iterator, const_iterator);
		void destroy();
		
		void grow();
		void append(const_adress val);
		
};
