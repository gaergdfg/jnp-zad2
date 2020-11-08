#include <stddef.h>
#include <stdbool.h>

#ifndef ENCSTRSET_H
#define ENCSTRSET_H


#ifdef __cplusplus
extern "C" {
#endif

	/*Tworzy nowy zbi�r i zwraca jego identyfikator.*/
	unsigned long encstrset_new();


	/*Je�eli istnieje zbi�r o identyfikatorze id, usuwa go, a w przeciwnym przypadku nie
	robi nic.*/
	void encstrset_delete(unsigned long id);


	/*Je�eli istnieje zbi�r o identyfikatorze id, zwraca liczb� jego element�w, a w
	przeciwnym przypadku zwraca 0.*/
	size_t encstrset_size(unsigned long id);


	/*Je�eli istnieje zbi�r o identyfikatorze id i element value po zaszyfrowaniu kluczem key
	nie nale�y do tego zbioru, to dodaje ten zaszyfrowany element do zbioru, a w
	przeciwnym przypadku nie robi nic.Szyfrowanie jest symetryczne, za pomoc�
	operacji bitowej XOR.Gdy klucz key jest kr�tszy od value, to nale�y go cyklicznie
	powt�rzy�.Wynikiem jest true, gdy element zosta� dodany, a false w przeciwnym
	przypadku.*/
	bool encstrset_insert(unsigned long id, const char* value, const char* key);


	/*Je�eli istnieje zbi�r o identyfikatorze id i element value zaszyfrowany kluczem key
	nale�y do tego zbioru, to usuwa element ze zbioru, a w przeciwnym przypadku nie
	robi nic.Wynikiem jest true, gdy element zosta� usuni�ty, a false w przeciwnym
	przypadku.*/
	bool encstrset_remove(unsigned long id, const char* value, const char* key);


	/*Je�eli istnieje zbi�r o identyfikatorze id i element value zaszyfrowany kluczem key
	nale�y do tego zbioru, to zwraca true, a w przeciwnym przypadku zwraca false.*/
	bool encstrset_test(unsigned long id, const char* value, const char* key);


	/*Je�eli istnieje zbi�r o identyfikatorze id, usuwa wszystkie jego elementy, a w
	przeciwnym przypadku nie robi nic.*/
	void encstrset_clear(unsigned long id);


	/*Je�eli istniej� zbiory o identyfikatorach src_id oraz dst_id, to kopiuje zawarto�� zbioru
	o identyfikatorze src_id do zbioru o identyfikatorze dst_id, a w przeciwnym przypadku
	nic nie robi.*/
	void encstrset_copy(unsigned long src_id, unsigned long dst_id);

#ifdef __cplusplus
}
#endif

#endif /*ENCSTRSET_H*/
