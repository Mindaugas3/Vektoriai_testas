#include "Vektorius.h"

template<class T>
Vektorius<T>& Vektorius<T>::operator=(const Vektorius<T>& v){

	if(!(&v == this)){
		this->destroy();
		this->create();
		for(auto it = v.begin(); it != v.end(); ++it){
			this->push_back(*it);
		}
	}

}

template<class T>
void Vektorius<T>::push_back(const T& val){
	if(avail == limit){
		grow();
	}
	actualsize += 1;
	append(val);
}

template <class T> size_t Vektorius<T>::realsize() const{

	return actualsize;
}

template <class T> void Vektorius<T>::create() {
    data = avail = limit = nullptr;
    actualsize = 0;
}

template <class T> void Vektorius<T>::create(size_type n, const T& val) {
    data = alloc.allocate(n); // gra�ina ptr i array pirma elementa    
	limit = avail = data + n; // sustato rodykles i vietas    
	std::uninitialized_fill(data, limit, val); // inicializuoja elementus val reik�me
	actualsize = n;
}

template <class T> void Vektorius<T>::create(const_iterator i, const_iterator j) {
    data = alloc.allocate(j - i); // i�skirti vietos j-i elementams
	limit = avail = std::uninitialized_copy(i, j, data); // nukopijuoja elementus i� intervalo 
	actualsize = (j - i);
}

template <class T> void Vektorius<T>::destroy() {
	if (data) {
	// sunaikinti (atbuline tvarka) sukonstruotus elementus
		iterator it = avail;
		while (it != data) alloc.destroy(--it);// atlaisvinti i�skirta atminti. Turi buti data != nullptr 
		alloc.deallocate(data, limit - data);    
	}// reset'inam pointer'iuss - Vector'ius tu�cias
	data =  limit  =  avail  =  nullptr;
	actualsize = 0;
}

template <class T> void Vektorius<T>::grow() {
	// dvigubai daugiau vietos, nei buvo    
	size_type new_size = std::max(2 * (limit - data), ptrdiff_t(1));
	// i�skirti nauja vieta ir perkopijuoti egzistuojancius elementus    
	iterator new_data = alloc.allocate(new_size);    
	iterator new_avail = std::uninitialized_copy(data, avail, new_data);
	size_type new_actual = actualsize;
	// atlaisvinti sena vieta    
	destroy();
	// reset'int rodykles i naujai i�skirta vieta    
	data = new_data;    
	avail = new_avail;     
	limit = data + new_size;
	actualsize = new_actual;
}
	
// tariame, kad `avail` point'ina i i�skirta, bet neinicializuota vieta
template <class T> void Vektorius<T>::append(const T& val) {
    alloc.construct(avail++, val);

}

template <class T> T Vektorius<T>::at(size_type i){
	if(!(data[i])){
		throw new std::domain_error("Accessing index out of bounds!");
		return nullptr;
	} else {
		return data[i];
	}
}
