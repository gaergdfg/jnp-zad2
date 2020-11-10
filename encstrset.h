#ifndef ENCSTRSET_H
#define ENCSTRSET_H

#ifdef __cplusplus
#include <iostream>
namespace jnp1 {
	extern "C" {
#else
#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#endif

	/*Tworzy nowy zbior i zwraca jego identyfikator.*/
	unsigned long encstrset_new();


	/*Jezeli istnieje zbior o identyfikatorze id, usuwa go, a w przeciwnym przypadku nie
	robi nic.*/
	void encstrset_delete(unsigned long id);


	/*Jezeli istnieje zbior o identyfikatorze id, zwraca liczbe jego elementow, a w
	przeciwnym przypadku zwraca 0.*/
	size_t encstrset_size(unsigned long id);


	/*Jezeli istnieje zbior o identyfikatorze id i element value po zaszyfrowaniu kluczem key
	nie nalezy do tego zbioru, to dodaje ten zaszyfrowany element do zbioru, a w
	przeciwnym przypadku nie robi nic.Szyfrowanie jest symetryczne, za pomoca
	operacji bitowej XOR.Gdy klucz key jest krotszy od value, to nalezy go cyklicznie
	powtorzyc.Wynikiem jest true, gdy element zostal dodany, a false w przeciwnym
	przypadku.*/
	bool encstrset_insert(unsigned long id, const char* value, const char* key);


	/*Jezeli istnieje zbior o identyfikatorze id i element value zaszyfrowany kluczem key
	nalezy do tego zbioru, to usuwa element ze zbioru, a w przeciwnym przypadku nie
	robi nic.Wynikiem jest true, gdy element zostal usuniety, a false w przeciwnym
	przypadku.*/
	bool encstrset_remove(unsigned long id, const char* value, const char* key);


	/*Jezeli istnieje zbior o identyfikatorze id i element value zaszyfrowany kluczem key
	nalezy do tego zbioru, to zwraca true, a w przeciwnym przypadku zwraca false.*/
	bool encstrset_test(unsigned long id, const char* value, const char* key);


	/*Jezeli istnieje zbior o identyfikatorze id, usuwa wszystkie jego elementy, a w
	przeciwnym przypadku nie robi nic.*/
	void encstrset_clear(unsigned long id);


	/*Jezeli istnieja zbiory o identyfikatorach src_id oraz dst_id, to kopiuje zawartosc zbioru
	o identyfikatorze src_id do zbioru o identyfikatorze dst_id, a w przeciwnym przypadku
	nic nie robi.*/
	void encstrset_copy(unsigned long src_id, unsigned long dst_id);

#ifdef __cplusplus
	}
};
#endif

#endif /*ENCSTRSET_H*/
